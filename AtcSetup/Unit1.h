//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "MsgMain.hpp"

#include <Registry.hpp>     //���W�X�g������p
#include <shlobj.h>	        //�\���A�C�R�����V�X�e���X�V

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
	void __fastcall FormCreate(TObject *Sender);


private:	// ���[�U�[�錾

	String AtcExeFilePath;
	String UserRegIconFilePath;
	int AtcsFileIconIndex;


	//�f�[�^�t�@�C�����V�X�e���Ɋ֘A�t��
	bool __fastcall RegistDataFileAssociation(void);
	//�f�[�^�t�@�C���̊֘A�t���ݒ�̍폜����
	bool __fastcall DeleteDataFileAssociation(void);



public:		// ���[�U�[�錾
	__fastcall TForm1(TComponent* Owner);



};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
