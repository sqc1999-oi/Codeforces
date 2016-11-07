#pragma warning(disable:4018)
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;
vector<int> G[400];
int mark[400];
bool dfs(int x, bool check = false)
{
	if (mark[x] == 1 || (check&&mark[x] == 2)) return true;
	if (mark[x ^ 1] == 1 || (check&&mark[x ^ 1] == 2)) return false;
	mark[x] = check ? 2 : 1;
	for (int i = 0; i < G[x].size(); i++)
		if (!dfs(G[x][i], check)) return false;
	return true;
}
char nextch(char ch, const string &s, char t)
{
	while (s[ch - 'a'] != t && ch - 'a' < s.length()) ch++;
	return ch;
}
pair<char, int> check(int i, char st, const string &s, char t, int n)
{
	char ch = nextch(st, s, t);
	if (ch - 'a' >= s.length()) return make_pair('z' + 1, 0);
	int x = i * 2 + (s[ch - 'a'] == 'C');
	for (int i = 0; i < n; i++)
		if (mark[i] == 2) mark[i] = 0;
	if (!dfs(x, true)) return make_pair('z' + 1, 0);
	return make_pair(ch, x);
}
int main()
{
	ios::sync_with_stdio(false);
	string let;
	int n, m;
	cin >> let >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int pos1, pos2;
		char t1, t2;
		cin >> pos1 >> t1 >> pos2 >> t2;
		--pos1 *= 2;
		--pos2 *= 2;
		if (t1 == 'C') pos1++;
		if (t2 == 'C') pos2++;
		G[pos1].push_back(pos2);
		G[pos2 ^ 1].push_back(pos1 ^ 1);
	}
	string s;
	cin >> s;
	for (int i = s.length(); i >= 0; i--)
	{
		memset(mark, 0x00, sizeof mark);
		bool flag = true;
		for (int j = 0; j < i; j++)
			if (!dfs(j * 2 + (let[s[j] - 'a'] == 'C')))
			{
				flag = false; break;
			}
		if (!flag) continue;
		string ans;
		for (int j = 0; j < s.length(); j++)
		{
			if (j < i) ans += s[j];
			else
			{
				char st = j == i ? s[j] + 1 : 'a';
				pair<char, int> p1, p2;
				p1.first = p2.first = 'z' + 1;
				if (mark[j * 2 + 1] != 1)
					p1 = check(j, st, let, 'V', n * 2);
				if (mark[j * 2] != 1)
					p2 = check(j, st, let, 'C', n * 2);
				pair<char, int> p = min(p1, p2);
				if (p.first > 'z') { flag = false; break; };
				dfs(p.second);
				ans += p.first;
			}
		}
		if (flag)
		{
			cout << ans;
			return 0;
		}
	}
	cout << -1;
}
