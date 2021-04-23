#pragma once
struct Vector2D {
	float x;
	float y;
};

struct Object2D {
	Vector2D position;			//オブジェクト座標(描画)
	Vector2D collisionPos;		//オブジェクトの当たり判定位置
	int width;					//幅
	int height;					//高さ
};