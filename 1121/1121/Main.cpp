#define SHOW 0
#if SHOW == 1

#include <Siv3D.hpp>

namespace /* Variable */ {
	// Set color
	const int wallColor = 137;

	// Timelimit
	const int defaultTime = 10;
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