// ゲーム開発に使う構造体や定数をまとめたファイル
#pragma once
//#include "Object.hpp"
//#include "GameObject.hpp"
//#include "Canvas"
#include "Vector2D.hpp"
//  オブジェクトのサイズ
typedef Vector2D<int> Size2D;
//  オブジェクトの位置
typedef Vector2D<float> Position;
//  画像
typedef int Image;
//  音楽
typedef int Audio;
// オブジェクトの基本情報
struct ObjInfo{
    Size2D size;
    Position Position;
};