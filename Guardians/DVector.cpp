/**
 * @file  DVector.cpp
 * @brief �ȒP�Ȑ���
 * @author danjo
 * @date ���t�i�J�n���H�j
 */

#include "stdafx.h"

/**
 * �x�N�g���̒�����Ԃ�
 * @param[in] _vector �x�N�g��
 * @return �x�N�g���̒���
 */
float CVector::GetVecLength(D3DXVECTOR3 _vector)
{
	
	float length;

	length = sqrt( _vector.x * _vector.x + _vector.y * _vector.y + _vector.z * _vector.z );

	return length;
}

/**
 * �P�ʃx�N�g����Ԃ�
 * @param[in] _vector �x�N�g��
 * @return �P�ʃx�N�g��
 */
D3DXVECTOR3 CVector::GetUnitVector(D3DXVECTOR3 _vector)
{

	// �x�N�g���̒������擾����
	float length = GetVecLength(_vector);

	// �e�����𒷂��Ŋ���
	return _vector / length;

}

/**
 * �����œn���ꂽ2�̃x�N�g���̊O�ς�Ԃ�
 * @param[in] v1 �x�N�g��1
 * @param[in] v2 �x�N�g��2
 * @return �O��
 */
float CVector::D3DXVecCross( D3DXVECTOR3* v1, D3DXVECTOR3* v2 ) 
{
   return v1->x * v2->y - v1->y * v2->x;
}
