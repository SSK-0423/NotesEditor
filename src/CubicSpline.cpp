#include "CubicSpline.hpp"
#include "EquationsSolver.hpp"
#include <iostream>

using namespace std;

double CubicSpline::interpolation(double p,bool inverse) {
	int inv = 0;
	if (inverse) inv = 1;
	printf("x = %lf\n",p);
	//点の数=N+1
	for (int i = 0; i < N; i++) {
		printf("xの範囲[%lf,%lf]\n", coord[i][0], coord[i + 1][0]);
		if (coord[i+inv][0] <= p && p <= coord[i+1-inv][0]) {
			printf("a=%lf,b=%lf,c=%lf,d=%lf ", keisu[i][0], keisu[i][1], keisu[i][2], keisu[i][3]);
			double tmp1 = keisu[i][0] * pow(p - coord[i][0], 3);
			double tmp2 = keisu[i][1] * pow(p - coord[i][0], 2);
			double tmp3 = keisu[i][2] * (p - coord[i][0]);
			return tmp1 + tmp2 + tmp3 + keisu[i][3];
		}
	}
}

//3次スプライン補間(点の座標データ、点の数)
void CubicSpline::cubicSpline(vector<vector<double>> points, int n){
	
	N = n - 1;//補間多項式の数(N)
	coord = points;

	double* u_array;
	u_array = new double[N+1];
	u_array[0] = u_array[N] = 0;
	calc_h();
	calc_v();
	make_array(h_array);
	calc_keisu(u_array);

	delete[] u_array;
}

//hの計算
void CubicSpline::calc_h() {
	for (int i = 0; i < N; i++) {
		h_array.push_back(coord[i + 1][0] - coord[i][0]);
		printf("h[%d]=%f\n", i, h_array[i]);
	}
	//cout << "h_size= " << h_array.size() << "\n";
}
//vの計算
void CubicSpline::calc_v() {
	for (int i = 1; i < N; i++) {
		double tmp1 = (coord[i + 1][1] - coord[i][1]) / h_array[i];
		double tmp2 = (coord[i][1] - coord[i - 1][1]) / h_array[i - 1];
		v_array.push_back(6 * (tmp1 - tmp2));
	}
	//cout << "v_size= " << v_array.size() << "\n";
	for (int i = 0; i < N - 1; i++) {
		cout << v_array[i] << " ";
	}
	cout << "\n";
}

//左辺左の行列作成
void CubicSpline::make_array(vector<double> h) {
	A.resize(N - 1);
	//配列の初期化
	for (int i = 0; i < N - 1; i++) {
		A[i].resize(N - 1);
		for (int j = 0; j < N - 1; j++) {
			A[i][j]=0;
		}
	}
	//1行目
	A[0][0] = 2 * (h[0] + h[1]);
	A[0][1] = h[1];
	//2行目～[n-1]行目の行列作成
	for (int i = 1; i < N - 1; i++) {
		//[n-1]行目
		if (i == N - 2) {
			A[i][i - 1] = h[i - 1];
			A[i][i] = 2 * (h[i - 1] + h[i]);
			break;
		}
		A[i][i-1] = h[i];
		A[i][i] = 2 * (h[i] + h[i + 1]);
		A[i][i + 1] = h[i + 1];

	}
	for (int i = 0; i < N - 1; i++) {
		printf("v_array[%d]=%4.2f \n",i,v_array[i]);
		A[i].push_back(v_array[i]);
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N; j++) {
			printf("%5.3f ",A[i][j]);
		}
		cout << "\n";
	}
}

//係数a,b,c,dの計算
void CubicSpline::calc_keisu(double u_array[]) {
	keisu.resize(N);
	EquationsSolver es;
	es.GaussEliminationPivoting(A, u_array,N-1,1,N-1);
	for (int i = 0; i <= N; i++) {
		printf("u[%d]=%5.3f\n",i,u_array[i]);
	}
	cout << "----------------------------------------\n";
	for (int i = 0; i <= N-1; i++) {
		keisu[i].push_back(calc_a(u_array, i));
		keisu[i].push_back(calc_b(u_array, i));
		keisu[i].push_back(calc_c(u_array, i));
		keisu[i].push_back(calc_d(i));

		cout << keisu[i][0] << "\n";
		cout << keisu[i][1] << "\n";
		cout << keisu[i][2] << "\n";
		cout << keisu[i][3] << "\n";
		cout << "------------------------\n";
		cout << endl;
	}
}
//aの計算
double CubicSpline::calc_a(double u_array[],int i){
	return (u_array[i + 1] - u_array[i]) / (6 * (coord[i + 1][0] - coord[i][0]));
}
//bの計算
double CubicSpline::calc_b(double u_array[],int i){
	return u_array[i] / 2;
}
//cの計算
double CubicSpline::calc_c(double u_array[],int i){
	double tmp1 = (coord[i + 1][1] - coord[i][1]) / (coord[i + 1][0] - coord[i][0]);
	double tmp2 = (coord[i + 1][0] - coord[i][0]) * (2 * u_array[i] + u_array[i + 1]) / 6;
	return tmp1 - tmp2;
}
//dの計算
double CubicSpline::calc_d(int i){
	return coord[i][1];
}
