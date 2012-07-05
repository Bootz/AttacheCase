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
//zlib�o�[�W����
String ZlibVersion = ZLIB_VERSION;
lblZlibVersion->Caption = "(zlib ver."+ ZlibVersion + ")";
//���쌠�\��
lblCopyright->Caption =
	StringReplace(pAppInfoString->LegalCopyright, ",", ",\n", TReplaceFlags()<<rfReplaceAll);
//�T�C�g�\��
lblHomePage->Caption = pAppInfoString->CompanyName;

delete pAppInfoString;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cmdOKClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CMMouseLeave( TMessage &Msg )
{

if (Msg.LParam == long(lblLisence)){
	lblLisence->Font->Color = TColor(TColor(0x00FF5A5A));
	lblLisence->Color = clBtnFace;

}
else if (Msg.LParam == long(lblLisenceJ)){
	lblLisenceJ->Font->Color = TColor(TColor(0x00FF5A5A));
	lblLisenceJ->Color = clBtnFace;

}
else if(Msg.LParam == long(lblHomePage)){
	lblHomePage->Font->Color = TColor(TColor(0x00FF5A5A));
	lblHomePage->Color = clBtnFace;

}//end if;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblLisenceClick(TObject *Sender)
{

//�u���E�U�N��
String Link = "https://www.gnu.org/licenses/gpl-3.0.html";
ShellExecuteW(NULL, L"open", Link.c_str(), NULL, NULL, SW_NORMAL);
Close();

}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblLisenceJClick(TObject *Sender)
{

//�u���E�U�N��
String Link = "http://ossipedia.ipa.go.jp/legalinfo/gpl-3.0J.html";
ShellExecuteW(NULL, L"open", Link.c_str(), NULL, NULL, SW_NORMAL);
Close();

}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblLisenceMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
//�����t�H���g�̃J���[�ύX
lblLisence->Font->Color = clBlue;
lblLisence->Update();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblLisenceJMouseMove(TObject *Sender, TShiftState Shift, int X,
					int Y)
{
//�����t�H���g�̃J���[�ύX
lblLisenceJ->Font->Color = clBlue;
lblLisenceJ->Update();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblHomePageMouseMove(TObject *Sender, TShiftState Shift, int X,
					int Y)
{
//�����t�H���g�̃J���[�ύX
lblHomePage->Font->Color = clBlue;
lblHomePage->Update();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::lblHomePageClick(TObject *Sender)
{

//�u���E�U�N��
String Link = "http://hibara.org/";
ShellExecuteW(NULL, L"open", Link.c_str(), NULL, NULL, SW_NORMAL);
Close();

}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblLisenceMouseEnter(TObject *Sender)
{

BalloonHint1->Title = "https://www.gnu.org/licenses/gpl-3.0.html";
BalloonHint1->Description = "�N���b�N����ƃu���E�U���N�����܂��B";
BalloonHint1->ShowHint(lblLisence->ClientToScreen(CenterPoint(lblLisence->ClientRect)));

}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblLisenceJMouseEnter(TObject *Sender)
{

BalloonHint1->Title = "http://ossipedia.ipa.go.jp/legalinfo/gpl-3.0J.html";
BalloonHint1->Description = "�N���b�N����ƃu���E�U���N�����܂��B";
BalloonHint1->ShowHint(lblLisenceJ->ClientToScreen(CenterPoint(lblLisenceJ->ClientRect)));

}
//---------------------------------------------------------------------------
void __fastcall TForm2::lblHomePageMouseEnter(TObject *Sender)
{

BalloonHint1->Title = "�N���b�N����ƃu���E�U���N�����܂��B";
BalloonHint1->Description = "";
BalloonHint1->ShowHint(lblHomePage->ClientToScreen(CenterPoint(lblHomePage->ClientRect)));

}
//---------------------------------------------------------------------------



