/**
 * @file  DVector.h
 * @brief 簡単な説明
 * @author danjo
 * @date 日付（開始日？）
 */

/**
 * この下のクラスについての簡単な説明
 */
class CVector
{
public:
	CVector(){}; // コンストラクタ
	~CVector(){}; // デストラクタ
	
	// ベクトルの長さを取得する
	float GetVecLength(D3DXVECTOR3 _vector);

	// 単位ベクトルを取得する
	D3DXVECTOR3 GetUnitVector(D3DXVECTOR3 _vector); 

	// 2Dベクトルの外積
	float D3DXVecCross( D3DXVECTOR3* vetor1,D3DXVECTOR3* vector2 );
private:

};
