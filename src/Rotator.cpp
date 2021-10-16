#include "Rotator.hpp"
#include "Matrix.hpp"
#include "GameUtility.hpp"
#include <cmath>

Math::Matrix Rotator::Rotate(const Math::Matrix matrix, Degree angle)
{
	// ƒ‰ƒWƒAƒ“‚Ö•ÏŠ·
	Radian radian = DegreeToRadian(angle);
	// 2ŸŒ³‚Ì‰ñ“]s—ñ
	Math::Matrix rotMat(2, 2);
	rotMat.SetValue({
		cosf(radian),-sinf(radian),
		sinf(radian), cosf(radian)
		});
	
	Math::Matrix mat(2,1);
	mat = rotMat * matrix;

	return mat;
}