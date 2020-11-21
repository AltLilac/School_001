#include <Siv3D.hpp>
#include "MainGameScene.h"

MainGameScene::MainGameScene(const InitData& init) : IScene(init), defaultTime(10), isPlaying(true), timeUiPos(380, 35) {
	
}

void MainGameScene::draw() const {
	Scene::SetBackground(Color(230));

	debug.DrawCoordinate();

	/*
	// �X�^�[�g�n�_�̕`��
	Rect(0, 0, 100, 100).draw(Color(0, 206, 201));
	// �S�[���n�_�̕`��
	Rect(700, 500, 100, 100).draw(Color(204, 0, 0));
	*/

	player.DrawPlayer();

	// �X�g�b�v�E�H�b�`���J�n������^�C�}�[��\��
	if (stopwatch.isStarted()) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos);
	}
}

void MainGameScene::update() {

	if (isPlaying) {
		stopwatch.start();
		player.InputPlayer();
	}

	currentTime = defaultTime - stopwatch.s64();

	// �������Ԃ�0�ɂȂ�����
	if (currentTime <= 0) {
		currentTime = currentTime;
		stopwatch.pause();
		isPlaying = false;
		changeScene(U"Result");
	}
}