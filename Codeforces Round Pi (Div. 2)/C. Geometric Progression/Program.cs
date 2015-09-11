using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C.Geometric_Progression
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
			int n = reader.NextInt(), k = reader.NextInt();
			var Dic = new Dictionary<long, long>();
			var Count = new long[n + 1];
			var a = (from i in Enumerable.Range(0, n + 1) select i == 0 ? 0 : reader.NextElement<long>()).ToArray();
			for (int i = 1; i <= n; i++)
			{
				if (a[i] % k == 0)
					Dic.TryGetValue(a[i] / k, out Count[i]);
				long x;
				Dic.TryGetValue(a[i], out x);
				Dic[a[i]] = x + 1;
			}
			Dic.Clear();
			long Ans = 0;
			for (int i = n; i > 0; i--)
			{
				long x;
				Dic.TryGetValue(a[i] * k, out x);
				Ans += Count[i] * x;
				Dic.TryGetValue(a[i], out x);
				Dic[a[i]] = x + 1;
			}
			writer.WriteLine(Ans);
			writer.Flush();
			Pause();
		}
	}
}
