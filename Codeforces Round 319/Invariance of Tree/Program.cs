using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Invariance_of_Tree
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
			var p = new int[n + 1];
			for (int i = 1; i <= n; i++) p[i] = reader.NextInt();
			var vis = new bool[n + 1];
			List<int> cyc1, cyc2;
			cyc1 = cyc2 = null;
			bool cyco = false;
			for (int i = 1; i <= n; i++)
				if (!vis[i])
				{
					int x = i;
					var l = new List<int>();
					do
					{
						vis[x] = true;
						l.Add(x);
						x = p[x];
					}
					while (x != i);
					if (l.Count == 1) cyc1 = l;
					else if (l.Count == 2) cyc2 = l;
					else if (l.Count % 2 == 1) cyco = true;
				}
			if (cyc1 != null)
			{
				writer.WriteLine("YES");
				for (int i = 1; i <= n; i++)
					if (i != cyc1[0])
						writer.WriteLine("{0} {1}", cyc1[0], i);
			}
			else if (cyc2 != null && !cyco)
			{
				writer.WriteLine("YES");
				Array.Clear(vis, 1, n);
				writer.WriteLine("{0} {1}", cyc2[0], cyc2[1]);
				vis[cyc2[0]] = vis[cyc2[1]] = true;
				for (int i = 1; i <= n; i++)
					if (!vis[i])
					{
						int x = i, cur = 0;
						do
						{
							vis[x] = true;
							writer.WriteLine("{0} {1}", cyc2[cur], x);
							x = p[x];
							cur ^= 1;
						}
						while (x != i);
					}
			}
			else Console.WriteLine("NO");
			writer.Flush();
			Pause();
		}
	}
}
