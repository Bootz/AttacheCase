//---------------------------------------------------------------------------

#include <vcl.h>





#pragma hdrstop

#include <tchar.h>

// �t�H���_�[���ɂ���pas�t�@�C�����������Ă܂Ƃ߂ď�������
bool SearchFolderForPasFiles(String DirPath);
// �錾���ꂽ���b�Z�[�W�萔���� initialization �ɏ�������
bool WriteToInitializationSection(String FilePath);

//---------------------------------------------------------------------------
#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{

int i;
String FilePath;
String MsgErrorString;

for (i = 1; i < argc; i++) {

	FilePath = argv[i];

	//�t�@�C��
	if (FileExists(FilePath) == true) {

		WriteToInitializationSection(FilePath);

	}
	//�f�B���N�g��
	else{

		if (DirectoryExists(FilePath) == true) {
			SearchFolderForPasFiles(FilePath);
		}
		else{
			MsgErrorString = "�w�肳�ꂽ�t�@�C��/�t�H���_�[��������܂���B\n�����𒆎~���܂��B\n"+FilePath;
			MessageDlg(MsgErrorString, mtConfirmation, TMsgDlgButtons()<<mbOK, 0);
			return 1;
		}

	}

}

return 0;


}
//===========================================================================
// �t�H���_�[���ɂ���pas�t�@�C�����������Ă܂Ƃ߂ď�������
//===========================================================================
bool SearchFolderForPasFiles(String DirPath)
{

TSearchRec sr;
String FilePath;
int ret  = FindFirst(DirPath + "*.pas", faAnyFile, sr);

while (ret == 0) {

	if (sr.Name != "." && sr.Name != "..") {

		FilePath = IncludeTrailingPathDelimiter(DirPath) + sr.Name;

		if (sr.Attr & faDirectory) {
			//�f�B���N�g���͖���
		}
		else{
			//�t�@�C��
			WriteToInitializationSection(FilePath);
		}
	}
	ret = FindNext(sr);
}

return(true);

}
//===========================================================================
// �錾���ꂽ���b�Z�[�W�萔���� initialization �ɏ�������
//===========================================================================
bool WriteToInitializationSection(String FilePath)
{

int i;
String fSection = "";

TStringList *FileList = new TStringList;
FileList->LoadFromFile(FilePath);

TStringList *OutFileList = new TStringList;

//�񋓂���萔���X�g��}������
TStringList *InitList = new TStringList;
InitList->Add("\n\t//Delphi�R���p�C���ɂ��œK����h��");

// '='��؂�̕�����𕪂���
TStringList* tsv = new TStringList();
tsv->StrictDelimiter = true;
tsv->Delimiter = '=';

for (i = 0; i < FileList->Count; i++) {

	if ( Trim(FileList->Strings[i]) == "resourcestring" ) {
		fSection = "resourcestring";
		OutFileList->Add(FileList->Strings[i]);
	}
	else if ( Trim(FileList->Strings[i]) == "implementation" ) {
		fSection = "implementation";
		OutFileList->Add(FileList->Strings[i]);
	}
	else if ( Trim(FileList->Strings[i]) == "initialization" ) {
		fSection = "initialization";
		OutFileList->Add(FileList->Strings[i]);
		//���߂Ă������e��f���o��
		OutFileList->Add(InitList->Text);
	}
	else if ( Trim(FileList->Strings[i]) == "end." ) {
		fSection = "end.";
		OutFileList->Add(FileList->Strings[i]);
	}
	else{
		if ( fSection == "resourcestring" ) {   // resourcestring���𐸍���...
			if (FileList->Strings[i].Pos("=") > 0) {
				tsv->DelimitedText = FileList->Strings[i];
				InitList->Add("\t" + Trim(tsv->Strings[0]) + ";");  //�萔�����������Ă���
			}
			else if (Trim(FileList->Strings[i]) == "") {          //��s���ꉞ�Č�
				InitList->Add("");
			}
			OutFileList->Add(FileList->Strings[i]);
		}
		else if ( fSection == "initialization" ) {
			// "initialization" �Z�N�V�����͂��łɏ����o�����̂Ŗ���
		}
		else{
			OutFileList->Add(FileList->Strings[i]);
		}
	}
}

OutFileList->SaveToFile(FilePath);

delete OutFileList;

delete InitList;
delete tsv;
delete FileList;

return(true);

}
//===========================================================================

