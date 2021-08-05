#pragma once
#include "Game.hpp"

class Sprite : public Component {
private:
	GameObject* _parent;
	Image _image;
	Size2D<int> _size;

public:
	Sprite(GameObject* parent) 
	{
		_parent = parent;
	}
	~Sprite() {}
	void SetImage(const char* filepath) {
		_image = LoadGraph(filepath);
	}
	void Draw() {
		//DrawModiGraph(
		//	position.x - (float)_size.width / 2, position.y - (float)_size.height / 2, //������W
		//	position.x + (float)_size.width / 2, position.y - (float)_size.height / 2, //�E����W
		//	position.x + (float)_size.width / 2, position.y + (float)_size.height / 2, //�E�����W
		//	position.x - (float)_size.width / 2, position.y + (float)_size.height / 2, //�������W
		//	_image, true); //�O���t�B�b�N�n���h���A���ߏ���
	}
};