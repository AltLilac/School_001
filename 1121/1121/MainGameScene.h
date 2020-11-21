#ifndef ___MAINGAMESCENE
#define ___MAINGAMESCENE

#include <Siv3D.hpp>
#include "Debug.h"
#include "Player.h"

class MainGameScene : public SceneManager<String>::Scene {
private:
	Debug     debug;
	Player    player;
	Stopwatch stopwatch;
	Vec2      timeUiPos;	// タイマーの表示位置
	Point     centerPos;	// シーンの中心座標

	const int defaultTime;  // 制限時間の初期設定
	int       currentTime;  // 現在の制限時間

	bool isPlaying;			// 制限時間内かどうか
	bool showTimer;			// 制限時間を表示するためのフラグ
	bool isDeath;			// プレイヤーの死亡判定

	int wallColor;			// 壁の色

	// 壁の描画
	Array<Rect> blocks = {
		Rect(100, 0, 100, 300),
		Rect(300, 100, 100, 500),
		Rect(500, 0, 100, 500),
		Rect(700, 100, 35, 400),
		Rect(735, 100, 25, 50),
		Rect(700, 200, 35, 100),
		Rect(775, 200, 25, 50),
		Rect(735, 300, 25, 50),
		Rect(775, 400, 25, 100),
		Rect(700, 500, 5, 100),
	};

public:
	MainGameScene(const InitData& init);

	void draw() const override;

	void update() override;

	int GetCurrentTime() const { return currentTime; }
};

#endif