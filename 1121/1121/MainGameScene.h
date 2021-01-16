#ifndef ___MAINGAMESCENE
#define ___MAINGAMESCENE

#include <Siv3D.hpp>
#include "Debug.h"
#include "Player.h"

class MainGameScene : public SceneManager<String>::Scene {
private:
	Debug       debug;

	enum ShowFlag { START, GOAL, NONE };  
	ShowFlag    showFlag;		// UI を表示するためのフラグ

	Player      player;
	Stopwatch   timeSW;			// 制限時間用のストップウォッチ
	Stopwatch   delaySW;		// 遅延処理用のストップウォッチ
	Vec2        timeUIPos;		// タイマーの表示位置
	Point       centerPos;		// シーンの中心座標

	Rect*       startArea;		// スタート地点
	Rect*       goalArea;		// ゴール地点

	const int   defaultTime;	// 制限時間の初期設定
	int         currentTime;	// 現在の制限時間

	double		delayTime;		// 遅延処理にかける時間

	bool        isPlaying;		// 制限時間内かどうか
	bool        showTimer;		// 制限時間を表示するためのフラグ
	bool        isDeath;		// プレイヤーの死亡判定

	int         wallColor;		// 壁の色

	// 壁の描画
	Array<Rect> blocks = {
		Rect(100,   0, 100, 500),
		Rect(200,   0, 300,  55),
		Rect(300, 100, 100, 500),
		Rect(500,   0, 100, 500),
		Rect(700, 100,  35, 400),
		Rect(735, 100,  25,  50),
		Rect(700, 200,  35, 100),
		Rect(775, 200,  25,  50),
		Rect(735, 300,  25,  50),
		Rect(775, 400,  25, 100),
		Rect(700, 500,   5, 100),

		// ここからマップ外に行ける不具合の修正
		Rect(-10, -10, 800,  10),	// 上側
		Rect(-10,   0,  10, 600),	// 左側
		Rect(800,   0,  10, 600),	// 右側
		Rect(  0, 600, 800,  10),	// 下側
	};

public:
	MainGameScene(const InitData& init);

	void draw() const override;
	void update() override;

	void DrawStartAndGoalArea() const;					// スタート地点とゴール地点の描画
	void DrawObstacles();								// 動く障害物の描画

	// スタートエリアとゴールエリアの判定を取得
	Rect GetStartArea() const { return *startArea; }
	Rect GetGoalArea()  const { return *goalArea; }

	void GameOverProcess();								// ゲームオーバー時の処理
};

#endif