using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Order_Book
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

	class BuyComparer : IComparer<int>
	{
		public int Compare(int x, int y)
		{
			return y.CompareTo(x);
		}
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
			int n = reader.NextInt(), s = reader.NextInt();
			var B = new SortedDictionary<int, int>(new BuyComparer());
			var S = new SortedDictionary<int, int>();
			for (int i = 1; i <= n; i++)
			{
				SortedDictionary<int, int> Now;
				if (reader.NextString() == "B") Now = B;
				else Now = S;
				int p = reader.NextInt(), q;
				Now.TryGetValue(p, out q);
				Now[p] = q + reader.NextInt();
			}
			var Emtr = S.GetEnumerator();
			var stack = new Stack<string>();
			for (int i = 1; i <= s && Emtr.MoveNext(); i++)
				stack.Push(string.Format("S {0} {1}", Emtr.Current.Key, Emtr.Current.Value));
			while (stack.Count > 0)
				writer.WriteLine(stack.Pop());
			Emtr = B.GetEnumerator();
			for (int i = 1; i <= s && Emtr.MoveNext(); i++)
				writer.WriteLine("B {0} {1}", Emtr.Current.Key, Emtr.Current.Value);
			writer.Flush();
			Pause();
		}
	}
}
