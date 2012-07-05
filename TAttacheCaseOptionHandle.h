//----------------------------------------------------------------------
#ifndef TAttacheCaseOptionHandleH
#define TAttacheCaseOptionHandleH


#include <IniFiles.hpp>     //INI�t�@�C������p
#include <Registry.hpp>     //���W�X�g������p
#include <Math.hpp>

#include <shlobj.h>
#include <Shobjidl.h>

#include "sha1.h"
#include "blowfish.h"

#include "MsgOption.hpp"

#include "TGetAppInfoString.h"


//���W�X�g���̏ꏊ
#define ATTACHE_CASE_REGISTRY_PATH "Software\\Hibara\\AttacheCase"

#define TYPE_ENCODE_FILE 0 //�Í���
#define TYPE_DECODE_FILE 1 //������

//256 + 8�i�p�X���[�h�{�g�[�N���j
#define BUF_PASSWORD_SIZE 264

//SHA-1�n�b�V���T�C�Y�i160bit�j
//#define BUF_SHA1_SIZE 20
#define BUF_SHA1_SIZE 32
//�n�b�V���l���v�Z����Ƃ��̓ǂݍ��݃o�b�t�@
#define READ_FILE_BUF_SIZE 2048


//----------------------------------------------------------------------
class TAttacheCaseOptionHandle : public TObject
{
private:


	//�L���p�X���[�h�����W�X�g���܂���INI�t�@�C������ǂݏo��
	AnsiString __fastcall ReadMyPasswordFromRegistry(int Type);
	//�L���p�X���[�h�����W�X�g���܂���INI�t�@�C���ۑ�����
	bool __fastcall SaveMyPasswordToRegistry(String Password, int Type);

	//�n�[�h�f�B�X�N�̃{�����[�����x��ID���擾����
	String __fastcall GetVolumeLabelIDNumber(void);
	// �����O�t�@�C�������擾����
	String __fastcall GetLongFilePath(String FilePath);
	// Windows�������Ȃ��t�@�C����������̌����֐�
	bool __fastcall ChkFileNameChr(String ChkText);

	// SaveShellLink
	bool __fastcall SaveShellLink(IShellLink *psl, String LinkName, BOOL bRemember);


protected:

public:

	__fastcall TAttacheCaseOptionHandle();
	__fastcall ~TAttacheCaseOptionHandle();

	//===================================
	// �ϐ�
	//===================================

	// �ǂݍ��񂾐�̃p�X�i���W�X�g�� or INI�t�@�C���j
	String OptionPath;
	int OptType;                    // 0:���W�X�g��, 1:INI�t�@�C��, 2:�R�}���h���C������

	//�A�v���P�[�V�������
	String AppPath;                 //�{�̂��C���X�g�[�����ꂽ�t���p�X
	int VersionNum;                 //�o�[�W����

	//�t�H�[���|�W�V����
	int FormTop;
	int FormLeft;
	int FormWidth;
	int FormHeight;
	int WinStyle;

	int ActiveTabNum;               //�J���Ă����^�u

	//�y��{�ݒ�z
	String MyPassword;              //�L�����Ă���p�X���[�h

	bool fArg;                      //���s�������������邩
	bool fArgPassword;              //���s�����Ƀp�X���[�h���w��

	bool fMyEncodePasswordKeep;     //�Í����p�X���[�h���L�����邩
	bool fMyDecodePasswordKeep;     //�����p�X���[�h���L�����邩
	AnsiString MyEncodePassword;    //�L���Í����p�X���[�h
	AnsiString MyDecodePassword;    //�L���������p�X���[�h

	bool fMemPasswordExe;           //�L���p�X���[�h�ő����Ɏ��s����
	bool fOpenFolder;               //�t�H���_�̏ꍇ�ɕ�����ɊJ����
	bool fOpenFile;                 //���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ��
	bool fEndToExit;                //������ɏI�����邩
	bool fWindowForeground;         //�f�X�N�g�b�v�ōőO�ʂɃE�B���h�E��\������
	bool fNoHidePassword;           //�u*�v�ŉB�����p�X���[�h���m�F���Ȃ�����͂���
	bool fSaveToExeout;             //��Ɏ��Ȏ��s�`���ŏo�͂���
	bool fShowExeoutChkBox;         //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
	bool fAskEncDecode;             //�Í�/������������₢���킹��
	int ProcTypeWithoutAsk;         //�Í�/�����������i����ݒ�ɂ͂Ȃ��B�R�}���h���C���̂݁j
	bool fNoMultipleInstance;       //�����N�����Ȃ�

