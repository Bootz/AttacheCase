unit MsgUnit1;

interface

resourcestring

  //�p�l��
  DRAG_AND_DROP_HERE                        = '�Í���/��������t�@�C�����t�H���_��'+#13+'�����փh���b�O���h���b�v���Ă��������B';
  INPUT_PASSWORD                            = '�t�@�C��/�t�H���_���Í������܂��B�p�X���[�h����͂��Ă��������F';
  CONFIRM_PASSWORD                          = '�m�F�̂��߁A������x�p�X���[�h����͂��Ă��������F';
  INPUT_DECRYPT_PASSWORD                    = '�������Č��̃t�@�C��/�t�H���_�ɖ߂��܂��B�p�X���[�h����͂��Ă��������F';

	//�_�C�A���O
	DIALOG_SELECT_DIRECTORY_TEXT              = '�Í�������f�B���N�g���i�t�H���_�j��I�����Ă��������B';

	DIALOG_OPEN_FILES_FOR_ENCRYPTION_TITLE    = '�Í�������t�@�C�����J��';
	DIALOG_OPEN_FILES_FOR_ENCRYPTION_FILTER   = '���ׂẴt�@�C��(*.*)|*.*';
	DIALOG_OPEN_FILES_FOR_DECRYPTION_TITLE    = '��������A�^�b�V�F�P�[�X�t�@�C�����J��';
	DIALOG_OPEN_FILES_FOR_DECRYPTION_FINTER   = '�A�^�b�V�F�P�[�X�t�@�C��(*.atc)|*.atc|���ׂẴt�@�C��(*.*)|*.*';
	DIALOG_SAVE_FILES_FOR_ENCRYPTION_TITLE    = '�Í������ꂽ�A�^�b�V�F�P�[�X�t�@�C�����̓���';
	DIALOG_SAVE_FILES_FOR_ENCRYPTION_FILTER   = '�A�^�b�V�F�P�[�X�t�@�C��(*.atc)|*.atc|���s�`���t�@�C��(*.exe)|(*.exe)|���ׂẴt�@�C��(*.*)|*.*';

	//�_�C�A���O�L���v�V����
	DIALOG_SAVE_AS_FOLDER_CAPTION             = '�����t�H���_�[�̕ۑ�';
	DIALOG_SAVE_AS_FILE_CAPTION               = '�����t�@�C���̕ۑ�';
	//�_�C�A���O�t�B���^�[
	DIALOG_SAVE_AS_FILTER                     = '�t�@�C���t�H���_�[|*';
	//�_�C�A���O�{�^���L���v�V����
	DIALOG_BUTTON_NAME_OVERWITE_YES_TO_ALL    = '�S�ď㏑��(&W)'; // YesToAll
	DIALOG_BUTTON_NAME_OVERWITE_YES           = '�㏑��(&O)';     // Yes
	DIALOG_BUTTON_NAME_OVERWITE_NO            = '�ʖ��ۑ�(&A)';   // No
	DIALOG_BUTTON_NAME_OVERWITE_CANCEL        = '�L�����Z��(&C)'; // Cancel

	//�`�F�b�N�{�b�N�X
	CHECK_BOX_EXEFILE_OUT                     = '���s�`���o��(&X)';

	//���b�Z�[�W�L���v�V����
	MSG_CAPTION_ERROR                         = '�G���[';
	MSG_CAPTION_CONFIRMATION                  = '�m�F';

  //���b�Z�[�W
  MSG_BROKEN_ATC_FILE                       = '���̈Í����t�@�C���̓p�X���[�h���͂Ɏ��s���Ĕj�󂳂�Ă���悤�ł��B';
  MSG_FILE_OPEN_ERROR                       = '�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
	MSG_CONFIRM_ENCRYPT_OR_DECRYPT            = '�h���b�O���h���b�v���ꂽ�t�@�C���܂��̓t�H���_�[���ǂ̂悤�ɏ������܂����H';
	MSG_ERROR_SAVE_ENC_TO_FOLDER_NOT_EXISTS   = '�ۑ������̃t�H���_�[��������܂���B�ۑ��ݒ���Ċm�F���Ă��������B'+#13+
	                                            '�Í����𒆎~���܂��B';
	MSG_ERROR_SAVE_DEC_TO_FOLDER_NOT_EXISTS   = '�ۑ������̃t�H���_�[��������܂���B�ۑ��ݒ���Ċm�F���Ă��������B'+#13+
	                                            '���������𒆎~���܂��B';
	MSG_ERROR_NOT_FOUND_ENC_PASSWORD_FILE     = '����ݒ�Ŏw�肳�ꂽ�Í�������p�X���[�h�t�@�C����������܂���B'+#13+
	                                            '�ݒ���m�F���Ă��������B';
	MSG_ERROR_NOT_FOUND_DEC_PASSWORD_FILE     = '����ݒ�Ŏw�肳�ꂽ��������p�X���[�h�t�@�C����������܂���B'+#13+
	                                            '�ݒ���m�F���Ă��������B';
	MSG_ERROR_OPEN_PASSWORD_FILE              = '�p�X���[�h�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
	MSG_ERROR_MISMATCH_PASSWORD_FILE          = '��ɓ��͂��ꂽ�p�X���[�h�t�@�C���Ƃ������܂��BSHA-1�n�b�V���l����v���܂���ł����B'+#13+
	                                            '�Í������邱�Ƃ��ł��܂���B';
	MSG_ERROR_NOT_EXISTS_COMPAER_FIlE         = '�R���y�A����Í����t�@�C���܂��̓t�H���_�[��������܂���B'+#13+
	                                            '�R���y�A�Ɏ��s���܂����B';

  //���x��
  LABEL_STATUS_TITLE_ENCRYPTING             = '�Í������Ă��܂�...';
  LABEL_STATUS_TITLE_DECRYPTING             = '�������Ă��܂�...';
  LABEL_STATUS_TITLE_LISTING                = '�t�@�C�����X�g�̐���';
  LABEL_STATUS_TITLE_ERROR                  = '�G���[';
  LABEL_STATUS_TITLE_USER_CANCEL            = '�L�����Z��';
  LABEL_STATUS_TITLE_COMPLETE               = '����';

  LABEL_STATUS_DETAIL_PREPARING_ENCRYPT     = '�Í������邽�߂̏��������Ă��܂�...';
  LABEL_STATUS_DETAIL_FAILED_ENCRYPT        = '�Í����Ɏ��s���܂����B';
  LABEL_STATUS_DETAIL_STOPPED_ENCRYPT       = '�Í��������~����܂����B';
  LABEL_STATUS_DETAIL_PREPARING_DECRYPT     = '�������邽�߂̏��������Ă��܂�...';
  LABEL_STATUS_DETAIL_FAILED_DECRYPT        = '�����Ɏ��s���܂����B';
  LABEL_STATUS_DETAIL_STOPPED_DECRYPT       = '�������������~����܂����B';



	//�{�^��
	BUTTON_CAPTION_ENCRYPTION                 = '�Í�������(&E)';
	BUTTON_CAPTION_DECRYPTION                 = '��������(&D)';
	BUTTON_CAPTION_CANCEL                     = '�L�����Z��(&C)';

	//�o���[���q���g
	BALLOON_HINT_PASSWOED_MISMATCH            = '��ɓ��͂��ꂽ�p�X���[�h�Ƃ������܂��B';
	BALLOON_HINT_PASSWOED_CONFIRMATION        = '�S�p�E���p�̂������ACAPS���b�N���Ȃ����m�F���Ă��������B';
	BALLOON_HINT_PASSWOED_LENGTH_LONG         = '�p�X���[�h���������܂��B';
	BALLOON_HINT_PASSWOED_LENGTH_SESCRIPTION  = '�p�X���[�h�Ɏg�p�ł��镶�����͔��p32�����i�S�p16�����j�ȓ��ł��B';
	BALLOON_HINT_PASSWORD_HASH_TITLE          = '�p�X���[�h�Ɉȉ��̃t�@�C���̃n�b�V���l�����͂���܂����B';



