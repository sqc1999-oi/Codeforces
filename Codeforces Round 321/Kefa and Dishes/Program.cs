using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Kefa_and_Dishes
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
		private static void Pause()
		{
			Console.ReadKey();
		}

		static void Main(string[] args)
		{
			var reader = new TextReaderHelper(new StreamReader(Console.OpenStandardInput(), Encoding.ASCII, false, 1048576));
			var writer = new StreamWriter(Console.OpenStandardOutput(), Encoding.ASCII, 1048576);
			int n = reader.NextInt(), m = reader.NextInt(), K = reader.NextInt();
			var a = new int[n];
			for (int i = 0; i < n; i++)
				a[i] = reader.NextInt();
			var rule = new int[n, n];
			for (int i = 1; i <= K; i++)
				rule[reader.NextInt() - 1, reader.NextInt() - 1] = reader.NextInt();
			var f = new long[1 << n, n];
			long ans = 0;
			for (int i = 0; i < n; i++)
			{
				f[1 << i, i] = a[i];
				if (m == 1) ans = Math.Max(ans, a[i]);
			}
			for (int i = 2; i < (1 << n); i++)
			{
				int x = i, cnt = 0;
				while (x > 0)
				{
					cnt += x % 2;
					x /= 2;
				}
				if (cnt <= 1 || cnt > m) continue;
				for (int j = 0; j < n; j++)
					if ((i & (1 << j)) > 0)
						for (int k = 0; k < n; k++)
							if (j != k && (i & (1 << k)) > 0)
								f[i, k] = Math.Max(f[i, k], f[i - (1 << k), j] + a[k] + rule[j, k]);
				if (cnt == m)
					for (int j = 0; j < n; j++)
						if ((i & (1 << j)) > 0)
							ans = Math.Max(ans, f[i, j]);
			}
			writer.WriteLine(ans);
			writer.Flush();
			Pause();
		}
	}
}