	//�y�ۑ��ݒ�z
	bool fSaveToSameFldr;           //�Í����t�@�C������ɓ����ꏊ�ɕۑ����邩
	String SaveToSameFldrPath;      //���̕ۑ��ꏊ
	bool fDecodeToSameFldr;         //��ɓ����ꏊ�փt�@�C���𕜍����邩
	String DecodeToSameFldrPath;    //���̕ۑ��ꏊ
	bool fConfirmOverwirte;         //�����t�@�C���̏㏑�����m�F���邩
	bool fKeepTimeStamp;            //�Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹��
	bool fSameTimeStamp;            //���������t�@�C���̃^�C���X�^���v�𐶐������ɂ���
	bool fAllFilePack;              //�����̃t�@�C�����Í�������ۂ͈�ɂ܂Ƃ߂�
	bool fFilesOneByOne;            //�t�H���_���̃t�@�C���͌ʂɈÍ���/��������
	bool fNoParentFldr;             //��������Ƃ��ɐe�t�H���_�𐶐����Ȃ�
	bool fExtInAtcFileName;         //�Í����t�@�C�����Ɋg���q���܂߂�
	bool fAutoName;                 //�����ňÍ����t�@�C������t������
	String AutoNameFormatText;	    //�����ŕt������t�@�C��������

	//�y�폜�ݒ�z
	bool fDelOrgFile;               //�Í���������A���t�@�C�����폜����
	bool fDelEncFile;               //������������A�Í����t�@�C�����폜����
	bool fShowDeleteChkBox;         //���C���t�H�[���Ƀ`�F�b�N�{�b�N�X��\������
	int fCompleteDelete;            //���S�폜���s����(0:�ʏ�C1:���S�폜�C2:���ݔ��j
	int DelRandNum;                 //���������񏑂����ݏ������邩
	int DelZeroNum;                 //NULL�����񏑂����ݏ������邩

	//�y����ݒ�z
	int CompressRate;               //���k��
	bool fCompareFile;              //�Í�������Ƀt�@�C���R���y�A���s����

	//�y�V�X�e���z
	bool fAssociationFile;          //�֘A�t���ݒ��ێ����邩
	int AtcsFileIconIndex;          //�t�@�C���A�C�R���ԍ�
	String UserRegIconFilePath;     //���[�U�[�w��̃t�@�C���A�C�R���p�X

	//�y���x�Ȑݒ�z
	bool fAllowPassFile;            //�p�X���[�h�t�@�C����������
	bool fCheckPassFile;            //�Í����Ƀp�X���[�h�t�@�C���������`�F�b�N����
	String PassFilePath;            //�Í����̃p�X���[�h�t�@�C���p�X
	bool fCheckPassFileDecrypt;     //�������Ƀp�X���[�h�t�@�C���������`�F�b�N����
	String PassFilePathDecrypt;     //�������̃p�X���[�h�t�@�C���p�X
	bool fNoErrMsgOnPassFile;       //�p�X���[�h�t�@�C�����Ȃ��ꍇ�G���[���o���Ȃ�
	bool fAddCamoExt;               //�Í����t�@�C���̊g���q���U������
	String CamoExt;                 //���̊g���q
	int MissTypeLimitsNum;          //�p�X���[�h�̃^�C�v�~�X�����񐔁iver.2.70�`�j
	bool fBroken;                   //�^�C�v�~�X�񐔂𒴂����Ƃ��Ƀt�@�C����j�󂷂邩�ۂ��iver.2.70�`�j

	//�y���̑��z�R�}���h���C������̂ݎw��
	bool fOver4GBok;                //4GB������e�F
	bool fHideMainForm;             //���C���t�H�[�����\��


	//===================================
	// �֐�
	//===================================

	//����ݒ�̓ǂݍ���
	bool __fastcall LoadOptionData(String IniFilePath);
	//����ݒ���L�^����
	bool __fastcall SaveOptionData(void);
	//�R�}���h���C���I�v�V��������̐ݒ�ǂݍ���
	bool __fastcall LoadOptionDataFromParamString(TStringList *FileList);

	//����ݒ��KeyValue�`����TStringList�Ŏ擾����
	void __fastcall GetKeyValueData(TStringList *KeyValueList);

	//�J�X�^�}�C�Y���ꂽ����������߂��ăt�@�C������u��������
	String __fastcall InterpretFormatText(String FileName, String InputText, int Num);
	//���ۂɃJ�X�^�}�C�Y����������߂��ďd���̂Ȃ�(�A�Ԃ�)�t�@�C���p�X��Ԃ�
	String __fastcall InterpretFormatTextToFilePath(String FilePath, String InputText);
	//�w��̃����_��������𐶐�
	String __fastcall MakeRandomFileName(int MojiNum, bool fNum, bool fKigo);
	//�t�@�C������SHA-1�n�b�V���l���擾����
	bool __fastcall GetSHA1HashFromFile(
		String FilePath,              //�p�X���[�h�t�@�C��
		unsigned char *sha1buffer,    //SHA-1�n�b�V���l�i160bit�j
		AnsiString &SHA1HashString,   //SHA-1�n�b�V���l�i������32�����j
		AnsiString &HeaderString );   //�w�b�_�f�[�^�i�擪������32�����j

	//�u����v�t�H���_�[�܂ł̃A�v���P�[�V�����t���p�X�𐶐�����
	String __fastcall CreateSendToFolderAppFullPath(void);
	// �V���[�g�J�b�g�t�@�C�����쐬����
	bool __fastcall CreateShortCutFile
		( String LinkFilePath,  String TargetFilePath, String Arguments, String WorkDir, int ShowCmd );

};


#endif

