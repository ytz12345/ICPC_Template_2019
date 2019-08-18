#include <bits/stdc++.h>

using namespace std;

const int N=10;

int T, n, m, q;

int a[500010];

int main() {
	ios::sync_with_stdio(false);
	srand(time(NULL));
	int n = rand() % N + 3, m = rand() % N + 3;
	printf("%d %d\n", n,m);
	for (int i = 2; i<=n; i ++) {
		printf("%d %d %d\n", i, rand()%(i-1)+1, rand() % N + 1);
	}
	int op,s,t,a,b;
	while ( m --) {
		op=rand()%2;
		if (op) {
			printf("1 %d %d %d %d\n", rand()%n+1,rand()%n+1,rand()%10, rand()%10+1);
		}
		else {
			printf("2 %d %d\n", rand()%n+1,rand()%n+1);
		}
	}
}