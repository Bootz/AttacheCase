/*

'AttacheCase' - file encryption software for Windows.

TAttacheCaseOptionHandle Class file.

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


#include "TAttacheCaseOptionHandle.h"


//===========================================================================
//�R���X�g���N�^
//===========================================================================
__fastcall TAttacheCaseOptionHandle::TAttacheCaseOptionHandle() : TObject()
{

//

}
//===========================================================================
//�f�X�g���N�^
//===========================================================================
__fastcall TAttacheCaseOptionHandle::~TAttacheCaseOptionHandle()
{

TCustomIniFile *pOpt;

try{

	if ( FileExists(OptionPath) == true ){
		//�ʏ�Ȃ�ǂݍ��񂾐�֕ۑ�����
		pOpt = new TIniFile(OptionPath);
	}
	else{
		//�Ȃ���΃��W�X�g����
		pOpt = new TRegistryIniFile("Software\\Hibara\\AttacheCase");
	}
	//-----------------------------------
	// �t�H�[���|�W�V���������͋L������
	//-----------------------------------
	pOpt->WriteInteger( "WindowPos", "WindowWidth", FormWidth);
	pOpt->WriteInteger( "WindowPos", "WindowHeight", FormHeight);
	pOpt->WriteInteger( "WindowPos", "WindowTop", FormTop);
	pOpt->WriteInteger( "WindowPos", "WindowLeft", FormLeft);
	pOpt->WriteInteger( "WindowPos", "FormStyle", WinStyle);

}
__finally{

	delete pOpt;

}


}
//===========================================================================
//����ݒ�̓ǂݍ���
//===========================================================================
bool __fastcall TAttacheCaseOptionHandle::LoadOptionData(String IniFilePath)
{

TCustomIniFile *pOpt;
TGetAppInfoString *pAppInfoString;

try{

	if ( FileExists(IniFilePath) == true ){
		// INI�t�@�C������ǂݍ���
		OptionPath = IniFilePath;
		pOpt = new TIniFile(OptionPath);
		OptType = 1;
	}
	else{
		// ���W�X�g������ǂݍ���
		OptionPath = ATTACHE_CASE_REGISTRY_PATH;	//"Software\\Hibara\\AttacheCase"
		pOpt = new TRegistryIniFile(OptionPath);
		OptType = 0;
	}

	//-----------------------------------
	//�A�v���P�[�V�������
	//-----------------------------------
	AppPath = Application->ExeName;

	//�o�[�W�����ԍ�
	pAppInfoString = new TGetAppInfoString();
	VersionNum = StrToIntDef(StringReplace(pAppInfoString->FileVersion, ".", "", TReplaceFlags()<<rfReplaceAll), -1);

	//-----------------------------------
	// �t�H�[���|�W�V�����Ȃ�
	//-----------------------------------
	FormWidth = pOpt->ReadInteger( "WindowPos", "WindowWidth", 350);
	FormHeight = pOpt->ReadInteger( "WindowPos", "WindowHeight", 290);
	FormTop = pOpt->ReadInteger( "WindowPos", "WindowTop", Screen->Height/2-FormHeight/2);
	FormLeft = pOpt->ReadInteger( "WindowPos", "WindowLeft", Screen->Width/2-FormWidth/2);
	WinStyle = pOpt->ReadInteger( "WindowPos", "FormStyle", 0);

	//-----------------------------------
	// ��{�ݒ�
	//-----------------------------------
	//�L���������p�X���[�h
	fMyEncodePasswordKeep = pOpt->ReadBool( "MyKey", "fKeep", false);
	fMyDecodePasswordKeep = pOpt->ReadBool( "MyKey", "fKeep01", false);
	MyEncodePassword = ReadMyPasswordFromRegistry(TYPE_ENCODE_FILE);
	MyDecodePassword = ReadMyPasswordFromRegistry(TYPE_DECODE_FILE);

	//�L������Ƀ`�F�b�N�������Ă���̂Ƀp�X���[�h���󕶎��̏ꍇ��
	//��`�F�b�N�ɂ���
	if ( fMyEncodePasswordKeep == true ) {
		if (MyEncodePassword == "") {
			fMyEncodePasswordKeep = false;
		}
	}
	if ( fMyDecodePasswordKeep == true ) {
		if (MyDecodePassword == "") {
			fMyDecodePasswordKeep = false;
		}
	}

	fMemPasswordExe = pOpt->ReadBool( "Option", "fMemPasswordExe", true);        //�L���p�X���[�h�Ŋm�F�Ȃ����s����
	fOpenFolder = pOpt->ReadBool( "Option", "fOpenFolder", false);               //�t�H���_���J��
	fOpenFile = pOpt->ReadBool( "Option", "fOpenFile", false);                   //���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ��
	fEndToExit = pOpt->ReadBool( "Option", "fEndToExit", false);                 //������A�A�v�����I������
	fWindowForeground = pOpt->ReadBool( "Option", "fWindowForeground", true);    //�f�X�N�g�b�v�ōőO�ʂɃE�B���h�E��\������
	fNoHidePassword = pOpt->ReadBool( "Option", "fNoHidePassword", false);       //�u*�v�ŉB�����p�X���[�h���m�F���Ȃ�����͂���
	fSaveToExeout = pOpt->ReadBool( "Option", "fSaveToExeout", false);           //��Ɏ��Ȏ��s�`���ŏo�͂���
	fShowExeoutChkBox = pOpt->ReadBool( "Option", "fShowExeoutChkBox", true);    //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
	fAskEncDecode = pOpt->ReadBool( "Option", "fAskEncDecode", false);           //�Í�/������������₢���킹��
	fNoMultipleInstance = pOpt->ReadBool( "Option", "fNoMultipleInstance", true);//�����N�����Ȃ�

	ProcTypeWithoutAsk = -1;     //�����I�ȈÍ�/�����������i�R�}���h���C������̂݁j

	//-----------------------------------
	// �ۑ��ݒ�
	//-----------------------------------
	fSaveToSameFldr = pOpt->ReadBool( "Option", "fSaveToSameFldr", false);          //��ɓ����ꏊ�ɕۑ����邩
	SaveToSameFldrPath = pOpt->ReadString( "Option", "SaveToSameFldrPath", "");
	fDecodeToSameFldr = pOpt->ReadInteger( "Option", "fDecodeToSameFldr", false);   //��ɓ����ꏊ�փt�@�C���𕜍������邩
	DecodeToSameFldrPath = pOpt->ReadString( "Option", "DecodeToSameFldrPath", ""); //���̕ۑ��ꏊ
	fConfirmOverwirte = pOpt->ReadBool( "Option", "ConfirmOverwite", true);         //�����t�@�C���̏㏑�����m�F���邩
	fKeepTimeStamp = pOpt->ReadBool( "Option", "fKeepTimeStamp", false);            //�Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹��
	fSameTimeStamp = pOpt->ReadBool( "Option", "fSameTimeStamp", false);            //���������t�@�C���̃^�C���X�^���v�𐶐������ɂ���
	fAllFilePack = pOpt->ReadBool( "Option", "fAllFilePack", false);                //�����̃t�@�C�����Í�������ۂ͈�ɂ܂Ƃ߂�
	fFilesOneByOne = pOpt->ReadBool( "Option", "fFilesOneByOne", false);            //�t�H���_���̃t�@�C���͌ʂɈÍ���/��������
	fNoParentFldr = pOpt->ReadBool( "Option", "fNoParentFldr", false);              //��������Ƃ��ɐe�t�H���_�𐶐����Ȃ�
	fExtInAtcFileName = pOpt->ReadBool( "Option", "fExtInAtcFileName", false);      //�Í����t�@�C�����Ɋg���q���܂߂�
	fAutoName = pOpt->ReadBool( "Option", "fAutoName", false);                      //�����ňÍ����t�@�C������t������
	AutoNameFormatText = pOpt->ReadString("Option", "AutoNameFormatText", "<filename>_<date:yyyy_mm_dd><ext>");//�����ŕt������t�@�C��������

	//-----------------------------------
	// �폜�ݒ�
	//-----------------------------------
	fDelOrgFile = pOpt->ReadBool( "Option", "fDelOrgFile", false);        //���t�@�C�����폜����
	fDelEncFile = pOpt->ReadBool( "Option", "fDelEncFile", false);        //�Í����t�@�C�����폜����
	fShowDeleteChkBox = pOpt->ReadBool( "Option", "fShowDeleteChkBox", false); //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
	fCompleteDelete = pOpt->ReadInteger( "Option", "fCompleteDelFile", 1);//���S�̕��@(0:�ʏ�C1:���S�폜�C2:���ݔ��j
	DelRandNum = pOpt->ReadInteger( "Option", "DelRandNum", 0);           //�����̏������݉�
	DelZeroNum = pOpt->ReadInteger( "Option", "DelZeroNum", 1);           //�[���������݉�

	//-----------------------------------
	// ����ݒ�
	//-----------------------------------
	CompressRate = pOpt->ReadInteger( "Option", "CompressRate", 6); //���k��
	fCompareFile = pOpt->ReadInteger( "Option", "fCompareFile", 0); //�Í�������Ƀt�@�C���R���y�A���s����

	//-----------------------------------
	// �V�X�e��
	//-----------------------------------
	fAssociationFile = pOpt->ReadInteger( "Option", "fAssociationFile", 1);      //�֘A�t���ݒ�
	AtcsFileIconIndex = pOpt->ReadInteger( "Option", "AtcsFileIconIndex", 1);    //�t�@�C���A�C�R���ԍ�
	UserRegIconFilePath = pOpt->ReadString( "Option", "UserRegIconFilePath", "");//���[�U�[�w��̃t�@�C���A�C�R���p�X

	//-----------------------------------
	// ���x�ݒ�
	//-----------------------------------
	fAllowPassFile = pOpt->ReadBool( "Option", "fAllowPassFile", false);               //�p�X���[�h�t�@�C����������
	fCheckPassFile = pOpt->ReadBool( "Option", "fCheckPassFile", false);               //�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
	PassFilePath = pOpt->ReadString( "Option", "PassFilePath", "");                    //�Í����̃p�X���[�h�t�@�C���p�X
	fCheckPassFileDecrypt = pOpt->ReadBool( "Option", "fCheckPassFileDecrypt", false); //�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
	PassFilePathDecrypt = pOpt->ReadString( "Option", "PassFilePathDecrypt", "");      //�������̃p�X���[�h�t�@�C���p�X
	fNoErrMsgOnPassFile = pOpt->ReadBool( "Option", "fNoErrMsgOnPassFile", false);     //�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
	fAddCamoExt = pOpt->ReadBool( "Option", "fAddCamoExt", false);                     //�Í����t�@�C���̊g���q���U������
	CamoExt = pOpt->ReadString( "Option", "CamoExt", ".jpg");                          //���̊g���q
	MissTypeLimitsNum = pOpt->ReadInteger( "Option", "MissTypeLimitsNum", 3);          //�p�X���[�h�̃^�C�v�~�X�����񐔁iver.2.70�`�j
	fBroken = pOpt->ReadBool( "Option", "fBroken", false);                             //�^�C�v�~�X�񐔂𒴂����Ƃ��Ƀt�@�C����j�󂷂邩�ۂ��iver.2.70�`�j

	//-----------------------------------
	// ���̑��i�R�}���h���C������̂݁j
	//-----------------------------------
	fOver4GBok = false;     //4GB������e�F


}
__finally{

	delete pOpt;
	delete pAppInfoString;

}

return(true);

}
//===========================================================================
//����ݒ��KeyValue�`����TStringList�Ŏ擾����
//===========================================================================
void __fastcall TAttacheCaseOptionHandle::GetKeyValueData(TStringList *KeyValueList)
{

TCustomIniFile *pOpt;
TGetAppInfoString *pAppInfoString;

try{

	if ( FileExists(OptionPath) == true ){
		// INI�t�@�C������ǂݍ���
		pOpt = new TIniFile(OptionPath);
		OptType = 1;
	}
	else{
		// ���W�X�g������ǂݍ���
		pOpt = new TRegistryIniFile(ATTACHE_CASE_REGISTRY_PATH);
		OptType = 0;
	}

	KeyValueList->Clear();

	//-----------------------------------
	//�A�v���P�[�V�������
	//-----------------------------------
	AppPath = Application->ExeName;

	//�o�[�W�����ԍ�
	pAppInfoString = new TGetAppInfoString();
	VersionNum = StrToIntDef(StringReplace(pAppInfoString->FileVersion, ".", "", TReplaceFlags()<<rfReplaceAll), -1);

	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("AppPath", AppPath))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("VersionNum", VersionNum))));

	//-----------------------------------
	// �t�H�[���|�W�V�����Ȃ�
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("FormWidth", FormWidth))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("FormHeight", FormHeight))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("FormTop", FormTop))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("FormLeft", FormLeft))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("WinStyle", WinStyle))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("ActiveTabNum", ActiveTabNum))));

	//-----------------------------------
	// ��{�ݒ�
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fMyEncodePasswordKeep", (int)fMyEncodePasswordKeep))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fMyDecodePasswordKeep", (int)fMyDecodePasswordKeep))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("MyEncodePassword", MyEncodePassword))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("MyDecodePassword", MyDecodePassword))));

	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fMemPasswordExe", (int)fMemPasswordExe))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fOpenFolder", (int)fOpenFolder))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fOpenFile", (int)fOpenFile))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fEndToExit", (int)fEndToExit))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fWindowForeground", (int)fWindowForeground))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fNoHidePassword", (int)fNoHidePassword))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fSaveToExeout", (int)fSaveToExeout))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fShowExeoutChkBox", (int)fShowExeoutChkBox))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fAskEncDecode", (int)fAskEncDecode))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fNoMultipleInstance", (int)fNoMultipleInstance))));

	//-----------------------------------
	// �ۑ��ݒ�
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fSaveToSameFldr", (int)fSaveToSameFldr))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("SaveToSameFldrPath", SaveToSameFldrPath))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fDecodeToSameFldr", (int)fDecodeToSameFldr))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("DecodeToSameFldrPath", DecodeToSameFldrPath))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fConfirmOverwirte", (int)fConfirmOverwirte))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fKeepTimeStamp", (int)fKeepTimeStamp))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fSameTimeStamp", (int)fSameTimeStamp))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fAllFilePack", (int)fAllFilePack))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fFilesOneByOne", (int)fFilesOneByOne))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fNoParentFldr", (int)fNoParentFldr))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fExtInAtcFileName", (int)fExtInAtcFileName))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fAutoName", (int)fAutoName))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("AutoNameFormatText", AutoNameFormatText))));

	//-----------------------------------
	// �폜�ݒ�
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fDelOrgFile", (int)fDelOrgFile))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fDelEncFile", (int)fDelEncFile))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fShowDeleteChkBox", (int)fShowDeleteChkBox))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fCompleteDelete", (int)fCompleteDelete))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("DelRandNum", DelRandNum))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("DelZeroNum", DelZeroNum))));

	//-----------------------------------
	// ����ݒ�
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("CompressRate", CompressRate))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fCompareFile", (int)fCompareFile))));

	//-----------------------------------
	// �V�X�e��
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fAssociationFile", (int)fAssociationFile))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("AtcsFileIconIndex", AtcsFileIconIndex))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("UserRegIconFilePath", UserRegIconFilePath))));

	//-----------------------------------
	// ���x�ݒ�
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fAllowPassFile", (int)fAllowPassFile))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fCheckPassFile", (int)fCheckPassFile))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("PassFilePath", PassFilePath))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fCheckPassFileDecrypt", (int)fCheckPassFileDecrypt))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("PassFilePathDecrypt", PassFilePathDecrypt))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fNoErrMsgOnPassFile", (int)fNoErrMsgOnPassFile))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fAddCamoExt", (int)fAddCamoExt))));
	KeyValueList->Add(String().Format("%s=%s", ARRAYOFCONST(("CamoExt", CamoExt))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("MissTypeLimitsNum", MissTypeLimitsNum))));
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fBroken", (int)fBroken))));

	//-----------------------------------
	// ���̑��i�R�}���h���C������̂݁j
	//-----------------------------------
	KeyValueList->Add(String().Format("%s=%d", ARRAYOFCONST(("fOver4GBok", (int)fOver4GBok))));


}
__finally{

	delete pAppInfoString;
	delete pOpt;

}


}
//===========================================================================
//����ݒ��ۑ�����
//===========================================================================
bool __fastcall TAttacheCaseOptionHandle::SaveOptionData(void)
{

TCustomIniFile *pOpt;
TGetAppInfoString *pAppInfoString;

try{

	if ( OptType == 0 ) {
		pOpt = new TRegistryIniFile("Software\\Hibara\\AttacheCase");
	}
	else{
		pOpt = new TIniFile(OptionPath);
	}

	//-----------------------------------
	//�A�v���P�[�V�������
	//-----------------------------------
	//���s�t�@�C���p�X
	pOpt->WriteString( "AppInfo", "AppPath", ExpandUNCFileName(Application->ExeName));

	//�o�[�W�����ԍ�
	pAppInfoString = new TGetAppInfoString();
	VersionNum = StrToIntDef(StringReplace(pAppInfoString->FileVersion, ".", "", TReplaceFlags()<<rfReplaceAll), -1);

	//-----------------------------------
	// �t�H�[���|�W�V�����Ȃ�
	//-----------------------------------
	pOpt->WriteInteger( "WindowPos", "WindowWidth", FormWidth);
	pOpt->WriteInteger( "WindowPos", "WindowHeight", FormHeight);
	pOpt->WriteInteger( "WindowPos", "WindowTop", FormTop);
	pOpt->WriteInteger( "WindowPos", "WindowLeft", FormLeft);
	pOpt->WriteInteger( "WindowPos", "FormStyle", WinStyle);

	//-----------------------------------
	// ��{�ݒ�
	//-----------------------------------
	pOpt->WriteBool( "MyKey", "fKeep", fMyEncodePasswordKeep);   //�p�X���[�h���L�^���邩
	pOpt->WriteBool( "MyKey", "fKeep01", fMyDecodePasswordKeep);
	//�L������p�X���[�h���L�^����
	SaveMyPasswordToRegistry(MyEncodePassword, 0);	//�Í���
	SaveMyPasswordToRegistry(MyDecodePassword, 1);	//����

	pOpt->WriteInteger( "Option", "fMemPasswordExe", fMemPasswordExe);     //�L���p�X���[�h�Ŋm�F�Ȃ����s����
	pOpt->WriteInteger( "Option", "fOpenFolder", fOpenFolder);             //�t�H���_���J��
	pOpt->WriteInteger( "Option", "fOpenFile", fOpenFile);                 //���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ��
	pOpt->WriteInteger( "Option", "fEndToExit", fEndToExit);               //������A�A�^�b�V�F�P�[�X���I������
	pOpt->WriteBool( "Option", "fWindowForeground", fWindowForeground);    //�f�X�N�g�b�v�ōőO�ʂɃE�B���h�E��\������
	pOpt->WriteBool( "Option", "fNoHidePassword", fNoHidePassword);        //�u*�v�ŉB�����p�X���[�h���m�F���Ȃ�����͂���
	pOpt->WriteBool( "Option", "fSaveToExeout", fSaveToExeout);            //��Ɏ��Ȏ��s�`���ŏo�͂���
	pOpt->WriteBool( "Option", "fShowExeoutChkBox", fShowExeoutChkBox);    //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
	pOpt->WriteBool( "Option", "fAskEncDecode", fAskEncDecode);            //�Í�/������������₢���킹��
	pOpt->WriteBool( "Option", "fNoMultipleInstance", fNoMultipleInstance);//�����N�����Ȃ�

	//-----------------------------------
	// �ۑ��ݒ�
	//-----------------------------------
	pOpt->WriteInteger( "Option", "fSaveToSameFldr", fSaveToSameFldr);          //��ɓ����ꏊ�ɕۑ����邩
	pOpt->WriteString( "Option", "SaveToSameFldrPath", SaveToSameFldrPath);     //���̕ۑ��ꏊ
	pOpt->WriteInteger( "Option", "fDecodeToSameFldr", fDecodeToSameFldr);      //��ɓ����ꏊ�փt�@�C���𕜍������邩
	pOpt->WriteString( "Option", "DecodeToSameFldrPath", DecodeToSameFldrPath); //���̕ۑ��ꏊ
	pOpt->WriteInteger( "Option", "ConfirmOverwite", fConfirmOverwirte);        //�����t�@�C���̏㏑�����m�F���邩
	pOpt->WriteInteger( "Option", "fKeepTimeStamp", fKeepTimeStamp);            //�Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹��
	pOpt->WriteInteger( "Option", "fSameTimeStamp", fSameTimeStamp);            //���������t�@�C���̃^�C���X�^���v�𐶐������ɂ���
	pOpt->WriteInteger( "Option", "fAllFilePack", fAllFilePack);                //�����̃t�@�C�����Í�������ۂ͈�ɂ܂Ƃ߂�
	pOpt->WriteInteger( "Option", "fFilesOneByOne", fFilesOneByOne);            //�t�H���_���̃t�@�C���͌ʂɈÍ���/��������
	pOpt->WriteInteger( "Option", "fNoParentFldr", fNoParentFldr);              //��������Ƃ��ɐe�t�H���_�𐶐����Ȃ�
	pOpt->WriteInteger( "Option", "fExtInAtcFileName", fExtInAtcFileName);      //�Í����t�@�C�����Ɋg���q���܂߂�
	pOpt->WriteInteger( "Option", "fAutoName", fAutoName);                      //�����ňÍ����t�@�C������t������
	pOpt->WriteString( "Option", "AutoNameFormatText", AutoNameFormatText);     //�����ŕt������t�@�C��������

	//-----------------------------------
	// �폜�ݒ�
	//-----------------------------------
	pOpt->WriteInteger( "Option", "fDelOrgFile", fDelOrgFile); //���t�@�C�����폜����
	pOpt->WriteInteger( "Option", "fDelEncFile", fDelEncFile); //�Í����t�@�C�����폜����
	pOpt->WriteInteger( "Option", "fShowDeleteChkBox", fShowDeleteChkBox); //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
	pOpt->WriteInteger( "Option", "fCompleteDelFile", fCompleteDelete);//�폜�̕��@�i 0: �ʏ�폜�A1: ���S�폜�A2: ���ݔ��ցj
	pOpt->WriteInteger( "Option", "DelRandNum", DelRandNum);   //�����̏������݉�
	pOpt->WriteInteger( "Option", "DelZeroNum", DelZeroNum);   //�[���������݉�

	//-----------------------------------
	// ����ݒ�
	//-----------------------------------
	pOpt->WriteInteger( "Option", "CompressRate", CompressRate); //���k��
	pOpt->WriteInteger( "Option", "fCompareFile", fCompareFile); //�Í�������Ƀt�@�C���R���y�A���s����

	//-----------------------------------
	// �V�X�e��
	//-----------------------------------
	pOpt->WriteInteger( "Option", "fAssociationFile", fAssociationFile);      //�֘A�t���ݒ�
	pOpt->WriteInteger( "Option", "AtcsFileIconIndex", AtcsFileIconIndex);    //�t�@�C���A�C�R���ԍ�
	pOpt->WriteString( "Option", "UserRegIconFilePath", UserRegIconFilePath); //���[�U�[�w��̃t�@�C���A�C�R���p�X

	//-----------------------------------
	// ���x�ݒ�
	//-----------------------------------
	pOpt->WriteBool( "Option", "fAllowPassFile", fAllowPassFile);               //�p�X���[�h�t�@�C����������
	pOpt->WriteBool( "Option", "fCheckPassFile", fCheckPassFile);               //�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
	pOpt->WriteString( "Option", "PassFilePath", PassFilePath);                 //�Í����̃p�X���[�h�t�@�C���p�X
	pOpt->WriteBool( "Option", "fCheckPassFileDecrypt", fCheckPassFileDecrypt); //�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
	pOpt->WriteString( "Option", "PassFilePathDecrypt", PassFilePathDecrypt);   //�������̃p�X���[�h�t�@�C���p�X
	pOpt->WriteBool( "Option", "fNoErrMsgOnPassFile", fNoErrMsgOnPassFile);     //�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
	pOpt->WriteBool( "Option", "fAddCamoExt", fAddCamoExt);                     //�Í����t�@�C���̊g���q���U������
	pOpt->WriteString( "Option", "CamoExt", CamoExt);                           //���̊g���q
	pOpt->WriteInteger( "Option", "MissTypeLimitsNum", MissTypeLimitsNum);      //�p�X���[�h�̃^�C�v�~�X�����񐔁iver.2.70�`�j
	pOpt->WriteBool( "Option", "fBroken", fBroken);                             //�^�C�v�~�X�񐔂𒴂����Ƃ��Ƀt�@�C����j�󂷂邩�ۂ��iver.2.70�`�j

}
__finally{

	delete pAppInfoString;
	delete pOpt;

}

return(true);

}
//===========================================================================
//�R�}���h���C���I�v�V��������̐ݒ�ǂݍ���
//===========================================================================
bool __fastcall TAttacheCaseOptionHandle::
	LoadOptionDataFromParamString(TStringList *FileList)
{

int i, c, L;
String strvalue = "";
int intvalue = 0;
String FilePath, FileName;
fArg = false; //�����͂Ȃ�

FileList->Clear();  //�t�@�C�����X�g�N���A

String CmdStr;

//-----------------------------------

//�������z���o��
for ( i = 1; i < ParamCount()+1 ; i++){

	//����
	if ( ParamStr(i).SubString(1,1) == "/" ){

		fArg = true;//���s���������i�O���[�o���j

		CmdStr = ParamStr(i).LowerCase();
		CmdStr = CmdStr.SubString(2, ParamStr(i).Pos("=")-2);

		// "="���𔲂��o��
		L = ParamStr(i).Pos("=");
		if ( L > 0 ){
			strvalue = ParamStr(i).SubString(L+1,ParamStr(i).Length()-L);
		}
		else{
			strvalue = "";
		}

		//��{�ݒ�-----------------------------------
		if (CmdStr == "p"){
			//�p�X���[�h
			MyPassword = strvalue;
			fArgPassword = true;  //���s�����Ƀp�X���[�h
		}
		else if (CmdStr == "mempexe"){
			//�L���p�X���[�h�Ŋm�F�Ȃ����s����
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fMemPasswordExe = true;
			}
			else{
				fMemPasswordExe = false;
			}
		}
		else if (CmdStr == "opd"){
			//�t�H���_�̏ꍇ�ɕ�����ɊJ����
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fOpenFolder = true;
			}
			else{
				fOpenFolder = false;
			}
		}
		else if (CmdStr == "opf"){
			//���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ��
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fOpenFile = true;
			}
			else{
				fOpenFile = false;
			}
		}
		else if (CmdStr == "exit"){
			//������ɏI�����邩
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fEndToExit = true;
			}
			else{
				fEndToExit = false;
			}
		}
		else if (CmdStr == "front"){
			//�f�X�N�g�b�v�ōőO�ʂɃE�B���h�E��\������
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fWindowForeground = true;
			}
			else{
				fWindowForeground = false;
			}
		}
		else if (CmdStr == "nohide"){
			//�u*�v�ŉB�����p�X���[�h���m�F���Ȃ�����͂���
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fNoHidePassword = true;//�����͋t
			}
			else{
				fNoHidePassword = false;
			}
		}
		else if (CmdStr == "exeout"){
			//��Ɏ��Ȏ��s�`���ŏo�͂���
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fSaveToExeout = true;
			}
			else{
				fSaveToExeout = false;
			}
		}
		else if (CmdStr == "chkexeout"){
			//���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fShowExeoutChkBox = true;
			}
			else{
				fShowExeoutChkBox = false;
			}
		}
		else if (CmdStr == "askende"){
			//�Í�/������������₢���킹��
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fAskEncDecode = true;
			}
			else{
				fAskEncDecode = false;
			}
		}
		else if (CmdStr == "en"){
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				ProcTypeWithoutAsk = 0; //�����I�ȈÍ�����
			}
		}
		else if (CmdStr == "de" ){
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				ProcTypeWithoutAsk = 1; //�����I�ȕ�������
			}
		}
		else if (CmdStr == "nomulti" ){
			//�����N�����Ȃ�
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fNoMultipleInstance = true;
			}
			else{
				fNoMultipleInstance = false;
			}
		}
		//�ۑ��ݒ�-----------------------------------
		else if (CmdStr == "saveto" ){
			//��ɓ����ꏊ�ֈÍ����t�@�C����ۑ�����
			fSaveToSameFldr = true;
			SaveToSameFldrPath = GetLongFilePath(ExpandUNCFileName(strvalue));
		}
		else if (CmdStr == "dsaveto"){
			//��ɓ����ꏊ�փt�@�C���𕜍�������
			fDecodeToSameFldr = true;
			DecodeToSameFldrPath = GetLongFilePath(ExpandUNCFileName(strvalue));
		}
		else if (CmdStr == "ow"){
			//�����t�@�C���̏㏑�����m�F���邩�i�m�F���ŏ㏑�����邩�H�j
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fConfirmOverwirte = false;//�����͋t
			}
			else{
				fConfirmOverwirte = true;
			}
		}
		else if (CmdStr == "orgdt"){
			//�Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹��
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fKeepTimeStamp = true;
			}
			else{
				fKeepTimeStamp = false;
			}
		}
		else if (CmdStr == "now"){
			//���������t�@�C���̃^�C���X�^���v�𐶐������ɂ���
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fSameTimeStamp = true;
			}
			else{
				fSameTimeStamp = false;
			}
		}
		else if (CmdStr == "allpack"){
			//�����̃t�@�C�����Í�������ۂ͈�ɂ܂Ƃ߂�
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fAllFilePack = true;
			}
			else{
				fAllFilePack = false;
			}
		}
		else if (CmdStr == "oneby"){
			//�t�H���_���̃t�@�C���͌ʂɈÍ���/��������
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fFilesOneByOne = true;
			}
			else{
				fFilesOneByOne = false;
			}
		}
		else if (CmdStr == "nopfldr"){
			//��������Ƃ��ɐe�t�H���_�𐶐����Ȃ�
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fNoParentFldr = true;
			}
			else{
				fNoParentFldr = false;
			}
		}
		else if (CmdStr == "withext"){
			//�Í����t�@�C�����Ɋg���q���܂߂�
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fExtInAtcFileName = true;
			}
			else{
				fExtInAtcFileName = false;
			}
		}
		else if (CmdStr == "autoname"){
			//�����ňÍ����t�@�C������t������
			FileName = ExtractFileName(InterpretFormatTextToFilePath("sample.atc", strvalue)); //�����ɉ��߂��Ă݂�
			if ( strvalue  != "" && ChkFileNameChr(FileName) == false){  //Windows�̋֎~�����H
				fAutoName = true;
				AutoNameFormatText = strvalue;
			}
			else{
				fAutoName = false;
			}
		}
		//�폜�ݒ�-----------------------------------
		else if (CmdStr == "del"){
			//���t�@�C���̊��S�폜���s����
			//(0:�폜���Ȃ�, 1:�ʏ�C2:���S�폜 3:���ݔ��j
			intvalue = StrToIntDef(strvalue.Trim(),-1);
			if ( 0 < intvalue && intvalue < 4 ){
				fDelOrgFile = true;
				fCompleteDelete = intvalue-1;
			}
			else{
				fDelOrgFile = false;
			}
		}
		else if (CmdStr == "delenc"){
			//�Í����t�@�C���̊��S�폜���s����
			//(0:�폜���Ȃ�, 1:�ʏ�C2:���ݔ��C3:���S�폜�j
			intvalue = StrToIntDef(strvalue.Trim(),-1);
			if ( 0 < intvalue && intvalue < 4 ){
				fDelEncFile = true;
				fCompleteDelete = intvalue-1;
			}
			else{
				fDelEncFile = false;
			}
		}
		else if (CmdStr == "chkdel"){
			//���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fShowDeleteChkBox = true;
			}
			else{
				fShowDeleteChkBox = false;
			}
		}
		else if (CmdStr == "delrand"){
			//���������񏑂����ݏ������邩
			intvalue = StrToIntDef(strvalue.Trim(),-1);
			if ( intvalue > 0 ){ //�}�C�i�X�l�͖���
				if ( intvalue > 99 ) intvalue = 99;
				DelRandNum = intvalue;
			}
		}
		else if (CmdStr == "delnull"){
			//NULL�����񏑂����ݏ������邩
			intvalue = StrToIntDef(strvalue.Trim(),-1);
			if ( intvalue > 0 ){ //�}�C�i�X�l�͖���
				if ( intvalue > 99 ) intvalue = 99;
				DelZeroNum = intvalue;
				i++;
			}
		}
		//����ݒ�-----------------------------------
		else if (CmdStr == "comprate"){
			//���k��
			intvalue = StrToIntDef(strvalue.Trim(),-1);
			if ( -1 < intvalue && intvalue < 10 ){
				CompressRate = intvalue;
			}
			else{
				CompressRate = 0; //�����k
			}
		}
		else if (CmdStr == "cmp"){
			//�Í���������Ƀf�[�^�̃R���y�A���s��
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fCompareFile = true;
			}
			else{
				fCompareFile = false;
			}
		}
		//���x�ݒ�-----------------------------------
		else if (CmdStr == "pf"){
			//�p�X���[�h�Ƀt�@�C���̎w���������
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fAllowPassFile = true;
			}
			else{
				fAllowPassFile = false;
			}
		}
		else if (CmdStr == "pfile"){
			//�p�X���[�h�t�@�C���p�X
			if ( strvalue != "" ){
				fAllowPassFile = true;
				fCheckPassFile = true;
				PassFilePath = GetLongFilePath(ExpandUNCFileName(strvalue)); //�����O�p�X�ɕϊ�
			}
			else{
				fCheckPassFile = false;
				if ( fCheckPassFileDecrypt == false )
					fAllowPassFile = false;
			}
		}
		else if (CmdStr == "dpfile"){
			//�������̃p�X���[�h�t�@�C���p�X
			if ( strvalue != "" ){
				fAllowPassFile = true;
				fCheckPassFileDecrypt = true;
				PassFilePathDecrypt = GetLongFilePath(ExpandUNCFileName(strvalue)); //�����O�p�X�ɕϊ�
			}
			else{
				fCheckPassFileDecrypt = false;
				if ( fCheckPassFile == false )
					fAllowPassFile = false;
			}
		}
		else if (CmdStr == "nomsgp"){
			//�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fNoErrMsgOnPassFile = true;
			}
			else{
				fNoErrMsgOnPassFile = false;
			}
		}
		else if (CmdStr == "camoext"){
			//�Í����t�@�C���̊g���q���U������
			if ( ChkFileNameChr(strvalue) == true ){ //�֎~�������g���Ă���
				fAddCamoExt = false;
				CamoExt = "";
			}
			else if ( strvalue.LowerCase() == "null" ){ //OFF
				fAddCamoExt = false;
			}
			else{
				fAddCamoExt = true;
				CamoExt = strvalue;
			}
		}
		//���̑��i�R�}���h���C������̂݁j-------------
		else if (CmdStr == "4gbok"){
			//4GB������e�F
			if ( StrToIntDef(strvalue.Trim(), -1) == 1 ){
				fOver4GBok = true;
			}
			else{
				fOver4GBok = false;
			}
		}
		//���̑��i�R�}���h���C������̂݁j-------------
		else if (CmdStr == "list"){
			//�w��̃t�@�C�����X�g��ǂݍ���
			if ( strvalue != "" ){
				String ListFilePath = GetLongFilePath(ExpandUNCFileName(strvalue)); //�����O�p�X�ɕϊ�
				if ( FileExists(ListFilePath) == true ){
					TStringList *ListFileList = new TStringList;
					ListFileList->LoadFromFile(ListFilePath);
					//�P�s�P�t�@�C���p�X�Ƃ��Ď��o���ăt�@�C�����X�g�֊i�[
					for ( c = 0; c < ListFileList->Count; c++ ){
						if ( ListFileList->Strings[c] != "" ){
							FileList->Add(GetLongFilePath(ExpandUNCFileName(ListFileList->Strings[c])));
						}
					}
					delete ListFileList;
				}
			}
		}
	}
	//�t�@�C���p�X
	else{
		String temp = ExpandUNCFileName(ParamStr(i));
		FileList->Add(GetLongFilePath(ExpandUNCFileName(ParamStr(i))));
	}

}//loop;


//w_char filepath[];
//size = GetFileTitle("�V����~1.txt",NULL,0);

if (ParamCount() > 0) {
	OptType = 2;
}

return(true);

}
//===========================================================================
// �����O�t�@�C�������擾����
//===========================================================================
String __fastcall TAttacheCaseOptionHandle::GetLongFilePath(String FilePath)
{

String FileName;
TSearchRec sr;

while(FindFirst(FilePath, faAnyFile, sr) == 0){
	if (sr.Name != "." && sr.Name != "..") {
		FileName = sr.FindData.cFileName;
		FilePath = IncludeTrailingPathDelimiter(ExtractFileDir(FilePath)) + FileName;
		return(FilePath);
	}
}

//�G���[
return("");

}
//===========================================================================
//�L���p�X���[�h�����W�X�g���܂���INI�t�@�C������ǂݏo��
//===========================================================================
AnsiString __fastcall TAttacheCaseOptionHandle::ReadMyPasswordFromRegistry(int Type)
{

int i;

//�擾�����p�X���[�h�����������`�F�b�N���邽�߂̕ϐ�
AnsiString TokenString;
AnsiString ResultString;
AnsiString Password;

char buffer[BUF_PASSWORD_SIZE];
char newbuffer[BUF_PASSWORD_SIZE];

TCustomIniFile *pOpt;
TMemoryStream *ms = new TMemoryStream();
CBlowFish *bf = new CBlowFish;

try{

	if ( FileExists(OptionPath) == true ){
		pOpt = new TIniFile(OptionPath);
	}
	else{
		//�Ȃ���΃��W�X�g��
		pOpt = new TRegistryIniFile(ATTACHE_CASE_REGISTRY_PATH);  //"Software\\Hibara\\AttacheCase"
	}

	//-----------------------------------
	//�Œ�p�X���[�h�̐���
	AnsiString MyKeyPass;

	//�R���s���[�^�����擾
	char UserName[255];
	DWORD  BufferLen = sizeof(UserName)-1;
	GetComputerName(UserName, &BufferLen);

	//�u�h���C�u�̃{�����[�����x��ID + �R���s���[�^���v���p�X���[�h�ɐݒ�
	MyKeyPass = (AnsiString)GetVolumeLabelIDNumber() + "_" + (AnsiString)UserName;
	// ex).  818980454_HIBARA

	//�o�b�t�@�̏�����
	for ( i = 0; i < BUF_PASSWORD_SIZE; i++ ){
		buffer[i] = NULL;
		newbuffer[i] = NULL;
	}

	//�Í����p�X���[�h
	if ( Type == TYPE_ENCODE_FILE ){
		pOpt->ReadBinaryStream("MyKey", "Passcode", ms);
	}
	//�����p�X���[�h
	else if ( Type == TYPE_DECODE_FILE ){
		pOpt->ReadBinaryStream( "MyKey", "Passcode01", ms);
	}

	ms->Position = 0;
	ms->Write(buffer, BUF_PASSWORD_SIZE);


	//-----------------------------------
	//
	//����
	//
	//������ver.1�̎d�l�����������Ă���Blowfish�ňÍ�������Ă��܂��B
	//

	bf->Initialize( MyKeyPass.c_str(), MyKeyPass.Length() );   //������
	bf->Decode( buffer, newbuffer, BUF_PASSWORD_SIZE);         //����

	//�擾�����p�X���[�h�����������`�F�b�N
	ResultString = (AnsiString)newbuffer;

	//�g�[�N���𔲂��o��
	if ( ResultString.Length() > 4 ){  //�p�X�R�[�h���I�������o���Ȃ������Ƃ��̃G���[�h�~

		TokenString = ResultString.SubString( ResultString.Length()-3, 4 );

		if ( TokenString == "_atc" ){
			Password = ResultString.SubString( 1, ResultString.Length()-4);
		}
		else{
			//�ǂݏo���Ȃ��Ƃ��̓L�[���폜���Ă���
			SaveMyPasswordToRegistry("", Type);
		}

	}
	else{

		//�ǂݏo���Ȃ��Ƃ��̓L�[���폜���Ă���
		SaveMyPasswordToRegistry("", Type);

	}

}
__finally	 {
	delete bf;
	delete ms;
	delete pOpt;

}

//�f�o�b�O
//ShowMessage(Password);

//�ۑ��̃p�X���[�h��Ԃ�
return(Password);


}//end GetMyKeyCode;
//===========================================================================
//�L���p�X���[�h�����W�X�g���܂���INI�t�@�C���ɕۑ�����
//===========================================================================
bool __fastcall TAttacheCaseOptionHandle::
	SaveMyPasswordToRegistry(String Password, int Type)
{

// Type:
// #define TYPE_ENCODE_FILE 0 //�Í���
// #define TYPE_DECODE_FILE 1 //������

//�w�b�_�� 256 + 8�i�p�X�{�g�[�N���j�����`
//#define BUF_PASSWORD_SIZE 264

int i;
char buffer[BUF_PASSWORD_SIZE];
char newbuffer[BUF_PASSWORD_SIZE];

for (i = 0; i < BUF_PASSWORD_SIZE; i++) {
	buffer[i] = 0;
	newbuffer[i] = 0;
}

TCustomIniFile *pOpt;
CBlowFish *bf = new CBlowFish;
TMemoryStream *ms = new TMemoryStream();

try{

	if ( FileExists(OptionPath) == true ){
		//�ʏ�Ȃ�ǂݍ��񂾐�֕ۑ�����
		pOpt = new TIniFile(OptionPath);
	}
	else{
		//�Ȃ���΃��W�X�g����
		pOpt = new TRegistryIniFile("Software\\Hibara\\AttacheCase");
	}

	//�p�X�R�[�h���N���A����
	if ( Password == "" ){

		if ( Type == TYPE_ENCODE_FILE){
			pOpt->DeleteKey( "MyKey", "Passcode");
		}
		else if ( Type == TYPE_DECODE_FILE){
			pOpt->DeleteKey( "MyKey", "Passcode01");
		}
		else{
			return(false);
		}

		return(true);

	}

	//��������Ƃ���Blowfish�p�X���[�h������MAX�ɐ؂�
	if ( Password.Length() > 32 ){
		Password.SetLength(32);
	}

	//-----------------------------------
	//�p�X���[�h�g�[�N���ƘA��
	String PassToken = "_atc";
	Password = Password + PassToken;

	//-----------------------------------
	//�Œ�p�X���[�h�̐���
	AnsiString MyKeyPass;

	//�ۑ������̃R���s���[�^�����擾
	char UserName[255];
	DWORD  BufferLen = sizeof(UserName)-1;
	GetComputerName(UserName, &BufferLen);

	//�u�h���C�u�̃{�����[�����x��ID + �R���s���[�^���v���p�X���[�h�ɐݒ�
	MyKeyPass = (AnsiString)GetVolumeLabelIDNumber() + "_" + (AnsiString)UserName;
	// ex).  818980454_HIBARA

	//-----------------------------------
	//
	//�Í���
	//
	//������ver.1�̎d�l�����������Ă���Blowfish�ňÍ�������Ă��܂��B
	//

	//�o�b�t�@�̏�����
	for ( i = 0; i < BUF_PASSWORD_SIZE; i++ ){
		buffer[i] = NULL;
		newbuffer[i] = NULL;
	}

	bf->Initialize( MyKeyPass.c_str(), MyKeyPass.Length() );   //������
	StrCopy( buffer, AnsiString(Password).c_str());  	 //�p�X���[�h���o�b�t�@��
	bf->Encode( buffer, newbuffer, BUF_PASSWORD_SIZE); //�Í���

	if ( Type == TYPE_ENCODE_FILE){
		ms->Write(newbuffer, BUF_PASSWORD_SIZE);
		ms->Position = 0;
		pOpt->WriteBinaryStream( "MyKey", "Passcode", ms);
	}
	else if ( Type == TYPE_DECODE_FILE){
		ms->Write(newbuffer, BUF_PASSWORD_SIZE);
		ms->Position = 0;
		pOpt->WriteBinaryStream( "MyKey", "Passcode01", ms);
	}
	else{
		return(false);
	}

}
__finally{

	delete bf;
	delete ms;
	delete pOpt;

}

return(true);

}
//===========================================================================
// �n�[�h�f�B�X�N�̃{�����[�����x��ID���擾����
//===========================================================================
String __fastcall TAttacheCaseOptionHandle::GetVolumeLabelIDNumber(void)
{

//�A�v���̂���h���C�u��
String DriveName = ExtractFileDrive(Application->ExeName);
DriveName = IncludeTrailingPathDelimiter(DriveName);

const wchar_t *pszDrv = DriveName.c_str();
wchar_t buf[MAX_PATH * 6];
wchar_t szVolName[MAX_PATH];
wchar_t szFileSystem[16];
DWORD dwVolId, dwMaxCmpLen, dwFSFlags;

GetVolumeInformationW(
		pszDrv,        // �h���C�u
		szVolName,     // �{�����[�����x��
		MAX_PATH,      // �{�����[�����x���̃o�b�t�@��(�K��)
		&dwVolId,      // �{�����[��ID
		&dwMaxCmpLen,  // �ő�R���|�[�l���g��
		&dwFSFlags,    // �t�@�C���V�X�e������
		szFileSystem,  // �t�@�C���V�X�e����
		16);           // �t�@�C���V�X�e�����̃o�b�t�@��(�K��)

return(String(dwVolId));

}//end GetVolumeLabelIDNumber;
//======================================================================
// Windows�������Ȃ��t�@�C����������̌����֐�
//======================================================================
bool __fastcall TAttacheCaseOptionHandle::ChkFileNameChr(String ChkText) {

	// ChkText :�`�F�b�N����e�L�X�g
	// �Ԃ�l  :�֎~���������������ꍇ�́ATrue��Ԃ�

	int i, L;
	String ChkOneWord;                   // �`�F�b�N����֎~����
	String DontUseText = "\\/:,*?\"<>|"; // �֎~�����񃊃X�g

	//�֎~���镶���񐔂��擾
	L = DontUseText.Length();

	for (i = 1; i < L + 1; i++) {
		// �`�F�b�N���镶�����֎~�����񂩂甲���o��
		ChkOneWord = DontUseText[i];
		if (ChkText.Pos(ChkOneWord) > 0) {
			// �֎~��������������
			return(true);
		}
	}

	return(false);

}// end ChkFileNameChr;
//===========================================================================
//�J�X�^�}�C�Y���ꂽ����������߂��ăt�@�C������u��������
//===========================================================================
String __fastcall TAttacheCaseOptionHandle::
	InterpretFormatText(String FileName, String InputText, int Num)
{

int i;
bool fScript = false;

int RandNum;      //�����_��������
int KetaNum;     	//�A�Ԍ���

String DateText;

int HeadNameNum, EndNameNum;

String strNumber = "";

String OneChar;
String FormatText;
String ReturnText;

String BaseFileName = ChangeFileExt(FileName, "");  //�g���q�����̃t�@�C����
String FileExt = ExtractFileExt(FileName);          //�g���q

ReturnText = "";

for ( i = 1; i < InputText.Length()+1; i++ ){

	OneChar = InputText.SubString(i,1);

	if ( OneChar == "<" ){
		fScript = true;
		FormatText = FormatText + OneChar;
	}
	else if ( OneChar == ">" ){

		FormatText = FormatText + OneChar;

		//-----------------------------------
		//�t�@�C����
		//-----------------------------------
		if ( FormatText.LowerCase() == "<filename>"){
			ReturnText = ReturnText + BaseFileName;
		}
		//-----------------------------------
		//�g���q
		//-----------------------------------
		else if ( FormatText.LowerCase() == "<ext>"){
			ReturnText = ReturnText + FileExt;
		}
		//-----------------------------------
		//�t�@�C�����̐擪
		//-----------------------------------
		else if ( FormatText.SubString(1,7).LowerCase() == "<fhead:" ){
			//�擪�t�@�C������������
			HeadNameNum = StrToIntDef(FormatText.SubString(8,FormatText.Length()-8), -1);
			if ( HeadNameNum > -1 ){
				ReturnText = ReturnText + BaseFileName.SubString(0, HeadNameNum);
			}
		}
		//-----------------------------------
		//�t�@�C�����̖���
		//-----------------------------------
		else if ( FormatText.SubString(1,6).LowerCase() == "<fend:" ){
			//�����t�@�C������������
			EndNameNum = StrToIntDef(FormatText.SubString(7,FormatText.Length()-7), -1);
			if ( EndNameNum > -1 ){
				ReturnText = ReturnText +
				BaseFileName.SubString(BaseFileName.Length()-EndNameNum+1, BaseFileName.Length());
			}
		}
		//-----------------------------------
		//�����_��������
		//-----------------------------------
		else if ( FormatText.SubString(1,8).LowerCase() == "<random:" ){
			//�����_��������
			RandNum = StrToIntDef(FormatText.SubString(9,FormatText.Length()-9), -1);
			if ( RandNum > -1 ){
				//�����_����������
				ReturnText = ReturnText + MakeRandomFileName(RandNum, true, true);
			}
		}
		//-----------------------------------
		//�i���o�����O
		//-----------------------------------
		else if ( FormatText.SubString(1,8).LowerCase() == "<number:" ){
			//�A�Ԍ���
			KetaNum = StrToIntDef(FormatText.SubString(9,FormatText.Length()-9), -1);
			if ( KetaNum > -1 ){
				strNumber = IntToStr(Num);
				//�������킹
				while( strNumber.Length() < KetaNum ){
					strNumber = "0" + strNumber;
				}
				ReturnText = ReturnText + strNumber;
			}
		}
		//-----------------------------------
		//���t�Ƃ��ĉ���
		//-----------------------------------
		else if ( FormatText.SubString(1,6).LowerCase() == "<date:" ){
			//���t�̏����w�肾�������o���i��������>�͏����j
			DateText = FormatText.SubString(7,FormatText.Length()-7);
			if ( DateText != "" ){
				ReturnText = ReturnText + Now().FormatString(DateText);
			}
		}//end if;

		//-----------------------------------

		FormatText = "";	//�N���A

		fScript = false;

	}
	//-----------------------------------
	//�ʏ핶����
	//-----------------------------------
	else{
		if ( fScript == true ){
			FormatText = FormatText + OneChar;
		}
		else{
			ReturnText = ReturnText + OneChar;
		}

	}

}//end for ( i = 1; i < InputText.Length()+1; i++ );

//���ʂ��J�����܂�
if ( fScript == true ){
	ReturnText = ReturnText + FormatText;
}

return(ReturnText);


}//end InterpretFormatText;
//===========================================================================
//���ۂɃJ�X�^�}�C�Y����������߂��ďd���̂Ȃ�(�A�Ԃ�)�t�@�C���p�X��Ԃ�
//===========================================================================
String __fastcall TAttacheCaseOptionHandle::
	InterpretFormatTextToFilePath(String FilePath, String InputText)
{

int c = 0;

String ReturnText = "";
String DirPath = ExtractFileDir(FilePath);          //�t�H���_��
String FileName = ExtractFileName(FilePath);        //�t�@�C����

do{
	FileName = InterpretFormatText(FileName, InputText, c); //����
	ReturnText = IncludeTrailingPathDelimiter(DirPath) + FileName;
	c++;
}while(FileExists(ReturnText));

return(ReturnText);

}
//===========================================================================
//�w��̃����_��������𐶐�
//===========================================================================
String __fastcall TAttacheCaseOptionHandle::
	MakeRandomFileName(int MojiNum, bool fNum, bool fKigo)
{

int i;
int RandNum;
String OneChar;
String ReturnText;

String FileNameCharList;
String CharAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
String CharNumber = "0123456789";
String CharKigo = "=-+!_#$%&()[]{}~^`'@";

//�A���t�@�x�b�g�̓f�t�H���g
FileNameCharList = CharAlphabet;

//�������܂߂�
if ( fNum == true )
	FileNameCharList = FileNameCharList + CharNumber;

//�L�����܂߂�
if ( fKigo == true )
	FileNameCharList = FileNameCharList + CharKigo;

//�w��̕������������_��������𐶐�
for ( i = 0; i < MojiNum; i++ ){

	RandNum = RandomRange( 1 ,FileNameCharList.Length());
	OneChar = FileNameCharList.SubString( RandNum, 1);
	ReturnText = ReturnText + OneChar;

}//loop;

return(ReturnText);

}//end MakeRandomFileName;
//===========================================================================
// �t�@�C������SHA-1�n�b�V���l���擾����
//===========================================================================
bool __fastcall TAttacheCaseOptionHandle::GetSHA1HashFromFile(
	String FilePath,              // �p�X���[�h�t�@�C���p�X
	AnsiString &HashDataVer2,     // ver.2.*  �`�FSHA-1�n�b�V���l�i20byte + 12byte�j
	AnsiString &HashDataVer1 )    // ver.1.*  �`�F�w�b�_�f�[�^�i�擪������32�����j
{

/*
 * �p�X���[�h�t�@�C������SHA-1���v�Z���āA�p�X���[�h�̒l�ɃZ�b�g���Ă��܂����A
 * SHA-1�̌v�Z���ʂ�20�o�C�g�i160�r�b�g�j�ŏo�͂����d�l�̂��߁ARijndael��
 * �p�X���[�h�T�C�Y�i32�o�C�g�j�ƍ����܂���B
 * ���̂��߁A�����ł͋����Ƀt�@�C������C�ӂ�12�o�C�g��ǉ�����32�o�C�g�Ƃ��Ă��܂��B
 *
 * ���N(2012�N)���ɂ͎�����́uSHA-3�v���I�肳��܂��̂ŁA����ɍ��킹�āA
 * 32�o�C�g�l���Z�b�g����d�l�Ƀo�[�W�����A�b�v���悤�ƍl���Ă��܂��B
 *
 * �Ȃ��ASHA-3�̍���󋵂ɂ��܂��ẮA���L���Q�Ƃ��������B
 *
 * http://csrc.nist.gov/groups/ST/hash/sha-3/index.html
 *
*/

