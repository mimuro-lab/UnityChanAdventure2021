
/*!
@file AnimationSwitch.cpp
@brief AnimationSwitch�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/15:29
@author mimuro
*/

#include "AnimationSwitch.h"

/*!
@brief �R���g���[����A�j���[�V�����A�X�e�[�^�X�ⓖ���蔻��̏�Ԃ��玟�̃A�N�V������Ԃ��v�Z����B
@par �Ԃ��̂�Animation�^�̕ϐ��B
@date 2020/05/04/15:30
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::update(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus,
	VirtualController controller)
{

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "damaging %d", playerStatus.isDamaging);
	soardCombContinue = getSoardComb(nowAction, animation, soardCombContinue, controller);

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "comb : %d", soardCombContinue);
	
	// �A�j���[�V������؂�ւ��Ă��悢�Ȃ�A
	if (acceptSwitching(animation, nowAction)) 
	{
		// _next�֎��̃V�[�����擾����B
		nextAction = getNextAction(collision, animation, playerStatus, nowAction, controller);
		if(acceptNextAction(nowAction, nextAction, playerStatus)) {
			// �A�j���[�V�����I�u�W�F�N�g���X�V���A�I���B
			nowAction = nextAction;
			return switchingAnimation(nextAction, playerStatus);
		}

		// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
		// switchingAnimation()�����s�����Ɋ֐����I���B(refresh�����ɏI��)
		if (isRefresh(nextAction, animation)) {
			shared_ptr<Animation> returnAnimation = animation;
			returnAnimation->refreshing();
			return returnAnimation;
		}
	}

	return animation;

}

/*!
@brief �A�j���[�V������؂�ւ��Ă��ǂ����𔻒f����B
@par �A�j���[�V�������I������O�ɐ؂�ւ��Ă��悢��Ԃ��A�����łȂ��Ă��A�j���[�V�������I����������true��Ԃ��B
@date 2020/05/04/15:30
@author mimuro
*/
bool AnimationSwitch::acceptSwitching(shared_ptr<Animation> animation, characterAction nowAction)
{
	// ���̏�Ԃ��r���؂�ւ��n�j��������؂�ւ��n�j
	if (IsAction_canSwitching[static_cast<int>(nowAction)])
		return true;

	// �r���؂�ւ��m�f���A�j���[�V�������I��������؂�ւ��n�j
	if(!IsAction_canSwitching[static_cast<int>(nowAction)] && animation->isEnd())
		return true;

	return false;
}

/*!
@brief ���̏�Ԃ��󂯓���Ă悢���ǂ����𔻒f����B
@par ���̏�Ԃ����Ɠ�����������p���Ȃ̂Ő؂�ւ��������s��Ȃ��B�܂��AJump_MidAir�ł͑��x��������̎��͐؂�ւ��������s��Ȃ��B
@date 2020/05/04/15:43
@author mimuro
*/
bool AnimationSwitch::acceptNextAction(characterAction nowAction, characterAction nextAction, Status _playerStatus)
{
	// ���݂̃A�N�V�����Ɠ����A�N�V���������̃A�N�V������������؂�ւ��Ȃ��B
	if (nowAction == nextAction)
		return false;

	//Jump_MidAir�̎��A���A���x������̊Ԃ̓A�j���[�V������؂�ւ��Ȃ��B
	if (nowAction == characterAction::Jump_MidAir && playerStatus._y_speed < 0)
		return false;

	// ��L�̏����ɓ��Ă͂܂�Ȃ��̂Ȃ�؂�ւ���B
	return true;
}

/*!
@brief �A�j���[�V���������t���b�V�����邩�ǂ������f����֐��B
@par ���Ⴊ�ށE�W�����v�i�󒆁j�A�A�j���[�V�������I�����Ă��Ȃ��Ȃ烊�t���b�V�����Ȃ��B����ȊO�Ȃ烊�t���b�V������B
@date 2020/05/04/15:48
@author mimuro
*/
bool AnimationSwitch::isRefresh(characterAction nowAction, shared_ptr<Animation> animation)
{
	// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
	// switchingAnimation()�����s�����Ɋ֐����I���B(refresh�����ɏI��)
	if (nowAction == characterAction::Crouch )
		return false;
	
	if (nowAction == characterAction::Jump_MidAir)
		return false;

	// �����A�N�V���������͂��ꑱ���āA���݂̃A�j���[�V�������I�������猻�݂̃A�j���[�V���������t���b�V������B
	// �܂��A���̃R�}�ł̏�L�̏���"_next = getNextAction();"�ōēx���̏�Ԃ��X�V�����B
	if (!animation->isEnd())
		return false;

	// ��L�̏����ɓ��Ă͂܂�Ȃ��̂Ȃ烊�t���b�V������B
	return true;
}

