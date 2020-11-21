#include <Siv3D.hpp>
#include "MainGameScene.h"

MainGameScene::MainGameScene(const InitData& init)
	: IScene(init), defaultTime(10), isPlaying(true), showTimer(true), isDeath(false), timeUiPos(380, 35), centerPos(400, 300), wallColor(137) {
	
}

void MainGameScene::draw() const {
	Scene::SetBackground(Color(230));

	debug.DrawCoordinate();

	// �X�g�b�v�E�H�b�`���J�n������^�C�}�[��\��
	if (stopwatch.isStarted() && showTimer) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos);

		// ���Ԑ؂�ɂȂ�������UI
		if (currentTime <= 0) {
			FontAsset(U"MainGameUiFont")(U"Time Over!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
			FontAsset(U"MainGameUiFont")(U"Time Over!").drawAt(centerPos);
		}
	}
}

void MainGameScene::update() {
	// �X�^�[�g�n�_
	Rect(0, 0, 100, 100).draw(Color(0, 206, 201));
	// �S�[���n�_
	Rect(700, 500, 100, 100).draw(Color(204, 0, 0));

	player.DrawPlayer();

	if (isPlaying) {
		stopwatch.start();
		player.InputPlayer();
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

	currentTime = defaultTime - stopwatch.s64();

	// �v���C���[���ǂɓ���������
	if (isDeath) {
		stopwatch.pause();
		// ���S����UI
		FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos);

		System::Sleep(3000);

		changeScene(U"Result");
	}

	// �������Ԃ�0�ɂȂ�����
	if (currentTime < 0) {
		currentTime = currentTime;
		isPlaying = false;

		stopwatch.pause();
		System::Sleep(3000);

		changeScene(U"Result");
	}

	if (stopwatch.isPaused()) {
		showTimer = false;
	}
}