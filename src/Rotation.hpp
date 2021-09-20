#pragma once
class Rotation {
private:
	float angle;

public:
	Rotation() : angle(0.f) {}
	Rotation(float angle) : angle(angle) {}

	float GetAngle()
	{
		return angle;
	}
	void Rotate(float angle)
	{
		this->angle += angle;
	}

	void SetAngle(float angle)
	{
		this->angle = angle;
	}
};