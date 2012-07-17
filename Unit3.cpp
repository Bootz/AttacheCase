//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
TDragAndDrop *DragAndDropOptionTarget;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{

TRegIniFile *pOpt;

//-----------------------------------
//���ׂẴ^�u������
PageControl1->Align = alClient;
for (int i = 0; i < PageControl1->PageCount; i++) {
	PageControl1->Pages[i]->TabVisible = false;
}

//-----------------------------------
//�T�C�h�o�[���j���[
//-----------------------------------
lblBasic->Caption = LoadResourceString(&Msgunit3::_LABEL_BASIC);
lblSave->Caption = LoadResourceString(&Msgunit3::_LABEL_SAVE);
lblDelete->Caption = LoadResourceString(&Msgunit3::_LABEL_DELETE);
lblMovement->Caption = LoadResourceString(&Msgunit3::_LABEL_MOVEMENT);
lblSystem->Caption = LoadResourceString(&Msgunit3::_LABEL_SYSTEM);
lblAdvanced->Caption = LoadResourceString(&Msgunit3::_LABEL_ADVANCED);

//-----------------------------------
//�y��{�ݒ�z�^�u
//-----------------------------------
PanelBasicCaption->Caption = LoadResourceString(&Msgunit3::_PANEL_BASIC_CAPTION);
chkMyEncPasswordKeep->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_MY_ENC_PASSWORD_KEEP);
chkMyDecPasswordKeep->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_MY_DEC_PASSWORD_KEEP);
chkMyPasswordExe->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_MY_PASSWORD_EXE);
chkOpenFolder->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_OPEN_FOLDER);
chkOpenFile->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_OPEN_FILE);
chkEndToExit->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_END_TO_EXIT);
chkWindowForeground->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_WINDOW_FOREGROUND);
chkNoHidePassword->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_NO_HIDE_PASSWORD);
chkSaveToExeout->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_SAVE_TO_EXEOUT);
chkShowExeoutChkBox->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_SHOW_EXEOUT_CHKBOX);
chkAskEncDecode->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_ASK_ENC_DECODE);
chkNoMultipleInstance->Caption = LoadResourceString(&Msgunit3::_BASIC_PANEL_CHECKBOX_NO_MULTIPLE_INSTANCE);

//-----------------------------------
//�y�ۑ��ݒ�z�^�u
//-----------------------------------
PanelSaveCaption->Caption = LoadResourceString(&Msgunit3::_PANEL_SAVE_CAPTION);
chkSaveToSameFldr->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_SAVE_TO_SAME_FOLDER);
chkDecodeToSameFldr->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_DECODE_TO_SAME_FOLDER);
chkConfirmOverwirte->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_CONFIRM_OVERWRITE);
//�����t�@�C��������Ƃ��̏���
radiogrpMultipleFiles->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_RADIO_GROUP_MULTIPLE_FILES);
radiogrpMultipleFiles->Items->Add(LoadResourceString(&Msgunit3::_SAVE_PANEL_RADIO_GROUP_NO_ACTION));
radiogrpMultipleFiles->Items->Add(LoadResourceString(&Msgunit3::_SAVE_PANEL_RADIO_GROUP_ALL_FILES_PACK));
radiogrpMultipleFiles->Items->Add(LoadResourceString(&Msgunit3::_SAVE_PANEL_RADIO_GROUP_FILES_ONE_BY_ONE));
chkNoParentFldr->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_NO_PARENT_FOLDER);
chkKeepTimeStamp->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_KEEP_TIME_STAMP);
chkSameTimeStamp->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_SAME_TIME_STAMP);
chkExtInAtcFileName->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_EXT_IN_ATC_FILE_NAME);
chkAutoName->Caption = LoadResourceString(&Msgunit3::_SAVE_PANEL_CHECKBOX_AUTO_NAME);

//�|�b�v�A�b�v���j���[
pmnuInsertFileName->Caption = LoadResourceString(&Msgunit3::_POPUP_MENU_ITEM_INSERT_FILENAME_FORMAT);
pmnuInsertFileExt->Caption = LoadResourceString(&Msgunit3::_POPUP_MENU_ITEM_INSERT_EXTENSION_FORMAT);
//--
pmnuInsertDatetime->Caption = LoadResourceString(&Msgunit3::_POPUP_MENU_ITEM_INSERT_DATETIME_FORMAT);
pmnuInsertSerialNum->Caption = LoadResourceString(&Msgunit3::_POPUP_MENU_ITEM_INSERT_SERIAL_NUM__FORMAT);
pmnuInsertRandomText->Caption = LoadResourceString(&Msgunit3::_POPUP_MENU_ITEM_INSERT_RANDOM_TEXT_FORMAT);
pmnuInsertFileNameHead->Caption = LoadResourceString(&Msgunit3::_POPUP_MENU_ITEM_INSERT_FILENAME_HEAD_FORMAT);
pmnuInsertFileNameEnd->Caption = LoadResourceString(&Msgunit3::_POPUP_MENU_ITEM_INSERT_FILENAME_END_FORMAT);

//-----------------------------------
//�y�폜�ݒ�z�^�u
//-----------------------------------
PanelDeleteCaption->Caption = LoadResourceString(&Msgunit3::_PANEL_DELETE_CAPTION);
chkDelOrgFile->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_CHECKBOX_DEL_ORG_FILE);
chkDelEncFile->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_CHECKBOX_DEL_ENC_FILE);
chkShowDeleteChkBox->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_CHECKBOX_SHOW_DELETE_CHKBOX);
//�폜�̏ڍאݒ�
gbDeleteOption->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_RADIO_GROUP_DELETE_OPTION);
optNormalDelete->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_RADIO_GROUP_NORMAL_DELETE);
optGoToTrash->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_RADIO_GROUP_GO_TO_TRASH);
optCompleteDelete->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_RADIO_GROUP_COMPLETE_DELETE);
txtDelRandNum->EditLabel->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_DEL_RAND_NUM);
txtDelZeroNum->EditLabel->Caption = LoadResourceString(&Msgunit3::_DELETE_PANEL_DEL_ZERO_NUM);
//���A�C�R��
imgArrowDiabled->BoundsRect = imgArrowEnabled->BoundsRect;

//-----------------------------------
//�y����ݒ�z�^�u
//-----------------------------------
PanelMovementCaption->Caption = LoadResourceString(&Msgunit3::_PANEL_MOVEMENT_CAPTION);
//���k���ݒ�
gbCompressRate->Caption = LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_RADIO_GROUP_COMPRESS_RATE);
chkCompress->Caption = LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_CHECKBOX_COMPRESS_RATE);
lblCompressRate->Caption = LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_6);
lblCompressRateDetail->Caption = LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_DETAIL);
//�R���y�A
gbCompare->Caption = LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_RADIO_GROUP_COMPARE);
chkCompareFile->Caption = LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_CHECKBOX_COMPARE_FILE);

//-----------------------------------
//�y�V�X�e���ݒ�z�^�u
//-----------------------------------
PanelSystemCaption->Caption = LoadResourceString(&Msgunit3::_PANEL_SYSTEM_CAPTION);
//Windows�V�X�e���̐ݒ�
gbWindowsSystemOption->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_RADIO_GROUP_WINDOWS_SYS_OPT);
cmdAssociateAtcFile->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_ASSOCIATE_ATC_FILE);
cmdUnAssociateAtcFile->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_UN_ASSOCIATE_ATC_FILE);
cmdShortCutToSendToFileDir->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_SHORTCUT_TO_SENDTOFILE_DIR);
//�t�@�C���A�C�R���̕ύX
gbChangeFileIcon->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_RADIO_GROUP_CHANGE_FILE_ICON);
cmdAddFileIcon->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_ADD_FILE_ICON);
//����ݒ�̏o��
gbOutputOptionData->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_RADIO_GROUP_OUTPUT_OPTION_DATA);
cmdOutputOptionData->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_OUTPUT_OPTION_DATA);
cmdChangeTempOptionData->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_CHANGE_TEMP_OPTION_DATA);

//-----------------------------------
//�y���x�ݒ�z�^�u
//-----------------------------------
PanelAdvancedCaption->Caption = LoadResourceString(&Msgunit3::_PANEL_ADVANCED_CAPTION);
//�p�X���[�h�t�@�C��
lblAdvancedOptionAlertMsg->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_LABEL_ADVANCED_OPTION_ALERT_MSG);
gbPasswordFile->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_RADIO_GROUP_PASSWORD_FILE);
chkAllowPassFile->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_CHECKBOX_ALLOW_PASS_FILE);
chkCheckPassFile->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_CHECKBOX_PASS_FILE);
chkCheckPassFileDecrypt->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_CHECKBOX_PASS_FILE_DECRYPT);
chkNoErrMsgOnPassFile->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_CHECKBOX_NO_ERR_MSG_ON_PASS_FILE);
//�g���q�U��
gbCamoExt->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_RADIO_GROUP_CAMO_EXT);
chkAddCamoExt->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_CHECKBOX_ADD_CAMO_EXT);
lblCamoExtDetail->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_LABEL_CAMO_EXT_DETAIL);
//�p�X���[�h���͉񐔐���
gbTypeLimit->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_RADIO_GROUP_TYPE_LIMIT);
lblTypeLimitAlertMsg->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_LABEL_TYPE_LIMIT_ALERT_MSG);
lblMissTypeLimitsNum->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_LABEL_TYPE_LIMIT_NUM);
chkBroken->Caption = LoadResourceString(&Msgunit3::_ADVANCED_PANEL_CHECKBOX_BROKEN);

