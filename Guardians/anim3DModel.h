/// X�t�@�C������Ǎ��񂾃��b�V��
class CAnim3DModel sealed {
private:
	LPDIRECT3DDEVICE9	pDevice;		// Direct3D�f�o�C�X�I�u�W�F�N�g
	LPD3DXMESH			pMesh;			// ���b�V��
	D3DMATERIAL9*		pMeshMaterials;	// �}�e���A���z��
	LPDIRECT3DTEXTURE9*	pMeshTextures;	// �e�N�X�`���z��
	DWORD				dwNumMaterials;	// �}�e���A���E�e�N�X�`���z��̑傫��

public:
	/// �R���X�g���N�^
	/// @param filename �摜�t�@�C����
	/// @param pDev		Direct3D�f�o�C�X�I�u�W�F�N�g
	CAnim3DModel(LPCTSTR filename, LPDIRECT3DDEVICE9 pDev);
	~CAnim3DModel(void);

	void Draw(D3DXVECTOR3 position, D3DXMATRIX rotation);
	LPD3DXMESH GetMesh();
};

/// ���b�V���̃r���[�ϊ��A�ˉe�ϊ����s�Ȃ��J����
class MeshCamera sealed {
private:
	LPDIRECT3DDEVICE9 pDevice;
public:
	/// �R���X�g���N�^
	/// @param pDev Direct3D�f�o�C�X�I�u�W�F�N�g
	MeshCamera(LPDIRECT3DDEVICE9 pDev);

	~MeshCamera(void);
	void Look(D3DXVECTOR3 eyePoint, D3DXVECTOR3 lookAtPoint);
};

/// ���b�V���p���C�g
class MeshLight sealed {
private:
	LPDIRECT3DDEVICE9 pDevice;
	D3DLIGHT9 light;

public:
	/// �R���X�g���N�^
	/// @param pDev Direct3D�f�o�C�X�I�u�W�F�N�g
	MeshLight(LPDIRECT3DDEVICE9 pDev);

	~MeshLight(void);
	void Illume(D3DXVECTOR3 direction);
};


/// X�t�@�C������Ǎ��񂾃A�j���[�V�������b�V��
class XFileAnimationMesh sealed {
public:
	// ���C�̏��
	typedef struct _RAY{
		D3DXVECTOR3 position;	// �J�n�n�_
		D3DXVECTOR3 length;		// ���C�̒���
	}RAY_PARAM;


	struct SPHERE // �X�t�B�A���i�[�p�\����
	{
		D3DXVECTOR3 center;				// ���S���W
		D3DXVECTOR3 position;			// �Փ˔���p(���S���W)
		float radius;					// ���a
		LPD3DXMESH  pShereMesh;			// ���b�V��
		D3DMATERIAL9*  pShereMaterials;	// �}�e���A��
	};

	struct BOX // �{�b�N�X���i�[�p�\����
	{
		char*		name;
		D3DXVECTOR3 center;				// ���_
		D3DXVECTOR3 size;
		D3DXVECTOR3 min;				// �ŏ��_���W
		D3DXVECTOR3 max;				// �ő�_���W
		D3DXVECTOR3 length;				// �ŏ��_����ő�_�ւ̃x�N�g��
		D3DXVECTOR3 position;		// ���b�V���̈ʒu
		LPD3DXMESH  pMesh;			// ���b�V��
		D3DMATERIAL9*  pMaterials;	// �}�e���A��
		LPD3DXBUFFER		pAdjacency;
	};
	// �A�j���[�V�������Ԋi�[�p
	typedef struct _ANIMLIST
	{
		double startTime;
		double endTime;
		bool   chancel;
	}ANIMLIST;

private:

