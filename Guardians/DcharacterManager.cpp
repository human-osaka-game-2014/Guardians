/**
 * @file DcharacterManager.cpp
 * @author �h��
 */
#include "stdafx.h"

/**
 * �R���X�g���N�^
 * @param LPDIRECT3DDEVICE9	�`��f�o�C�X
 */
CCharacterManager::CCharacterManager(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,MODELDATA* _chara) : m_pDevice(_pDevice),m_pGameData(_pGameData) , m_moveFlag(false) , m_hitWall(false) , isHit(false)
{	
	// ���f���f�[�^��ۑ�
	m_pModel = _chara;
	m_activePlayer = m_pModel->player[m_pGameData->m_playerCharaNo];
	// �퓬�J�n���̉��o�̈ʒu���Z�b�g
	if( m_activePlayer->GetStep() == CCharacter::STEP_FADE_IN )
		m_activePlayer->SetPosition(INIT_PLAYER_POSITION);
	// �`�F�b�N�|�C���g�Q�ȍ~�͉��o�����܂Ȃ�
	else if( m_activePlayer->GetStep() == CCharacter::STEP_MOVE )
		m_activePlayer->SetPosition(INIT_PLAYER_POSITION);
	
	m_activePlayer->SetPosition( INIT_PLAYER_POSITION );

	m_activePlayer->SetCharaSpeed( m_pGameData->m_chara[ m_pGameData->m_turnNo[0] ].spd );
	// �ҋ@���[�V�������Z�b�g
	m_activePlayer->SetPosition( INIT_PLAYER_POSITION );
	m_activePlayer->ResetMotion(CPlayer::MOTION_WAIT);


	if( (m_pGameData->m_selectStageNum + 1) % 4 == 0 )
		m_activeEnemy = _chara->enemy[3];
	else 
		m_activeEnemy = _chara->enemy[0];
	m_activeEnemy->SetPosition( INIT_ENEMY_POSITION );

	//m_activeEnemy->SetPosition( D3DXVECTOR3(5.f,0.f,2.f) );
	m_activeEnemy->ResetMotion(CPlayer::MOTION_WAIT);

}
/**
 * �f�X�g���N�^
 */
CCharacterManager::~CCharacterManager()
{

}
/**
 * ����
 */
void CCharacterManager::Control()
{

	// �v���C���[�̐���
	m_activePlayer->Control(); 
	// �G�̐���
	m_activeEnemy->SetPlayerPos( m_activePlayer->GetPosition() );	// �v���C���[�̈ʒu���Z�b�g
	m_activeEnemy->Control();	// �G�̐���

	// �v���C���[�ƓG�̏�Ԃ��擾
	m_playerState =  m_activePlayer->GetState();
	m_enemyState  =	 m_activeEnemy->GetState();

	// �����̃L�����N�^�[���U����ԈȊO�Ȃ�Փ˔�����s��Ȃ�
	if( m_enemyState < STATE_ATTACK && m_playerState < STATE_ATTACK ) return;

	//// Player�̍U������
	// �G�̍U������
	if ( m_playerState >= STATE_ATTACK ){
		// �G�̂��ꔻ��ƃv���C���[�̍U��������`�F�b�N
		if( m_pGameData->m_playerCharaNo == MINE ) 
			// ����Ă���L�������~�l���c�@�̎��̓��C�ƃ��b�V���Ŕ�����s��
			isHit = RayToBox(m_activePlayer->GetRay(),m_activeEnemy->GetunHittingBox());
		else 
			isHit = HitCheck( m_activePlayer->GetHittingBox(),m_activeEnemy->GetunHittingBox() );
		// �q�b�g���Ă��邩�ǂ������Z�b�g����
		m_activePlayer->SetHitFlag(isHit);
		// ���[�V�������̃_���[�W
		CalcPlayerDamage();
	}


	// �G�̍U������
	if ( m_enemyState >= STATE_ATTACK ){
		isHit = HitCheck( m_activeEnemy->GetHittingBox(),m_activePlayer->GetunHittingBox() );

		m_activeEnemy->SetHitFlag(isHit);
	 
		CalcEnemyDamage();
	}
}
/**
 * �G�̃_���[�W���v�Z����
 */