//-----------------------------------
//�y�f�o�b�O�z�^�u
//-----------------------------------
PanelDebugCaption->Caption = LoadResourceString(&Msgunit3::_PANEL_DEBUG_CAPTION);
ValueListEditor1->Align = alClient;


//-----------------------------------
//�ݒ�l���t�H�[���ɔ��f����
ShowOptionData();


//-----------------------------------
//�A�N�e�B�u�^�u�i����̓I�v�V�����N���X�Ƃ͕ʓǂ݁j
if ( FileExists(Form1->opthdl->OptionPath) == true ){
	//�ʏ�Ȃ�ǂݍ��񂾐�֕ۑ�����
	pOpt = new TRegIniFile(Form1->opthdl->OptionPath);
}
else{
	//�Ȃ���΃��W�X�g����
	pOpt = new TRegIniFile("Software\\Hibara\\AttacheCase");
}

int ActiveTabNum = pOpt->ReadInteger( "WindowPos", "ActiveTabNum", 0);
delete pOpt;

if (ActiveTabNum > -1 &&  ActiveTabNum < 7) {
	PageControl1->ActivePageIndex = ActiveTabNum;
}
else{
	PageControl1->ActivePageIndex = 0;
}

//-----------------------------------
switch(PageControl1->ActivePageIndex){
case 1:
	imgFocusLight->BoundsRect = imgSave->BoundsRect;
	break;
case 2:
	imgFocusLight->BoundsRect = imgDelete->BoundsRect;
	break;
case 3:
	imgFocusLight->BoundsRect = imgMovement->BoundsRect;
	break;
case 4:
	imgFocusLight->BoundsRect = imgSystem->BoundsRect;
	break;
case 5:
	imgFocusLight->BoundsRect = imgAdvanced->BoundsRect;
	break;
default:
	imgFocusLight->BoundsRect = imgBasic->BoundsRect;
	break;
}

