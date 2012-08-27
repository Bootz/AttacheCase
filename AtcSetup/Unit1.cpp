//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

int opt;
String MsgText;

TRegistryIniFile *pReg;


try{

	//�������w�肳��Ă����ꍇ�̂݋N���`
	if ( ParamCount() > 0 ){

		pReg = new TRegistryIniFile ("Software\\Hibara");

		//�A�^�b�V�F�P�[�X�{�̂̃p�X
		AtcExeFilePath = pReg->ReadString( "AttacheCase\\AppInfo", "AppPath", "");

		if ( AtcExeFilePath == "" ){
			AtcExeFilePath = ExtractFileDir(ExpandUNCFileName(Application->ExeName))+"\\AtchCase.exe";
		}

		if ( FileExists(AtcExeFilePath) == false ){
			exit(0);
		}

		//�t�@�C���A�C�R���ԍ�
		AtcsFileIconIndex = pReg->ReadInteger( "AttacheCase\\Option", "AtcsFileIconIndex", 1);
		//���[�U�[�w��̃t�@�C���A�C�R���p�X
		UserRegIconFilePath = pReg->ReadString( "AttacheCase\\Option", "UserRegIconFilePath", "");

		//-----------------------------------

		opt = StrToIntDef(ParamStr(1), 0);

		if ( opt == 0 ){
			//�֘A�t���ݒ�
			RegistDataFileAssociation();
		}
		else{
			//�֘A�t������
			DeleteDataFileAssociation();
		}

	}
	//���������N���̏ꍇ�̓��b�Z�[�W�Œʒm
	else{
		//'���̃v���O�����͒P�̂ł͓��삵�܂���B'+#13+
		//'�A�^�b�V�F�P�[�X����t�@�C���̊֘A�t���ݒ�ŌĂяo�����Ƃ��̂ݎg�p����܂��B';
		MsgText = LoadResourceString(&Msgmain::_MSG_ERROR_THIS_APP_DOES_NOT_EXECUTE_ALONE);
		MessageDlg(MsgText, mtWarning   , TMsgDlgButtons() << mbOK, 0);
	}

}
__finally{

		delete pReg;

}

