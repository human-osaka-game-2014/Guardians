

class CGameSelectWindow : public CGameWindow
{
private:

	static const float MAX_WIDTH;
	static const float MAX_HEIGHT;

	int					m_id;			// ���j���[ID
public:
	CGameSelectWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int _id);	// �R���X�g���N�^(�f�o�C�X ���W id)
	~CGameSelectWindow();
	void Control();																	//����
	void Draw();																	// �`��
};