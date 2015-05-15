#ifndef _GAME_MENU_BAR_H_
#define _GAME_MENU_BAR_H_

class CMenuBar
{
public:
	enum TEX_NUM
	{
		TEX_BAR,
		TEX_ICON,

		TEX_MAX,
	};
	enum PIC_NO 
	{
		PIC_MENU,
		PIC_PREPARATION,
		PIC_CANCEL,
		PIC_STAGE_SELECT,
		PIC_TURN_NO,
		PIC_CHARA_SELECT,
		PIC_CHANGE_EQUIP,
		PIC_BUY,
		PIC_ENTER,
		PIC_ITEM_SELECT,
	};

	int							m_state;
protected:
	LPDIRECT3DDEVICE9			m_pDevice;
	CTexture					m_texture[2];
	CVertex						m_vertex;

	int							m_oldState;
public:
	CMenuBar(LPDIRECT3DDEVICE9 _pDevice);
	virtual ~CMenuBar();
	//void Control();
	virtual void Draw(int _state);
private:
};

#endif 