void CCharacterManager::CalcPlayerDamage()
{
	srand((unsigned)time(NULL));
	if( isHit ){

		m_activePlayer->SetHitFlag(isHit);

		int damage = 0; // �_���[�W��
		// �v���C���[�̍U���͂��擾
		int atk = m_pGameData->m_chara[m_pGameData->m_turnNo[0]].atk;
		//int def = m_activeEnemy->
		// �G�̖h��͂��擾
		int def = 0;
		// �_���[�W�v�Z( ( �v���C���[�U���� �~ 2 ) - �G�h��� �~ �h��ђ� ) �~ �Z�␳ �~ �����_���l�␳�i�����_�ȉ��؎̂āj
		
		damage = ( ( atk * 2 ) - def * m_activePlayer->Getflag() ) * m_activePlayer->GetDamage() * RAND_FLOAT(0.9f,1.1f);
		if( damage != 0 ) CBattleScene::comboCount++;
		// �{�X��HP�����炷
		m_pGameData->m_pDamage.damage += damage;
		isHit = false;
	}
	
	if( m_pGameData->m_win == true ){
		m_activeEnemy->ResetMotion( CEnemy::MOTION_DEATH );
		m_activePlayer->ResetMotion( CPlayer::MOTION_APPEAL2 );
	}

}
/**
 * �v���C���[�̃_���[�W���v�Z����
 */
void CCharacterManager::CalcEnemyDamage()
{
	if( isHit ){
		int atk = m_activeEnemy->GetDamage();
		int def = 0;// �h��␳�l
		int damage = 0;

		//( �G�Z�U���� - �h��Z�␳ ) �~ 2 �~ (120 - �v���C���[�h���) / 100 �~ �����_���l�␳�i�����_�ȉ��؎̂āj
		//damage = ( atk - def ) * 2 * (120 - m_pGameData->m_chara[m_pGameData->m_turnNo[0]].def ) / 100 * RAND_FLOAT(0.9,1.1);
	
		// �󂯂��_���[�W�����Z
		m_pGameData->m_pDamage.damageTaken += atk;
		isHit = false;

		// atk��0�łȂ���(�_���[�W���󂯂��Ƃ�)
		if( atk ){
			m_activePlayer->ResetMotion( CPlayer::MOTION_FLINCH ); // �Ђ�݃��[�V������
		}
	}

	// HP��0�ɂȂ�����
	if( m_pGameData->m_chara[m_pGameData->m_turnNo[0]].hp <= m_pGameData->m_pDamage.damageTaken )
		m_pGameData->m_death = true;

	if( m_pGameData->m_death == true ) {
		m_activePlayer->ResetMotion( CPlayer::MOTION_DEAD );	// �v���C���[�����S	���[�V������
	}
}
/**
 * HP���擾����
 */
CGameData::ENEMY_STATUS CCharacterManager::GetHP()
{
	return m_activeEnemy->GetStatus();
}
/**
 * �Փ˂��Ă��邩�`�F�b�N����
 * 	@param	std::vector<XFileAnimationMesh::BOX> �U������
 *	@param  std::vector<XFileAnimationMesh::BOX> ���ꔻ��
 *  @retval true	�������Ă���
 *  @retval false	�������Ă��Ȃ�
 */
bool CCharacterManager::HitCheck(std::vector<XFileAnimationMesh::BOX> _hitting_box,std::vector<XFileAnimationMesh::BOX> _unhitting_box)
{
	// �v���C���[�̂��ꔻ��ƓG�̍U��������`�F�b�N
	for(unsigned i = 0; i < _unhitting_box.size();i++){
		for(unsigned j = 0; j < _hitting_box.size();j++){
			// ��x�ł��q�b�g���Ă���΃��[�v�𔲂���
			if( AABBtoAABB( _hitting_box[j],_unhitting_box[i]) ){
				return true;
			}
		}
	}
	// �������Ă��Ȃ�
	return false;
}
/**
 * �`��
 */
void CCharacterManager::Draw()
{
	m_activePlayer->Draw();

	m_activeEnemy->Draw();

	m_activePlayer->DrawEffect();

}
/**
 * �~���m�̏Փ˔���
 * @param[in]	_sphereA �X�t�B�A
 * @param[in]	_pShereB  �X�t�B�A
 */
bool CCharacterManager::SphereCollision(XFileAnimationMesh::SPHERE _sphereA, XFileAnimationMesh::SPHERE _sphereB)
{
	D3DXVECTOR3 dmy;
	if(D3DXVec3LengthSq( D3DXVec3Subtract(&dmy,&_sphereA.position,&_sphereB.position) ) <= (_sphereA.radius+_sphereB.radius)*(_sphereA.radius+_sphereB.radius))
	{
        return true;    //�Փ˂��Ă���
    }
	return false;       //�Փ˂��Ă��Ȃ�
}
/**
 * �{�b�N�X���m�̓����蔻��
 * @param[in]	_box1 �{�b�N�X
 * @param[in]	_box2 �{�b�N�X
 */
