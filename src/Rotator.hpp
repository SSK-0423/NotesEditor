#pragma once
/*
	��]�ړ����s���N���X
*/
namespace Math 
{
	class Matrix;
}
using Degree = float;
class Rotator {
public:
	// ��]�ړ�
	Math::Matrix Rotate(const Math::Matrix matrix,Degree angle);
};