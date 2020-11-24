#include <Siv3D.hpp>
#include "MainGameScene.h"

MainGameScene::MainGameScene(const InitData& init)
	: IScene(init), 
	  defaultTime(100), isPlaying(true), showTimer(true), isDeath(false), 
	  timeUIPos(380, 35), centerPos(400, 300), wallColor(137), showFlag(START),
	  startArea(new Rect(0, 0, 100, 100)), goalArea(new Rect(700, 500, 100, 100)) {
	
}

void MainGameScene::DrawStartAndGoalArea() const {
	startArea->draw(Color(0, 206, 201));
	goalArea->draw(Color(204, 0, 0));
}

void MainGameScene::draw() const {
	Scene::SetBackground(Color(230));

	debug.DrawCoordinate();

	DrawStartAndGoalArea();

	player.DrawPlayer();

	// �ǂ̕`��
	for (auto& block : blocks) {
		block.draw(Color(wallColor));
	}

	// �X�g�b�v�E�H�b�`���J�n������^�C�}�[��\��
	if (stopwatch.isStarted() && showTimer) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos);

		// ���Ԑ؂�ɂȂ������� UI
		if (currentTime <= 0) {
			FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
			FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos);
		}
	}

	// StartArea ����������
	if (GetStartArea().contains(player.GetPlayer()) && showFlag == START) {
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

	// �������ԓ��ł���� player �̑�����󂯕t����
	if (isPlaying) {
		player.InputPlayer();
	}

	if (!GetStartArea().intersects(player.GetPlayer())) {
		stopwatch.start();
		showFlag = NONE;
	}

	// �v���C���[���X�^�[�g�n�_����o����
	if (!GetStartArea().intersects(player.GetPlayer())) {
		stopwatch.start();
		showFlag = NONE;
	}

	// �v���C���[���S�[���n�_�ɐG�ꂽ��
	if (GetGoalArea().intersects(player.GetPlayer())) {
		showFlag = GOAL;

		// �S�[���n�_�ɓ�������
		if (GetGoalArea().contains(player.GetPlayer()) && showFlag == GOAL) {
			stopwatch.pause();
			isPlaying == false;

			FontAsset(U"MainGameUIFont")(U"Game Clear!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
			FontAsset(U"MainGameUIFont")(U"Game Clear!").drawAt(centerPos);

			System::Sleep(3000);
			changeScene(U"Result");
		}
	}

	for (auto& block : blocks) {
		if (!isDeath) {
			// �v���C���[���ǂɓ��������玀�S�t���O�� true �ɂ���
			isDeath = block.intersects(player.GetPlayer());
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