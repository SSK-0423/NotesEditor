#pragma once
#include "KeyInput.hpp"
//操作可能なオブジェクトのインターフェース
class PlayableObj {
private:
	//キーボード、マウス操作の管理
	virtual void Controll() = 0;
	//移動限界
	virtual void PosLimit() = 0;
};