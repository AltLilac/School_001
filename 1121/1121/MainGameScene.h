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
	Vec2      timeUiPos;	// �^�C�}�[�̕\���ʒu
	Point     centerPos;

	// ��������
	const int defaultTime;
	int       currentTime;

	bool isPlaying;
	bool showTimer;

public:
	MainGameScene(const InitData& init);

	void draw() const override;

	void update() override;

	int GetCurrentTime() const { return currentTime; }
};

#endif