#include <Siv3D.hpp>
#include "MainGameScene.h"

MainGameScene::MainGameScene(const InitData& init)
	: IScene(init), defaultTime(10), isPlaying(true), showTimer(true), isDeath(false), timeUiPos(380, 35), centerPos(400, 300), wallColor(137) {
	
}

void MainGameScene::draw() const {
	Scene::SetBackground(Color(230));

	debug.DrawCoordinate();

	// ストップウォッチが開始したらタイマーを表示
	if (stopwatch.isStarted() && showTimer) {
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"TimeLimitFont")(U"{}{}{}"_fmt(U"Time", U" : ", currentTime)).drawAt(timeUiPos);

		// 時間切れになった時のUI
		if (currentTime <= 0) {
			FontAsset(U"MainGameUiFont")(U"Time Over!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
			FontAsset(U"MainGameUiFont")(U"Time Over!").drawAt(centerPos);
		}
	}
}

void MainGameScene::update() {
	// スタート地点
	Rect(0, 0, 100, 100).draw(Color(0, 206, 201));
	// ゴール地点
	Rect(700, 500, 100, 100).draw(Color(204, 0, 0));

	player.DrawPlayer();

	if (isPlaying) {
		stopwatch.start();
		player.InputPlayer();
	}

	for (auto& block : blocks) {
		if (!isDeath) {
			// プレイヤーが壁に当たったら死亡フラグを true にする
			isDeath = block.intersects(player.DrawPlayer());
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

		block.draw(Color(wallColor));
	}

	currentTime = defaultTime - stopwatch.s64();

	// プレイヤーが壁に当たったら
	if (isDeath) {
		stopwatch.pause();
		// 死亡時のUI
		FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos.movedBy(2, 2), ColorF(0.0, 0.7));
		FontAsset(U"MainGameUiFont")(U"You Died!").drawAt(centerPos);

		System::Sleep(3000);

		changeScene(U"Result");
	}

	// 制限時間が0になったら
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