#include <Siv3D.hpp>
#include "MainGameScene.h"

MainGameScene::MainGameScene(const InitData& init)
	: IScene(init), 
	  defaultTime(100),						// 制限時間
	  isPlaying(true),							// 制限時間内かどうか
	  showTimer(true),							// true なら制限時間を表示
	  isDeath(false),							// プレイヤーの死亡判定
	  timeUIPos(380, 25),						// 制限時間を表示する位置
	  centerPos(400, 300),						// ゲーム進行に応じた UI を描画するための位置を取得（画面中央）
	  wallColor(137),							// 壁の色
	  showFlag(START),							// UI を表示するフラグを enum で管理
	  startArea(new Rect(0, 0, 100, 100)),		// スタートエリアを生成する位置
	  goalArea(new Rect(700, 500, 100, 100)),	// ゴールエリアを生成する位置
	  delayTime(3.0)							// 遅延処理にかける時間
{
	
}

void MainGameScene::DrawStartAndGoalArea() const {
	startArea->draw(Color(0, 206, 201));
	goalArea->draw(Color(204, 0, 0));
}

// 動く障害物の描画
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
	// ストップウォッチの経過時間が delayTime を超えたら
	if (delaySW.sF() > delayTime) {
		changeScene(U"GameOver");
	}
}

void MainGameScene::draw() const {
	Scene::SetBackground(Color(220));	// 背景色の設定

	DrawStartAndGoalArea();				// スタートエリアとゴールエリアの描画

	player.DrawPlayer();				// プレイヤーの描画

	// 壁の描画
	for (auto& block : blocks) {
		block.draw(Color(wallColor));
	}

	// ストップウォッチが開始したらタイマーを表示
	if (timeSW.isStarted() && showTimer) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos);
	}

	// 時間切れになった時の UI
	if (currentTime < 0 && !isPlaying) {
		FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos);
	}

	// StartArea 内だったら
	if (GetStartArea().contains(player.GetPlayer()) && showFlag == START) {
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos);
	}

	// GoalArea 内だったら
	if (GetGoalArea().contains(player.GetPlayer()) && showFlag == GOAL) {
		FontAsset(U"MainGameUIFont")(U"Game Clear!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Game Clear!").drawAt(centerPos);
	}

	// Player が死亡したら
	if (isDeath) {
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos);
	}
}

void MainGameScene::update() {

	DrawObstacles();

	// 制限時間内であれば player の操作を受け付ける
	if (isPlaying) {
		player.InputPlayer();
	}

	// プレイヤーがスタート地点から出たら
	if (!GetStartArea().intersects(player.GetPlayer())) {
		timeSW.start();
		showFlag = NONE;
	}

	// プレイヤーがゴール地点に触れたら
	if (GetGoalArea().intersects(player.GetPlayer())) {
		showFlag = GOAL;

		// ゴール地点に入ったら
		if (GetGoalArea().contains(player.GetPlayer()) && showFlag == GOAL) {
			timeSW.pause();
			isPlaying = false;

			delaySW.start();
			// ストップウォッチの経過時間が delayTime を超えたら
			if (delaySW.sF() > delayTime) {
				changeScene(U"Result");
			}
		}
	}

	// ブロックの当たり判定を用意
	for (auto& block : blocks) {

		if (block.intersects(player.GetPlayer())) {
			isPlaying = false;
			showTimer = false;
			isDeath = true;

			timeSW.pause();

			delaySW.start();
			// ストップウォッチの経過時間が delayTime を超えたら
			if (delaySW.sF() > delayTime) {
				changeScene(U"GameOver");
			}
		}
	}

	// 制限時間の初期値から、stopwatch の経過時間を減算
	currentTime = defaultTime - timeSW.s64();

	// 制限時間が 0 になったら
	if (currentTime < 0) {
		isPlaying = false;

		timeSW.pause();

		delaySW.start();
		// ストップウォッチの経過時間が delayTime を超えたら
		if (delaySW.sF() > delayTime) {
			changeScene(U"GameOver");
		}
	}

	// stopwatch が pause であれば制限時間 UI を消去
	if (timeSW.isPaused()) {
		showTimer = false;
	}
}