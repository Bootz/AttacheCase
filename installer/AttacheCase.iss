#define MyAppVer GetFileVersion("..\AttacheCase.exe")
#define MyAppVerNum StringChange(MyAppVer, ".", "")
#define BetaVerString "��"
#define BetaVerNum "b"

[Setup]
AppName=�A�^�b�V�F�P�[�X
AppVersion={#MyAppVer}
AppVerName=�A�^�b�V�F�P�[�X ver.{#MyAppVer}{#BetaVerString}
DefaultGroupName=�A�^�b�V�F�P�[�X
OutputBaseFilename=atcs{#MyAppVerNum}{#BetaVerNum}
DefaultDirName={pf}\AttacheCase
UsePreviousAppDir=yes
AppendDefaultDirName=yes 
OutputDir=.\

;-----------------------------------
;�C���X�g�[���v���O����
;-----------------------------------
VersionInfoVersion={#MyAppVer}
VersionInfoDescription=�Í����\�t�g�E�F�A�u�A�^�b�V�F�P�[�X�v���Z�b�g�A�b�v����v���O����
AppCopyright=Copyright(C) 2012 M.Hibara, All rights reserved.
;SetupIconFile=icon\main_icon.ico
;�E�B�U�[�h�y�[�W�ɕ\�������O���t�B�b�N�i*.bmp: 164 x 314�j
WizardImageFile=bmp\installer_pic_01.bmp
;�E�B�U�[�h�y�[�W�ɕ\�������O���t�B�b�N���g�傳��Ȃ�
WizardImageStretch=no
;���̌��ԐF
WizardImageBackColor=$ffffff 
;�E�B�U�[�h�y�[�W�̉E�㕔���̃O���t�B�b�N�i*.bmp: 55 x 58�j
WizardSmallImageFile=bmp\installer_pic_02.bmp
;�i���\���H
ShowTasksTreeLines=yes

;------------------------------------------
;�u�v���O�����̒ǉ��ƍ폜�v�_�C�A���O���
;------------------------------------------
;�z�z��
AppPublisher=Hibara, Mitsuhiro
;�A�v���P�[�V�����z�z�� Web�T�C�g�� URL
AppPublisherURL=http://hibara.org/
;�A����
AppContact=m@hibara.org
;�T�|�[�g�T�C�gURL
AppSupportURL=http://hibara.org/software/
;ReadMe�t�@�C���p�X
AppReadmeFile="{app}\AttacheCase\readme.txt"
;���i�X�V���URL
AppUpdatesURL=http://hibara.org/software/attachecase/
;�A�v���P�[�V�����̐���
AppComments=�t�@�C��/�t�H���_�[�Í����\�t�g�E�F�A

[Files]
Source: "bin\AttacheCase.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "bin\AtcSetup.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "bin\AttacheCase.chm"; DestDir: "{app}"; Flags: ignoreversion
Source: "bin\readme.txt"; DestDir: "{app}"; Flags: isreadme  ignoreversion

[Languages]
Name: japanese; MessagesFile: compiler:Languages\Japanese.isl

[Icons]
Name: "{group}\�A�^�b�V�F�P�[�X"; Filename: "{app}\AttacheCase.exe"; WorkingDir: "{app}"
Name: "{group}\�w���v�t�@�C��"; Filename: "{app}\AttacheCase.chm"; WorkingDir: "{app}"
Name: "{group}\�A���C���X�g�[��"; Filename: "{uninstallexe}"
Name: "{commondesktop}\�A�^�b�V�F�P�[�X"; Filename: "{app}\AttacheCase.exe"; WorkingDir: "{app}"; Tasks: desktopicon

[Tasks]
Name: desktopicon; Description: "�f�X�N�g�b�v�ɃV���[�g�J�b�g�A�C�R�����쐬����"
Name: association; Description: "*.ATC�t�@�C�����A�^�b�V�F�P�[�X�Ɋ֘A�t������";

[Run]
Filename: "{app}\AtcSetup.exe"; Parameters: "0"; Tasks: association; Flags: nowait skipifsilent runascurrentuser

[Registry]
;�i�A���C���X�g�[�����Ɂj�A�^�b�V�F�P�[�X�̓���ݒ���폜
Root: HKCU; Subkey: "Software\Hibara\AttacheCase"; Flags: uninsdeletekey
;�i�A���C���X�g�[�����Ɂj�֘A�t���ݒ���폜
Root: HKCR; Subkey: "AttacheCase.DataFile"; Flags: uninsdeletekey
Root: HKCR; Subkey: ".atc"; Flags: uninsdeletekey