int i;

int fh;
int bytes, rest;
char buffer[255];	                               //�ǂݍ��݃o�b�t�@
char sha1_hash_data_mixed_padding[BUF_HASH_DATA];// 32byte

for (i = 0; i < BUF_HASH_DATA; i++) {
	sha1_hash_data_mixed_padding[i] = NULL;
}

if ( !FileExists(FilePath) ) return(false);

try{

	if ( (fh = FileOpen(FilePath, fmShareDenyNone)) == -1 ){
		//�p�X���[�h�t�@�C�����J���Ȃ��H
		return(false);
	}

	//�w�b�_�擪��255byte��ǂށiver.1.* �`�j
	FileRead(fh, buffer, 255);
	HashDataVer1 = (AnsiString)buffer;

	//SHA-1�n�b�V���̌v�Z
	FileSeek(fh, 0, 0);
	SHA1Context sha;
	unsigned char Message_Digest[20];
	ZeroMemory(Message_Digest, 20);

	//�������i���Z�b�g�j
	if ( SHA1Reset(&sha)){
		return(false);
	}

	//�t�@�C����ǂݏo����SHA-1�֓��͂��Ă���
	while ((bytes = FileRead (fh, buffer, 255)) != 0){
		rest = bytes;
		if ( SHA1Input(&sha, (const unsigned char *)buffer, bytes) ){
			return(false);
		}
	}

	if ( FileSeek(fh, -rest, 2) > 0 ){
		FileRead(fh, buffer, 255);
	}
	else{
		FileSeek(fh, 0, 0);
		FileRead(fh, buffer, 255);
	}

	//�o��
	if(SHA1Result(&sha, Message_Digest)){
		return(false);
	}
	for (i = 0; i < BUF_SHA1_SIZE; i++){   // 20byte
		sha1_hash_data_mixed_padding[i] = Message_Digest[i];
	}

	//�c���12byte���U
	for (i = 0; i < 12; i++) {             // 12byte
		 sha1_hash_data_mixed_padding[BUF_SHA1_SIZE+i] = buffer[i];
	}

	HashDataVer2 = "";
	for (i = 0; i < BUF_HASH_DATA; i++){   // 32byte
		//�K�؂ɃL���X�g�����悤��1byte�����
		HashDataVer2 += (AnsiString)sha1_hash_data_mixed_padding[i];
	}
	HashDataVer2.SetLength(32);

}
__finally{

	FileClose(fh);

}
return(true);


}
//===========================================================================
//�u����v�t�H���_�[�܂ł̃A�v���P�[�V�����t���p�X�𐶐�����
//===========================================================================
String __fastcall TAttacheCaseOptionHandle::CreateSendToFolderAppFullPath(void)
{

//'�A�^�b�V�F�P�[�X'
String ApplicationName = LoadResourceString(&Msgoption::_APPLICATION_NAME);
String SendToFolderPath;
String ShortCutFilePath;
wchar_t path[MAX_PATH];

LPITEMIDLIST PidList;

SHGetSpecialFolderLocation(Application->Handle, CSIDL_SENDTO, &PidList );
SHGetPathFromIDListW( PidList, path );

SendToFolderPath = path;
ShortCutFilePath = IncludeTrailingPathDelimiter(SendToFolderPath) + ApplicationName + ".lnk";

return(ShortCutFilePath);


}
//===========================================================================
// �V���[�g�J�b�g�t�@�C�����쐬����
//===========================================================================
bool __fastcall TAttacheCaseOptionHandle::CreateShortCutFile
( String LinkFilePath, String TargetFilePath, String Arguments, String WorkDir, int ShowCmd )
{

// LinkFile   : �V���[�g�J�b�g�t�@�C���̖��O(*.lnk)
// TargetFile : �����N��
// Arguments  : �R�}���h���C������
// WorkDir    : ��ƃf�B���N�g��
// ShowCmd    : ���s���̑傫��

IShellLink *psl;

//IShellLinkW *psl;	// ���ꂾ�Ƃ��܂��V���[�g�J�b�g�t�@�C���������ł��Ȃ��H

CoInitialize( NULL );

if ( CoCreateInstance
		( CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&psl ) == S_OK){

	psl->SetPath(TargetFilePath.t_str());          // �����N���ݒ�

	if ( Arguments != "" ){
		psl->SetArguments( Arguments.t_str() );      // �R�}���h���C��������ݒ�
	}
	if ( WorkDir != "" ){                          // ��ƃt�H���_��ݒ�
		psl->SetWorkingDirectory( WorkDir.t_str() );
	}
	psl->SetShowCmd( ShowCmd );                    // ���s���̑傫����ݒ�

	// �V���[�g�J�b�g�̕ۑ�
	if ( SaveShellLink( psl, LinkFilePath, TRUE ) == true){
		psl->Release();
		CoUninitialize();
		return(true);
	}
	else{
		psl->Release();
	}

}

CoUninitialize();
return(false);


}//CreateShellLink
//===========================================================================
// SaveShellLink
//===========================================================================
bool __fastcall TAttacheCaseOptionHandle::SaveShellLink
	( IShellLink *psl, String LinkName, BOOL bRemember )
{

bool fResult;

IPersistFile *ppf;

if ( psl->QueryInterface( IID_IPersistFile, (void **)&ppf ) != S_OK ){
	return(false);
}

if ( ppf->Save( LinkName.c_str(), bRemember ) == S_OK ){
	fResult = true;
}
else{
	fResult = false;
}

ppf->Release();
return(fResult);

}//SaveShellLink;
//----------------------------------------------------------------------


