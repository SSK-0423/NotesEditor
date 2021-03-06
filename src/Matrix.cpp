#include "Matrix.hpp"

Math::Matrix::Matrix(int r, int c) : row(r), col(c)
{
	Resize(r, c);
}

// ÁZ
Math::Matrix Math::Matrix::operator+(const Matrix& matrix) const
{
	Matrix mat(this->row, this->col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat.myMatrix[i][j] = this->myMatrix[i][j] + matrix.myMatrix[i][j];
		}
	}
	return mat;
}

// ÁZãü
Math::Matrix& Math::Matrix::operator+=(const Matrix& matrix)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			this->myMatrix[i][j] += matrix.myMatrix[i][j];
		}
	}
	return *this;
}

// ¸Z
Math::Matrix Math::Matrix::operator-(const Matrix& matrix) const
{
	Matrix mat(this->row, this->col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat.myMatrix[i][j] = this->myMatrix[i][j] - matrix.myMatrix[i][j];
		}
	}
	return mat;
}

// ¸Zãü
Math::Matrix& Math::Matrix::operator-=(const Matrix& matrix)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			this->myMatrix[i][j] -= matrix.myMatrix[i][j];
		}
	}
	return *this;
}

// sñÏ
Math::Matrix Math::Matrix::operator*(const Matrix& matrix) const
{
	Matrix mat(this->row, matrix.col);
	for (int i = 0; i < mat.row; i++)
	{
		for (int j = 0; j < mat.col; j++)
		{
			for (int k = 0; k < mat.row; k++)
			{
				mat.myMatrix[i][j] += this->myMatrix[i][k] * matrix.myMatrix[k][j];
			}
		}
	}
	return mat;
}

// sñÏãü
Math::Matrix& Math::Matrix::operator*=(const Matrix& matrix)
{
	// sñÏ
	Matrix mat(this->row, matrix.col);
	for (int i = 0; i < mat.row; i++)
	{
		for (int j = 0; j < mat.col; j++)
		{
			for (int k = 0; k < mat.row; k++)
			{
				mat.myMatrix[i][j] += this->myMatrix[i][k] * matrix.myMatrix[k][j];
			}
		}
	}

	// ZÊÌTCYÉTCY
	Resize(mat.row, mat.col);

	// this.myMatrixÖÏÌÊãü
	for (int i = 0; i < mat.row; i++)
	{
		for (int j = 0; j < mat.col; j++)
		{
			this->myMatrix[i][j] = mat.myMatrix[i][j];
		}
	}
	return *this;
}

void Math::Matrix::Resize(int r, int c)
{
	myMatrix.clear();
	myMatrix.shrink_to_fit();

	row = r;
	col = c;

	myMatrix.resize(r);
	for (int i = 0; i < r; i++)
		myMatrix[i].resize(c);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			myMatrix[i][j] = 0;
		}
	}
}

void Math::Matrix::SetValue(std::initializer_list<float> val)
{
	std::vector<float> vec;
	for (auto v : val)
	{
		vec.push_back(v);
	}

	int index = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			myMatrix[i][j] = vec[index];
			index++;
		}
	}
}
