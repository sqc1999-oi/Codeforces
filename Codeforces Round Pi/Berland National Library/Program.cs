using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Berland_National_Library
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
			var reader = new TextReaderHelper(new StreamReader(Console.OpenStandardInput(10240), Encoding.ASCII, false, 10240));
			var writer = new StreamWriter(Console.OpenStandardOutput(10240), Encoding.ASCII, 10240);
			int n = reader.NextInt();
			var In = new bool[1000001];
			var StartCount = 0;
			int Count = 0;
			int Max = int.MinValue;
			for (int i = 1; i <= n; i++)
			{
				string s = reader.NextString();
				int r = reader.NextInt();
				if (s == "+")
				{
					In[r] = true;
					Count++;
					Max = Math.Max(Max, Count);
				}
				else if (s == "-")
				{
					if (!In[r])
						StartCount++;
					In[r] = false;
					Count--;
				}
			}
			writer.WriteLine(Count + StartCount);
			writer.Flush();
			Pause();
		}
	}
}
