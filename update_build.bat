@echo OFF
@echo. ======================================================================
@echo. ���̃o�b�`�t�@�C���ł́A�K�v�ȃt�@�C�����e������R�s�[���Ă��āA
@echo. �ŏI�I�Ȑ��i�Ƃ��� �u�A�^�b�V�F�P�[�X�v���p�b�N���A�C���X�g�[���[��
@echo. �쐬����Ƃ���܂ōs���܂��B���̏����ɂ́A���炩���߃C���X�g�[������
@echo. �����ׂ��c�[��������������܂��B
@echo. 
@echo. �ȉ��̃c�[��������̏ꏊ�ɃC���X�g�[������Ă��邱�Ƃ��m�F���Ă���
@echo. ���s���Ă��������B
@echo. 
@echo. ��Inno Setup�i�C���X�g�[���[�쐬�\�t�g�j
@echo. ��UPX�i���s�t�@�C�����k�\�t�g�j
@echo. 
@echo. ======================================================================

set /p NUM="�����[�X�����iyyyy mm dd�j���p�X�y�[�X��؂�œ��͂��Ă��������B>"

@echo. 
@echo. -----------------------------------
@echo. HTML Help�t�@�C���̐���
@echo. -----------------------------------




@echo 
@echo -----------------------------------
@echo �K�v�t�@�C���̃R�s�[
@echo -----------------------------------

mkdir installer\bin

@rem  �K�v�t�@�C����installer�փR�s�[
copy readme\readme.txt installer\bin\readme.txt
copy help\Output\chm\AttacheCase.chm installer\bin\AttacheCase.chm
copy AtcSetup\AtcSetup.exe installer\bin\AtcSetup.exe
copy exeout\exeout.exe installer\bin\exeout.exe
copy AttacheCase.exe installer\bin\AttacheCase.exe


@echo. 
@echo. -----------------------------------
@echo. UPX�ł̏���
@echo. -----------------------------------

upx308w\upx --compress-icons=0 -6 installer\bin\AttacheCase.exe
upx308w\upx --compress-resources=0 --best installer\bin\exeout.exe

@echo. 
@echo. -----------------------------------
@echo. �e�t�@�C���̃^�C���X�^���v��ύX
@echo. -----------------------------------

tools\chgtm\chgtm.exe "installer\bin\AttacheCase.exe" %NUM%
tools\chgtm\chgtm.exe "installer\bin\exeout.exe" %NUM%
tools\chgtm\chgtm.exe "installer\bin\AtcSetup.exe" %NUM%
tools\chgtm\chgtm.exe "installer\bin\AttacheCase.chm" %NUM%
tools\chgtm\chgtm.exe "installer\bin\readme.txt" %NUM%

@echo. 
@echo. -----------------------------------
@echo. ���Ȏ��s�t�@�C���`���̃}�[�W
@echo. -----------------------------------

tools\merge\merge.exe installer\bin\AttacheCase.exe installer\bin\exeout.exe


@echo. 
@echo. -----------------------------------
@echo. �C���X�g�[���p�b�P�[�W�̐���
@echo. -----------------------------------

if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
"%ProgramFiles(x86)%\Inno Setup 5\ISCC.exe" installer\AttacheCase.iss
) else (
"%ProgramFiles%\Inno Setup 5\ISCC.exe" installer\AttacheCase.iss
)

@echo. 
@echo. -----------------------------------
@echo. �n�b�V���l���e�L�X�g�t�@�C���ۑ�
@echo. -----------------------------------

tools\gethash\gethash.exe installer\*.exe


@echo. 
@echo. -----------------------------------
@echo. bin�f�B���N�g���̍폜
@echo. -----------------------------------

rd /s /q "installer\bin"

:END

@echo 
@echo **********************************************************************
@echo �������������܂����B
@echo **********************************************************************
@echo 


pause

