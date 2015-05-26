#include "stdafx.h"


/*

////static D3DXVECTOR2 position[CFireBall::PARTICLE_MAX_NUM];
//// α増加量
//static float addAlpha[CEffectManager::PARTICLE_MAX_NUM];
//
//static D3DXEVCTOR2 move[CEffectManager::PARTICLE_MAX_NUM];


//static int ALPHA_MAX = 255;
//static int PARTICLE_MAX_NUM = 10;			// 描画する画像の最大数

static int END_TIME = 100;				// 描画終了フレーム
static int ERASE_TIME = 30;
*/
static D3DXVECTOR3 Position[CFireBallManager::PARTICLE_MAX_NUM];
// 初期スケール
const float CFireBallManager::INIT_SCALE = 1.8f;
// 初期移動量
static const D3DXVECTOR3 INIT_MOVE = D3DXVECTOR3(0.4f,0.0f,0.0f);

const float CFireBallManager::FIRE_MOVE = 0.1f;


CFireBallManager::CFireBallManager(LPDIRECT3DDEVICE9 _pDevice) : CEffectManager(_pDevice)
{
	m_texture.Load(L"Effect\\texture\\fire_1.png",m_pDevice);
	// 描画フレーム
	m_endTime = 200;
}
CFireBallManager::~CFireBallManager()	
{

}
void CFireBallManager::Play( float _angle,D3DXVECTOR3 _position )
{

	if( !m_isPlay ){
		// 配列の初期化
		memset(m_particle,0,sizeof(m_particle));

		m_angle = _angle + 90;
		float radian = D3DXToRadian(m_angle);
		m_fireMove = FIRE_MOVE * cos(radian);

		m_position.x = _position.x;
		m_position.y = _position.y;
		m_position.z = _position.z -1;
		// 円形に粒子を配置する
		float radius = 2;	
		float degree =  360 / PARTICLE_MAX_NUM;

		for(int i = 0; i < PARTICLE_MAX_NUM; i++){
			Position[i].x = radius * cos(degree * i);
			Position[i].y = radius * sin(degree * i);
			Position[i].z = 0;

			m_particle[i].move = D3DXVECTOR3(-INIT_MOVE.x * cos(D3DXToRadian(m_angle)),INIT_MOVE.y,0.f);
			m_particle[i].position = m_position;
			m_particle[i].scale = INIT_SCALE;
			m_particle[i].color = D3DCOLOR_ARGB(0,255,255,255);				// α値を初期化
			m_particle[i].addAlpha = (float)(rand() % 20 + 10);
			
			m_particle[i].scale = INIT_SCALE;
		}
	}

	m_isPlay = true;

}
void CFireBallManager::Run()
{

	if( !m_isPlay ) return;

	static float Flick = 0.01f;

	for(int i = 0; i < PARTICLE_MAX_NUM; i++){

		//if( m_drawTime < m_particle[i].drawFrame ) continue;

		// パラメーターをセットする
		m_efk->SetParameter(&m_particle[i]);
		// 制御
		m_efk->Control();
		// 描画
		m_efk->Draw(m_texture);

		m_particle[i].move.y = rand() % 100 < 50 ? -Flick : rand() % 100 < 50 ? Flick : 0;
		if( m_position.y < m_particle[i].position.y ) m_particle[i].move.y = -Flick * 3;
		else m_particle[i].move.y = Flick * 3;
		// 徐々に小さくする
		//m_particle[i].scale -= INIT_SCALE * 0.0f;
		m_particle[i].scale -= rand() % 100 < 50 ? INIT_SCALE * 0.06f : rand() % 100 < 50 ? INIT_SCALE * 0.07f : INIT_SCALE * 0.08f;
		//if( m_particle[i].scale <= 0  ) m_particle[i].scale = 0.f;
		// スケールが０になったらパラメーターをリセット
		if( m_particle[i].scale <= 0 ){
			m_particle[i].color.a = 0;
			m_particle[i].position = m_position + Position[i];
			m_particle[i].scale = INIT_SCALE;
		}
	}
	m_position.x += m_fireMove;
	m_drawTime++;
	// 描画終了 
	if( m_drawTime >= m_endTime ){
		m_isPlay = false;
		m_drawTime = 0;
		SAFE_DELETE(m_efk);
	}
}