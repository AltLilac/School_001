#ifndef ___PLAYER
#define ___PLAYER

class Player {
private:
	// スポーン位置
	const int posX;
	const int posY;

	// プレイヤー位置
	Vec2 playerPos;

	// プレイヤーサイズ
	const int playerWidth;
	const int playerHeight;

	// プレイヤー速度
	const double delta;

public:
	Player();

	Rect DrawPlayer() const;

	void InputPlayer();
};

#endif