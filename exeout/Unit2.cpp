//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{

/*
//�o�[�W�������擾
pAppInfoString->Comments;
pAppInfoString->InternalName;
pAppInfoString->ProductName;
pAppInfoString->CompanyName;
pAppInfoString->LegalCopyright;
pAppInfoString->ProductVersion;
pAppInfoString->FileDescription;
pAppInfoString->LegalTrademarks;
pAppInfoString->PrivateBuild;
pAppInfoString->FileVersion;
pAppInfoString->OriginalFilename;
pAppInfoString->SpecialBuild;
*/

TGetAppInfoString *pAppInfoString = new TGetAppInfoString();
//�A�v���P�[�V������
lblAppName->Caption = pAppInfoString->ProductName;
//�o�[�W�������
lblVersion->Caption = "ver."+ pAppInfoString->FileVersion;
//���쌠�\��
lblCopyright->Caption = pAppInfoString->LegalCopyright;
//�T�C�g�\��
lblWebSite->Caption = pAppInfoString->CompanyName;

delete pAppInfoString;

imgMainIcon->Picture->Icon = Application->Icon;

//'�o�[�W�������'
this->Caption = LoadResourceString(&Msgexeout::_FORM_ABOUT_CAPTION);

//'���̃t�@�C���́A�t���[�ŁA���I�[�v���\�[�X�ŊJ������Ă���A';
//'�\�t�g�E�F�A�ňÍ�������Ă��܂��B';
//'�ڂ������͈ȉ��̃T�C�g���������������B';
//'http://hibara.org/';
lblDescription01->Caption = LoadResourceString(&Msgexeout::_FORM_ABOUT_LABEL_CAPTION_DESCRIPTION_01);
lblDescription02->Caption = LoadResourceString(&Msgexeout::_FORM_ABOUT_LABEL_CAPTION_DESCRIPTION_02);
lblDescription03->Caption = LoadResourceString(&Msgexeout::_FORM_ABOUT_LABEL_CAPTION_DESCRIPTION_03);

}
//---------------------------------------------------------------------------
void __fastcall TForm2::cmdExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblWebSiteMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
lblWebSite->Font->Color = TColor(0x00CC0000);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblWebSiteMouseLeave(TObject *Sender)
{
lblWebSite->Font->Color = TColor(0x00FF9999);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblWebSiteClick(TObject *Sender)
{

//�u���E�U�֘A�t���I�[�v��
ShellExecuteW(NULL, L"open", lblWebSite->Caption.c_str(), NULL, NULL, SW_NORMAL);
Close();

}
//---------------------------------------------------------------------------

