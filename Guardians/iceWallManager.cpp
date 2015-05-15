#include "stdafx.h"

float CIceWallManager::ADD_ROTATE = 10;

CIceWallManager::CIceWallManager(LPDIRECT3DDEVICE9 _pDevice) : CEffectManager(_pDevice)
{
	m_tex.Load(L"Effect\\texture\\Ice_1.png",m_pDevice);
	m_magic = new CMagicSquare(_pDevice);
	m_endTime = 90;
}
CIceWallManager::~CIceWallManager()
{
	SAFE_DELETE(m_magic);
}
static float MAX_SCALE = 2.5f;
static int ICE_DRAW_TIME = 10;
static float ADD_SCALE = MAX_SCALE / ICE_DRAW_TIME;
static int ERASE_TIME = 60;

void CIceWallManager::Play(float _angle,D3DXVECTOR3 _position)
{

	// iceを配置する角度
	float degree;

	if(!m_isPlay){
		memset(m_particle,0,sizeof(m_particle));

		m_angle = _angle + 90;
		m_magic->Play(m_angle,_position);
		float radius = (m_magic->GetSize() / 2) * cos(D3DXToRadian(m_angle));	// iceを配置する半径(魔方陣のテクスチャサイズ)

		for(int i = 0; i < PARTICLE_NUM; i++){
			m_particle[i].color = D3DCOLOR_ARGB(255,236,255,255);
			m_particle[i].scale = 0;
			// 角度を計算
			degree = (180 / ((float)PARTICLE_NUM - 1)) * i;
			m_maxRotate[i] = degree;	// Iceの最大回転角度を取得
			if( m_angle == 180.f ) m_maxRotate[i] += 180.f;
			degree = DegreesToRadian( degree + -90.f);
			m_particle[i].position = D3DXVECTOR3(_position.x + radius * cos(degree),_position.y + radius * sin(degree),_position.z + 0.5f);
			m_particle[i].rotate = m_maxRotate[i];
		}
	}
	m_isPlay = true;
}
void CIceWallManager::Run()
{
	if( !m_isPlay ) return;

	// iceWallを再生
	if( !m_magic->GetExists() ){
		// 
		float addScale = 0;
		addScale += ADD_SCALE;

		for(int i = 0; i < PARTICLE_NUM; i++){
			// パラメータをセット
			m_efk->SetParameter(&m_particle[i]);
			// 制御
			m_efk->Control();
			// 描画
			m_efk->Draw(m_tex);

			m_particle[i].scale += addScale;
			if( m_particle[i].scale >= MAX_SCALE)
				m_particle[i].scale = MAX_SCALE;

			if( m_drawTime >= ERASE_TIME){
				m_particle[i].color -= D3DCOLOR_ARGB(255 / (ERASE_TIME),0,0,0);
				if( m_particle[i].color.a <= 0 ) m_particle[i].color.a = 0;
			}
		}
	}
	// 魔方陣を再生
	m_magic->Run();

	m_drawTime++;
}