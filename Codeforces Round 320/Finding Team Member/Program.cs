using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Finding_Team_Member
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
			int n = reader.NextInt() * 2;
			var l = new List<Team>();
			for (int i = 2; i <= n; i++)
				for (int j = 1; j < i; j++)
					l.Add(new Team { A = i, B = j, Strength = reader.NextInt() });
			l.Sort();
			var ans = new int[n + 1];
			foreach (var item in l)
				if (ans[item.A] == 0 && ans[item.B] == 0)
				{
					ans[item.A] = item.B;
					ans[item.B] = item.A;
				}
			for (int i = 1; i <= n; i++)
				writer.Write("{0} ", ans[i]);
			writer.Flush();
			Pause();
		}
	}

	struct Team : IComparable<Team>
	{
		public int A, B, Strength;

		public int CompareTo(Team other) { return other.Strength - Strength; }
	}
}
