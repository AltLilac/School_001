#define SHOW 1
#if SHOW == 1

#include <Siv3D.hpp>
#include "TitleScene.h"
#include "MainGameScene.h"
#include "ResultScene.h"

using App = SceneManager<String>;

void Main() {
	FontAsset::Register(U"TitleFont", 60, Typeface::Medium);
	FontAsset::Register(U"TimeLimitFont", 45, Typeface::Medium);
	FontAsset::Register(U"ResultFont", 45, Typeface::Medium);

	App manager;

	manager.add<TitleScene>(U"Title");
	manager.add<MainGameScene>(U"MainGame");
	manager.add<ResultScene>(U"Result");
	
	while (System::Update()) {

		if (!manager.update()) {
			break;
		}
	}
}

#endif