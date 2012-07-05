//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop



#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "HTMLHelpViewer"

TForm1 *Form1;
TDragAndDrop *DragAndDropTarget;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

int i;

//�y�[�W�R���g���[���̃^�u���\����
PageControl1->Align = alClient;
for (i = 0; i < PageControl1->PageCount; i++) {
	PageControl1->Pages[i]->TabVisible = false;
}
//���C���p�l���\��
PageControl1->ActivePageIndex = 0;

PaintBoxMain->Align = alClient;
PaintBoxEncrypt->Align = alClient;
PaintBoxConfirm->Align = alClient;
PaintBoxDecrypt->Align = alClient;

//����ݒ�C���X�^���X�̍쐬
opthdl = new TAttacheCaseOptionHandle();

//�p�X���[�h�t�@�C���֌W
PasswordFileHeader = "";
PasswordFileHash = "";
for (i = 0; i < 32; i++) {
	password_hash[i] = 0;
	temp_password_hash[i] = 0;
}

//�e�R���|�[�l���g�̔z�u
SetFormComponent(NULL);

String IniFilePath = "";
FileList = new TStringList;

lblMain->Caption = LoadResourceString(&Msgunit1::_DRAG_AND_DROP_HERE);
txtEncryptPassword->EditLabel->Caption = LoadResourceString(&Msgunit1::_INPUT_PASSWORD);
chkExeFileOut->Caption = LoadResourceString(&Msgunit1::_CHECK_BOX_EXEFILE_OUT);
txtPasswordConfirm->EditLabel->Caption = LoadResourceString(&Msgunit1::_CONFIRM_PASSWORD);
chkExeFileOutConf->Caption = LoadResourceString(&Msgunit1::_CHECK_BOX_EXEFILE_OUT);
txtDecryptPassword->EditLabel->Caption = LoadResourceString(&Msgunit1::_INPUT_DECRYPT_PASSWORD);

//-----------------------------------
//�_�C�A���O����
//-----------------------------------

//'�Í�������t�@�C�����J��'
OpenDialogEncrypt->Title = LoadResourceString(&Msgunit1::_DIALOG_OPEN_FILES_FOR_ENCRYPTION_TITLE);
//'���ׂẴt�@�C��(*.*)|*.*'
OpenDialogEncrypt->Filter = LoadResourceString(&Msgunit1::_DIALOG_OPEN_FILES_FOR_ENCRYPTION_FILTER);
//'��������A�^�b�V�F�P�[�X�t�@�C�����J��'
OpenDialogDecrypt->Title = LoadResourceString(&Msgunit1::_DIALOG_OPEN_FILES_FOR_DECRYPTION_TITLE);
//'�A�^�b�V�F�P�[�X�t�@�C��(*.atc)|*.atc|���ׂẴt�@�C��(*.*)|*.*';
OpenDialogDecrypt->Filter = LoadResourceString(&Msgunit1::_DIALOG_OPEN_FILES_FOR_DECRYPTION_FINTER);
//'�Í������ꂽ�A�^�b�V�F�P�[�X�t�@�C�����̓���';
SaveDialog1->Title = LoadResourceString(&Msgunit1::_DIALOG_SAVE_FILES_FOR_ENCRYPTION_TITLE);
//'�A�^�b�V�F�P�[�X�t�@�C��(*.atc)|*.atc|���s�`���t�@�C��(*.exe)|(*.exe)|���ׂẴt�@�C��(*.*)|*.*';
SaveDialog1->Filter = LoadResourceString(&Msgunit1::_DIALOG_SAVE_FILES_FOR_ENCRYPTION_FILTER);

//-----------------------------------
//����ݒ��ǂݍ���
//-----------------------------------

// �R�}���h���C������������
if ( ParamCount() > 0){

	opthdl->LoadOptionDataFromParamString(FileList);

	//�t�@�C�����X�g������΁A���̓��f�B���N�g����INI�t�@�C�������邩�H
	if ( FileList->Count > 0 ){

		if ( DirectoryExists(FileList->Strings[0]) == true ){
			//�t�H���_�Ȃ炻�̒��ɂ���t�@�C��
			IniFilePath = IncludeTrailingPathDelimiter(FileList->Strings[0])+INI_FILE_NAME;
		}
		else {
			//�t�@�C���Ȃ瓯���f�B���N�g������
			IniFilePath = IncludeTrailingPathDelimiter(ExtractFileDir(FileList->Strings[0]))+INI_FILE_NAME;
		}

		// INI�t�@�C��������΂�������A�Ȃ���΃��W�X�g������ǂݍ���
		opthdl->LoadOptionData(IniFilePath);

	}
	//�t�@�C�����X�g�͂Ȃ�
	else{
		// ���W�X�g������ǂݍ���
		opthdl->LoadOptionData("");
	}

	//������x�A���̏ォ��R�}���h���C���������㏑������
	opthdl->LoadOptionDataFromParamString(FileList);

}
else{

	//-----------------------------------
	// INI�t�@�C��������΂�������A
	// �Ȃ���΃��W�X�g������ǂݍ���
	//-----------------------------------

	//�J�����g�f�B���N�g���ɐݒ�INI�t�@�C�������邩�H
	String IniFilePath = IncludeTrailingPathDelimiter(GetCurrentDir())+INI_FILE_NAME;

	if ( FileExists(IniFilePath) == false ){
		//�Ȃ���Ζ{�̃f�B���N�g������
		IniFilePath = IncludeTrailingPathDelimiter(ExtractFileDir(Application->ExeName))+INI_FILE_NAME;
	}

	opthdl->LoadOptionData(IniFilePath);

}

//-----------------------------------
//�E�B���h�E�|�W�V����
//-----------------------------------
this->Width = opthdl->FormWidth;
this->Height = opthdl->FormHeight;
this->Top = opthdl->FormTop;
this->Left = opthdl->FormLeft;
if ( opthdl->WinStyle == 1 ) {     	//�ŏ���
	Application->Minimize();
}
else if ( opthdl->WinStyle == 2 ) {	//�ő剻
	this->WindowState = wsMaximized;
}
else{
	this->WindowState = wsNormal;
}


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
//�E�B���h�E�|�W�V�����Ȃǂ��L������
//-----------------------------------
opthdl->FormWidth = this->Width;
opthdl->FormHeight = this->Height;
opthdl->FormTop = this->Top;
opthdl->FormLeft = this->Left;
if ( this->WindowState == wsMinimized ){       //�ŏ���
	opthdl->WinStyle = 1;
}
else if ( Form1->WindowState == wsMaximized ){ //�ő剻
	opthdl->WinStyle = 2;
}
else{
	opthdl->WinStyle = 0;
}

delete opthdl;

delete FileList;  //��������t�@�C�����X�g

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

