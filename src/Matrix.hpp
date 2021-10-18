#pragma once
#include <vector>
#include <initializer_list>

/*
* 行列クラス
*/
namespace Math
{
	class Matrix
	{
	public:
		// 行
		int row;
		// 列
		int col;

		// 行列
		std::vector<std::vector<float>> myMatrix;

		Matrix(int r, int c);

		// 加算
		Matrix operator+(const Matrix& matrix) const;
		// 加算代入
		Matrix& operator+=(const Matrix& matrix);

		// 減算 
		Matrix operator-(const Matrix& matrix) const;
		// 減算代入
		Matrix& operator-=(const Matrix& matrix);

		// 行列積
		Matrix operator*(const Matrix& matrix) const;
		// 行列積代入
		Matrix& operator*=(const Matrix& matrix);

		void Resize(int r, int c);
		void SetValue(std::initializer_list<float> val);
	};
}