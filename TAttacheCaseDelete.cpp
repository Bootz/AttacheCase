﻿/*

'AttacheCase' - file encryption software for Windows.

TAttacheCaseDelete Class file.

Copyright (C) 2012 M.Hibara, All rights reserved.
http://hibara.org/

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see

http://www.gnu.org/licenses/

*/
//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
#include "TAttacheCaseDelete.h"

#pragma package(smart_init)
// ---------------------------------------------------------------------------
// 注意：異なるスレッドが所有する VCL のメソッド/関数/プロパティを別の
// レッド所有のオブジェクトに対しては Synchronize を使用できます。
//
// Synchronize(&UpdateCaption);
//
// 例えば UpdateCaption を以下のように定義し
//
// void __fastcall TAttacheCaseDelete::UpdateCaption()
// {
// Form1->Caption = "スレッドから書き換えました";
// }
// ---------------------------------------------------------------------------
__fastcall TAttacheCaseDelete::TAttacheCaseDelete
(bool CreateSuspended) : TThread(CreateSuspended)
{

DeleteList = new TStringList;

Opt = 0;	                     //通常削除
RandClearNum = 0;              //乱数書き込み回数
ZeroClearNum = 0;              //ゼロ書き込み回数

ProgressPercentNum = -1;       //進捗パーセント
ProgressStatusText = "";       //進捗ステータス
ProgressMsgText = "";          //進捗メッセージ

StatusNum = 0;                 //ステータス表示内容番号
MsgErrorString = "";           //エラーメッセージ

}
//===========================================================================
//デストラクタ
//===========================================================================
__fastcall TAttacheCaseDelete::~TAttacheCaseDelete(void)
{

delete DeleteList;

}
//===========================================================================
//スレッド実行
//===========================================================================
void __fastcall TAttacheCaseDelete::Execute()
{

int i;
int FileCount = 0;
int TotalFileCount = 0;
__int64 CountFileSize = 0;
__int64 TotalFileSize = 0;

int ret;
int ErrorNum;
TSearchRec sr;
int Attrs;

String FilePath;

//-----------------------------------
// ゴミ箱の場合はファイル/フォルダ毎
// そのまま移動
//-----------------------------------
if (Opt == 2) {
	for (i = 0; i < DeleteFileList->Count; i++) {
		if (Terminated == true) {
			goto LabelStop;
		}

		if ( GoToTrash(DeleteFileList->Strings[i]) == false ){
			//エラー
			goto LabelStop;
		}
	}

	ProgressPercentNum = 100;
	//'完了'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_COMPLETE);
	//'削除が正常に完了しました。'
	ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_COMPLETE);
	return;

}

//----------------------------------------------------
// 削除ファイルリスト情報（ファイル数、サイズ）を取得
//----------------------------------------------------
ProgressPercentNum = -1;
//'ファイルリストの生成'
ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_LISTING);
//'削除するための準備をしています...'
ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_PREPARING);

for (i = 0; i < DeleteFileList->Count; i++) {

	if ( FindFirst(DeleteFileList->Strings[i], faAnyFile, sr) == 0 ){
		do {
			if (sr.Name != "." && sr.Name != "..") {
				if (sr.Attr & faDirectory) {
					//ディレクトリ
					DeleteList->Add(DeleteFileList->Strings[i]);
					if ( (ErrorNum = GetDeleteFileListInfo(DeleteFileList->Strings[i], DeleteList, TotalFileCount, TotalFileSize)) < 0 ){
						FindClose(sr);
						if (ErrorNum == -1) {
							goto LabelStop;
						}
						else{
							goto LabelError;
						}
					}
					TotalFileCount++;
				}
				else{
					//ファイル
					DeleteList->Add(DeleteFileList->Strings[i]);
					TotalFileSize += sr.Size;
					TotalFileCount++;
				}
			}

		}while(FindNext(sr) == 0 && Terminated == true);

		FindClose(sr);

		if (Terminated == true) {
			goto LabelStop;
		}

	}
}

