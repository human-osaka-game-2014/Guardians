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