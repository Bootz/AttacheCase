//---------------------------------------------------------------------------
#ifndef TAttacheCaseFileEncryptH
#define TAttacheCaseFileEncryptH
//---------------------------------------------------------------------------
#include <Classes.hpp>

#include "MsgEncrypt.hpp"

#include "rijndael.h"
#include "zlib.h"
#include "isaac.h"

//�o�b�t�@�T�C�Y
#define BUF_SIZE 32
#define LARGE_BUF_SIZE 1024
#define MARGIN_BUF_SIZE 256
#define FOOTER_BUF_SIZE 16
#define PASSWORD_BUF_SIZE 264 //MyPasscode + "_atc"

//�f�[�^�o�[�W����
#define ATC_DATA_FILE_VERSION 105
//�f�[�^�T�u�o�[�W����
#define ATC_DATA_SUB_VERSION 6     //ver.2.70�`
//#define ATC_DATA_SUB_VERSION 7       //ver.2.80�`

//�����T�C�Y4GB (4294967296-230=4294967066)
#define SIZE_4GB 4294967066

//�A���S���Y���^�C�v
#define TYPE_ALGORISM_BLOWFISH 0  // Blowfish
#define TYPE_ALGORISM_RIJNDAEL 1  // Rijndael


//---------------------------------------------------------------------------
class TAttacheCaseFileEncrypt : public TThread
{


private:

	//-----------------------------------
	// �ϐ�
	//-----------------------------------

	//�o�͂���Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹�邽�߂Ɋi�[����\����
	_WIN32_FIND_DATAW first_fd;

	//���b�Z�[�W�_�C�A���O
	String MsgText;
	TMsgDlgType MsgType;
	// --
	// mtWarning
	// mtError
	// mtInformation
	// mtConfirmation
	// mtCustom
	TMsgDlgButtons MsgButtons;
	TMsgDlgBtn MsgDefaultButton;
	int MsgReturnVal;
	String MsgReturnPath;

	//�����t�@�C���͂��ׂď㏑�����ĈÍ�������
	//�i���[�U�[���_�C�A���O�Łu���ׂĂ͂��v��I�������Ƃ� = true �j
	bool fOverwirteYesToAll;


	//-----------------------------------
	// �֐�
	//-----------------------------------

	//�w�b�_���𐶐�����
	bool __fastcall CreateHeaderData
		(TMemoryStream *pms,
		 TStringList *FileList, TStringList *FilePathList,
		 __int64 &AllTotalFileSize);
	//�Í�������t�@�C�����X�g�ƃt�@�C�����̃��X�g�𐶐�����
	__int64 __fastcall GetFileInfoList
		( int &Index, String DirPath, String FileName, String BasePath,
			TStringList *FileList, TStringList *DataList);
	// FILETIME�\���̂�TTimeStamp�ɕϊ����ĕ�����Ƃ��Ď擾����
	String __fastcall TimeStampToString(FILETIME ft);
	//�f�B�X�N�̋󂫗e�ʂ𒲂ׂ�
	__int64 __fastcall GetDiskFreeSpaceNum(String FilePath);
	//�������x�N�g���iIV�j�̐���
	void fillrand(char *buf, const int len);
	//���C���t�H�[���Ɋm�F���b�Z�[�W�𓊂��ď����𒆒f����
	void __fastcall PostConfirmMessageForm();
	//���C���t�H�[���ɏ㏑���̊m�F���b�Z�[�W�𓊂��ď����𒆒f����
	void __fastcall PostConfirmOverwriteMessageForm();



protected:
	void __fastcall Execute();



public:
	__fastcall TAttacheCaseFileEncrypt(bool CreateSuspended);
	__fastcall ~TAttacheCaseFileEncrypt();


	//-----------------------------------
	// �ϐ�
	//-----------------------------------

	//�p�X���[�h�L�[
	char key[32];

	int StatusNum;                     //�X�e�[�^�X���b�Z�[�W�ԍ��i�G���[���e���܂ށj

	String MsgErrorString;             //�G���[���b�Z�[�W

	int ProgressPercentNum;            //�i���p�[�Z���g
	String ProgressStatusText;         //�i���X�e�[�^�X
	String ProgressMsgText;            //�i���X�e�[�^�X���e

	int CompressRateNum;               //���k��
	bool fOver4gbOk;                   //4GB��������
	bool fKeepTimeStamp;               //�Í����t�@�C���̃^�C���X�^���v�����t�@�C���ɍ��킹��
	int fAllFilesPackOption;           //���ׂẴt�@�C�����P�ɂ܂Ƃ߂�
	bool fExeOutputOption;             //���s�`���o��
	bool fOptBrokenFileOption;         //�~�X�^�C�v�Ńt�@�C����j�󂷂邩�ۂ�
	int intOptMissTypeLimitsNumOption; //�^�C�v�~�X�ł����
	bool fConfirmOverwirte;            //�����t�@�C��������Ƃ��͏㏑���̊m�F������

	String AppExeFilePath;	           //�A�^�b�V�F�P�[�X�{�̂̏ꏊ
	String OutFilePath;                //�o�͂���Í����t�@�C��
	TStringList *InputFileList;        //�Í������錳�t�@�C�����X�g

	//-----------------------------------
	// �֐�
	//-----------------------------------

	//�p�X���[�h��������Z�b�g����
	void __fastcall SetPasswordString(AnsiString Password);
	//�p�X���[�h�Ƀo�C�i���l���Z�b�g����
	void __fastcall SetPasswordBinary(unsigned char *password);


};
//---------------------------------------------------------------------------
#endif /* TAttacheCaseFileEncryptH */

