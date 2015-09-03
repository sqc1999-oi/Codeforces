using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace D.Tree_Requests
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

	struct Info : IComparable<Info>
	{
		public int TimeStamp, Flags;

		public int CompareTo(Info other)
		{
			return TimeStamp.CompareTo(other.TimeStamp);
		}
	}

	class Program
	{
		static string S;
		static LinkedList<int>[] Graph;
		static List<Info>[] D;
		static int Now;
		static int[] Begin, End;

		[Conditional("DEBUG")]
		static void Pause()
		{
			Console.ReadKey();
		}

		static void DFS(int id, int depth)
		{
			D[depth].Add(new Info() { TimeStamp = ++Now, Flags = D[depth].Last().Flags ^ (1 << (S[id - 1] - 'a')) });
			Begin[id] = Now;
			foreach (var item in Graph[id])
				DFS(item, depth + 1);
			End[id] = Now;
		}

		static void Main(string[] args)
		{
			var reader = new TextReaderHelper(new StreamReader(Console.OpenStandardInput(), Encoding.ASCII, false, 1048576));
			var writer = new StreamWriter(Console.OpenStandardOutput(), Encoding.ASCII, 1048576);
			int n = reader.NextInt(), m = reader.NextInt();
			Graph = new LinkedList<int>[n + 1];
			for (int i = 1; i <= n; i++) Graph[i] = new LinkedList<int>();
			for (int i = 2; i <= n; i++)
				Graph[reader.NextInt()].AddLast(i);
			S = reader.NextString();
			D = new List<Info>[n + 1];
			for (int i = 1; i <= n; i++)
			{
				D[i] = new List<Info>();
				D[i].Add(new Info() { TimeStamp = 0, Flags = 0 });
			}
			Now = 0;
			Begin = new int[n + 1];
			End = new int[n + 1];
			DFS(1, 1);
			for (int i = 1; i <= n; i++) D[i].Add(new Info() { TimeStamp = int.MaxValue, Flags = D[i].Last().Flags });
			var start = DateTime.Now;
			for (int i = 1; i <= m; i++)
			{
				int v = reader.NextInt(), h = reader.NextInt();
				int l = D[h].BinarySearch(new Info() { TimeStamp = Begin[v] }), r = D[h].BinarySearch(new Info { TimeStamp = End[v] });
				
				if (l < 0) l = ~l;
				if (r < 0) r = ~r - 1;
				int x = D[h][l - 1].Flags ^ D[h][r].Flags;
				int cnt = 0;
				while (x > 0)
				{
					cnt += (x & 1);
					x >>= 1;
				}
				writer.WriteLine(cnt > 1 ? "No" : "Yes");
			}
			writer.Flush();
			Pause();
		}
	}
}
