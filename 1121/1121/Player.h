#ifndef ___PLAYER
#define ___PLAYER

class Player {
private:
	const int    posX;			// �����X�|�[��X���W
	const int    posY;			// �����X�|�[��Y���W

	const int    playerWidth;   // �v���C���[�̉���
	const int    playerHeight;  // �v���C���[�̏c��

	const double delta;			// �v���C���[�̍��W�X�V�p

	Vec2         playerPos;		// �v���C���[�̈ʒu

	Rect*        playerEntity;  // �v���C���[�{��

public:
	Player();

	void DrawPlayer() const;

	void InputPlayer();

	Rect GetPlayer() const { return *playerEntity; }
};

#endif