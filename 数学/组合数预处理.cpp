fac[0] = 1, inv[0] = 1, inv[1] = 1;
for (int i = 1; i <= n; i ++) {
    fac[i] = fac[i - 1] * i % Mod;
    if (i != 1) inv[i] = inv[Mod % i] * (Mod - Mod / i) % Mod;
}
for (int i = 2; i <= n; i ++) 
    inv[i] = inv[i] * inv[i - 1] % Mod;