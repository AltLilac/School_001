#ifndef ___MAINGAMESCENE
#define ___MAINGAMESCENE

#include <Siv3D.hpp>
#include "Debug.h"
#include "Player.h"

class MainGameScene : public SceneManager<String>::Scene {
private:
	Debug       debug;

	enum ShowFlag { START, GOAL, NONE };  
	ShowFlag    showFlag;		// UI ��\�����邽�߂̃t���O

	Player      player;
	Stopwatch   timeSW;			// �������ԗp�̃X�g�b�v�E�H�b�`
	Stopwatch   delaySW;		// �x�������p�̃X�g�b�v�E�H�b�`
	Vec2        timeUIPos;		// �^�C�}�[�̕\���ʒu
	Point       centerPos;		// �V�[���̒��S���W

	Rect*       startArea;		// �X�^�[�g�n�_
	Rect*       goalArea;		// �S�[���n�_

	const int   defaultTime;	// �������Ԃ̏����ݒ�
	int         currentTime;	// ���݂̐�������

	double		delayTime;		// �x�������ɂ����鎞��

	bool        isPlaying;		// �������ԓ����ǂ���
	bool        showTimer;		// �������Ԃ�\�����邽�߂̃t���O
	bool        isDeath;		// �v���C���[�̎��S����

	int         wallColor;		// �ǂ̐F

	// �ǂ̕`��
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

		// ��������}�b�v�O�ɍs����s��̏C��
		Rect(-10, -10, 800,  10),	// �㑤
		Rect(-10,   0,  10, 600),	// ����
		Rect(800,   0,  10, 600),	// �E��
		Rect(  0, 600, 800,  10),	// ����
	};

public:
	MainGameScene(const InitData& init);

	void draw() const override;
	void update() override;

	void DrawStartAndGoalArea() const;					// �X�^�[�g�n�_�ƃS�[���n�_�̕`��
	void DrawObstacles();								// ������Q���̕`��

	// �X�^�[�g�G���A�ƃS�[���G���A�̔�����擾
	Rect GetStartArea() const { return *startArea; }
	Rect GetGoalArea()  const { return *goalArea; }

	void GameOverProcess();								// �Q�[���I�[�o�[���̏���
};

#endif