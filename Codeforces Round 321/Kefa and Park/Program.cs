using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Kefa_and_Park
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
			int n = reader.NextInt(), m = reader.NextInt();
			var a = new bool[n + 1];
			for (int i = 1; i <= n; i++)
				a[i] = reader.NextInt() == 1;
			var Graph = new LinkedList<int>[n + 1];
			for (int i = 1; i <= n; i++) Graph[i] = new LinkedList<int>();
			for (int i = 1; i < n; i++)
			{
				int x = reader.NextInt(), y = reader.NextInt();
				Graph[x].AddLast(y);
				Graph[y].AddLast(x);
			}
			int ans = 0;
			Action<int, int, int> dfs = null;
			dfs = (cur, fa, cnt) =>
			{
				if (cnt > m) return;
				if (cur != 1 && Graph[cur].Count == 1)
					ans++;
				foreach (var i in Graph[cur])
					if (i != fa)
						dfs(i, cur, a[i] ? cnt + 1 : 0);
			};
			dfs(1, 0, a[1] ? 1 : 0);
			writer.WriteLine(ans);
			writer.Flush();
			Pause();
		}
	}
}