	struct MYFRAME: public D3DXFRAME {
		D3DXMATRIX CombinedTransformationMatrix;
	};
	struct MYMESHCONTAINER: public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9*  ppTextures;
		DWORD dwWeight;							// �d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
		DWORD dwBoneAmt;						// �{�[���̐�
		LPD3DXBUFFER pBoneBuffer;				// �{�[���E�e�[�u��
		D3DXMATRIX** ppBoneMatrix;				// �S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
		D3DXMATRIX* pBoneOffsetMatrices;		// �t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
	};
	class MyHierarchy : public ID3DXAllocateHierarchy {
	private:
		void CreateTexture(MYMESHCONTAINER* pMeshContainer, LPDIRECT3DDEVICE9 pDevice, DWORD NumMaterials);
		void SetDefaultMaterial(MYMESHCONTAINER* pMeshContainer);
	public:
		MyHierarchy(){};
		~MyHierarchy(){};
		STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
		STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*, CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD*, LPD3DXSKININFO, LPD3DXMESHCONTAINER*);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);

	};

	LPDIRECT3DDEVICE9			pDevice;										// Direct3D�f�o�C�X�I�u�W�F�N�g
	MyHierarchy					cHierarchy;										// �A���P�[�g�q�G�����L�[�I�u�W�F�N�g
	LPD3DXFRAME					pFrameRoot;										// �t���[��
	LPD3DXANIMATIONCONTROLLER	pAnimController;								// �A�j���[�V�����R���g���[��
	LPD3DXANIMATIONSET			pAnimSet[100];									// �A�j���[�V�����Z�b�g
	int							m_curAnimNo;									// ���݂̃A�j���[�V�����ԍ�
	
	double						m_AnimTime;										// 
	std::vector<ANIMLIST>		m_animList;
	_D3DCOLORVALUE				m_color;									// ���b�V���̐F


	HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER);							// ���b�V���ɍs�������U��
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME);								// �ċA�R�[�h�F�t���[���K�w��W�J���Ċe���b�V���ɍs�������U��
	
	D3DXVECTOR3		m_vecScale;
	void UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );						// �ċA�R�[�h�F�t���[���̃��[���h�ϊ�
	void RenderMeshContainer(LPDIRECT3DDEVICE9, MYMESHCONTAINER* ,MYFRAME* );	// ���b�V���R���e�i�̃����_�����O
	void DrawFrame(LPDIRECT3DDEVICE9,LPD3DXFRAME );								// �ċA�R�[�h�F�t���[���̃����_�����O
	void FreeAnim(LPD3DXFRAME pF);												// �ċA�R�[�h�F�S�Ẵ��b�V���R���e�i�������[�X
public:

	/// �R���X�g���N�^
	/// @param filename �摜�t�@�C����
	/// @param pDevice	Direct3D�f�o�C�X�I�u�W�F�N�g
	XFileAnimationMesh(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 _scale);

	/// �f�X�g���N�^
	~XFileAnimationMesh(void);

	// �`��
	void Draw(D3DXVECTOR3 position, D3DXMATRIX rotation);

	void CreateSphere(XFileAnimationMesh::SPHERE* _sphere);
	
	// �{�b�N�X�̃}�e���A������
	void CreateBox(XFileAnimationMesh::BOX* _box);
	// �X�P�[�����Z�b�g
	void SetScale(D3DXVECTOR3 _vecScale);
	/// ���Ԃ�i�s
	double AdvanceTime(double time);

	/// ������؂�ւ���
	bool ChangeMotion(int motion_number);

	// �A�j���[�V�����Đ����Ԃ��Z�b�g����
	void SetAnimList(std::vector<ANIMLIST>* _animList);

	// �t���[�����擾
	LPD3DXFRAME GetFrameRoot();

	void SetMaterial(MYMESHCONTAINER* pMeshContainer);								
	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);	// �}�e���A���̐F���Z�b�g
	void Scalling(D3DXVECTOR3* _size,D3DXVECTOR3 _scale)							// �X�P�[�����Z�b�g
	{
		_size->x = _size->x * _scale.x;
		_size->y = _size->y * _scale.y;
		_size->z = _size->z * _scale.z;
	}

};