//�R�}���h���C�������Ƀt�@�C�����������܂�Ă��Ă���
if ( FileList->Count > 0 ) {
	//�Í���/�����������������肵���s����
	DoExecute(FileList);
}
else{
	//���C���p�l����ʏ�\��
	PageControl1->ActivePage = TabSheetMain;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{

if (Key == VK_ESCAPE) {
	Close();
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{

SetFormComponent(Sender);

}
//---------------------------------------------------------------------------
//�t�H�[�����R���|�[�l���g��z�u����
//---------------------------------------------------------------------------
void __fastcall TForm1::SetFormComponent(TObject *Sender)
{

//-----------------------------------
//�f�X�N�g�b�v�ōőO�ʂɃE�B���h�E��\�����邩
//-----------------------------------
if ( opthdl->fWindowForeground == true ){
	this->FormStyle = fsStayOnTop;
}
else{
	this->FormStyle = fsNormal;
}

//-----------------------------------
//���C���p�l��
//-----------------------------------
lblMain->Left = Form1->Width/2 - lblMain->Width/2;
lblMain->Top = TabSheetMain->Height/2 - lblMain->Height/2;

imgOptionPanel->Picture = imgOptionIcon->Picture;

//-----------------------------------
//�Í����p�X���[�h���̓p�l��
//-----------------------------------
txtEncryptPassword->Left = 24;
txtEncryptPassword->Top = TabSheetInputEncPass->Height/2 - txtEncryptPassword->Height;
txtEncryptPassword->Width = TabSheetInputEncPass->Width - txtEncryptPassword->Left*2;

//�u*�v�ŉB�����p�X���[�h���m�F���Ȃ�����͂���
if ( opthdl->fNoHidePassword == true ){
	txtEncryptPassword->PasswordChar = NULL;
}
else{
	txtEncryptPassword->PasswordChar = '*';
}

chkExeFileOut->Top = txtEncryptPassword->BoundsRect.Bottom + 8;
chkExeFileOut->Left = txtEncryptPassword->Left;
chkExeFileOut->Width = txtEncryptPassword->Width;
if ( Sender == NULL) {
	//���T�C�Y�C�x���g�ł͕ύX���Ȃ�
	chkExeFileOut->Checked = opthdl->fSaveToExeout;       //��Ɏ��Ȏ��s�`���ŏo�͂���
}
chkExeFileOut->Visible = opthdl->fShowExeoutChkBox;   //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������

cmdEncryptPasswordCancel->Top = chkExeFileOut->BoundsRect.Bottom + 8;
cmdEncryptPasswordCancel->Left = chkExeFileOut->BoundsRect.Right - cmdEncryptPasswordCancel->Width;

cmdEncryptPasswordOK->Top = cmdEncryptPasswordCancel->Top;
cmdEncryptPasswordOK->Left = cmdEncryptPasswordCancel->Left - cmdEncryptPasswordOK->Width - 8;

//�߂�{�^��
imgBackFromInputEncPass->Picture = imgBackNormal->Picture;

//-----------------------------------
//�Í����p�X���[�h�Ċm�F�p�l��
//-----------------------------------
txtPasswordConfirm->Left = 24;
txtPasswordConfirm->Top = TabSheetInputEncPassConfirm->Height/2 - txtPasswordConfirm->Height;
txtPasswordConfirm->Width = TabSheetInputEncPassConfirm->Width - txtPasswordConfirm->Left*2;

//�u*�v�ŉB�����p�X���[�h���m�F���Ȃ�����͂���
if ( opthdl->fNoHidePassword == true ){
	txtPasswordConfirm->PasswordChar = NULL;
}
else{
	txtPasswordConfirm->PasswordChar = '*';
}

chkExeFileOutConf->Top = txtPasswordConfirm->BoundsRect.Bottom + 8;
chkExeFileOutConf->Left = txtPasswordConfirm->Left;
chkExeFileOutConf->Width = txtPasswordConfirm->Width;
//chkExeFileOut->Checked = true;	//chkExeFileOut�̃N���b�N�C�x���g�Ő��䂷��
chkExeFileOutConf->Visible = opthdl->fShowExeoutChkBox;   //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������

cmdConfirmCancel->Top = chkExeFileOutConf->BoundsRect.Bottom + 8;
cmdConfirmCancel->Left = chkExeFileOutConf->BoundsRect.Right - cmdConfirmCancel->Width;

cmdConfirmOK->Top = cmdConfirmCancel->Top;
cmdConfirmOK->Left = cmdConfirmCancel->Left - cmdConfirmOK->Width - 8;

//�߂�{�^��
imgBackFromInputEncPassConfirm->Picture = imgBackNormal->Picture;


//-----------------------------------
//�����p�X���[�h���̓p�l��
//-----------------------------------
txtDecryptPassword->Left = 24;
txtDecryptPassword->Top = TabSheetInputDecPass->Height/2 - txtDecryptPassword->Height;
txtDecryptPassword->Width = TabSheetInputDecPass->Width - txtDecryptPassword->Left*2;

//�u*�v�ŉB�����p�X���[�h���m�F���Ȃ�����͂���
if ( opthdl->fNoHidePassword == true ){
	txtDecryptPassword->PasswordChar = NULL;
}
else{
	txtDecryptPassword->PasswordChar = '*';
}

cmdDecryptPasswordCancel->Top = txtDecryptPassword->BoundsRect.Bottom + 8;
cmdDecryptPasswordCancel->Left =
	txtDecryptPassword->BoundsRect.Right - cmdDecryptPasswordCancel->Width;

cmdDecryptPasswordOK->Top = cmdDecryptPasswordCancel->Top;
cmdDecryptPasswordOK->Left = cmdDecryptPasswordCancel->Left - cmdDecryptPasswordOK->Width - 8;

//�߂�{�^��
imgBackFromInputDecPass->Picture = imgBackNormal->Picture;


//-----------------------------------
//���s�p�l��
//-----------------------------------
ProgressBar1->Left = 24;
ProgressBar1->Top = TabSheetExecute->Height/2 - ProgressBar1->Height;
ProgressBar1->Width =TabSheetExecute->Width - ProgressBar1->Left*2;

lblMsg->Left = ProgressBar1->Left;
lblMsg->Top = ProgressBar1->Top - lblMsg->Height*2 - 8;

lblProgressPercentNum->Top = ProgressBar1->Top + ProgressBar1->Height + 8;
lblProgressPercentNum->Left =
	ProgressBar1->Left + ProgressBar1->Width/2 - lblProgressPercentNum->Width/2;

lblStatus->Left = ProgressBar1->Left;
lblStatus->Top = lblMsg->Top - lblStatus->Height - 8;

cmdCancel->Top = ProgressBar1->BoundsRect.Bottom + 8;
cmdCancel->Left = ProgressBar1->BoundsRect.Right - cmdCancel->Width;

//�߂�{�^��
imgBackFromExecute->Picture = imgBackNormal->Picture;

if (TimerEncrypt->Enabled == false &&
		TimerDecrypt->Enabled == false && TimerDelete->Enabled == false) {
	imgBackFromExecute->Visible = true;
}
else{
	imgBackFromExecute->Visible = false;
}


}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBoxMainMouseEnter(TObject *Sender)
{

//�_���g��\������

#define DOT_HEIGHT 8
#define DOT_WIDTH 8

int PosX, PosY;

this->Canvas->Pen->Color = TColor(RGB(200,200,200));
this->Canvas->Brush->Color = TColor(RGB(200,200,200));

PosY = PageControl1->BoundsRect.Bottom;
for (PosX = 0; PosX < this->Width; PosX+=24) {
	this->Canvas->Rectangle(PosX, 0, PosX+16, DOT_HEIGHT);
	this->Canvas->Rectangle(PosX, PosY, PosX+16, PosY+DOT_HEIGHT);
}

PosX = PageControl1->BoundsRect.Right;
for (PosY = 0; PosY < this->Height; PosY+=24) {
	this->Canvas->Rectangle(0, PosY, DOT_WIDTH, PosY+16);
	this->Canvas->Rectangle(PosX, PosY, PosX+DOT_WIDTH, PosY+16);
}


}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBoxMainMouseLeave(TObject *Sender)
{

//�_���g���N���A
this->Canvas->Brush->Color = clBtnFace;
this->Canvas->FillRect(Rect(0, 0, this->Width, this->Height));

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

//-----------------------------------
// ���C���p�l��
//-----------------------------------
if ( PageControl1->ActivePage == TabSheetMain ) {

	this->Color = TColor(RGB(80,80,80));
	DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

}
//-----------------------------------
// �p�X���[�h���̓p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputEncPass ) {

	//�p�X���[�h�t�@�C����������
	if ( opthdl->fAllowPassFile == true ) {

		DragAndDropTarget->fMultipleFilesOk = false;
		DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

		//�p�X���[�h���̓{�b�N�X
		px = txtEncryptPassword->Left;
		py = txtEncryptPassword->Top;
		pr = txtEncryptPassword->BoundsRect.Right;
		pb = txtEncryptPassword->BoundsRect.Bottom;
		rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

		if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
			txtEncryptPassword->Color = TColor(0xDBEBF7);  //�I�����W�F
		}
		else{
			txtEncryptPassword->Color = clBtnFace;
		}

	}
	else{
		DragAndDropTarget->DropImageType = DROPIMAGE_NONE;
	}

}
//-----------------------------------
// �p�X���[�h�Ċm�F�p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputEncPassConfirm ) {

	//�p�X���[�h�t�@�C����������
	if ( opthdl->fAllowPassFile == true ) {

		DragAndDropTarget->fMultipleFilesOk = false;
		DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

		//�p�X���[�h���̓{�b�N�X
		px = txtPasswordConfirm->Left;
		py = txtPasswordConfirm->Top;
		pr = txtPasswordConfirm->BoundsRect.Right;
		pb = txtPasswordConfirm->BoundsRect.Bottom;
		rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

		if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
			txtPasswordConfirm->Color = TColor(0x99ccff);  //���Z���I�����W�F
		}
		else{
			txtPasswordConfirm->Color = TColor(0xDBEBF7);  //�I�����W�F�ɖ߂�
		}

	}
	else{
		DragAndDropTarget->DropImageType = DROPIMAGE_NONE;
	}

}
//-----------------------------------
// �����p�X���[�h���̓p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputDecPass ) {

	//�p�X���[�h�t�@�C����������
	if ( opthdl->fAllowPassFile == true ) {

		DragAndDropTarget->fMultipleFilesOk = false;
		DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

		//�p�X���[�h���̓{�b�N�X
		px = txtDecryptPassword->Left;
		py = txtDecryptPassword->Top;
		pr = txtDecryptPassword->BoundsRect.Right;
		pb = txtDecryptPassword->BoundsRect.Bottom;
		rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

		if (IntersectRect(rcResult, rcMouse, rcTarget) == true ) {
			txtDecryptPassword->Color = TColor(0xDBEBF7);  //�I�����W�F
		}
		else{
			txtDecryptPassword->Color = clBtnFace;
		}

	}
	else{
		DragAndDropTarget->DropImageType = DROPIMAGE_NONE;
	}

}
//-----------------------------------
// ���s���p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetExecute ) {
	//���s���̓h���b�v���󂯕t���Ȃ�
	DragAndDropTarget->DropImageType = DROPIMAGE_NONE;

}

}
//---------------------------------------------------------------------------
// DragLeave �C�x���g�̃R�[���o�b�N�֐�
//---------------------------------------------------------------------------
void __fastcall TForm1::FilesDragLeave(void)
{

//-----------------------------------
// ���C���p�l��
//-----------------------------------
if ( PageControl1->ActivePage == TabSheetMain ) {
	//���C���t�H�[��
	this->Color = clBtnFace;
}
//-----------------------------------
// �p�X���[�h���̓p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputEncPass ) {
	txtEncryptPassword->Color = clBtnFace;
}
//-----------------------------------
// �p�X���[�h�Ċm�F�p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputEncPassConfirm ) {
	txtPasswordConfirm->Color = TColor(0xDBEBF7);  //�I�����W�F�ɖ߂�
}
//-----------------------------------
// �����p�X���[�h���̓p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputDecPass ) {
	txtDecryptPassword->Color = clBtnFace;
}
//-----------------------------------
// ���s���p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetExecute ) {

}

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

