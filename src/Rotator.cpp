#include "Rotator.hpp"
#include "Matrix.hpp"
#include <cmath>

Math::Matrix Rotator::Rotate(const Math::Matrix matrix, Degree angle)
{
	// ラジアンへ変換
	float radian = acosf(-1) / 180.f * angle;
	// 2次元の回転行列
	Math::Matrix rotMat(2, 2);
	rotMat.SetValue({
		cosf(radian),-sinf(radian),
		sinf(radian), cosf(radian)
		});
	
	Math::Matrix mat(2,1);
	mat = rotMat * matrix;

	return mat;
}