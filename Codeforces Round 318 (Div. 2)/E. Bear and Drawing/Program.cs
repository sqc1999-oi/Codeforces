using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Linq;

namespace E.Bear_and_Drawing
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
			int n = reader.NextInt();
			var G = new LinkedList<int>[n + 1];
			for (int i = 1; i <= n; i++)
				G[i] = new LinkedList<int>();
			for (int i = 1; i < n; i++)
			{
				int a = reader.NextInt(), b = reader.NextInt();
				G[a].AddLast(b);
				G[b].AddLast(a);
			}
			var del = new bool[n + 1];
			Action<int, int> dfs = null;
			dfs = (x, fa) =>
			{
				if (G[x].Count <= 2)
				{
					del[x] = true;
					foreach (var item in G[x])
						if (item != fa)
							dfs(item, x);
				}
			};
			for (int i = 1; i <= n; i++)
				if (G[i].Count == 1)
					dfs(i, 0);
			var leg = new int[n + 1];
			for (int i = 1; i <= n; i++)
				leg[i] = Math.Min(2, Enumerable.Aggregate(G[i], 0, (sum, cur) => del[cur] ? sum + 1 : sum));
			bool flag = true;
			for (int i = 1; i <= n; i++)
				if (!del[i])
					if (Enumerable.Aggregate(G[i], 0, (sum, cur) => (!del[cur] && G[cur].Count - leg[cur] > 1) ? sum + 1 : sum) > 2)
					{
						flag = false;
						writer.WriteLine("No");
						break;
					}
			if (flag) writer.WriteLine("Yes");
			writer.Flush();
			Pause();
		}
	}
}
