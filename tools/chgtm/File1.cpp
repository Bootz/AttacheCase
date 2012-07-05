//---------------------------------------------------------------------------

#include <vcl.h>

//printf
#include <stdio.h>
#include <locale.h>

#pragma hdrstop

#include <tchar.h>
//---------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{

setlocale(LC_CTYPE, "");  //���ꂪ�Ȃ��ƕ�����������

//�����w�肪�Ȃ��Ƃ��͌��ݓ���
TDateTime BaseDateTime = Now();

String FilePath = String(argv[1]);

//-----------------------------------
//�쐬������ύX

SYSTEMTIME      sysTime;
FILETIME        fTime,   fLocTime;

//�t�@�C�����J��
HANDLE hFile = CreateFileW( FilePath.c_str(), GENERIC_READ | GENERIC_WRITE,
										0, NULL, OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL, NULL );

if( hFile == INVALID_HANDLE_VALUE ) {
	wprintf(L"\"%s\" �̍쐬�����̕ύX�Ɏ��s���܂���\n", FilePath.c_str());
	return 1;
}
else{

	if (argc > 2 ) {
		BaseDateTime =TDateTime(StrToIntDef(argv[2], 0),    //year
																			StrToIntDef(argv[3], 0),    //month
																			StrToIntDef(argv[4], 0),    //day
																			StrToIntDef(argv[5], 0),    //hour
																			StrToIntDef(argv[6], 0),    //min
																			StrToIntDef(argv[7], 0),    //sec
																			StrToIntDef(argv[8], 0)     //msec
																				);
	}

	DateTimeToSystemTime(BaseDateTime, sysTime);
	SystemTimeToFileTime( &sysTime, &fLocTime );
	LocalFileTimeToFileTime( &fLocTime, &fTime );
	SetFileTime( hFile, &fTime, &fTime, &fTime );
	CloseHandle( hFile );

}

wprintf(L"\"%s\" �̃^�C���X�^���v��ύX���܂���\n", FilePath.c_str());

return 0;



}//end main();
//---------------------------------------------------------------------------

