

class CGameSelectWindow : public CGameWindow
{
private:

	static const float MAX_WIDTH;
	static const float MAX_HEIGHT;

	int					m_id;			// メニューID
public:
	CGameSelectWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int _id);	// コンストラクタ(デバイス 座標 id)
	~CGameSelectWindow();
	void Control();																	//制御
	void Draw();																	// 描画
};