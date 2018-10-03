#ifndef _TEXTURE_MANAGER_H_

#define _TEXTURE_MANAGER_H_

class CTextureManager
{
public:

private:
	CTextureManager(){}
	//static const char* LOAD_FILENAME[][];	// �ǂݍ��݉摜�����X�g-�z��(�V�[���ԍ��~�V�[�����Ƃ̕K�v�ȉ摜����)

	int m_sceneID;					// ���݂̃V�[��
	int m_nextSceneID;				// ���̃V�[��
	std::vector<CTexture> m_texList;	// �ǂݍ��܂�Ă���e�N�X�`�����
public:
	static CTextureManager& getInstance() {
		static CTextureManager instance;
		return instance;
	}

	void Load(int _sceneID,LPDIRECT3DDEVICE9 _pDevice);	// �摜�ǂݍ���
	void Release();			// �摜���

	// �A�N�Z�b�T
	CTexture Get(int _no);	// �摜�擾
};

#define CTexMgr CTextureManager::getInstance()

#endif