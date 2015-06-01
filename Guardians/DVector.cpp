/**
 * @file  DVector.cpp
 * @brief 簡単な説明
 * @author danjo
 * @date 日付（開始日？）
 */

#include "stdafx.h"

/**
 * ベクトルの長さを返す
 * @param[in] _vector ベクトル
 * @return ベクトルの長さ
 */
float CVector::GetVecLength(D3DXVECTOR3 _vector)
{
	
	float length;

	length = sqrt( _vector.x * _vector.x + _vector.y * _vector.y + _vector.z * _vector.z );

	return length;
}

/**
 * 単位ベクトルを返す
 * @param[in] _vector ベクトル
 * @return 単位ベクトル
 */
D3DXVECTOR3 CVector::GetUnitVector(D3DXVECTOR3 _vector)
{

	// ベクトルの長さを取得する
	float length = GetVecLength(_vector);

	// 各成分を長さで割る
	return _vector / length;

}

/**
 * 引数で渡された2つのベクトルの外積を返す
 * @param[in] v1 ベクトル1
 * @param[in] v2 ベクトル2
 * @return 外積
 */
float CVector::D3DXVecCross( D3DXVECTOR3* v1, D3DXVECTOR3* v2 ) 
{
   return v1->x * v2->y - v1->y * v2->x;
}
