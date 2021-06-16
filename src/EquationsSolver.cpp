#include "EquationsSolver.hpp"
#include "GaussElimination.hpp"
#include "LUdecomposition.hpp"

//部分ピボット選択付きガウスの消去法(スプライン補間用)
void EquationsSolver::GaussEliminationPivoting(vector<vector<double>>& a, double x[], int n,const int first, const int last) {
	GaussEliminationWithPivoting(a,x,n,first,last);
}
//部分ピボット選択付きガウスの消去法
void EquationsSolver::GaussEliminationPivoting(vector<vector<double>>& a, double x[], int n) {
	GaussEliminationWithPivoting(a, x, n);
}

//LU分解(未実装)必要になったらやる
void EquationsSolver::LU() {
	LUdecomposition();
}