#include "stdafx.h"

// �ÓI�ȕϐ��̎��̂�錾
bool CScene::m_skipFlag = false;

float* CScene::keyPushTime;

int	CScene::m_keyStatePush;
// �������ςȂ�
int	CScene::m_keyStateOn;

CScene::SceneID CScene::Control()
{
	// �e�f�o�C�X�̏����擾
	CInputGamepad* gPad = m_Input->Gamepad();
	CInputKeyboard* keyboard = m_Input->Keyboard();
	
	keyPushTime = keyboard->ChkRelease();
	
	// ������
//	keyPushTime[DIK_RIGHT];
	if( keyboard->ChkKeyDown(DIK_RIGHT) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_RIGHT) == CInputGamepad::KEY_ON) {
		m_keyStateOn |= RIGHT;
	}
	if( keyboard->ChkKeyDown(DIK_LEFT) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_LEFT) == CInputGamepad::KEY_ON) {
		m_keyStateOn |= LEFT;
	}
	if( keyboard->ChkKeyDown(DIK_UP) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_UP) == CInputGamepad::KEY_ON) {		// ����L�[�������ꂽ��
		m_keyStateOn |= UP;
	}
	if( keyboard->ChkKeyDown(DIK_DOWN) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_DOWN) == CInputGamepad::KEY_ON) {		// �����L�[�������ꂽ��
		m_keyStateOn |= DOWN;
	}
	//// �ȉ�11/26 �ǉ�
	if( keyboard->ChkKeyDown(DIK_S) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_B) == CInputGamepad::KEY_PUSH) {		// �����L�[�������ꂽ��
		m_keyStateOn |= KEY_S;
	}
	if( keyboard->ChkKeyDown(DIK_D) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_A) == CInputGamepad::KEY_PUSH ){
		m_keyStateOn |= KEY_D;
	}
	if( keyboard->ChkKeyDown(DIK_W) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_Y) == CInputGamepad::KEY_PUSH ){
		m_keyStateOn |= KEY_W;
	}
	if( keyboard->ChkKeyDown(DIK_A) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_X) == CInputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_A;
	}
	if( keyboard->ChkKeyDown(DIK_E) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_RB) == CInputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_E;
	}
	if( keyboard->ChkKeyDown(DIK_Q) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_LB) == CInputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_Q;
	}
	if( keyboard->ChkKeyDown(DIK_Z) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_BACK) == CInputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_Z;
	}
	if( keyboard->ChkKeyAction(DIK_SPACE) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_START) == CInputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_SPACE;
	}


	if( keyboard->ChkKeyAction(DIK_RIGHT) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_RIGHT) == CInputGamepad::KEY_PUSH) {
		m_keyStatePush |= RIGHT;
	}
	if( keyboard->ChkKeyAction(DIK_LEFT) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_LEFT) == CInputGamepad::KEY_PUSH) {
		m_keyStatePush |= LEFT;
	}
	if( keyboard->ChkKeyAction(DIK_UP) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_UP) == CInputGamepad::KEY_PUSH) {		// ����L�[�������ꂽ��
		m_keyStatePush |= UP;
	}
	if( keyboard->ChkKeyAction(DIK_DOWN) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_DOWN) == CInputGamepad::KEY_PUSH) {		// �����L�[�������ꂽ��
		m_keyStatePush |= DOWN;
	}
	//// �ȉ�11/26 �ǉ�
	if( keyboard->ChkKeyAction(DIK_S) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_B) == CInputGamepad::KEY_PUSH) {		// �����L�[�������ꂽ��
		m_keyStatePush |= KEY_S;
	}
	if( keyboard->ChkKeyAction(DIK_D) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_A) == CInputGamepad::KEY_PUSH ){
		m_keyStatePush |= KEY_D;
	}
	if( keyboard->ChkKeyAction(DIK_W) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_Y) == CInputGamepad::KEY_PUSH ){
		m_keyStatePush |= KEY_W;
	}
	if( keyboard->ChkKeyAction(DIK_A) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_A) == CInputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_A;
	}
	if( keyboard->ChkKeyAction(DIK_E) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_RB) == CInputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_E;
	}
	if( keyboard->ChkKeyAction(DIK_Q) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_LB) == CInputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_Q;
	}
	if( keyboard->ChkKeyAction(DIK_Z) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_R3) == CInputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_Z;
	}
	if( keyboard->ChkKeyAction(DIK_SPACE) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_START) == CInputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_SPACE;
	}



	//if( keyboard->ChkKeyDown( DIK_R) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_RB) == CInputGamepad::KEY_PUSH){
	//	m_keyStatePush |= KEY_R;
	//}
	//if( keyboard->ChkKeyDown( DIK_B ) ||  gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_B) == CInputGamepad::KEY_PUSH){ 
	//	m_keyStatePush |= KEY_B;
	//}
	//if( keyboard->ChkKeyDown(DIK_Z) ){	// ����L�[�������ꂽ�瑕���E�B���h�E�Ƒ���/����I���J�[�\�����ړ������Ȃ��瑕���I���E�B���h�E/�����ύX�I���J�[�\�����o��������
	//	m_keyStatePush |= KEY_Z;
	//}

	//if( keyboard->ChkKeyDown(DIK_T)){
	//	CScene::m_keyStatePush |= KEY_T;
	//}


	//if( keyboard->ChkKeyDown('E') | gPad->ChkGamePadDownKEY_E
	//	CScene::m_keyStateOn |= KEY_E;
	//}


	return m_sceneID;
}