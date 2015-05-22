#include "stdafx.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

/*------------------------------------------
   
    �R���X�g���N�^
	@param LPCTSTR            �t�@�C����        
	@param LPDIRECT3DDEVICE9  �`��f�o�C�X

------------------------------------------*/
C3DModel::C3DModel(LPCTSTR _fileName, LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_angle(D3DXVECTOR3(0,0,0))
{
	// �}�e���A�������i�[����̈��錾
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	
	// �t�@�C���ǂݍ���
	if ( FAILED( D3DXLoadMeshFromX(_fileName, D3DXMESH_SYSTEMMEM, m_pDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_NumMaterials, &m_pMesh) ) ) // &�����Ă���̂��K�v���
		throw TEXT("�t�@�C���ǂݍ��ݎ��s");

	// �K�v�ȃ}�e���A�������擾
	D3DXMATERIAL * d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	
	// �}�e���A���ƃe�N�X�`�������i�[����̈�𐔕�����
	m_pMeshMaterials = new D3DMATERIAL9[m_NumMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	// ���ꂼ��̏����i�[
	for( DWORD i = 0; i < m_NumMaterials; i++ ){
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMeshMaterials[i].Diffuse.a = 1.0f;
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;

		m_pTextures[i] = NULL;

		// �e�N�X�`���t�@�C������UNICODE�ɑΉ�
		char str[256] = {0};
		// �t�@�C���������݂��Ă������U�L�����^�ɃR�s�[
		if( d3dxMaterials[i].pTextureFilename ) strcpy_s( str, d3dxMaterials[i].pTextureFilename);
		TCHAR textureFileName[256] = {0};
		#ifdef UNICODE 
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, str, strlen(str), textureFileName, (sizeof(textureFileName)/2 ) );
		#else
		strcpy_s(textureFileName, str);
		#endif

		//// �e�N�X�`�������蓖�Ă��Ă��邩�`�F�b�N
		if( textureFileName && lstrlen(textureFileName) > 0 ){
			// �e�N�X�`���ǂݍ���
			if( FAILED( D3DXCreateTextureFromFileEx( m_pDevice, textureFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pTextures[i]) ) )
				throw TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s");
		}
	}
	if( m_pMesh != NULL)
	{
		// �o�E���f�B���O�{�b�N�X�v�Z
		DWORD VertexCnt = m_pMesh->GetNumVertices(); // ���_��
		DWORD VertexSize = m_pMesh->GetNumBytesPerVertex(); // �P�̒��_�̃T�C�Y
		BYTE *p;
		// ���_�o�b�t�@�����b�N���A���_�̐擪�A�h���X�擾
		HRESULT hr = m_pMesh->LockVertexBuffer(D3DLOCK_READONLY,(LPVOID*)&p);
		if(SUCCEEDED(hr)){
			// �o�E���f�B���O�{�b�N�X���Z�o
			D3DXComputeBoundingBox( (D3DXVECTOR3*)p,
			VertexCnt,
			VertexSize,
			&m_min,
			&m_max);
			m_length = m_max - m_min;
			// ���_�o�b�t�@���A�����b�N
			m_pMesh->UnlockVertexBuffer();
		}
	}

	//--------------------------------------
	// ���C�g�̐ݒ�	
	//--------------------------------------
	D3DLIGHT9	mLight;
    ZeroMemory( &mLight, sizeof(D3DLIGHT9) );
	mLight.Type       = D3DLIGHT_DIRECTIONAL;
    mLight.Diffuse.r  = 1.0f;
    mLight.Diffuse.g  = 1.0f;
    mLight.Diffuse.b  = 1.0f;
    D3DXVECTOR3		mVecDir;
    mVecDir = D3DXVECTOR3( -0.5f, -0.5f, 1.0f);
    D3DXVec3Normalize( (D3DXVECTOR3*)&mLight.Direction, &mVecDir );
    m_pDevice->SetLight( 0, &mLight );
    m_pDevice->LightEnable( 0, TRUE );
    m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );


	//�ꎞ�f�[�^�����
	SAFE_RELEASE( pD3DXMtrlBuffer );
}

/*------------------------------------------
   
    �f�X�g���N�^�i���f���̉���j

------------------------------------------*/
C3DModel::~C3DModel()
{
	SAFE_RELEASE(m_pMesh);    // ���b�V�����
	for( DWORD i = 0; i < m_NumMaterials; i++ ){  // �e�N�X�`�����
		SAFE_RELEASE(m_pTextures[i]);
	}
	SAFE_DELETE(m_pTextures);
	SAFE_DELETE(m_pMeshMaterials);   // �}�e���A�����
}

/*------------------------------------------
   
    ���f���̕`��
	@param D3DXVECTOR3   �\���ʒu      
	@param D3DXMATRIX    ���W�ϊ��s��   

------------------------------------------*/
void C3DModel::Draw(D3DXVECTOR3 _position, D3DXMATRIX _matrix)
{
	D3DXMATRIX matWorld = _matrix, matTrans, matScale, matRotate;

	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixRotationYawPitchRoll(&matRotate, D3DXToRadian(m_angle.y), D3DXToRadian(m_angle.x), D3DXToRadian(m_angle.z));

	D3DXMatrixScaling(&matScale,m_vecScale.x,m_vecScale.y,m_vecScale.z);
	//�ړ��̂��߂̃}�g���b�N�X
	D3DXMatrixTranslation(&matTrans, _position.x, _position.y, _position.z);
	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&matWorld);
	matWorld = matScale * matRotate * matTrans;

	D3DXMatrixMultiply(&matWorld,&matWorld,&_matrix);

	// ���[���h�s���o�^
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// �A���t�@�u�����h��L���ɂ���
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �|���S���̓����x���e�N�X�`���ɔ��f
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// ���f���̕`��
	for( DWORD i = 0; i < m_NumMaterials; i++ ){
		m_pMeshMaterials[i].Ambient.a = 1.0f;
		m_pMeshMaterials[i].Ambient.r =
		m_pMeshMaterials[i].Ambient.g =
		m_pMeshMaterials[i].Ambient.b = 1.0f;

		m_pMeshMaterials[i].Diffuse = m_pMeshMaterials[i].Emissive = 
			m_pMeshMaterials[i].Specular = m_pMeshMaterials[i].Ambient;
		m_pDevice->SetMaterial(&m_pMeshMaterials[i]);
		m_pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}
void C3DModel::SetScale(D3DXVECTOR3 _vecScale)
{
	m_vecScale = _vecScale;
}
void C3DModel::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}
void C3DModel::SetAngle(D3DXVECTOR3 _angle)
{
	m_angle = _angle;
}
void C3DModel::GetMeshSize(D3DXVECTOR3* _min,D3DXVECTOR3* _max)
{
	*_min = m_min;
	*_max = m_max;
}
void C3DModel::SetColor(float _a,float _r,float _g,float _b)
{
	m_color.a = _a;
	m_color.r = _r;
	m_color.g = _g;
	m_color.b = _b;
}