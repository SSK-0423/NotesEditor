#pragma once
#include "GameObject.hpp"
class Notes : public GameObject{
protected:
	float timing; // 判定タイミング＝小節線の末端座標 / 曲の長さ * ノーツの座標
	int lane;
public:
	//virtual void Put() noexcept {}
	float GetTiming() noexcept;
	int GetLane() noexcept;
	virtual void Draw() noexcept;
	virtual void Update() noexcept;
};
