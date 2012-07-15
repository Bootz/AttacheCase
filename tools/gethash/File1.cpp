//---------------------------------------------------------------------------

#include <vcl.h>

#include <IdHashMessageDigest.hpp>
#include <IdHashSHA1.hpp>
#include <stdio.h>
#include <locale.h>

#include "md5.h"
#include "sha1.h"

#define BUF_SIZE 20480

#pragma hdrstop

#include <tchar.h>

//---------------------------------------------------------------------------

// �t�@�C������MD5���Z�o���ĕ�����ŕԂ�
String __fastcall GetMD5FromFile(String FilePath);
// �t�@�C������SHA1���Z�o���ĕ�����ŕԂ�
String __fastcall GetSHA1FromFile(String FilePath);

//---------------------------------------------------------------------------
#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{

setlocale(LC_CTYPE, "");  //���ꂪ�Ȃ��ƕ�����������

int i;
String DirPath, FilePath, FileName;
TStringList *FileList = new TStringList;

int ret;
TSearchRec sr;

String OutFilePathMD5, OutFilePathSHA1;
TStringList *SaveFileList;

String MD5String, SHA1String;

TFileStream *fs;
TIdHashMessageDigest5 *md5;
TIdHashSHA1 *sha1;

for (i = 1; i < argc; i++) {

	FilePath = ExpandUNCFileName(argv[i]);
	DirPath = ExtractFileDir(FilePath);
	FileName = ExtractFileName(FilePath);

	ret = FindFirst(IncludeTrailingPathDelimiter(DirPath)+FileName, faAnyFile, sr);

	while (ret == 0) {

		if (sr.Name != "." && sr.Name != "..") {
			if (sr.Attr & faDirectory) {
			}
			else{
				FileList->Add(IncludeTrailingPathDelimiter(DirPath)+sr.Name);
			}
		}
		ret = FindNext(sr);
	}

	FindClose(sr);
}

if (FileList->Count == 0) {
	wprintf(L"�w��̃t�@�C����������܂���ł����B\n");
	delete FileList;
	return 1;
}

for (i = 0; i < FileList->Count; i++) {

	FilePath = FileList->Strings[i];
	wprintf(L"%s\n", FilePath);

	//-----------------------------------
	wprintf(L"MD5�n�b�V�����v�Z��...\n");
	MD5String = LowerCase(GetMD5FromFile(FilePath));   //��������

	if (MD5String == "") {
		wprintf(L"%s\nMD5�n�b�V���̎擾�Ɏ��s���܂����B\n", FilePath);
		break;
	}
	else{
		wprintf(L"%s\n", MD5String.c_str());
	}

	//�e�L�X�g�t�@�C���ɕۑ�����
	OutFilePathMD5 = FilePath + ".md5";
	SaveFileList = new TStringList;
	SaveFileList->Add(MD5String);
	SaveFileList->SaveToFile(OutFilePathMD5);
	delete SaveFileList;

	//-----------------------------------
	wprintf(L"SHA-1�n�b�V�����v�Z��...\n");
	SHA1String = LowerCase(GetSHA1FromFile(FilePath));   //��������

	if (SHA1String == "") {
		wprintf(L"%s\nSHA-1�n�b�V���̎擾�Ɏ��s���܂����B\n", FilePath);
		break;
	}
	else{
		wprintf(L"%s\n", SHA1String.c_str());
	}

	//�e�L�X�g�t�@�C���ɕۑ�����
	OutFilePathSHA1 = FilePath + ".sha1";
	SaveFileList = new TStringList;
	SaveFileList->Add(SHA1String);
	SaveFileList->SaveToFile(OutFilePathSHA1);
	delete SaveFileList;

}

//system("pause");
delete FileList;

return 0;

}
//---------------------------------------------------------------------------
// �t�@�C������MD5���Z�o���ĕ�����ŕԂ�
//---------------------------------------------------------------------------
String __fastcall GetMD5FromFile(String FilePath)
{

int i;
String ReturnText;

__int64 TotalSize = 0;
__int64 FileSize;
float percent;
int PercentNum;

int bytes;
unsigned char buffer[BUF_SIZE];
char textbuffer[BUF_SIZE];

String result;

if ( !FileExists(FilePath)) return("");

int fh = FileOpen(FilePath, fmOpenRead);

if (fh < 0) {
	//�I�[�v���Ɏ��s
	wprintf(L"�t�@�C���I�[�v���Ɏ��s���܂����B\n", FilePath);
	return("");
}

FileSize = FileSeek(fh, (__int64)0, 2);
FileSeek(fh, 0, 0);

MD5_CTX mdContext;

//MD5 - ������
MD5Init(&mdContext);

//�t�@�C���ǂݏo��
while ((bytes = FileRead (fh, buffer, BUF_SIZE)) != 0){

	MD5Update (&mdContext, buffer, bytes);
	TotalSize+=bytes;

	percent = (float)TotalSize/FileSize;
	PercentNum = int(percent*100);
	wprintf(L"MD5 �v�Z�� - %d%%\r", PercentNum);

}

wprintf(L"MD5 �v�Z���� - 100%%\n");

MD5Final(&mdContext);

FileClose(fh);

for (i = 0; i < BUF_SIZE; i++)
	textbuffer[i] = NULL;

for (i = 0; i < 16; i++)
	buffer[i] = mdContext.digest[i];

BinToHex( buffer, textbuffer, 16);

return((String)textbuffer);

}
//---------------------------------------------------------------------------
// �t�@�C������SHA1���Z�o���ĕ�����ŕԂ�
//---------------------------------------------------------------------------
String __fastcall GetSHA1FromFile(String FilePath)
{

int i;
String ReturnText;

__int64 TotalSize = 0;
__int64 FileSize;
float percent;
int PercentNum;

SHA1Context sha;
unsigned char Message_Digest[20];

int bytes;
unsigned char buffer[BUF_SIZE];
char textbuffer[BUF_SIZE];

String result;

if ( !FileExists(FilePath)) return("");

int fh = FileOpen(FilePath, fmOpenRead);

if (fh < 0) {
	//�I�[�v���Ɏ��s
	wprintf(L"�t�@�C���I�[�v���Ɏ��s���܂����B\n", FilePath);
	return("");
}

FileSize = FileSeek(fh, (__int64)0, 2);
FileSeek(fh, 0, 0);

//�������i���Z�b�g�j
if ( SHA1Reset(&sha))return("");

//�t�@�C���ǂݏo��
while ((bytes = FileRead (fh, buffer, BUF_SIZE)) != 0){
	if ( SHA1Input(&sha, (const unsigned char *)buffer, bytes) ){
		return("");
	}

	TotalSize+=bytes;
	percent = (float)TotalSize/FileSize;
	PercentNum = int(percent*100);
	wprintf(L"SHA-1 �v�Z�� - %d%%\r", PercentNum);

}

wprintf(L"SHA-1 �v�Z���� - 100%%\n");

//�o��
if ( SHA1Result(&sha, Message_Digest) )	return("");

FileClose(fh);

for (i = 0; i < BUF_SIZE; i++)
	textbuffer[i] = NULL;

for (i = 0; i < 20; i++)
	buffer[i] = Message_Digest[i];

BinToHex( buffer, textbuffer, 20);

return((String)textbuffer);

}
//---------------------------------------------------------------------------


