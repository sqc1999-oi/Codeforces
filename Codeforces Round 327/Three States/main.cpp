#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
const int D[][2] = { {0,1},{1,0},{-1,0},{0,-1} };
char map[1000000];
int dis[4][1000000], sdis[4][4];
int get(int x, int y, int m) { return x*m + y; }
bool islegal(int x, int y, int n, int m) { return x >= 0 && x < n && y >= 0 && y < m; }
bool isborder(int x, int y, int n, int m)
{
	if (!isdigit(map[get(x, y, m)])) return false;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + D[i][0], ny = y + D[i][1];
		if (islegal(nx, ny, n, m) && map[get(x, y, m)] != map[get(nx, ny, m)]) return true;
	}
	return false;
}
void bfs(int k, int n, int m)
{
	queue<int> q;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
 			if (map[get(i, j, m)] == k + '0' && isborder(i, j, n, m))
				q.push(get(i, j, m));
			else dis[k][get(i, j, m)] = INT_MAX;
		}
	for (int i = 1; i <= 3; i++)
		sdis[k][i] = INT_MAX;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		int ux = u / m, uy = u%m;
		for (int i = 0; i < 4; i++)
		{
			int vx = ux + D[i][0], vy = uy + D[i][1];
			int v = get(vx, vy, m);
			if (islegal(vx, vy, n, m) && map[v] != '#' && dis[k][v] == INT_MAX)
				if (isdigit(map[v]))
				{
					sdis[k][map[v] - '0'] = min(sdis[k][map[v] - '0'], dis[k][u]);
					sdis[map[v] - '0'][k] = min(sdis[map[v] - '0'][k], dis[k][u]);
				}
				else
				{
					dis[k][v] = dis[k][u] + 1;
					q.push(v);
				}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	cin.get();
	for (int i = 0; i < n; i++)
		cin.getline(map + i*m, m + 1);
	for (int i = 1; i <= 3; i++)
		bfs(i, n, m);
	int ans = INT_MAX;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int x = get(i, j, m);
			if (isdigit(map[x]))
			{
				int sum = 0;
				for (int k = 1; k <= 3; k++)
					if (map[x] != k + '0')
					{
						if (sdis[map[x] - '0'][k] == INT_MAX)
						{
							sum = INT_MAX;
							break;
						}
						sum += sdis[map[x] - '0'][k];
					}
				if (sum == INT_MAX) continue;
				ans = min(ans, sum);
			}
			else
			{
				int sum = 0;
				for (int k = 1; k <= 3; k++)
				{
					if (dis[k][x] == INT_MAX)
					{
						sum = INT_MAX;
						break;
					}
					sum += dis[k][x];
				}
				if (sum == INT_MAX) continue;
				ans = min(ans, sum - 2);
			}
		}
	if (ans == INT_MAX) cout << -1;
	else cout << ans;
}
