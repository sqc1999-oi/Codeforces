using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Pig_and_Palindromes
{
	class TextReaderHelper
	{
		protected TextReader BaseReader;
		protected LinkedList<string> Buffer;

		public TextReaderHelper(TextReader baseReader)
		{
			this.BaseReader = baseReader;
			Buffer = new LinkedList<string>();
		}

		protected void ReadIfEmpty()
		{
			if (Buffer.Count > 0) return;
			string line;
			do
			{
				line = BaseReader.ReadLine();
				if (line == null) return;
			}
			while (line.Trim() == string.Empty);
			foreach (var item in line.Split(' ', '\n', '\t'))
				if (item != string.Empty)
					Buffer.AddLast(item);
		}

		private object ReadChar()
		{
			var node = Buffer.First;
			var ret = node.Value[0];
			if (node.Value.Length > 1) node.Value = node.Value.Substring(1);
			else Buffer.RemoveFirst();
			return ret;
		}

		public T NextElement<T>()
		{
			ReadIfEmpty();
			if (typeof(T) == typeof(char)) return (T)ReadChar();
			var ret = (T)Convert.ChangeType(Buffer.First.Value, typeof(T));
			Buffer.RemoveFirst();
			return ret;
		}

		public int NextInt() { return NextElement<int>(); }

		public string NextString() { return NextElement<string>(); }
	}

	class Program
	{

		[Conditional("DEBUG")]
		static void Pause()
		{
			Console.ReadKey();
		}

		static void Main(string[] args)
		{
			var reader = new TextReaderHelper(new StreamReader(Console.OpenStandardInput(), Encoding.ASCII, false, 1048576));
			var writer = new StreamWriter(Console.OpenStandardOutput(), Encoding.ASCII, 1048576);
			int n = reader.NextInt(), m = reader.NextInt();
			var map = new char[n + 1, m + 1];
			for (int i = 1; i <= n; i++)
			{
				string line = reader.NextString();
				for (int j = 1; j <= m; j++)
					map[i, j] = line[j - 1];
			}
			var f = new int[2, n + 2, n + 2];
			const int M = (int)1e9 + 7;
			int cur = 1;
			if (map[1, 1] == map[n, m]) f[1, 1, n] = 1;
			for (int i = 1; i <= (n + m - 2) / 2; i++)
			{
				cur ^= 1;
				for (int j = 1; j <= n; j++) for (int k = 1; k <= n; k++) f[cur, j, k] = 0;
				for (int x1 = 1; x1 <= n && x1 - 1 <= i; x1++)
					for (int x2 = n; x2 >= x1 && n - x2 <= i; x2--)
					{
						int y1 = i - x1 + 2, y2 = m - i + n - x2;
						if (y1 <= y2 && map[x1, y1] == map[x2, y2])
						{
							f[cur, x1, x2] = (f[cur, x1, x2] + f[cur ^ 1, x1, x2]) % M;
							f[cur, x1, x2] = (f[cur, x1, x2] + f[cur ^ 1, x1 - 1, x2]) % M;
							f[cur, x1, x2] = (f[cur, x1, x2] + f[cur ^ 1, x1, x2 + 1]) % M;
							f[cur, x1, x2] = (f[cur, x1, x2] + f[cur ^ 1, x1 - 1, x2 + 1]) % M;
						}
					}
			}
			int ans = 0;
			for (int i = 1; i <= n; i++)
				ans = (ans + f[cur, i, i]) % M;
			if ((n + m) % 2 == 1)
				for (int i = 1; i < n; i++)
					ans = (ans + f[cur, i, i + 1]) % M;
			writer.WriteLine(ans);
			writer.Flush();
			Pause();
		}
	}
}
