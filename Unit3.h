//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>;

#include "Unit1.h"
#include "Unit4.h"

#include "help.h"
#include "Windowsx.h"
#include "MsgUnit3.hpp"

#include "TDragAndDrop.h"


#define FILE_ICON_NUM 4

//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
	TPanel *Panel1;
	TButton *cmdOK;
	TButton *cmdCancel;
	TStatusBar *StatusBar1;
	TImage *imgBat;
	TImage *imgReg;
	TImage *imgIni;
	TPageControl *PageControl1;
	TTabSheet *TabBasic;
	TTabSheet *TabSave;
	TPanel *PanelMenu;
	TImage *imgBasic;
	TImage *imgSave;
	TImage *imgMovement;
	TImage *imgDelete;
	TImage *imgAdvanced;
	TTabSheet *TabDelete;
	TTabSheet *TabMovement;
	TTabSheet *TabSystem;
	TImage *imgSystem;
	TTabSheet *TabAdvanced;
	TPanel *PanelBasicCaption;
	TPanel *PanelSaveCaption;
	TPanel *PanelDeleteCaption;
	TPanel *PanelMovementCaption;
	TPanel *PanelSystemCaption;
	TPanel *PanelAdvancedCaption;
	TImage *imgFocusLight;
	TLabel *lblBasic;
	TLabel *lblSave;
	TLabel *lblDelete;
	TLabel *lblMovement;
	TLabel *lblSystem;
	TLabel *lblAdvanced;
	TImage *imgSelectCursor;
	TCheckBox *chkNoMultipleInstance;
	TCheckBox *chkMyEncPasswordKeep;
	TButtonedEdit *btneditMyEncPassword;
	TCheckBox *chkMyDecPasswordKeep;
	TButtonedEdit *btneditMyDecPassword;
	TCheckBox *chkMyPasswordExe;
	TCheckBox *chkOpenFolder;
	TCheckBox *chkOpenFile;
	TCheckBox *chkEndToExit;
	TCheckBox *chkWindowForeground;
	TCheckBox *chkNoHidePassword;
	TCheckBox *chkSaveToExeout;
	TCheckBox *chkShowExeoutChkBox;
	TCheckBox *chkAskEncDecode;
	TCheckBox *chkSaveToSameFldr;
	TButtonedEdit *btneditSaveToSameFldrPath;
	TImageList *ImageList1;
	TCheckBox *chkDecodeToSameFldr;
	TButtonedEdit *btneditDecodeToSameFldrPath;
	TCheckBox *chkConfirmOverwirte;
	TRadioGroup *radiogrpMultipleFiles;
	TCheckBox *chkNoParentFldr;
	TCheckBox *chkKeepTimeStamp;
	TCheckBox *chkSameTimeStamp;
	TCheckBox *chkExtInAtcFileName;
	TCheckBox *chkAutoName;
	TButtonedEdit *btneditAutoNameFormatText;
	TLabel *lblAutoFormatExample;
	TCheckBox *chkDelOrgFile;
	TCheckBox *chkDelEncFile;
	TCheckBox *chkShowDeleteChkBox;
	TGroupBox *gbDeleteOption;
	TRadioButton *optNormalDelete;
	TRadioButton *optGoToTrash;
	TRadioButton *optCompleteDelete;
	TLabeledEdit *txtDelRandNum;
	TUpDown *UpDownDelRand;
	TImage *imgArrowEnabled;
	TImage *imgArrowDiabled;
	TLabeledEdit *txtDelZeroNum;
	TUpDown *UpDownDelZero;
	TGroupBox *gbCompressRate;
	TCheckBox *chkCompress;
	TTrackBar *TrackBar1;
	TLabel *lblCompressRateDetail;
	TLabel *lblCompressRate;
	TGroupBox *gbCompare;
	TCheckBox *chkCompareFile;
	TGroupBox *gbWindowsSystemOption;
	TButton *cmdAssociateAtcFile;
	TButton *cmdUnAssociateAtcFile;
	TButton *cmdShortCutToSendToFileDir;
	TGroupBox *gbChangeFileIcon;
	TButton *cmdAddFileIcon;
	TGroupBox *gbOutputOptionData;
	TButton *cmdOutputOptionData;
	TButton *cmdChangeTempOptionData;
	TGroupBox *gbPasswordFile;
	TCheckBox *chkAllowPassFile;
	TCheckBox *chkCheckPassFile;
	TButtonedEdit *btneditPassFilePath;
	TCheckBox *chkCheckPassFileDecrypt;
	TButtonedEdit *btneditPassFilePathDecrypt;
	TCheckBox *chkNoErrMsgOnPassFile;
	TGroupBox *gbCamoExt;
	TCheckBox *chkAddCamoExt;
	TEdit *txtCamoExt;
	TLabel *lblCamoExtDetail;
	TGroupBox *gbTypeLimit;
	TComboBox *cmbMissTypeLimitsNum;
	TLabel *lblMissTypeLimitsNum;
	TCheckBox *chkBroken;
	TLabel *lblTypeLimitAlertMsg;
	TLabel *lblAdvancedOptionAlertMsg;
	TTabSheet *TabDebug;
	TValueListEditor *ValueListEditor1;
	TPanel *PanelDebugCaption;
	TImageList *ImageList2;
	TComboBoxEx *comboDataIcon;
	TOpenDialog *OpenDialog1;
	TImage *Image1;
	TImage *Image2;
	TPopupMenu *PopupMenu1;
	TImageList *ImageList3;
	TMenuItem *pmnuInsertFileName;
	TMenuItem *pmnuInsertFileExt;
	TMenuItem *pmnuSeparator;
	TMenuItem *pmnuInsertDatetime;
	TMenuItem *pmnuInsertSerialNum;
	TMenuItem *pmnuInsertRandomText;
	TMenuItem *pmnuInsertFileNameHead;
	TMenuItem *pmnuInsertFileNameEnd;
	TMemo *Memo1;
	TBalloonHint *BalloonHint1;
	TButton *cmdHelp;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall cmdCancelClick(TObject *Sender);
	void __fastcall cmdOKClick(TObject *Sender);
	void __fastcall imgBasicMouseEnter(TObject *Sender);
	void __fastcall imgSaveMouseEnter(TObject *Sender);
	void __fastcall imgDeleteMouseEnter(TObject *Sender);
	void __fastcall imgMovementMouseEnter(TObject *Sender);
	void __fastcall imgSystemMouseEnter(TObject *Sender);
	void __fastcall imgAdvancedMouseEnter(TObject *Sender);
	void __fastcall imgBasicClick(TObject *Sender);
	void __fastcall imgSaveClick(TObject *Sender);
	void __fastcall imgDeleteClick(TObject *Sender);
	void __fastcall imgMovementClick(TObject *Sender);
	void __fastcall imgSystemClick(TObject *Sender);
	void __fastcall imgAdvancedClick(TObject *Sender);
	void __fastcall PanelMenuDblClick(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall optNormalDeleteClick(TObject *Sender);
	void __fastcall optGoToTrashClick(TObject *Sender);
	void __fastcall optCompleteDeleteClick(TObject *Sender);
	void __fastcall btneditMyEncPasswordLeftButtonClick(TObject *Sender);
	void __fastcall btneditMyDecPasswordLeftButtonClick(TObject *Sender);
	void __fastcall btneditSaveToSameFldrPathLeftButtonClick(TObject *Sender);
	void __fastcall btneditDecodeToSameFldrPathLeftButtonClick(TObject *Sender);
	void __fastcall btneditPassFilePathLeftButtonClick(TObject *Sender);
	void __fastcall btneditPassFilePathDecryptLeftButtonClick(TObject *Sender);
	void __fastcall chkAllowPassFileClick(TObject *Sender);
	void __fastcall chkCheckPassFileClick(TObject *Sender);
	void __fastcall chkCheckPassFileDecryptClick(TObject *Sender);
	void __fastcall chkAddCamoExtClick(TObject *Sender);
	void __fastcall pmnuInsertFileNameClick(TObject *Sender);
	void __fastcall pmnuInsertFileExtClick(TObject *Sender);
	void __fastcall pmnuInsertDatetimeClick(TObject *Sender);
	void __fastcall pmnuInsertSerialNumClick(TObject *Sender);
	void __fastcall pmnuInsertRandomTextClick(TObject *Sender);
	void __fastcall pmnuInsertFileNameHeadClick(TObject *Sender);
	void __fastcall pmnuInsertFileNameEndClick(TObject *Sender);
	void __fastcall chkMyEncPasswordKeepClick(TObject *Sender);
	void __fastcall chkMyDecPasswordKeepClick(TObject *Sender);
	void __fastcall chkSaveToSameFldrClick(TObject *Sender);
	void __fastcall chkDecodeToSameFldrClick(TObject *Sender);
	void __fastcall cmdAssociateAtcFileClick(TObject *Sender);
	void __fastcall cmdUnAssociateAtcFileClick(TObject *Sender);
	void __fastcall cmdShortCutToSendToFileDirClick(TObject *Sender);
	void __fastcall chkAutoNameClick(TObject *Sender);
	void __fastcall chkDelOrgFileClick(TObject *Sender);
	void __fastcall chkDelEncFileClick(TObject *Sender);
	void __fastcall chkShowDeleteChkBoxClick(TObject *Sender);
	void __fastcall cmdHelpClick(TObject *Sender);
	void __fastcall btneditAutoNameFormatTextChange(TObject *Sender);

private:	// ���[�U�[�錾

	//���[�U�[�w��̃A�C�R���t�@�C���p�X�iOK�{�^�����������܂ł̃e���|�����j
	String TempUserRegIconFilePath;

	//�ݒ�l�𓮍�ݒ�t�H�[���ɔ��f�\������
	void __fastcall ShowOptionData(void);
	//����ݒ�t�H�[������ݒ�l�ɔ��f����i�e���f�B�A�֕ۑ����s���j
	void __fastcall SaveOptionData(void);
	//�t�@�C���A�C�R�����R���{�{�b�N�X�֓o�^����
	void __fastcall RegIconFileToComboBox(void);
	//UAC�G���x�[�V������v�����Ċ֘A�t���v���O���������s
	bool __fastcall RunAsAdmin(int Option);
	//�u'�폜�̏ڍאݒ�F'�v�O���[�v�{�b�N�X���̗L���E�����𐧌䂷��
	bool __fastcall DeleteGroupEnabled(void);

	//�p�l�����j���[�\���̃��t���b�V�����s��
	void __fastcall PanelMenuRefresh(void);







public:		// ���[�U�[�錾
	__fastcall TForm3(TComponent* Owner);


	//�L���p�X���[�h���ύX���ꂽ�Ƃ��Ɋi�[����
	AnsiString TempMyEncodePassword;
	AnsiString TempMyDecodePassword;

	//OLE�h���b�O���h���b�v�̃R�[���o�b�N�֐�
	void __fastcall FilesDragOver(POINTL ptl);
	void __fastcall FilesDragLeave(void);
	void __fastcall FilesDragEnd(POINTL ptl, String FileListText);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
