#include "stdafx.h"


/*--------------------------------------------------------------

	処理内容:セーブデータの表示
	作成者:岸
	作成日:10/16
	更新日:11/08
	更新内容
	コードの簡略化
	mapchipアイコンの追加
--------------------------------------------------------------*/

CGameSaveDataWindow::CGameSaveDataWindow(LPDIRECT3DDEVICE9 _pDevice,D3DXVECTOR2 _position,int m_state):
CGameWindow(_pDevice,_position,static_cast<float>(MAX_WIDTH), static_cast<float>(MAX_HEIGHT))
{
	for(int i=0;i<10;i++){   //データ１０個分ロード
		Load(i);
	}
	m_textureChip= CTexMgr.Get(TEX_MAP_CHIP );
	m_head=0;  //描画初期化
	m_tail=2;  //描画初期化
	m_drawID=0;  //描画初期化
}
CGameSaveDataWindow::~CGameSaveDataWindow()
{

}
/*--------------------------------------------------------------

	SAVEDATA.txtのロード
	@param int  ID    SAVEDATA.txtの番号
	@return なし

--------------------------------------------------------------*/

void CGameSaveDataWindow::Load(int _ID)
{							
	int itemcount=0;					//アイテム数
	int onlyitemcount[MAX_ITEM];		//各々のアイテム所持数
	int emblemcount=0;					//称号数
	int onlyemblemcount[MAX_EMBLEM];	//各々の称号獲得
	
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _ID;
	ss << ".txt"; 
	std::ifstream ifs(ss.str());

	if(ifs.fail()) {	//データ読み込み失敗
		m_Data[_ID].data=FALSE;	//データの有無
	}
	else{	//データ読み込み成功
		std::string str;	//文字列型
		int count=0;
		//ファイル内のデータの終わりまでループ
		while( std::getline(ifs,str) ){
			switch(count){
				case 0: // セーブ日付
					sscanf_s(str.c_str(),"セーブ日時:%d/%d/%d %d:%d", &m_Data[_ID].year,&m_Data[_ID].month,&m_Data[_ID].date,&m_Data[_ID].realhour,&m_Data[_ID].realminutes);
					break;
				case 1: // プレイタイム
					sscanf_s(str.c_str(),"プレイ時間:%d:%d:%d", &m_Data[_ID].hour, &m_Data[_ID].minute, &m_Data[_ID].second);
					break;
				case 2: // 所持金
					sscanf_s(str.c_str(),"所持金:%d", &m_Data[_ID].money);
					break;

				case 3: // 取得装備
					sscanf_s(str.c_str(),"取得装備:%d", &m_Data[_ID].equipper);
					break;
				case 4: //ステージクリア数
					sscanf_s(str.c_str(),"ステージクリア数:%d",&m_Data[_ID].stageclear);
					break;
				case 47:
					sscanf_s(str.c_str(),"取得アイテム:%d",&m_Data[_ID].itemper);
					break;
				case 48:
					sscanf_s(str.c_str(),"取得称号:%d",&m_Data[_ID].achieve);
					break;
			}
			count++;
		}
	


		m_Data[_ID].data = TRUE;
	}
}
void CGameSaveDataWindow::Control() //制御
{
	CGameWindow::Control();
}	

	


