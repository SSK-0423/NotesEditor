#pragma once
/*
	‰ñ“]ˆÚ“®‚ğs‚¤ƒNƒ‰ƒX
*/
namespace Math 
{
	class Matrix;
}
using Degree = float;
class Rotator {
public:
	// ‰ñ“]ˆÚ“®
	Math::Matrix Rotate(const Math::Matrix matrix,Degree angle);
};