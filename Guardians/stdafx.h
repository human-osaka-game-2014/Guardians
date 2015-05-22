// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <tchar.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h>
// Directx ヘッダーファイル:
#include <d3dx9.h>
#include <d3d9.h>
#include <dshow.h>
// C ランタイム ヘッダー ファイル
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
// Effekseer ヘッダーファイル
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif // _DEBUG

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include "macro.h"
#include "define.h"

#include "DVector.h"
//ライブラリ
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
//以下2D
//--------------------------------------------------

#include "charaPicture.h"
#include "MgameData.h"
#include "DgameMenuBar.h"
#include "DgameIcon.h"
#include "stringList.h"
//テロップ
#include "MgameTelop.h"
#include "MgameBossTelop.h"
#include "MgameCharaTelop.h"
#include "MgameExplainTelop.h"
#include "MgameStageTelop.h"
//カーソル
#include "DgameCursor.h"
#include "DgameCharaCursor.h"
#include "DgameItemCursor.h"
#include "DgameMenuCursor.h"
#include "DgameSaveCursor.h"
#include "DgameSelectCursor.h"
//ウインドウ
#include "KgameWindow.h"
#include "KgameDataWindow.h"
#include "KgameEquipWindow.h"
#include "KgameShopListWindow.h"
#include "KgameShopMenuWindow.h"
#include "KgameStatusWindow.h"
#include "KgameThingsWindow.h"
#include "KgameSelectWindow.h"
#include "KgameSaveDataWindow.h"
//マップ
#include "chip.h"
#include "gameMapPointer.h"
#include "gameMap.h"
#include "chipMonster.h"

//スクリーン
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
//以下3D
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

// フィールド
#include "MLayer.h"
#include "Mlayer1.h"
#include "Mlayer2.h"
#include "Mlayer3.h"
#include "Mlayer4.h"
#include "Mlayer5.h"
#include "Mlayer6.h"
#include "Mlayer7.h"
#include "Mfield.h"

//シーン
#include "Dscene.h"
#include "DlogoScene.h"
#include "DtitleScene.h"
#include "DopeningScene.h"
#include "DprepareMissionScene.h"
#include "DbattleScene.h"
#include "resultScene.h"
#include "endingScene.h"
#include "DsceneManager.h"



