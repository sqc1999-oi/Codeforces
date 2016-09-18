using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Duff_in_Beach
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
			const int P = (int)1e9 + 7;
			var n = reader.NextInt();
			long l = reader.NextElement<long>();
			var k = reader.NextInt();
			var a = (from i in Enumerable.Range(0, n) select reader.NextInt()).ToArray();
			var b = (from i in a orderby i select i).Distinct().ToArray();
			a = (from i in a select Array.BinarySearch(b, i)).ToArray();
			int m = b.Length;
			var cnt = new int[m, 2];
			for (int i = 0; i < n; i++)
			{
				cnt[a[i], 0] = (cnt[a[i], 0] + 1) % P;
				if (i < l % n) cnt[a[i], 1] = (cnt[a[i], 1] + 1) % P;
			}
			var f = new int[k + 1, m, 2];
			for (int i = 0; i < m; i++)
			{
				f[1, i, 0] = cnt[i, 0];
				f[1, i, 1] = cnt[i, 1];
			}
			for (int i = 2; i <= k; i++)
			{
				int tmp = 0;
				for (int j = 0; j < m; j++)
				{
					tmp = (int)(((long)tmp + f[i - 1, j, 0]) % P);
					f[i, j, 0] = (int)((long)tmp * cnt[j, 0] % P);
					f[i, j, 1] = (int)((long)tmp * cnt[j, 1] % P);
				}
			}
			int ans = 0;
			for (int i = 1; i <= k && i <= l / n; i++)
			{
				int sum = 0;
				for (int j = 0; j < m; j++)
					sum = (sum + f[i, j, 0]) % P;
				ans = (int)((ans + sum * ((l / n - i + 1) % P)) % P);
			}
			for (int i = 1; i <= k && i <= Math.Ceiling((double)l / n); i++)
			{
				int sum = 0;
				for (int j = 0; j < m; j++)
					sum = (sum + f[i, j, 1]) % P;
				ans = (ans + sum) % P;
			}
			writer.WriteLine(ans);
			writer.Flush();
			Pause();
		}
	}
}
