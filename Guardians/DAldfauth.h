/**
 * @file DAldfauth.h
 * @author �h��
 */

/**
 * �A���h�t�@�E�g�̐���
 */
class CAldfauth : public CPlayer
{
public:
	enum BOX_TYPE{
		BOX_BODY,
		BOX_ATTACK,
		BOX_HAND_STRIKE,
	};
private:
	CAldEffect* m_efk;
public:
	// �R���X�g���N�^
	CAldfauth(LPDIRECT3DDEVICE9 _pDevice);
	// �f�X�g���N�^
	~CAldfauth();

	void DrawEffect();
	// �`��
	void Draw();

	// ���[�V�����ύX
	void SetMotion(int _motionID);

	// �Đ�����G�t�F�N�̐���
	void ChangeEffect(){};
	// �G�t�F�N�g�̍Đ�
	void PlayEffect();

private:
	// ��`���쐬
	void CreateBox();
	// ��`�̐���
	void ControlRect();

	// �A���h�t�@�E�g���[�V����
	void Rush();	// �ːi
};
