// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <tchar.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h>
// Directx �w�b�_�[�t�@�C��:
#include <d3dx9.h>
#include <d3d9.h>
#include <dshow.h>
// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <memory>
#include <crtdbg.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <comdef.h>   // _bstr_t
#include <algorithm>
// Effekseer �w�b�_�[�t�@�C��
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif // _DEBUG

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
#include "macro.h"
#include "define.h"

#include "DVector.h"
//���C�u����
#include "StringConvert.h"
#include "texture.h"
#include "vertex.h"
#include "3DVertex.h"

#include "Polygon.h"
#include "TexCharacter.h"
#include "fontPolygon.h"
#include "TexString.h"

#include "DtextureManager.h"
#include "graphicsDevice.h"
#include "input.h"
#include "animVertex.h"
#include "DdirectShow.h"



//--------------------------------------------------
//�ȉ�2D
//--------------------------------------------------

#include "charaPicture.h"
#include "MgameData.h"
#include "DgameMenuBar.h"
#include "DgameIcon.h"
#include "stringList.h"
//�e���b�v
#include "MgameTelop.h"
#include "MgameBossTelop.h"
#include "MgameCharaTelop.h"
#include "MgameExplainTelop.h"
#include "MgameStageTelop.h"
//�J�[�\��
#include "DgameCursor.h"
#include "DgameCharaCursor.h"
#include "DgameItemCursor.h"
#include "DgameMenuCursor.h"
#include "DgameSaveCursor.h"
#include "DgameSelectCursor.h"
//�E�C���h�E
#include "KgameWindow.h"
#include "KgameDataWindow.h"
#include "KgameEquipWindow.h"
#include "KgameShopListWindow.h"
#include "KgameShopMenuWindow.h"
#include "KgameStatusWindow.h"
#include "KgameThingsWindow.h"
#include "KgameSelectWindow.h"
#include "KgameSaveDataWindow.h"
//�}�b�v
#include "chip.h"
#include "gameMapPointer.h"
#include "gameMap.h"
#include "chipMonster.h"

//�X�N���[��
#include "menuScreen.h"
#include "DmenuSelectScreen.h"
#include "DmenuShopScreen.h"
#include "DmenuStatusScreen.h"
#include "MmenuDataScreen.h"

#include "Dtitle.h"
#include "DtitleMenu.h"
#include "DtitleSelect.h"

#include "Dlogo.h"
//--------------------------------------------------
//�ȉ�3D
//--------------------------------------------------

//3dmodel
#include "3DModel.h"
#include "anim3DModel.h"
//Effect
#include "Deffect.h"

// UI

#include "KbattleUI.h"


#include "DBillBoard.h"
#include "Effect.h"
#include "DEffectManager.h"
#include "DfireBallManager.h"
#include "MagicSquareManager.h"
#include "iceWallManager.h"


#include "Dcharacter.h"
#include "Dplayer.h"
#include "Denemy.h"
#include "DcharacterManager.h"

#include "DMaru.h"
#include "DNeru.h"
#include "Dminertza.h"
#include "DAldfauth.h"
#include "fenrir.h"
#include "Dmushroom.h"


//camera
#include "Mcamera.h"

// �t�B�[���h
#include "MLayer.h"
#include "Mlayer1.h"
#include "Mlayer2.h"
#include "Mlayer3.h"
#include "Mlayer4.h"
#include "Mlayer5.h"
#include "Mlayer6.h"
#include "Mlayer7.h"
#include "Mfield.h"

//�V�[��
#include "Dscene.h"
#include "DlogoScene.h"
#include "DtitleScene.h"
#include "DopeningScene.h"
#include "DprepareMissionScene.h"
#include "DbattleScene.h"
#include "resultScene.h"
#include "endingScene.h"
#include "DsceneManager.h"



