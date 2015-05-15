#include "stdafx.h"
/*--------------------------------------------------------------

	処理内容:キャラ,最大HP,MP,攻撃,防御,速度,瞬発の表示
	作成者:岸
	作成日:10/07
	更新日:11/08
	更新内容
	  アイコンの追加
	  フォント文字の修正
	  効果追加表示
	関数　
		drawの作成
	変数　
	int	m_hp	HPの追加
	int	m_mp	MPの追加
	int	m_atk	攻撃力の追加
	int	m_def	守備力の追加
	int	m_spd	速度力の追加
	int	m_ins	瞬発力の追加
--------------------------------------------------------------*/


CGameStatusWindow::CGameStatusWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData) :
	CGameWindow( _pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT)),m_pGameData( _pGameData ),m_charaID(0)
{

	m_texChara = CTexMgr.Get(TEX_CHARA_ICON );

}
CGameStatusWindow::~CGameStatusWindow()
{

}

void CGameStatusWindow::Control() //制御
{
	CGameWindow::Control();
}	
void CGameStatusWindow::Draw()    //描画
{
	CGameWindow::Draw();

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-280, m_position.y-170,0,272,280,274);			//仕切りの表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-170,520,272,800,274);			//仕切りの表示


	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y-140,-2,492,126,524);		//最大HP表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-120, m_position.y-140,128,588,162,620);		//:の表示

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y-80,126,492,254,524);		//最大MP表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-120, m_position.y-80,128,588,162,620);		//:の表示

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-280, m_position.y-10,0,272,280,274);			//仕切りの表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-10,520,272,800,274);			//仕切りの表示

	switch(m_charaID){			  //キャラのID選択
		
		case 0:
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-205, m_position.y-220,0,300,255,332);		//アルドファウトの表示
			m_vertex.DrawTextureLT(m_pDevice, m_texChara, m_position.x-30, m_position.y-250,0,0,320,520);		//アルドファウト
			break;
		case 1:
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-205, m_position.y+-220,0,332,255,364);	//ネルの表示
			m_vertex.DrawTextureLT(m_pDevice, m_texChara, m_position.x-30, m_position.y-250,320,0,640,520);		//ネル＆マル
			break;
		case 2:
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-205, m_position.y+-220,0,364,256,396);	//ミネルツァの表示
			m_vertex.DrawTextureLT(m_pDevice, m_texChara, m_position.x-30, m_position.y-250,640,0,960,520);		//ミネルツァ
			break;
		default:
			break;
	}


	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+15,0,524,128,556);			//攻撃の表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+65,126,524,254,556);		//防御の表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+115,0,556,128,588);			//速度の表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+165,128,556,256,588);		//瞬発の表示

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+15,128,588,162,620);		//:の表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+65,128,588,162,620);		//:の表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+115,128,588,162,620);		//:の表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+165,128,588,162,620);		//:の表示

	m_hp=m_pGameData->m_chara[m_charaID].hp;				//キャラのHP	
	m_mp=m_pGameData->m_chara[m_charaID].mp;				//キャラのMP	
	m_atk=m_pGameData->m_chara[m_charaID].atk;				//キャラの攻撃　
	m_def=m_pGameData->m_chara[m_charaID].def;				//キャラの防御  
	m_spd=m_pGameData->m_chara[m_charaID].spd;				//キャラの速度	
	m_ins=m_pGameData->m_chara[m_charaID].ins;				//キャラの瞬発  
	//キャラのステータスの表示
	for(int i = 0;i < 2; i++){
		switch( m_pGameData->m_chara[m_charaID].equip[i].stType ){
		case 0:
			m_hp -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 1:
			m_mp -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 2:
			m_atk -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 3:
			m_def -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 4:
			m_spd -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 5:
			m_ins -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		};
	};

	/*ローカル変数宣言*/
	int l_hpdiv[3];												//HPを分割
	int l_mpdiv[3];												//MPを分割
	int l_atkdiv[2];											//攻撃を分割
	int l_defdiv[2];											//防御を分割
	int l_spddiv[2];											//速度を分割
	int l_insdiv[2];											//瞬発を分割
	
	for(int i=2;i>=0;i--){										//HP,MPのステータスを1桁ずつ格納
		l_hpdiv[i]=m_hp%10;
		l_mpdiv[i]=m_mp%10;
		m_hp/=10;
		m_mp/=10;
	}
	for(int i=1;i>=0;i--){										//攻撃,防御,速度,瞬発のステータスを1桁ずつ格納
		l_atkdiv[i]=m_atk%10;
		l_defdiv[i]=m_def%10;
		l_spddiv[i]=m_spd%10;
		l_insdiv[i]=m_ins%10;
		m_atk /= 10;
		m_def /= 10;
		m_spd /= 10;
		m_ins /= 10;
	}
	
	for( int i = 0; i < 3; i++ ) {                      //HP,MP数字の表示を処理
		int alpha = CStringList::numberStrList[i] ? 255 : 128;
		CStringList::numberStrList[l_hpdiv[i]]->Draw(m_position.x - 80 + 20 * i, m_position.y - 126, D3DCOLOR_ARGB(alpha,255,255,255), CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_mpdiv[i]]->Draw(m_position.x-80+20 * i, m_position.y-67,		D3DCOLOR_ARGB(alpha,255,255,255),  CStringList::numberStrList[i]->getLength());
	}
	for( int i = 0; i < 2; i++ ) {                      //攻撃,防御,速度,瞬発数字の表示を処理
		int alpha = CStringList::numberStrList[i] ? 255 : 128;
		CStringList::numberStrList[l_atkdiv[i]]->Draw(m_position.x-150+20*i, m_position.y+30, D3DCOLOR_ARGB(alpha,255,255,255),  CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_defdiv[i]]->Draw(m_position.x-150+20*i, m_position.y+80, D3DCOLOR_ARGB(alpha,255,255,255),  CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_spddiv[i]]->Draw(m_position.x-150+20*i, m_position.y+130, D3DCOLOR_ARGB(alpha,255,255,255), CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_insdiv[i]]->Draw(m_position.x-150+20*i, m_position.y+180, D3DCOLOR_ARGB(alpha,255,255,255), CStringList::numberStrList[i]->getLength());
	}
	// 変化能力値格納用変数
	std::vector<int> variation;
	std::vector<int>::iterator it;
	int type;
	int power;
	// 変化するパラメーターによってfor文を回す回数を変える
	if(m_pGameData->m_chara[m_charaID].equip[0].stType ==  m_pGameData->m_chara[m_charaID].equip[1].stType) type = 1;
	else type = 2;

	for(int i = 0; i < type;i++){
		// typeが1の場合装備の2つの変化値を足しておく
		type == 1 ? power = m_pGameData->m_chara[m_charaID].equip[0].power + m_pGameData->m_chara[m_charaID].equip[1].power : power = m_pGameData->m_chara[m_charaID].equip[i].power;
		// 能力変化の値を分解
		for(int j = 2; j >= 0;j--){
			if( power == 0 ) break;
			it = variation.begin();
			variation.insert(it,power % 10);
			power = power / 10;
		}
		// 描画する位置
		int drawPos = m_pGameData->m_chara[m_charaID].equip[i].stType;
		// 描画位置(HP・MPの場合)
		if(drawPos < 2){
			for(unsigned i = 0; i < variation.size() ;i++){
				CStringList::numberStrList[ variation[i] ]->Draw( m_position.x -10+(20 * i)  , m_position.y - 126 + ( drawPos * 59 ), D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ variation[i] ]->getLength());
			}
			// +の描画
			CStringList::numberStrList[ 12 ]->Draw( m_position.x - 40  , m_position.y - 126 + ( drawPos * 59 ), D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ 12 ]->getLength());
			// vector配列をクリア
			variation.clear();
		}else{
			for(unsigned i = 0; i < variation.size() ;i++){
				CStringList::numberStrList[ variation[i] ]->Draw( m_position.x-60 + 20 * i  , m_position.y - 70 + ( drawPos * 50 ), D3DCOLOR_ARGB(255,255,255,255),CStringList::numberStrList[ variation[i] ]->getLength());
			}
			// +の描画
			CStringList::numberStrList[ 12 ]->Draw( m_position.x-90  , m_position.y - 70 + ( drawPos * 50 ), D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ 12 ]->getLength());
			// vector配列をクリア
			variation.clear();

		}
	}
		//if( i < 2 ) m_strLst[ 10 ]->Draw( m_position.x-10  , m_position.y - 126 + ( i * 59 ), D3DCOLOR_ARGB(alpha,255,255,255), m_strLst[ 10 ]->getLength());
}		
void CGameStatusWindow::SetSelectEquipID(int _selectEquipID)// 選択されている装備のIDをセット
{
	m_selectEquipID =_selectEquipID;
};											
void CGameStatusWindow::SetCharaID(int _charaID)
{
	m_charaID = _charaID;								// 選択されているキャラのIDをセット
};