String SHA1HashPassword = "";
TStringList *DropFileList = new TStringList;
DropFileList->Text = FileListText;

//�Ċm�F�p�̃p�X���[�h�n�b�V��
AnsiString TempPasswordFileHeader;
AnsiString TempPasswordFileHash;

//-----------------------------------
// ���C���p�l��
//-----------------------------------
if ( PageControl1->ActivePage == TabSheetMain ) {

	//���C���t�H�[��
	this->Color = clBtnFace;

	//�h���b�O���h���b�v���ꂽ�t�@�C�����X�g���擾����
	FileList->Text = FileListText;

	//-----------------------------------
	//�Í���/�����������������肵���s����
	//-----------------------------------
	if (FileList->Count > 0) {
		DoExecute(FileList);
	}

}
//-----------------------------------
// �p�X���[�h���̓p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputEncPass ) {

	txtEncryptPassword->Color = clBtnFace;

	//�p�X���[�h�t�@�C����������
	if ( opthdl->fAllowPassFile == true ) {

		DragAndDropTarget->fMultipleFilesOk = false;
		DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

		//�p�X���[�h���̓{�b�N�X
		px = txtEncryptPassword->Left;
		py = txtEncryptPassword->Top;
		pr = txtEncryptPassword->BoundsRect.Right;
		pb = txtEncryptPassword->BoundsRect.Bottom;
		rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

		if (IntersectRect(rcResult, rcMouse, rcTarget) == true && DropFileList->Count > 0) {

			//SHA-1�n�b�V�������߂�
			if ( opthdl->GetSHA1HashFromFile(
				DropFileList->Strings[0], password_hash, PasswordFileHeader, PasswordFileHash ) == true ){
				txtEncryptPassword->Text = PasswordFileHash.SetLength(32);
				//'�p�X���[�h�Ɉȉ��̃t�@�C���̃n�b�V���l�����͂���܂���'
				BalloonHint1->Title = LoadResourceString(&Msgunit1::_BALLOON_HINT_PASSWORD_HASH_TITLE);
				//���̃t�@�C���p�X��\������
				BalloonHint1->Description = DropFileList->Strings[0];
				BalloonHint1->ShowHint(txtEncryptPassword->ClientToScreen(CenterPoint(txtEncryptPassword->ClientRect)));
				txtEncryptPassword->SetFocus();
				txtEncryptPassword->SelectAll();
			}
			else{
				//'�p�X���[�h�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_OPEN_PASSWORD_FILE)+"\n"+
																		 DropFileList->Strings[0];
				MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
			}
		}

	}
	else{
		DragAndDropTarget->DropImageType = DROPIMAGE_NONE;
	}

}
//-----------------------------------
// �p�X���[�h�Ċm�F�p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputEncPassConfirm ) {

	txtPasswordConfirm->Color = TColor(0xDBEBF7);  //�I�����W�F�ɖ߂�

	//�p�X���[�h�t�@�C����������
	if ( opthdl->fAllowPassFile == true ) {

		DragAndDropTarget->fMultipleFilesOk = false;
		DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

		//�p�X���[�h���̓{�b�N�X
		px = txtPasswordConfirm->Left;
		py = txtPasswordConfirm->Top;
		pr = txtPasswordConfirm->BoundsRect.Right;
		pb = txtPasswordConfirm->BoundsRect.Bottom;
		rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

		if (IntersectRect(rcResult, rcMouse, rcTarget) == true && DropFileList->Count > 0) {
			//SHA-1�n�b�V�������߂�
			if ( opthdl->GetSHA1HashFromFile(
				DropFileList->Strings[0], temp_password_hash, TempPasswordFileHeader, TempPasswordFileHash ) == true ){
				txtPasswordConfirm->Text = TempPasswordFileHash.SetLength(32);
				//�����Ɏ��s�i���s��Ńp�X���[�h�̐��ۃ`�F�b�N���s����j
				cmdConfirmOKClick((TObject*)0);
			}
			else{
				//'�p�X���[�h�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_OPEN_PASSWORD_FILE)+"\n"+
																		 DropFileList->Strings[0];
				MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
			}
		}

	}
	else{
		DragAndDropTarget->DropImageType = DROPIMAGE_NONE;
	}

}
//-----------------------------------
// �����p�X���[�h���̓p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetInputDecPass ) {

	txtDecryptPassword->Color = clBtnFace;

	//�p�X���[�h�t�@�C����������
	if ( opthdl->fAllowPassFile == true ) {

		DragAndDropTarget->fMultipleFilesOk = false;
		DragAndDropTarget->DropImageType = DROPIMAGE_COPY;

		//�p�X���[�h���̓{�b�N�X
		px = txtDecryptPassword->Left;
		py = txtDecryptPassword->Top;
		pr = txtDecryptPassword->BoundsRect.Right;
		pb = txtDecryptPassword->BoundsRect.Bottom;
		rcTarget = Rect(ClientToScreen(TPoint(px, py)), ClientToScreen(TPoint(pr, pb)));

		if (IntersectRect(rcResult, rcMouse, rcTarget) == true && DropFileList->Count > 0) {
			//SHA-1�n�b�V�������߂�
			if ( opthdl->GetSHA1HashFromFile(
				DropFileList->Strings[0], password_hash, PasswordFileHeader, PasswordFileHash ) == true ){
				txtDecryptPassword->Text = PasswordFileHash;
				cmdDecryptPasswordOKClick((TObject*)0);
			}
			else{
				//'�p�X���[�h�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_OPEN_PASSWORD_FILE)+"\n"+
																		 DropFileList->Strings[0];
				MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
			}
		}

	}
	else{
		DragAndDropTarget->DropImageType = DROPIMAGE_NONE;
	}

}
//-----------------------------------
// ���s���p�l��
//-----------------------------------
else if ( PageControl1->ActivePage == TabSheetExecute ) {

}

