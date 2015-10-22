using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Text;

namespace E.Weakness_and_Poorness
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
			int n = reader.NextInt();
			var a = new int[n + 1];
			for (int i = 1; i <= n; i++)
				a[i] = reader.NextInt();
			Func<double, bool, double> f = (x, flag) =>
			 {
				 double ans = 0, sum = 0;
				 for (int i = 1; i <= n; i++)
				 {
					 sum += flag ? (a[i] - x) : (x - a[i]);
					 sum = Math.Max(sum, 0);
					 ans = Math.Max(ans, sum);
				 }
				 return ans;
			 };
			const double eps = 1e-12;
			double l = -1e4, r = 1e4;
			while (Math.Abs(l - r) > eps)
			{
				double mid = (l + r) / 2;
				if (f(mid, true) > f(mid, false)) l = mid;
				else r = mid;
			}
			writer.WriteLine(f(l, false).ToString(new CultureInfo("zh-cn")));
			writer.Flush();
			Pause();
		}
	}
}
