unit MsgExeOut;

interface

resourcestring

	//�A�v���P�[�V������
	APP_NAME                                  = '�A�^�b�V�F�P�[�X�i�Í����\�t�g�E�F�A�j';

	//�t�H�[���{�^��
	BUTTON_CAPTION_DECRYOTION                 = '��������(&D)';
	BUTTON_CAPTION_CANCEL                     = '�L�����Z��(&C)';
	BUTTON_CAPTION_EXIT                       = '�I��(&X)';
	BUTTON_CAPTION_HELP                       = '�w���v(&H)';

	//�`�F�b�N�{�b�N�X
	CHECK_BOX_SAVE_TO_OTHER_DIRECTORY         = '���̃t�@�C��������t�H���_�[�Ƃ͕ʂ̏ꏊ�ɕۑ�����(&T)';
	//�t�H���_�[�I���_�C�A���O���b�Z�[�W
	DIALOG_MSG_SELECT_SAVE_TO_FOLDER          = '���������̃t�H���_�[���w�肵�Ă��������B';

	//�t�H�[�����x��
	LABEL_CAPTION_ABOUT                       = '���̃t�@�C���ɂ���';
	LABEL_CAPTION_SELECT_DECRYPTION_FOLDER    = '������t�H���_�̎w��F';
	LABEL_CAPTION_INPUT_PASSWORD              = '���̃t�@�C���͈Í�������Ă��܂��B�p�X���[�h����͂��Ă�������...';

	//�V�X�e�����j���[
	SYSTEM_CONTEXT_MENU_DECYPTION             = '�A�^�b�V�F�P�[�X�t�@�C���𕜍�����';

	//�G���[���b�Z�[�W
	MSG_ERROR_DO_NOT_READ_REGISTRY            = '���R�͂킩��܂��񂪁A���W�X�g������̓ǂݍ��݂Ɏ��s���܂����B';
	MSG_ERROR_THIS_APP_DOES_NOT_EXECUTE_ALONE = '���̃v���O�����͒P�̂ł͓��삵�܂���B'+#13+
                                              '�A�^�b�V�F�P�[�X����t�@�C���̊֘A�t���ݒ�ŌĂяo�����Ƃ��̂ݎg�p����܂��B';
	MSG_ERROR_OPEN_PASSWORD_FILE              = '�p�X���[�h�t�@�C�����J���܂���B���̃A�v���P�[�V�����Ŏg�p���̉\��������܂��B';
	MSG_ERROR_SAVE_DEC_TO_FOLDER_NOT_EXISTS   = '�ۑ������̃t�H���_�[��������܂���B�ۑ��ݒ���Ċm�F���Ă��������B'+#13+
                                              '�����������𒆎~���܂��B';
	//���b�Z�[�W�L���v�V����
	MSG_CAPTION_ERROR                         = '�G���[';
	MSG_CAPTION_CONFIRMATION                  = '�m�F';
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

	//���x��
	LABEL_STATUS_TITLE_DECRYPTING     = '�������Ă��܂�...';
	LABEL_STATUS_TITLE_LISTING        = '�t�@�C�����X�g�̐���';
	LABEL_STATUS_TITLE_ERROR          = '�G���[';
	LABEL_STATUS_TITLE_USER_CANCEL    = '�L�����Z��';
	LABEL_STATUS_TITLE_COMPLETE       = '����';

	LABEL_STATUS_DETAIL_PREPARING     = '�������邽�߂̏��������Ă��܂�...';
	LABEL_STATUS_DETAIL_FAILED        = '�����Ɏ��s���܂����B';
	LABEL_STATUS_DETAIL_STOPPED       = '���������~����܂����B';


	//�t�H�[���i�o�[�W�������j���x��
	FORM_ABOUT_CAPTION                        = '�o�[�W�������';
	FORM_ABOUT_LABEL_CAPTION_DESCRIPTION_01   = '���̃t�@�C���́A�t���[�ŁA���I�[�v���\�[�X�ŊJ������Ă���A';
	FORM_ABOUT_LABEL_CAPTION_DESCRIPTION_02   = '�\�t�g�E�F�A�ňÍ�������Ă��܂��B';
	FORM_ABOUT_LABEL_CAPTION_DESCRIPTION_03   = '�ڂ������͈ȉ��̃T�C�g���������������B';
	FORM_ABOUT_LABEL_WEB_SITE_URL             = 'http://hibara.org/';



implementation



initialization

	//Delphi�R���p�C���ɂ��œK����h��
	SYSTEM_CONTEXT_MENU_DECYPTION;
	MSG_ERROR_DO_NOT_READ_REGISTRY;
	MSG_ERROR_THIS_APP_DOES_NOT_EXECUTE_ALONE;




end.

