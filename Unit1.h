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
#include <FileCtrl.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>;

#include "TAttacheCaseFileEncrypt.h"
#include "TAttacheCaseFileDecrypt2.h"
#include "TAttacheCaseDelete.h"
#include "TAttacheCaseOptionHandle.h"

#include "MsgUnit1.hpp"
#include "TDragAndDrop.h"
#include "shlobj.h"

#include "Unit2.h"
#include "Unit3.h"


#define INI_FILE_NAME "_AtcCase.ini"

#define TYPE_CRYPT_ENCRYPT 1	//�Í���
#define TYPE_CRYPT_DECRYPT 2  //����
#define TYPE_CRYPT_ERROR -1   //�G���[


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g

	TStatusBar *StatusBar1;
	TTimer *TimerEncrypt;
	TMainMenu *MainMenu1;
	TMenuItem *mnuFile;
	TMenuItem *mnuHelp;
	TMenuItem *mnuContents;
	TMenuItem *N1;
	TMenuItem *mnuAbout;
	TMenuItem *mnuOption;
	TMenuItem *mnuSetting;
	TMenuItem *mnuEncryptFiles;
	TMenuItem *mnuEncryptDir;
	TMenuItem *mnuDecrypt;
	TMenuItem *N3;
	TMenuItem *mnuExit;
	TOpenDialog *OpenDialogEncrypt;
	TOpenDialog *OpenDialogDecrypt;
	TTimer *TimerDecrypt;
	TBalloonHint *BalloonHint1;
	TTimer *TimerDelete;
	TMenuItem *E1;
	TPageControl *PageControl1;
	TTabSheet *TabSheetMain;
	TTabSheet *TabSheetInputEncPass;
	TTabSheet *TabSheetInputEncPassConfirm;
	TTabSheet *TabSheetInputDecPass;
	TTabSheet *TabSheetExecute;
	TLabel *lblMain;
	TLabeledEdit *txtEncryptPassword;
	TButton *cmdEncryptPasswordOK;
	TButton *cmdEncryptPasswordCancel;
	TLabeledEdit *txtPasswordConfirm;
	TButton *cmdConfirmOK;
	TButton *cmdConfirmCancel;
	TLabeledEdit *txtDecryptPassword;
	TButton *cmdDecryptPasswordOK;
	TButton *cmdDecryptPasswordCancel;
	TLabel *lblStatus;
	TLabel *lblMsg;
	TProgressBar *ProgressBar1;
	TLabel *lblProgressPercentNum;
	TButton *cmdCancel;
	TCheckBox *chkExeFileOut;
	TCheckBox *chkExeFileOutConf;
	TSaveDialog *SaveDialog1;
	TPaintBox *PaintBoxMain;
	TImage *imgMain;
	TImage *imgOptionPanel;
	TImage *imgOptionIconSelect;
	TImage *imgOptionIcon;
	TImage *imgEncrypt;
	TImage *imgDecrypt;
	TPaintBox *PaintBoxEncrypt;
	TPaintBox *PaintBoxConfirm;
	TPaintBox *PaintBoxDecrypt;
	TImage *imgBackFromInputEncPass;
	TImage *imgBackNormal;
	TImage *imgBackActive;
	TImage *imgBackFromInputEncPassConfirm;
	TImage *imgBackFromInputDecPass;
	TImage *imgBackFromExecute;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall EncryptThreadTerminated(TObject *Sender);
	void __fastcall DecryptThreadTerminated(TObject *Sender);
	void __fastcall DeleteThreadTerminated(TObject *Sender);
	void __fastcall TimerEncryptTimer(TObject *Sender);
	void __fastcall mnuEncryptFilesClick(TObject *Sender);
	void __fastcall mnuEncryptDirClick(TObject *Sender);
	void __fastcall mnuDecryptClick(TObject *Sender);
	void __fastcall mnuExitClick(TObject *Sender);
	void __fastcall mnuSettingClick(TObject *Sender);
	void __fastcall mnuContentsClick(TObject *Sender);
	void __fastcall mnuAboutClick(TObject *Sender);
	void __fastcall TimerDecryptTimer(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall cmdEncryptPasswordOKClick(TObject *Sender);
	void __fastcall cmdEncryptPasswordCancelClick(TObject *Sender);
	void __fastcall cmdConfirmOKClick(TObject *Sender);
	void __fastcall cmdConfirmCancelClick(TObject *Sender);
	void __fastcall txtEncryptPasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall txtPasswordConfirmKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall txtDecryptPasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cmdCancelClick(TObject *Sender);
	void __fastcall TimerDeleteTimer(TObject *Sender);
	void __fastcall cmdDecryptPasswordOKClick(TObject *Sender);
	void __fastcall chkExeFileOutClick(TObject *Sender);
	void __fastcall PaintBoxMainPaint(TObject *Sender);
	void __fastcall imgOptionPanelClick(TObject *Sender);
	void __fastcall imgOptionPanelMouseEnter(TObject *Sender);
	void __fastcall imgOptionPanelMouseLeave(TObject *Sender);
	void __fastcall mnuFileClick(TObject *Sender);
	void __fastcall mnuOptionClick(TObject *Sender);
	void __fastcall imgBackMouseEnter(TObject *Sender);
	void __fastcall imgBackMouseLeave(TObject *Sender);
	void __fastcall PaintBoxMainMouseEnter(TObject *Sender);
	void __fastcall PaintBoxMainMouseLeave(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall txtDecryptPasswordChange(TObject *Sender);
	void __fastcall txtEncryptPasswordChange(TObject *Sender);
	void __fastcall txtPasswordConfirmChange(TObject *Sender);




private:	// ���[�U�[�錾

	TAttacheCaseFileEncrypt *encrypt;
	TAttacheCaseFileDecrypt2 *decrypt;
	TAttacheCaseDelete *cmpdel;

	//��ɋN�����Ă���A�^�b�V�F�P�[�X����̃��b�Z�[�W�󂯎��
	void __fastcall EvWmCOPYDATA(TMessage message);

	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_COPYDATA, TMessage, EvWmCOPYDATA);
	END_MESSAGE_MAP(TForm);

	//�^�X�N�o�[�Ƀv���O���X�o�[�\�� �iWin7�j
	ITaskbarList3* ptl;

	//�������܂ꂽ�t�@�C�����X�g
	TStringList *FileList;
	//�t�@�C�����ǂ��܂ŏ������ꂽ��
	int FileListPosition;

	//�p�X���[�h�̍ē���
	String RetryAtcFilePath;
	int RetryNum;

	//�p�X���[�h�t�@�C���p�X
	String PasswordFilePath;
	String ConfirmPasswordFilePath;

	// �t�@�C��/�t�H���_�̈Í�������
	void __fastcall FileEncrypt(void);
	// �t�@�C���𕜍����鏈��
	void __fastcall FileDecrypt(void);
	// �t�@�C�����R���y�A���鏈���i�Ƃ͌����Ă����ۂ͕��������j
	void __fastcall FileCompare(void);

	//�t�@�C���̔��ʂ��s�������𕪂��Ď��s
	void __fastcall DoExecute(TStringList *FileList);
	//���S�폜�������s�i�f�o�b�O�p�j
	void __fastcall DoDeleteFile(TStringList *FileList);
	//�t�H�[�����R���|�[�l���g��z�u����
	void __fastcall SetFormComponent(TObject *Sender);

	// �Í����t�@�C���̃w�b�_����i���ׂ�ATC�t�@�C���Ȃ�^��Ԃ��j
	bool __fastcall CheckAtcFileHeader(TStringList *FileList);

	//�Í����t�@�C����j�󂷂�
	bool __fastcall DestroyAtcFile(String AtcFilePath);






public:		// ���[�U�[�錾
	__fastcall TForm1(TComponent* Owner);


	//����ݒ�̃C���X�^���X
	TAttacheCaseOptionHandle *opthdl;


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