delete DropFileList;


}
//---------------------------------------------------------------------------
// �Í����t�@�C���̃w�b�_����
//---------------------------------------------------------------------------
bool __fastcall TForm1::CheckAtcFileHeader(TStringList *FileList)
{

int i;
String FilePath;

TFileStream *fs;
char token[17];
ZeroMemory(token, 17);

//���肷��t�@�C�����X�g�����ׂ�ATC�t�@�C���`���ł���΁u������true�v��Ԃ�
bool fDecrypt = true;

//-----------------------------------
// �t�@�C���w�b�_�𔻒�
//-----------------------------------
for (i = 0; i < FileList->Count; i++) {

	FilePath = FileList->Strings[i];

	if ( FileExists(FilePath) == true ) {

		try{
			fs = new TFileStream(FilePath, fmOpenRead);
		}
		catch(...){
			//�t�@�C�����J���Ȃ��ꍇ�͖���
			return(false);
		}

		fs->Seek((__int64)4, TSeekOrigin::soBeginning);
		fs->Read(token, 16);
		delete fs;

		//�Í����t�@�C��
		if ( StrComp(token, "_AttacheCaseData") == 0 ) {

		}
		//�j�󂳂ꂽ�t�@�C��
		else if ( StrComp(token, "_Atc_Broken_Data") == 0 ) {
			return(true);	//�����ɂ��Ď��s���������ăG���[���͂����邽��
		}
		//�ʏ�̃t�@�C��
		else{
			fDecrypt = false;	//1�ł�atc�t�@�C���ȊO������΁u�Í����v����
		}

	}
	else{
		//�f�B���N�g��
		fDecrypt = false;
	}

}//end for (i = 0; i < FileList->Count; i++);

return(fDecrypt);

}
//---------------------------------------------------------------------------
//�t�@�C���̔��ʂ��s������ɏ����𕪂��Ď��s
//---------------------------------------------------------------------------
void __fastcall TForm1::DoExecute(TStringList *FileList)
{

int i;
String MsgText;
String FilePath;

int CryptTypeNum = 0;	// 1:�Í���(TYPE_CRYPT_ENCRYPT), 2:����(TYPE_CRYPT_DECRYPT)

int res;
TForm* dlgconf;
TButton *btn;

TFileStream *fs;
char token[17];
ZeroMemory(token, 17);

FileListPosition = 0;

//-----------------------------------
//�Í�/������������₢���킹��
//-----------------------------------
if ( opthdl->fAskEncDecode == true ) {

	//'�h���b�O���h���b�v���ꂽ�t�@�C���܂��̓t�H���_�[���ǂ̂悤�ɏ������܂����H'
	MsgText = LoadResourceString(&Msgunit1::_MSG_CONFIRM_ENCRYPT_OR_DECRYPT)+"\n"+
									 FileList->Strings[0];

	if ( FileList->Count > 1) {
		MsgText = MsgText + "\n..." + IntToStr(FileList->Count) + " files.";
	}

	dlgconf = CreateMessageDialog(MsgText, mtConfirmation, TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel, mbCancel);
	dlgconf->Caption = LoadResourceString(&Msgunit1::_MSG_CAPTION_CONFIRMATION);	//'�m�F'
	//�{�^���������ꂼ�ꏑ��������
	btn = (TButton*)dlgconf->FindComponent("Yes");        //'�Í�������(&E)'
	btn->Caption = LoadResourceString(&Msgunit1::_BUTTON_CAPTION_ENCRYPTION);
	btn = (TButton*)dlgconf->FindComponent("No");         //'��������(&D)'
	btn->Caption = LoadResourceString(&Msgunit1::_BUTTON_CAPTION_DECRYPTION);
	btn = (TButton*)dlgconf->FindComponent("Cancel");     //'�L�����Z��(&C)'
	btn->Caption = LoadResourceString(&Msgunit1::_BUTTON_CAPTION_CANCEL);
	dlgconf->ParentWindow = Form1->Handle;
	res = dlgconf->ShowModal();
	delete dlgconf;

	//-----------------------------------
	//�Í���
	if (res == mrYes) {
		CryptTypeNum = TYPE_CRYPT_ENCRYPT;
	}
	//-----------------------------------
	//����
	else if (res == mrNo) {
		CryptTypeNum = TYPE_CRYPT_DECRYPT;
	}
	//-----------------------------------
	//�L�����Z��
	else {
		FileList->Clear();
		return;
	}

}
//-------------------------------------
//�Í�/������������₢���킹�����肷��
//-------------------------------------
else{

	CryptTypeNum = TYPE_CRYPT_DECRYPT;

	//-----------------------------------
	// �t�@�C���w�b�_�𔻒�
	//-----------------------------------
	for (i = 0; i < FileList->Count; i++) {

		FilePath = FileList->Strings[i];

		if ( FileExists(FilePath) == true ) {

			try{
				fs = new TFileStream(FilePath, fmOpenRead);
			}
			catch(...){
				//'�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
				MsgText = LoadResourceString(&Msgunit1::_MSG_FILE_OPEN_ERROR) + "\n" + FilePath;
				MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
				break;
			}

			fs->Seek((__int64)4, TSeekOrigin::soBeginning);
			fs->Read(token, 16);
			delete fs;

			//�Í����t�@�C��
			if ( StrComp(token, "_AttacheCaseData") == 0 ) {

			}
			//�j�󂳂ꂽ�t�@�C��
			else if ( StrComp(token, "_Atc_Broken_Data") == 0 ) {
				// '���̈Í����t�@�C���̓p�X���[�h���͂Ɏ��s���Ĕj�󂳂�Ă���悤�ł��B'
				MsgText = LoadResourceString(&Msgunit1::_MSG_BROKEN_ATC_FILE) + "\n" + FilePath;
				MessageDlg(MsgText, mtInformation, TMsgDlgButtons() << mbOK, 0);
				break;
			}
			//�ʏ�̃t�@�C��
			else{
				//1�ł�atc�t�@�C���ȊO������΁u�Í����v����
				CryptTypeNum = TYPE_CRYPT_ENCRYPT;
			}

		}
		else{
			//�f�B���N�g���i�Í������j
			CryptTypeNum = TYPE_CRYPT_ENCRYPT;
		}

	}//end for (i = 0; i < FileList->Count; i++);

}//end if ( opthdl->fAskEncDecode == true );

//-----------------------------------
// �Í���/�������ꂼ��̏������s
//-----------------------------------
//�Í���
if ( CryptTypeNum == TYPE_CRYPT_ENCRYPT ) {

	//�L���p�X���[�h�ő����Ɏ��s����
	if ( opthdl->fMemPasswordExe == true && opthdl->fMyEncodePasswordKeep == true) {
		//���s�p�l���\��
		PageControl1->ActivePage = TabSheetExecute;
		//�Ċm�F�e�L�X�g�{�b�N�X�ɓ���Ă��܂�
		txtPasswordConfirm->Text = opthdl->MyEncodePassword;
		//�Í����J�n
		FileEncrypt();
		return;
	}
	//�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
	else if ( opthdl->fAllowPassFile == true && opthdl->fCheckPassFile == true ) {

		if ( FileExists(opthdl->PassFilePath) == false ) {
			//�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
			if ( opthdl->fNoErrMsgOnPassFile == true ) {
				//���b�Z�[�W���o�����Ƀp�X���[�h���̓p�l����
				PageControl1->ActivePage = TabSheetInputEncPass;
				txtEncryptPassword->SetFocus();
				return;
			}
			else{
				//'����ݒ�Ŏw�肳�ꂽ�Í������邽�߂̃p�X���[�h�t�@�C����������܂���B
				//'�ݒ���m�F���Ă��������B'
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_NOT_FOUND_ENC_PASSWORD_FILE)+"\n"+
									opthdl->PassFilePath;
				MessageDlg(MsgText, mtInformation, TMsgDlgButtons() << mbOK, 0);
				return;
			}

		}

	}
	else{
		//�p�X���[�h���̓p�l���֐i��
		PageControl1->ActivePage = TabSheetInputEncPass;
		txtEncryptPassword->SetFocus();
		return;
	}

}
//-----------------------------------
//����
else if ( CryptTypeNum == TYPE_CRYPT_DECRYPT) {

	//�L���p�X���[�h�ő����Ɏ��s����
	if ( opthdl->fMemPasswordExe == true && opthdl->fMyDecodePasswordKeep == true) {
		//���s�p�l���\��
		PageControl1->ActivePage = TabSheetExecute;
		FileDecrypt();
		return;
	}
	//�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
	else if ( opthdl->fAllowPassFile == true && opthdl->fCheckPassFileDecrypt == true ) {

		if ( FileExists(opthdl->PassFilePathDecrypt) == false ) {
			//�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
			if ( opthdl->fNoErrMsgOnPassFile == true ) {
				//���b�Z�[�W���o�����Ƀp�X���[�h���̓p�l����
				PageControl1->ActivePage = TabSheetInputDecPass;
				txtDecryptPassword->SetFocus();
				return;
			}
			else{
				//'����ݒ�Ŏw�肳�ꂽ��������p�X���[�h�t�@�C����������܂���B'+#13+
				//'�ݒ���m�F���Ă��������B';
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_NOT_FOUND_DEC_PASSWORD_FILE)+"\n"+
									opthdl->PassFilePath;
				MessageDlg(MsgText, mtInformation, TMsgDlgButtons() << mbOK, 0);
				return;
			}

		}

	}
	else{
		//�p�X���[�h���̓p�l���֐i��
		PageControl1->ActivePage = TabSheetInputDecPass;
		txtDecryptPassword->SetFocus();
		return;
	}

}


}
//---------------------------------------------------------------------------
//���S�폜�������s
//---------------------------------------------------------------------------
void __fastcall TForm1::DoDeleteFile(TStringList *FileList)
{

//���s�p�l���\��
PageControl1->ActivePage = TabSheetExecute;

//���S�폜�C���X�^���X�̍쐬
cmpdel = new TAttacheCaseDelete(true);
cmpdel->FileList = FileList;
cmpdel->Opt = opthdl->fCompleteDelete;	// 0:�ʏ�폜, 1:���S�폜, 2:�S�~��
cmpdel->OnTerminate = DeleteThreadTerminated;
cmpdel->FreeOnTerminate = true;

//�폜�̎��s
cmpdel->Start();

//�^�X�N�o�[�i���\���iWin7�j
if(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&ptl) != S_OK) {
	//���s
}
if (ptl) ptl->SetProgressState(Application->Handle, TBPF_NORMAL);

