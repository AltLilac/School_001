#include <Siv3D.hpp>
#include "MainGameScene.h"

MainGameScene::MainGameScene(const InitData& init)
	: IScene(init), defaultTime(100), isPlaying(true), showTimer(true), isDeath(false), timeUiPos(380, 35), centerPos(400, 300), wallColor(137) {
	
}

Rect MainGameScene::GetStartArea() const {
	constexpr Rect startArea(0, 0, 100, 100);
	startArea.draw(Color(0, 206, 201));

	return startArea;
}

Rect MainGameScene::GetGoalArea() const {
	constexpr Rect goalArea(700, 500, 100, 100);
	goalArea.draw(Color(204, 0, 0));

	return goalArea;
}

void MainGameScene::draw() const {
	Scene::SetBackground(Color(230));

	debug.DrawCoordinate();

	player.DrawPlayer();

	// �X�g�b�v�E�H�b�`���J�n������^�C�}�[��\��
	if (stopwatch.isStarted() && showTimer) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos);

		// ���Ԑ؂�ɂȂ������� UI
		if (currentTime <= 0) {
			FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
			FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos);
		}
	}

	// StartArea ����������
	if (GetStartArea().contains(player.DrawPlayer()) && showFlag == START) {
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos);
	}

	// Player �����S������
	if (stopwatch.isPaused() && isDeath) {
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos);
	}
}

void MainGameScene::update() {
	// �X�^�[�g�n�_
	Rect(0, 0, 100, 100).draw(Color(0, 206, 201));
	// �S�[���n�_
	Rect(700, 500, 100, 100).draw(Color(204, 0, 0));

	// �������ԓ��ł���� player �̑�����󂯕t����
	if (isPlaying) {
		player.InputPlayer();
	}

	// �v���C���[���X�^�[�g�n�_����o����
	if (!GetStartArea().intersects(player.DrawPlayer())) {
		stopwatch.start();
		showFlag = NONE;
	}

	if (GetGoalArea().intersects(player.DrawPlayer())) {
		showFlag = GOAL;
	}

	//�@�v���C���[���S�[���n�_�ɓ�������
	if (GetGoalArea().contains(player.DrawPlayer()) && showFlag == GOAL) {
		stopwatch.pause();
		isPlaying == false;
	}

	for (auto& block : blocks) {
		if (!isDeath) {
			// �v���C���[���ǂɓ��������玀�S�t���O�� true �ɂ���
			isDeath = block.intersects(player.DrawPlayer());
		}
		//// ���S����
		//if (isDeath) {
		//	stopwatch.pause();
		//	// ���S����UI
		//	FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		//	FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos);
		//	
		//	System::Sleep(3000);

		//	changeScene(U"Result");
		//	break;
		//}

		block.draw(Color(wallColor));
	}

	// �������Ԃ̏����l����Astopwatch �̌o�ߎ��Ԃ����Z
	currentTime = defaultTime - stopwatch.s64();

	// �v���C���[���ǂɓ���������
	if (isDeath) {
		stopwatch.pause();
		System::Sleep(3000);  // 3 �b�ԃX���b�h�̎��s���~

		changeScene(U"Result");
	}

	// �������Ԃ� 0 �ɂȂ�����
	if (currentTime < 0) {
		isPlaying = false;

		stopwatch.pause();
		System::Sleep(3000);

		changeScene(U"Result");
	}

	// stopwatch �� pause �ł���ΐ������� UI ������
	if (stopwatch.isPaused()) {
		showTimer = false;
	}
}