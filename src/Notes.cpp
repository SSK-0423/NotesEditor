#include "Notes.hpp"
#include "DxLib.h"
//クラス変数実体化
float Notes::GetTiming() noexcept {
	return timing;
}

int Notes::GetLane() noexcept {
	return lane;
}