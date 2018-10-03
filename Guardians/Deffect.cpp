#include "stdafx.h"


#if _DEBUG
#pragma comment(lib, "Effekseer.Debug.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Debug.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Debug.lib" )
#else
#pragma comment(lib, "Effekseer.Release.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Release.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Release.lib" )
#endif


/*-----------------------------------------------------------------------------------

	�R���X�g���N�^
	@param	LPCTSTR				�t�@�C����
	@param	D3DXVECTOR3			�`��ʒu
	@param	D3DXVECTOR3			�X�P�[��
	@param	LPDIRECT3DDEVICE9	�`��f�o�C�X

------------------------------------------------------------------------------------*/
CEffectt::CEffectt( D3DXVECTOR3 _position , LPDIRECT3DDEVICE9 _device ) : efk_handle(-1) ,
	efk_effect(NULL) , efk_renderer(NULL) , efk_manager(NULL) , m_pDevice(_device) , m_position(_position)
	,m_xAudio( NULL ) , efk_sound(NULL) , m_xa_master(NULL), m_charaHeight(0) , m_angle(0)
{
	//�G�t�F�N�g�֘A��������
	//�`��p�C���X�^���X�̐���
	efk_renderer= EffekseerRendererDX9::Renderer::Create(m_pDevice,2000);
	//�G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	efk_manager = Effekseer::Manager::Create(2000);
	//�`��p�C���X�^���X����`��@�\��ݒ�
	efk_manager->SetSpriteRenderer(efk_renderer->CreateSpriteRenderer());
	efk_manager->SetRibbonRenderer(efk_renderer->CreateRibbonRenderer());
	//�`��p�C���X�^���X����e�N�X�`���̓ǂݍ��݋@�\��ݒ�(�Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���)
	efk_manager->SetTextureLoader(efk_renderer->CreateTextureLoader());
	//���W�n�̎w��(LH : ������W�n, RH : �E����W�n)
	efk_manager->SetCoordinateSystem(Effekseer::COORDINATE_SYSTEM_LH);

	efk_renderer->SetProjectionMatrix(Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(90),1280.0f/730.0f,0.1f,2000.f));
	
    CoInitializeEx(NULL, COINIT_MULTITHREADED);


	XAudio2Create( &m_xAudio );
	
	m_xAudio->CreateMasteringVoice( &m_xa_master );
	// ���Đ��p�C���X�^���X�̐���
	efk_sound = ::EffekseerSound::Sound::Create( m_xAudio, 16, 16 );

	// ���Đ��p�C���X�^���X����Đ��@�\���w��
	efk_manager->SetSoundPlayer( efk_sound->CreateSoundPlayer() );
	
	// ���Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	efk_manager->SetSoundLoader( efk_sound->CreateSoundLoader() );
}
/*-----------------------------------------------------------------------------------

	�G�t�F�N�g�̐���
	@param	LPCWSTR �t�@�C����
	@param	D3DXVECTOR3	�ʒu
	@param	D3DXVECTOR3	�X�P�[��
	@return �Ȃ�

------------------------------------------------------------------------------------*/
void CEffectt::Create( LPCWSTR _fileName,	D3DXVECTOR3	_position)
{

	//�J�����s���ݒ�
	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));

	//char a[256];
	//a = new char[256];
	//std::string str;
	//str = "Effect\\FireBall_01.efk";
	//WCHAR wchar;

	//std::wstring wstr;
	//setlocale( LC_CTYPE, "jpn" );
	
	if( efk_effect == NULL)
		efk_effect = Effekseer::Effect::Create(efk_manager,(const EFK_CHAR*)_fileName);// �G�t�F�N�g�̓Ǎ�
	
	//�G�t�F�N�g����
	//efk_manager->SetLocation(efk_handle,m_position.x,m_position.y ,m_position.z);//�ʒu
	//efk_manager->SetRotation(efk_handle,Effekseer::Vector3D(0.0f,0.0f,0.0f),0.0f);//��]
	//efk_manager->SetScale(efk_handle,m_scale.x,m_scale.y,m_scale.x);//�{��
}
void CEffectt::SetRotate(float _angle)
{
	m_angle = _angle + 90;
}
void CEffectt::StopEffect()
{
	// �G�t�F�N�g�̒�~
	efk_manager->StopEffect( efk_handle );
}
/*-----------------------------------------------------------------------------------

	�f�X�g���N�^

------------------------------------------------------------------------------------*/
CEffectt::~CEffectt()
{
	// �G�t�F�N�g�̒�~
	efk_manager->StopEffect( efk_handle );
	// �G�t�F�N�g�����(�Đ����̏ꍇ�͍Đ��I�����Ɏ����I�ɉ��)
	ES_SAFE_RELEASE(efk_effect);
	
	efk_manager->Destroy();
	efk_sound->Destory();
	efk_renderer->Destory();

	// XAudio2�̉��
	if(  m_xa_master != NULL )
	{
		m_xa_master->DestroyVoice();
		m_xa_master = NULL;
	}
	ES_SAFE_RELEASE( m_xAudio );

	//CoUninitialize();
}
/*-----------------------------------------------------------------------------------

	����
	@param	D3DXVECTOR3 �ړ���
	@return �Ȃ�

------------------------------------------------------------------------------------*/
void CEffectt::Control(D3DXVECTOR3 _value , D3DXVECTOR3 _position)
{

	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));

	//�`��
	efk_manager->Update();//�G�t�F�N�g�̍X�V����
		
	efk_renderer->BeginRendering();//�G�t�F�N�g�̕`��J�n����

	efk_manager->Draw();//�G�t�F�N�g�̕`��

	efk_renderer->EndRendering();//�G�t�F�N�g�̕`��I������

	// �G�t�F�N�g�̈ړ��������s��
	efk_manager->AddLocation( efk_handle,Effekseer::Vector3D( _value.x,_value.y,_value.z ) );
	//m_position += _value;
	// �G�t�F�N�g�������Ԃ����Z
	m_time++;

}
/*-----------------------------------------------------------------------------------

	�`��
	@param	�Ȃ�
	@return true �Đ��J�n : false �Đ���

------------------------------------------------------------------------------------*/
bool CEffectt::Play( D3DXVECTOR3 _position ,D3DXVECTOR3 _scale )
{

	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));
	static float a = 0;
	// �G�t�F�N�g�̃C���X�^���X�����݂��Ă��Ȃ���΍Đ�����
	if(!efk_manager->Exists(efk_handle)){
		m_time = 0;
		m_position = _position;
		m_position.y += m_charaHeight;
		// �G�t�F�N�g�Đ��ʒu�͌��_���獂���𑫂�
		efk_handle = efk_manager->Play(efk_effect,m_position.x,m_position.y,m_position.z);//�G�t�F�N�g�̍Đ�
		
		
		efk_manager->SetRotation(efk_handle,0.f,180.f,0.f );//��]
		efk_manager->SetRotation(efk_handle,D3DXToRadian(m_angle),0.f,0.f );//��]
		efk_manager->SetRotation(efk_handle,0.f,D3DXToRadian(m_angle),0.f );//��]

		efk_manager->SetScale(efk_handle,_scale.x,_scale.y,_scale.x);//�{��
		return true;
	}
	a++;
	return false;
}

