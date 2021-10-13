#pragma once
#include "Vector2.hpp"

//操作可能なオブジェクトのインターフェース
class IPlayable {
protected:
	//オブジェクトの移動限界
	Vector2<float> minLimitPos;	//下限(左上)
	Vector2<float> maxLimitPos;	//上限(右上)
private:
	//キーボード、マウス操作の管理
	virtual void Controll() = 0;
	//移動限界
	virtual void LimitPos() = 0;
public:
	// キー入力受付
	// virtual void Input() = 0;
};