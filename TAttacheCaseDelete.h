//---------------------------------------------------------------------------
#ifndef TAttacheCaseDeleteH
#define TAttacheCaseDeleteH
//---------------------------------------------------------------------------
#include <Classes.hpp>

#include "MsgDelete.hpp"

#define LARGE_BUF 1024

#include "shlobj.h"
#include "isaac.h"




//---------------------------------------------------------------------------
class TAttacheCaseDelete : public TThread
{


private:

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

	// �f�B���N�g��/�t�@�C�����ċA�I�ɍ폜����
	int __fastcall DeleteDirAndFiles(String DirPath, int &FileCount, int TotalFileCount,
			__int64 &CountFileSize, __int64 TotalFileSize);
	//�t�@�C���̊��S�폜
	int __fastcall CompleteDeleteFile(String FilePath, __int64 &CountFileSize, __int64 TotalFileSize);
	//���ݔ��ւ̈ړ�
	bool __fastcall GoToTrash(String Path);
	// �폜����t�@�C�����X�g���i�t�@�C�����A���v�T�C�Y�j�����W����
	int __fastcall GetDeleteFileListInfo
		(String DirPath, int &TotalFileCount, __int64 &TotalFileSize);
	//�����_���l�̐����iCRNG�j
	void fillrand(char *buf, const int len);

	//���C���t�H�[���Ɋm�F���b�Z�[�W�𓊂��ď����𒆒f����
	void __fastcall PostConfirmMessageForm();

protected:
	void __fastcall Execute();


public:
	__fastcall TAttacheCaseDelete(bool CreateSuspended);
	__fastcall ~TAttacheCaseDelete();

	int StatusNum;                     //�X�e�[�^�X���b�Z�[�W�ԍ��i�G���[���e���܂ށj
	String MsgErrorString;             //�G���[���b�Z�[�W

	TStringList *FileList;
	int Opt;                           // 0:�ʏ�폜, 1:���S�폜, 2:�S�~����
	int RandClearNum;                  // ���S�폜���̗����������݉�
	int ZeroClearNum;                  // ���S�폜����NULL�������݉�

	int ProgressPercentNum;            // �i���p�[�Z���g
	String ProgressStatusText;         // �i���X�e�[�^�X
	String ProgressMsgText;            // �i�����b�Z�[�W

};
//---------------------------------------------------------------------------
#endif	/* TAttacheCaseDeleteH */