bool CEffectt::replay(D3DXVECTOR3 _position,D3DXVECTOR3 _scale)
{
	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));

	StopEffect();
	// �G�t�F�N�g�̃C���X�^���X�����݂��Ă��Ȃ���΍Đ�����
	if(!efk_manager->Exists(efk_handle)){
		m_time = 0;
		m_position = _position;
		// �G�t�F�N�g�Đ��ʒu�͌��_���獂���𑫂�
		efk_handle = efk_manager->Play(efk_effect,m_position.x,m_position.y + m_charaHeight,m_position.z);//�G�t�F�N�g�̍Đ�
		static float a = 0;
		efk_manager->SetRotation(efk_handle,0.f,180.f,0 );//��]
		efk_manager->SetRotation(efk_handle,D3DXToRadian(m_angle),0.f,0.f );//��]
		efk_manager->SetRotation(efk_handle,0.f,D3DXToRadian(m_angle),0.f );//��]	
		efk_manager->SetScale(efk_handle,_scale.x,_scale.y,_scale.x);//�{��
		return true;
	}
	return false;
}
/*-----------------------------------------------------------------------------------

	�G�t�F�N�g���Đ��I�����Ă��邩�ǂ���
	@param	�Ȃ�
	@return bool true �Đ��I���@: false �Đ���

------------------------------------------------------------------------------------*/
bool CEffectt::checkEnd()
{
	return efk_manager->Exists(efk_handle);
}
/*-----------------------------------------------------------------------------------

	�`��ʒu���擾
	@param	�Ȃ�
	@return D3DXVECTOR3�@�ʒu

------------------------------------------------------------------------------------*/
D3DXVECTOR3 CEffectt::GetPosition()
{
	D3DXVECTOR3 pos;
	
	pos.x = efk_manager->GetLocation(efk_handle).X;
	pos.y = efk_manager->GetLocation(efk_handle).Y;
	pos.z = efk_manager->GetLocation(efk_handle).Z;

	return m_position;
}
/*-----------------------------------------------------------------------------------

	�J��
	@param	�Ȃ�
	@return �Ȃ�

------------------------------------------------------------------------------------*/
void CEffectt::Release()
{
	// �G�t�F�N�g�̒�~
	//efk_manager->StopEffect( efk_handle );
	// �G�t�F�N�g�����(�Đ����̏ꍇ�͍Đ��I�����Ɏ����I�ɉ��)
	ES_SAFE_RELEASE(efk_effect);
}
Effekseer::Matrix44 CEffectt::D3DXMATRIXtoMatrix44( D3DXMATRIX* _matrix)
{
	Effekseer::Matrix44 mat;
	mat.Values[0][0] = _matrix->_11;
	mat.Values[0][1] = _matrix->_12;
	mat.Values[0][2] = _matrix->_13;
	mat.Values[0][3] = _matrix->_14;
	mat.Values[1][0] = _matrix->_21;
	mat.Values[1][1] = _matrix->_22;
	mat.Values[1][2] = _matrix->_23;
	mat.Values[1][3] = _matrix->_24;
	mat.Values[2][0] = _matrix->_31;
	mat.Values[2][1] = _matrix->_32;
	mat.Values[2][2] = _matrix->_33;
	mat.Values[2][3] = _matrix->_34;
	mat.Values[3][0] = _matrix->_41;
	mat.Values[3][1] = _matrix->_42;
	mat.Values[3][2] = _matrix->_43;
	mat.Values[3][3] = _matrix->_44;
	return mat;

}
void CEffectt::SetCharaHeight(float _height)
{
	m_charaHeight = _height;
}
void CEffectt::SetLocation(D3DXVECTOR3 _position)
{
	efk_manager->SetLocation( efk_handle,Effekseer::Vector3D( _position.x,_position.y + m_charaHeight,_position.z ));
}
int CEffectt::GetDrawTime()
{
	// �G�t�F�N�g�����݂��Ă�����`�掞�Ԃ�Ԃ�
	if( efk_manager->Exists(efk_handle))
		return m_time;
	else{
		return m_time = 0;
	}
}