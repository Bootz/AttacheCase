//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TDragAndDrop *DragAndDropTarget;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

//�p�X���[�h�̏�����
for (int i = 0; i < 32; i++) {
	password_hash[i] = 0;
}

txtInputPassword->Text = "";

this->Caption = ExtractFileName(Application->ExeName);

lblMsgInputPassword->Caption = LoadResourceString(&Msgexeout::_LABEL_CAPTION_INPUT_PASSWORD);
lblAbout->Caption = LoadResourceString(&Msgexeout::_LABEL_CAPTION_ABOUT);

chkSaveToOtherDirectory->Caption = LoadResourceString(&Msgexeout::_CHECK_BOX_SAVE_TO_OTHER_DIRECTORY);

cmdOK->Caption = LoadResourceString(&Msgexeout::_BUTTON_CAPTION_DECRYOTION);
cmdExit->Caption = LoadResourceString(&Msgexeout::_BUTTON_CAPTION_CANCEL);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{

//-----------------------------------
//OLE�h���b�O���h���b�v�̌�n��
//-----------------------------------
RevokeDragDrop(Form1->Handle);
DragAndDropTarget->Release();
OleUninitialize();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{

//-----------------------------------
//�h���b�O���h���b�v�N���X
//-----------------------------------
OleInitialize(NULL);
//Form��Create���Ă���łȂ��ƌĂяo���Ȃ�
DragAndDropTarget = new TDragAndDrop(Form1);
DragAndDropTarget->FilesDragOver = FilesDragOver;
DragAndDropTarget->FilesDragLeave = FilesDragLeave;
DragAndDropTarget->FilesDragEnd = FilesDragEnd;
RegisterDragDrop(Form1->Handle, (IDropTarget*)DragAndDropTarget);

}
//---------------------------------------------------------------------------
//�t�H�[���̃��T�C�Y�C�x���g
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{

txtInputPassword->Top = this->ClientHeight/2 - txtInputPassword->Height;

ProgressBar1->Top = txtInputPassword->Top;
lblProgressPercentNum->Top = ProgressBar1->BoundsRect.Bottom + 1;
lblStatus->Top = ProgressBar1->Top - lblStatus->Height - 1;
lblMsg->Top = lblStatus->Top - lblMsg->Height - 1;

imgKeyIcon->Top = txtInputPassword->Top + txtInputPassword->Height/2 - imgKeyIcon->Height/2;
chkSaveToOtherDirectory->Top = ProgressBar1->BoundsRect.Bottom + 4;
lblMsgInputPassword->Top = txtInputPassword->Top - lblMsgInputPassword->Height - 8;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{

if ( Key == VK_ESCAPE ) {
	Close();
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdExitClick(TObject *Sender)
{

if (ProgressBar1->Visible == true) {
	if (ProgressBar1->Position == 100 || ProgressBar1->Position == 0) {
		ChangeFormStatus(0);  //���C���t�H�[���֖߂�
		return;
	}
	else{
		if (decrypt != NULL) {
			decrypt->Terminate();
			return;
		}
		else{
			ChangeFormStatus(0);  //���C���t�H�[���֖߂�
			return;
		}
	}
}
else{
	Close();
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::lblAboutMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
lblAbout->Font->Color = TColor(0x00CC0000);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lblAboutMouseLeave(TObject *Sender)
{
lblAbout->Font->Color = TColor(0x00FF9999);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lblAboutClick(TObject *Sender)
{

//�o�[�W�������̕\��
Form2 = new TForm2(this);
Form2->PopupParent = Form1;
Form2->ShowModal();
Form2->Release();

}
//---------------------------------------------------------------------------
// DragOver �C�x���g�̃R�[���o�b�N�֐�
//---------------------------------------------------------------------------
void __fastcall TForm1::FilesDragOver(POINTL ptl)
{

int px, py, pr, pb;
TRect rcResult;
TRect rcMouse = TRect(ptl.x-1, ptl.y-1, ptl.x+1, ptl.y+1);   //�}�E�X�ʒu
TRect rcTarget;

DragAndDropTarget->fMultipleFilesOk = false;
DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

//�p�X���[�h���̓{�b�N�X
px = txtInputPassword->Left;
py = txtInputPassword->Top;
pr = txtInputPassword->BoundsRect.Right;
pb = txtInputPassword->BoundsRect.Bottom;
rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
	txtInputPassword->Color = TColor(0xDBEBF7);  //�I�����W�F
}
else{
	txtInputPassword->Color = clWindow;
}


}
//---------------------------------------------------------------------------
// DragLeave �C�x���g�̃R�[���o�b�N�֐�
//---------------------------------------------------------------------------
void __fastcall TForm1::FilesDragLeave(void)
{

txtInputPassword->Color = clWindow;

}
//---------------------------------------------------------------------------
// DragEnd �C�x���g�̃R�[���o�b�N�֐�
//---------------------------------------------------------------------------
void __fastcall TForm1::FilesDragEnd(POINTL ptl, String FileListText)
{

int px, py, pr, pb;
TRect rcResult;
TRect rcMouse = TRect(ptl.x-1, ptl.y-1, ptl.x+1, ptl.y+1);   //�}�E�X�ʒu
TRect rcTarget;

String MsgText;
unsigned char *sha1hash;

String SHA1HashPassword = "";
TStringList *DropFileList = new TStringList;
DropFileList->Text = FileListText;

DragAndDropTarget->fMultipleFilesOk = false;
DragAndDropTarget->DropImageType =DROPIMAGE_COPY;

//�p�X���[�h���̓{�b�N�X
px = txtInputPassword->Left;
py = txtInputPassword->Top;
pr = txtInputPassword->BoundsRect.Right;
pb = txtInputPassword->BoundsRect.Bottom;
rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

if (IntersectRect(rcResult, rcMouse, rcTarget) == true && DropFileList->Count > 0) {

	txtInputPassword->Color = TColor(0xDBEBF7);  //�I�����W�F

	//SHA-1�n�b�V�������߂�
	if ( GetSHA1HashFromFile(	DropFileList->Strings[0], password_hash ) == true ){
		FileDecrypt();
	}
	else{
		//'�p�X���[�h�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
		MsgText = LoadResourceString(&Msgexeout::_MSG_ERROR_OPEN_PASSWORD_FILE)+"\n"+
																 DropFileList->Strings[0];
		MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
	}
}

txtInputPassword->Color = clWindow;
delete DropFileList;

}
//---------------------------------------------------------------------------
// �t�H�[����Ԃ̐؂�ւ�
//---------------------------------------------------------------------------
void __fastcall TForm1::ChangeFormStatus(int opt)
{

if (opt == 1) {                        //���s��
	//�t�H�[�������s��Ԃɂ���
	lblMsgInputPassword->Visible = false;
	txtInputPassword->Visible = false;
	imgKeyIcon->Visible = false;
	chkSaveToOtherDirectory->Visible = false;
	//�v���O���X�o�[�֘A�̕\��
	ProgressBar1->Visible = true;
	lblProgressPercentNum->Visible = true;
	lblStatus->Visible = true;
	lblMsg->Visible = true;
}
else{                                  //���C���\��
	//�p�X���[�h���̓{�b�N�X�̕\��
	lblMsgInputPassword->Visible = true;
	txtInputPassword->Visible = true;
	imgKeyIcon->Visible = true;
	chkSaveToOtherDirectory->Visible = true;
	//�v���O���X�o�[�֘A�̕\��������
	ProgressBar1->Visible = false;
	lblProgressPercentNum->Visible = false;
	lblStatus->Visible = false;
	lblMsg->Visible = false;
}

}
//---------------------------------------------------------------------------
// �t�@�C���𕜍����鏈��
//---------------------------------------------------------------------------
void __fastcall TForm1::FileDecrypt(void)
{

int i;
String MsgText;

String AtcFilePath;
String OutDirPath;
String RootDirPath = ExtractFileDir(Application->ExeName);

TSelectDirExtOpts opt;

//�t�H�[�������s����Ԃɂ���
ChangeFormStatus(1);

//�e�t�H���_�𐶐����Ȃ�
//if ( fNoParentFldr == true  )

if ( chkSaveToOtherDirectory->Checked == true ) {

	opt = TSelectDirExtOpts() << sdShowShares << sdNewUI << sdNewFolder << sdShowEdit << sdValidateDir;
	// '���������̃t�H���_�[���w�肵�Ă��������B'
	if (SelectDirectory(LoadResourceString(&Msgexeout::_DIALOG_MSG_SELECT_SAVE_TO_FOLDER),
			RootDirPath, OutDirPath, opt, this) == false){
		return;
	}

}
else{
	OutDirPath = ExtractFileDir(Application->ExeName);
}


if ( DirectoryExists(OutDirPath) == false ) {
	//'�ۑ������̃t�H���_�[��������܂���B�ۑ��ݒ���Ċm�F���Ă��������B'+#13+
	//'�����������𒆎~���܂��B';
	MsgText = LoadResourceString(&Msgexeout::_MSG_ERROR_SAVE_DEC_TO_FOLDER_NOT_EXISTS)+"\n"+
						OutDirPath;
	MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
	//�G���[�I���\��
	ProgressBar1->Position = 0;
	lblProgressPercentNum->Caption = " - %";
	//'�L�����Z��'
	lblStatus->Caption = LoadResourceString(&Msgexeout::_LABEL_STATUS_TITLE_USER_CANCEL);
	//'���������~����܂����B'
	lblMsg->Caption = LoadResourceString(&Msgexeout::_LABEL_STATUS_DETAIL_STOPPED);
	return;
}

//-----------------------------------
// ���������̊J�n
//-----------------------------------

//���������C���X�^���X�̍쐬
decrypt = new TAttacheCaseFileDecrypt2(true);
decrypt->OnTerminate = DecryptThreadTerminated;
decrypt->FreeOnTerminate = true;
decrypt->AppExeFilePath = Application->ExeName;  //�A�^�b�V�F�P�[�X�{�̂̏ꏊ�i���s�`���o�͂̂Ƃ��ɎQ�Ƃ���j
decrypt->AtcFilePath = Application->ExeName;     //���͂���Í����t�@�C���p�X�i�������g�j
decrypt->OutDirPath = OutDirPath;                //�o�͂���f�B���N�g��

//-----------------------------------
//�p�X���[�h�̃Z�b�g
//-----------------------------------

//�p�X���[�h�t�@�C�����g�p����
if (password_hash[0] != 0) {
	//�o�C�i���l�ŃZ�b�g
	decrypt->SetPasswordBinary(password_hash);
}
else{
	//��������Z�b�g
	decrypt->SetPasswordString(txtInputPassword->Text);
}

//�����̎��s
decrypt->Start();

//�^�X�N�o�[�i���\���iWin7�j
if(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&ptl) != S_OK) {
	//���s
}
if (ptl) ptl->SetProgressState(Application->Handle, TBPF_NORMAL);

//�i����Timer�ŊĎ�
TimerDecrypt->Enabled = true;



}
//---------------------------------------------------------------------------
// �t�@�C������SHA-1�n�b�V���l���擾����
//---------------------------------------------------------------------------
bool __fastcall TForm1::GetSHA1HashFromFile(String FilePath, unsigned char *sha1buffer)
{

int i;

int fh;
int bytes;
char buffer[READ_FILE_BUF_SIZE];
char sha1_hash_string[BUF_SHA1_SIZE];

if ( !FileExists(FilePath) ){
 return(false);
}

if ( (fh = FileOpen(FilePath, fmShareDenyNone)) == -1 ){
	//�p�X���[�h�t�@�C�����J���Ȃ��H
	return(false);
}

SHA1Context sha;
unsigned char Message_Digest[BUF_SHA1_SIZE];
ZeroMemory(Message_Digest, BUF_SHA1_SIZE);

//�������i���Z�b�g�j
if ( SHA1Reset(&sha)){
	FileClose(fh);
	return(false);
}

//�t�@�C����ǂݏo����SHA-1�֓��͂��Ă���
while ((bytes = FileRead (fh, buffer, READ_FILE_BUF_SIZE)) != 0){
	if ( SHA1Input(&sha, (const unsigned char *)buffer, bytes) ){
		FileClose(fh);
		return(false);
	}
}

//�o��
if(SHA1Result(&sha, Message_Digest)){
	FileClose(fh);
	return(false);
}

//�t�@�C�������
FileClose(fh);

for (i = 0; i < BUF_SHA1_SIZE; i++){
	sha1buffer[i] = Message_Digest[i];
	sha1_hash_string[i] = Message_Digest[i];
}

return(true);


}
//---------------------------------------------------------------------------
//���������X���b�h�̏I��
//---------------------------------------------------------------------------
void __fastcall TForm1::DecryptThreadTerminated(TObject *Sender)
{

ProgressBar1->Style = pbstNormal;
ProgressBar1->Position = decrypt->ProgressPercentNum;
lblProgressPercentNum->Caption = IntToStr(decrypt->ProgressPercentNum)+"%";
lblStatus->Caption = decrypt->ProgressStatusText;
lblMsg->Caption = decrypt->ProgressMsgText;

if(ptl){
	ptl->SetProgressValue(Application->Handle, 100, 100);
	ptl->Release();
	ptl = NULL;
}

/*
�yToDo�z
�p�X���[�h���܂������ē��͂����Ƃ��̉񐔐�����
�j��̃��[�`���������Ă��Ȃ��B
*/


//�����ɐ���
decrypt = NULL;

TimerDecrypt->Enabled = false;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdOKClick(TObject *Sender)
{

//�����J�n
FileDecrypt();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerDecryptTimer(TObject *Sender)
{

//�����̐i���󋵂��m�F����

if (decrypt != NULL) {
	ProgressBar1->Position = decrypt->ProgressPercentNum;
	lblProgressPercentNum->Caption = IntToStr(decrypt->ProgressPercentNum)+"%";

	lblStatus->Caption = decrypt->ProgressStatusText;
	lblMsg->Caption = decrypt->ProgressMsgText;

	//�^�X�N�o�[�i���\���iWin7�j
	if(ptl){
		ptl->SetProgressValue(Application->Handle, decrypt->ProgressPercentNum, 100);
	}
}
else{
	TimerDecrypt->Enabled = false;
}

}
//---------------------------------------------------------------------------
//���b�Z�[�W�_�C�A���O�̕\���i�X���b�h�I�u�W�F�N�g����Ă΂��j
//---------------------------------------------------------------------------
int __fastcall TForm1::ShowConfirmMassageForm
	(String MsgText, TMsgDlgType MsgType, TMsgDlgButtons MsgButtons, TMsgDlgBtn MsgDefaultButton)
{

TForm *dlg = CreateMessageDialog(MsgText, MsgType, MsgButtons, MsgDefaultButton);
dlg->ParentWindow = Form1->Handle;

if ( MsgType == mtError) {
	dlg->Caption = LoadResourceString(&Msgexeout::_MSG_CAPTION_ERROR);
}
else {
	dlg->Caption = LoadResourceString(&Msgexeout::_MSG_CAPTION_CONFIRMATION);
}

//���b�Z�[�W�_�C�A���O�̕\��
int ret = dlg->ShowModal();
delete dlg;
return(ret);

}
//---------------------------------------------------------------------------
//�㏑���m�F���b�Z�[�W�_�C�A���O�̕\���i�����X���b�h�I�u�W�F�N�g����Ă΂��j
//---------------------------------------------------------------------------
int __fastcall TForm1::ShowConfirmOverwriteMassageForm(String MsgText, String &Path)
{

//�{�^�����J�X�^�}�C�Y����̂ŏ�L�֐��ƕ����č쐬

TButton *btn;
TMsgDlgButtons MsgButtons = (TMsgDlgButtons() << mbYesToAll << mbYes << mbNo << mbCancel);
TForm *dlg = CreateMessageDialog(MsgText, mtConfirmation, MsgButtons, mbCancel);

//�{�^���������ꂼ�ꏑ��������
btn = (TButton *)dlg->FindComponent("YesToAll");   //'�S�ď㏑��(&W)'
btn->Caption = LoadResourceString(&Msgexeout::_DIALOG_BUTTON_NAME_OVERWITE_YES_TO_ALL);
btn = (TButton *)dlg->FindComponent("Yes");        //'�㏑��(&O)'
btn->Caption = LoadResourceString(&Msgexeout::_DIALOG_BUTTON_NAME_OVERWITE_YES);
btn = (TButton *)dlg->FindComponent("No");         //'�ʖ��ۑ�(&A)'
btn->Caption = LoadResourceString(&Msgexeout::_DIALOG_BUTTON_NAME_OVERWITE_NO);
btn = (TButton *)dlg->FindComponent("Cancel");     //'�L�����Z��(&C)'
btn->Caption = LoadResourceString(&Msgexeout::_DIALOG_BUTTON_NAME_OVERWITE_CANCEL);

dlg->Caption = LoadResourceString(&Msgexeout::_MSG_CAPTION_CONFIRMATION);
dlg->ParentWindow = Form1->Handle;

//���b�Z�[�W�_�C�A���O�̕\��
int ret = dlg->ShowModal();

if (ret == mrNo) { //�ʖ��ŕۑ�����i�������j

	TSaveDialog *dlgsave = new TSaveDialog(dlg);
	//'�����t�@�C���̕ۑ�'
	dlgsave->Title = LoadResourceString(&Msgexeout::_DIALOG_SAVE_AS_FILE_CAPTION);
	dlgsave->InitialDir = ExtractFileDir(ExcludeTrailingPathDelimiter(Path));
	dlgsave->FileName = ExtractFileName(ExcludeTrailingPathDelimiter(Path));
	//'�t�@�C���t�H���_�[|*'
	dlgsave->Filter = LoadResourceString(&Msgexeout::_DIALOG_SAVE_AS_FILTER);
	//�ʖ��ۑ��_�C�A���O
	if ( dlgsave->Execute() == true ){
		Path = dlgsave->FileName;
	}
	else{
		//�L�����Z��
		ret = mrCancel;
	}
	delete dlgsave;
}

delete dlg;
return(ret);

}
//---------------------------------------------------------------------------



