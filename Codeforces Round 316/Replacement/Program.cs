using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Replacement
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
			var s = new StringBuilder(' ' + reader.NextString() + ' ');
			int len = 0, cnt = 0;
			for (int i = 1; i <= n; i++)
			{
				if (s[i] == '.')
				{
					len++;
					if (s[i - 1] != '.') cnt++;
				}
			}
			for (int i = 1; i <= m; i++)
			{
				int x = reader.NextInt();
				char c = reader.NextElement<char>();
				if (c != '.')
				{
					if (s[x] == '.')
					{
						len--;
						if (s[x - 1] == '.' && s[x + 1] == '.') cnt++;
						else if (s[x - 1] != '.' && s[x + 1] != '.') cnt--;
					}
				}
				else
				{
					if (s[x] != '.')
					{
						len++;
						if (s[x - 1] == '.' && s[x + 1] == '.') cnt--;
						else if (s[x - 1] != '.' && s[x + 1] != '.') cnt++;
					}
				}
				s[x] = c;
				writer.WriteLine(len - cnt);
			}
			writer.Flush();
			Pause();
		}
	}
}