bool AnimationSwitch::getSoardComb(characterAction nowAction, shared_ptr<Animation> animation, bool nowCombContinue, VirtualController controller)
{
	if (controller.push_X) {
		if (nowAction == characterAction::Soard1_init)
			return true;
		if (nowAction == characterAction::Soard2_init)
			return true;
		if (nowAction == characterAction::Soard3_init)
			return true;
	}


	return nowCombContinue;
}

/*!
@biref �R���g���[���̓��͏�Ԃɂ���Ď��̃A�N�V������Ԃ��擾����BplayerStatus�̍X�V�͂����ł͍s��Ȃ��B��Ԃ����肷�鏈�������B
@date 2020/05/04/15:49
@author mimuro
*/
characterAction AnimationSwitch::getNextAction(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus,
	characterAction nowAction
	, VirtualController controller)
{

	if (playerStatus.isDead) {
		return characterAction::Death;
	}

	if (playerStatus.isDamage) {
		return characterAction::Damage;
	}

	// Brake���I������狭���I�ɃA�C�h�����O��ԂɕύX����
	if (nowAction == characterAction::Brake && animation->isEnd()) {
		return characterAction::Idle;
	}

	// Jump_Up to Jump_MidAir
	if (nowAction == characterAction::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return characterAction::Jump_MidAir;
	}

	// ���U���P�͂���
	if (controller.push_X)
		return characterAction::Soard1_init;


	// ���U���R���{1
	if (nowAction == characterAction::Soard1_init && nowAction != characterAction::Death) {

		// �R���{����Ȃ�A���̃R���{��Ԃ��B
		if (soardCombContinue) {
			soardCombContinue = false;
			return characterAction::Soard2_init;

		}

		// �R���{���Ȃ��Ȃ�soardCombContinue��false�ɂ��ďI���`��
		return characterAction::Soard1_end;

	}

	// ���U���R���{2
	if (nowAction == characterAction::Soard2_init && nowAction != characterAction::Death) {

		// �R���{����Ȃ�A���̃R���{��Ԃ��B
		if (soardCombContinue) {
			soardCombContinue = false;
			return characterAction::Soard3_init;

		}

		// �R���{�𑱂��Ȃ��Ȃ�I���`��
		return characterAction::Soard1_end;
	}

	// ���U���R���{3
	if (nowAction == characterAction::Soard3_init && nowAction != characterAction::Death) {

		// �R���{����Ȃ�A���̃R���{��Ԃ��B
		if (soardCombContinue) {
			soardCombContinue = false;
			return characterAction::Soard2_init;
		}

		// �R���{�𑱂��Ȃ��Ȃ�I���`��
		return characterAction::Soard1_end;
	}

	// �n���h�K���̌��������鏈��
	if (nowAction == characterAction::Hundgun_init || nowAction == characterAction::Hundgun_horizonal
		&& controller.on_Y) {
		return characterAction::Hundgun_horizonal;
	}

	// �n���h�K����ł��I���鏈��
	if (nowAction == characterAction::Hundgun_horizonal) {
		return characterAction::Hundgun_end;
	}
	// �n���h�K�������n��
	if (controller.on_Y)
		return characterAction::Hundgun_init;



	// Jump_MidAir to Fall
	if (nowAction == characterAction::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return characterAction::Fall;
	}

	// �W�����v���ɓ���ɏ�ǂ���������Fall�ɋ����ύX
	if (nowAction == characterAction::Jump_Up || nowAction == characterAction::Jump_MidAir) {
		if(collision->getCollisionedSide().head)
			return characterAction::Fall;
	}

	if (playerStatus._y_speed > 0) {
		return characterAction::Fall;
	}

	// Jump_Landing
	if (nowAction == characterAction::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return characterAction::Jump_Landing;
	}

	// �W�����v�ŕ����オ���Ă���Ƃ��ȊO�ŁA�����ɏ�ǂ��������Fall�ɋ����ύX
	if (nowAction != characterAction::Jump_Up && nowAction != characterAction::Jump_MidAir) {
		if (!collision->getCollisionedSide().bottom) {
			return characterAction::Fall;
		}
	}

	// Crouch��������́A�������n�ʂɂ��Ă��鎖
	if (controller.on_down && collision->getCollisionedSide().bottom) {
		return characterAction::Crouch;
	}

	// Brake
	if (nowAction == characterAction::Run) {
		// R
		if (playerStatus.directRight && !controller.on_right)
			return characterAction::Brake;
		// L
		if (!playerStatus.directRight && !controller.on_left)
			return characterAction::Brake;
	}

	// Jump��������́A�������n�ʂɂ��Ă��鎖
	if (controller.push_A && collision->getCollisionedSide().bottom) {
		return characterAction::Jump_Up;
	}


	/// �������n�ʂɂ��Ă����ԂŁA�W�����v�Œn�ʂ�����グ���u�ԏo�Ȃ���
	if (collision->getCollisionedSide().bottom && nowAction != characterAction::Jump_Up) {

		// Run R
		if (controller.on_B && controller.on_right) {
			playerStatus.directRight = true;
			return characterAction::Run;
		}

		// Run L
		if (controller.on_B && controller.on_left) {
			playerStatus.directRight = false;
			return characterAction::Run;
		}

		// Walk R
		if (controller.on_right) {
			playerStatus.directRight = true;
			return characterAction::Walk;
		}

		// Walk L
		if (controller.on_left) {
			playerStatus.directRight = false;
			return characterAction::Walk;
		}
	}
	// �������͂���Ȃ����Idling��Ԃɂ���B
	if (nowAction != characterAction::Jump_Up && nowAction != characterAction::Jump_MidAir) {

		return characterAction::Idle;
	}

	return nowAction;

}