//�i����Timer�ŊĎ�
TimerDelete->Enabled = true;


}
//---------------------------------------------------------------------------
//�Í��������X���b�h�̏I��
//---------------------------------------------------------------------------
void __fastcall TForm1::EncryptThreadTerminated(TObject *Sender)
{

ProgressBar1->Style = pbstNormal;

if (encrypt->ProgressPercentNum < 0) {
	ProgressBar1->Position = 0;
	lblProgressPercentNum->Caption = " - %";
}
else{
	ProgressBar1->Position = encrypt->ProgressPercentNum;
	lblProgressPercentNum->Caption = IntToStr(encrypt->ProgressPercentNum)+"%";
}

lblStatus->Caption = encrypt->ProgressStatusText;
lblMsg->Caption = encrypt->ProgressMsgText;

if(ptl){
	ptl->SetProgressValue(Application->Handle, 100, 100);
	ptl->Release();
	ptl = NULL;
}

//�Í�������
if ( encrypt->StatusNum > 0 ) {

	//�R���y�A
	if ( opthdl->fCompareFile == true && FileListPosition < FileList->Count ){
		FileCompare();
		return;
	}

	//�ʂɈÍ�������I�v�V�����ł܂���������t�@�C�����c���Ă���
	if (FileListPosition < FileList->Count) {
		FileEncrypt();
		return;
	}

	TimerEncrypt->Enabled = false;

	//�f�o�b�O���b�Z�[�W
	//ShowMessage("�Í����X���b�h���I�����܂����B");
	encrypt = NULL;

	//���t�@�C���̍폜����
	if ( opthdl->fDelOrgFile == true ) {
		DoDeleteFile(FileList);
		return;
	}

	//������ɏI������
	if ( opthdl->fEndToExit == true ) {
		Application->Terminate();
	}

}
else{
	//�G���[�ŏI�����Ă���
	encrypt = NULL;
}


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

//�����ɐ���
if ( decrypt->StatusNum > 0 ) {

	//�R���y�A���Ă���
	if (decrypt->fCompare == true) {
		//�f�o�b�O���b�Z�[�W
		//ShowMessage("�R���y�A�����X���b�h���I�����܂����B");
		decrypt = NULL;
		//���̈Í��������X���b�h�֖߂�
		EncryptThreadTerminated(Sender);
		return;
	}

	//�ʂɈÍ�������I�v�V�����ł܂���������t�@�C�����c���Ă���
	if (FileListPosition < FileList->Count) {
		FileDecrypt();
		return;
	}

	TimerDecrypt->Enabled = false;

	//�f�o�b�O���b�Z�[�W
	//ShowMessage("���������X���b�h���I�����܂����B");
	decrypt = NULL;

	//�Í����t�@�C���̍폜����
	if ( opthdl->fDelEncFile == true ) {
		DoDeleteFile(FileList);
		return;
	}

	//������ɏI������
	if ( opthdl->fEndToExit == true ) {
		Application->Terminate();
	}

}
else{
	//�G���[�ŏI�����Ă���
	decrypt = NULL;
}

}
//---------------------------------------------------------------------------
//���S�폜�����X���b�h�̏I��
//---------------------------------------------------------------------------
void __fastcall TForm1::DeleteThreadTerminated(TObject *Sender)
{

ProgressBar1->Style = pbstNormal;
ProgressBar1->Position = cmpdel->ProgressPercentNum;
	lblProgressPercentNum->Caption = IntToStr(cmpdel->ProgressPercentNum)+"%";

lblStatus->Caption = cmpdel->ProgressStatusText;
lblMsg->Caption = cmpdel->ProgressMsgText;

if(ptl){
	ptl->SetProgressValue(Application->Handle, 100, 100);
	ptl->Release();
	ptl = NULL;
}

TimerDelete->Enabled = false;

//�f�o�b�O���b�Z�[�W
//ShowMessage("���S�폜�����X���b�h���I�����܂����B");
cmpdel = NULL;

FileList->Clear();

//������ɏI������
if ( opthdl->fEndToExit == true ) {
	Application->Terminate();
}


}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerEncryptTimer(TObject *Sender)
{

//�Í����̐i���󋵂��m�F����

//�y�⑫�z
// TThread�N���X�� Synchronize() �AQueue()
// ���g���ƃ}���`�X���b�h�̉��b�ɗa���ꂸ�A�ɒ[�ɏ������x���ቺ���邽��
// ���C���X���b�h�����TTimer�Ō�����悤�ɂ��Ă��܂��B

if (encrypt != NULL) {

	if (encrypt->ProgressPercentNum == -1) {
		//�}�[�L�[�\��
		ProgressBar1->Style = pbstMarquee;
		lblProgressPercentNum->Caption = " - %";
		if (ptl) {
			ptl->SetProgressState(Application->Handle, TBPF_INDETERMINATE);
		}

	}
	else{
		ProgressBar1->Style = pbstNormal;
		ProgressBar1->Position = encrypt->ProgressPercentNum;
		lblProgressPercentNum->Caption = IntToStr(encrypt->ProgressPercentNum)+"%";
		//�^�X�N�o�[�i���\���iWin7�j
		if(ptl){
			ptl->SetProgressValue(Application->Handle, encrypt->ProgressPercentNum, 100);
		}
	}
	lblStatus->Caption = encrypt->ProgressStatusText;
	lblMsg->Caption = encrypt->ProgressMsgText;

}
else{
	TimerEncrypt->Enabled = false;
}

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
void __fastcall TForm1::TimerDeleteTimer(TObject *Sender)
{

//���S�폜�����̐i���󋵂��m�F����

if (cmpdel != NULL) {
	if (cmpdel->ProgressPercentNum == -1) {
		//�}�[�L�[�\��
		ProgressBar1->Style = pbstMarquee;
		lblProgressPercentNum->Caption = " - %";
		if (ptl) {
			ptl->SetProgressState(Application->Handle, TBPF_INDETERMINATE);
		}
	}
	else{
		ProgressBar1->Style = pbstNormal;
		ProgressBar1->Position = cmpdel->ProgressPercentNum;
		lblProgressPercentNum->Caption = IntToStr(cmpdel->ProgressPercentNum)+"%";
		//�^�X�N�o�[�i���\���iWin7�j
		if(ptl){
			ptl->SetProgressValue(Application->Handle, cmpdel->ProgressPercentNum, 100);
		}
	}
	lblStatus->Caption = cmpdel->ProgressStatusText;
	lblMsg->Caption = cmpdel->ProgressMsgText;
}
else{
	TimerDelete->Enabled = false;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuFileClick(TObject *Sender)
{

if ( PageControl1->ActivePage == TabSheetMain ){
	mnuEncryptFiles->Enabled = true;
	mnuEncryptDir->Enabled = true;
	mnuDecrypt->Enabled = true;
}
else if ( PageControl1->ActivePage == TabSheetInputEncPass ){
	mnuEncryptFiles->Enabled = true;
	mnuEncryptDir->Enabled = true;
	mnuDecrypt->Enabled = false;
}
else if ( PageControl1->ActivePage == TabSheetInputEncPassConfirm ){
	mnuEncryptFiles->Enabled = false;
	mnuEncryptDir->Enabled = false;
	mnuDecrypt->Enabled = false;
}
else if ( PageControl1->ActivePage == TabSheetInputDecPass ){
	mnuEncryptFiles->Enabled = false;
	mnuEncryptDir->Enabled = false;
	mnuDecrypt->Enabled = true;
}
else if ( PageControl1->ActivePage == TabSheetExecute ){
	mnuEncryptFiles->Enabled = false;
	mnuEncryptDir->Enabled = false;
	mnuDecrypt->Enabled = false;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuEncryptFilesClick(TObject *Sender)
{

String MsgText;

if (OpenDialogEncrypt->Execute() == true) {

	FileList->Clear();
	FileList->Text = OpenDialogEncrypt->Files->Text;  //�Í������錳�t�@�C�����X�g

	//�L���p�X���[�h�ő����Ɏ��s����
	if ( opthdl->fMemPasswordExe == true && opthdl->fMyEncodePasswordKeep == true) {
		//���s�p�l���\��
		PageControl1->ActivePage = TabSheetExecute;
		//�Ċm�F�e�L�X�g�{�b�N�X�ɓ���Ă��܂�
		txtPasswordConfirm->Text = opthdl->MyEncodePassword;
		//�Í����J�n
		FileEncrypt();
		return;
	}
	//�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
	else if ( opthdl->fAllowPassFile == true && opthdl->fCheckPassFile == true ) {

		if ( FileExists(opthdl->PassFilePath) == false ) {
			//�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
			if ( opthdl->fNoErrMsgOnPassFile == true ) {
				//���b�Z�[�W���o�����Ƀp�X���[�h���̓p�l����
				PageControl1->ActivePage = TabSheetInputEncPass;
				txtEncryptPassword->SetFocus();
				return;
			}
			else{
				//'����ݒ�Ŏw�肳�ꂽ�Í������邽�߂̃p�X���[�h�t�@�C����������܂���B
				//'�ݒ���m�F���Ă��������B'
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_NOT_FOUND_ENC_PASSWORD_FILE)+"\n"+
									opthdl->PassFilePath;
				MessageDlg(MsgText, mtInformation, TMsgDlgButtons() << mbOK, 0);
				return;
			}

		}

	}
	else{
		//�p�X���[�h���̓p�l���֐i��
		PageControl1->ActivePage = TabSheetInputEncPass;
		txtEncryptPassword->SetFocus();
		return;
	}

}//end if (OpenDialogEncrypt->Execute() == true);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuEncryptDirClick(TObject *Sender)
{

String MsgText;

String DirPath;

TSelectDirExtOpts opt =
	TSelectDirExtOpts() << sdNewUI << sdNewFolder << sdShowEdit << sdValidateDir;

// "�Í�������f�B���N�g���i�t�H���_�j��I�����Ă��������B"
if (SelectDirectory(LoadResourceString(&Msgunit1::_DIALOG_SELECT_DIRECTORY_TEXT), L"", DirPath, opt) == true){

	FileList->Clear();
	FileList->Text = DirPath;

		//�L���p�X���[�h�ő����Ɏ��s����
	if ( opthdl->fMemPasswordExe == true && opthdl->fMyEncodePasswordKeep == true) {
		//���s�p�l���\��
		PageControl1->ActivePage = TabSheetExecute;
		//�Ċm�F�e�L�X�g�{�b�N�X�ɓ���Ă��܂�
		txtPasswordConfirm->Text = opthdl->MyEncodePassword;
		//�Í����J�n
		FileEncrypt();
		return;
	}
	//�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
	else if ( opthdl->fAllowPassFile == true && opthdl->fCheckPassFile == true ) {

		if ( FileExists(opthdl->PassFilePath) == false ) {
			//�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
			if ( opthdl->fNoErrMsgOnPassFile == true ) {
				//���b�Z�[�W���o�����Ƀp�X���[�h���̓p�l����
				PageControl1->ActivePage = TabSheetInputEncPass;
				txtEncryptPassword->SetFocus();
				return;
			}
			else{
				//'����ݒ�Ŏw�肳�ꂽ�Í������邽�߂̃p�X���[�h�t�@�C����������܂���B
				//'�ݒ���m�F���Ă��������B'
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_NOT_FOUND_ENC_PASSWORD_FILE)+"\n"+
									opthdl->PassFilePath;
				MessageDlg(MsgText, mtInformation, TMsgDlgButtons() << mbOK, 0);
				return;
			}

		}

	}
	else{
		//�p�X���[�h���̓p�l���֐i��
		PageControl1->ActivePage = TabSheetInputEncPass;
		txtEncryptPassword->SetFocus();
		return;
	}

}//end if (SelectDirectory);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuDecryptClick(TObject *Sender)
{

String MsgText;

if (OpenDialogDecrypt->Execute() == true) {

	FileList->Clear();
	FileList->Text = OpenDialogDecrypt->Files->Text;  //�������錳�t�@�C�����X�g

	//�L���p�X���[�h�ő����Ɏ��s����
	if ( opthdl->fMemPasswordExe == true && opthdl->fMyDecodePasswordKeep == true) {
		//���s�p�l���\��
		PageControl1->ActivePage = TabSheetExecute;
		FileDecrypt();
		return;
	}
	//�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
	else if ( opthdl->fAllowPassFile == true && opthdl->fCheckPassFileDecrypt == true ) {

		if ( FileExists(opthdl->PassFilePathDecrypt) == false ) {
			//�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
			if ( opthdl->fNoErrMsgOnPassFile == true ) {
				//���b�Z�[�W���o�����Ƀp�X���[�h���̓p�l����
				PageControl1->ActivePage = TabSheetInputDecPass;
				txtDecryptPassword->SetFocus();
				return;
			}
			else{
				//'����ݒ�Ŏw�肳�ꂽ��������p�X���[�h�t�@�C����������܂���B'+#13+
				//'�ݒ���m�F���Ă��������B';
				MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_NOT_FOUND_DEC_PASSWORD_FILE)+"\n"+
									opthdl->PassFilePath;
				MessageDlg(MsgText, mtInformation, TMsgDlgButtons() << mbOK, 0);
				return;
			}

		}

	}
	else{
		//�p�X���[�h���̓p�l���֐i��
		PageControl1->ActivePage = TabSheetInputDecPass;
		txtDecryptPassword->SetFocus();
		return;
	}

}//end if (OpenDialogDecrypt->Execute() == true)

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuOptionClick(TObject *Sender)
{

if ( PageControl1->ActivePage == TabSheetMain ){
	mnuSetting->Enabled = true;
}
else{
	mnuSetting->Enabled = false;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuSettingClick(TObject *Sender)
{
//�I�v�V�����p�l���̕\��
Form3 = new TForm3(this);
Form3->PopupParent = Screen->ActiveForm;
Form3->ShowModal();
Form3->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuContentsClick(TObject *Sender)
{

//�w���v�t�@�C���̖ڎ����J��
Application->HelpShowTableOfContents();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuAboutClick(TObject *Sender)
{
//�o�[�W�������̕\��
Form2 = new TForm2(this);
Form2->PopupParent = Screen->ActiveForm;
Form2->ShowModal();
Form2->Release();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{

if (encrypt != NULL) {
	encrypt->Terminate();
	CanClose = false;
}

if (decrypt != NULL) {
	decrypt->Terminate();
	CanClose = false;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdEncryptPasswordOKClick(TObject *Sender)
{

if (AnsiString(txtEncryptPassword->Text).Length() > 32) {
	//'���͂��ꂽ�p�X���[�h���������܂��B'
	BalloonHint1->Title = LoadResourceString(&Msgunit1::_BALLOON_HINT_PASSWOED_LENGTH_LONG);
	//'�p�X���[�h�Ɏg�p�ł��镶�����͔��p32�����i�S�p16�����j�ȓ��ł�'
	BalloonHint1->Description = LoadResourceString(&Msgunit1::_BALLOON_HINT_PASSWOED_LENGTH_SESCRIPTION);
	BalloonHint1->ShowHint(txtEncryptPassword->ClientToScreen(CenterPoint(txtEncryptPassword->ClientRect)));
	txtEncryptPassword->SetFocus();
	txtEncryptPassword->SelectAll();
	return;
}

//���s�\�`���o�͂̃`�F�b�N�{�b�N�X
chkExeFileOutConf->Checked = chkExeFileOut->Checked;

//�p�X���[�h�Ċm�F�p�l���֐i��
PageControl1->ActivePage = TabSheetInputEncPassConfirm;
txtPasswordConfirm->SetFocus();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdEncryptPasswordCancelClick(TObject *Sender)
{

//���C���p�l���֖߂�
PageControl1->ActivePage = TabSheetMain;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdConfirmOKClick(TObject *Sender)
{

String MsgText;

//-----------------------------------
//�p�X���[�h�t�@�C�����g���Ă���
if (password_hash[0] != 0 ){

	if ( memcmp( password_hash, temp_password_hash, 32) != 0) {
		//'��ɓ��͂��ꂽ�p�X���[�h�t�@�C���Ƃ������܂��BSHA-1�n�b�V���l����v���܂���ł����B'+#13+
		//'�Í������邱�Ƃ��ł��܂���B';
		MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_MISMATCH_PASSWORD_FILE);
		MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
		txtPasswordConfirm->SelectAll();
		return;
	}

}
//-----------------------------------
//�O�ɓ��͂��ꂽ�p�X���[�h�ƕs��v
else if (txtEncryptPassword->Text != txtPasswordConfirm->Text){
	txtPasswordConfirm->SelectAll();
	//'��ɓ��͂��ꂽ�p�X���[�h�Ƃ������܂��B'
	BalloonHint1->Title = LoadResourceString(&Msgunit1::_BALLOON_HINT_PASSWOED_MISMATCH);
	//'�S�p�E���p�̂������ACAPS���b�N���Ȃ����m�F���Ă��������B'
	BalloonHint1->Description = LoadResourceString(&Msgunit1::_BALLOON_HINT_PASSWOED_CONFIRMATION);
	BalloonHint1->ShowHint(
		txtPasswordConfirm->ClientToScreen(CenterPoint(txtPasswordConfirm->ClientRect)));
	return;

}

//-----------------------------------
//�Í���
//-----------------------------------

//���s�p�l���\��
PageControl1->ActivePage = TabSheetExecute;
//�Í����J�n
FileEncrypt();


}
//---------------------------------------------------------------------------
// �t�@�C��/�t�H���_�̈Í�������
//---------------------------------------------------------------------------
void __fastcall TForm1::FileEncrypt(void)
{

AnsiString Password;
String MsgText;
String DirPath, FilePath, FileName, Extension;
TStringList *InputFileList = new TStringList;

//-----------------------------------
// �f�B���N�g��
//-----------------------------------
if ( opthdl->fSaveToSameFldr == true ) {
	//�Í����t�@�C������ɓ����ꏊ�ɕۑ����邩
	DirPath = opthdl->SaveToSameFldrPath;
}
else{
	DirPath = ExtractFileDir(FileList->Strings[0]);
}

if ( DirectoryExists(DirPath) == false ) {
	//'�ۑ������̃t�H���_�[��������܂���B�ۑ��ݒ���Ċm�F���Ă��������B'+#13+
	//'�Í����𒆎~���܂��B';
	MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_SAVE_ENC_TO_FOLDER_NOT_EXISTS)+"\n"+
						DirPath;
	MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
	//�G���[�I���\��
	ProgressBar1->Position = 0;
	lblProgressPercentNum->Caption = " - %";
	//'�L�����Z��'
	lblStatus->Caption = LoadResourceString(&Msgunit1::_LABEL_STATUS_TITLE_USER_CANCEL);
	//'�Í��������~����܂����B'
	lblMsg->Caption = LoadResourceString(&Msgunit1::_LABEL_STATUS_DETAIL_STOPPED_ENCRYPT);
	delete InputFileList;
	return;
}

//-----------------------------------
// �t�@�C����
//-----------------------------------

FileName = ExtractFileName(FileList->Strings[0]);

//�����̃t�@�C�����Í�������ۂ͈�ɂ܂Ƃ߂�
if ( opthdl->fAllFilePack == true && FileList->Count > 1){

	if ( opthdl->fAutoName == false) {

		SaveDialog1->InitialDir = DirPath;
		SaveDialog1->FileName = FileName;
		Extension = ExtractFileExt(FileList->Strings[0]);
		// FilterIndex
		if ( Extension.UpperCase() == ".ATC" ){
			SaveDialog1->FilterIndex = 1;
		}
		else if ( Extension.UpperCase() == ".EXE" ){
			SaveDialog1->FilterIndex = 2;
		}
		else{
			SaveDialog1->FilterIndex = 3;
		}

		//�ۑ��_�C�A���O�\��
		if ( SaveDialog1->Execute() == true ){
			FilePath = SaveDialog1->FileName;
			DirPath = ExtractFileDir(FilePath);
			FileName = ExtractFileName(FilePath);
		}
		else{
			//�L�����Z���I���\��
			ProgressBar1->Position = 0;
			lblProgressPercentNum->Caption = " - %";
			//'�L�����Z��'
			lblStatus->Caption = LoadResourceString(&Msgunit1::_LABEL_STATUS_TITLE_USER_CANCEL);
			//'�Í��������~����܂����B'
			lblMsg->Caption = LoadResourceString(&Msgunit1::_LABEL_STATUS_DETAIL_STOPPED_ENCRYPT);
			delete InputFileList;
			return;
		}

	}

	//�܂Ƃ߂�̂ł��̂܂܃t�@�C�����X�g���Í��������ɂ�����
	FileListPosition = FileList->Count;
	InputFileList = FileList;

}
//-----------------------------------
//�ʂɃt�@�C�����Í�������
//-----------------------------------
else{

	InputFileList->Add(FileList->Strings[FileListPosition]);
	FileListPosition++;

}

//-----------------------------------
//�o�̓t�@�C���i�Í����t�@�C���j�p�X������
//-----------------------------------

//�Í����t�@�C���̊g���q���U������
if ( opthdl->fAddCamoExt == true ){
	Extension = opthdl->CamoExt;
}
//���s�\�`��
else if ( chkExeFileOutConf->Checked == true ){
	Extension = ".exe";
}
//�ʏ�̈Í����t�@�C��
else{
	Extension = ".atc";
}

//-----------------------------------
//�Í����t�@�C�����Ɋg���q���܂߂�
//-----------------------------------
if ( opthdl->fExtInAtcFileName == true ) {
	FilePath = IncludeTrailingPathDelimiter(DirPath) + FileName + Extension;
}
else{
	FilePath = IncludeTrailingPathDelimiter(DirPath) + ChangeFileExt(FileName, Extension);
}

//-----------------------------------
//�����ňÍ����t�@�C������t������
//-----------------------------------
if ( opthdl->fAutoName == true ) {
	FilePath = opthdl->InterpretFormatTextToFilePath(FilePath, opthdl->AutoNameFormatText);
}

//-----------------------------------
//�Í����C���X�^���X�̍쐬
//-----------------------------------
encrypt = new TAttacheCaseFileEncrypt(true);

encrypt->OnTerminate = EncryptThreadTerminated;
encrypt->FreeOnTerminate = true;
//�Í����I�v�V���������ꂼ��Z�b�g����
encrypt->OutFilePath = FilePath;                                   //�o�͂���Í����t�@�C��
encrypt->InputFileList = InputFileList;                            //�Í������錳�t�@�C�����X�g
encrypt->CompressRateNum = opthdl->CompressRate;                   //���k��
encrypt->fOver4gbOk = opthdl->fOver4GBok;                          //4GB��������
encrypt->fAllFilesPackOption = opthdl->fAllFilePack;               //���ׂẴt�@�C�����P�ɂ܂Ƃ߂�
encrypt->fExeOutputOption = chkExeFileOutConf->Checked;            //���s�`���o��
encrypt->fOptBrokenFileOption = opthdl->fBroken;                   //�~�X�^�C�v�Ńt�@�C����j�󂷂邩�ۂ�
encrypt->fConfirmOverwirte = opthdl->fConfirmOverwirte;            //�����t�@�C��������Ƃ��͏㏑���̊m�F������
encrypt->intOptMissTypeLimitsNumOption = opthdl->MissTypeLimitsNum;//�^�C�v�~�X�ł����
encrypt->AppExeFilePath = Application->ExeName;	                   //�A�^�b�V�F�P�[�X�{�̂̏ꏊ�i���s�`���o�͂̂Ƃ��ɎQ�Ƃ���j

//�p�X���[�h
if ( password_hash[0] == 0) {
	//�p�X���[�h�ɕ�������Z�b�g
	Password = AnsiString(txtPasswordConfirm->Text);
	encrypt->SetPasswordString(Password);;
}
else{
	//�p�X���[�h�t�@�C����SHA-1�l���Z�b�g
	encrypt->SetPasswordBinary(password_hash);
}

//�Í����̎��s
encrypt->Start();

//�^�X�N�o�[�i���\���iWin7�j
if(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&ptl) != S_OK) {
	//���s�����ꍇ�͖���
}
if (ptl) ptl->SetProgressState(Application->Handle, TBPF_NORMAL);

//�i����Timer�ŊĎ�
TimerEncrypt->Enabled = true;

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


//�e�t�H���_�𐶐����Ȃ�
//if ( fNoParentFldr == true  )

//-----------------------------------
//�ۑ���̃f�B���N�g��
//-----------------------------------
if ( opthdl->fDecodeToSameFldr == true ) {
	//��ɓ����ꏊ�ɕ������邩
	OutDirPath = opthdl->DecodeToSameFldrPath;
}
else{
	OutDirPath = ExtractFileDir(FileList->Strings[0]);
}

if ( DirectoryExists(OutDirPath) == false ) {
	//'�ۑ������̃t�H���_�[��������܂���B�ۑ��ݒ���Ċm�F���Ă��������B'+#13+
	//'�����������𒆎~���܂��B';
	MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_SAVE_DEC_TO_FOLDER_NOT_EXISTS)+"\n"+
						OutDirPath;
	MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
	//�G���[�I���\��
	ProgressBar1->Position = 0;
	lblProgressPercentNum->Caption = " - %";
	//'�L�����Z��'
	lblStatus->Caption = LoadResourceString(&Msgunit1::_LABEL_STATUS_TITLE_USER_CANCEL);
	//'���������~����܂����B'
	lblMsg->Caption = LoadResourceString(&Msgunit1::_LABEL_STATUS_DETAIL_STOPPED_DECRYPT);
	return;

}

//-----------------------------------
// ���������̊J�n
//-----------------------------------

FileListPosition = 0;

if ( FileList->Count > 0) {

	AtcFilePath = FileList->Strings[FileListPosition];

	//���������C���X�^���X�̍쐬
	decrypt = new TAttacheCaseFileDecrypt2(true);
	decrypt->OnTerminate = DecryptThreadTerminated;
	decrypt->FreeOnTerminate = true;
	decrypt->AppExeFilePath = Application->ExeName;  //�A�^�b�V�F�P�[�X�{�̂̏ꏊ�i���s�`���o�͂̂Ƃ��ɎQ�Ƃ���j
	decrypt->AtcFilePath = AtcFilePath;              //���͂���Í����t�@�C���p�X
	decrypt->OutDirPath = OutDirPath;                //�o�͂���f�B���N�g��

	decrypt->fOpenFolder = opthdl->fOpenFolder;             //�t�H���_�̏ꍇ�ɕ�����ɊJ����
	decrypt->fOpenFile = opthdl->fOpenFile;                 //���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ��
	decrypt->fConfirmOverwirte = opthdl->fConfirmOverwirte; //�����t�@�C���̏㏑�����m�F���邩

	//-----------------------------------
	//�p�X���[�h�̃Z�b�g
	//-----------------------------------

	//�p�X���[�h�t�@�C�����g�p����
	if ( opthdl->fCheckPassFileDecrypt == true &&
			 FileExists(opthdl->PassFilePathDecrypt) == true) {
		//�p�X���[�h���o�C�i���l�ŃZ�b�g
		decrypt->SetPasswordBinary(password_hash);
		//�p�X���[�h��������o�C�i���l�ŃZ�b�g�iver.2.75�ȑO�j
		decrypt->SetPasswordStringToBinary(PasswordFileHash);
	}
	else{
		decrypt->SetPasswordString(txtDecryptPassword->Text);
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


}
//---------------------------------------------------------------------------
// �t�@�C�����R���y�A���鏈���i�Ƃ͌����Ă����ۂ͕��������j
//---------------------------------------------------------------------------
void __fastcall TForm1::FileCompare(void)
{

int i;

String MsgText;

String AtcFilePath;
String OutDirPath;

//-----------------------------------
// �R���y�A�����̊J�n
//-----------------------------------
if (FileListPosition > FileList->Count - 1) {
	return;
}

//-----------------------------------
// �R���y�A�����̊J�n
//-----------------------------------

// ���̏����̑O�ɈÍ����������s���Ă��邩
//�i�Í����C���X�^���X�����邩�j
if ( encrypt == NULL) {
	//'�R���y�A����Í����t�@�C���܂��̓t�H���_�[��������܂���B'+#13+
	//'�R���y�A�Ɏ��s���܂����B';
	MsgText = LoadResourceString(&Msgunit1::_MSG_ERROR_NOT_EXISTS_COMPAER_FIlE);
	MessageDlg(MsgText, mtError, TMsgDlgButtons() << mbOK, 0);
	return;
}

AtcFilePath = FileList->Strings[FileListPosition];

//���������C���X�^���X�̍쐬
decrypt = new TAttacheCaseFileDecrypt2(true);

decrypt->fCompare = true;	//�R���y�A
decrypt->CompareFileList = encrypt->InputFileList;

decrypt->OnTerminate = DecryptThreadTerminated;
decrypt->FreeOnTerminate = true;
decrypt->AppExeFilePath = Application->ExeName;  //�A�^�b�V�F�P�[�X�{�̂̏ꏊ�i���s�`���o�͂̂Ƃ��ɎQ�Ƃ���j
decrypt->AtcFilePath = AtcFilePath;              //���͂���Í����t�@�C���p�X
decrypt->OutDirPath = "";                        //�o�͂���f�B���N�g��

//-----------------------------------
//�p�X���[�h�̃Z�b�g
//-----------------------------------
memcpy(decrypt->key, encrypt->key, 32);

//�R���y�A�i�����j�̎��s
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
void __fastcall TForm1::cmdConfirmCancelClick(TObject *Sender)
{

//�p�X���[�h���̓p�l���֖߂�
PageControl1->ActivePage = TabSheetInputEncPass;
txtEncryptPassword->SetFocus();
txtEncryptPassword->SelectAll();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdDecryptPasswordOKClick(TObject *Sender)
{

//-----------------------------------
//��������
//-----------------------------------

//���s�p�l���\��
PageControl1->ActivePage = TabSheetExecute;
//�����J�n
FileDecrypt();


}
//---------------------------------------------------------------------------
void __fastcall TForm1::txtEncryptPasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
if (Key == VK_RETURN) {
	cmdEncryptPasswordOKClick(Sender);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::txtPasswordConfirmKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
if (Key == VK_RETURN) {
	cmdConfirmOKClick(Sender);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::txtDecryptPasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
if (Key == VK_RETURN) {
	cmdDecryptPasswordOKClick(Sender);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdCancelClick(TObject *Sender)
{

//�Í����i�����j�����̃L�����Z��

if (encrypt != NULL) {
	encrypt->Terminate();
}
else if (decrypt != NULL) {
	decrypt->Terminate();
}
else{
	//���C���p�l���֖߂�
	PageControl1->ActivePage = TabSheetMain;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::StatusBar1DblClick(TObject *Sender)
{

//�f�o�b�O

//�I�v�V�����p�l���̕\��
Form3 = new TForm3(Application);
Form3->PopupParent = Screen->ActiveForm;
Form3->ShowModal();
Form3->Release();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::chkExeFileOutClick(TObject *Sender)
{

//�u�Í����p�X���[�h�̓��͍Ċm�F�v�p�l���̃`�F�b�N�{�b�N�X���ύX����
chkExeFileOutConf->Checked = chkExeFileOut->Checked;

}
//---------------------------------------------------------------------------
// ��d�N�������悩��̃��b�Z�[�W�󂯎��
//---------------------------------------------------------------------------
void __fastcall TForm1::EvWmCOPYDATA(TMessage message)
{

int i, c;

bool fChk = false;
String OneLine;

//���b�Z�[�W���e�����o��
COPYDATASTRUCT *cds;
cds = (COPYDATASTRUCT *)message.LParam;

if (cds == NULL) {
	return;
}

wchar_t *buffer;
buffer = new wchar_t[cds->cbData];
ZeroMemory(buffer, cds->cbData);
memmove_s(buffer, cds->cbData, cds->lpData, cds->cbData);
//char *buffer;
//buffer = new char[cds->cbData];
//ZeroMemory(buffer, cds->cbData);
//memmove_s(buffer, cds->cbData, cds->lpData, cds->cbData);

TStringList *TempList = new TStringList;
TempList->Text = buffer;

if (TempList->Count > 0) {
	delete[] buffer;
	delete TempList;
	return;
}

// ���łɊi�[����Ă���FileList�ɒǉ�����Ƃ���������
// �ǂ��Ȃ̂��H�@�v���������B

for ( i = 0; i < TempList->Count; i++){

	OneLine = TempList->Strings[i];

	if ( OneLine != "" ){

		for ( c = 0; c < FileList->Count; c++){

			if ( OneLine == FileList->Strings[c] ){
				//���łɃt�@�C�����X�g�ɑ��݂���t�@�C���͖���
				fChk = true;
				break;
			}

		}

		if ( fChk == true ){
			fChk = false;
		}
		else{
			FileList->Add(OneLine);
		}

	}

}

delete[] buffer;
delete TempList;

//-----------------------------------
//�����J�n
//-----------------------------------
DoExecute(FileList);


}//end EvWmCOPYDATA;
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBoxMainPaint(TObject *Sender)
{

//�����̃O���t�B�b�N�`��
int posx = 0;
int posy = TabSheetMain->Height - imgMain->Height;
PaintBoxMain->Canvas->Draw( posx, posy,	imgMain->Picture->Bitmap);
PaintBoxEncrypt->Canvas->Draw( posx, posy,	imgEncrypt->Picture->Bitmap);
PaintBoxConfirm->Canvas->Draw( posx, posy,	imgEncrypt->Picture->Bitmap);
PaintBoxDecrypt->Canvas->Draw( posx, posy,	imgDecrypt->Picture->Bitmap);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgOptionPanelClick(TObject *Sender)
{

//�I�v�V�����p�l���̕\��
Form3 = new TForm3(this);
Form3->PopupParent = Screen->ActiveForm;
Form3->ShowModal();
Form3->Release();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgOptionPanelMouseEnter(TObject *Sender)
{

imgOptionPanel->Picture = imgOptionIconSelect->Picture;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgOptionPanelMouseLeave(TObject *Sender)
{

imgOptionPanel->Picture = imgOptionIcon->Picture;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgBackMouseEnter(TObject *Sender)
{

TImage *img = dynamic_cast<TImage *>(Sender);
img->Picture = imgBackActive->Picture;


}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgBackMouseLeave(TObject *Sender)
{

TImage *img = dynamic_cast<TImage *>(Sender);
img->Picture = imgBackNormal->Picture;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgBackOnClick(TObject *Sender)
{

TImage *img = dynamic_cast<TImage *>(Sender);

if ( img->Name == "imgBackFromInputEncPass") {
	PageControl1->ActivePage = TabSheetMain;
}
else if ( img->Name == "imgBackFromInputEncPassConfirm") {
	PageControl1->ActivePage = TabSheetInputEncPass;
}
else if ( img->Name == "imgBackFromInputDecPass") {
	PageControl1->ActivePage = TabSheetMain;
}
else if ( img->Name == "imgBackFromExecute") {
	PageControl1->ActivePage = TabSheetMain;
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
	dlg->Caption = LoadResourceString(&Msgunit1::_MSG_CAPTION_ERROR);
}
else {
	dlg->Caption = LoadResourceString(&Msgunit1::_MSG_CAPTION_CONFIRMATION);
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
btn->Caption = LoadResourceString(&Msgunit1::_DIALOG_BUTTON_NAME_OVERWITE_YES_TO_ALL);
btn = (TButton *)dlg->FindComponent("Yes");        //'�㏑��(&O)'
btn->Caption = LoadResourceString(&Msgunit1::_DIALOG_BUTTON_NAME_OVERWITE_YES);
btn = (TButton *)dlg->FindComponent("No");         //'�ʖ��ۑ�(&A)'
btn->Caption = LoadResourceString(&Msgunit1::_DIALOG_BUTTON_NAME_OVERWITE_NO);
btn = (TButton *)dlg->FindComponent("Cancel");     //'�L�����Z��(&C)'
btn->Caption = LoadResourceString(&Msgunit1::_DIALOG_BUTTON_NAME_OVERWITE_CANCEL);

dlg->Caption = LoadResourceString(&Msgunit1::_MSG_CAPTION_CONFIRMATION);
dlg->ParentWindow = Form1->Handle;

//���b�Z�[�W�_�C�A���O�̕\��
int ret = dlg->ShowModal();

if (ret == mrNo) { //�ʖ��ŕۑ�����i�������j

	TSaveDialog *dlgsave = new TSaveDialog(dlg);
	//'�����t�@�C���̕ۑ�'
	dlgsave->Title = LoadResourceString(&Msgunit1::_DIALOG_SAVE_AS_FILE_CAPTION);
	dlgsave->InitialDir = ExtractFileDir(ExcludeTrailingPathDelimiter(Path));
	dlgsave->FileName = ExtractFileName(ExcludeTrailingPathDelimiter(Path));
	//'�t�@�C���t�H���_�[|*'
	dlgsave->Filter = LoadResourceString(&Msgunit1::_DIALOG_SAVE_AS_FILTER);
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

