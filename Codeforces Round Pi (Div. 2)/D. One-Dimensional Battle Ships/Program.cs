using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace D.One_Dimensional_Battle_Ships
{
	/*class TextReaderHelper
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
	}*/

	struct Segment : IComparable<Segment>
	{
		public int Left, Right;

		public int CompareTo(Segment other)
		{
			return Right.CompareTo(other.Right);
		}
	}

	class Program
	{
		[Conditional("DEBUG")]
		static void Pause()
		{
			Console.ReadKey();
		}

		static StreamReader reader;

		static int NextInt()
		{
			int ret = 0;
			char ch;
			do ch = (char)reader.Read();
			while (!char.IsDigit(ch));
			do
			{
				ret = ret * 10 + ch - '0';
				ch = (char)reader.Read();
			}
			while (char.IsDigit(ch));
			return ret;
		}

		static void Main(string[] args)
		{
			reader = new StreamReader(Console.OpenStandardInput(10240), Encoding.ASCII, false, 10240);
			var writer = new StreamWriter(Console.OpenStandardOutput(10240), Encoding.ASCII, 10240);
			int n = NextInt(), k = NextInt(), a = NextInt(), m = NextInt();
			var set = new SortedSet<Segment>();
			set.Add(new Segment() { Left = 1, Right = n });
			int Count = (n + 1) / (a + 1);
			var Visited = new bool[n + 1];
			bool Found = false;
			for (int i = 1; i <= m; i++)
			{
				int x = NextInt();
				if (Visited[x]) continue;
				Visited[x] = true;
				var seg = set.GetViewBetween(new Segment() { Right = x }, new Segment { Right = n + 1 }).First();
				set.Remove(seg);
				Count -= (seg.Right - seg.Left + 2) / (a + 1);
				if (x != seg.Left)
				{
					var l = new Segment() { Left = seg.Left, Right = x - 1 };
					Count += (l.Right - l.Left + 2) / (a + 1);
					set.Add(l);
				}
				if (x != seg.Right)
				{
					var r = new Segment() { Left = x + 1, Right = seg.Right };
					Count += (r.Right - r.Left + 2) / (a + 1);
					set.Add(r);
				}
				if (Count < k)
				{
					writer.WriteLine(i);
					Found = true;
					break;
				}
			}
			if (!Found) writer.WriteLine(-1);
			writer.Flush();
			Pause();
		}
	}
}
