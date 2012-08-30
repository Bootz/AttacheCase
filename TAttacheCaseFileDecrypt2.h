//---------------------------------------------------------------------------
#ifndef TAttacheCaseFileDecrypt2H
#define TAttacheCaseFileDecrypt2H
//---------------------------------------------------------------------------
#include <Classes.hpp>

#include "MsgDecrypt.hpp"

#include "rijndael.h"
#include "zlib.h"
#include "isaac.h"

//�o�b�t�@�T�C�Y
#define BUF_SIZE 32
#define LARGE_BUF_SIZE 1024
#define MARGIN_BUF_SIZE 256
#define FOOTER_BUF_SIZE 16
#define PASSWORD_BUF_SIZE 264 //MyPasscode + "_atc"

//�����T�C�Y4GB (4294967296-230=4294967066)
#define SIZE_4GB 4294967066

//-----------------------------------
//�f�[�^�o�[�W�����i�������������
// ���ʃo�[�W�����ŕ����ł��Ȃ��G���[����������j
#define ATC_DATA_FILE_VERSION 105
//-----------------------------------
//�f�[�^�T�u�o�[�W����
#define ATC_DATA_SUB_VERSION 6     //ver.2.70�`


//�A���S���Y���^�C�v
#define TYPE_ALGORISM_BLOWFISH 0  // Blowfish
#define TYPE_ALGORISM_RIJNDAEL 1  // Rijndael


//---------------------------------------------------------------------------
class TAttacheCaseFileDecrypt2 : public TThread
{

private:

	//�p�X���[�h�L�[
	char key[32];

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

	//�u���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ���v�ꎞ�I�Ȑݒ�
	bool fTempOpenFile;
	//�ŏ�ʂ̃t�H���_�[���J������
	bool fOpenFolderOnce;
	//�����t�@�C��/�t�H���_�[�͂��ׂď㏑�����ĕ�������
	//�i���[�U�[���_�C�A���O�Łu���ׂĂ͂��v��I�������Ƃ� = true �j
	bool fOverwirteYesToAll;

	//�o�b�t�@�̓���
	__int64 __fastcall InputBuffer(
		int &buff_size, char *source_buffer, char *chain_buffer,
		TFileStream *fsIn, bool &fOpen,
		__int64 TotalSize, __int64 AllTotalSize
	);
	//�o�b�t�@�̏o��
	int __fastcall OutputBuffer(
		char *output_buffer, int buff_size,
		TFileStream *&fsOut, bool &fOpen,
		TStringList *FileList, int &FileIndex,
		__int64 *FileSizeList, int *FileAttrList,
		int *FileDtChangeList, int *FileTmChangeList,
		int *FileDtCreateList, int *FileTmCreateList
	);

	//�t�@�C��/�f�B���N�g���̃^�C���X�^���v��ݒ肷��
	void __fastcall FileSetTimeStamp
		(String FilePath,
		 int tsChangeDateNum, int tsChangeTimeNum, int tsCreateDateNum, int tsCreateTimeNum,
		 bool fNow, bool fDir);
	//�����f�[�^�̐���
	void fillrand(char *buf, const int len);
	//�f�B�X�N�̋󂫗e�ʂ𒲂ׂ�
	__int64 __fastcall GetDiskFreeSpaceNum(String FilePath);
	//���C���t�H�[���Ɋm�F���b�Z�[�W�𓊂��ď����𒆒f����
	void __fastcall PostConfirmMessageForm();
	//���C���t�H�[���ɏ㏑���̊m�F���b�Z�[�W�𓊂��ď����𒆒f����
	void __fastcall PostConfirmOverwriteMessageForm();



protected:
	void __fastcall Execute();


public:
	__fastcall TAttacheCaseFileDecrypt2(bool CreateSuspended);
	__fastcall ~TAttacheCaseFileDecrypt2();

	//-----------------------------------
	// �ϐ�
	//-----------------------------------

	int StatusNum;                     //�X�e�[�^�X
	String MsgAppendString;            //���b�Z�[�W�{�b�N�X�ɕ\������t���e�L�X�g
	String StatusMsg;                  //�ǉ��X�e�[�^�X���e�i�t�@�C�����Ȃǖ|��s�v�̂��́j

	int ProgressPercentNum;            //�i���p�[�Z���g
	String ProgressStatusText;         //�i���X�e�[�^�X
	String ProgressMsgText;            //�i���X�e�[�^�X���e

	bool fCompare;                     //�R���y�A
	TStringList *CompareFileList;      //�R���y�A���錳�t�@�C�����X�g

	bool fOpenFolder;                  //�t�H���_�̏ꍇ�ɕ�����ɊJ����
	bool fOpenFile;                    //���������t�@�C�����֘A�t�����ꂽ�\�t�g�ŊJ��
	bool fConfirmOverwirte;            //�����t�@�C���̏㏑�����m�F���邩

	String AppExeFilePath;	           //�A�^�b�V�F�P�[�X�{�̂̏ꏊ
	String AtcFilePath;                //���͂���Í����t�@�C���p�X
	String OutDirPath;                 //�o�͂���f�B���N�g��

	int NumOfTrials;                   //���s��
	int TypeLimits;                    //�~�X�^�C�v�� 0�`10
	bool fDestroy;                     //�j�󂷂邩�ۂ� 0 or 1


	//-----------------------------------
	// �֐�
	//-----------------------------------

	//�p�X���[�h��������Z�b�g����iver.1.* �`�j
	//void __fastcall SetPasswordString(AnsiString Password);

	//�p�X���[�h�Ƀo�C�i���l���Z�b�g����
	void __fastcall SetPasswordBinary(char *password);



};
//---------------------------------------------------------------------------
#endif	/* TAttacheCaseFileDecryptH */