//Application->Terminate();
exit(0);


}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
//�f�[�^�t�@�C�����V�X�e���Ɋ֘A�t��
//---------------------------------------------------------------------------
bool __fastcall TForm1::RegistDataFileAssociation(void)
{


TRegistry *pReg;


try{

	pReg = new TRegistry();

	//�o�^���e
	String RegData = "\"" + AtcExeFilePath + "\" \"%1\"";
	String RegIconData;

	//-----------------------------------
	//���[�g�L�[�w��
	pReg->RootKey = HKEY_CLASSES_ROOT;
	pReg->Access = KEY_ALL_ACCESS;

	//-----------------------------------
	//�R���e�L�X�g���j���[�o�^

	//���J���Ă݂āA���W�X�g�����J���Ȃ��悤�Ȃ�G���[
	//�i��Win2000/XP�ȂǂŐ������[�U�[�ł���\���j
	if ( pReg->OpenKey( "AttacheCase.DataFile\\Shell", true)){

		//open�R�}���h
		//�Â��L�[������Ȃ�폜�iver.2.21�`�j
		if ( pReg->KeyExists( "open"))  pReg->DeleteKey("open");

		pReg->OpenKey("open\\command", true);
		pReg->WriteExpandString( "", RegData);
		pReg->CloseKey();

		//decode�R�}���h
		pReg->RootKey = HKEY_CLASSES_ROOT;
		pReg->Access = KEY_ALL_ACCESS;
		pReg->OpenKey( "AttacheCase.DataFile\\Shell", true);
		pReg->WriteExpandString("", "");  // Shell�������N���A�i�O�̃o�[�W�����Ŏc��ꍇ���L��j

		if ( !pReg->KeyExists( "decode")){

			pReg->OpenKey("decode", true);
			//'�A�^�b�V�F�P�[�X�t�@�C���𕜍�����'
			pReg->WriteExpandString( "", LoadResourceString(&Msgmain::_SYSTEM_CONTEXT_MENU_DECYPTION));

			if ( !pReg->KeyExists( "command")){
				pReg->OpenKey("command", true);
				pReg->WriteExpandString( "", RegData);
			}

		}
		else{

			//���W�X�g���̓o�^��������
			if (pReg->ReadString("decode\\command") != RegData ){
				pReg->OpenKey("decode\\command", true);
				pReg->WriteExpandString( "", RegData);
			}

		}


	}
	else{

		//���W�X�g�����ǂݏo���Ȃ��H
		return(false);

	}

	//-----------------------------------
	//�֘A�t���A�C�R���̐ݒ�
	if ( FileExists(UserRegIconFilePath)){  //���[�U�[�w��
		RegIconData = "\""+UserRegIconFilePath+"\"";
	}
	else{ //�����A�C�R��
		RegIconData = "\""+AtcExeFilePath+"\","+IntToStr(AtcsFileIconIndex);
	}

	if ( pReg->OpenKey("AttacheCase.DataFile\\DefaultIcon", true) == true ){
		pReg->WriteExpandString( "", RegIconData);
		pReg->CloseKey();
	}
	else{
		//���W�X�g�����ǂݏo���Ȃ��H
		return(false);
	}

	//-----------------------------------
	// .atc�g���q�̊֘A�t��

	if ( pReg->OpenKey(".atc", true)){
		pReg->WriteExpandString( "", "AttacheCase.DataFile");
		pReg->CloseKey();
	}
	else{
		return(false);	//���s
	}

	//-----------------------------------
	//�V�X�e������A�C�R���̕\���X�V
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);

}
__finally{

	delete  pReg;

}

return(true);


}//end RegistDataFileAssociation;
//---------------------------------------------------------------------------
//�f�[�^�t�@�C���̊֘A�t���ݒ�̍폜����
//---------------------------------------------------------------------------
bool __fastcall TForm1::DeleteDataFileAssociation(void)
{

TRegIniFile *Reg = new TRegIniFile("");

//�o�^���e
String RegData = "\"" + AtcExeFilePath + "\" \"%1\"";
//AnsiString RegIconData = "\""+AtcExeFilePath+"\",1";

//-----------------------------------
//���[�g�L�[�w��
Reg->RootKey = HKEY_CLASSES_ROOT;
Reg->Access = KEY_ALL_ACCESS;

//-----------------------------------
//���W�X�g���̓o�^�����邩�H

if (Reg->ReadString("AttacheCase.DataFile\\Shell\\open\\Command","","") != RegData ){

	//delete Reg;
	//return(false);

}
else{

	//���J���Ă݂āA���W�X�g�����J���Ȃ��悤�Ȃ�G���[
	//��Win2000/XP�ȂǂŐ������[�U�[�ł���\��
	if ( !Reg->OpenKey("AttacheCase.DataFile\\Shell\\open\\Command", true)){
		delete Reg;
		return(false);
	}

}

delete Reg;

//-----------------------------------
//���W�X�g���폜

TRegIniFile *DelReg = new TRegIniFile("");

//���[�g�L�[�w��
DelReg->RootKey = HKEY_CLASSES_ROOT;
DelReg->EraseSection(".atc");
DelReg->EraseSection("AttacheCase.DataFile");

delete DelReg;

//-----------------------------------
//�A�^�b�V�F�P�[�X�e�ݒ�̍폜
//���A���C���X�g�[���[�����ꂢ�ɂ��Ă����̂ł����ł͂��Ȃ��B
/*
DelReg = new TRegIniFile("Software\\Hibara");
//���W�X�g���폜
DelReg->EraseSection("AttacheCase");

delete DelReg;
*/

SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);

return(true);

}//end DeleteDataFileAssociation;
//---------------------------------------------------------------------------

