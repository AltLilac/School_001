#include <Siv3D.hpp>
#include "MainGameScene.h"

MainGameScene::MainGameScene(const InitData& init)
	: IScene(init), 
	  defaultTime(100),						// ��������
	  isPlaying(true),							// �������ԓ����ǂ���
	  showTimer(true),							// true �Ȃ琧�����Ԃ�\��
	  isDeath(false),							// �v���C���[�̎��S����
	  timeUIPos(380, 25),						// �������Ԃ�\������ʒu
	  centerPos(400, 300),						// �Q�[���i�s�ɉ����� UI ��`�悷�邽�߂̈ʒu���擾�i��ʒ����j
	  wallColor(137),							// �ǂ̐F
	  showFlag(START),							// UI ��\������t���O�� enum �ŊǗ�
	  startArea(new Rect(0, 0, 100, 100)),		// �X�^�[�g�G���A�𐶐�����ʒu
	  goalArea(new Rect(700, 500, 100, 100)),	// �S�[���G���A�𐶐�����ʒu
	  delayTime(3.0)							// �x�������ɂ����鎞��
{
	
}

void MainGameScene::DrawStartAndGoalArea() const {
	startArea->draw(Color(0, 206, 201));
	goalArea->draw(Color(204, 0, 0));
}

// ������Q���̕`��
void MainGameScene::DrawObstacles() {
	double x1 = 450 * Periodic::Triangle0_1(5s);
	double x2 = 650 * Periodic::Triangle0_1(9s);
	double x3 = 650 * Periodic::Triangle0_1(12s);
	double x4 = 450 * Periodic::Triangle0_1(7s);
	double x5 = 450 * Periodic::Triangle0_1(9s);
	double x6 = 450 * Periodic::Triangle0_1(11s);

	double y1 = -50 * Periodic::Triangle0_1(12s);
	double y2 = 450 * Periodic::Triangle0_1(10s);
	double y3 = 450 * Periodic::Triangle0_1(20s);

	Rect* rect1 = new Rect(x1, 200, 50, 50);
	Rect* rect2 = new Rect(x2, 500, 50, 50);
	Rect* rect3 = new Rect(200, y1, 600, 100);
	Rect* rect4 = new Rect(600, y2, 50, 50);
	Rect* rect5 = new Rect(650, y3, 50, 50);
	Rect* rect6 = new Rect(x4, 250, 50, 50);
	Rect* rect7 = new Rect(x5, 300, 50, 50);
	Rect* rect8 = new Rect(x6, 350, 50, 50);
	Rect* rect9 = new Rect(x1, 400, 50, 50);
	Rect* rect10 = new Rect(x5, 450, 50, 50);

	rect1->draw(Color(wallColor));
	rect2->draw(Color(wallColor));
	rect3->draw(Color(wallColor));
	rect4->draw(Color(wallColor));
	rect5->draw(Color(wallColor));
	rect6->draw(Color(wallColor));
	rect7->draw(Color(wallColor));
	rect8->draw(Color(wallColor));
	rect9->draw(Color(wallColor));
	rect10->draw(Color(wallColor));

	if (rect1->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect2->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect3->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect4->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect5->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect6->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect7->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect8->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect9->intersects(player.GetPlayer())) {
		GameOverProcess();
	}

	if (rect10->intersects(player.GetPlayer())) {
		GameOverProcess();
	}
}

void MainGameScene::GameOverProcess() {
	isPlaying = false;
	showTimer = false;
	isDeath = true;

	timeSW.pause();

	delaySW.start();
	// �X�g�b�v�E�H�b�`�̌o�ߎ��Ԃ� delayTime �𒴂�����
	if (delaySW.sF() > delayTime) {
		changeScene(U"GameOver");
	}
}

void MainGameScene::draw() const {
	Scene::SetBackground(Color(220));	// �w�i�F�̐ݒ�

	DrawStartAndGoalArea();				// �X�^�[�g�G���A�ƃS�[���G���A�̕`��

	player.DrawPlayer();				// �v���C���[�̕`��

	// �ǂ̕`��
	for (auto& block : blocks) {
		block.draw(Color(wallColor));
	}

	// �X�g�b�v�E�H�b�`���J�n������^�C�}�[��\��
	if (timeSW.isStarted() && showTimer) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos);
	}

	// ���Ԑ؂�ɂȂ������� UI
	if (currentTime < 0 && !isPlaying) {
		FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos);
	}

	// StartArea ����������
	if (GetStartArea().contains(player.GetPlayer()) && showFlag == START) {
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos);
	}

	// GoalArea ����������
	if (GetGoalArea().contains(player.GetPlayer()) && showFlag == GOAL) {
		FontAsset(U"MainGameUIFont")(U"Game Clear!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Game Clear!").drawAt(centerPos);
	}

	// Player �����S������
	if (isDeath) {
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos);
	}
}

void MainGameScene::update() {

	DrawObstacles();

	// �������ԓ��ł���� player �̑�����󂯕t����
	if (isPlaying) {
		player.InputPlayer();
	}

	// �v���C���[���X�^�[�g�n�_����o����
	if (!GetStartArea().intersects(player.GetPlayer())) {
		timeSW.start();
		showFlag = NONE;
	}

	// �v���C���[���S�[���n�_�ɐG�ꂽ��
	if (GetGoalArea().intersects(player.GetPlayer())) {
		showFlag = GOAL;

		// �S�[���n�_�ɓ�������
		if (GetGoalArea().contains(player.GetPlayer()) && showFlag == GOAL) {
			timeSW.pause();
			isPlaying = false;

			delaySW.start();
			// �X�g�b�v�E�H�b�`�̌o�ߎ��Ԃ� delayTime �𒴂�����
			if (delaySW.sF() > delayTime) {
				changeScene(U"Result");
			}
		}
	}

	// �u���b�N�̓����蔻���p��
	for (auto& block : blocks) {

		if (block.intersects(player.GetPlayer())) {
			isPlaying = false;
			showTimer = false;
			isDeath = true;

			timeSW.pause();

			delaySW.start();
			// �X�g�b�v�E�H�b�`�̌o�ߎ��Ԃ� delayTime �𒴂�����
			if (delaySW.sF() > delayTime) {
				changeScene(U"GameOver");
			}
		}
	}

	// �������Ԃ̏����l����Astopwatch �̌o�ߎ��Ԃ����Z
	currentTime = defaultTime - timeSW.s64();

	// �������Ԃ� 0 �ɂȂ�����
	if (currentTime < 0) {
		isPlaying = false;

		timeSW.pause();

		delaySW.start();
		// �X�g�b�v�E�H�b�`�̌o�ߎ��Ԃ� delayTime �𒴂�����
		if (delaySW.sF() > delayTime) {
			changeScene(U"GameOver");
		}
	}

	// stopwatch �� pause �ł���ΐ������� UI ������
	if (timeSW.isPaused()) {
		showTimer = false;
	}
}