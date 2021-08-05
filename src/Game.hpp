// ゲーム開発に使う構造体や定数をまとめたファイル
#pragma once
#include "Object.hpp"
#include "GameObject.hpp"
#include "ComponentSystem.hpp"

template<class ...T>
struct Size2D;

template<>
struct Size2D<int> {
	int width;
	int height;
};

template<>
struct Size2D<float> {
	int width;
	int height;
};

template <class ...T>
struct Position;
/* 以下特殊化 */
template<>
struct Position<int> {
	int x;
	int y;
};

template<>
struct Position<float>{
	float x;
	float y;
};

//  色
typedef unsigned int Color;
//  画像
typedef int Image;
//  オーディオ
typedef int Audio;

