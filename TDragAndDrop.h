#ifndef TDragAndDropH
#define TDragAndDropH


#include <windows.h>
#include <oleidl.h>
#include <vcl.h>

#include "shlobj.h"
//---------------------------------------------------------------------------
class TDragAndDrop : public IDropTarget
{

public:
	//�R���X�g���N�^
	__fastcall TDragAndDrop::TDragAndDrop(TForm *_Form);
	//�f�X�g���N�^
	__fastcall ~TDragAndDrop(void);


	//�����t�@�C���̎󂯓���������邩
	bool fMultipleFilesOk;
	//�h���b�v�C���[�W�^�C�v
	DROPIMAGETYPE DropImageType;

	/*
	typedef enum {
		DROPIMAGE_INVALID = -1,
		DROPIMAGE_NONE = 0,
		DROPIMAGE_COPY = DROPEFFECT_COPY,
		DROPIMAGE_MOVE = DROPEFFECT_MOVE,
		DROPIMAGE_LINK = DROPEFFECT_LINK,
		DROPIMAGE_LABEL = 6,
		DROPIMAGE_WARNING = 7
	} DROPIMAGETYPE;
	*/

	//OLE�h���b�v����t�H�[���ւ̃|�C���^
	TForm *Form;
	//���z�֐�
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
	virtual HRESULT __stdcall DragEnter(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	virtual HRESULT __stdcall DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	virtual HRESULT __stdcall DragLeave();
	virtual HRESULT __stdcall Drop(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	//Form�ւ̃R�[���o�b�N�֐��i�o�^����t�H�[�����ɂ�����K�v����j
	void __fastcall (__closure *FilesDragOver)(POINTL ptl);
	void __fastcall (__closure *FilesDragLeave)(void);
	void __fastcall (__closure *FilesDragEnd)(POINTL ptl, String FileListText);

private:
	LONG _RefCount;
	IDataObject *_DataObject;

	int FileCount;


};
//---------------------------------------------------------------------------

#endif


