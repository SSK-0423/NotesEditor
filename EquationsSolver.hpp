#pragma once
#include <vector>
using namespace std;

//˜A—§ˆêŸ•û’ö®‚ğ‰ğ‚­ƒNƒ‰ƒX
class EquationsSolver {
public:
	void GaussEliminationPivoting(vector<vector<double>>& a, double x[], int n);
	void GaussEliminationPivoting(vector<vector<double>>& a, double x[], int n,const int first, const int last);
	void LU();
};