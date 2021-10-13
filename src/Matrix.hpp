#pragma once
#include <vector>
#include <initializer_list>

namespace Math
{
	class Matrix
	{
	public:
		// s
		int row;
		// —ñ
		int col;

		// s—ñ
		std::vector<std::vector<float>> myMatrix;

		Matrix(int r, int c);

		// ‰ÁZ
		Matrix operator+(const Matrix& matrix) const;
		// ‰ÁZ‘ã“ü
		Matrix& operator+=(const Matrix& matrix);

		// Œ¸Z 
		Matrix operator-(const Matrix& matrix) const;
		// Œ¸Z‘ã“ü
		Matrix& operator-=(const Matrix& matrix);

		// s—ñÏ
		Matrix operator*(const Matrix& matrix) const;
		// s—ñÏ‘ã“ü
		Matrix& operator*=(const Matrix& matrix);

		void Resize(int r, int c);
		void SetValue(std::initializer_list<float> val);
	};
}