void CGameSaveDataWindow::Draw()    //描画
{
	CGameWindow::Draw();
	//カーソルの動きに合わせて描画
	if(m_cursolpoint>m_tail){
		if(m_cursolpoint-m_tail>6){
		m_head=7;
		m_tail=9;
		m_drawID=7;
		}
		else{
		m_head++;
		m_tail++;
		m_drawID++;
		}
	}
	if(m_cursolpoint<m_head){
		if(m_head-m_cursolpoint>6){
		m_head=0;
		m_tail=2;
		m_drawID=0;
		}
		else{
		m_head--;
		m_tail--;
		m_drawID--;
		}
	}
	if(m_drawID<0){m_drawID=0;}
	if(m_drawID>7){m_drawID=7;}
	//カーソルが移動したときにDATA表示が動く	
	/*セーブ,ロード,実績,コンフィグの表示(変わらないところの表示)*/
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-400, m_position.y-210,0,716,256,748);	//セーブ
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-250, m_position.y-210,0,748,256,780);	//ロード
    m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-90, m_position.y-210,0,780,256,812);	//実績
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+50, m_position.y-210,0,812,256,844);	//コンフィグ
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+250, m_position.y-210,0,844,256,876);	//ゲーム終了
	for(int i=0;i<4;i++){
		m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-525+20*i, m_position.y-150+130*i,0,272,400,274);		//仕切りの表示
		m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-125+20*i, m_position.y-150+130*i,400,272,800,274);	//仕切りの表示
	}
	for(int i=m_drawID;i<m_drawID+3;i++){
		CStringList::saveStrList[6+i]->Draw(m_position.x-525+20*(i-m_drawID), m_position.y-130+130*(i-m_drawID),  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[6]->getLength());	//DATAの表示
	}
	//セーブデータの表示
	int l_timeSeconds[3];		//プレイ時間(秒)
	int l_timeMinutes[3];       //プレイ時間(分)
	int l_timeHours[3];			//プレイ時間(時間)
	int l_money[3];				//所持金
	int l_timediv[3][6];		//TIMEを分割
	int l_moneydiv[3][6];		//MONEYを分割
	int l_equipnum[3];			//装備数
	int l_equipdiv[3][2];		//装備数を分割
	int l_itemnum[3];			//アイテム数
	int l_itemdiv[3][2];		//アイテム数を分割
	int l_achievenum[3];		//実績数
	int l_achievediv[3][2];		//実績数を分割
	int l_yearnum[3];			//年数
	int l_yeardiv[3][4];		//年数を分割
	int l_monthnum[3];			//月数
	int l_monthdiv[3][2];		//月を分割  
	int l_daynum[3];			//日数
	int l_daydiv[3][2];			//日を分割
	int l_realtimeMinutes[3];	//リアルタイム(分)
	int l_realtimeHours[3];		//リアルタイム(時間)
	int l_realtimediv[3][4];	//リアルタイムを分割
	for(int i=0;i<3;i++){
		if (m_Data[m_drawID+i].data==FALSE){	//データ無しの表示
			CStringList::saveStrList[5]->Draw(m_position.x-325+20*i, m_position.y-85+130*i,  D3DCOLOR_ARGB(255,255,255,255),CStringList::saveStrList[5]->getLength());
			continue;
		}
		// 斜線の描画
		for(int j = 0; j < 2; j++){
			CStringList::middleNumberStrList[13]->Draw(m_position.x-250+20*i + (50 * j),  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[13]->getLength());
		}
		//:の表示
		for(int j = 0; j < 3; j++){
			CStringList::middleNumberStrList[10]->Draw( m_position.x-267+20*i + (43 * j), m_position.y-125+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	
		}
		CStringList::middleNumberStrList[10]->Draw(m_position.x-23+20*i, m_position.y-125+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:の表示
		CStringList::middleNumberStrList[10]->Draw(m_position.x-10+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:の表示			
		CStringList::middleNumberStrList[10]->Draw(m_position.x-245+20*i , m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:の表示
		CStringList::middleNumberStrList[10]->Draw(m_position.x+173+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:の表示
		CStringList::middleNumberStrList[10]->Draw(m_position.x-151+20*i, m_position.y-85+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:の表示 

		CStringList::saveStrList[0]->Draw(m_position.x-400+20*i, m_position.y-130+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[0]->getLength());	//プレイ時間
		CStringList::saveStrList[1]->Draw(m_position.x-100+20*i,m_position.y-130+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[1]->getLength());	//所持金
		CStringList::saveStrList[2]->Draw(m_position.x-350+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[2]->getLength());	//取得装備
		CStringList::saveStrList[3]->Draw(m_position.x-170+20*i, m_position.y-40+130*i,    D3DCOLOR_ARGB(255,255,255,255),CStringList::saveStrList[3]->getLength());	//取得アイテム
		CStringList::saveStrList[4]->Draw(m_position.x+70+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255),  CStringList::saveStrList[4]->getLength());	//実績解除
		//ステージクリアのアイコン表示
		m_vertex.SetSizeY(0.6f);
		m_vertex.SetSizeX(0.6f);
		if(m_Data[m_drawID+i].stageclear>7)m_Data[m_drawID+i].stageclear=7;
		if(m_Data[m_drawID+i].stageclear<=4)m_vertex.DrawTextureLT(m_pDevice, m_textureChip, m_position.x-535+20*static_cast<float>(i), m_position.y-125+130*static_cast<float>(i),0+160*static_cast<float>(m_Data[m_drawID+i].stageclear-1),360,160+160*static_cast<float>(m_Data[m_drawID+i].stageclear-1),540);	
		else if(m_Data[m_drawID+i].stageclear>4)m_vertex.DrawTextureLT(m_pDevice, m_textureChip, m_position.x-535+20*i, m_position.y-123+130*i,0+160*static_cast<float>(m_Data[m_drawID+i].stageclear-5),540,160+160*static_cast<float>(m_Data[m_drawID+i].stageclear-5),720);
		m_vertex.SetSizeY(1.0f);
		m_vertex.SetSizeX(1.0f);
		//時間と所持金の表示処理
		l_timeSeconds[i]=m_Data[m_drawID+i].second;	//秒の分割				
		l_timeMinutes[i]=m_Data[m_drawID+i].minute;	//分の分割
		l_timeHours[i]=m_Data[m_drawID+i].hour;		//時間の分割
		l_money[i]=m_Data[m_drawID+i].money;			//MONEYの取得	
		for(int j=5;j>=4;j--){	
		l_timediv[i][j]=l_timeSeconds[i]%10;	//TIME(秒)のステータスを1桁ずつ格納	
		l_timeSeconds[i]/=10;
		l_timediv[i][j-2]=l_timeMinutes[i]%10;  //TIME(分)のステータスを1桁ずつ格納	
		l_timeMinutes[i]/=10;
		l_timediv[i][j-4]=l_timeHours[i]%10;	//TIME(時間)のステータスを1桁ずつ格納
		l_timeHours[i]/=10;
		}
		for(int j=5;j>=0;j--){	//MONEYのステータスを1桁ずつ格納
			l_moneydiv[i][j]=l_money[i]%10;
			l_money[i]/=10;
		}
		for( int j = 0; j < 2; j++ ) {  //TIMEの表示				   
			CStringList::middleNumberStrList[l_timediv[i][j]]->Draw(m_position.x-250+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255),    CStringList::middleNumberStrList[i]->getLength());
			CStringList::middleNumberStrList[l_timediv[i][j+2]]->Draw( m_position.x-208+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		    CStringList::middleNumberStrList[l_timediv[i][j+4]]->Draw( m_position.x-166+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		for( int j = 0; j < 6; j++ ) {	//MONEYの表示					
			CStringList::middleNumberStrList[l_moneydiv[i][j]]->Draw( m_position.x-10+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}	
		//取得装備の表示
		l_equipnum[i]=m_Data[m_drawID+i].equipper;	//装備の取得
		if(l_equipnum[i]==100){	//100％の時は100％を表示
			CStringList::middleNumberStrList[1]->Draw(m_position.x-236+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[1]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x-220+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x-204+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[ 14 ]->Draw(m_position.x-188+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());
		}
		else{
			for(int j=1;j>=0;j--){	//装備数を1桁ずつ格納
				l_equipdiv[i][j]=l_equipnum[i]%10;	
				l_equipnum[i]/=10;
			}
			for(int j = 0; j < 2; j++ ) {	//装備数の表示		
				CStringList::middleNumberStrList[l_equipdiv[i][j]]->Draw(m_position.x-235+16*j+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
			}
			CStringList::middleNumberStrList[14]->Draw(m_position.x-200+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());	//%の表示
		}
		//取得アイテムの表示
		l_itemnum[i]=m_Data[m_drawID+i].itemper;	//アイテム数の取得
		if(l_itemnum[i]==100){		//100％の時は100％を表示
			CStringList::middleNumberStrList[1]->Draw(m_position.x+1+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),   CStringList::middleNumberStrList[1]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+17+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+33+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[14]->Draw(m_position.x+49+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());
		 }
		 else{
			for(int j=1;j>=0;j--){	//アイテム数を1桁ずつ格納
				l_itemdiv[i][j]=l_itemnum[i]%10;	
				l_itemnum[i]/=10;
			}
			for(int j = 0; j < 2; j++ ) {	//アイテム数の表示		
				CStringList::middleNumberStrList[l_itemdiv[i][j]]->Draw(m_position.x+2+16*j+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
			}
			CStringList::middleNumberStrList[14]->Draw(m_position.x+38+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());	//%の表示
		 }
		//実績解除の表示
		l_achievenum[i]=m_Data[m_drawID+i].achieve;	//実績数の取得
		if(l_achievenum[i]==100){	 //100％の時は100％を表示
			CStringList::middleNumberStrList[1]->Draw(m_position.x+182+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[1]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+198+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+216+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[12]->Draw(m_position.x+232+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[12]->getLength());
		}
		else{
			for(int j=1;j>=0;j--){	//実績数を1桁ずつ格納
				l_achievediv[i][j]=l_achievenum[i]%10;	
				l_achievenum[i]/=10;
			}
			for(int j = 0; j < 2; j++ ) {	//実績数の表示		
				CStringList::middleNumberStrList[l_achievediv[i][j]]->Draw(m_position.x+183+16*j+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
			}
			CStringList::middleNumberStrList[14]->Draw(m_position.x+219+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());	//%の表示
		}
		//年月日の表示 
		l_yearnum[i]=m_Data[m_drawID+i].year;	//年数の取得
									//年数を分割
		for(int j=3;j>=0;j--){						//年数を1桁ずつ格納
			l_yeardiv[i][j]=l_yearnum[i]%10;	
			l_yearnum[i]/=10;
		}
		for(int j = 0; j < 4; j++ ) {	//年数の表示
			CStringList::middleNumberStrList[l_yeardiv[i][j]]->Draw(m_position.x-370+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		l_monthnum[i]=m_Data[m_drawID+i].month;  //月の取得
		for(int j=1;j>=0;j--){	//月数を1桁ずつ格納
		l_monthdiv[i][j]=l_monthnum[i]%10;	
		l_monthnum[i]/=10;
		}
		if(l_monthdiv[i][0]==0)l_monthdiv[i][0]=0;
		for(int j = 0; j < 2; j++ ) {	//月数の表示		
		CStringList::middleNumberStrList[l_monthdiv[i][j]]->Draw(m_position.x-285+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		l_daynum[i]=m_Data[m_drawID+i].date; //日の取得
		for(int j=1;j>=0;j--){	//日数を1桁ずつ格納
		l_daydiv[i][j]=l_daynum[i]%10;	
		l_daynum[i]/=10;
		}
		if(l_daydiv[i][0]==0)l_daydiv[i][0]=29;
		for(int j = 0; j < 2; j++ ) {	//日数の表示		
			CStringList::middleNumberStrList[l_daydiv[i][j]]->Draw(m_position.x-235+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		l_realtimeMinutes[i]=m_Data[m_drawID+i].realminutes;	//分のみの計算
		l_realtimeHours[i]=m_Data[m_drawID+i].realhour;		//時間のみの計算
		for(int j=3;j>=2;j--){	//分を1桁ずつ格納
			l_realtimediv[i][j]=l_realtimeMinutes[i]%10;	
			l_realtimeMinutes[i]/=10;
		}
		for(int j=1;j>=0;j--){	//時間を1桁ずつ格納
			l_realtimediv[i][j]=l_realtimeHours[i]%10;	
			l_realtimeHours[i]/=10;
		}
		for(int j = 0; j < 2; j++ ) {	//時間と分の表示				   
			CStringList::middleNumberStrList[l_realtimediv[i][j]]->Draw(m_position.x-180+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		    CStringList::middleNumberStrList[l_realtimediv[i][j+2]]->Draw( m_position.x-138+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}  
	}
	//スクロールバーの表示
	int l_schrolladjust=m_cursolpoint;		//スクロールバーの中の長さ調整のために取得
	int l_scrollHeight=270*7/10;			//スクロールバーの中の高さ
	float l_scrollmoving=27;				//スクロールバーの中の移動幅	
	int   l_marginHeight;					//スクロールバー中の高さの調整用
	int   l_firstBurring;					//スクロールバーの中を最初に埋める変数
	if(l_schrolladjust>5){l_schrolladjust=l_schrolladjust-5;}
	else{l_schrolladjust=0;}
	for(int i=0;i<l_scrollHeight/16;i++){	//スクロールバーの中のバー表示
		m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+516, m_position.y-150+16*i+(l_schrolladjust*l_scrollmoving),272,218,286,234);
		l_marginHeight=l_scrollHeight-16*i;
		l_firstBurring=16*i;
	}
	for(int i=0;i<l_marginHeight;i++){		 //残りのスクロールバーの中を1pxで埋める
		m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+516, m_position.y-150+l_firstBurring+(1*i)+l_scrollmoving*l_schrolladjust,272,218,286,219);
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+495, m_position.y-200,272,48,322,128);		//スクロールバーの表示(上)　　　
	for(int i=0;i<27;i++){	//スクロールバーの表示(中)
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+495, m_position.y-150+10*i,272,128,322,138);	
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+495, m_position.y+120,272,138,322,218);	//スクロールバーの表示(下)
}
void CGameSaveDataWindow::SetCursorID(int _cursorID)
{
	m_cursolpoint = _cursorID;
};
