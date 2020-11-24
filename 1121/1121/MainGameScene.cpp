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

	// 壁の描画
	for (auto& block : blocks) {
		block.draw(Color(wallColor));
	}

	// ストップウォッチが開始したらタイマーを表示
	if (stopwatch.isStarted() && showTimer) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUIPos);

		// 時間切れになった時の UI
		if (currentTime <= 0) {
			FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
			FontAsset(U"MainGameUIFont")(U"Time Over!").drawAt(centerPos);
		}
	}

	// StartArea 内だったら
	if (GetStartArea().contains(player.GetPlayer()) && showFlag == START) {
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"Game Start!").drawAt(centerPos);
	}

	// Player が死亡したら
	if (stopwatch.isPaused() && isDeath) {
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUIFont")(U"You Died!").drawAt(centerPos);
	}
}

void MainGameScene::update() {

	// 制限時間内であれば player の操作を受け付ける
	if (isPlaying) {
		player.InputPlayer();
	}

	if (!GetStartArea().intersects(player.GetPlayer())) {
		stopwatch.start();
		showFlag = NONE;
	}

	// プレイヤーがスタート地点から出たら
	if (!GetStartArea().intersects(player.GetPlayer())) {
		stopwatch.start();
		showFlag = NONE;
	}

	// プレイヤーがゴール地点に触れたら
	if (GetGoalArea().intersects(player.GetPlayer())) {
		showFlag = GOAL;

		// ゴール地点に入ったら
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
			// プレイヤーが壁に当たったら死亡フラグを true にする
			isDeath = block.intersects(player.GetPlayer());
		}
		//// 死亡処理
		//if (isDeath) {
		//	stopwatch.pause();
		//	// 死亡時のUI
		//	FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		//	FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos);
		//	
		//	System::Sleep(3000);

		//	changeScene(U"Result");
		//	break;
		//}
	}

	// 制限時間の初期値から、stopwatch の経過時間を減算
	currentTime = defaultTime - stopwatch.s64();

	// プレイヤーが壁に当たったら
	if (isDeath) {
		stopwatch.pause();
		System::Sleep(3000);  // 3 秒間スレッドの実行を停止

		changeScene(U"Result");
	}

	// 制限時間が 0 になったら
	if (currentTime < 0) {
		isPlaying = false;

		stopwatch.pause();
		System::Sleep(3000);

		changeScene(U"Result");
	}

	// stopwatch が pause であれば制限時間 UI を消去
	if (stopwatch.isPaused()) {
		showTimer = false;
	}
}