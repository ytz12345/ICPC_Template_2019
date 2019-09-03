int n, m;//向量个数和维度
struct Base {
	double a[N][N]; bool v[N];
	Base() {
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < N; j ++)
				a[i][j] = 0;
		for (int i = 0; i < N; i ++)
			v[i] = 0;
	}
	bool ins(double *x) {//高斯消元
		for (int i = 0; i < m; i ++) if (fabs(x[i]) > 1e-5) {
			if (v[i]) {
				double t = x[i] / a[i][i];
				for (int j = 0; j < m; j ++)
					x[j] -= t * a[i][j];
			}
			else {
				v[i] = 1;
				for (int j = 0; j < m; j ++)
					a[i][j] = x[j];
				return 1;
			}
		}
		return 0;
	}
}base;