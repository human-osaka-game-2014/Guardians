/*--------------------------------------------------------------

	�������e:�e�N�X�`���̊Ǘ�
	�쐬��:�h��
	�쐬��:9/27
	�X�V��:11/08
	�X�V���e:
	�֐��@
		Load
		Release
		Get
	�ϐ�
	�@	
--------------------------------------------------------------*/
#include "stdafx.h"

#define DUMMY L"dummy"

const wchar_t* LOAD_LOGO[] = {
		L"image\\title\\TeamLogo.png",
		NULL,
};
const wchar_t* LOAD_OPENING[] = {
		NULL,
};
const wchar_t* LOAD_TITLE_FILENAME[] = {
/*0*/	L"image\\title\\Guardiands.png",
/*2*/	L"image\\title\\titleSelect.png",
		NULL,
};
const wchar_t*LOAD_PREPAREMISSION[] = {
/*0*/	L"image\\prepare\\boss.png",
/*1*/	L"image\\prepare\\button_icon.png",
/*2*/	L"image\\prepare\\chara_menu.png",
/*3*/	L"image\\prepare\\field_menu.png",
/*4*/	L"image\\prepare\\map.png",
/*5*/	L"image\\prepare\\map_chip.png",
/*6*/	L"image\\prepare\\monster_chip.png",
/*7*/	L"image\\prepare\\road_line.png",
/*8*/	L"image\\prepare\\telop.png",
/*9*/	L"image\\prepare\\window.png",
/*10*/	L"image\\prepare\\cursor.png",
/*11*/	L"image\\prepare\\chara_window.png",
/*12*/	L"image\\prepare\\equip_icon.png",	// 11/06�ǉ��@��
/*13*/  L"image\\prepare\\item_icon.png",		// 11/06�ǉ��@��


	NULL,
};

const wchar_t*LOAD_BATTLE[] = {
		DUMMY,
		L"image\\prepare\\button_icon.png",
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
		DUMMY,
/*14*/  L"image\\UI\\battle_UI.png",		// 11/18�ǉ��@��
/*15*/	L"image\\feed.png",
/*16*/  L"image\\UI\\battleblack.png",
/*17*/	L"image\\UI\\�GHP�o�[.png",
		NULL,
};
// ���U���g
const wchar_t* LOAD_RESULT[] = {
	L"image\\result\\result_checkpoint.png",
	L"image\\result\\result_stage_clear.png",
	L"image\\result\\result_lose.png",
	L"image\\result\\record_ui.png",
	L"image\\prepare\\item_icon.png",
	NULL,
};
const wchar_t** LOAD_FILENAME[] = {
	LOAD_LOGO,
	LOAD_OPENING,
	LOAD_TITLE_FILENAME,
	LOAD_PREPAREMISSION,
	LOAD_BATTLE,
	LOAD_RESULT,
};

//std::vector<CTexture> CTexMgr.m_texList;
/*--------------------------------------------------------------

	�e�N�X�`���̃��[�h
	@param int					�g�p����摜ID
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@return �Ȃ�

--------------------------------------------------------------*/
void CTextureManager::Load(int _sceneID,LPDIRECT3DDEVICE9 _pDevice)
{
	int texCount = 0;

	for(;*LOAD_FILENAME[_sceneID] != NULL;){
		CTexture tex;
		// dummy���ǂݍ��܂�Ă���Ȃ��΂�
		if( wcscmp(*LOAD_FILENAME[_sceneID], L"dummy") == 0 )  {
			m_texList.push_back(tex);
			LOAD_FILENAME[_sceneID]++;
			texCount++;
			continue;
		}

		if( !tex.Load(*LOAD_FILENAME[_sceneID],_pDevice) )
			throw TEXT("TextureLoad���s");
			m_texList.push_back(tex);
			LOAD_FILENAME[_sceneID]++;
			texCount++;
	}
	if( texCount != 0 ) {
		LOAD_FILENAME[_sceneID] -= texCount;
	}
}
/*--------------------------------------------------------------

	�e�N�X�`���̉��
	@return �Ȃ�

--------------------------------------------------------------*/
void CTextureManager::Release()
{
	for(int i = 0;i < static_cast<int>(m_texList.size());i++){
		m_texList[i].Release();
	}
	std::vector<CTexture>().swap(m_texList);
}
/*--------------------------------------------------------------

	�e�N�X�`���擾
	@param	int �e�N�X�`���ԍ�
	@return �e�N�X�`�����

--------------------------------------------------------------*/
CTexture CTextureManager::Get(int _no)
{
	return m_texList[_no];
}