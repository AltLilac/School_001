#include <Siv3D.hpp>
#include "Debug.h"

void Debug::DrawCoordinate() const {
	ClearPrint();

	Print << U"X: " << Cursor::Pos().x;
	Print << U"Y: " << Cursor::Pos().y;
}