//-----------------------------------
//�\�����f
PanelMenuRefresh();


}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{

//

}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormDestroy(TObject *Sender)
{

TRegIniFile *pOpt;
//�A�N�e�B�u�^�u�i����̓I�v�V�����N���X�Ƃ͕ʕۑ��j
if ( FileExists(Form1->opthdl->OptionPath) == true ){
	//�ʏ�Ȃ�ǂݍ��񂾐�֕ۑ�����
	pOpt = new TRegIniFile(Form1->opthdl->OptionPath);
}
else{
	//�Ȃ���΃��W�X�g����
	pOpt = new TRegIniFile("Software\\Hibara\\AttacheCase");
}
pOpt->WriteInteger( "WindowPos", "ActiveTabNum", PageControl1->ActivePageIndex);
delete pOpt;

//-----------------------------------
//OLE�h���b�O���h���b�v�̌�n��
//-----------------------------------
RevokeDragDrop(Form3->Handle);
DragAndDropOptionTarget->Release();
OleUninitialize();

}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormShow(TObject *Sender)
{

//-----------------------------------
//�h���b�O���h���b�v�N���X
//-----------------------------------
OleInitialize(NULL);
//Form��Create���Ă���łȂ��ƌĂяo���Ȃ�
DragAndDropOptionTarget = new TDragAndDrop(Form3);
DragAndDropOptionTarget->fMultipleFilesOk = false;	//�����t�@�C���h���b�v�s��
DragAndDropOptionTarget->FilesDragOver = FilesDragOver;
DragAndDropOptionTarget->FilesDragLeave = FilesDragLeave;
DragAndDropOptionTarget->FilesDragEnd = FilesDragEnd;
RegisterDragDrop(Form3->Handle, (IDropTarget*)DragAndDropOptionTarget);

//-----------------------------------
//�ǂݍ��ݐ���t�H�[���L���v�V�����ɕ\��

// INI�t�@�C��
if (Form1->opthdl->OptType == 1) {
	Form3->Icon = imgIni->Picture->Icon;
	Form3->Caption = "INI�t�@�C���F" + Form1->opthdl->OptionPath;
}
// �R�}���h���C������
else if (Form1->opthdl->OptType == 1) {
	Form3->Icon = imgBat->Picture->Icon;
	Form3->Caption = "�R�}���h���C���F" + Form1->opthdl->OptionPath;
}
// ���W�X�g��
else{
	Form3->Icon = imgReg->Picture->Icon;
	Form3->Caption = "���W�X�g���F" + Form1->opthdl->OptionPath;
}


}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormResize(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm3::cmdCancelClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::cmdOKClick(TObject *Sender)
{

//�ݒ�l�𓮍�ݒ�t�H�[���ɔ��f�\������
SaveOptionData();

Close();

}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgBasicMouseEnter(TObject *Sender)
{
imgFocusLight->BoundsRect = imgBasic->BoundsRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgSaveMouseEnter(TObject *Sender)
{
imgFocusLight->BoundsRect = imgSave->BoundsRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgDeleteMouseEnter(TObject *Sender)
{
imgFocusLight->BoundsRect = imgDelete->BoundsRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgMovementMouseEnter(TObject *Sender)
{
imgFocusLight->BoundsRect = imgMovement->BoundsRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgSystemMouseEnter(TObject *Sender)
{
imgFocusLight->BoundsRect = imgSystem->BoundsRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgAdvancedMouseEnter(TObject *Sender)
{
imgFocusLight->BoundsRect = imgAdvanced->BoundsRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgBasicClick(TObject *Sender)
{
PageControl1->ActivePageIndex = 0;
PanelMenuRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgSaveClick(TObject *Sender)
{
PageControl1->ActivePageIndex = 1;
PanelMenuRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgDeleteClick(TObject *Sender)
{
PageControl1->ActivePageIndex = 2;
PanelMenuRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgMovementClick(TObject *Sender)
{
PageControl1->ActivePageIndex = 3;
PanelMenuRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgSystemClick(TObject *Sender)
{
PageControl1->ActivePageIndex = 4;
PanelMenuRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::imgAdvancedClick(TObject *Sender)
{
PageControl1->ActivePageIndex = 5;
PanelMenuRefresh();
}
//---------------------------------------------------------------------------
//�p�l�����j���[�\���̃��t���b�V�����s��
void __fastcall TForm3::PanelMenuRefresh(void)
{

switch(PageControl1->ActivePageIndex){
case 1:
	imgSelectCursor->Top = imgSave->Top;
	imgSelectCursor->Left = PanelMenu->Width - imgSelectCursor->Width - 4;
	break;
case 2:
	imgSelectCursor->Top = imgDelete->Top;
	imgSelectCursor->Left = PanelMenu->Width - imgSelectCursor->Width - 4;
	break;
case 3:
	imgSelectCursor->Top = imgMovement->Top;
	imgSelectCursor->Left = PanelMenu->Width - imgSelectCursor->Width - 4;
	break;
case 4:
	imgSelectCursor->Top = imgSystem->Top;
	imgSelectCursor->Left = PanelMenu->Width - imgSelectCursor->Width - 4;
	break;
case 5:
	imgSelectCursor->Top = imgAdvanced->Top;
	imgSelectCursor->Left = PanelMenu->Width - imgSelectCursor->Width - 4;
	break;
default:	// 0
	imgSelectCursor->Top = imgBasic->Top;
	imgSelectCursor->Left = PanelMenu->Width - imgSelectCursor->Width - 4;
	break;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::PanelMenuDblClick(TObject *Sender)
{

TStringList *KeyValueList = new TStringList();
Form1->opthdl->GetKeyValueData(KeyValueList);

//�ݒ�l���܂Ƃ߂ăf�o�b�O�\������
for (int i = 0; i < KeyValueList->Count; i++) {
	ValueListEditor1->InsertRow(KeyValueList->Names[i], KeyValueList->ValueFromIndex[i], true);
}

delete KeyValueList;

//�ݒ�l�̃f�o�b�O�ꗗ�\��
PageControl1->ActivePageIndex = 6;

}
//===========================================================================
// �ݒ�l�𓮍�ݒ�t�H�[���ɔ��f�\������
//===========================================================================
void __fastcall TForm3::ShowOptionData(void)
{

//-----------------------------------
//�y��{�ݒ�z�^�u
//-----------------------------------
//������������"*"��\������
int pNum;
chkMyEncPasswordKeep->Checked = Form1->opthdl->fMyEncodePasswordKeep;
if ( (pNum = Form1->opthdl->MyEncodePassword.Length()) > 32 ){
	pNum = 32;
}
btneditMyEncPassword->Text = String::StringOfChar('*', pNum);

chkMyDecPasswordKeep->Checked = Form1->opthdl->fMyDecodePasswordKeep;
if ( (pNum = Form1->opthdl->MyDecodePassword.Length()) > 32 ){
	pNum = 32;
}
btneditMyDecPassword->Text = String::StringOfChar('*', pNum);

chkMyPasswordExe->Checked = Form1->opthdl->fMemPasswordExe;
chkOpenFolder->Checked = Form1->opthdl->fOpenFolder;
chkOpenFile->Checked = Form1->opthdl->fOpenFile;
chkEndToExit->Checked = Form1->opthdl->fEndToExit;
chkWindowForeground->Checked = Form1->opthdl->fWindowForeground;
chkNoHidePassword->Checked = Form1->opthdl->fNoHidePassword;
chkSaveToExeout->Checked = Form1->opthdl->fSaveToExeout;
chkShowExeoutChkBox->Checked = Form1->opthdl->fShowExeoutChkBox;
chkAskEncDecode->Checked = Form1->opthdl->fAskEncDecode;
chkNoMultipleInstance->Checked = Form1->opthdl->fNoMultipleInstance;

//-----------------------------------
//�y�ۑ��ݒ�z�^�u
//-----------------------------------
chkSaveToSameFldr->Checked = Form1->opthdl->fSaveToSameFldr;
btneditSaveToSameFldrPath->Text = Form1->opthdl->SaveToSameFldrPath;
if (chkSaveToSameFldr->Checked == true) {
	btneditSaveToSameFldrPath->Enabled = true;
	btneditSaveToSameFldrPath->Color = clWindow;
}
else{
	btneditSaveToSameFldrPath->Enabled = false;
	btneditSaveToSameFldrPath->Color = clBtnFace;
}

chkDecodeToSameFldr->Checked = Form1->opthdl->fDecodeToSameFldr;
btneditDecodeToSameFldrPath->Text = Form1->opthdl->DecodeToSameFldrPath;
if (chkDecodeToSameFldr->Checked == true) {
	btneditDecodeToSameFldrPath->Enabled = true;
	btneditDecodeToSameFldrPath->Color = clWindow;
}
else{
	btneditDecodeToSameFldrPath->Enabled = false;
	btneditDecodeToSameFldrPath->Color = clBtnFace;
}

chkConfirmOverwirte->Checked = Form1->opthdl->fConfirmOverwirte;

//�����t�@�C��������Ƃ��̏���
if ( Form1->opthdl->fAllFilePack == true ) {
	//�����̃t�@�C�����Í�������ۂ͈�ɂ܂Ƃ߂�
	radiogrpMultipleFiles->ItemIndex = 1;
}
else if ( Form1->opthdl->fFilesOneByOne == true ) {
	//�t�H���_���̃t�@�C���͌ʂɈÍ���/��������
	radiogrpMultipleFiles->ItemIndex = 2;
}
else{
	//�������Ȃ�
	radiogrpMultipleFiles->ItemIndex = 0;
}

chkNoParentFldr->Checked = Form1->opthdl->fNoParentFldr;
chkKeepTimeStamp->Checked = Form1->opthdl->fKeepTimeStamp;
chkSameTimeStamp->Checked = Form1->opthdl->fSameTimeStamp;
chkExtInAtcFileName->Checked = Form1->opthdl->fExtInAtcFileName;
chkAutoName->Checked = Form1->opthdl->fAutoName;
btneditAutoNameFormatText->Text = Form1->opthdl->AutoNameFormatText;


//-----------------------------------
//�y�폜�ݒ�z�^�u
//-----------------------------------
chkDelOrgFile->Checked = Form1->opthdl->fDelOrgFile;
chkDelEncFile->Checked = Form1->opthdl->fDelEncFile;
chkShowDeleteChkBox->Checked = Form1->opthdl->fShowDeleteChkBox;

//�폜�̏ڍאݒ�
if (Form1->opthdl->fCompleteDelete == 1) {      //���S�폜
	optCompleteDelete->Checked = true;
	imgArrowEnabled->Visible = true;
	imgArrowDiabled->Visible = false;
	UpDownDelRand->Enabled = true;
	UpDownDelZero->Enabled = true;
	txtDelRandNum->Color = clWindow;
	txtDelZeroNum->Color = clWindow;
}
else if (Form1->opthdl->fCompleteDelete == 2) { //���ݔ��ֈړ�
	optGoToTrash->Checked = true;
	imgArrowEnabled->Visible = false;
	imgArrowDiabled->Visible = true;
	UpDownDelRand->Enabled = false;
	UpDownDelZero->Enabled = false;
	txtDelRandNum->Color = clBtnFace;
	txtDelZeroNum->Color = clBtnFace;
}
else{                                           //�ʏ�폜
	optNormalDelete->Checked = true;
	imgArrowEnabled->Visible = false;
	imgArrowDiabled->Visible = true;
	UpDownDelRand->Enabled = false;
	UpDownDelZero->Enabled = false;
	txtDelRandNum->Color = clBtnFace;
	txtDelZeroNum->Color = clBtnFace;
}
//�폜��
UpDownDelRand->Position = Form1->opthdl->DelRandNum;
UpDownDelZero->Position = Form1->opthdl->DelZeroNum;

//�u�폜�̏ڍאݒ�v�O���[�v�{�b�N�X���̗L��/�����𐧌䂷��
DeleteGroupEnabled();

//-----------------------------------
//�y����ݒ�z�^�u
//-----------------------------------
//���k���ݒ�
if ( Form1->opthdl->CompressRate == 0 ) {
	chkCompress->Checked = false;
}
else{
	chkCompress->Checked = true;
}
TrackBar1->Position = Form1->opthdl->CompressRate;

//�R���y�A
chkCompareFile->Checked = Form1->opthdl->fCompareFile;

//-----------------------------------
//�y�V�X�e���ݒ�z�^�u
//-----------------------------------

//'�u����v�t�H���_�[�ɃA�^�b�V�F�P�[�X��ǉ�(&S)';
String SendToFilePath = Form1->opthdl->CreateSendToFolderAppFullPath();

if ( FileExists(SendToFilePath) == true) {
	//'�u����v�t�H���_�[����A�^�b�V�F�P�[�X���폜(&S)'
	cmdShortCutToSendToFileDir->Caption =
		LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_DELETE_FROM_SENDTOFILE_DIR);
}
else{
	//'�u����v�t�H���_�[�ɃA�^�b�V�F�P�[�X��ǉ�(&S)';
	cmdShortCutToSendToFileDir->Caption =
		LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_SHORTCUT_TO_SENDTOFILE_DIR);
}

//�t�@�C���A�C�R���̓o�^
RegIconFileToComboBox();

//����ݒ�̏o��
bool fArgs = false;

//�����N���Ȃ�ݒ�͕ۑ��ł��Ȃ�
if ( ParamCount() > 0) {
	cmdOutputOptionData->Enabled = false;
	fArgs = true;
}

//�����N�����A�܂���ini�t�@�C������
if ( fArgs == true || Form1->opthdl->OptType == 1){
	cmdChangeTempOptionData->Enabled = true; //�ꎞ�ݒ�����݂̐ݒ�ɒu��������
}
else{
	cmdChangeTempOptionData->Enabled = false;
}

//-----------------------------------
//�y���x�ݒ�z�^�u
//-----------------------------------
//�p�X���[�h�t�@�C��
chkAllowPassFile->Checked = Form1->opthdl->fAllowPassFile;

//-----------------------------------
//�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
if ( Form1->opthdl->fCheckPassFile == true &&	chkAllowPassFile->Checked == true ){
	chkCheckPassFile->Checked = true;
	//cmdSelectPassFolder->Glyph = imgFolder->Picture->Bitmap;
	btneditPassFilePath->ReadOnly = false;
	btneditPassFilePath->Color = clWindow;
}
else{
	chkCheckPassFile->Checked = false;
	//cmdSelectPassFolder->Glyph = imgNoFolder->Picture->Bitmap;
	btneditPassFilePath->ReadOnly = true;
	btneditPassFilePath->Color = clBtnFace;
}
btneditPassFilePath->Text = Form1->opthdl->PassFilePath;
btneditPassFilePath->SelStart = btneditPassFilePath->Text.Length(); //�p�X�����̕���\��

//-----------------------------------
//�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
if ( Form1->opthdl->fCheckPassFileDecrypt == true && chkAllowPassFile->Checked == true ){
	chkCheckPassFileDecrypt->Checked = true;
	//cmdSelectPassFolderDecrypt->Glyph = imgFolder->Picture->Bitmap;
	btneditPassFilePathDecrypt->ReadOnly = false;
	btneditPassFilePathDecrypt->Color = clWindow;
}
else{
	chkCheckPassFileDecrypt->Checked = false;
	//cmdSelectPassFolderDecrypt->Glyph = imgNoFolder->Picture->Bitmap;
	btneditPassFilePathDecrypt->ReadOnly = true;
	btneditPassFilePathDecrypt->Color = clBtnFace;
}
btneditPassFilePathDecrypt->Text = Form1->opthdl->PassFilePathDecrypt;
btneditPassFilePathDecrypt->SelStart = btneditPassFilePathDecrypt->Text.Length(); //�p�X�����̕���\��

chkNoErrMsgOnPassFile->Checked = Form1->opthdl->fNoErrMsgOnPassFile;

//�g���q�U��
if ( Form1->opthdl->fAddCamoExt == true ){
	chkAddCamoExt->Checked = true;
	txtCamoExt->Enabled = true;
	txtCamoExt->Color = clWindow;
}
else{
	chkAddCamoExt->Checked = false;
	txtCamoExt->Enabled = false;
	txtCamoExt->Color = clBtnFace;
}

txtCamoExt->Text = Form1->opthdl->CamoExt;

//�p�X���[�h���͉񐔐���
cmbMissTypeLimitsNum->ItemIndex = Form1->opthdl->MissTypeLimitsNum-1;
chkBroken->Checked = Form1->opthdl->fBroken;


}
//===========================================================================
// ����ݒ�t�H�[������ݒ�l�ɔ��f����i���W�X�g�� or INI�t�@�C���ւ̕ۑ����s���j
//===========================================================================
void __fastcall TForm3::SaveOptionData(void)
{

//-----------------------------------
//�y��{�ݒ�z�^�u
//-----------------------------------

//�Í����p�X���[�h���L������
Form1->opthdl->fMyEncodePasswordKeep = chkMyEncPasswordKeep->Checked;
if (TempMyEncodePassword != "" && Form1->opthdl->fMyEncodePasswordKeep == true) {
	Form1->opthdl->MyEncodePassword = TempMyEncodePassword;
	TempMyEncodePassword = "";
}

if ( chkMyEncPasswordKeep->Checked == false ){
	Form1->opthdl->MyEncodePassword = "";	//�L���p�X���[�h�̃N���A
}

//�����p�X���[�h���L������
Form1->opthdl->fMyDecodePasswordKeep = chkMyDecPasswordKeep->Checked;
if ( TempMyDecodePassword != "" && Form1->opthdl->fMyDecodePasswordKeep == true ) {
	Form1->opthdl->MyDecodePassword = TempMyDecodePassword;
	TempMyDecodePassword = "";
}

if ( chkMyDecPasswordKeep->Checked == false ){
	Form1->opthdl->MyDecodePassword = "";	//�L���p�X���[�h�̃N���A
}

Form1->opthdl->fMemPasswordExe = chkMyPasswordExe->Checked;
Form1->opthdl->fOpenFolder = chkOpenFolder->Checked;
Form1->opthdl->fOpenFile = chkOpenFile->Checked;
Form1->opthdl->fEndToExit = chkEndToExit->Checked;
Form1->opthdl->fWindowForeground = chkWindowForeground->Checked;
Form1->opthdl->fNoHidePassword = chkNoHidePassword->Checked;
Form1->opthdl->fSaveToExeout = chkSaveToExeout->Checked;
Form1->opthdl->fShowExeoutChkBox = chkShowExeoutChkBox->Checked;
Form1->opthdl->fAskEncDecode = chkAskEncDecode->Checked;
Form1->opthdl->fNoMultipleInstance = chkNoMultipleInstance->Checked;

//-----------------------------------
//�y�ۑ��ݒ�z�^�u
//-----------------------------------
Form1->opthdl->fSaveToSameFldr = chkSaveToSameFldr->Checked;
Form1->opthdl->SaveToSameFldrPath = btneditSaveToSameFldrPath->Text;
Form1->opthdl->fDecodeToSameFldr = chkDecodeToSameFldr->Checked;
Form1->opthdl->DecodeToSameFldrPath = btneditDecodeToSameFldrPath->Text;

Form1->opthdl->fConfirmOverwirte = chkConfirmOverwirte->Checked;

//�����̃t�@�C�����Í�������ۂ͈�ɂ܂Ƃ߂�
if ( radiogrpMultipleFiles->ItemIndex == 1 ){
	Form1->opthdl->fAllFilePack = true;
	Form1->opthdl->fFilesOneByOne = false;
}
//�t�H���_���̃t�@�C���͌ʂɈÍ���/��������
else if ( radiogrpMultipleFiles->ItemIndex == 2 ){
	Form1->opthdl->fAllFilePack = false;
	Form1->opthdl->fFilesOneByOne = true;
}
else{
	//�������Ȃ�
	Form1->opthdl->fAllFilePack = false;
	Form1->opthdl->fFilesOneByOne = false;
}

Form1->opthdl->fNoParentFldr = chkNoParentFldr->Checked;
Form1->opthdl->fKeepTimeStamp = chkKeepTimeStamp->Checked;
Form1->opthdl->fSameTimeStamp = chkSameTimeStamp->Checked;
Form1->opthdl->fExtInAtcFileName = chkExtInAtcFileName->Checked;
Form1->opthdl->fAutoName = chkAutoName->Checked;
Form1->opthdl->AutoNameFormatText = btneditAutoNameFormatText->Text;

//-----------------------------------
//�y�폜�ݒ�z�^�u
//-----------------------------------
Form1->opthdl->fDelOrgFile = chkDelOrgFile->Checked;
Form1->opthdl->fDelEncFile = chkDelEncFile->Checked;
Form1->opthdl->fShowDeleteChkBox = chkShowDeleteChkBox->Checked;

//�폜�̏ڍאݒ�
if ( optCompleteDelete->Checked == true ) {     //���S�폜
	Form1->opthdl->fCompleteDelete = 1;
}
else if ( optGoToTrash->Checked == true ) {     //���ݔ��ֈړ�
	Form1->opthdl->fCompleteDelete = 2;
}
else{
	Form1->opthdl->fCompleteDelete = 3;           //�ʏ�폜
}

//�폜��
Form1->opthdl->DelRandNum = UpDownDelRand->Position;
Form1->opthdl->DelZeroNum = UpDownDelZero->Position;


//-----------------------------------
//�y����ݒ�z�^�u
//-----------------------------------
//���k���ݒ�
Form1->opthdl->CompressRate = TrackBar1->Position;
//�R���y�A
Form1->opthdl->fCompareFile = chkCompareFile->Checked;

//-----------------------------------
//�y�V�X�e���ݒ�z�^�u
//-----------------------------------
//�֘A�Â��t�@�C���A�C�R���ԍ�
Form1->opthdl->AtcsFileIconIndex = comboDataIcon->ItemIndex + 1;
//���[�U�[�o�^�A�C�R���t�@�C���̃p�X
Form1->opthdl->UserRegIconFilePath = TempUserRegIconFilePath;

//-----------------------------------
//�y���x�ݒ�z�^�u
//-----------------------------------
//�p�X���[�h�t�@�C��
Form1->opthdl->fAllowPassFile = chkAllowPassFile->Checked;

//-----------------------------------
//�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
Form1->opthdl->fCheckPassFile = chkCheckPassFile->Checked;
Form1->opthdl->PassFilePath = btneditPassFilePath->Text;

//�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
Form1->opthdl->fCheckPassFileDecrypt = chkCheckPassFileDecrypt->Checked;
Form1->opthdl->PassFilePathDecrypt = btneditPassFilePathDecrypt->Text;

Form1->opthdl->fNoErrMsgOnPassFile = chkNoErrMsgOnPassFile->Checked;

//�g���q�U��
Form1->opthdl->fAddCamoExt = chkAddCamoExt->Checked;
Form1->opthdl->CamoExt = txtCamoExt->Text;

//�p�X���[�h���͉񐔐���
Form1->opthdl->MissTypeLimitsNum = cmbMissTypeLimitsNum->ItemIndex + 1;
Form1->opthdl->fBroken = chkBroken->Checked;

//-----------------------------------
// �ݒ�l��ۑ�
//-----------------------------------
Form1->opthdl->SaveOptionData();


}
//---------------------------------------------------------------------------
void __fastcall TForm3::TrackBar1Change(TObject *Sender)
{

//���k���̕ύX
switch(TrackBar1->Position){
case 0:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_0);
	break;
case 1:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_1);
	break;
case 2:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_2);
	break;
case 3:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_3);
	break;
case 4:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_4);
	break;
case 5:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_5);
	break;
case 7:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_7);
	break;
case 8:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_8);
	break;
case 9:
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_9);
	break;
default:
	// 6: �W�����k
	lblCompressRate->Caption =
		LoadResourceString(&Msgunit3::_MOVEMENT_PANEL_LABEL_COMPRESS_RATE_6);
	break;
}

if ( TrackBar1->Position == 0 ) {
	chkCompress->Checked = false;
}
else{
	chkCompress->Checked = true;
}


}
//----------------------------------------------------------------------
//�t�@�C���A�C�R�����R���{�{�b�N�X�֓o�^����
void __fastcall TForm3::RegIconFileToComboBox(void)
{

//�t�@�C���A�C�R���̃��[�h

int i;
String FilePath;
String IconName;

TIcon *icon= new TIcon;
TComboExItem *pItem;

ImageList2->Clear();
comboDataIcon->Items->Clear();

//���\�[�X����A�C�R���t�@�C����o�^
for ( i = 0; i < FILE_ICON_NUM; i++ ){

	IconName = "SUBICON" + IntToStr(i);
	icon->LoadFromResourceName((int)HInstance, IconName);

	if(icon->Handle){
		ImageList2->AddIcon(icon);
		pItem = comboDataIcon->ItemsEx->Add();
		pItem->ImageIndex = i;
		pItem->Caption = "Icon "+IntToStr(i+1);
	}

}

//���[�U�[�w��̃A�C�R���t�@�C����o�^
if ( TempUserRegIconFilePath != "" ){
	FilePath = TempUserRegIconFilePath;
}
else{
	FilePath = Form1->opthdl->UserRegIconFilePath;
}

if ( FileExists(FilePath) == true ){
	icon->LoadFromFile(FilePath);
	ImageList2->AddIcon(icon);
	pItem = comboDataIcon->ItemsEx->Add();
	pItem->ImageIndex = ImageList2->Count-1;
	pItem->Caption = LoadResourceString(&Msgunit3::_SYSTEM_PANEL_COMBO_USER_REG_FILE_ICON);
	Form1->opthdl->AtcsFileIconIndex = comboDataIcon->ItemsEx->Count;
}

comboDataIcon->ItemIndex = Form1->opthdl->AtcsFileIconIndex-1;

delete icon;

}
//---------------------------------------------------------------------------
void __fastcall TForm3::optNormalDeleteClick(TObject *Sender)
{
//'�ʏ�̍폜���s��(&N)
imgArrowEnabled->Visible = false;
imgArrowDiabled->Visible = true;
UpDownDelRand->Enabled = false;
UpDownDelZero->Enabled = false;
txtDelRandNum->Color = clBtnFace;
txtDelZeroNum->Color = clBtnFace;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::optGoToTrashClick(TObject *Sender)
{
//'���ݔ��ւ̍폜���s��(&T)'
imgArrowEnabled->Visible = false;
imgArrowDiabled->Visible = true;
UpDownDelRand->Enabled = false;
UpDownDelZero->Enabled = false;
txtDelRandNum->Color = clBtnFace;
txtDelZeroNum->Color = clBtnFace;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::optCompleteDeleteClick(TObject *Sender)
{
//'���S�폜���s��(&C)'
imgArrowEnabled->Visible = true;
imgArrowDiabled->Visible = false;
UpDownDelRand->Enabled = true;
UpDownDelZero->Enabled = true;
txtDelRandNum->Color = clWindow;
txtDelZeroNum->Color = clWindow;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::btneditMyEncPasswordLeftButtonClick(TObject *Sender)
{
//�Í����̋L���p�X���[�h���̓p�l����\��
Form4 = new TForm4(this, 0);
Form4->ShowModal();
Form4->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::btneditMyDecPasswordLeftButtonClick(TObject *Sender)
{
//��������L���p�X���[�h���̓p�l����\��
Form4 = new TForm4(this, 1);
Form4->ShowModal();
Form4->Release();
}
//---------------------------------------------------------------------------
// �Í���/�����p�X���[�h�L���̃e�L�X�g�{�b�N�X�Ƀt�@�C�����h���b�O���h���b�v

//---------------------------------------------------------------------------
void __fastcall TForm3::btneditSaveToSameFldrPathLeftButtonClick(TObject *Sender)
{

String DirPath;
TSelectDirExtOpts opt =
	TSelectDirExtOpts() << sdNewUI << sdNewFolder << sdShowEdit << sdValidateDir;

// '�Í����t�@�C������ɕۑ��������t�H���_�[��I�����Ă��������B'
if (SelectDirectory(
	LoadResourceString(
		&Msgunit3::_DIALOG_MSG_SELECT_SAVE_ATC_FILE_TO_DIR_PATH),
		L"",
		DirPath, opt) == true){

	btneditSaveToSameFldrPath->Text = DirPath;
	chkSaveToSameFldr->Checked = true;

}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::btneditDecodeToSameFldrPathLeftButtonClick(TObject *Sender)
{

String DirPath;
TSelectDirExtOpts opt =
	TSelectDirExtOpts() << sdNewUI << sdNewFolder << sdShowEdit << sdValidateDir;

// '���������t�@�C������ɕۑ��������t�H���_�[��I�����Ă��������B'
if (SelectDirectory(
	LoadResourceString(
		&Msgunit3::_DIALOG_MSG_SELECT_DECODE_TO_SAME_DIR_PATH),
		L"",
		DirPath, opt) == true){

	btneditSaveToSameFldrPath->Text = DirPath;
	chkDecodeToSameFldr->Checked = true;

}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkAllowPassFileClick(TObject *Sender)
{

//'�p�X���[�h�t�@�C���Ƀt�@�C���̎w���������(&D)'
if ( chkAllowPassFile->Checked == true ) {
	chkCheckPassFile->Enabled = true;
	btneditPassFilePath->ReadOnly = false;
	btneditPassFilePath->Color = clWindow;
	chkCheckPassFileDecrypt->Enabled = true;
	btneditPassFilePathDecrypt->ReadOnly = false;
	btneditPassFilePathDecrypt->Color = clWindow;
}
else{
	chkCheckPassFile->Enabled = false;
	btneditPassFilePath->ReadOnly = true;
	btneditPassFilePath->Color = clBtnFace;
	chkCheckPassFileDecrypt->Enabled = false;
	btneditPassFilePathDecrypt->ReadOnly = true;
	btneditPassFilePathDecrypt->Color = clBtnFace;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkCheckPassFileClick(TObject *Sender)
{

//'�Í������Ƀp�X���[�h�t�@�C���������`�F�b�N����(&H)'
if ( chkCheckPassFile->Checked == true) {
	btneditPassFilePathLeftButtonClick(Sender);
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkCheckPassFileDecryptClick(TObject *Sender)
{

//'�������Ƀp�X���[�h�t�@�C���������`�F�b�N����(&K)';
if ( chkCheckPassFileDecrypt->Checked == true) {
	btneditPassFilePathDecryptLeftButtonClick(Sender);
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::btneditPassFilePathLeftButtonClick(TObject *Sender)
{

//'�Í�������Ƃ��̃p�X���[�h�t�@�C���I��'
OpenDialog1->Title = LoadResourceString(&Msgunit3::_DIALOG_CAPTION_SELECT_PASSWORD_FILE_ENCRYPT);
//'���ׂẴt�@�C��(*.*)|*.*'
OpenDialog1->Filter = LoadResourceString(&Msgunit3::_DIALOG_SELECT_PASSWORD_FILE_FILTER_TEXT);

if ( OpenDialog1->Execute() == true ) {
	btneditPassFilePath->Text = OpenDialog1->FileName;
	chkCheckPassFile->Checked = true;
}
else{
	chkCheckPassFile->Checked = false;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::btneditPassFilePathDecryptLeftButtonClick(TObject *Sender)
{

//'��������Ƃ��̃p�X���[�h�t�@�C���̑I��'
OpenDialog1->Title = LoadResourceString(&Msgunit3::_DIALOG_MSG_SELECT_PASSWORD_FILE_DECRYPT);
//'���ׂẴt�@�C��(*.*)|*.*'
OpenDialog1->Filter = LoadResourceString(&Msgunit3::_DIALOG_SELECT_PASSWORD_FILE_FILTER_TEXT);

if ( OpenDialog1->Execute() == true ) {
	btneditPassFilePathDecrypt->Text = OpenDialog1->FileName;
	chkCheckPassFileDecrypt->Checked = true;
}
else{
	chkCheckPassFileDecrypt->Checked = false;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkAddCamoExtClick(TObject *Sender)
{

if ( chkAddCamoExt->Checked == true ) {
	txtCamoExt->Enabled = true;
	txtCamoExt->Color = clWindow;
}
else{
	txtCamoExt->Enabled = false;
	txtCamoExt->Color = clBtnFace;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::pmnuInsertFileNameClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm3::pmnuInsertFileExtClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm3::pmnuInsertDatetimeClick(TObject *Sender)
{
Form4 = new TForm4(this, 2);	//�����}��
Form4->ShowModal();
Form4->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::pmnuInsertSerialNumClick(TObject *Sender)
{
Form4 = new TForm4(this, 3);	//�A�ԑ}��
Form4->ShowModal();
Form4->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::pmnuInsertRandomTextClick(TObject *Sender)
{
Form4 = new TForm4(this, 4);	//�����_��������̑}��
Form4->ShowModal();
Form4->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::pmnuInsertFileNameHeadClick(TObject *Sender)
{
Form4 = new TForm4(this, 5);	//�t�@�C�����̐擪�������̑}��
Form4->ShowModal();
Form4->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::pmnuInsertFileNameEndClick(TObject *Sender)
{
Form4 = new TForm4(this, 6);	//�t�@�C�����̖����������̑}��
Form4->ShowModal();
Form4->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkMyEncPasswordKeepClick(TObject *Sender)
{

//�t�H�[�����������Ƃ��ɃN���b�N�C�x���g���N���Ă��܂��̂ŁA
//�t�H�[�����\������Ă���Ƃ��̂ݍ��{�^���C�x���g���Ă�
if ( this->Visible == true && chkMyEncPasswordKeep->Checked == true ) {
	btneditMyEncPasswordLeftButtonClick(Sender);
	if ( TempMyEncodePassword == "") {
		chkMyEncPasswordKeep->Checked = false;
	}
}

if ( chkMyEncPasswordKeep->Checked == true ) {
	btneditMyEncPassword->ReadOnly = false;
	btneditMyEncPassword->Color = clWindow;
}
else{
	btneditMyEncPassword->ReadOnly = true;
	btneditMyEncPassword->Color = clBtnFace;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkMyDecPasswordKeepClick(TObject *Sender)
{

if ( this->Visible == true && chkMyDecPasswordKeep->Checked == true ) {
	btneditMyDecPasswordLeftButtonClick(Sender);
	if ( TempMyDecodePassword == "") {
		chkMyDecPasswordKeep->Checked = false;
	}
}

if ( chkMyDecPasswordKeep->Checked == true ) {
	btneditMyDecPassword->Enabled = true;
	btneditMyDecPassword->Color = clWindow;
}
else{
	btneditMyDecPassword->Enabled = false;
	btneditMyDecPassword->Color = clBtnFace;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkSaveToSameFldrClick(TObject *Sender)
{

if ( chkSaveToSameFldr->Checked == true ) {
	btneditSaveToSameFldrPath->Enabled = true;
	btneditSaveToSameFldrPath->Color = clWindow;
}
else{
	btneditSaveToSameFldrPath->Enabled = false;
	btneditSaveToSameFldrPath->Color = clBtnFace;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkDecodeToSameFldrClick(TObject *Sender)
{

if ( chkDecodeToSameFldr->Checked == true ) {
	btneditDecodeToSameFldrPath->Enabled = true;
	btneditDecodeToSameFldrPath->Color = clWindow;
}
else{
	btneditDecodeToSameFldrPath->Enabled = false;
	btneditDecodeToSameFldrPath->Color = clBtnFace;
}


}
//---------------------------------------------------------------------------
void __fastcall TForm3::cmdAssociateAtcFileClick(TObject *Sender)
{
//'�Í����t�@�C��(*.atc)�̊֘A�t���ݒ�(&A)';
RunAsAdmin(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::cmdUnAssociateAtcFileClick(TObject *Sender)
{

//'�Í����t�@�C��(*.atc)�̊֘A�t������(&F)';
RunAsAdmin(1);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::cmdShortCutToSendToFileDirClick(TObject *Sender)
{

//'�u����v�t�H���_�[�ɃA�^�b�V�F�P�[�X��ǉ�(&S)';
String SendToFilePath = Form1->opthdl->CreateSendToFolderAppFullPath();

//ShowMessage(SendToFilePath);
//return;

if ( FileExists(SendToFilePath) == true) {
	//�u����v�ɂ���V���[�g�J�b�g�t�@�C���̍폜
	DeleteFile(SendToFilePath);
	//'�u����v�t�H���_�[�ɃA�^�b�V�F�P�[�X��ǉ�(&S)';
	cmdShortCutToSendToFileDir->Caption =
		LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_SHORTCUT_TO_SENDTOFILE_DIR);
}
else{
	// �u����v�ɃV���[�g�J�b�g�t�@�C�����쐬����
	if ( Form1->opthdl->CreateShortCutFile(SendToFilePath, Application->ExeName, "", "", 0 ) == false ){

		//�G���[
		ShowMessage("�G���[");
	}

	//'�u����v�t�H���_�[����A�^�b�V�F�P�[�X���폜(&S)'
	cmdShortCutToSendToFileDir->Caption =
		LoadResourceString(&Msgunit3::_SYSTEM_PANEL_BUTTON_DELETE_FROM_SENDTOFILE_DIR);
}

}
//===========================================================================
//UAC�G���x�[�V������v�����Ċ֘A�t���v���O���������s
//===========================================================================
bool __fastcall TForm3::RunAsAdmin(int Option)
{

// Option : 0  atc�t�@�C���̊֘A�t���ݒ���s��
//          1  �֘A�t���ݒ����������

String Parameters;
String MsgErrorString;
String AtcSetupExePath = ExtractFileDir(Application->ExeName)+"\\AtcSetup.exe";

//-----------------------------------
//�֘A�t���v���O�����̎w��
if ( FileExists(AtcSetupExePath) == false ){
	//'�A�^�b�V�F�P�[�X�ɕt������֘A�t���A�v���P�[�V����(AtcSetup.exe)��������܂���B'
	MsgErrorString = LoadResourceString(&Msgunit3::_DIALOG_MSG_NOT_FOUND_ATC_SETUP_EXE);
	MessageDlg(MsgErrorString, mtError, TMsgDlgButtons() << mbOK, 0);
	return(false);
}

//-----------------------------------
//�p�����[�^�̐ݒ�
Parameters = IntToStr(Option);


//-----------------------------------
//UAC�G���x�[�V������v�����Ċ֘A�t���v���O�������Ăяo��

TShellExecuteInfoW sei = {0};

if ( Win32MajorVersion >= 6 ) {
	sei.lpVerb = L"runas";	//Vista
}
else{
	sei.lpVerb = L"open";	//���̑�OS
}

sei.cbSize = sizeof(sei);
sei.hwnd = Application->Handle;
sei.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_FLAG_NO_UI;
sei.lpFile = AtcSetupExePath.c_str();
sei.lpParameters = Parameters.c_str();
sei.nShow = SW_SHOWNOACTIVATE;

if ( ShellExecuteExW(&sei) == false){
		//RaiseLastOSError();
		return(false);
}

return(true);

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkAutoNameClick(TObject *Sender)
{

// '�����ňÍ����t�@�C������t������(&R)';
if ( chkAutoName->Checked == true ) {
	btneditAutoNameFormatText->ReadOnly = false;
	btneditAutoNameFormatText->Color = clWindow;
	btneditAutoNameFormatText->RightButton->Enabled = true;
	btneditAutoNameFormatText->SetFocus();
}
else{
	btneditAutoNameFormatText->ReadOnly = true;
	btneditAutoNameFormatText->Color = clBtnFace;
	btneditAutoNameFormatText->RightButton->Enabled = false;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkDelOrgFileClick(TObject *Sender)
{

//'�Í���������A���t�@�C��/�t�H���_�[���폜����(&D)';
DeleteGroupEnabled();

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkDelEncFileClick(TObject *Sender)
{

//'����������A�Í����t�@�C�����폜����(&E)';
DeleteGroupEnabled();

}
//---------------------------------------------------------------------------
void __fastcall TForm3::chkShowDeleteChkBoxClick(TObject *Sender)
{

//'���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������(&I)';
DeleteGroupEnabled();

}
//---------------------------------------------------------------------------
//�u'�폜�̏ڍאݒ�F'�v�O���[�v�{�b�N�X���̗L���E�����𐧌䂷��
bool __fastcall TForm3::DeleteGroupEnabled(void)
{

if ( chkDelOrgFile->Checked == true || chkDelEncFile->Checked == true || chkDelEncFile->Checked == true ) {

	gbDeleteOption->Enabled = true;
	optNormalDelete->Enabled = true;
	optGoToTrash->Enabled = true;
	optCompleteDelete->Enabled = true;
	txtDelRandNum->Color = clWindow;
	txtDelZeroNum->Color = clWindow;
	imgArrowEnabled->Visible = true;
	imgArrowDiabled->Visible = false;
	return(true);
}
else{
	gbDeleteOption->Enabled = false;
	optNormalDelete->Enabled = false;
	optGoToTrash->Enabled = false;
	optCompleteDelete->Enabled = false;
	txtDelRandNum->Color = clBtnFace;
	txtDelZeroNum->Color = clBtnFace;
	imgArrowEnabled->Visible = false;
	imgArrowDiabled->Visible = true;
	return(false);
}

}
//---------------------------------------------------------------------------
// DragOver �C�x���g�̃R�[���o�b�N�֐�
//---------------------------------------------------------------------------
void __fastcall TForm3::FilesDragOver(POINTL ptl)
{

int px, py, pr, pb;

TRect rcResult;
TRect rcMouse = TRect(ptl.x-1, ptl.y-1, ptl.x+1, ptl.y+1);   //�}�E�X�ʒu
TRect rcTarget;

//-----------------------------------
// �y��{�ݒ�z
//-----------------------------------
if ( PageControl1->ActivePage == TabBasic ){

	//-----------------------------------
	//�Í����p�X���[�h���L�����邩�i�`�F�b�N�{�b�N�X�A�e�L�X�g�{�b�N�X�ɂ������Ă��邩�j
	px = chkMyEncPasswordKeep->Left;
	py = chkMyEncPasswordKeep->Top;
	pr = btneditMyEncPassword->BoundsRect.Right;
	pb = btneditMyEncPassword->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
		btneditMyEncPassword->Color = TColor(0xDBEBF7);  //�I�����W�F
	}
	else{
		btneditMyEncPassword->Color = clBtnFace;
	}

	//-----------------------------------
	//�����p�X���[�h���L�����邩�i�`�F�b�N�{�b�N�X�A�e�L�X�g�{�b�N�X�ɂ������Ă��邩�j
	px = chkMyDecPasswordKeep->Left;
	py = chkMyDecPasswordKeep->Top;
	pr = btneditMyDecPassword->BoundsRect.Right;
	pb = btneditMyDecPassword->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
		btneditMyDecPassword->Color = TColor(0xDBEBF7);  //�I�����W�F
	}
	else{
		btneditMyDecPassword->Color = clBtnFace;
	}

}
//-----------------------------------
// �y�ۑ��ݒ�z
//-----------------------------------
else if ( PageControl1->ActivePage == TabSave ){

	//-----------------------------------
	//'��ɓ����ꏊ�ֈÍ����t�@�C����ۑ�����(&C)'
	px = chkSaveToSameFldr->Left;
	py = chkSaveToSameFldr->Top;
	pr = btneditSaveToSameFldrPath->BoundsRect.Right;
	pb = btneditSaveToSameFldrPath->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
		btneditSaveToSameFldrPath->Color = TColor(0xDBEBF7);  //�I�����W�F
	}
	else{
		if ( chkSaveToSameFldr->Checked == true ) {
			btneditSaveToSameFldrPath->Color = clWindow;
		}
		else{
			btneditSaveToSameFldrPath->Color = clBtnFace;
		}
	}

	//-----------------------------------
	//'��ɓ����ꏊ�փt�@�C���𕜍�����(&D)'
	px = chkDecodeToSameFldr->Left;
	py = chkDecodeToSameFldr->Top;
	pr = btneditDecodeToSameFldrPath->BoundsRect.Right;
	pb = btneditDecodeToSameFldrPath->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
		btneditDecodeToSameFldrPath->Color = TColor(0xDBEBF7);  //�I�����W�F
	}
	else{
		if ( chkDecodeToSameFldr->Checked == true ) {
			btneditDecodeToSameFldrPath->Color = clWindow;
		}
		else{
			btneditDecodeToSameFldrPath->Color = clBtnFace;
		}
	}

}
//-----------------------------------
// �y���x�Ȑݒ�z
//-----------------------------------
else if ( PageControl1->ActivePage == TabAdvanced ){

	//-----------------------------------
	//'�Í������Ƀp�X���[�h�t�@�C���������`�F�b�N����(&H)'
	px = gbPasswordFile->Left + chkCheckPassFile->Left;
	py = gbPasswordFile->Top + chkCheckPassFile->Top;
	pr = gbPasswordFile->Left + btneditDecodeToSameFldrPath->BoundsRect.Right;
	pb = gbPasswordFile->Top + btneditDecodeToSameFldrPath->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
		btneditPassFilePath->Color = TColor(0xDBEBF7);  //�I�����W�F
	}
	else{
		if ( chkCheckPassFile->Checked == true ) {
			btneditPassFilePath->Color = clWindow;
		}
		else{
			btneditPassFilePath->Color = clBtnFace;
		}
	}

	//-----------------------------------
	//'�������Ƀp�X���[�h�t�@�C���������`�F�b�N����(&K)';
	px = gbPasswordFile->Left + chkCheckPassFileDecrypt->Left;
	py = gbPasswordFile->Top + chkCheckPassFileDecrypt->Top;
	pr = gbPasswordFile->Left + btneditPassFilePathDecrypt->BoundsRect.Right;
	pb = gbPasswordFile->Top + btneditPassFilePathDecrypt->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
		btneditPassFilePathDecrypt->Color = TColor(0xDBEBF7);  //�I�����W�F
	}
	else{
		if ( chkCheckPassFileDecrypt->Checked == true ) {
			btneditPassFilePathDecrypt->Color = clWindow;
		}
		else{
			btneditPassFilePathDecrypt->Color = clBtnFace;
		}
	}
	//-----------------------------------

}


}
//---------------------------------------------------------------------------
// DragLeave �C�x���g�̃R�[���o�b�N�֐�
//---------------------------------------------------------------------------
void __fastcall TForm3::FilesDragLeave(void)
{

//-----------------------------------
// �y��{�ݒ�z
//-----------------------------------
if ( PageControl1->ActivePage == TabBasic ){

	if ( chkMyEncPasswordKeep->Checked == true ) {
		btneditMyEncPassword->ReadOnly = false;
		btneditMyEncPassword->Color = clWindow;
	}
	else{
		btneditMyEncPassword->ReadOnly = true;
		btneditMyEncPassword->Color = clBtnFace;
	}

	if ( chkMyDecPasswordKeep->Checked == true ) {
		btneditMyDecPassword->ReadOnly = false;
		btneditMyDecPassword->Color = clWindow;
	}
	else{
		btneditMyDecPassword->ReadOnly = true;
		btneditMyDecPassword->Color = clBtnFace;
	}

}
//-----------------------------------
// �y�ۑ��ݒ�z
//-----------------------------------
else if ( PageControl1->ActivePage == TabSave ){

	if ( chkSaveToSameFldr->Checked == true ) {
		btneditSaveToSameFldrPath->ReadOnly = false;
		btneditSaveToSameFldrPath->Color = clWindow;
	}
	else{
		btneditSaveToSameFldrPath->ReadOnly = true;
		btneditSaveToSameFldrPath->Color = clBtnFace;
	}

	if ( chkDecodeToSameFldr->Checked == true ) {
		btneditDecodeToSameFldrPath->ReadOnly = false;
		btneditDecodeToSameFldrPath->Color = clWindow;
	}
	else{
		btneditDecodeToSameFldrPath->ReadOnly = true;
		btneditDecodeToSameFldrPath->Color = clBtnFace;
	}

}
//-----------------------------------
// �y���x�Ȑݒ�z
//-----------------------------------
else if ( PageControl1->ActivePage == TabAdvanced ){

	//�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
	if ( chkCheckPassFile->Checked == true ){
		//cmdSelectPassFolder->Glyph = imgFolder->Picture->Bitmap;
		btneditPassFilePath->ReadOnly = false;
		btneditPassFilePath->Color = clWindow;
	}
	else{
		//cmdSelectPassFolder->Glyph = imgNoFolder->Picture->Bitmap;
		btneditPassFilePath->ReadOnly = true;
		btneditPassFilePath->Color = clBtnFace;
	}

	//�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
	if ( chkCheckPassFileDecrypt->Checked == true ){
		//cmdSelectPassFolderDecrypt->Glyph = imgFolder->Picture->Bitmap;
		btneditPassFilePathDecrypt->ReadOnly = false;
		btneditPassFilePathDecrypt->Color = clWindow;
	}
	else{
		//cmdSelectPassFolderDecrypt->Glyph = imgNoFolder->Picture->Bitmap;
		btneditPassFilePathDecrypt->ReadOnly = true;
		btneditPassFilePathDecrypt->Color = clBtnFace;
	}

}


}
//---------------------------------------------------------------------------
// DragEnd �C�x���g�̃R�[���o�b�N�֐�
//---------------------------------------------------------------------------
void __fastcall TForm3::FilesDragEnd(POINTL ptl, String FileListText)
{

TStringList *FileList = new TStringList;
FileList->Text = FileListText;

int res;
String MsgText;
AnsiString SHA1HashPassword;

TColor tmpColor;
TForm* dialog;

int px, py, pr, pb;

TRect rcResult;
TRect rcMouse = TRect(ptl.x-1, ptl.y-1, ptl.x+1, ptl.y+1); //�}�E�X�ʒu�i�����ɂ߂ɐݒ�j
TRect rcTarget;

String FilePath;

//-----------------------------------
//�����t�@�C���̃h���b�v�������Ȃ�
if ( FileList->Count > 0 ) {
	FilePath = FileList->Strings[0];
}
else{
	return;
}


//-----------------------------------
// �y��{�ݒ�z
//-----------------------------------
if ( PageControl1->ActivePage == TabBasic ){

	//-----------------------------------
	//�Í����p�X���[�h���L�����邩�i�`�F�b�N�{�b�N�X�A�e�L�X�g�{�b�N�X�ɂ������Ă��邩�j
	px = chkMyEncPasswordKeep->Left;
	py = chkMyEncPasswordKeep->Top;
	pr = btneditMyEncPassword->BoundsRect.Right;
	pb = btneditMyEncPassword->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {

		if ( chkAllowPassFile->Checked == false ) {
			//'�p�X���[�h�t�@�C�����g�p����ɂ́y���x�ݒ�z�^�u��'+#13+
			//'�u�p�X���[�h�t�@�C���Ƀt�@�C���̎w���������(&D)�v��L���ɂ��Ă��������B';
			MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_ALLOW_PASSWORD_FILE_OPTION);
			MessageDlg(MsgText, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
			return;
		}

		tmpColor = btneditMyEncPassword->Color;
		btneditMyEncPassword->Color = TColor(0xDBEBF7);  //�I�����W�F�ɂ��ċ���

		// '�h���b�O���h���b�v���ꂽ�t�@�C����SHA-1�n�b�V���l��'+#13+
		//'�Í����p�X���[�h�Ƃ��ċL�����܂��B��낵���ł����H';
		MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_MEM_ENCRYPT_PASSWORD_HASH)+"\n"+
							FilePath;
		dialog = CreateMessageDialog(MsgText, mtConfirmation, TMsgDlgButtons()<<mbYes<<mbNo, mbNo);
		dialog->Caption = LoadResourceString(&Msgunit3::_MSG_CAPTION_CONFIRMATION);	//'�m�F'

		if (dialog->ShowModal() == ID_NO){
			btneditMyEncPassword->Color = tmpColor;        //���̐F�ɖ߂�
			delete dialog;
			return;
		}
		else{
			delete dialog;
		}

		//SHA-1�n�b�V�������߂�
		if ( Form1->opthdl->GetSHA1HashFromFile(
			FilePath, (unsigned char*)NULL, SHA1HashPassword, (AnsiString)NULL) == true ){
			//���̋L���Í����p�X���[�h
			TempMyEncodePassword = SHA1HashPassword;
			btneditMyEncPassword->Text = String::StringOfChar('*', 32);
			chkMyEncPasswordKeep->OnClick = NULL;
			chkMyEncPasswordKeep->Checked = true;
			chkMyEncPasswordKeep->OnClick = chkMyEncPasswordKeepClick;
		}

	}

	//-----------------------------------
	//�����p�X���[�h���L�����邩�i�`�F�b�N�{�b�N�X�A�e�L�X�g�{�b�N�X�ɂ������Ă��邩�j
	//-----------------------------------
	px = chkMyDecPasswordKeep->Left;
	py = chkMyDecPasswordKeep->Top;
	pr = btneditMyDecPassword->BoundsRect.Right;
	pb = btneditMyDecPassword->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {

		if ( chkAllowPassFile->Checked == false ) {
			//'�p�X���[�h�t�@�C�����g�p����ɂ́y���x�ݒ�z�^�u��'+#13+
			//'�u�p�X���[�h�t�@�C���Ƀt�@�C���̎w���������(&D)�v��L���ɂ��Ă��������B';
			MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_ALLOW_PASSWORD_FILE_OPTION);
			MessageDlg(MsgText, mtConfirmation, TMsgDlgButtons()<<mbOK, 0);
			return;
		}

		tmpColor = btneditMyDecPassword->Color;
		btneditMyDecPassword->Color = TColor(0xDBEBF7);  //�I�����W�F�ɂ��ċ���

		//'�h���b�O���h���b�v���ꂽ�t�@�C����SHA-1�n�b�V���l��'+#13+
		//'��������p�X���[�h�Ƃ��ċL�����܂��B��낵���ł����H';
		MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_MEM_DECRYPT_PASSWORD_HASH)+"\n"+
							FilePath;
		dialog = CreateMessageDialog(MsgText, mtConfirmation, TMsgDlgButtons()<<mbYes<<mbNo, mbNo);
		dialog->Caption = LoadResourceString(&Msgunit3::_MSG_CAPTION_CONFIRMATION);	//'�m�F'


		if (dialog->ShowModal() == ID_NO){
			btneditMyDecPassword->Color = tmpColor;        //���̐F�ɖ߂�
			delete dialog;
			return;
		}
		else{
			delete dialog;
		}

		//SHA-1�n�b�V�������߂�
		if ( Form1->opthdl->GetSHA1HashFromFile(
			FilePath, (unsigned char*)NULL, SHA1HashPassword, (AnsiString)NULL) == true ){
			//���̋L���Í����p�X���[�h
			TempMyDecodePassword = SHA1HashPassword;
			btneditMyDecPassword->Text = String::StringOfChar('*', 32);
			chkMyDecPasswordKeep->OnClick = NULL;
			chkMyDecPasswordKeep->Checked = true;
			chkMyDecPasswordKeep->OnClick = chkMyDecPasswordKeepClick;
		}

	}
}
//-----------------------------------
// �y�ۑ��ݒ�z
//-----------------------------------
else if ( PageControl1->ActivePage == TabSave ){

	//-----------------------------------
	//'��ɓ����ꏊ�ֈÍ����t�@�C����ۑ�����(&C)'
	px = chkSaveToSameFldr->Left;
	py = chkSaveToSameFldr->Top;
	pr = btneditSaveToSameFldrPath->BoundsRect.Right;
	pb = btneditSaveToSameFldrPath->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if ( IntersectRect(rcResult, rcMouse, rcTarget) == true ) {

		if (FileExists(FilePath) == true ) {
			chkSaveToSameFldr->Checked = true;
			btneditSaveToSameFldrPath->Text = ExtractFileDir(FilePath);
			btneditSaveToSameFldrPath->SetFocus();
		}
		else if ( DirectoryExists(FilePath) == true ){
			chkSaveToSameFldr->Checked = true;
			btneditSaveToSameFldrPath->Text = FilePath;
			btneditSaveToSameFldrPath->SetFocus();
		}

	}

	//-----------------------------------
	//'��ɓ����ꏊ�փt�@�C���𕜍�����(&D)'
	px = chkDecodeToSameFldr->Left;
	py = chkDecodeToSameFldr->Top;
	pr = btneditDecodeToSameFldrPath->BoundsRect.Right;
	pb = btneditDecodeToSameFldrPath->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if ( IntersectRect(rcResult, rcMouse, rcTarget) == true ) {

		if ( FileExists(FilePath) == true ) {
			chkDecodeToSameFldr->Checked = true;
			btneditDecodeToSameFldrPath->Text = ExtractFileDir(FilePath);
			btneditDecodeToSameFldrPath->SetFocus();
		}
		else if ( DirectoryExists(FilePath) == true ){
			chkDecodeToSameFldr->Checked = true;
			btneditDecodeToSameFldrPath->Text = FilePath;
			btneditDecodeToSameFldrPath->SetFocus();
		}

	}

}
//-----------------------------------
// �y���x�Ȑݒ�z
//-----------------------------------
else if ( PageControl1->ActivePage == TabAdvanced ){

	//-----------------------------------
	//'�Í������Ƀp�X���[�h�t�@�C���������`�F�b�N����(&H)'
	px = gbPasswordFile->Left + chkCheckPassFile->Left;
	py = gbPasswordFile->Top + chkCheckPassFile->Top;
	pr = gbPasswordFile->Left + btneditPassFilePath->BoundsRect.Right;
	pb = gbPasswordFile->Top + btneditPassFilePath->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if ( IntersectRect(rcResult, rcMouse, rcTarget) == true ) {

		if ( chkAllowPassFile->Checked == false || chkCheckPassFile->Checked == false) {

			tmpColor = btneditMyDecPassword->Color;
			btneditPassFilePath->Color = TColor(0xDBEBF7);  //�I�����W�F�ɂ��ċ���

			//'�p�X���[�h�t�@�C�����Ƀt�@�C�����h���b�O���h���b�v����܂����B'+#13+
			//'�Í������Ɏg���p�X���[�h�t�@�C���Ƃ��ēo�^���ėL���ɂ��܂����H';
			MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_ALLOW_ENCRYPT_PASSWORD_FILE_ENABLED);
			res = MessageDlg(MsgText, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);

			if ( res == mrNo ) {
				btneditPassFilePath->Color = tmpColor;        //���̐F�ɖ߂�
				return;
			}
		}

		if ( FileExists(FilePath) == true ) {
			btneditPassFilePath->Text = FilePath;
			chkAllowPassFile->Checked = true;
			chkCheckPassFile->OnClick = NULL;
			chkCheckPassFile->Checked = true;
			chkCheckPassFile->OnClick = chkCheckPassFileClick;
			btneditPassFilePath->SetFocus();
		}
		else{
			//'�L���ȃt�@�C���i���Ƃ��΃f�B���N�g���Ȃǁj�ȊO�͓o�^���邱�Ƃ��ł��܂���B'
			MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_ERROR_PASSWORD_FILE_WRONG)+"\n"+
								FilePath;
			MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
			btneditPassFilePath->Color = tmpColor;        //���̐F�ɖ߂�
			return;
		}

	}

	//-----------------------------------
	//'�������Ƀp�X���[�h�t�@�C���������`�F�b�N����(&K)';
	px = gbPasswordFile->Left + chkCheckPassFileDecrypt->Left;
	py = gbPasswordFile->Top + chkCheckPassFileDecrypt->Top;
	pr = gbPasswordFile->Left + btneditPassFilePathDecrypt->BoundsRect.Right;
	pb = gbPasswordFile->Top + btneditPassFilePathDecrypt->BoundsRect.Bottom;
	rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

	if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {

		if ( chkAllowPassFile->Checked == false || chkCheckPassFileDecrypt->Checked == false) {

			tmpColor = btneditPassFilePathDecrypt->Color;
			btneditPassFilePathDecrypt->Color = TColor(0xDBEBF7);  //�I�����W�F�ɂ��ċ���

			//'�p�X���[�h�t�@�C�����Ƀt�@�C�����h���b�O���h���b�v����܂����B'+#13+
			//'�������Ɏg���p�X���[�h�t�@�C���Ƃ��ēo�^���ėL���ɂ��܂����H';
			MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_ALLOW_DECRYPT_PASSWORD_FILE_ENABLED);
			res = MessageDlg(MsgText, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);

			if ( res == mrNo ) {
				btneditPassFilePathDecrypt->Color = tmpColor;        //���̐F�ɖ߂�
				return;
			}
		}

		if ( FileExists(FilePath) == true ) {
			btneditPassFilePathDecrypt->Text = FilePath;
			chkAllowPassFile->Checked = true;
			chkCheckPassFileDecrypt->OnClick = NULL;
			chkCheckPassFileDecrypt->Checked = true;
			chkCheckPassFileDecrypt->OnClick = chkCheckPassFileDecryptClick;
			btneditPassFilePathDecrypt->SetFocus();
		}
		else{
			//'�L���ȃt�@�C���i���Ƃ��΃f�B���N�g���Ȃǁj�ȊO�͓o�^���邱�Ƃ��ł��܂���B'
			MsgText = LoadResourceString(&Msgunit3::_DIALOG_MSG_ERROR_PASSWORD_FILE_WRONG)+"\n"+
								FilePath;
			MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
			btneditPassFilePathDecrypt->Color = tmpColor;        //���̐F�ɖ߂�
			return;
		}

	}
	//-----------------------------------

}


}
//---------------------------------------------------------------------------
void __fastcall TForm3::cmdHelpClick(TObject *Sender)
{

//�J���Ă���y�[�W�ɉ������w���v�t�@�C���̃y�[�W��\��

if ( PageControl1->ActivePage == TabBasic ) {
	Application->HelpContext(IDH_BASIC_OPTION);
}
else if ( PageControl1->ActivePage == TabSave ) {
	Application->HelpContext(IDH_SAVE_OPTION);
}
else if ( PageControl1->ActivePage == TabDelete ) {
	Application->HelpContext(IDH_DELETE_OPTION);
}
else if ( PageControl1->ActivePage == TabMovement ) {
	Application->HelpContext(IDH_MOVEMENT_OPTION);
}
else if ( PageControl1->ActivePage == TabSystem ) {
	Application->HelpContext(IDH_SYSTEM_OPTION);
}
else if ( PageControl1->ActivePage == TabAdvanced ) {
	Application->HelpContext(IDH_ADVANCED_OPTION);
}
else {

}

}
//---------------------------------------------------------------------------

