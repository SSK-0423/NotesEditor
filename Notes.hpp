#pragma once
#include "GameObject.hpp"
class Notes : public GameObject{
private:
	float timing;
	int lane;
public:
	//virtual void Put() noexcept {}
	float GetTiming() noexcept;
	int GetLane() noexcept;
	virtual void Draw() noexcept;
	virtual void Update() noexcept;
};