//-----------------------------------
// 削除、または完全削除
//-----------------------------------
if ( Opt == 0){
	//'削除しています...'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_DELETING);
}
else if ( Opt == 1 ) {
	//'完全削除しています...'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_COMPLETE_DELETING);
	//完全削除回数分×合計サイズが増える
	TotalFileSize = TotalFileSize * (RandClearNum + ZeroClearNum > 0 ? RandClearNum + ZeroClearNum : 1 );
}


//-----------------------------------
// つくったリストから削除実行
//-----------------------------------
for (i = DeleteList->Count-1; i > -1; i--) {

	FilePath = DeleteList->Strings[i];

	//-----------------------------------
	// ファイル
	//-----------------------------------
	if (FileExists(FilePath) == true) {

		//読み取り専用なら外してから
		if ( FileIsReadOnly(FilePath) == true ){
			FileSetReadOnly(FilePath, false);
		}

		//-----------------------------------
		// 通常削除
		//-----------------------------------
		if ( Opt == 0){
			DeleteFile(FilePath);
			FileCount++;
			//ファイル数でプログレス表示
			ProgressPercentNum = ((float)FileCount/TotalFileCount)*100;
		}
		//-----------------------------------
		// 完全削除
		//-----------------------------------
		else if ( Opt == 1 ) {
			//処理サイズでプログレス表示（「完全削除」関数内で処理）
			if ( CompleteDeleteFile(FilePath, CountFileSize, TotalFileSize) == false ){
				goto LabelError;
			}
		}

	}
	//-----------------------------------
	// ディレクトリ
	//-----------------------------------
	else{

		//空になったディレクトリの削除
		if ( RemoveDir(FilePath) == false ){
			//削除に失敗したときは属性を変更
			Attrs = FileGetAttr(FilePath);
			if (Attrs & faHidden){   //隠しファイル属性のときは外す
				FileSetAttr( FilePath, Attrs & !faHidden);
			}
			if (Attrs & faReadOnly){ //読み取り専用属性のときも外す
				FileSetAttr( FilePath, Attrs & !faReadOnly	);
			}
			RemoveDir(FilePath);     //再チャレンジ
		}

	}

	if (Terminated == true) {
		goto LabelStop;
	}


}//end for (i = DeleteList->Count-1; i > -1; i--);


ProgressPercentNum = 100;
//'完了'
ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_COMPLETE);
//'削除が正常に完了しました。'
ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_COMPLETE);

StatusNum = 1;
return;

//-----------------------------------
// エラー
//-----------------------------------
LabelError:

	ProgressPercentNum = 0;
	//'エラー'
	ProgressStatusText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_TITLE_ERROR);
	//'削除に失敗しました。'
	ProgressMsgText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_DETAIL_FAILED);

	StatusNum = -1;

	return;


