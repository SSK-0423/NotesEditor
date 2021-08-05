// �Q�[���J���Ɏg���\���̂�萔���܂Ƃ߂��t�@�C��
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
/* �ȉ����ꉻ */
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

//  �F
typedef unsigned int Color;
//  �摜
typedef int Image;
//  �I�[�f�B�I
typedef int Audio;

