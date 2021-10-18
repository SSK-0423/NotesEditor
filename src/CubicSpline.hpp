#pragma once
#include <vector>

/*
* 3���X�v���C����ԃN���X
*/

using namespace std;

class CubicSpline {
public:
	CubicSpline();
	void Init();
	void cubicSpline(vector<vector<double>> points, size_t n);
	double interpolation(double p, bool inverse);//��Ԓl�̌v�Z
private:

	int N;//��ԑ������̌�
	vector<vector<double>> coord;//�_�̍��W

	vector<double> v_array;//v_j
	vector<double> h_array;//h_j
	vector<vector<double>> A;

	vector<vector<double>> keisu; //keisu[n][4]

	void calc_v();//v�̌v�Z
	void calc_h();//h�̌v�Z
	void make_array(vector<double> h);//�z��쐬

	void calc_keisu(double u_array[]);//�W���̌v�Z
	double calc_a(double u_array[], size_t i);//�W��a_j�̌v�Z
	double calc_b(double u_array[], size_t i);//�W��b_j�̌v�Z
	double calc_c(double u_array[], size_t i);//�W��c_j�̌v�Z
	double calc_d(size_t i);//�W��d_j�̌v�Z
};