bool CCharacterManager::AABBtoAABB(XFileAnimationMesh::BOX _box1,XFileAnimationMesh::BOX _box2)
{ 
	if( _box1.min.x < _box2.max.x && _box2.min.x < _box1.max.x && _box1.min.y < _box2.max.y && _box2.min.y < _box1.max.y)
	{
		return true;
	}
	return false;
}
/**
 * �~�ƃ{�b�N�X���m�̓����蔻��
 * @param[in]	_sphere �{�b�N�X
 * @param[in]	_box �{�b�N�X
 *  @retval true	�������Ă���
 *  @retval false	�������Ă��Ȃ�
 */
bool CCharacterManager::SphereToBox(XFileAnimationMesh::SPHERE _sphere,XFileAnimationMesh::BOX _box)
{
	// ��̉~�̒��S�_�����`�̂P�ԋ߂����W
	float x, y;
	// �P�ԋ߂�x���W�����߂�
	if ( _sphere.position.x < _box.min.x )
		x = _box.min.x;
	else if ( _sphere.position.x > _box.max.x )
		x = _box.max.x;
	else
		x = _sphere.position.x;
 
	// �P�ԋ߂�y���W�����߂�
	if ( _sphere.position.y < _box.min.y )
		y = _box.min.y;
	else if ( _sphere.position.y > _box.max.y )
		y = _box.max.y;
	else
		y = _sphere.position.y;
	// x,y�̈ʒu����~�̋��������߂�
	float a = abs( _sphere.position.x - x );
    float b = abs( _sphere.position.y - y );
 
    float c = sqrt((a * a) + (b * b));
	// ���߂��������~�̔��a��菬�����Ȃ�
	if ( c < _sphere.radius){
		return true; // �Փ�
	}
	return false;
}
/**
 *  ���C�ƃ{�b�N�X�̏Փ˔���
 * 	@param	_ray ���C
 *	@param  _box �{�b�N�X
 *  @retval true	�������Ă���
 *  @retval false	�������Ă��Ȃ�
 */
bool CCharacterManager::RayToBox(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box)
{
	// �l�p�`��4�̕ӂ�ۑ�����
	XFileAnimationMesh::RAY_PARAM EnemyRay[4];
	// �󂯎������`�̐���for������
	for(unsigned i = 0; i < _box.size(); i++){

		// �������n�_�Ƃ�����
		// �c
		EnemyRay[0].position  = EnemyRay[1].position = D3DXVECTOR3(_box[i].min.x,_box[i].min.y,_box[i].min.z);
		EnemyRay[0].length = D3DXVECTOR3(0,_box[i].length.y,_box[i].min.z);
		// ��
		EnemyRay[1].length = D3DXVECTOR3(_box[i].length.x,0,_box[i].min.z);
		
		// �E��
		// �c
		EnemyRay[2].position = EnemyRay[3].position =  D3DXVECTOR3(_box[i].max.x,_box[i].max.y,_box[i].max.z);
		EnemyRay[2].length = D3DXVECTOR3(0,_box[i].length.y,_box[i].min.z);
		// ��
		EnemyRay[3].length = D3DXVECTOR3(_box[i].length.x,0,_box[i].min.z);

		bool isHit = false;
		// �e�ӂƃ��C���������Ă��Ȃ������ׂ�
		for(int i = 0; i < 4; i++){
			isHit = ColSegments(_ray,EnemyRay[i]);

			if( isHit )
				return true;

		}
	}
	return false;
}
/**
 *  �����Ɛ����̏Փ�
 * 	@param	_ray1 ���C
 *	@param  _ray2 ���C
 *  @retval true	�������Ă���
 *  @retval false	�������Ă��Ȃ�
 */
bool CCharacterManager::ColSegments(XFileAnimationMesh::RAY_PARAM _ray1,XFileAnimationMesh::RAY_PARAM _ray2)
{
	CVector v;
	D3DXVECTOR3 vector = _ray2.position - _ray1.position;
	float CrossProduct = v.D3DXVecCross( &_ray1.length,&_ray2.length );
	if ( CrossProduct == 0.0f ) {
      // ���s���
      return false;
   }

   float Crs_v_v1 = v.D3DXVecCross( &vector, &_ray1.length );
   float Crs_v_v2 = v.D3DXVecCross( &vector, &_ray2.length );

   float t1 = Crs_v_v2	/ CrossProduct;
   float t2 = Crs_v_v1 / CrossProduct;

   const float eps = 0.00001f;
   if ( t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1 ) {
      // �������Ă��Ȃ�
      return false;
   }

   return true;
}
/**
 *  �����Ɛ����̏Փ�
 * 	@param	_ray ���C
 *	@param  _box �{�b�N�X
 *  @retval true	�������Ă���
 *  @retval false	�������Ă��Ȃ�
 */
