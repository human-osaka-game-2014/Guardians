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

	// ice��z�u����p�x
	float degree;

	if(!m_isPlay){
		memset(m_particle,0,sizeof(m_particle));

		m_angle = _angle + 90;
		m_magic->Play(m_angle,_position);
		float radius = (m_magic->GetSize() / 2) * cos(D3DXToRadian(m_angle));	// ice��z�u���锼�a(�����w�̃e�N�X�`���T�C�Y)

		for(int i = 0; i < PARTICLE_NUM; i++){
			m_particle[i].color = D3DCOLOR_ARGB(255,236,255,255);
			m_particle[i].scale = 0;
			// �p�x���v�Z
			degree = (180 / ((float)PARTICLE_NUM - 1)) * i;
			m_maxRotate[i] = degree;	// Ice�̍ő��]�p�x���擾
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

	// iceWall���Đ�
	if( !m_magic->GetExists() ){
		// 
		float addScale = 0;
		addScale += ADD_SCALE;

		for(int i = 0; i < PARTICLE_NUM; i++){
			// �p�����[�^���Z�b�g
			m_efk->SetParameter(&m_particle[i]);
			// ����
			m_efk->Control();
			// �`��
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
	// �����w���Đ�
	m_magic->Run();

	m_drawTime++;
}