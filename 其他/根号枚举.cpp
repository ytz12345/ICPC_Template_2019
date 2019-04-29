for (int i = 1, last; i <= n; i = last + 1) {
	last = n / (n / i);
	//当前枚举区间为[i, last]
}