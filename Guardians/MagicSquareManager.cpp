#include "stdafx.h"

// �~�̑����X�P�[��
const float CMagicSquare::CIRCLE_ADDSCALE[CIRCLE_NUM] = {
	0.2f,
	0.25f,
	0.3f,
};
// �����w�̏����X�P�[��
const float CMagicSquare::INIT_MAGIC_SCALE = 5.f;
// �~�̏����X�P�[��
const float CMagicSquare::INIT_CIRCLE_SCALE = CMagicSquare::INIT_MAGIC_SCALE * 2.5f;
// �����̍ő�X�P�[��
const float CMagicSquare::MAX_CIRCLE_SCALE = CMagicSquare::INIT_MAGIC_SCALE * 1.6;

CMagicSquare::CMagicSquare(LPDIRECT3DDEVICE9 _pDevice) : CEffectManager(_pDevice)
{
	m_tex[SHINY].Load(L"Effect\\texture\\shape_01.png",m_pDevice);
	m_tex[CIRCLE].Load(L"Effect\\texture\\magic_circle2.png",m_pDevice);
	m_tex[MAGIC].Load(L"Effect\\texture\\PC2_Magic_03.png",m_pDevice);
	m_efk = new CEffect(m_pDevice);
	
	m_endTime = 20;

}
CMagicSquare::~CMagicSquare()
{
	SAFE_DELETE(m_efk);
}
void CMagicSquare::Play(float _angle,D3DXVECTOR3 _position)
{
	if( !m_isPlay){
		// �g�p����p�[�e�B�N���̍\���̂�������
		memset(m_circle,0,sizeof(m_circle));
		memset(&m_magic,0,sizeof(m_magic));
		// �~�̃p�����[�^�̏�����
		for(int i = 0; i < CIRCLE_NUM; i++){
			m_circle[i].position = _position;
			m_circle[i].scale = INIT_CIRCLE_SCALE;
			m_circle[i].color = D3DCOLOR_ARGB(255,236,255,252);
		}
		// �����w�̃p�����[�^
		m_magic.position = _position;
		m_magic.scale = INIT_MAGIC_SCALE;
		m_magic.color = D3DCOLOR_ARGB(255,255,255,255);
	}
	m_isPlay = true;
}
void CMagicSquare::Run()
{
	if( !m_isPlay ) return;

	for(int i = 0; i < CIRCLE_NUM; i++){
		m_efk->SetParameter(&m_circle[i]);
		m_efk->Control();
		// �X�P�[���̐���
		m_circle[i].scale -= CIRCLE_ADDSCALE[i];
		// �����w�̃T�C�Y�Ɖ~�������T�C�Y�Ȃ�~�̃X�P�[�����Œ�
		if( m_circle[i].scale <= MAX_CIRCLE_SCALE )
			m_circle[i].scale = MAX_CIRCLE_SCALE;

		m_efk->Draw(m_tex[CIRCLE]);
	}

	m_efk->SetParameter(&m_magic);
	m_efk->Control();

	m_efk->Draw(m_tex[MAGIC]);

	m_drawTime++;
}
// �`�掞�̃e�N�X�`���T�C�Y��Ԃ�
float CMagicSquare::GetSize()
{
	return 2 * MAX_CIRCLE_SCALE;
}