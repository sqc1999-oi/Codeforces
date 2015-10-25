using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Mausoleum
{
	class TextReaderHelper
	{
		protected TextReader baseReader;
		protected LinkedList<string> buffer;

		public TextReaderHelper(TextReader baseReader)
		{
			this.baseReader = baseReader;
			buffer = new LinkedList<string>();
		}

		protected void readIfEmpty()
		{
			if (buffer.Count > 0) return;
			string line;
			do
			{
				line = baseReader.ReadLine();
				if (line == null) return;
			}
			while (line.Trim() == string.Empty);
			foreach (var item in line.Split(' ', '\n', '\t'))
				if (item != string.Empty)
					buffer.AddLast(item);
		}

		private object readChar()
		{
			var node = buffer.First;
			var ret = node.Value[0];
			if (node.Value.Length > 1) node.Value = node.Value.Substring(1);
			else buffer.RemoveFirst();
			return ret;
		}

		public T NextElement<T>()
		{
			readIfEmpty();
			if (typeof(T) == typeof(char)) return (T)readChar();
			var ret = (T)Convert.ChangeType(buffer.First.Value, typeof(T));
			buffer.RemoveFirst();
			return ret;
		}

		public int NextInt() { return NextElement<int>(); }

		public string NextString() { return NextElement<string>(); }
	}

	class Program
	{
		static long[,] f;
		static int k;
		static int[] x, y;
		static string[] sign;

		static void Main(string[] args)
		{
			var reader = new TextReaderHelper(new StreamReader(Console.OpenStandardInput(10240), Encoding.ASCII, false, 10240));
			var writer = new StreamWriter(Console.OpenStandardOutput(10240), Encoding.ASCII, 10240);
			int n = reader.NextInt() * 2;
			k = reader.NextInt();
			f = new long[n, n];
			for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) f[i, j] = -1;
			x = new int[k];
			y = new int[k];
			sign = new string[100];
			for (int i = 0; i < k; i++)
			{
				x[i] = reader.NextInt() - 1;
				sign[i] = reader.NextString();
				y[i] = reader.NextInt() - 1;
			}
			writer.WriteLine(dp(0, n - 1));
			writer.Flush();
			Pause();
		}

		[Conditional("DEBUG")]
		static void Pause()
		{
			Console.ReadKey();
		}

		static long dp(int l, int r)
		{
			if (f[l, r] == -1)
			{
				f[l, r] = 0;
				if (l + 1 == r)
				{
					if (check(l, r, l, r))
						f[l, r]++;
				}
				else
				{
					if (check(l, r, l, l + 1)) f[l, r] += dp(l + 2, r);
					if (check(l, r, l, r)) f[l, r] += dp(l + 1, r - 1);
					if (check(l, r, r - 1, r)) f[l, r] += dp(l, r - 2);
				}
			}
			return f[l, r];
		}

		static bool check(int l, int r, int a, int b)
		{
			for (int i = 0; i < k; i++)
			{
				int flagX = getFlag(l, r, a, b, x[i]), flagY = getFlag(l, r, a, b, y[i]);
				if ((flagX == 0 || flagY == 0) && !match(flagX, sign[i], flagY)) return false;
			}
			return true;
		}

		static int getFlag(int l, int r, int a, int b, int x)
		{
			if (x < l || x > r) return -1;
			if (x == a || x == b) return 0;
			return 1;
		}

		static bool match(int a, string s, int b)
		{
			switch (s)
			{
				case "<": return a < b;
				case ">": return a > b;
				case "<=": return a <= b;
				case ">=": return a >= b;
				default: return a == b;
			}
		}
	}
}
