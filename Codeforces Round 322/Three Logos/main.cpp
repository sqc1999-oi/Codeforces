#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
const char ch[] = { 'A','B','C' };
int x[3], y[3];
void check1(int x1, int y1, int x2, int y2, int x3, int y3, char ch1, char ch2, char ch3)
{
	if (y1 == y2 && y2 == y3 && y1 == x1 + x2 + x3)
	{
		cout << y1 << endl;
		for (int i = 1; i <= x1; i++)
		{
			for (int j = 1; j <= y1; j++)
				cout << ch1;
			cout << endl;
		}
		for (int i = 1; i <= x2; i++)
		{
			for (int j = 1; j <= y1; j++)
				cout << ch2;
			cout << endl;
		}
		for (int i = 1; i <= x3; i++)
		{
			for (int j = 1; j <= y1; j++)
				cout << ch3;
			cout << endl;
		}
		exit(0);
	}
}
void check2(int x1, int y1, int x2, int y2, int x3, int y3, char ch1, char ch2, char ch3)
{
	if (x1 == x2 && y1 + y2 == y3 && x1 + x3 == y3)
	{
		cout << y3 << endl;
		for (int i = 1; i <= x1; i++)
		{
			for (int j = 1; j <= y1; j++)
				cout << ch1;
			for (int j = y1 + 1; j <= y3; j++)
				cout << ch2;
			cout << endl;
		}
		for (int i = 1; i <= x3; i++)
		{
			for (int j = 1; j <= y3; j++)
				cout << ch3;
			cout << endl;
		}
		exit(0);
	}
}
void check(int x1, int y1, int x2, int y2, int x3, int y3, char ch1, char ch2, char ch3)
{
	check1(x1, y1, x2, y2, x3, y3, ch1, ch2, ch3);
	check2(x1, y1, x2, y2, x3, y3, ch1, ch2, ch3);
}
void rcheck(int a, int b, int c)
{
	check(x[a], y[a], x[b], y[b], x[c], y[c], ch[a], ch[b], ch[c]);
	check(y[a], x[a], x[b], y[b], x[c], y[c], ch[a], ch[b], ch[c]);
	check(x[a], y[a], y[b], x[b], x[c], y[c], ch[a], ch[b], ch[c]);
	check(x[a], y[a], x[b], y[b], y[c], x[c], ch[a], ch[b], ch[c]);
	check(x[a], y[a], y[b], x[b], y[c], x[c], ch[a], ch[b], ch[c]);
	check(y[a], x[a], x[b], y[b], y[c], x[c], ch[a], ch[b], ch[c]);
	check(y[a], x[a], y[b], x[b], x[c], y[c], ch[a], ch[b], ch[c]);
	check(y[a], x[a], y[b], x[b], y[c], x[c], ch[a], ch[b], ch[c]);
}
int main()
{
	ios::sync_with_stdio(false);
	for (int i = 0; i < 3; i++)
		cin >> x[i] >> y[i];
	rcheck(0, 1, 2);
	rcheck(0, 2, 1);
	rcheck(1, 0, 2);
	rcheck(1, 2, 0);
	rcheck(2, 0, 1);
	rcheck(2, 1, 0);
	cout << -1;
}
