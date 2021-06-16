#pragma once
#include <vector>
using std::vector;

void View_a(vector<vector<double>> &matrix, int n);
void Pivoting(vector<vector<double>> &a, int n, int k);
int GaussEliminationWithPivoting(vector<vector<double>>& a, double x[], int n);
int GaussEliminationWithPivoting(vector<vector<double>>& a, double x[], int n, const int first, const int last);