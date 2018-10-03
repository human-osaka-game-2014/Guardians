/**
 * @file  DVector.h
 * @brief �ȒP�Ȑ���
 * @author danjo
 * @date ���t�i�J�n���H�j
 */

#include "stdafx.h"

/**
 * @fn
 * �x�N�g���̒�����Ԃ�
 * @param (D3DXVECTOR3) �x�N�g��
 * @return �x�N�g���̒���
 */
float CVector::GetVecLength(D3DXVECTOR3 _vector)
{
	
	float length;

	length = sqrt( _vector.x * _vector.x + _vector.y * _vector.y + _vector.z * _vector.z );

	return length;
}
/**
 * @fn
 * �P�ʃx�N�g����Ԃ�
 * @param (D3DXVECTOR3) �x�N�g��
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
 * @fn
 * �x�N�g���̊O�ς�Ԃ�
 * @param (D3DXVECTOR3) �x�N�g��
 * @return �O��
 */
float CVector::D3DXVecCross( D3DXVECTOR3* v1, D3DXVECTOR3* v2 ) 
{
   return v1->x * v2->y - v1->y * v2->x;
}
