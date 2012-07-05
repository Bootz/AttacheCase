//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "TGetAppInfoString.h"
#include "MsgExeOut.hpp"

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
	TButton *cmdExit;
	TImage *imgMainIcon;
	TLabel *lblWebSite;
	TLabel *lblCopyright;
	TLabel *lblAppName;
	TLabel *lblVersion;
	TLabel *lblDescription01;
	TLabel *lblDescription02;
	TLabel *lblDescription03;
	void __fastcall cmdExitClick(TObject *Sender);
	void __fastcall lblWebSiteMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall lblWebSiteMouseLeave(TObject *Sender);
	void __fastcall lblWebSiteClick(TObject *Sender);

private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
