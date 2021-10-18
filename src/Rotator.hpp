#pragma once
/*
	回転移動を行うクラス
*/

namespace Math 
{
	class Matrix;
}
using Degree = float;
class Rotator {
public:
	// 回転移動
	Math::Matrix Rotate(const Math::Matrix matrix,Degree angle);
};