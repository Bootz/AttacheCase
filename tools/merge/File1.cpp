//---------------------------------------------------------------------------

#include <vcl.h>

//printf
#include <stdio.h>

#pragma hdrstop

#define BUF_SIZE 256

#include <tchar.h>
//---------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{

//���P�[���̐ݒ�
_tsetlocale(LC_ALL, _T(""));

//-----------------------------------
//�p�����[�^�`�F�b�N
//-----------------------------------
String FilePath = ExpandFileName(String(argv[1]));  //�A�^�b�V�F�P�[�X�{��
String mFilePath = ExpandFileName(String(argv[2])); //Merge���鎩�Ȏ��s�t�@�C��

if ( FileExists(FilePath) == false ){
	wprintf(L"\"%s\" - �}�[�W����{�̂̃t�@�C����������܂���B\n", FilePath.c_str());
	return 1;
}

if ( FileExists(mFilePath) == false ){
	wprintf(L"\"%s\" - �}�[�W����t�@�C����������܂���B\n", mFilePath.c_str());
	return 1;
}

//-----------------------------------
// �}�[�W
//-----------------------------------

int i;

int pos;
int bufsize;
char buffer[BUF_SIZE];

//�ǉ��t�@�C�����J��
int fh = FileOpen(FilePath, fmOpenReadWrite);
int mfh = FileOpen(mFilePath, fmOpenRead);

if (fh == -1 || mfh == -1) {
	wprintf(L"%s - �}�[�W����t�@�C�����J���܂���B", FilePath.c_str());
	FileClose(fh);
	FileClose(mfh);
	return 1;
}

//�}�[�W�t�@�C���̃T�C�Y�擾
__int64 size = FileSeek(mfh, (__int64)0, 2);
FileSeek(mfh, 0, 0);

//�{�̖����փ|�C���g
FileSeek(fh, 0, 2);

while ((pos = FileRead( mfh, buffer, BUF_SIZE )) != 0 ){

	if ( FileWrite( fh, buffer, pos) == -1 ){
		wprintf(L"%s - �������݂Ŏ��s���܂����B", FilePath.c_str());
		FileClose(fh);
		FileClose(mfh);
		return 1;
	}

	for ( i = 0; i < BUF_SIZE; i++ ){
		buffer[i] = NULL;
	}

}

//���K�Ƀ}�[�W�����t�@�C���T�C�Y�𖄂ߍ���
FileWrite( fh, &size, sizeof(__int64));

FileClose(fh);
FileClose(mfh);

wprintf(L"%s - �}�[�W�������܂����B\n", FilePath.c_str());

return 0;

}
//---------------------------------------------------------------------------
