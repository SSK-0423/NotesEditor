#include "EquationsSolver.hpp"
#include "GaussElimination.hpp"
#include "LUdecomposition.hpp"

//�����s�{�b�g�I��t���K�E�X�̏����@(�X�v���C����ԗp)
void EquationsSolver::GaussEliminationPivoting(vector<vector<double>>& a, double x[], int n,const int first, const int last) {
	GaussEliminationWithPivoting(a,x,n,first,last);
}
//�����s�{�b�g�I��t���K�E�X�̏����@
void EquationsSolver::GaussEliminationPivoting(vector<vector<double>>& a, double x[], int n) {
	GaussEliminationWithPivoting(a, x, n);
}

//LU����(������)�K�v�ɂȂ�������
void EquationsSolver::LU() {
	LUdecomposition();
}