// �Q�[���J���Ɏg���\���̂�萔���܂Ƃ߂��t�@�C��
#pragma once
#include "Object.hpp"
#include "ComponentSystem.hpp"
#include "Vector2.hpp"

// �E�B���h�E�T�C�Y
//struct WindowSize 
//{
//	static const int WINDOW_SIZE_WIDTH;
//	static const int WINDOW_SIZE_HEIGHT;
//};

template<class T>
struct Size2D;

template<>
struct Size2D<int>
{
	int width;
	int height;
	Size2D() : width(0),height(0)
	{
	}
	Size2D(int w, int h) : width(w), height(h)
	{
	}
};

template<>
struct Size2D<float>
{
	float width;
	float height;
	Size2D() : width(0), height(0)
	{
	}
	Size2D(float w, float h) : width(w), height(h)
	{
	}
};

template<class T>
using Position2D = Vector2<T>;

template<class T>
using Rotation2D = Vector2<T>;

// �F
using Color = unsigned int;
// �摜
using Image = int;
// �I�[�f�B�I
using Audio = int;
// �t�H���g
using Font = int;
//
using Degree = float;
