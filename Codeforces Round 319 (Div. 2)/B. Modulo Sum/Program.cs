using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B.Modulo_Sum
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

		static void Main(string[] args)
		{
			var reader = new TextReaderHelper(new StreamReader(Console.OpenStandardInput(), Encoding.ASCII, false, 1048576));
			var writer = new StreamWriter(Console.OpenStandardOutput(), Encoding.ASCII, 1048576);
			int n = reader.NextInt(), m = reader.NextInt();
			if (n > m) writer.WriteLine("YES");
			else
			{
				var a = (from i in Enumerable.Range(0, n) select reader.NextInt() % m).ToArray();
				var dp = new int[n, m];
				dp[0, 0] = 1;
				dp[0, a[0]] = 2;
				for (int i = 1; i < n; i++)
					for (int j = 0; j < m; j++)
					{
						if (dp[i - 1, (j - a[i] + m) % m] > 0)
							dp[i, j] = Math.Max(Math.Min(dp[i - 1, (j - a[i] + m) % m] + 1, 2), dp[i, j]);
						if (dp[i - 1, j] > 0)
							dp[i, j] = Math.Max(dp[i - 1, j], dp[i, j]);
					}
				writer.WriteLine(dp[n - 1, 0] > 1 ? "YES" : "NO");
			}
			writer.Flush();
			Pause();
		}
	}
}
