#ifndef _NERU_H_
#define _NERU_H_

class CNeru : public CPlayer
{
public:
	XFileAnimationMesh*			m_model;
private:
	LPDIRECT3DDEVICE9			m_pDevice;		// �`��f�o�C�X
	D3DXVECTOR3					m_position;		// �L�����N�^�[�̈ʒu

	float						m_speed;
public:
	CNeru(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~CNeru();									// �f�X�g���N�^
	
	void Draw();								// �`��
	//void SetPosition(D3DXVECTOR3 _position);	// �ړ�
	void SetMotion(int _motionID);				// ���[�V����ID

	// �Q�b�^
	float GetCharaSpeed();						// �L�����̃X�s�[�h��Ԃ�

private:
};

#endif