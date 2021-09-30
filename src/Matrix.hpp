#pragma once
#include <vector>
#include <initializer_list>

namespace Math
{
	class Matrix
	{
	public:
		// �s
		int row;
		// ��
		int col;

		// �s��
		std::vector<std::vector<float>> myMatrix;

		Matrix(int r, int c);

		// ���Z
		Matrix operator+(const Matrix& matrix) const;
		// ���Z���
		Matrix& operator+=(const Matrix& matrix);

		// ���Z 
		Matrix operator-(const Matrix& matrix) const;
		// ���Z���
		Matrix& operator-=(const Matrix& matrix);

		// �s���
		Matrix operator*(const Matrix& matrix) const;
		// �s��ϑ��
		Matrix& operator*=(const Matrix& matrix);

		void Resize(int r, int c);
		void SetValue(std::initializer_list<float> val);
	};
}