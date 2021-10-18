#include <iostream>
#include <vector>
#define N 3 //解の個数

using namespace std;

// 拡大係数行列の表示
void View_a(vector<vector<double>> &matrix,int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n+1; j++) {
			printf("%f ",matrix[i][j]);
		}
		printf("\n");
	}
}

//ピボット選択
inline void Pivoting(vector<vector<double>> &a , int n, int k) {
	int p = k;//ピボットのある行
	int max = fabs(a[k][k]);//最大値
	for (int i = k + 1; i < n; i++) {
		if (fabs(a[i][k]) > max) {
			p = i;//ピボットのある行を更新
			max = fabs(a[i][k]);
		}
	}

	//新たにピボットが選択されていたら
	if (k != p) {
		swap(a[k], a[p]);
	}
}

//部分ピボット選択付きガウス消去法
int GaussEliminationWithPivoting(vector<vector<double>> &a, double x[],int n) {
	
	//前進消去
	for (int k = 0; k < n-1; k++) { //前進消去のステップ＝解の個数 - 1回
		//ピボット選択
		Pivoting(a, n, k);
		for (int i = k + 1; i < n; i++) {
			for (int j = k+1; j < n+1; j++) {
				a[i][j] = a[i][j] - a[i][k] * (a[k][j] / a[k][k]);
			}
		}
	}

	//後退代入
	// x_n
	x[n - 1] = a[n - 1][n] / a[n - 1][n - 1];
	// x_j
	for (int i = N - 2; i >= 0; i--) {
		double sum = 0.0;
		for (int j = i + 1; j < n; j++) {
			sum += a[i][j] * x[j];
		}
		printf("%f, %f\n", a[i][n] - sum, a[i][i]);
		x[i] = (a[i][n] - sum) / a[i][i];
	}

	return 1;
}