bool CCharacterManager::RayToMesh(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box)
{
	BOOL isHit = false;
	DWORD index,pCountOfHits;
	float p,v,d;
    LPD3DXBUFFER *ppAllHits = NULL;

	// �󂯎����box�̃��b�V���̐�����for������
	for(unsigned i = 0; i < _box.size(); i++){
		// ���[�J�����W�n�ɕϊ�
		//D3DXVECTOR3 length =  _ray.position + _ray.length;
		D3DXMATRIX matTrans, matWorld, invWorld, invRotation,matScale;
		//  �g��i�k���j�s����쐬����
		D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
		//D3DXMatrixIdentity(&meshRotate);
		D3DXMatrixTranslation(&matTrans,_box[i].position.x, _box[i].position.y, _box[i].position.z);
		matWorld = matScale * matTrans;
		// �t�s������߂�
		D3DXMatrixInverse(&invWorld, 0, &matWorld);
		//D3DXMatrixInverse(&invRotation, 0, &meshRotate);

		D3DXVECTOR3 invRayPos,invRayDir;
		D3DXVec3TransformCoord(&invRayPos, &_ray.position, &invWorld);
		
		D3DXVec3TransformCoord(&invRayDir,&_ray.length,&invWorld);

		// ���[�J�����W�ɕϊ����ďՓ˔�����s��
		D3DXIntersect( _box[i].pMesh,&invRayPos,&invRayDir,&isHit,&index,&p,&v,&d,ppAllHits,&pCountOfHits);
		if( isHit ){
			return true;
		}
	}
	// �������Ă��Ȃ�
	return false;
}
/**
 *  �v���C���[�����擾����
 *  @return �A�N�e�B�u�v���C���[�̃|�C���^�[��Ԃ�
 */
CPlayer* CCharacterManager::GetPlayer()
{
	return m_activePlayer;
}
/**
 * �L�����N�^�[�̈ړ����x���擾����
 * @return �ړ����x
 */
D3DXVECTOR2 CCharacterManager::GetCharaSpeed()
{
	return m_activePlayer->GetCharaSpeed();
}
/**
 *  �L�����N�^�[�̈ʒu���擾����
 * 	@return	�ʒu
 */
D3DXVECTOR3 CCharacterManager::GetCharaPosition()
{
	return m_activePlayer->GetPosition();
}
/**
 * ���[�V�������I�����Ă��邩���ׂ�
 * @param[in] _motionID ���[�V�����ԍ�
 * @retval true ���[�V�����I��
 * @retval false ���[�V�����Đ���
 */
bool CCharacterManager::GetMotionEnd(int _motionID)
{
	return m_activePlayer->CheckMotionEnd(_motionID);
}
/**
 * �L�����N�^�[��ύX����(���[�V���������ւ���E�L�����N�^�[�̈ړ����x���Z�b�g����)
 * @param[in] _time �o�ߎ���
 */
void CCharacterManager::CharacterChange(int _time)
{
	// ���f���͔�����
	float MAX_ALPHA = 0.5f;
	const int ERASE_FRAME = 10;
	float addAlpha = MAX_ALPHA / ERASE_FRAME;

	m_activePlayer->SetCharaSpeed( 0 ); // �L�����N�^�[�̈ړ����x��0��

	if( _time <= ERASE_FRAME )
		m_activePlayer->addAlpha(-addAlpha);
	else if ( _time >= CBattleScene::CHANGE_LIMIT ){
		// ���f���f�[�^��擪�̃L�����֓���ւ���
		m_activePlayer = m_pModel->player[m_pGameData->m_playerCharaNo];
		m_activePlayer->SetCharaSpeed( m_pGameData->m_chara[ m_pGameData->m_playerCharaNo ].spd ); // �L�����N�^�[�̈ړ����x���Z�b�g
		m_activePlayer->ResetMotion(CPlayer::MOTION_WAIT); // �ҋ@���[�V�������Z�b�g
	}else{
		// ���f���f�[�^��擪�̃L�����֓���ւ���
		m_activePlayer = m_pModel->player[m_pGameData->m_playerCharaNo];
		m_activePlayer->ResetMotion(CPlayer::MOTION_WAIT); // �ҋ@���[�V�������Z�b�g
	}
}
/**
 * ���f���̃A���t�@�l��ύX����
 */
void CCharacterManager::SetAlpha()
{
	m_activePlayer->addAlpha(1.0f);
}