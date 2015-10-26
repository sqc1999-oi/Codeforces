#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cctype>
#include <climits>
#include <cstring>
using namespace std;
const int D[][2] = { {0,1},{1,0},{0,-1},{-1,0} };
char map[1001][1001];
int dis[4][1001][1001];
bool inq[1001][1001];
bool islegal(int x, int y, int n, int m) { return x > 0 && x <= n&&y > 0 && y <= m; }
bool isborder(int x, int y, int n, int m)
{
	for (int i = 0; i < 4; i++)
	{
		int nx = x + D[i][0], ny = y + D[i][1];
		if (islegal(nx, ny, n, m) && map[x][y] != map[nx][ny])
			return true;
	}
	return false;
}
void spfa(int dis[][1001], int n, int m, pair<int, int> s)
{
	for (int i = 1; i <= n; i++)
		fill(dis[i] + 1, dis[i] + 1 + m, INT_MAX);
	memset(inq, 0x00, sizeof inq);
	queue<pair<int, int> > q;
	q.push(s);
	dis[s.first][s.second] = 0;
	inq[s.first][s.second] = true;
	while (!q.empty())
	{
		auto u = q.front();
		q.pop();
		inq[u.first][u.second] = false;
		for (int i = 0; i < 4; i++)
		{
			auto v = make_pair(u.first + D[i][0], u.second + D[i][1]);
			if (islegal(v.first, v.second, n, m) &&	map[v.first][v.second] != '#')
			{
				int &disv = dis[v.first][v.second];
				int tmp = disv;
				disv = min(disv, dis[u.first][u.second] + !isdigit(map[v.first][v.second]));
				if (tmp != disv && !inq[v.first][v.second])
				{
					q.push(v);
					inq[v.first][v.second] = true;
				}
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	pair<int,int> s[4];
	for (int i = 1; i <= n; i++)
	{
		map[i][0] = ' ';
		for (int j = 1; j <= m; j++)
		{
			cin >> map[i][j];
			if (isdigit(map[i][j]) && isborder(i, j, n, m))
				s[map[i][j] - '0'] = make_pair(i, j);
		}
	}
	for (int i = 1; i <= 3; i++)
		spfa(dis[i], n, m, s[i]);
	int ans = INT_MAX;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			int sum = 0;
			for (int k = 1; k <= 3; k++)
				if (dis[k][i][j] < INT_MAX)
					sum += dis[k][i][j];
				else
				{
					sum = INT_MAX;
					break;
				}
			ans = min(ans, sum);
		}
	cout << (ans == INT_MAX ? -1 : ans);
}