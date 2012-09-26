/*

'AttacheCase' - file encryption software for Windows.

TAttacheCaseFileEncrypt Class file.

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
#include "TAttacheCaseFileEncrypt.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

// ���ӁF�قȂ�X���b�h�����L���� VCL �̃��\�b�h/�֐�/�v���p�e�B��ʂ�
// ���b�h���L�̃I�u�W�F�N�g�ɑ΂��Ă� Synchronize ���g�p�ł��܂��B
//
//      Synchronize(&UpdateCaption);
//
// �Ⴆ�� UpdateCaption ���ȉ��̂悤�ɒ�`��
//
//      void __fastcall TAttacheCaseFileEncode::UpdateCaption()
//      {
//        Form1->Caption = "�X���b�h���珑�������܂���";
//      }
//---------------------------------------------------------------------------
__fastcall TAttacheCaseFileEncrypt::TAttacheCaseFileEncrypt
	(bool CreateSuspended) : TThread(CreateSuspended)
{

	int i;

	//�I�v�V�����i�f�t�H���g�l�j
	CompressRateNum = Z_DEFAULT_COMPRESSION; //���k��
	fOver4gbOk = true;                       //4GB��������
	fAllFilesPackOption = false;             //���ׂẴt�@�C�����P�ɂ܂Ƃ߂�
	fExeOutputOption = false;                //���s�`���o��
	fOptBrokenFileOption = false;            //�~�X�^�C�v�Ńt�@�C����j�󂷂邩�ۂ�
	intOptMissTypeLimitsNumOption = 3;       //�^�C�v�~�X�ł����
	fConfirmOverwirte = true;                //�����t�@�C��������Ƃ��͏㏑���̊m�F������
	fOverwirteYesToAll = false;              //�����t�@�C���͂��ׂď㏑�����ĈÍ�������i�_�C�A���O�Łu���ׂĂ͂��v��I�� = true�j

	ProgressPercentNum = -1;                 //�i���p�[�Z���g
	ProgressStatusText = "";                 //�i���X�e�[�^�X
	ProgressMsgText = "";                    //�i�����b�Z�[�W

	AppExeFilePath = "";                     //�A�^�b�V�F�P�[�X�{�̂̏ꏊ

	OutFilePath = "";                        //�o�͂���Í����t�@�C��
	InputFileList = new TStringList;         //�Í������錳�t�@�C�����X�g

	for (i = 0; i < 32; i++) {
		key[i] = 0;
	}

	StatusNum = 0;                           //�X�e�[�^�X�\�����e�ԍ�
	MsgErrorString = "";                     //�G���[���b�Z�[�W


}
//===========================================================================
//�f�X�g���N�^
//===========================================================================
__fastcall TAttacheCaseFileEncrypt::~TAttacheCaseFileEncrypt(void)
{

delete InputFileList;

}
//===========================================================================
// �X���b�h���s
//===========================================================================
void __fastcall TAttacheCaseFileEncrypt::Execute()
{

int i, c;
int res;

z_stream z;          // zlib���C�u�����Ƃ��Ƃ肷�邽�߂̍\����
int flush, status;   // zlib

//�o�͂���Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹��
HANDLE hFile;
//_WIN32_FIND_DATAW first_fd;
ZeroMemory(&first_fd, sizeof(_WIN32_FIND_DATAW));

int len, pos;
int FileIndex;
String FilePath;

int HeaderSize;                          //�w�b�_�f�[�^�T�C�Y
__int64 CurrentDriveFreeSpaceSize = -1;  //�ۑ�����h���C�u�̋󂫗e��


//���s�\�`���o�̓t�@�C���̃f�[�^�T�C�Y
__int64 ExeAllSize = 0;
__int64 ExeSize    = 0;

//�S�̂̃t�@�C���T�C�Y
__int64 AllTotalSize = 0;
__int64 TotalSize    = 0;

//�o�b�t�@
char source_buffer[BUF_SIZE];
char read_buffer[BUF_SIZE];
char out_buffer[BUF_SIZE];
char chain_buffer[BUF_SIZE]; // IV�Ȃǂ��i�[����`�F�C���o�b�t�@
char margin_buffer[BUF_SIZE];

//�t�@�C���X�g���[��
TFileStream *fsIn;
TFileStream *fsOut;
TFileStream *fsExe;

//�I�[�v������
bool fOpenIn;
bool fOpenOut;
//�������X�g���[��
TMemoryStream *pms = new TMemoryStream;
TStringList *FilePathList = new TStringList;

// �}�[�W���o�b�t�@�T�C�Y
int MarginBufSize = MARGIN_BUF_SIZE;

// PKCS #7 Pading num.
int paddingNum = 0;

//---------------------------------------
// �����t�@�C��������̂Ń_�C�A���O�\��
//---------------------------------------
if ( fConfirmOverwirte == true && fOverwirteYesToAll == false ) {

	if (FileExists(OutFilePath) == true) {
		//�����t�@�C���̏㏑���m�F���b�Z�[�W�_�C�A���O
		MsgText = LoadResourceString(&Msgencrypt::_MSG_CONFIRM_OVER_WRITE_SAME_FILE)+"\n"+OutFilePath;
		Synchronize(&PostConfirmOverwriteMessageForm);
		if ( MsgReturnVal == mrYes ) {
			//�㏑��OK�Ȃ̂�FilePath�͂��̂܂�
		}
		else if ( MsgReturnVal == mrNo ) {
			//�ʖ��ۑ���FilePath�����񂪏����������Ă��Ă���
			OutFilePath = MsgReturnPath;
		}
		else if ( MsgReturnVal == mrYesToAll ) {
			//���ׂď㏑���iYesToAll�j
			fOverwirteYesToAll = true;
		}
		else if ( MsgReturnVal == mrCancel ) {
			//�L�����Z��
			delete pms;
			goto LabelStop;
		}
	}

}

//---------------------------------------
// �w�b�_���̐������t�@�C�����T�C�Y�擾
//---------------------------------------
if ( CreateHeaderData( pms, InputFileList, FilePathList, AllTotalSize) == false ){
	if (Terminated == true) {
		//���[�U�[�L�����Z���Ŕ����Ă���
		delete pms;
		goto LabelStop;
	}
	else{
		//'�Í�������t�@�C�����J���܂���B���̃A�v���P�[�V�������g�p���̉\��������܂��B'
		MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_FILE_OPEN);
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		delete pms;
		goto LabelError;
	}

}

//-----------------------------------
// �f�B�X�N�̋󂫗e�ʃ`�F�b�N
//-----------------------------------

CurrentDriveFreeSpaceSize = GetDiskFreeSpaceNum(OutFilePath);

if (CurrentDriveFreeSpaceSize > -1 ) {
	if ( AllTotalSize > CurrentDriveFreeSpaceSize ) {
		//"�f�B�X�N�̋󂫗e�ʂ�����܂���I�@�Í����t�@�C����ۑ��ł��܂���B\n
		//�Í����𒆎~���܂��B;"
		MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_NO_DISK_FREE_SPACE);
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		delete pms;
		goto LabelError;
	}
}
else{
	// -1�̓l�b�g���[�N�h���C�u�̉\��������̂Ŗ���
	//(������A�ʂ̃G���[�̏ꍇ�A���ۏ������݂Ɉڍs�����Ƃ��G���[����������)
}

//-----------------------------------
// ���s�\�`���ł���
// ���v�o�C�g����4GB���z�����Ƃ��̃G���[
//-----------------------------------
if ( fExeOutputOption == true && fOver4gbOk == false && AllTotalSize > SIZE_4GB ){

	//���s�`���t�@�C���̃T�C�Y��4GB�𒴂��Ă��܂��\��������܂��I\n
	//Win32�A�v���P�[�V�����Ƃ��Ď��s�ł��Ȃ��Ȃ邩������܂��񂪂�낵���ł����H';
	MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_OVER_4GB_EXE);
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbYes << mbNo;
	MsgDefaultButton = mbNo;
	Synchronize(&PostConfirmMessageForm);

	if ( MsgReturnVal == mbNo) {
		//�L�����Z��
		delete pms;
		goto LabelStop;
	}

}

//-----------------------------------
// �Í����t�@�C���̐����J�n
//-----------------------------------

//'�Í������Ă��܂�...'
ProgressStatusText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_TITLE_ENCRYPTING);

try{
	fsOut = new TFileStream(OutFilePath, fmCreate);
	fOpenOut = true;
}
catch(...){
	//'�ۑ������̃t�@�C�����J���܂���B���̃A�v���P�[�V�������g�p���̉\��������܂��B'
	MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_OUT_FILE_OPEN) + "\n" + OutFilePath;
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	delete pms;
	goto LabelError;
}

//-----------------------------------
// ���s�\�`���̏o��
//-----------------------------------
if ( fExeOutputOption == true ){

	//-----------------------------------
	// �����̂��K������s�f�[�^�𒊏o
	//-----------------------------------

	//�������g�̎��s�t�@�C�����J��
	try{
		fsExe = new TFileStream(Application->ExeName, fmShareDenyNone);
	}
	catch(...){
		//'���s�\�`���o�͂Ɏ��s���܂����B�Í��������𒆎~���܂��B'
		MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_EXEOUT_FAILED);
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
		delete pms;
		goto LabelError;
	}

	//�؂�o���T�C�Y���擾
	fsExe->Seek(-(__int64)sizeof(__int64), TSeekOrigin::soEnd);
	fsExe->Read(&ExeAllSize, sizeof(__int64));

	//���Ȏ��s�\�`���f�[�^�̋��E��
	fsExe->Seek(-(__int64)ExeAllSize-sizeof(__int64), TSeekOrigin::soEnd);

	while(fsExe->Read(read_buffer, BUF_SIZE) != 0 ){
		ExeSize+=BUF_SIZE;
		//��������
		if ( ExeSize < ExeAllSize ){
			fsOut->Write(read_buffer, BUF_SIZE);
		}
		else{
			fsOut->Write(read_buffer, ExeSize-ExeAllSize);
		}
	}
	//�������g�����
	delete fsExe;

}

//-----------------------------------
// �w�b�_���̕`������
//-----------------------------------

pms->SaveToStream(fsOut);	//fsOut�ɒǋL
delete pms;


//-----------------------------------
// Rijndael�̏�����
//-----------------------------------

gentables();

gkey( 8, 8, key);

// �������x�N�g���𐶐����Đ擪�ɏ�������
fillrand(chain_buffer, BUF_SIZE);

if ( fsOut->Write(chain_buffer, BUF_SIZE) < BUF_SIZE ){
	//''�ۑ���Ɏw�肳�ꂽ�Í����t�@�C���ɏ������߂܂���B
	MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_OUT_FILE_WRITE) + "\n" + OutFilePath;
	MsgType = mtError;
	MsgButtons = TMsgDlgButtons() << mbOK;
	MsgDefaultButton = mbOK;
	Synchronize(&PostConfirmMessageForm);
	goto LabelError;
}

//-----------------------------------
// zlib �������i���k�ɂ����Ă��ׂẴ������Ǘ������C�u�����ɔC����j
z.zalloc = Z_NULL;
z.zfree  = Z_NULL;
z.opaque = Z_NULL;
//z.next_in = Z_NULL;

// ��2�����͈��k�̓x���B0�`9 �͈̔͂̐����ŁC0 �͖����k
// Z_DEFAULT_COMPRESSION (= 6) ���W��

if (deflateInit(&z, CompressRateNum) != Z_OK){
	//zlib�G���[�\���̓��x�����
	goto LabelError;
}

//�o�̓o�b�t�@�̏�����
for(i = 0; i < BUF_SIZE; i++){
	out_buffer[i] = 0;
}

// zlib�ɓ��o�̓o�b�t�@���Z�b�g����
z.avail_in  = 0;                    // ���̓o�b�t�@���̃f�[�^�̃o�C�g��
z.next_out  = out_buffer;           // �o�̓o�b�t�@�c��
z.avail_out = BUF_SIZE;             // �o�̓|�C���^

// �ʏ�� deflate() �̑�2������ Z_NO_FLUSH �ɂ��ČĂяo��
flush = Z_NO_FLUSH;

TotalSize = 0;
FileIndex = 0;

while(!Terminated) {

	//-----------------------------------
	//����
	//-----------------------------------
	if ( z.avail_in == 0 && flush != Z_FINISH){

		pos = 0;

		for(i = 0; i < BUF_SIZE; i++){
			source_buffer[i] = 0;
			read_buffer[i] = 0;
		}

		while ( pos < BUF_SIZE ){

			//�I�[�v�����̃t�@�C��������΂�������ǂ�
			if ( fOpenIn == true ) {

				if (pos < BUF_SIZE) {

					len = fsIn->Read(read_buffer, BUF_SIZE - pos);
					TotalSize+=len;

					for (i = 0; i < len; i++) {
						source_buffer[pos+i] = read_buffer[i];
					}

					if (len < BUF_SIZE - pos) {
						fOpenIn = false; //�t�@�C�������
						delete fsIn;
					}

				}

				pos += len;

			}
			//�t�@�C�����J��
			else{
				if (FileIndex < FilePathList->Count) {
					while(FileIndex < FilePathList->Count){
						if (FilePathList->Strings[FileIndex] != "") {
							try{
								fsIn = new TFileStream(FilePathList->Strings[FileIndex], fmOpenRead);
								fOpenIn = true;
								FileIndex++;
								break;
							}
							catch(...){
								//'�Í�������t�@�C�����J���܂���B���̃A�v���P�[�V�������g�p���̉\��������܂��B'
								MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_FILE_OPEN);
								MsgType = mtError;
								MsgButtons = TMsgDlgButtons() << mbOK;
								MsgDefaultButton = mbOK;
								Synchronize(&PostConfirmMessageForm);
								fOpenIn = false;
								goto LabelError;
							}
						}
						FileIndex++;
					}
				}
				else{

					//�ǂݍ��ރt�@�C�����Ȃ��Ȃ����̂ŁA
					//���K�Ƀ_�~�[�̃}�[�W���f�[�^��}������
					//
					//�y�⑫�z
					// �{���͂����ɂ���}�[�W���f�[�^�}�������͕s�v�ł����A
					// �̂ɍ�����ۂɕ����̍ۂɈ��k�f�[�^���E�̃`�F�b�N��
					// �ӂ��Ă������߁A���̂悤�ɗ]���ȃf�[�^��
					// ����Ă����Ƃ����͋Ƃ��g���Ă��܂��i���݂܂���...�j
					fillrand(margin_buffer, BUF_SIZE);

					for (i = pos; i < BUF_SIZE; i++) {
						source_buffer[i] = margin_buffer[i];
					}

					pos = BUF_SIZE;
					MarginBufSize -= BUF_SIZE;

				}//end if (FileIndex < FilePathList->Count);

			}//end if ( fOpenIn == true );

		}//while ( pos < BUF_SIZE && 0 < MarginBufSize );

		if (MarginBufSize < 1) {
			flush = Z_FINISH;	//���̓o�b�t�@�͂��ꂪ�Ō�
		}

		z.next_in = source_buffer;
		z.avail_in = pos;

	}//end if ( z.avail_in == 0 );

	//-----------------------------------
	//���k
	//-----------------------------------
	if ( z.avail_out > 0 ){
		status = deflate(&z, flush);
	}
	if (status == Z_STREAM_END){
			break;
	}
	if (status != Z_OK ){
		//#define Z_OK              0
		//#define Z_STREAM_END      1
		//#define Z_NEED_DICT       2
		//#define Z_ERRNO         (-1)
		//#define Z_STREAM_ERROR  (-2)
		//#define Z_DATA_ERROR    (-3)
		//#define Z_MEM_ERROR     (-4)
		//#define Z_BUF_ERROR     (-5)
		//#define Z_VERSION_ERROR (-6)
		goto LabelError;
	}
	//-----------------------------------
	//�o��
	//-----------------------------------
	if ( z.avail_out == 0 ){

		// CBC - xor the file bytes with the IV bytes
		for(i = 0; i < BUF_SIZE; i++){
			out_buffer[i] ^= chain_buffer[i];
		}

		//encrypt!
		rijndael_encrypt(out_buffer);

		len = fsOut->Write(out_buffer, BUF_SIZE);

		if (len < BUF_SIZE) {
			//'�ۑ���Ɏw�肳�ꂽ�Í����t�@�C���ɏ������߂܂���B
			MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_OUT_FILE_WRITE) + "\n" + OutFilePath;
			MsgType = mtError;
			MsgButtons = TMsgDlgButtons() << mbOK;
			MsgDefaultButton = mbOK;
			Synchronize(&PostConfirmMessageForm);
			goto LabelError;
		}

		for(i = 0; i < BUF_SIZE; i++){
			chain_buffer[i] = out_buffer[i];
			out_buffer[i] = 0;
		}

		z.next_out = out_buffer;    // �o�̓o�b�t�@�c�ʂ����ɖ߂�
		z.avail_out = BUF_SIZE;     // �o�̓|�C���^�����ɖ߂�

	}

	//-----------------------------------
	//�i���󋵕\��
	ProgressPercentNum = ((float)TotalSize/AllTotalSize)*100;

	if ( fOpenIn == true ){
		ProgressMsgText = ExtractFileName(fsIn->FileName);
	}
	else{
		ProgressMsgText = ExtractFileName(OutFilePath);
	}


}//while(!Terminated);

if (Terminated == true) {
	//���[�U�[�L�����Z���Ŕ����Ă���
	goto LabelStop;
}

//�c��̃o�b�t�@
if (z.avail_out > 0) {

		// PKCS #7
		paddingNum = z.avail_out;
		len = BUF_SIZE - paddingNum;

		for(i = len; i < BUF_SIZE; i++){
			out_buffer[i] = paddingNum;
		}

		// CBC - xor the file bytes with the IV bytes
		for(i = 0; i < BUF_SIZE; i++){
			out_buffer[i] ^= chain_buffer[i];
		}

		//encrypt!
		rijndael_encrypt(out_buffer);

		if ((len = fsOut->Write(out_buffer, BUF_SIZE)) != BUF_SIZE){
			//'�ۑ���Ɏw�肳�ꂽ�Í����t�@�C���ɏ������߂܂���B
			MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_OUT_FILE_WRITE) + "\n" + OutFilePath;
			MsgType = mtError;
			MsgButtons = TMsgDlgButtons() << mbOK;
			MsgDefaultButton = mbOK;
			Synchronize(&PostConfirmMessageForm);
			goto LabelError;
		}

}

if (deflateEnd(&z) != Z_OK){
	//zlib�G���[
	goto LabelError;
}


//-----------------------------------
// ���s�\�`���t�@�C����
// �����ֈÍ����f�[�^�T�C�Y����������
//-----------------------------------
if ( fExeOutputOption == true ){
	ExeSize = fsOut->Seek((__int64)0, TSeekOrigin::soEnd);
	ExeSize = ExeSize-ExeAllSize;
	fsOut->Write(&ExeSize, sizeof(__int64));
}

//-----------------------------------
// ����
//-----------------------------------
ProgressPercentNum = 100;
//'����'
ProgressStatusText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_TITLE_COMPLETE);
ProgressMsgText = ExtractFileName(OutFilePath);

if (fOpenIn == true) {
	delete fsIn;
}
if (fOpenOut == true) {
	delete fsOut;
}

//�o�͂���Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹��
if ( fKeepTimeStamp == true && first_fd.cFileName[0] != NULL ) {

	hFile = CreateFileW(FilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE) {
		SetFileTime( hFile, &first_fd.ftCreationTime, &first_fd.ftLastAccessTime, &first_fd.ftLastWriteTime);
		CloseHandle(hFile);
	}
}

delete FilePathList;

StatusNum = 1;
return;

//-----------------------------------
// �G���[�̌�n��
//-----------------------------------
LabelError:

	ProgressPercentNum = 0;

	if ( status < 0 ){
		//'zlib���C�u��������G���[��Ԃ���܂����B'
		//'�G���[�ԍ��F'
		MsgText = LoadResourceString(&Msgencrypt::_MSG_ERROR_ZLIB) + IntToStr(status) + "\n" + z.msg;
		MsgType = mtError;
		MsgButtons = TMsgDlgButtons() << mbOK;
		MsgDefaultButton = mbOK;
		Synchronize(&PostConfirmMessageForm);
	}

	//'�G���['
	ProgressStatusText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_TITLE_ERROR);
	//'�Í����Ɏ��s���܂����B'
	ProgressMsgText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_DETAIL_FAILED);

	if (fOpenIn == true) {
		delete fsIn;
	}
	if (fOpenOut == true) {
		delete fsOut;
	}

	delete FilePathList;
	StatusNum = -1;

	return;


//-----------------------------------
// ���[�U�[�L�����Z���̌�n��
//-----------------------------------
LabelStop:

	ProgressPercentNum = 0;
	//'�L�����Z��'
	ProgressStatusText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_TITLE_USER_CANCEL);
	//'�Í��������~����܂����B'
	ProgressMsgText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_DETAIL_STOPPED);

	if (fOpenIn == true) {
		delete fsIn;
	}
	if (fOpenOut == true) {
		delete fsOut;
	}

	delete FilePathList;
	StatusNum = -2;

	return;

}
//---------------------------------------------------------------------------
// �������x�N�g���iIV�j�̐���
//---------------------------------------------------------------------------
void TAttacheCaseFileEncrypt::fillrand(char *buf, const int len)
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
// �w�b�_���𐶐�����
//===========================================================================
bool __fastcall TAttacheCaseFileEncrypt::CreateHeaderData
		 ( TMemoryStream *pms,
			 TStringList   *FileList,
			 TStringList   *FilePathList,
			 __int64       &AllTotalFileSize
		 )
{

int i, c;

int ret;
int Index = 0;
int HeaderSizeAddress = 0;
TSearchRec sr;
String OneLine;
String DirPath, FileName;

//�Í����g�[�N��
const AnsiString Passcode_AttacheCase = "Passcode:AttacheCase\n";
//�Í����t�@�C���̍쐬��
AnsiString LastDateTimeString = "LastDateTime:" + DateTimeToStr(Now()) + "\n";

int EncryptHeaderSize = 0;  //�Í����w�b�_�T�C�Y

char buffer[BUF_SIZE];
char chain_buffer[BUF_SIZE];

TStringList *HeaderDataList;
TMemoryStream* tpms;          //�e���|�����������X�g���[��

//-----------------------------------
// �w�b�_���i�����j
//-----------------------------------
const char charReservedValue[4] = { 0, 0, 0, 0 };

const char charDataSubVersion = ATC_DATA_SUB_VERSION;
const char charOptMissTypeLimitsNumOption = intOptMissTypeLimitsNumOption;
const char charOptBrokenFileOption = (fOptBrokenFileOption > 0 ? 1 : 0);
const char charTokenString[16] = "_AttacheCaseData";
const int DataFileVersion = ATC_DATA_FILE_VERSION;
const int AlgorismType = TYPE_ALGORISM_RIJNDAEL;

//�f�[�^�T�u�o�[�W����                              : 1byte
pms->Write(&charDataSubVersion, sizeof(char));
//�\��f�[�^(reserved�j                             : 1byte
pms->Write(&charReservedValue, sizeof(char));
//�~�X�^�C�v��                                    : 1byte
pms->Write(&charOptMissTypeLimitsNumOption, sizeof(char));
//�j�󂷂邩�ۂ�                                    : 1byte
pms->Write(&charOptBrokenFileOption, sizeof(char));
//�g�[�N��                                          : 16byte
pms->Write(&charTokenString, 16);
//�f�[�^�t�@�C���o�[�W����                          : 4byte
pms->Write(&DataFileVersion, sizeof(int));
//�A���S���Y���^�C�v                                : 4byte
pms->Write(&AlgorismType, sizeof(int));
//�Í��������̃w�b�_�f�[�^�T�C�Y�i��Ɋm�ۂ��Ă����j�F4byte
HeaderSizeAddress = pms->Position;
pms->Write(&EncryptHeaderSize, sizeof(int));

//-----------------------------------
// �w�b�_���i�Í��������j
//-----------------------------------

//�i���󋵕\��
ProgressPercentNum = -1;
//'�t�@�C�����X�g�̐���'
ProgressStatusText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_TITLE_LISTING);
//'�Í������邽�߂̏��������Ă��܂�...'
ProgressStatusText = LoadResourceString(&Msgencrypt::_LABEL_STATUS_DETAIL_PREPARING);

//�w�b�_�f�[�^���X�g�i������j
HeaderDataList = new TStringList;
//�p�X���[�h
HeaderDataList->Add(Passcode_AttacheCase);
//�쐬��
HeaderDataList->Add(LastDateTimeString);

for ( i = 0; i < FileList->Count; i++ ){
	//�t�@�C��
	if (FileExists(FileList->Strings[i]) == true) {
		DirPath = ExtractFileDir(FileList->Strings[i]);
		FileName = ExtractFileName(FileList->Strings[i]);
		AllTotalFileSize =
			GetFileInfoList(Index, DirPath, FileName, FileList->Strings[i], FilePathList, HeaderDataList);
	}
	//�f�B���N�g��
	else{
		DirPath = ExtractFileDir(FileList->Strings[i]);
		FileName = ExtractFileName(FileList->Strings[i]);
		//�g�b�v�f�B���N�g��
		GetFileInfoList(Index, DirPath, FileName, FileList->Strings[i], FilePathList, HeaderDataList);
		//���̔z��
		AllTotalFileSize =
			GetFileInfoList(Index, FileList->Strings[i], "", FileList->Strings[i], FilePathList, HeaderDataList);
	}

	//���[�U�[�L�����Z��
	if (Terminated == true) {
		delete HeaderDataList;
		return(false);
	}

}// end for;

//�������X�g���[���֏�������
tpms = new TMemoryStream;

/* ------------------------------------------------
 ���o�[�W�����ňÍ������ꂽ�t�@�C���̉��ʌ݊����ƁA
 �V�o�[�W�����ɂ��Unicode�t�@�C�����ɑΉ����邽�߁A
 �ȉ��̂悤�Ƀt�@�C�����X�g�����d�������Ă��܂��B
 ���ɗǂ����@������΍�҂܂ł���Ă����������
 ���ꂵ���ł��B
--------------------------------------------------- */

