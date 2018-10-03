#ifndef _LAYER_H_
#define _LAYER_H_

class CLayer
{
protected:
	D3DXVECTOR2			m_speed;        // ���C���[�̈ړ����x
	D3DXVECTOR3			m_angle;	// �t�B�[���h�̊p�x
	LPDIRECT3DDEVICE9	m_pDevice;
	D3DXVECTOR3			m_position;		// ���C���[���W
	D3DXVECTOR3			m_initPosition;	// �������W
	CTexture			m_tex;
	CTexture			m_tex2;
	C3DModel*			m_plane;  

public:
	enum TEX_ID {	// �e�N�X�`���ԍ�
	TEX_SKY, 
	TEX_MOUNTAIN,
	TEX_HILL_TREE,
	TEX_HILL,
	TEX_TREE,
	TEX_ROAD,
	TEX_STONE,
	TEX_NERU,
	TEX_NERU2,
	};



	CLayer( LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR3 _position, int _stageID ); // �R���X�g���N�^(�f�o�C�X�A�X�e�[�WID���Z�b�g)
	~CLayer();
	void Control();
	void Draw();
	virtual void SetCharaSpeed(D3DXVECTOR2 _speed) = 0;
	void SetPosition(D3DXVECTOR2 _position);
	D3DXVECTOR3 GetPosition();
	void SetInitPosition();
};

#endif