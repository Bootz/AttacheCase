/*

'AttacheCase' - file encryption software for Windows.

TAttacheCaseFileDecrypt2 Class file.

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
#include "TAttacheCaseFileDecrypt2.h"

#pragma package(smart_init)
// ---------------------------------------------------------------------------
// ���ӁF�قȂ�X���b�h�����L���� VCL �̃��\�b�h/�֐�/�v���p�e�B��ʂ�
// ���b�h���L�̃I�u�W�F�N�g�ɑ΂��Ă� Synchronize ���g�p�ł��܂��B
//
// Synchronize(&UpdateCaption);
//
// �Ⴆ�� UpdateCaption ���ȉ��̂悤�ɒ�`��
//
// void __fastcall TAttacheCaseFileEncode::UpdateCaption()
// {
// Form1->Caption = "�X���b�h���珑�������܂���";
// }
// ---------------------------------------------------------------------------
__fastcall TAttacheCaseFileDecrypt2::TAttacheCaseFileDecrypt2
(bool CreateSuspended) : TThread(CreateSuspended)
{

for (int i = 0; i < 32; i++) {
	key[i] = 0;
}

fCompare = false;        // �R���y�A

ProgressPercentNum = -1; // �i���p�[�Z���g
ProgressStatusText = ""; // �i���X�e�[�^�X���e

AtcFilePath = "";        // ���͂���Í����t�@�C��
OutDirPath = "";         // �o�͂���f�B���N�g��

NumOfTrials = 1;         // �p�X���[�h���͎��s��

StatusNum = -1;          // �������ʃX�e�[�^�X
												 //   1: ��������
												 //   0: ���[�U�[�L�����Z��
												 //  -1: �p�X���[�h���̓G���[
												 //  -2: �����G���[

}
//===========================================================================
//�f�X�g���N�^
//===========================================================================
__fastcall TAttacheCaseFileDecrypt2::~TAttacheCaseFileDecrypt2(void)
{

//

}
//===========================================================================
//�X���b�h���s
//===========================================================================
void __fastcall TAttacheCaseFileDecrypt2::Execute()
{

int i, len;

// �o�b�t�@
char source_buffer[BUF_SIZE];
char temp_buffer[BUF_SIZE];
char chain_buffer[BUF_SIZE];
char output_buffer[LARGE_BUF_SIZE];
char *headerbuffer;

String FilePath, FileName;

// �t�@�C���X�g���[��
TFileStream *fsIn;
TFileStream *fsOut;
bool fInputFileOpen = false;
bool fOutputFileOpen = false;

float free_space_required;
__int64 TotalSize, AllTotalSize;
__int64 CurrentDriveFreeSpaceSize;

int ret;	//�o�b�t�@�o�͂̕Ԓl
int FileIndex = 0;

char token[16];
const char charTokenString[16] = "_AttacheCaseData";         //�����̐��ۂɎg��
String AtcFileTokenString;                                   //�Í����t�@�C���̃g�[�N���i������j
String AtcFileCreateDateString;                              //�Í����t�@�C���̐��������i������j

//�����t�@�C��/�t�H���_�[�͂��ׂď㏑�����ĕ�������
//�i���[�U�[���_�C�A���O�Łu���ׂĂ͂��v��I�������Ƃ� = true �j
fOverwirteYesToAll = false;
//�u���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ���v�ꎞ�I�Ȑݒ�
fTempOpenFile = fOpenFile;
//�t�H���_�[����x�J�������i�[���t�H���_�[���ׂĂ��J���Ȃ��悤�Ɂj
fOpenFolderOnce = false;

// �o�͂���f�B���N�g��
OutDirPath = IncludeTrailingPathDelimiter(OutDirPath);

// �����w�b�_�T�C�Y�i�f�[�^�T�u�o�[�W�����A�j��ݒ�Ȃǁj
int PlaneHeaderSize = 0;
// �Í��������̃w�b�_�T�C�Y
int EncryptHeaderSize = 0;

int DataVersion;      // ver.2.00�`�� "5", ver.2.70�`�� "6"
int AlgorismType;

char reserved;        // 0
//int TypeLimits;     // �~�X�^�C�v�� 0�`10  �i�O���[�o��:public�錾�Ƃ����j
//bool fDestroy;      // �j�󂷂邩�ۂ� 0 or 1 �i�O���[�o��:public�錾�Ƃ����j

String PrefixString;	//�t�@�C�����X�g�̐ړ����iFn_*, U_*�j

int flush, status;    // zlib
z_stream z;           // zlib���C�u�����Ƃ��Ƃ肷�邽�߂̍\����

//�w�b�_�f�[�^����K�v�������o�����߂�
TMemoryStream *pms;   // �������X�g���[��

int idx;
TStringList *DataList;
TStringList *tsv;

TStringList *FileList = new TStringList();  // 0: �t�@�C����
__int64 *FileSizeList = 0;               // 1: �t�@�C���T�C�Y�i�t�H���_��-1�j
int *FileAttrList     = 0;               // 2: ����
int *FileDtChangeList = 0;               // 3: �X�V��
int *FileTmChangeList = 0;               // 4: �X�V��
int *FileDtCreateList = 0;               // 5: �쐬��
int *FileTmCreateList = 0;               // 6: �쐬��

int rest;
int buf_size;

//-----------------------------------
// �����̃w�b�_���e�`�F�b�N

try {
#ifdef EXE_OUT //���Ȏ��s�`���i���g���J���j
	fsIn = new TFileStream(AtcFilePath, fmShareDenyNone);
#else
	fsIn = new TFileStream(AtcFilePath, fmOpenRead);
#endif
}
catch(...) {
	//'��������t�@�C�����J���܂���B���̃A�v���P�[�V�������g�p���̉\��������܂��B'
	MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_FILE_OPEN);
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	goto LabelError;
}

fInputFileOpen = true;

// �����w�b�_�T�C�Y���擾
fsIn->Read(&PlaneHeaderSize, sizeof(int));
// �g�[�N�����擾
fsIn->Read(token, 16);

if (memcmp(token, charTokenString, 16) != 0 ) {

	//--------------------------------------------------------
	//���͎��Ȏ��s�`���t�@�C���H�i�g���q�U������Ă���ꍇ���j
	//--------------------------------------------------------
	// �T�C�Y���Ď擾
	fsIn->Seek(-(__int64)sizeof(__int64), TSeekOrigin::soEnd);
	fsIn->Read(&AllTotalSize, sizeof(__int64));
	// �ʒu��߂�
	fsIn->Seek(-(AllTotalSize + sizeof(__int64)), TSeekOrigin::soEnd);
	// ������x�A�����w�b�_�T�C�Y��ǂݍ���
	fsIn->Read(&PlaneHeaderSize, sizeof(int));
	// ������x�A�g�[�N�����擾
	fsIn->Read(token, 16);

	// �g�[�N�����ă`�F�b�N
	if (memcmp(token, charTokenString, 16) != 0 ) {
		if (token == "_Atc_Broken_Data") {
			//'��������t�@�C�����J���܂���B���̈Í����t�@�C���͔j�󂳂�Ă��܂��B'
			MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_FILE_BROKEN);
			MsgType = mtError;
			MsgButtons = TMsgDlgButtons() << mbOK;
			MsgDefaultButton = mbOK;
			Synchronize(&PostConfirmMessageForm);
		}
		else {
			// '�Í����t�@�C���ł͂���܂���B�A�^�b�V�F�P�[�X�ɂ���ĈÍ������ꂽ�t�@�C���łȂ����A'+#13+
			// '�t�@�C�������Ă���\��������܂��B'
			MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_FILE_NOT_ATC);
			MsgType = mtError;
			MsgButtons = TMsgDlgButtons() << mbOK;
			MsgDefaultButton = mbOK;
			Synchronize(&PostConfirmMessageForm);
		}
		goto LabelError;
	}

}

//-----------------------------------
// �f�[�^�o�[�W�����`�F�b�N
//-----------------------------------
DataVersion = -1;
fsIn->Read(&DataVersion, sizeof(int));

if (DataVersion > ATC_DATA_FILE_VERSION && DataVersion < 200) {
	//'�f�[�^�o�[�W�������������܂��B�����ł��܂���B'+#13+
	//'�t�@�C���͏�ʃo�[�W�����̃A�^�b�V�F�P�[�X�ňÍ�������Ă��܂��B'+#13+
	//'�ŐV�ł���肵�ĕ��������݂Ă��������B';
	MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_FILE_HIGHER_VERSION);
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	goto LabelError;
}
else if (DataVersion <= 103) {

	// Blowfish�ňÍ������ꂽ�t�@�C��
	// �����łł͐���ɕ�������邪�A�����ł̓G���[�Ƃ���

	//'�f�[�^�o�[�W�������������܂��B�����ł��܂���B'+#13+
	//'�t�@�C����ver.1�̃A�^�b�V�F�P�[�X�ňÍ�������Ă��܂��B'+#13+
	//'�Â��o�[�W�����iver.2.75�ȑO�j�������ł���肵�ĕ��������݂Ă��������B';
	MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_FILE_LOWER_VERSION);
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	goto LabelError;

}
else {

	// 104 �`
	// Rijndael�ňÍ�������Ă���

	// �A���S���Y���^�C�v
	fsIn->Read(&AlgorismType, sizeof(int));
	// �w�b�_�T�C�Y��ǂݍ���
	fsIn->Read(&EncryptHeaderSize, sizeof(int));
	// int�^����|�C���^�L���X�g��char�z������o��
	headerbuffer = (char*) & PlaneHeaderSize;
	// �f�[�^�T�u�o�[�W�����`�F�b�N�iver.2.70�`�j
	if (headerbuffer[0] == 6) {
		TypeLimits = (int)headerbuffer[2];
		fDestroy = (bool)headerbuffer[3];
		// �L���͈́i1�`10�j���`�F�b�N
		if (TypeLimits < 1 || 10 < TypeLimits) {
			TypeLimits = 3; // �f�t�H���g
		}
	}
	else { // headerbuffer[0] == 5            //���o�[�W����
		TypeLimits = 3;
		fDestroy = false;
	}
}

//-----------------------------------
// �����̏���
//-----------------------------------

// �e�[�u������
gentables();

//�p�X���[�h�Z�b�g
if (DataVersion == 105) {  //ver.2.75

	if ( old_key[0] != 0) {  //�Â��`���̃p�X���[�h�t�@�C�����g���Ă���
		gkey(8, 8, old_key);
	}
	else{
		gkey(8, 8, key);
	}

}
else if( DataVersion == 106 ){
	gkey(8, 8, key);
}

//-----------------------------------
// �Í����w�b�_�̕���
//-----------------------------------

pms = new TMemoryStream;

// IV�̓ǂݍ���
fsIn->Read(chain_buffer, BUF_SIZE);

len = 0;

while (len < EncryptHeaderSize) {

	// �ǂݏo���o�b�t�@
	for (i = 0; i < BUF_SIZE; i++) {
		source_buffer[i] = 0;
	}
	// �Í������ꂽ�f�[�^�u���b�N�̓ǂݏo��
	len += fsIn->Read(source_buffer, BUF_SIZE);

	for (i = 0; i < BUF_SIZE; i++) {
		// ���Ƃ�xor�̂��߂ɂ悯�Ă���
		temp_buffer[i] = source_buffer[i];
	}

	// ��������
	rijndael_decrypt(source_buffer);

	// xor
	for (i = 0; i < BUF_SIZE; i++) {
		source_buffer[i] ^= chain_buffer[i];
		chain_buffer[i] = temp_buffer[i]; // CBC
	}

	pms->Write(source_buffer, BUF_SIZE);


}

pms->Seek((__int64)0, TSeekOrigin::soBeginning);  //�|�C���^��擪�֖߂�
DataList = new TStringList;

DataList->LoadFromStream(pms);                                 // default encoding

//DataList->LoadFromStream(pms, TEncoding::UTF8);              // TEncoding::UTF8

//DataList->LoadFromStream(pms, TEncoding::GetEncoding(932));  // shift-jis

delete pms;

//-----------------------------------
// �������ہi�����ł������j
//-----------------------------------
if (DataList->Count == 0 || DataList->Strings[0].Pos("AttacheCase") == 0) {

	//'�p�X���[�h���������܂��B�����ł��܂���B'+#13+
	//'�ꍇ�ɂ���Ă̓t�@�C�������Ă���\��������܂��B';
	MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_PASSWORD_WRONG);
	if ( fCompare == true ) {
		//���b�Z�[�W��'�R���y�A�Ɏ��s���܂����B'��ǉ�
		MsgText += "\n" + LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_FILE);
	}
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	delete DataList;
	goto LabelTypeMiss;

}

//-----------------------------------
// �Í����t�@�C���̐�������
//-----------------------------------
//�����ɍ��͎g�p���Ă��Ȃ����A�����I��
//  �����t���Ńt�@�C���𕜍��ł��Ȃ��Ȃ�
//  �Ȃǂ̋@�\��ǉ����Ă��ǂ������B
//-----------------------------------
AtcFileCreateDateString = DataList->Strings[1];

//-----------------------------------
// �w�b�_�f�[�^����t�@�C�����X�g��
// �t�@�C�����Ȃǂ��e�ϐ��𓮓I�m��
//-----------------------------------

FileSizeList = new __int64[DataList->Count];  // 1: �t�@�C���T�C�Y�i�t�H���_��-1�j
FileAttrList = new int[DataList->Count];      // 2: ����
FileDtChangeList = new int[DataList->Count];  // 3: �X�V��
FileTmChangeList = new int[DataList->Count];  // 4: �X�V��
FileDtCreateList = new int[DataList->Count];  // 5: �쐬��
FileTmCreateList = new int[DataList->Count];  // 6: �쐬��

DataList->NameValueSeparator = ':';

PrefixString = "Fn_";
for (i = 0; i < DataList->Count; i++) {
	if ( DataList->IndexOfName("U_"+IntToStr(i)) > -1){
		PrefixString = "U_";	//�V�o�[�W�����iver.2.8.0�`�j�ňÍ�������Ă���悤��
		break;
	}
}

tsv = new TStringList;
tsv->Delimiter = '\t';
tsv->StrictDelimiter = true;

AllTotalSize = 0;
for (i = 0; i < DataList->Count; i++) {

	idx = DataList->IndexOfName(PrefixString+IntToStr(i));

	if (idx > 0) {
		tsv->DelimitedText = DataList->ValueFromIndex[idx];
		FileList->Add(tsv->Strings[0]);
		FileSizeList[i] = StrToIntDef(tsv->Strings[1], -1);    // 1: �t�@�C���T�C�Y�i�t�H���_��-1�j
		if (FileSizeList[i] > 0) {
			AllTotalSize += FileSizeList[i];
		}
		FileAttrList[i] = StrToIntDef(tsv->Strings[2], -1);    // 2: ����
		FileDtChangeList[i] = StrToIntDef(tsv->Strings[3], -1);// 3: �X�V��
		FileTmChangeList[i] = StrToIntDef(tsv->Strings[4], -1);// 4: �X�V��
		FileDtCreateList[i] = StrToIntDef(tsv->Strings[5], -1);// 5: �쐬��
		FileTmCreateList[i] = StrToIntDef(tsv->Strings[6], -1);// 6: �쐬��
	}

}

delete tsv;
delete DataList;

//-----------------------------------
//�f�B�X�N�̋󂫗e�ʃ`�F�b�N
//-----------------------------------

CurrentDriveFreeSpaceSize = GetDiskFreeSpaceNum(OutDirPath);

if (CurrentDriveFreeSpaceSize > -1 && fCompare == false) {
	if ( AllTotalSize > CurrentDriveFreeSpaceSize ) {
		//'���������̃h���C�u�̋󂫗e�ʂ�����܂���B'+#13+
		//'��������ɂ́A��%dMB�̋󂫗e�ʂ��K�v�ł��B���������𒆎~���܂��B';
		MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_DRIVE_NO_FREE_SPACE);
		free_space_required = (float)AllTotalSize/1024/1024;  // MB
		MsgText = String().sprintf(MsgText.c_str(), free_space_required);
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		goto LabelError;
	}
}
else{
	// OK!
	//
}

//-----------------------------------
//�����t�H���_/�t�@�C�����J�����Ƃ��Ă���̂Ŋm�F
//-----------------------------------

//���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ����
if ( fTempOpenFile == true && FileList->Count > 4 && fCompare == false) {

	//'5�ȏ�̃t�@�C���𕜍���ɊJ�����Ƃ��Ă��܂����A�����𑱂��܂����H'+#13+
	//'�u�������v��I������ƁA�J�����������܂��B';
	MsgText = LoadResourceString(&Msgdecrypt::_MSG_CONFIRM_OPEN_DECRYPTED_FILES);
	MsgType = mtConfirmation;
	MsgButtons = TMsgDlgButtons() << mbYes << mbNo << mbCancel;
	MsgDefaultButton = mbCancel;
	Synchronize(&PostConfirmMessageForm);

	if ( MsgReturnVal == mrCancel ) {
		goto LabelStop;
	}
	else if ( MsgReturnVal == mrNo ) {
		fTempOpenFile = true;
	}

}

//-----------------------------------
// �����J�n
//-----------------------------------

// �t�@�C���T�C�Y���擾����
AllTotalSize = fsIn->Size - fsIn->Position;
// �������x�N�g���̓ǂݏo��
TotalSize = fsIn->Read(chain_buffer, BUF_SIZE);

// zlib �O����
// ���k�ɂ����Ă��ׂẴ������Ǘ������C�u�����ɔC����
z.zalloc = Z_NULL;
z.zfree = Z_NULL;
z.opaque = Z_NULL;

if (inflateInit(&z) != Z_OK) {
	// �G���[
	// zlib�G���[�͍Ō�ł܂Ƃ߂ă��b�Z�[�W����
	goto LabelError;
}

// �ʏ�� deflate() �̑�2������ Z_NO_FLUSH �ɂ��ČĂяo��
flush = Z_NO_FLUSH;

// ���o�̓o�b�t�@
for (i = 0; i < LARGE_BUF_SIZE; i++) {
	output_buffer[i] = 0;
}

z.avail_in  = 0;               // ���̓o�b�t�@���̃f�[�^�̃o�C�g��
z.next_in   = Z_NULL;          // ���̓o�b�t�@���̃f�[�^�̃o�C�g��
z.next_out  = output_buffer;   // �o�̓o�b�t�@�c��
z.avail_out = LARGE_BUF_SIZE;  // �o�̓|�C���^�i�W�J����̂ő傫�߂Ɂj
status      = Z_OK;

while (Terminated == false) {

	//-----------------------------------
	// ����
	//-----------------------------------
	if (z.avail_in == 0) {

		// ���̓o�b�t�@
		for (i = 0; i < BUF_SIZE; i++) {
			source_buffer[i] = 0;
		}

		TotalSize =
			InputBuffer(
				len, source_buffer, chain_buffer,
				fsIn, fInputFileOpen,
				TotalSize, AllTotalSize
			);

		z.avail_in = len;
		z.next_in = source_buffer;

		if ( len < BUF_SIZE ) {
			status = Z_FINISH;
		}

	}

	//-----------------------------------
	// �W�J
	//-----------------------------------
	status = inflate(&z, flush);

	if (status == Z_STREAM_END) {
		break;
	}

	//-----------------------------------
	// �����X�e�[�^�X
	//-----------------------------------
	if ( status == Z_OK ){
	}
	else if ( status == Z_BUF_ERROR ) { //���͂��s�����\��
		//�o�̓o�b�t�@���N���A�ɂ��Čp��������
		len = LARGE_BUF_SIZE - z.avail_out;
		ret = OutputBuffer(output_buffer, len,
											 fsOut, fOutputFileOpen,
											 FileList, FileIndex,
											 FileSizeList, FileAttrList,
											 FileDtChangeList, FileTmChangeList,
											 FileDtCreateList, FileTmCreateList);
		if (ret == 0) {
			z.next_out = output_buffer;
			z.avail_out = LARGE_BUF_SIZE;
		}
		else if ( ret == 1) {
			break;
		}
		else{
			if ( ret == -2) {
				goto LabelStop;
			}
			else {
				goto LabelError;
			}
		}

	}
	else{
		// #define Z_OK              0
		// #define Z_STREAM_END      1
		// #define Z_NEED_DICT       2
		// #define Z_ERRNO         (-1)
		// #define Z_STREAM_ERROR  (-2)
		// #define Z_DATA_ERROR    (-3)
		// #define Z_MEM_ERROR     (-4)
		// #define Z_BUF_ERROR     (-5)
		// #define Z_VERSION_ERROR (-6)
		goto LabelError;
	}

	// -----------------------------------
	// �o��
	// -----------------------------------
	if ( z.avail_out == 0 ) {

		ret = OutputBuffer(output_buffer, LARGE_BUF_SIZE,
											 fsOut, fOutputFileOpen,
											 FileList, FileIndex,
											 FileSizeList, FileAttrList,
											 FileDtChangeList, FileTmChangeList,
											 FileDtCreateList, FileTmCreateList);

		if ( ret < 0) {      //�G���[
			if (ret == -2) {
				goto LabelStop;
			}
			else{
				goto LabelError;
			}
		}
		else{

			for (i = 0; i < LARGE_BUF_SIZE; i++) {
				output_buffer[i] = 0;
			}
			z.next_out = output_buffer;
			z.avail_out = LARGE_BUF_SIZE;
		}


	}//end if (z.avail_out == 0);

	//-----------------------------------
	//�i���󋵕\��
	ProgressPercentNum = ((float)TotalSize/AllTotalSize)*100;
	//'�������Ă��܂�...'
	ProgressStatusText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_TITLE_DECRYPTING);
	ProgressMsgText = ExtractFileName(AtcFilePath);


}//while (!Terminated);

if (Terminated == true) {
	//���[�U�[�L�����Z���Ŕ����Ă���
	goto LabelStop;
}

//----------------------------------------------------------------------
// ������A�o�̓o�b�t�@�ɗ]�肪����ꍇ
//----------------------------------------------------------------------
if (z.avail_out > 0) {

		len = LARGE_BUF_SIZE - z.avail_out;
		ret = OutputBuffer(output_buffer, len,
										 fsOut, fOutputFileOpen,
										 FileList, FileIndex,
										 FileSizeList, FileAttrList,
										 FileDtChangeList, FileTmChangeList,
										 FileDtCreateList, FileTmCreateList);
	if ( ret < 0 ) {
		if ( ret == -2 ){
			goto LabelStop;
		}
		else{
			goto LabelError;
		}
	}

}

if (inflateEnd(&z) != Z_OK) {
	goto LabelError;
}

ProgressPercentNum = 100;
//'����'
ProgressStatusText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_TITLE_COMPLETE);
ProgressMsgText = ExtractFileName(AtcFilePath);

if ( fInputFileOpen == true ) {
	delete fsIn;
	fInputFileOpen = false;
}
if ( fOutputFileOpen == true ) {
	delete fsOut;
	fOutputFileOpen = false;
}

delete FileList;
delete [] FileSizeList;      // 1: �t�@�C���T�C�Y�i�t�H���_��-1�j
delete [] FileAttrList;      // 2: ����
delete [] FileDtChangeList;  // 3: �X�V��
delete [] FileTmChangeList;  // 4: �X�V��
delete [] FileDtCreateList;  // 5: �쐬��
delete [] FileTmCreateList;  // 6: �쐬��

//��������
StatusNum = 1;
return;


//-----------------------------------
//�p�X���[�h���̓~�X�̌�n��
//-----------------------------------
LabelTypeMiss:

	ProgressPercentNum = 0;

	//'�G���['
	ProgressStatusText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_TITLE_ERROR);
	//'�����Ɏ��s���܂����B'
	ProgressMsgText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_DETAIL_FAILED);

	if ( fInputFileOpen == true ) {
		delete fsIn;
		fInputFileOpen = false;
	}
	if ( fOutputFileOpen == true ) {
		delete fsOut;
		fOutputFileOpen = false;
	}

	delete FileList;
	delete [] FileSizeList;
	delete [] FileAttrList;
	delete [] FileDtChangeList;
	delete [] FileTmChangeList;
	delete [] FileDtCreateList;
	delete [] FileTmCreateList;

	StatusNum = -1;
	return;


//-----------------------------------
//�G���[�̌�n��
//-----------------------------------
LabelError:

	ProgressPercentNum = 0;

	if ( status < 0 ){
		//'zlib���C�u��������G���[��Ԃ���܂����B'
		//'�G���[�ԍ��F'
		MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_ZLIB) + IntToStr(status) + "\n" + z.msg;
		if ( fCompare == true ) {
			//���b�Z�[�W��'�R���y�A�Ɏ��s���܂����B'��ǉ�
			MsgText += "\n" + LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_FILE);
		}
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
	}

	//'�G���['
	ProgressStatusText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_TITLE_ERROR);
	//'�����Ɏ��s���܂����B'
	ProgressMsgText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_DETAIL_FAILED);

	if ( fInputFileOpen == true ) {
		delete fsIn;
		fInputFileOpen = false;
	}
	if ( fOutputFileOpen == true ) {
		delete fsOut;
		fOutputFileOpen = false;
	}

	delete FileList;
	delete [] FileSizeList;
	delete [] FileAttrList;
	delete [] FileDtChangeList;
	delete [] FileTmChangeList;
	delete [] FileDtCreateList;
	delete [] FileTmCreateList;

	StatusNum = -2;
	return;


//-----------------------------------
//���[�U�[�L�����Z���̌�n��
//-----------------------------------
LabelStop:

	ProgressPercentNum = 0;
	//'�L�����Z��'
	ProgressStatusText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_TITLE_USER_CANCEL);
	//'���������~����܂����B'
	ProgressMsgText = LoadResourceString(&Msgdecrypt::_LABEL_STATUS_DETAIL_STOPPED);

	if ( fInputFileOpen == true ) {
		delete fsIn;
		fInputFileOpen = false;
	}
	if ( fOutputFileOpen == true ) {
		delete fsOut;
		fOutputFileOpen = false;
	}

	delete FileList;
	delete [] FileSizeList;
	delete [] FileAttrList;
	delete [] FileDtChangeList;
	delete [] FileTmChangeList;
	delete [] FileDtCreateList;
	delete [] FileTmCreateList;

	StatusNum = 0;
	return;

}
//===========================================================================
// �o�b�t�@�̓���
//===========================================================================
__int64 __fastcall TAttacheCaseFileDecrypt2::InputBuffer
	(int &buff_size, char *source_buffer, char *chain_buffer,
	 TFileStream *fsIn, bool &fOpen,
	 __int64 TotalSize, __int64 AllTotalSize )
{

int i;

bool fPKCS;
int paddingNum;
char temp_buffer[BUF_SIZE];

// �ǂݏo���o�b�t�@�̏�����
for (i = 0; i < BUF_SIZE; i++) {
	source_buffer[i] = 0;
}

// ���̓t�@�C�����J����Ă��Ȃ�
if ( fOpen == false ) {
	buff_size = 0;
	return(TotalSize);
}

// �Ō�̃u���b�N���z���Ă���
if (TotalSize >= AllTotalSize) {
	buff_size = 0;
	return(TotalSize);
}

// �Í������ꂽ�f�[�^�u���b�N�̓ǂݏo��
TotalSize += fsIn->Read(source_buffer, BUF_SIZE);

for (i = 0; i < BUF_SIZE; i++) {
	// ���Ƃ�xor�̂��߂ɂ悯�Ă���
	temp_buffer[i] = source_buffer[i];
}

// ��������
rijndael_decrypt(source_buffer);

// xor
for (i = 0; i < BUF_SIZE; i++) {
	source_buffer[i] ^= chain_buffer[i];
	chain_buffer[i] = temp_buffer[i]; // CBC
}

// �Ō�̃u���b�N�̋��E...
if (TotalSize >= AllTotalSize) {

	// Check PKCS #7 pading num
	fPKCS = false;
	paddingNum = source_buffer[BUF_SIZE - 1];
	for (i = 0; i < paddingNum; i++) {
		if (source_buffer[BUF_SIZE - 1 - i] == paddingNum) {
			fPKCS = true;
		}
		else {
			fPKCS = false;
			break;
		}
	}
	if (fPKCS == true) {
		buff_size = BUF_SIZE - paddingNum;
	}
	else {
		buff_size = BUF_SIZE;
	}

}
else {
	buff_size = BUF_SIZE;
}

return(TotalSize);

}
//===========================================================================
// �o�b�t�@�̏o��
//===========================================================================
int __fastcall TAttacheCaseFileDecrypt2::OutputBuffer
	(char *output_buffer, int buff_size,
	TFileStream *&fsOut, bool &fOpen,
	TStringList *FileList, int &FileIndex,
	__int64 *FileSizeList, int *FileAttrList,
	int *FileDtChangeList, int *FileTmChangeList,
	int *FileDtCreateList, int *FileTmCreateList)
{

//�Ԓl�@0=<:����, -1:�G���[, -2:���[�U�[�L�����Z��

int i;
int res;

int rest;
String FileName, FilePath;
char read_buffer[LARGE_BUF_SIZE];      //�R���y�A�p

// �𓀂��ꂽ�o�b�t�@�����ׂď������܂��܂Ń��[�v
while (buff_size > 0 && !Terminated) {

	// �t�@�C�����J����Ă��Ȃ��Ȃ�I�[�v������
	if ( fOpen == false ) {

		for (i = FileIndex; i < FileList->Count; i++) {

			FileName = FileList->Strings[i];
			FilePath = OutDirPath + FileName;

			//-----------------------------------
			// �f�B���N�g��
			//-----------------------------------
			if (FileName.IsPathDelimiter(FileList->Strings[i].Length()) == true) {

				//�R���y�A
				if (fCompare == true) {
					if (FileName == ExtractRelativePath(OutDirPath, CompareFileList->Strings[i])) {
						continue;
					}
					else{
						//'�R���y�A�Ɏ��s���܂����B'
						MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_FILE_MISMATCH)+"\n";
						//'���̃t�@�C���܂��̓t�H���_�̓��e���قȂ�悤�ł��B'
						MsgText += LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_FILE_MISMATCH)+"\n";
						// '�Í���:'+CompareFileList->Strings[i];
						MsgText += LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_ENCRYPT_FILE)+"\n"+CompareFileList->Strings[i];
						// '����  :'+FilePath;
						MsgText += LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_DECRYPT_FILE)+"\n"+FilePath;
						MsgType = mtError;
						MsgButtons = TMsgDlgButtons() << mbOK;
						MsgDefaultButton = mbOK;
						Synchronize(&PostConfirmMessageForm);
						goto LabelError;
					}
				}


				if ( fConfirmOverwirte == true && fOverwirteYesToAll == false ) {

					if (DirectoryExists(FilePath) == true) {

						//�����t�H���_�[�̏㏑���m�F���b�Z�[�W�_�C�A���O
						MsgText = LoadResourceString(&Msgdecrypt::_MSG_CONFIRM_OVER_WRITE_SAME_DIR)+"\n"+FilePath;
						Synchronize(&PostConfirmOverwriteMessageForm);

						if ( MsgReturnVal == mrYes ) {
							//�㏑��OK�Ȃ̂�FilePath�͂��̂܂�
						}
						else if ( MsgReturnVal == mrNo ) {
							//�ʖ��ۑ���FilePath�����񂪏����������Ă��Ă���
							FilePath = MsgReturnPath;
						}
						else if ( MsgReturnVal == mrYesToAll ) {
							//���ׂď㏑���iYesToAll�j
							fOverwirteYesToAll = true;
						}
						else if ( MsgReturnVal == mrCancel ) {
							//�L�����Z��
							goto LabelStop;
						}
					}

				}

				//-----------------------------------
				//�Í����t�@�C�����g�ւ̕�����NG
				//�iex: ..\hoge -> ..\hoge�j
				//-----------------------------------
				if ( FilePath == AtcFilePath ) {
					//'�Í����t�@�C�����g�Ƀt�@�C���܂��̓t�H���_�[�𕜍����邱�Ƃ͂ł��܂���B'+#13+
					//'���������𒆎~���܂��B';
					MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_NOT_OVERWRITE_MYSELF)+"\n"+FilePath;
					MsgType = mtError;
					MsgButtons = TMsgDlgButtons() << mbOK;
					MsgDefaultButton = mbOK;
					Synchronize(&PostConfirmMessageForm);
					//�G���[
					goto LabelError;
				}

				//�t�H���_�̐���
				ForceDirectories(FilePath);
				//�^�C���X�^���v�̃Z�b�g
				FileSetTimeStamp(
					FilePath,
					FileDtChangeList[i], FileTmChangeList[i],
					FileDtCreateList[i], FileTmCreateList[i],
					false, true);
				//�����̃Z�b�g
				FileSetAttr(FilePath, FileAttrList[i]);

				if ( fOpenFolder == true && fOpenFolderOnce == false ) {
					ShellExecuteW(NULL, L"open", L"EXPLORER.EXE", FilePath.c_str(), FilePath.c_str(), SW_NORMAL);  //�Ǝ㐫�΍�iver.2.70�j
					//ShellExecuteW(NULL, L"explore", FilePath.c_str(), NULL, NULL, SW_NORMAL);	//������ł����퓮�삵���悤��
					fOpenFolderOnce = true;
				}

				continue;

			}
			//-----------------------------------
			// �t�@�C��
			//-----------------------------------
			else {

				if ( fCompare == false && fConfirmOverwirte == true && fOverwirteYesToAll == false ) {

					if (FileExists(FilePath) == true) {
						//�����t�@�C���̏㏑���m�F���b�Z�[�W�_�C�A���O
						MsgText = LoadResourceString(&Msgdecrypt::_MSG_CONFIRM_OVER_WRITE_SAME_FILE)+"\n"+FilePath;
						Synchronize(&PostConfirmOverwriteMessageForm);
						if ( MsgReturnVal == mrYes ) {
							//�㏑��OK�Ȃ̂�FilePath�͂��̂܂�
						}
						else if ( MsgReturnVal == mrNo ) {
							//�ʖ��ۑ���FilePath�����񂪏����������Ă��Ă���
							FilePath = MsgReturnPath;
						}
						else if ( MsgReturnVal == mrYesToAll ) {
							//���ׂď㏑���iYesToAll�j
							fOverwirteYesToAll = true;
						}
						else if ( MsgReturnVal == mrCancel ) {
							//�L�����Z��
							goto LabelStop;
						}
					}

				}

				//-----------------------------------
				//�Í����t�@�C�����g�ւ̕�����NG
				//�iex: ..\hoge -> ..\hoge�j
				//-----------------------------------
				if ( fCompare == false && FilePath == AtcFilePath ) {
					//'�Í����t�@�C�����g�Ƀt�@�C���܂��̓t�H���_�[�𕜍����邱�Ƃ͂ł��܂���B'+#13+
					//'���������𒆎~���܂��B';
					MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_NOT_OVERWRITE_MYSELF)+"\n"+FilePath;
					MsgType = mtError;
					MsgButtons = TMsgDlgButtons() << mbOK;
					MsgDefaultButton = mbOK;
					Synchronize(&PostConfirmMessageForm);
					//�G���[
					goto LabelError;
				}

				try {

					if (fCompare == true) {
						//�R���y�A�͌��t�@�C�����J��
						fsOut = new TFileStream(CompareFileList->Strings[i], fmOpenRead);
					}
					else{
						//�o�͂���t�@�C�����J��
						fsOut = new TFileStream(FilePath, fmCreate);
					}

				}
				catch(...) {

					//�ۑ������̃t�@�C�����J���܂���B���̃A�v���P�[�V�������g�p���̉\��������܂��B
					MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_OUT_FILE_OPEN)+"\n"+FilePath;
					if ( fCompare == true ) {
						//���b�Z�[�W��'�R���y�A�Ɏ��s���܂����B'��ǉ�
						MsgText += "\n" + LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_FILE);
					}
					MsgType = mtError;
					MsgButtons = TMsgDlgButtons() << mbOK;
					MsgDefaultButton = mbOK;
					Synchronize(&PostConfirmMessageForm);
					goto LabelError;

				}

				fOpen = true;

				if (FileSizeList[i] == 0) { // 0�o�C�g�t�@�C��

					delete fsOut;

					if (fCompare == true) {
						//�R���y�A�̏ꍇ�͔�����
						continue;
					}

					fOpen = false;

					FileSetTimeStamp(FilePath,
						(int)FileDtChangeList[i], (int)FileTmChangeList[i],
						(int)FileDtCreateList[i], (int)FileTmCreateList[i],	false, true);

					FileSetAttr(FilePath, (int)FileAttrList[i]);

					//�֘A�t����ꂽ�A�v���P�[�V�����Ńt�@�C�����J��
					if ( fTempOpenFile == true ) {
						ShellExecuteW(NULL, L"open", FilePath.c_str(), NULL, NULL, SW_NORMAL);
					}
				}
				else{
					break;
				}

			}

		} // end for;

		FileIndex = i;

	} // end if (fOpen == false);

	//-----------------------------------
	// �J�����t�@�C���ɏ�������
	//-----------------------------------
	if ( fOpen == true ) {

		//-----------------------------------
		// �R���y�A
		//-----------------------------------
		if ( fCompare == true ) {

			if (fsOut->Position + LARGE_BUF_SIZE < FileSizeList[FileIndex]) {

				if (fsOut->Read(read_buffer, LARGE_BUF_SIZE) != LARGE_BUF_SIZE) {
					//�ǂݍ��݃G���[
					goto LabelReadWriteError;
				}
				else{
					//�f�[�^�̃R���y�A
					if ( CompareMem(read_buffer, output_buffer, LARGE_BUF_SIZE) == false ){
						//'�f�[�^�̈�v���Ȃ��t�@�C����������܂����B'
						MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_DATA_NOT_MATCH)+"\n"+fsOut->FileName;
						//'�R���y�A�Ɏ��s���܂����B';
						MsgText += LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_FILE);
						MsgType = mtError;
						MsgButtons = TMsgDlgButtons() << mbOK;
						MsgDefaultButton = mbOK;
						Synchronize(&PostConfirmMessageForm);
						goto LabelError;
					}
				}

			}
			else{
				rest = FileSizeList[FileIndex] - fsOut->Position;
				if (fsOut->Read(read_buffer, rest) != rest) {
					//�ǂݍ��݃G���[
					goto LabelReadWriteError;
				}
				else {
					buff_size -= rest;
					delete fsOut;
					fOpen = false;

					FileSetTimeStamp(
						FilePath,
						FileDtChangeList[FileIndex], FileTmChangeList[FileIndex],
						FileDtCreateList[FileIndex], FileTmCreateList[FileIndex],
						false, true);
					FileSetAttr(FilePath, FileAttrList[FileIndex]);

					//�֘A�t����ꂽ�A�v���P�[�V�����Ńt�@�C�����J��
					if ( fTempOpenFile == true ) {
						ShellExecuteW(NULL, L"open", FilePath.c_str(), NULL, NULL, SW_NORMAL);
					}

					FileIndex++;

				}//end if (fsOut->Write(output_buffer, rest) != rest);

			}

		}
		//-----------------------------------
		// �ʏ�̕�������
		//-----------------------------------
		else{

			if (fsOut->Position + LARGE_BUF_SIZE < FileSizeList[FileIndex]) {
				if (fsOut->Write(output_buffer, LARGE_BUF_SIZE) != LARGE_BUF_SIZE) {
					goto LabelReadWriteError;
				}
				else {
					buff_size -= LARGE_BUF_SIZE;
				}
			}
			else {
				rest = FileSizeList[FileIndex] - fsOut->Position;
				if (fsOut->Write(output_buffer, rest) != rest) {
					goto LabelReadWriteError;
				}
				else {
					buff_size -= rest;
					delete fsOut;
					fOpen = false;

					FileSetTimeStamp(
						FilePath,
						FileDtChangeList[FileIndex], FileTmChangeList[FileIndex],
						FileDtCreateList[FileIndex], FileTmCreateList[FileIndex],
						false, true);
					FileSetAttr(FilePath, FileAttrList[FileIndex]);

					//�֘A�t����ꂽ�A�v���P�[�V�����Ńt�@�C�����J��
					if ( fTempOpenFile == true ) {
						ShellExecuteW(NULL, L"open", FilePath.c_str(), NULL, NULL, SW_NORMAL);
					}

					FileIndex++;

				}

			}

		}//end if ( fCompare == true );

	}
	else {
		//�����J���t�@�C�����Ȃ�
		break;

	}//end if ( fOpen == true );
	//-----------------------------------

}//end while ( buf_size < 0 );

if ( Terminated == true ) {
	goto LabelStop;
}

//����
return(0);

//-----------------------------------
//�ǂݏ����G���[
LabelReadWriteError:

	if ( fCompare == true ) {
		//'�R���y�A���s�����̃t�@�C����ǂݍ��ނ��Ƃ��ł��܂���B'
		MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_NOT_READ_SOURCE)+"\n"+fsOut->FileName;
		//'�R���y�A�Ɏ��s���܂����B';
		MsgText += LoadResourceString(&Msgdecrypt::_MSG_ERROR_COMPARE_FILE);
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
	}
	else{
		//'�ۑ������̃t�@�C���ɏ������߂܂���B�����ł��܂���B'
		MsgText = LoadResourceString(&Msgdecrypt::_MSG_ERROR_OUT_FILE_WRITE)+"\n"+fsOut->FileName;
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
	}

	if ( fOpen == true ) {
		delete fsOut;
		fOpen = false;
	}

	return(-1);


//-----------------------------------
//�G���[
LabelError:

	//�����̃G���[�͒��O�Ń��b�Z�[�W��񎦂��Ă��痈�Ă���

	if ( fOpen == true ) {
		delete fsOut;
		fOpen = false;
	}

	return(-1);

//-----------------------------------
//���[�U�[�L�����Z��
LabelStop:

	if ( fOpen == true ) {
		delete fsOut;
		fOpen = false;
	}

	return(-2);


}
//===========================================================================
// �t�@�C��/�f�B���N�g���̃^�C���X�^���v��ݒ肷��
//===========================================================================
void __fastcall TAttacheCaseFileDecrypt2::FileSetTimeStamp(String FilePath, // �p�X
	int tsChangeDateNum, // �X�V�� �i��Win98�̏ꍇ�͂�����FileAge������j
	int tsChangeTimeNum, // �X�V��
	int tsCreateDateNum, // �쐬��
	int tsCreateTimeNum, // �쐬��
	bool fNow,           // true�Ȃ瑼�̈����Ɋ֌W�Ȃ��X�V���������݂ɐݒ�
	bool fDir            // �f�B���N�g��
		)
{

	HANDLE hFile;

	FILETIME ChangeFileTime, CreateFileTime;
	SYSTEMTIME sysChangeFileTime, sysCreateFileTime;

	TDateTime dtChangeDate, dtCreateDate;
	TTimeStamp tsChangeDate, tsCreateDate;

	// -----------------------------------
	// 2000, XP�n

	// Win95/98��Win2000/XP�֕�������Ƃ��ɕs���ȃ^�C���X�^���v��
	// �n�邱�Ƃ�����̂ŁA�ȉ��ɗ�O�������{��
	try {

		// TTimeStamp�֑��
		tsChangeDate.Date = tsChangeDateNum; // �X�V����
		tsChangeDate.Time = tsChangeTimeNum;
		tsCreateDate.Date = tsCreateDateNum; // �쐬����
		tsCreateDate.Time = tsCreateTimeNum;

		// ���ݓ�����������Ȃ�
		if (fNow == true) {
			dtChangeDate = Now();
			dtCreateDate = Now();
		}
		else {
			// TimeStamp����TDateTime��
			dtChangeDate = TimeStampToDateTime(tsChangeDate);
			dtCreateDate = TimeStampToDateTime(tsCreateDate);
		}

	}
	catch(Exception & e) {

		return; // �^�C���X�^���v�͌��ݓ����ɐݒ肷��

	}

	// �X�V����
	DateTimeToSystemTime(dtChangeDate, sysChangeFileTime);
	// TDateTime �� SystemTime
	SystemTimeToFileTime(&sysChangeFileTime, &ChangeFileTime);
	// SystemTime �� FILETIME
	// �쐬����
	DateTimeToSystemTime(dtCreateDate, sysCreateFileTime);
	// TDateTime �� SystemTime
	SystemTimeToFileTime(&sysCreateFileTime, &CreateFileTime);
	// SystemTime �� FILETIME

	// ���[�J���̃t�@�C���������A���E���莞���iUTC�j�Ɋ�Â��t�@�C�������֕ϊ�����
	if (fNow == true) {
		LocalFileTimeToFileTime(&ChangeFileTime, &ChangeFileTime);
		LocalFileTimeToFileTime(&CreateFileTime, &CreateFileTime);
	}

	// -----------------------------------
	// �f�B���N�g��
	if (fDir == true) {
		// �f�B���N�g���n���h���𓾂�i��NT/2000�n�̂݁FFILE_FLAG_BACKUP_SEMANTICS�j
		hFile = CreateFileW(FilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	}
	// -----------------------------------
	// �t�@�C�����J���i���uGENERIC_WRITE�v�ɂ��Ă����Ȃ��ƕύX�ł��Ȃ��悤�j
	else {
		hFile = CreateFileW(FilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	// -----------------------------------
	// �t�@�C�����I�[�v������Ă���
	if (hFile != INVALID_HANDLE_VALUE) {

		// �쐬����0�ɂȂ��Ă���Ȃ�
		if (tsCreateDateNum == 0) {
			SetFileTime(hFile, NULL, NULL, &ChangeFileTime); // �^�C���X�^���v�̃Z�b�g
		}
		else {
			SetFileTime(hFile, &CreateFileTime, NULL, &ChangeFileTime); // �^�C���X�^���v�̃Z�b�g
		}

	}

	CloseHandle(hFile);

}
// end SetFileAgeStr;
//===========================================================================
//�f�B�X�N�̋󂫗e�ʂ𒲂ׂ�
//===========================================================================
__int64 __fastcall TAttacheCaseFileDecrypt2::GetDiskFreeSpaceNum(String FilePath)
{

int i;
int flag;

__int64 FreeSpace;

String DriveName = ExtractFileDrive(FilePath)+":";
String DirPath = IncludeTrailingPathDelimiter(ExtractFileDir(FilePath));

OSVERSIONINFO ovi;   // �o�[�W���������i�[����\����
ovi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

// �o�[�W�������擾
GetVersionEx( (LPOSVERSIONINFO)&ovi );

// Windows95 OSR2�ȑO
if( ( ovi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
		&& ( int( ovi.dwBuildNumber & 0xffff ) <= 1000 ) ){

	DWORD SCluster,BSector,FCluster,TCluster;

	if ( GetDiskFreeSpaceW(String(DriveName).c_str(), &SCluster, &BSector, &FCluster, &TCluster) > 0){
		FreeSpace = SCluster*BSector*FCluster;
	}
	else{
		//�l�b�g���[�N�T�[�o��͎擾�ł����G���[�ƂȂ�
		FreeSpace = -1;
	}

}
// OSR2�ȍ~�`
else{

	ULARGE_INTEGER pqwFreeCaller;
	ULARGE_INTEGER pqwTot;
	ULARGE_INTEGER pqwFree;

	if(::GetDiskFreeSpaceExW(String(DirPath).c_str(), &pqwFreeCaller, &pqwTot, &pqwFree)){
		//64bit Integer�ŕԂ�
		FreeSpace = pqwFreeCaller.QuadPart;
	}
	else{
		FreeSpace = -1;
	}

}

return(FreeSpace);

}//end GetDiskFreeSpaceNum;
//===========================================================================
// �����f�[�^�̐���
//===========================================================================
void TAttacheCaseFileDecrypt2::fillrand(char *buf, const int len)
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
//�p�X���[�h��������Z�b�g����
//===========================================================================
void __fastcall TAttacheCaseFileDecrypt2::SetPasswordString(AnsiString Password)
{

for ( int i = 0; i < 32; i++){
	key[i]=0;
}
StrCopy(key, Password.c_str());


}
//===========================================================================
//�p�X���[�h�Ƀo�C�i���l���Z�b�g����iver.2.80�`�j
//===========================================================================
void __fastcall TAttacheCaseFileDecrypt2::SetPasswordBinary(unsigned char *password)
{

for ( int i = 0; i < 32; i++){
	key[i]=0;
}
memcpy(key, password, 32);

}
//===========================================================================
//�p�X���[�h�����񂩂�o�C�i���l���Z�b�g����i���ʌ݊��j
//===========================================================================
void __fastcall TAttacheCaseFileDecrypt2::SetPasswordStringToBinary(AnsiString Password)
{

//�܂�͐擪��32�o�C�g����password�ɑ������Ȃ�
for ( int i = 0; i < 32; i++){
	old_key[i]=0;
}
strcpy( old_key, Password.c_str() );

}
//===========================================================================
//���C���t�H�[���Ɋm�F���b�Z�[�W�𓊂��ď����𒆒f����
//===========================================================================
void __fastcall TAttacheCaseFileDecrypt2::PostConfirmMessageForm()
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
//���C���t�H�[���ɏ㏑���̊m�F���b�Z�[�W�𓊂��ď����𒆒f����
//===========================================================================
void __fastcall TAttacheCaseFileDecrypt2::PostConfirmOverwriteMessageForm()
{

//�O���[�o���ϐ�(private)�Ƃ��Ē�`���Ă���

//String MsgText;
//String MsgReturnPath;

MsgReturnVal = Form1->ShowConfirmOverwriteMassageForm(MsgText, MsgReturnPath);

}
//===========================================================================

