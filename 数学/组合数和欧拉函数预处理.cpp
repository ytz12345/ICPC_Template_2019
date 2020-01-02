/*组合数预处理*/
fac[0] = 1, inv[0] = 1, inv[1] = 1;
for (int i = 1; i <= n; i ++) {
    fac[i] = fac[i - 1] * i % Mod;
    if (i != 1) inv[i] = inv[Mod % i] * (Mod - Mod / i) % Mod;
}
for (int i = 2; i <= n; i ++) 
    inv[i] = inv[i] * inv[i - 1] % Mod;

/*欧拉函数预处理*/
void get_phi(int n, int *phi, int *p, int *v) {
    for (int i = 2; i <= n; i ++) {
        if (!v[i]) phi[i] = i - 1, p[++ p[0]] = i;
        for (int j = 1; j <= p[0] && i * p[j] <= n; j ++) {
            v[i * p[j]] = 1;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            else phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
}