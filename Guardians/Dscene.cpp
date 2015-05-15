#include "stdafx.h"

// 静的な変数の実体を宣言
bool CScene::m_skipFlag = false;

float* CScene::keyPushTime;

int	CScene::m_keyStatePush;
// 押しっぱなし
int	CScene::m_keyStateOn;

CScene::SceneID CScene::Control()
{
	// 各デバイスの情報を取得
	CInputGamepad* gPad = m_Input->Gamepad();
	CInputKeyboard* keyboard = m_Input->Keyboard();
	
	keyPushTime = keyboard->ChkRelease();
	
	// 長押し
//	keyPushTime[DIK_RIGHT];
	if( keyboard->ChkKeyDown(DIK_RIGHT) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_RIGHT) == CInputGamepad::KEY_ON) {
		m_keyStateOn |= RIGHT;
	}
	if( keyboard->ChkKeyDown(DIK_LEFT) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_LEFT) == CInputGamepad::KEY_ON) {
		m_keyStateOn |= LEFT;
	}
	if( keyboard->ChkKeyDown(DIK_UP) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_UP) == CInputGamepad::KEY_ON) {		// 上矢印キーが押されたら
		m_keyStateOn |= UP;
	}
	if( keyboard->ChkKeyDown(DIK_DOWN) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_DOWN) == CInputGamepad::KEY_ON) {		// 下矢印キーが押されたら
		m_keyStateOn |= DOWN;
	}
	//// 以下11/26 追加
	if( keyboard->ChkKeyDown(DIK_S) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_B) == CInputGamepad::KEY_PUSH) {		// 下矢印キーが押されたら
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
	if( keyboard->ChkKeyAction(DIK_UP) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_UP) == CInputGamepad::KEY_PUSH) {		// 上矢印キーが押されたら
		m_keyStatePush |= UP;
	}
	if( keyboard->ChkKeyAction(DIK_DOWN) || gPad->ChkGamePadAction(CInputGamepad::GamePadLStick_DOWN) == CInputGamepad::KEY_PUSH) {		// 下矢印キーが押されたら
		m_keyStatePush |= DOWN;
	}
	//// 以下11/26 追加
	if( keyboard->ChkKeyAction(DIK_S) || gPad->ChkGamePadAction(CInputGamepad::GamePadBtn_B) == CInputGamepad::KEY_PUSH) {		// 下矢印キーが押されたら
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
	//if( keyboard->ChkKeyDown(DIK_Z) ){	// 決定キーが押されたら装備ウィンドウと装備/道具選択カーソルを移動させながら装備選択ウィンドウ/装備変更選択カーソルを出現させる
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