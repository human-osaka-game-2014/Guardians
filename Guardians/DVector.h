class CVector
{
public:
	CVector(){}; // �R���X�g���N�^
	~CVector(){}; // �f�X�g���N�^
	
	// �x�N�g���̒������擾����
	float GetVecLength(D3DXVECTOR3 _vector);

	// �P�ʃx�N�g�����擾����
	D3DXVECTOR3 GetUnitVector(D3DXVECTOR3 _vector); 

	// 2D�x�N�g���̊O��
	float D3DXVecCross( D3DXVECTOR3* vetor1,D3DXVECTOR3* vector2 );
private:

};