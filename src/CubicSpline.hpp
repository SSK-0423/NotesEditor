#pragma once
#include <vector>

/*
* 3ŸƒXƒvƒ‰ƒCƒ“•âŠÔƒNƒ‰ƒX
*/

using namespace std;

class CubicSpline {
	public:
		void Init();
		void cubicSpline(vector<vector<double>> points, int n);
		double interpolation(double p,bool inverse);//•âŠÔ’l‚ÌŒvZ
	private:

		int N;//•âŠÔ‘½€®‚ÌŒÂ”
		vector<vector<double>> coord;//“_‚ÌÀ•W

		vector<double> v_array;//v_j
		vector<double> h_array;//h_j
		vector<vector<double>> A;

		vector<vector<double>> keisu; //keisu[n][4]

		void calc_v();//v‚ÌŒvZ
		void calc_h();//h‚ÌŒvZ
		void make_array(vector<double> h);//”z—ñì¬

		void calc_keisu(double u_array[]);//ŒW”‚ÌŒvZ
		double calc_a(double u_array[],int i);//ŒW”a_j‚ÌŒvZ
		double calc_b(double u_array[],int i);//ŒW”b_j‚ÌŒvZ
		double calc_c(double u_array[],int i);//ŒW”c_j‚ÌŒvZ
		double calc_d(int i);//ŒW”d_j‚ÌŒvZ
};