#ifndef _TEXTURE_MANAGER_H_

#define _TEXTURE_MANAGER_H_

class CTextureManager
{
public:

private:
	CTextureManager(){}
	//static const char* LOAD_FILENAME[][];	// 読み込み画像名リスト-配列(シーン番号×シーンごとの必要な画像枚数)

	int m_sceneID;					// 現在のシーン
	int m_nextSceneID;				// 次のシーン
	std::vector<CTexture> m_texList;	// 読み込まれているテクスチャ情報
public:
	static CTextureManager& getInstance() {
		static CTextureManager instance;
		return instance;
	}

	void Load(int _sceneID,LPDIRECT3DDEVICE9 _pDevice);	// 画像読み込み
	void Release();			// 画像解放

	// アクセッサ
	CTexture Get(int _no);	// 画像取得
};

#define CTexMgr CTextureManager::getInstance()

#endif