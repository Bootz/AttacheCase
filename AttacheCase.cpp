//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include "Unit1.h"
#include "MsgWinMain.hpp"

//---------------------------------------------------------------------------
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit4.cpp", Form4);
//---------------------------------------------------------------------------
HANDLE mx;
void SendToMsgData(HWND handle);

//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	//'�A�^�b�V�F�P�[�X'
	String ApplicationTitle = LoadResourceString(&Msgwinmain::_TITLE_APP_NAME);
	HWND handle = NULL;

	mx = CreateMutex( NULL, true, "AtacheCase2" );

	if( GetLastError() ){
		//���łɋN�����̃A�^�b�V�F�P�[�X�̃E�B���h�E�n���h�����擾
		handle = ::FindWindowW(NULL, ApplicationTitle.c_str());
	}

	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = ApplicationTitle;
		Application->HelpFile = "AttacheCase.chm";
		Application->CreateForm(__classid(TForm1), &Form1);
		if ( handle != NULL && Form1->opthdl->fNoMultipleInstance == true){
			//���łɋN�����̃A�^�b�V�F�P�[�X�փ��b�Z�[�W�𑗂�
			SendToMsgData(handle);
			//���Ĕj��
			CloseHandle(mx);
			ReleaseMutex(mx);
		}
		else{
			Application->Run();
		}

	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;

}
//----------------------------------------------------------------------
//���łɋN�����̃A�^�b�V�F�P�[�X�փt�@�C�����X�g�����b�Z�[�W�Ƃ��đ���
//----------------------------------------------------------------------
void SendToMsgData(HWND handle)
{

int i;
TStringList *SendFileList = new TStringList;

WPARAM wParam;
LPARAM lParam;

COPYDATASTRUCT cds;

wParam = (WPARAM)Application->Handle;
lParam = (LPARAM)&cds;

//�R�}���h���C���������܂Ƃ߂�
for ( i = 1; i < ParamCount()+1 ; i++){
	if ( FileExists(ParamStr(i)) || DirectoryExists(ParamStr(i))){
		SendFileList->Add(ExpandFileName(ParamStr(i)));
	}
}

if ( SendFileList->Count > 0 ){

	// �f�[�^�T�C�Y�iUnicodeString�j
	int size = SendFileList->Text.Length()*SendFileList->Text.ElementSize() + 1;
	wchar_t *buffer = new wchar_t[size];
	ZeroMemory( buffer, size );                          // ������
	StrLCopy( buffer, SendFileList->Text.c_str(), size); // �o�b�t�@�փR�s�[

	cds.dwData = 1;
	cds.cbData = size;
	cds.lpData = (LPVOID)buffer;

	//�������
	::SendMessage(handle, WM_COPYDATA, wParam, lParam);

}

//�E�B���h�E��O�ʂ�
SetForegroundWindow(handle);

delete SendFileList;

}//end SendToMsgData;
//---------------------------------------------------------------------------