//-----------------------------------
// ユーザーキャンセル
//-----------------------------------
LabelStop:

	ProgressPercentNum = 0;
	//'キャンセル'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_USER_CANCEL);
	//'削除が中止されました。'
	ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_STOPPED);

	StatusNum = -2;

	return;


}
//===========================================================================
// 削除するファイルリスト情報（ファイル数、合計サイズ）を収集する
//===========================================================================
int __fastcall TAttacheCaseDelete::
	GetDeleteFileListInfo(String DirPath, TStringList *DelList, int &TotalFileCount, __int64 &TotalFileSize)
{

TSearchRec sr;

String FilePath;

if ( FindFirst(IncludeTrailingPathDelimiter(DirPath) + "*", faAnyFile, sr) == 0 ){

	do {

		if (sr.Name != "." && sr.Name != "..") {

			FilePath = IncludeTrailingPathDelimiter(DirPath)+sr.Name;

			if (sr.Attr & faDirectory) {
				DelList->Add(FilePath);
				// 再帰呼び出し
				GetDeleteFileListInfo(FilePath, DelList, TotalFileCount, TotalFileSize);
				TotalFileCount++;	//ディレクトリ分
			}
			else{
				DelList->Add(FilePath);
				TotalFileSize += sr.Size;
				TotalFileCount++;
			}

		}

	}while(FindNext(sr) == 0 && Terminated == false);

	FindClose(sr);

	if (Terminated == true) {
		return(-2);
	}

}

return(1);

}
//===========================================================================
//ファイルの完全削除
//===========================================================================
int __fastcall TAttacheCaseDelete::
	CompleteDeleteFile(String FilePath, __int64 &CountSize, __int64 TotalFileSize)
{

int i, c;
int res;
char buffer[LARGE_BUF];

float ProgressPercentNumF;

HANDLE  hFile;
DWORD uniWriteByte;

int fh = FileOpen(FilePath, fmShareDenyNone);
if ( fh == -1 )return(false);

__int64 uiWriteSize;
__int64 uiFileSize = FileSeek(fh,(__int64)0, 2);
FileClose(fh);

//読み取り専用なら外しておく
if ( FileIsReadOnly(FilePath) == true ){
	FileSetReadOnly(FilePath, false);
}

//-----------------------------------
//ランダムな値で指定回数書き込みを行う
//-----------------------------------
for ( i = 0; i < RandClearNum; i++ ){

	//'乱数を書き込み、完全削除を行っています...(Step:%d/%d)'
	ProgressMsgText =
		String().Format(LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_WRITE_RAND),
										 ARRAYOFCONST((i + 1, RandClearNum+ZeroClearNum))) + "\n" + FilePath;

	//キャッシュを直接ディスクへ書き込む
	hFile = CreateFileW(
		FilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);

	if ( hFile != INVALID_HANDLE_VALUE ){

		uiWriteSize = 0;

		while ( uiWriteSize < uiFileSize ){

			fillrand(buffer, LARGE_BUF);

			//ランダムの値で埋め尽くす
			if ( WriteFile( hFile, buffer, LARGE_BUF, &uniWriteByte, NULL) == 0 ){
				break;
			}

			uiWriteSize+=uniWriteByte;
			CountSize+=uniWriteByte;

			//途中キャンセルされたときの処理
			if ( Terminated == true ){
				CloseHandle( hFile );
				DeleteFile(FilePath);  //ふつうに削除する
				return(-2);
			}

			//プログレス表示
			ProgressPercentNumF = (float)CountSize/TotalFileSize;
			ProgressPercentNum = (int)(ProgressPercentNumF*100);
			if (TotalFileSize < 104857600) {	// 100MB未満
				ProgressPercentNumText = IntToStr(ProgressPercentNum)+"%";
			}
			else{
				ProgressPercentNumText = FloatToStrF(ProgressPercentNumF*100, ffNumber, 4, 1)+"%";
			}

		}//while;

	}
	else{
		//'ファイル削除中にエラーが発生しました。ファイルを開くことができません。'
		MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_NOT_FILE_OPEN) + "\n" + FilePath;
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		CloseHandle( hFile );
		return(-1);

	}//end if;

	CloseHandle( hFile );

}//loop;

//-----------------------------------
//NULL値で指定回数書き込む
//-----------------------------------

for ( c = 0; c < LARGE_BUF; c++ ){
	buffer[c] = NULL;
}

for ( i = 0; i < ZeroClearNum; i++ ){

	//'ゼロ(NULL)を書き込み、完全削除を行っています...(Step:%d/%d)'
	ProgressMsgText =
		String().Format(LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_WRITE_ZERO),
										 ARRAYOFCONST((i + 1 + RandClearNum, RandClearNum+ZeroClearNum))) +
										 "\n" + FilePath;

	//キャッシュを直接ディスクへ書き込む
	hFile = CreateFileW(
		FilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);

	if ( hFile != INVALID_HANDLE_VALUE ){

		uiWriteSize = 0;

		while ( uiWriteSize < uiFileSize ){

			//NULL値で埋め尽くす
			if ( WriteFile( hFile, buffer, LARGE_BUF, &uniWriteByte, NULL) == 0 ){
				break;
			}
			uiWriteSize+=uniWriteByte;
			CountSize+=uniWriteByte;

			//途中キャンセルされたときの処理
			if ( Terminated == true ){
				CloseHandle( hFile );
				DeleteFile(FilePath);  //ふつうに削除する
				return(-2);
			}

			//プログレス表示
			ProgressPercentNumF = (float)CountSize/TotalFileSize;
			ProgressPercentNum = (int)(ProgressPercentNumF*100);
			if (TotalFileSize < 104857600) {	// 100MB未満
				ProgressPercentNumText = IntToStr(ProgressPercentNum)+"%";
			}
			else{
				ProgressPercentNumText = FloatToStrF(ProgressPercentNumF*100, ffNumber, 4, 1)+"%";
			}

		}//while;

	}
	else{
		//'ファイル削除中にエラーが発生しました。ファイルを開くことができません。'
		MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_NOT_FILE_OPEN) + "\n" + FilePath;
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		CloseHandle( hFile );
		return(-1);

	}//end if;

	CloseHandle( hFile );

}//loop;