//���o�[�W�����p�ɕۑ�
HeaderDataList->SaveToStream(tpms, TEncoding::GetEncoding(932)); //shift-jis

//�V�o�[�W�����iver.2.8.0�`�j�p�ɕۑ�
for (i = 0; i < HeaderDataList->Count; i++) {
	HeaderDataList->Strings[i] =
		StringReplace(HeaderDataList->Strings[i], "Fn_", "U_", TReplaceFlags() << rfIgnoreCase );
}

//HeaderDataList->SaveToStream(tpms, TEncoding::UTF8); //UTF-8

//UTF-8�Ƃ��ď������ނ���TBytes�ŏ������񂾕������������������悤���B
TBytes ByteArray = HeaderDataList->Text.BytesOf();
tpms->Write(&ByteArray[0], ByteArray.Length);

delete HeaderDataList;

//-----------------------------------
//�w�b�_���̈Í���
//-----------------------------------

//�Í����̏���
gentables();
//�L�[����
gkey( 8, 8, key);

for (i = 0; i < BUF_SIZE; i++) {
	buffer[i] = 0;
}

//�������x�N�g���iIV�j�𐶐�
fillrand(chain_buffer, BUF_SIZE);
pms->Write(chain_buffer, BUF_SIZE);

//�擪�Ƀ|�C���^��߂�
tpms->Seek((__int64)0, TSeekOrigin::soBeginning);
EncryptHeaderSize = 0;

