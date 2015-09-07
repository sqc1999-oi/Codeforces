using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace E.President_and_Roads
{
	public class Heap<T>
	{
		private readonly List<T> data;
		private readonly Comparison<T> compare;

		public Heap(Comparison<T> compare)
		{
			this.compare = compare;
			data = new List<T> { default(T) };
		}

		public int Count
		{
			get { return data.Count - 1; }
		}

		public T Peek()
		{
			return data[1];
		}

		public void Push(T item)
		{
			data.Add(item);
			var curPlace = Count;
			while (curPlace > 1 && compare(item, data[curPlace / 2]) < 0)
			{
				data[curPlace] = data[curPlace / 2];
				data[curPlace / 2] = item;
				curPlace /= 2;
			}
		}

		public T Pop()
		{
			var ret = data[1];
			data[1] = data[Count];
			data.RemoveAt(Count);
			var curPlace = 1;
			while (true)
			{
				var max = curPlace;
				if (Count >= curPlace * 2 && compare(data[max], data[2 * curPlace]) > 0)
					max = 2 * curPlace;
				if (Count >= curPlace * 2 + 1 && compare(data[max], data[2 * curPlace + 1]) > 0)
					max = 2 * curPlace + 1;
				if (max == curPlace)
					break;
				var item = data[max];
				data[max] = data[curPlace];
				data[curPlace] = item;
				curPlace = max;
			}

			return ret;
		}
	}

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

	class Edge
	{
		public int From, To;
		public long Power;

		public override string ToString()
		{
			return string.Format("From: {0}, To: {1}, Power: {2}", From, To, Power);
		}
	}

	abstract class GraphSolver
	{
		public LinkedList<int>[] Graph { get; protected set; }
		public Edge[] Edges { get; protected set; }

		public GraphSolver(int n, int m)
		{
			Graph = new LinkedList<int>[n + 1];
			Edges = new Edge[m + 1];
			for (int i = 1; i <= n; i++) Graph[i] = new LinkedList<int>();
			for (int i = 1; i <= m; i++) Edges[i] = new Edge();
		}

		public abstract void Solve(int source);
	}

	sealed class DijSolver : GraphSolver
	{
		private struct node
		{
			public int From;
			public long Dist;
		}

		private bool[] inQueue;

		public long[] Distance { get; private set; }

		public DijSolver(int n, int m)
			: base(n, m)
		{
			Distance = new long[n + 1];
			inQueue = new bool[n + 1];
		}

		public override void Solve(int source)
		{
			int n = Distance.Length - 1;
			for (int i = 1; i <= n; i++) Distance[i] = long.MaxValue;
			Distance[source] = 0;
			var heap = new Heap<node>((x, y) => x.Dist.CompareTo(y.Dist));
			heap.Push(new node() { From = source, Dist = 0 });
			while (heap.Count > 0)
			{
				var u = heap.Pop();
				if (u.Dist != Distance[u.From]) continue;
				foreach (var item in Graph[u.From])
				{
					var e = Edges[item];
					if (Distance[e.To] > e.Power + u.Dist)
					{
						Distance[e.To] =  e.Power + u.Dist;
						heap.Push(new node() { From = e.To, Dist = Distance[e.To] });
                    }
				}
			}
		}
	}

	sealed class TarjanSolver : GraphSolver
	{
		private int dfsClock;

		public int[] TimeStamp { get; private set; }

		public int[] Low { get; private set; }

		public bool[] IsBridge { get; private set; }

		public int[] Id { get; set; }

		public TarjanSolver(int n, int m)
			: base(n, m)
		{
			TimeStamp = new int[n + 1];
			Low = new int[n + 1];
			IsBridge = new bool[m + 1];
			Id = new int[m + 1];
			dfsClock = 0;
		}

		private void dfs(int u, int fa)
		{
			TimeStamp[u] = Low[u] = ++dfsClock;
			foreach (var item in Graph[u])
			{
				int v = Edges[item].To;
				if (TimeStamp[v] == 0)
				{
					dfs(v, Id[item]);
					Low[u] = Math.Min(Low[u], Low[v]);
					if (TimeStamp[u] < Low[v]) IsBridge[Id[item]] = true;
				}
				else if (Id[item] != fa) Low[u] = Math.Min(Low[u], TimeStamp[v]);
			}
		}

		public override void Solve(int source) { dfs(source, 0); }
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
			int n = reader.NextInt(), m = reader.NextInt(), s = reader.NextInt(), t = reader.NextInt();
			var solver = new DijSolver(n, m);
			var rSolver = new DijSolver(n, m);
			for (int i = 1; i <= m; i++)
			{
				solver.Edges[i].From = reader.NextInt();
				solver.Edges[i].To = reader.NextInt();
				solver.Edges[i].Power = reader.NextInt();
				rSolver.Edges[i].From = solver.Edges[i].To;
				rSolver.Edges[i].To = solver.Edges[i].From;
				rSolver.Edges[i].Power = solver.Edges[i].Power;
				solver.Graph[solver.Edges[i].From].AddLast(i);
				rSolver.Graph[rSolver.Edges[i].From].AddLast(i);
			}
			solver.Solve(s);
			rSolver.Solve(t);
			long minTime = solver.Distance[t];
			var tSolver = new TarjanSolver(n, m * 2);
			int edgeCount = 0;
			for (int i = 1; i <= m; i++)
				if (solver.Distance[solver.Edges[i].From] + rSolver.Distance[rSolver.Edges[i].From] + solver.Edges[i].Power == minTime)
				{
					tSolver.Edges[++edgeCount] = solver.Edges[i];
					tSolver.Id[edgeCount] = i;
					tSolver.Graph[tSolver.Edges[edgeCount].From].AddLast(edgeCount);
					tSolver.Edges[++edgeCount] = rSolver.Edges[i];
					tSolver.Id[edgeCount] = i;
					tSolver.Graph[tSolver.Edges[edgeCount].From].AddLast(edgeCount);
				}
			tSolver.Solve(s);
			for (int i = 1; i <= m; i++)
			{
				var e = solver.Edges[i];
				if (tSolver.IsBridge[i]) writer.WriteLine("YES");
				else
				{
					long tmp = minTime - solver.Distance[e.From] - rSolver.Distance[e.To] - 1;
					if (tmp > 0 && solver.Distance[e.From] != long.MaxValue && rSolver.Distance[e.To] != long.MaxValue) writer.WriteLine("CAN {0}", e.Power - tmp);
					else writer.WriteLine("NO");
				}
			}
			writer.Flush();
			Pause();
		}
	}
}
