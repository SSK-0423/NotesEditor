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
		//	position.x - (float)_size.width / 2, position.y - (float)_size.height / 2, //左上座標
		//	position.x + (float)_size.width / 2, position.y - (float)_size.height / 2, //右上座標
		//	position.x + (float)_size.width / 2, position.y + (float)_size.height / 2, //右下座標
		//	position.x - (float)_size.width / 2, position.y + (float)_size.height / 2, //左下座標
		//	_image, true); //グラフィックハンドル、透過処理
	}
};