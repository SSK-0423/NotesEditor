#pragma once
class Component {
private:
public:
	Component() {};
	~Component() {};
	virtual void Update() = 0;
	virtual void Draw() {};
};