tpms->Size;

//CBC���[�h�ŏ�������
while (tpms->Read( buffer, BUF_SIZE ) != NULL){

	EncryptHeaderSize += BUF_SIZE;

	// xor
	for ( i = 0; i < BUF_SIZE; i++ ){
		buffer[i] ^= chain_buffer[i];
	}

	// rijndael
	rijndael_encrypt(buffer);

	pms->Write(buffer, BUF_SIZE);

	//CBC���o�b�t�@�̏�����
	for ( i = 0; i < BUF_SIZE; i++ ){
		chain_buffer[i] = buffer[i];
		buffer[i] = 0;
	}

	//���[�U�[�L�����Z��
	if (Terminated == true) {
		delete tpms;
		return(false);
	}

}//loop;

delete tpms;

//�Í��������̃w�b�_�f�[�^�T�C�Y�i�m�ۂ��Ă������ꏊ�։��߂ď������ށj
pms->Position = HeaderSizeAddress;
pms->Write(&EncryptHeaderSize, sizeof(int));
//�擪�Ƀ|�C���^��߂�
pms->Seek((__int64)0, TSeekOrigin::soBeginning);

return(true);


}//end CreateHeaderData;
//===========================================================================
// �Í�������t�@�C�����X�g�ƃt�@�C�����̃��X�g�𓯎���������
//===========================================================================
__int64 __fastcall TAttacheCaseFileEncrypt::GetFileInfoList
	( int &Index,
		String DirPath,
		String FileName,
		String BasePath,
		TStringList *FileList,
		TStringList *DataList
	)
{

/* ------------------------------------------------
 �t�@�C�����X�g�̃t�@�C���ԍ��̓��ɁuFn_*:�v��
 �Ȃ��d������悤�ȋL�����}������Ă��邩�ƌ����܂���
 ���܂�Ӗ��͂������܂���E�E�E���p��������������E�E�E
 ���݂܂���A�����ver.1����̎d�l�����������Ă���̂ƁA
 �K�쎞��ɂ������������Ӗ��ȃf�[�^�d�l�̈�ł��B
--------------------------------------------------- */

int ret;
__int64 TotalSize = 0;

bool fParent = false;
String OneLine;
String FilePath;
String FileNameString;

TSearchRec sr;
//_WIN32_FIND_DATAW fd;

DirPath = IncludeTrailingPathDelimiter(DirPath);

if (FileName == "") {  //�f�B���N�g��
	FileName = "*.*";
}
else{
	fParent = true;
}

ret = FindFirst(DirPath + FileName, faAnyFile, sr);

while (ret == 0) {

	if (sr.Name != "." && sr.Name != "..") {

		FilePath = DirPath + sr.Name;
		FileNameString = ExtractRelativePath(BasePath, FilePath);

		//-----------------------------------
		//�f�B���N�g��
		if (sr.Attr & faDirectory) {

			// Win95/98�n�i��Ή������ꉞ�j
			if ( Win32Platform == VER_PLATFORM_WIN32_WINDOWS ){
				OneLine =
					"Fn_" + IntToStr((int)Index) + ":" +                 //�C���f�b�N�X
					FileNameString + "\\\t" +                            //�f�B���N�g����
					"*\t16\t0\t0\t0\t0";                                 //�c���0
			}
			else{
				// _WIN32_FIND_DATAW �\����
				//fd = sr.FindData;
				OneLine =
					"Fn_" + IntToStr((int)Index) + ":" +                 //�C���f�b�N�X
					FileNameString + "\\\t" +                            //�f�B���N�g���̑��΃p�X
					"*\t" +                                              //�t�@�C���T�C�Y(=0)
					IntToStr(sr.Attr) + "\t" +                           //����
					TimeStampToString(sr.FindData.ftLastWriteTime)+"\t"+ //�X�V����
					TimeStampToString(sr.FindData.ftCreationTime);       //�쐬����

					//�o�͂���Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹�邽�ߕێ�
					if ( fKeepTimeStamp == true && first_fd.cFileName[0] == NULL ) {
						first_fd = sr.FindData;
					}

			}

			FileList->Add("");      //�f�B���N�g���͋�s
			DataList->Add(OneLine);
			Index++;

			if (fParent == false) {
				//�ċA�Ăяo��
				TotalSize += GetFileInfoList(Index, FilePath, "", BasePath, FileList, DataList);
			}

		}
		//-----------------------------------
		//�t�@�C��
		else{
			OneLine =
				"Fn_" + IntToStr((int)Index) + ":" +                   //�C���f�b�N�X
				FileNameString + "\t" +                                //�t�@�C���̑��΃p�X
				IntToStr(sr.Size) + "\t" +                             //�t�@�C���T�C�Y
				IntToStr(sr.Attr) + "\t" +                             //����
				TimeStampToString(sr.FindData.ftLastWriteTime)+"\t"+   //�X�V����
				TimeStampToString(sr.FindData.ftCreationTime);         //�쐬����

			//�o�͂���Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹�邽�ߕێ�
			if ( fKeepTimeStamp == true && first_fd.cFileName[0] == NULL ) {
				first_fd = sr.FindData;
			}

			if (sr.Size > 0) {
				FileList->Add(FilePath);
			}
			else{
				FileList->Add("");      //��t�@�C���͉����Ȃ�
			}

			DataList->Add(OneLine);
			Index++;

			//�t�@�C�����v
			TotalSize += sr.Size;

		}
		//-----------------------------------

	}//end if;

	ret = FindNext(sr);

}//while;

FindClose(sr);

return(TotalSize);


}//end GetFileInfoList;
//===========================================================================
//FILETIME�\���̂�TTimeStamp�ɕϊ����ĕ�����Ƃ��Ď擾����
//===========================================================================
String __fastcall TAttacheCaseFileEncrypt::TimeStampToString(FILETIME ft)
{

SYSTEMTIME st;
TDateTime dt;
TTimeStamp ts;

//FileTime �� SystemFileTime
FileTimeToSystemTime(&ft, &st);
//SystemTime �� TDateTime
dt = SystemTimeToDateTime(st);
//TDateTime �� TimeStamp
ts = DateTimeToTimeStamp(dt);

/*
//�t�@�C��/�f�B���N�g���̓������Ȃ�
//�킴�킴�T�C�Y���傫��TTimeStamp�ɕϊ����Ċi�[�����̂��H
//���߂�Ȃ����A�Ӗ��͂���܂���(��)�B

struct TTimeStamp
{
	int Time;
	int Date;
};
*/

return(IntToStr(ts.Date)+"\t"+IntToStr(ts.Time));

}
//===========================================================================
//�f�B�X�N�̋󂫗e�ʂ𒲂ׂ�
//===========================================================================
__int64 __fastcall TAttacheCaseFileEncrypt::GetDiskFreeSpaceNum(String FilePath)
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
//�p�X���[�h��������Z�b�g����
//===========================================================================
/*
void __fastcall TAttacheCaseFileEncrypt::SetPasswordString(AnsiString Password)
{

for (int i = 0; i < 32; i++) {
	key[i] = 0;
}

StrCopy(key, Password.c_str());

}
*/
//===========================================================================
//�p�X���[�h�Ƀo�C�i���l���Z�b�g����
//===========================================================================
void __fastcall TAttacheCaseFileEncrypt::SetPasswordBinary(char *password)
{

for (int i = 0; i < 32; i++) {
	key[i] = 0;
}

memcpy(key, password, 32);

}
//===========================================================================
//���ݐݒ肳��Ă���p�X���[�h���擾����
//===========================================================================
void __fastcall TAttacheCaseFileEncrypt::GetPasswordBinary(char *password)
{

memcpy(password, key, 32);

}
//===========================================================================
//���C���t�H�[���Ɋm�F���b�Z�[�W�𓊂��ď����𒆒f����
//===========================================================================
void __fastcall TAttacheCaseFileEncrypt::PostConfirmMessageForm()
{

//���ȉ����A�O���[�o���ϐ�(private)�Ƃ��Ē�`���Ă���
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
void __fastcall TAttacheCaseFileEncrypt::PostConfirmOverwriteMessageForm()
{

//�O���[�o���ϐ�(private)�Ƃ��Ē�`���Ă���

//String MsgText;
//String MsgReturnPath;

MsgReturnVal = Form1->ShowConfirmOverwriteMassageForm(MsgText, MsgReturnPath);

}
//===========================================================================

