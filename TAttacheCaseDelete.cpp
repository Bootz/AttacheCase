/*

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
// ���ӁF�قȂ�X���b�h�����L���� VCL �̃��\�b�h/�֐�/�v���p�e�B��ʂ�
// ���b�h���L�̃I�u�W�F�N�g�ɑ΂��Ă� Synchronize ���g�p�ł��܂��B
//
// Synchronize(&UpdateCaption);
//
// �Ⴆ�� UpdateCaption ���ȉ��̂悤�ɒ�`��
//
// void __fastcall TAttacheCaseDelete::UpdateCaption()
// {
// Form1->Caption = "�X���b�h���珑�������܂���";
// }
// ---------------------------------------------------------------------------
__fastcall TAttacheCaseDelete::TAttacheCaseDelete
(bool CreateSuspended) : TThread(CreateSuspended)
{

Opt = 0;	                //�ʏ�폜
RandClearNum = 1;         //�����������݉�
ZeroClearNum = 1;         //�[���������݉�

ProgressPercentNum = -1;  //�i���p�[�Z���g
ProgressStatusText = "";  //�i���X�e�[�^�X���e
ProgressMsgText = "";

}
//===========================================================================
//�f�X�g���N�^
//===========================================================================
__fastcall TAttacheCaseDelete::~TAttacheCaseDelete(void)
{
//
}
//===========================================================================
//�X���b�h���s
//===========================================================================
void __fastcall TAttacheCaseDelete::Execute()
{

int i;
int FileCount = 0;
int TotalFileCount = 0;
__int64 CountFileSize = 0;
__int64 TotalFileSize = 0;

int ret;
TSearchRec sr;
int Attrs;

String FilePath;

//-----------------------------------
// �S�~���̏ꍇ�̓t�@�C��/�t�H���_��
// ���̂܂܈ړ�
//-----------------------------------
if (Opt == 2) {
	for (i = 0; i < FileList->Count; i++) {
		if ( GoToTrash(FileList->Strings[i]) == false ){
			//�G���[
			return;
		}
	}
	ProgressPercentNum = 100;
	//'����'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_COMPLETE);
	//'�폜������Ɋ������܂����B'
	ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_COMPLETE);
	return;
}

//-----------------------------------
// �폜����t�@�C�����X�g�����擾
//-----------------------------------
ProgressPercentNum = -1;
//'�t�@�C�����X�g�̐���'
ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_LISTING);
//'�폜���邽�߂̏��������Ă��܂�...'
ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_PREPARING);

for (i = 0; i < FileList->Count; i++) {
	ret  = FindFirst(FileList->Strings[i], faAnyFile, sr);
	while (ret == 0) {
		if (sr.Name != "." && sr.Name != "..") {
			if (sr.Attr & faDirectory) {
				//�f�B���N�g��
				GetDeleteFileListInfo(FileList->Strings[i], TotalFileCount, TotalFileSize);
				TotalFileCount++;
			}
			else{
				//�t�@�C��
				TotalFileSize += sr.Size;
				TotalFileCount++;
			}
		}
		ret = FindNext(sr);
	}
}

//-----------------------------------
// �폜
//-----------------------------------
if ( Opt == 0){
	//'�폜���Ă��܂�...'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_DELETING);
}
else if ( Opt == 1 ) {
	//'���S�폜���Ă��܂�...'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_COMPLETE_DELETING);
	//���S�폜�񐔕��~���v�T�C�Y��������
	TotalFileSize =
		TotalFileSize * (RandClearNum + ZeroClearNum > 0 ? RandClearNum + ZeroClearNum : 1 );
}


for (i = 0; i < FileList->Count; i++) {

	FilePath = FileList->Strings[i];
	ret  = FindFirst(FilePath, faAnyFile, sr);

	while (ret == 0) {

		if (sr.Name != "." && sr.Name != "..") {

			//-----------------------------------
			// �f�B���N�g��
			//-----------------------------------
			if (sr.Attr & faDirectory) {
				//�ċA�Ăяo��
				DeleteDirAndFiles(FilePath, FileCount, TotalFileCount, CountFileSize, TotalFileSize);

				//��ɂȂ����f�B���N�g���̍폜
				if ( !RemoveDir(FilePath) ){
					//�폜�Ɏ��s�����Ƃ��͑�����ύX
					Attrs = FileGetAttr(FilePath);
					if (Attrs & faHidden){   //�B���t�@�C�������̂Ƃ��͊O��
						FileSetAttr( FilePath, Attrs & !faHidden);
					}
					if (Attrs & faReadOnly){ //�ǂݎ���p�����̂Ƃ����O��
						FileSetAttr( FilePath, Attrs & !faReadOnly	);
					}
					RemoveDir(FilePath);      //�ă`�������W
				}

				FileCount++;
			}
			//-----------------------------------
			// �t�@�C��
			//-----------------------------------
			else{
				//�ǂݎ���p�Ȃ�O���Ă���
				if ( FileIsReadOnly(FilePath) == true ){
					FileSetReadOnly(FilePath, false);
				}

				//-----------------------------------
				// �ʏ�폜
				//-----------------------------------
				if ( Opt == 0){
					DeleteFile(FilePath);
					FileCount++;
					//�t�@�C�����Ńv���O���X�\��
					ProgressPercentNum = ((float)FileCount/TotalFileCount)*100;
				}
				//-----------------------------------
				// ���S�폜
				//-----------------------------------
				else if ( Opt == 1 ) {
					//�����T�C�Y�Ńv���O���X�\���i�u���S�폜�v�֐����ŏ����j
					if ( CompleteDeleteFile(FilePath, CountFileSize, TotalFileSize) == false ){
						break; //�G���[ or ���[�U�[�L�����Z���Ŕ����Ă���
					}
				}
			}
		}
		ret = FindNext(sr);
	}
}

if (Terminated == true) {
	ProgressPercentNum = 0;
	//'�L�����Z��'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_USER_CANCEL);
	//'�폜�����~����܂����B'
	ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_STOPPED);
}
else{
	ProgressPercentNum = 100;
	//'����'
	ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_COMPLETE);
	//'�폜������Ɋ������܂����B'
	ProgressMsgText = LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_COMPLETE);
}


}
//===========================================================================
// �폜����t�@�C�����X�g���i�t�@�C�����A���v�T�C�Y�j�����W����
//===========================================================================
void __fastcall TAttacheCaseDelete::
	GetDeleteFileListInfo(String DirPath, int &TotalFileCount, __int64 &TotalFileSize)
{

TSearchRec sr;
String FilePath;

int ret  = FindFirst(DirPath + "\\*.*", faAnyFile, sr);

while (ret == 0) {

	if (sr.Name != "." && sr.Name != "..") {

		FilePath = IncludeTrailingPathDelimiter(DirPath)+sr.Name;

		if (sr.Attr & faDirectory) {
			// �ċA�Ăяo��
			GetDeleteFileListInfo(FilePath, TotalFileCount, TotalFileSize);
			TotalFileCount++;	//�f�B���N�g����
		}
		else{
			TotalFileSize += sr.Size;
			TotalFileCount++;
		}

	}
	ret = FindNext(sr);

}

FindClose(sr);

return;

}
//===========================================================================
// �f�B���N�g��/�t�@�C�����ċA�I�ɍ폜����
//===========================================================================
void __fastcall TAttacheCaseDelete::DeleteDirAndFiles
	(String DirPath, int &FileCount, int TotalFileCount, __int64 &CountFileSize, __int64 TotalFileSize)
{

TSearchRec sr;
String FilePath;

int Attrs;
int ret  = FindFirst(DirPath + "\\*.*", faAnyFile, sr);

while (ret == 0) {

	if (sr.Name != "." && sr.Name != "..") {

		FilePath = IncludeTrailingPathDelimiter(DirPath)+sr.Name;

		//-----------------------------------
		// �f�B���N�g��
		//-----------------------------------
		if (sr.Attr & faDirectory) {

			// �ċA�Ăяo��
			DeleteDirAndFiles(FilePath, FileCount, TotalFileCount, CountFileSize, TotalFileSize);

			//��ɂȂ����f�B���N�g���̍폜
			if ( !RemoveDir(FilePath) ){
				//�폜�Ɏ��s�����Ƃ��͑�����ύX
				Attrs = FileGetAttr(FilePath);
				if (Attrs & faHidden){   //�B���t�@�C�������̂Ƃ��͊O��
					FileSetAttr( FilePath, Attrs & !faHidden);
				}
				if (Attrs & faReadOnly){ //�ǂݎ���p�����̂Ƃ����O��
					FileSetAttr( FilePath, Attrs & !faReadOnly	);
				}
				RemoveDir(FilePath);      //�ă`�������W
			}
			FileCount++;

		}
		//-----------------------------------
		// �t�@�C��
		//-----------------------------------
		else{

			//�ǂݎ���p�Ȃ�O���Ă���
			if ( FileIsReadOnly(FilePath) == true ){
				FileSetReadOnly(FilePath, false);
			}

			if ( Opt == 0){                                  //�ʏ�폜
				DeleteFile(FilePath);
				FileCount++;
				//�t�@�C�����Ńv���O���X�\��
				ProgressPercentNum = ((float)FileCount/TotalFileCount)*100;
			}
			else if ( Opt == 1 ) {                           //���S�폜
				//�����T�C�Y�Ńv���O���X�\���i�֐����ŏ����j
				if ( CompleteDeleteFile(FilePath, CountFileSize, TotalFileSize) == false ){
					break; //�G���[ or ���[�U�[�L�����Z���Ŕ����Ă���
				}
			}

		}

	}
	ret = FindNext(sr);

}

FindClose(sr);

return;

}
//===========================================================================
//�t�@�C���̊��S�폜
//===========================================================================
bool __fastcall TAttacheCaseDelete::
	CompleteDeleteFile(String FilePath, __int64 &CountSize, __int64 TotalFileSize)
{

int i, c;
int res;
char buffer[LARGE_BUF];

HANDLE  hFile;
DWORD uniWriteByte;

int fh = FileOpen(FilePath, fmShareDenyNone);
if ( fh == -1 )return(false);

__int64 uiWriteSize;
__int64 uiFileSize = FileSeek(fh,(__int64)0, 2);
FileClose(fh);

//�ǂݎ���p�Ȃ�O���Ă���
if ( FileIsReadOnly(FilePath) == true ){
	FileSetReadOnly(FilePath, false);
}

//-----------------------------------
//�����_���Ȓl�Ŏw��񐔏������݂��s��
//-----------------------------------
for ( i = 0; i < RandClearNum; i++ ){

	//'�������������݁A���S�폜���s���Ă��܂�...(Step:%d/%d)'
	ProgressMsgText =
		String().Format(LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_WRITE_RAND),
										 ARRAYOFCONST((i + 1, RandClearNum+ZeroClearNum))) + "\n" + FilePath;

	//�L���b�V���𒼐ڃf�B�X�N�֏�������
	hFile = CreateFileW(
		FilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);

	if ( hFile != INVALID_HANDLE_VALUE ){

		uiWriteSize = 0;

		while ( uiWriteSize < uiFileSize ){

			fillrand(buffer, LARGE_BUF);

			//�����_���̒l�Ŗ��ߐs����
			if ( WriteFile( hFile, buffer, LARGE_BUF, &uniWriteByte, NULL) == 0 ){
				break;
			}

			uiWriteSize+=uniWriteByte;
			CountSize+=uniWriteByte;

			//�r���L�����Z�����ꂽ�Ƃ��̏���
			if ( Terminated == true ){
				//'���~����Ɗ��S�ɍ폜����Ȃ��\��������܂��B'+#13+
				//'����ł����~���܂����H';
				MsgText = LoadResourceString(&Msgdelete::_MSG_CONFIRM_COMPLETE_DELETE_STOP);
				MsgType = mtConfirmation;
				MsgButtons = TMsgDlgButtons() << mbYes << mbNo;
				MsgDefaultButton = mbNo;
				Synchronize(&PostConfirmMessageForm);
				//�u�͂��v
				if (MsgReturnVal == mrYes){
					CloseHandle( hFile );
					return(false);
				}
			}

			//�v���O���X�\��
			ProgressPercentNum = ((float)CountSize/TotalFileSize)*100;

		}//while;

	}
	else{
		//'�t�@�C���폜���ɃG���[���������܂����B�t�@�C�����J�����Ƃ��ł��܂���B'
		MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_NOT_FILE_OPEN) + "\n" + FilePath;
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		CloseHandle( hFile );
		return(false);

	}//end if;

	CloseHandle( hFile );

}//loop;

//-----------------------------------
//NULL�l�Ŏw��񐔏�������
//-----------------------------------

for ( c = 0; c < LARGE_BUF; c++ ){
	buffer[c] = NULL;
}

for ( i = 0; i < ZeroClearNum; i++ ){

	//'�[��(NULL)���������݁A���S�폜���s���Ă��܂�...(Step:%d/%d)'
	ProgressMsgText =
		String().Format(LoadResourceString(&Msgdelete::_LABEL_STATUS_DETAIL_WRITE_ZERO),
										 ARRAYOFCONST((i + 1 + RandClearNum, RandClearNum+ZeroClearNum))) +
										 "\n" + FilePath;

	//�L���b�V���𒼐ڃf�B�X�N�֏�������
	hFile = CreateFileW(
		FilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);

	if ( hFile != INVALID_HANDLE_VALUE ){

		uiWriteSize = 0;

		while ( uiWriteSize < uiFileSize ){

			//NULL�l�Ŗ��ߐs����
			if ( WriteFile( hFile, buffer, LARGE_BUF, &uniWriteByte, NULL) == 0 ){
				break;
			}
			uiWriteSize+=uniWriteByte;
			CountSize+=uniWriteByte;

			//�r���L�����Z�����ꂽ�Ƃ��̏���
			if ( Terminated == true ){
				//'���~����Ɗ��S�ɍ폜����Ȃ��\��������܂��B'+#13+
				//'����ł����~���܂����H';
				MsgText = LoadResourceString(&Msgdelete::_MSG_CONFIRM_COMPLETE_DELETE_STOP);
				MsgType = mtConfirmation;
				MsgButtons = TMsgDlgButtons() << mbYes << mbNo;
				MsgDefaultButton = mbNo;
				Synchronize(&PostConfirmMessageForm);
				//�u�͂��v
				if (MsgReturnVal == mrYes){
					CloseHandle( hFile );
					return(false);
				}
			}

			//�v���O���X�\��
			ProgressPercentNum = ((float)CountSize/TotalFileSize)*100;

		}//while;

	}
	else{
		//'�t�@�C���폜���ɃG���[���������܂����B�t�@�C�����J�����Ƃ��ł��܂���B'
		MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_NOT_FILE_OPEN) + "\n" + FilePath;
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		CloseHandle( hFile );
		return(false);

	}//end if;

	CloseHandle( hFile );

}//loop;

//-----------------------------------
//����Ƀt�@�C���T�C�Y��0�o�C�g�ɂ���

hFile = CreateFileW(
	FilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
	NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING, NULL);//FILE_FLAG_WRITE_THROUGH

CloseHandle( hFile );

//-----------------------------------
//�悤�₭�����ō폜

DeleteFile(FilePath);

return(true);


}//end CompleteDeleteFile;
//===========================================================================
//���ݔ��ւ̈ړ�
//===========================================================================
bool __fastcall TAttacheCaseDelete::GoToTrash(String Path)
{

ProgressPercentNum = -1;
//'���ݔ��ֈړ����Ă��܂�...'
ProgressStatusText = LoadResourceString(&Msgdelete::_LABEL_STATUS_TITLE_GO_TO_TRASH);
ProgressMsgText = Path;

if (FileExists(Path) == true) {
}
else{
	if (DirectoryExists(Path) == true) {
		Path = ExcludeTrailingPathDelimiter(Path);
	}
	else{
		//'���ݔ��ւ̍폜�Ɏ��s���܂����B'+#13+
		//'�ꕔ�̃t�@�C��/�t�H���_���폜�ł����Ɏc���Ă��܂����\��������܂��B';
		MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_GO_TO_TRASH_FAILED);
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		return(false);
	}
}

const int len = Path.Length() + 2;  //�I�[\0\0
wchar_t* from = new wchar_t[len];
wcscpy(from, Path.c_str());
from[len-1] = 0;

SHFILEOPSTRUCTW sh;
ZeroMemory(&sh, sizeof(SHFILEOPSTRUCT));
sh.hwnd = Application->Handle;
sh.wFunc = FO_DELETE;              // �S�~���֎̂Ă�
sh.pFrom = from;                   // �t�@�C���̃|�C���^
sh.pTo = NULL;
// Undo��, �m�F�Ȃ��i���ł����ʓI��Undo�͕s�\�ɂȂ�݂����j
sh.fFlags= FOF_ALLOWUNDO + FOF_NOCONFIRMATION;

if ( SHFileOperationW(&sh) != 0 ){
	//'���ݔ��ւ̍폜�Ɏ��s���܂����B'+#13+
	//'�ꕔ�̃t�@�C��/�t�H���_���폜�ł����Ɏc���Ă��܂����\��������܂��B';
	MsgText = LoadResourceString(&Msgdelete::_MSG_ERROR_GO_TO_TRASH_FAILED);
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	return(false);
}

delete[] from;

//�t�H���_���̕\���X�V
SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_PATH, Path.c_str(), 0);

return(true);


}//end GotoTrashOneFile;
//===========================================================================
// �����_���l�̐����iCRNG�j
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
//���C���t�H�[���Ɋm�F���b�Z�[�W�𓊂��ď����𒆒f����
//===========================================================================
void __fastcall TAttacheCaseDelete::PostConfirmMessageForm()
{

//�O���[�o���ϐ�(private)�Ƃ��Ē�`���Ă���

//String MsgText;
//TMsgDlgType MsgType;
//TMsgDlgButtons MsgButtons;
//TMsgDlgBtn MsgDefaultButton;

MsgReturnVal =
	Form1->ShowConfirmMassageForm(MsgText, MsgType, MsgButtons, MsgDefaultButton);


}
//===========================================================================




