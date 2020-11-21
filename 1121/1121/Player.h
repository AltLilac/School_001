#ifndef ___PLAYER
#define ___PLAYER

class Player {
private:
	// �X�|�[���ʒu
	const int posX;
	const int posY;

	// �v���C���[�ʒu
	Vec2 playerPos;

	// �v���C���[�T�C�Y
	const int playerWidth;
	const int playerHeight;

	// �v���C���[���x
	const double delta;

public:
	Player();

	Rect DrawPlayer() const;

	void InputPlayer();
};

#endif