implementation

initialization

	//Delphi�R���p�C���ɂ��œK����h��

	DRAG_AND_DROP_HERE;
	INPUT_PASSWORD;
	CONFIRM_PASSWORD;
	INPUT_DECRYPT_PASSWORD;

	DIALOG_SELECT_DIRECTORY_TEXT;

	DIALOG_OPEN_FILES_FOR_ENCRYPTION_TITLE;
	DIALOG_OPEN_FILES_FOR_ENCRYPTION_FILTER;
	DIALOG_OPEN_FILES_FOR_DECRYPTION_TITLE;
	DIALOG_OPEN_FILES_FOR_DECRYPTION_FINTER;
	DIALOG_SAVE_FILES_FOR_ENCRYPTION_TITLE;
	DIALOG_SAVE_FILES_FOR_ENCRYPTION_FILTER;

	DIALOG_SAVE_AS_FOLDER_CAPTION;
	DIALOG_SAVE_AS_FILE_CAPTION;
	DIALOG_SAVE_AS_FILTER;
	DIALOG_BUTTON_NAME_OVERWITE_YES_TO_ALL;
	DIALOG_BUTTON_NAME_OVERWITE_YES;
	DIALOG_BUTTON_NAME_OVERWITE_NO;
	DIALOG_BUTTON_NAME_OVERWITE_CANCEL;

	CHECK_BOX_EXEFILE_OUT;

	MSG_CAPTION_ERROR;
	MSG_CAPTION_CONFIRMATION;

	MSG_BROKEN_ATC_FILE;
	MSG_FILE_OPEN_ERROR;
	MSG_CONFIRM_ENCRYPT_OR_DECRYPT;
	MSG_ERROR_SAVE_ENC_TO_FOLDER_NOT_EXISTS;
	MSG_ERROR_SAVE_DEC_TO_FOLDER_NOT_EXISTS;
	MSG_ERROR_NOT_FOUND_ENC_PASSWORD_FILE;
	MSG_ERROR_NOT_FOUND_DEC_PASSWORD_FILE;
	MSG_ERROR_OPEN_PASSWORD_FILE;
	MSG_ERROR_MISMATCH_PASSWORD_FILE;

	LABEL_STATUS_TITLE_ENCRYPTING;
	LABEL_STATUS_TITLE_DECRYPTING;
	LABEL_STATUS_TITLE_LISTING;
	LABEL_STATUS_TITLE_ERROR;
	LABEL_STATUS_TITLE_USER_CANCEL;
	LABEL_STATUS_TITLE_COMPLETE;

	LABEL_STATUS_DETAIL_PREPARING_ENCRYPT;
	LABEL_STATUS_DETAIL_FAILED_ENCRYPT;
	LABEL_STATUS_DETAIL_STOPPED_ENCRYPT;
	LABEL_STATUS_DETAIL_PREPARING_DECRYPT;
	LABEL_STATUS_DETAIL_FAILED_DECRYPT;
	LABEL_STATUS_DETAIL_STOPPED_DECRYPT;



	BUTTON_CAPTION_ENCRYPTION;
	BUTTON_CAPTION_DECRYPTION;
	BUTTON_CAPTION_CANCEL;

	BALLOON_HINT_PASSWOED_MISMATCH;
	BALLOON_HINT_PASSWOED_CONFIRMATION;
	BALLOON_HINT_PASSWOED_LENGTH_LONG;
	BALLOON_HINT_PASSWOED_LENGTH_SESCRIPTION;
	BALLOON_HINT_PASSWORD_HASH_TITLE;




end.

