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

private:
	CBillBoard vertex;
	CTexture tex;
public:
	// �R���X�g���N�^
	CAldfauth(LPDIRECT3DDEVICE9 _pDevice);
	// �f�X�g���N�^
	~CAldfauth();

	// �`��
	void Draw();
	// ���[�V�����ύX
	void SetMotion(int _motionID);

	// �Đ�����G�t�F�N�̐���
	void ChangeEffect(){};
	// �G�t�F�N�g�̍Đ�
	void PlayEffect(int){};

private:
	// ��`���쐬
	void CreateBox();
	// ��`�̐���
	void ControlRect();
	// �G�t�F�N�g�̐���
	void ControlEffect();

	// �A���h�t�@�E�g���[�V����
	void Rush();	// �ːi
	void Upper();	// �A�b�p�[
};
