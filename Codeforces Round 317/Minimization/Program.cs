using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Minimization
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
		[Conditional("DEBUG")]
		static void Pause()
		{
			Console.ReadKey();
		}

		static int Calc(int i, int j, int[] a, int len, int flag)
		{
			int s = (i + j) * len + i + 1;
			int e = s + len + flag - 1;
			return a[e] - a[s];
		}

		static void Main(string[] args)
		{
			var reader = new TextReaderHelper(new StreamReader(Console.OpenStandardInput(), Encoding.ASCII, false, 1048576));
			var writer = new StreamWriter(Console.OpenStandardOutput(), Encoding.ASCII, 1048576);
			int n = reader.NextInt(), k = reader.NextInt();
			var a = (from i in Enumerable.Range(0, n + 1) select i == 0 ? 0 : reader.NextInt()).ToArray();
			Array.Sort(a, 1, n);
			int x = n % k, y = k - n % k;
			var f = new int[x + 1, y + 1];
			int len = n / k;
			for (int i = 0; i <= x; i++)
				for (int j = 0; j <= y; j++)
				{
					f[i, j] = int.MaxValue;
					if (i > 0) f[i, j] = Math.Min(f[i, j], f[i - 1, j] + Calc(i - 1, j, a, len, 1));
					if (j > 0) f[i, j] = Math.Min(f[i, j], f[i, j - 1] + Calc(i, j - 1, a, len, 0));
					if (f[i, j] == int.MaxValue) f[i, j] = 0;
				}
			writer.WriteLine(f[x, y]);
			writer.Flush();
			Pause();
		}
	}
}
