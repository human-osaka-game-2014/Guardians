class CStringList
{
public:
	// 10/30�ǋL�@�����摜�T�C�Y
	static const int FONT_SIZE_H = 60;
	static const int FONT_SIZE_W = 32;

	static  std::vector<CTexString*> MenuStrList;
	static  std::vector<CTexString*> numberStrList;		//�����摜�\��
	static  std::vector<CTexString*> smallNumberStrList;	// �����̃��X�g(�Q�[���f�[�^�E�C���h�E�p)
	static  std::vector<CTexString*> middleNumberStrList;	// �����̃��X�g(�Z�[�u�f�[�^�X�N���[���p)
	static  std::vector<CTexString*> saveStrList;		//�����摜�\��
	static  std::vector<CTexString*> itemStrList;		//�����摜�\��
	static  std::vector<CTexString*> equipStrList;		//�����摜�\��
	static  std::vector<CTexString*> MessageStrList;
	static  std::vector<CTexString*> equipPrice;		// �����̒l�i
	static  std::vector<CTexString*> itemPrice;			// �A�C�e���̒l�i
	// ���������p
	struct List{
		CTexString* m_strLst;				//�����摜�\��
		int No;
	};

	static  std::vector<List> explainStrList;		// �A�C�e�������p

	static 	CTexString*				 m_none;					// �u�Ȃ��v�Ƃ��������摜		10/30�ǋL

private:

	static std::vector<bool> m_isSelLst;			//�����摜�\��
public:
	static void Create(LPDIRECT3DDEVICE9 _pDevice , CGameData* _pGameData);
	static void Release();

private:
};