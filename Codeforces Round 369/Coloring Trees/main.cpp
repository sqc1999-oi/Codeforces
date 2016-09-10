#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int p[N][N + 1], c[N];
long long f[N][N + 1][N + 1];
void update(long long &x, long long y) { x = min(x, y); }
int main()
{
	ios::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) cin >> c[i];
	for (int i = 0; i < n; i++)
		for (int j = 1; j <= m; j++)
			cin >> p[i][j];
	memset(f, 0x3f, sizeof f);
	if (c[0] == 0)
	{
		for (int i = 1; i <= m; i++)
			f[0][i][1] = p[0][i];
	}
	else f[0][c[0]][1] = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 1; k <= n; k++)
				if (f[i][j][k] < INF)
				{
					if (c[i + 1] == 0)
					{
						for (int l = 1; l <= m; l++)
							update(f[i + 1][l][k + (j != l)], f[i][j][k] + p[i + 1][l]);
					}
					else update(f[i + 1][c[i + 1]][k + (j != c[i + 1])], f[i][j][k]);
				}
	long long ans = INF;
	for (int i = 1; i <= m; i++) ans = min(ans, f[n - 1][i][k]);
	cout << (ans == INF ? -1 : ans) << endl;
}