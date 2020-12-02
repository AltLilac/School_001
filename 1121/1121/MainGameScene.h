#ifndef ___MAINGAMESCENE
#define ___MAINGAMESCENE

#include <Siv3D.hpp>
#include "Debug.h"
#include "Player.h"

class MainGameScene : public SceneManager<String>::Scene {
private:
	enum ShowFlag { START, GOAL, NONE };  
	ShowFlag    showFlag;	  // UI ��\�����邽�߂̃t���O

	Debug       debug;
	Player      player;
	Stopwatch   stopwatch;
	Vec2        timeUIPos;	  // �^�C�}�[�̕\���ʒu
	Point       centerPos;	  // �V�[���̒��S���W

	Rect*       startArea;	  // �X�^�[�g�n�_
	Rect*       goalArea;	  // �S�[���n�_

	const Font* font;		  // UI�p�t�H���g

	const int   defaultTime;  // �������Ԃ̏����ݒ�
	int         currentTime;  // ���݂̐�������

	bool        isPlaying;	  // �������ԓ����ǂ���
	bool        showTimer;	  // �������Ԃ�\�����邽�߂̃t���O
	bool        isDeath;	  // �v���C���[�̎��S����

	int         wallColor;	  // �ǂ̐F

	// �ǂ̕`��
	Array<Rect> blocks = {
		Rect(100,   0, 100, 300),
		Rect(300, 100, 100, 500),
		Rect(500,   0, 100, 500),
		Rect(700, 100,  35, 400),
		Rect(735, 100,  25, 50),
		Rect(700, 200,  35, 100),
		Rect(775, 200,  25, 50),
		Rect(735, 300,  25, 50),
		Rect(775, 400,  25, 100),
		Rect(700, 500,   5, 100),
	};

	// �X�^�[�g�E�S�[���n�_

public:
	MainGameScene(const InitData& init);

	void draw() const override;
	void update() override;

	void DrawStartAndGoalArea() const;

	Rect GetStartArea() const { return *startArea; }
	Rect GetGoalArea()  const { return *goalArea; }
};

#endif