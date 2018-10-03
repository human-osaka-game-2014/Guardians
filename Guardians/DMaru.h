/**
 * @file DMaru.h
 */

class CMaru : public CPlayer
{
public:

private:
	int		m_teleportState;		///< �e���|�[�g�̏��
	float	m_alpha;			///< ���f���̃��l
	D3DXVECTOR3 m_neruPos;
public:
	void DrawEffect(){};
	CMaru(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~CMaru();									// �f�X�g���N�^

	void ChangeEffect(){};						// �G�t�F�N�g�̐���
	void Draw();								// �`��
	void Move( D3DXVECTOR3 _position , int _motionID , int _angle);
	//void SetPosition(D3DXVECTOR3 _position);	// �ړ�
	void SetMotion(int _motionID);				// ���[�V����ID
	void SetPosition( D3DXVECTOR3 _position);
	void SetStopMotion(bool _flag);
private:
	void CreateBox();	// �{�b�N�X�𐶐�
	void SetEffectList(){};	// ���X�g����
	void PlayEffect(int){};

};
