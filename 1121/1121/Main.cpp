#define SHOW 0
#if SHOW == 1

#include <Siv3D.hpp>

namespace /* Variable */ {
	// Set color
	const int wallColor = 137;

	constexpr Rect startArea(0, 0, 100, 100);
	constexpr Rect goalArea(700, 500, 100, 100);

	// Timelimit
	const int defaultTime = 10;
}

void DrawMainLevel() {
	// Draw start and goal area
	startArea.draw(Color(0, 206, 201));
	goalArea.draw(Color(204, 0, 0));

	// Draw walls
	Rect(100, 0, 100, 300).draw(Color(wallColor));
	Rect(300, 100, 100, 500).draw(Color(wallColor));
	Rect(500, 0, 100, 500).draw(Color(wallColor));
	Rect(700, 100, 35, 400).draw(Color(wallColor));
	Rect(735, 100, 25, 50).draw(Color(wallColor));
	Rect(700, 200, 35, 100).draw(Color(wallColor));
	Rect(775, 200, 25, 50).draw(Color(wallColor));
	Rect(735, 300, 25, 50).draw(Color(wallColor));
	Rect(775, 400, 25, 100).draw(Color(wallColor));
	Rect(700, 500, 5, 100).draw(Color(wallColor));
}

void Main() {
	const     Font font(40, Typeface::Medium);
	constexpr Vec2 timeUIPos(380, 35);

	// 制限時間用ストップウォッチ
	Stopwatch stopwatch;

	// UI massages show flag
	enum ShowFlag {
		START,
		GOAL,
		NONE,
	};

	ShowFlag showFlag = START;

	bool isPlaying = true;

	while (System::Update()) {
		DrawMainLevel();

		/* --- Timelimit --- */

		// スタート地点から出たらカウントダウン開始
		if (!startArea.contains(playerEntity)) {
			stopwatch.start();
		}

		// 時間切れ
		if (currentTime <= 0) {
			stopwatch.pause();
			isPlaying = false;
			font(U"{}{}"_fmt(U"Time ", U"over!")).draw(Arg::center(Scene::Center()));
		}

		////////////////////////////////////////////////////////////////////////////


		/* --- UI massages --- */


		if (startArea.contains(playerEntity) && showFlag == START) {
			font(U"{}{}"_fmt(U"Game ", U"start!")).draw(Arg::center(Scene::Center()));
		}

		if (!startArea.contains(playerEntity)) {
			showFlag = NONE;
		}

		if (goalArea.intersects(playerEntity)) {
			showFlag = GOAL;

			if (goalArea.contains(playerEntity) && showFlag == GOAL) {
				stopwatch.pause();
				isPlaying = false;
				font(U"{}{}"_fmt(U"Game ", U"clear!")).draw(Arg::center(Scene::Center()));
				// Open to result level
			}
		}

		////////////////////////////////////////////////////////////////////////////
	}
}

#endif