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

//�������w�肳��Ă����ꍇ�̂݋N���`
if ( ParamCount() > 0 ){

	TRegIniFile *pReg = new TRegIniFile("Software\\Hibara");

	//�A�^�b�V�F�P�[�X�{�̂̃p�X
	AtcExeFilePath = pReg->ReadString( "AttacheCase\\AppInfo", "AppPath", "");

	if ( AtcExeFilePath == "" ){
		AtcExeFilePath = ExtractFileDir(ExpandUNCFileName(Application->ExeName))+"\\AtchCase.exe";
	}

	if ( FileExists(AtcExeFilePath) == false ){
		delete pReg;
		exit(0);
	}

	//�t�@�C���A�C�R���ԍ�
	AtcsFileIconIndex = pReg->ReadInteger( "AttacheCase\\Option", "AtcsFileIconIndex", 2);
	//���[�U�[�w��̃t�@�C���A�C�R���p�X
	UserRegIconFilePath = pReg->ReadString( "AttacheCase\\Option", "UserRegIconFilePath", "");

	pReg->CloseKey();
	delete pReg;

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

TRegIniFile *Reg = new TRegIniFile("");

//�o�^���e
String RegData = "\"" + AtcExeFilePath + "\" \"%1\"";
String RegIconData;

//-----------------------------------
//���[�g�L�[�w��
Reg->RootKey = HKEY_CLASSES_ROOT;
Reg->Access = KEY_ALL_ACCESS;

//-----------------------------------
//�R���e�L�X�g���j���[�o�^

//���J���Ă݂āA���W�X�g�����J���Ȃ��悤�Ȃ�G���[
//�i��Win2000/XP�ȂǂŐ������[�U�[�ł���\���j
if ( Reg->OpenKey( "AttacheCase.DataFile\\Shell", true)){

	//open�R�}���h
	//�Â��L�[������Ȃ�폜�iver.2.21�`�j
	if ( Reg->KeyExists( "open"))  Reg->EraseSection( "open");

	Reg->OpenKey("open\\command", true);
	Reg->WriteExpandString( "", RegData);
	Reg->CloseKey();

	//decode�R�}���h
	Reg->RootKey = HKEY_CLASSES_ROOT;
	Reg->Access = KEY_ALL_ACCESS;
	Reg->OpenKey( "AttacheCase.DataFile\\Shell", true);
	Reg->WriteExpandString("", "");  // Shell�������N���A�i�O�̃o�[�W�����Ŏc��ꍇ���L��j

	if ( !Reg->KeyExists( "decode")){

		Reg->OpenKey("decode", true);
		//'�A�^�b�V�F�P�[�X�t�@�C���𕜍�����'
		Reg->WriteExpandString( "", LoadResourceString(&Msgmain::_SYSTEM_CONTEXT_MENU_DECYPTION));

		if ( !Reg->KeyExists( "command")){
			Reg->OpenKey("command", true);
			Reg->WriteExpandString( "", RegData);
		}

	}
	else{

		//���W�X�g���̓o�^��������
		if (Reg->ReadString("decode\\command","","") != RegData ){
			Reg->OpenKey("decode\\command", true);
			Reg->WriteExpandString( "", RegData);
		}

	}

	Reg->CloseKey();

}
else{

	//���W�X�g�����ǂݏo���Ȃ��H
	delete Reg;
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

if ( Reg->OpenKey("AttacheCase.DataFile\\DefaultIcon", true) == true ){
	Reg->WriteExpandString( "", RegIconData);
	Reg->CloseKey();
}
else{
	//���W�X�g�����ǂݏo���Ȃ��H
	delete Reg;
	return(false);
}

//-----------------------------------
// .atc�g���q�̊֘A�t��

if ( Reg->OpenKey(".atc", true)){
	Reg->WriteExpandString( "", "AttacheCase.DataFile");
	Reg->CloseKey();
}
else{
	delete Reg;
	return(false);	//���s
}

delete Reg;

//-----------------------------------
//�V�X�e������A�C�R���̕\���X�V
SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);


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