//-----------------------------------
//さらにファイルサイズを0バイトにする

hFile = CreateFileW(
	FilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
	NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING, NULL);//FILE_FLAG_WRITE_THROUGH

CloseHandle( hFile );

//-----------------------------------
//ようやくここで削除

DeleteFile(FilePath);

return(1);


}//end CompleteDeleteFile;
//===========================================================================
//ごみ箱への移動
//===========================================================================
bool __fastcall TAttacheCaseDelete::GoToTrash(String Path)
{

ProgressPercentNum = -1;
//'ごみ箱へ移動しています...'
ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_GO_TO_TRASH);
ProgressMsgText = Path;

if (FileExists(Path) == true) {
}
else{
	if (DirectoryExists(Path) == true) {
		Path = ExcludeTrailingPathDelimiter(Path);
	}
	else{
		//'ごみ箱への削除に失敗しました。'+#13+
		//'一部のファイル/フォルダが削除できずに残ってしまった可能性があります。';
		MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_GO_TO_TRASH_FAILED);
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		return(false);
	}
}

const int len = Path.Length() + 2;  //終端\0\0
wchar_t* from = new wchar_t[len];
wcscpy(from, Path.c_str());
from[len-1] = 0;

SHFILEOPSTRUCTW sh;
ZeroMemory(&sh, sizeof(SHFILEOPSTRUCT));
sh.hwnd = Application->Handle;
sh.wFunc = FO_DELETE;              // ゴミ箱へ捨てる
sh.pFrom = from;                   // ファイルのポインタ
sh.pTo = NULL;
// Undo可, 確認なし（※でも結果的にUndoは不可能になるみたい）
sh.fFlags= FOF_ALLOWUNDO + FOF_NOCONFIRMATION;

if ( SHFileOperationW(&sh) != 0 ){
	//'ごみ箱への削除に失敗しました。'+#13+
	//'一部のファイル/フォルダが削除できずに残ってしまった可能性があります。';
	MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_GO_TO_TRASH_FAILED);
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	return(false);
}

delete[] from;

//フォルダ内の表示更新
SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_PATH, Path.c_str(), 0);

return(true);


}//end GotoTrashOneFile;
//===========================================================================
// ランダム値の生成（CRNG）
//===========================================================================
void TAttacheCaseDelete::fillrand(char *buf, const int len)
{

static unsigned long count = 4;
static char          r[4];
int                  i;

// ISAAC ( Cryptographic Random Number Generator )
randctx ctx;

// init
randinit(&ctx, 1);

for(i = 0; i < len; ++i){
	if(count == 4){
		*(unsigned long*)r = rand(&ctx);
		count = 0;
	}
	buf[i] = r[count++];
}

}
//===========================================================================
//メインフォームに確認メッセージを投げて処理を中断する
//===========================================================================
void __fastcall TAttacheCaseDelete::PostConfirmMessageForm()
{

//グローバル変数(private)として定義してある

//String MsgText;
//TMsgDlgType MsgType;
//TMsgDlgButtons MsgButtons;
//TMsgDlgBtn MsgDefaultButton;

MsgReturnVal =
	Form1->ShowConfirmMassageForm(MsgText, MsgType, MsgButtons, MsgDefaultButton);


}
//===========================================================================




