#ifndef _GAME_EXPLAIN_TELOP_H_
#define _GAME_EXPLAIN_TELOP_H_

class CGameExplainTelop : public CGameTelop
{
private:
	static const D3DXVECTOR2 EXPLAIN_POSITION;	// �u�A�C�e�������v�`��ʒu
	static const float TELOP_HEIGHT;			// �e���b�v�̍���
	static const float TELOP_MAX_WIDTH;			// �e���b�v�ő啝
	//static const int TEX_TOOL_ID = ??
	//CTexture           m_toolID;

	int m_toolID;	// �A�C�e���ԍ�
		

	CGameData* m_pGameData;
public:
	CGameExplainTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CGameData* _pGameData);	// �R���X�g���N�^(�f�o�C�X�A���W�A�A�C�e��ID���Z�b�g)
	~CGameExplainTelop();
	void Control();																		// ����
	void Draw(int _no);																		// �`��
	int Search(int _No);
};

#endif