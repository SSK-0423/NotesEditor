#pragma once
#include "Vector2D.hpp"
#include "KeyInput.hpp"
//操作可能なオブジェクトのインターフェース
class PlayableObj {
protected:
	//オブジェクトの移動限界
	Vector2D<float> minLimitPos;	//下限(左上)
	Vector2D<float> maxLimitPos;	//上限(右上)
private:
	//キーボード、マウス操作の管理
	virtual void Controll() = 0;
	//移動限界
	virtual void PosLimit() = 0;
public:
	PlayableObj() {
		maxLimitPos.x = 0;
		maxLimitPos.y = 0;
		minLimitPos.x = 0;
		minLimitPos.y = 0;
	}
};