/*!
@brief IsAction���X�V���āA���̃A�N�V������Animation�^�̃I�u�W�F�N�g��Ԃ��B
@date 2020/05/04/15:49
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::switchingAnimation(characterAction next, Status nowStatus)
{
	using namespace std;
	switch (next) {
	case characterAction::Brake:
		nowAction = characterAction::Brake;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Brake, nowStatus);
		break;
	case characterAction::Crouch:
		nowAction = characterAction::Crouch;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Crouch, nowStatus);
		break;
	case characterAction::Death:
		nowAction = characterAction::Death;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Death, nowStatus, 0, 0, 18, 99, true);
		break;
	case characterAction::Damage:
		nowAction = characterAction::Damage;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Damage, nowStatus);
		break;
	case characterAction::Idle:
		nowAction = characterAction::Idle;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Idle, nowStatus);
		break;
	case characterAction::Jump_Fall:
		nowAction = characterAction::Jump_Fall;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case characterAction::Jump_Landing:
		nowAction = characterAction::Jump_Landing;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case characterAction::Jump_MidAir:
		nowAction = characterAction::Jump_MidAir;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_MidAir, nowStatus, 3);
		break;
	case characterAction::Jump_Up:
		nowAction = characterAction::Jump_Up;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case characterAction::Fall:
		nowAction = characterAction::Fall;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Fall, nowStatus);
		break;
	case characterAction::Run:
		nowAction = characterAction::Run;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Run, nowStatus);
		break;
	case characterAction::Walk:
		nowAction = characterAction::Walk;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Walk, nowStatus);
		break;
	case characterAction::Hundgun_init:
		nowAction = characterAction::Hundgun_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Hundgun_init, nowStatus, 0, -3, 1);
		break;
	case characterAction::Hundgun_end:
		nowAction = characterAction::Hundgun_end;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Hundgun_end, nowStatus, 0, -3, 5);
		break;
	case characterAction::Hundgun_horizonal:
		nowAction = characterAction::Hundgun_horizonal;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Hundgun_horizonal, nowStatus, 0, -3, 4);
		break;
	case characterAction::Soard1_init:
		nowAction = characterAction::Soard1_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard1_init, nowStatus, 0, -59, 5);
		break;
	case characterAction::Soard1_end:
		nowAction = characterAction::Soard1_end;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard1_end, nowStatus, 0, -59, 3);
		break;
	case characterAction::Soard2_init:
		nowAction = characterAction::Soard2_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard2_init, nowStatus, 0, -59, 4);
		break;
	case characterAction::Soard3_init:
		nowAction = characterAction::Soard3_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard3_init, nowStatus, 0, -59, 4);
		break;
	}

	// �G���[�����A�����I������Ȃ��������荇�����A�C�h�����O��Ԃɂ���B
	return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Idle, nowStatus);
}
