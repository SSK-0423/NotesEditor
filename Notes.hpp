#pragma once
#include "GameObject.hpp"
class Notes : public GameObject{
protected:
	float timing; // ����^�C�~���O�����ߐ��̖��[���W / �Ȃ̒��� * �m�[�c�̍��W
	int lane;
public:
	//virtual void Put() noexcept {}
	float GetTiming() noexcept;
	int GetLane() noexcept;
	virtual void Draw() noexcept;
	virtual void Update() noexcept;
};
