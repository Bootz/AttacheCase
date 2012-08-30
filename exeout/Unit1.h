//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <FileCtrl.hpp>

#include "Unit2.h"
#include "MsgExeOut.hpp"
#include "TAttacheCaseFileDecrypt2.h"
#include "TDragAndDrop.h"
#include "sha1.h"

//�o�b�t�@�T�C�Y
#define BUF_SIZE 32

//SHA-1�n�b�V���v�Z�i160bit��20byte�j
#define BUF_SHA1_SIZE 20
#define BUF_HASH_DATA 32


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
	TEdit *txtInputPassword;
	TButton *cmdExit;
	TLabel *lblAbout;
	TProgressBar *ProgressBar1;
	TTimer *TimerDecrypt;
	TButton *cmdOK;
	TLabel *lblMsgInputPassword;
	TCheckBox *chkSaveToOtherDirectory;
	TImage *imgKeyIcon;
	TLabel *lblProgressPercentNum;
	TLabel *lblMsg;
	TLabel *lblStatus;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cmdExitClick(TObject *Sender);
	void __fastcall lblAboutMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall lblAboutMouseLeave(TObject *Sender);
	void __fastcall lblAboutClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall DecryptThreadTerminated(TObject *Sender);
	void __fastcall cmdOKClick(TObject *Sender);
	void __fastcall TimerDecryptTimer(TObject *Sender);
	void __fastcall txtInputPasswordChange(TObject *Sender);


private:	// ���[�U�[�錾

	//�^�X�N�o�[�Ƀv���O���X�o�[�\�� �iWin7�j
	ITaskbarList3* ptl;

	TAttacheCaseFileDecrypt2 *decrypt; // �����N���X�̃C���X�^���X

  String PasswordFilePath;           // �p�X���[�h�t�@�C���p�X

	int TypeLimits;                    // �~�X�^�C�v�� 0�`10
	bool fDestroy;                     // �j�󂷂邩�ۂ� 0 or 1

	//�p�X���[�h�̍ē��͉�
	int RetryNum;

	// �t�H�[����Ԃ̐؂�ւ�
	void __fastcall ChangeFormStatus(int opt);	// 0:���C��, 1:���s��
	// �t�@�C���𕜍����鏈��
	void __fastcall FileDecrypt(void);
	// �t�@�C������SHA-1�n�b�V���l���擾����
	bool __fastcall GetSHA1HashFromFile(
		String FilePath,              // �p�X���[�h�t�@�C���p�X
		AnsiString &HashDataVer2,     // ver.2.*  �`�FSHA-1�n�b�V���l�i20byte + 12byte�j
		AnsiString &HashDataVer1 );   // ver.1.*  �`�F�w�b�_�f�[�^�i�擪������32�����j
	//�Í����t�@�C����j�󂷂�
	bool __fastcall DestroyAtcFile(void);


public:		// ���[�U�[�錾
	__fastcall TForm1(TComponent* Owner);

	//OLE�h���b�O���h���b�v�̃R�[���o�b�N�֐�
	void __fastcall FilesDragOver(POINTL ptl);
	void __fastcall FilesDragLeave(void);
	void __fastcall FilesDragEnd(POINTL ptl, String FileListText);

	//���b�Z�[�W�_�C�A���O�̕\���i�X���b�h�I�u�W�F�N�g����Ă΂��j
	int __fastcall ShowConfirmMassageForm(String MsgText, TMsgDlgType MsgType, TMsgDlgButtons MsgButtons, TMsgDlgBtn MsgDefaultButton);
	//�㏑���m�F���b�Z�[�W�_�C�A���O�̕\���i�����X���b�h�I�u�W�F�N�g����Ă΂��j
	int __fastcall ShowConfirmOverwriteMassageForm(String MsgText, String &Path);


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
