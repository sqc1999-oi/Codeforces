using System;
using System.Linq;

namespace Duff_as_a_Queen
{

    class Program
    {
        static void Main()
        {
            var n = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            var a = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
			var solver = new Solver(a);
			for (int i = 0; i < n[1]; i++)
			{
				var q = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
				if (q[0] == 1) solver.Update(q[1] - 1, q[2], q[3]);
				else Console.WriteLine(solver.Query(q[1] - 1, q[2]));
			}
        }
    }

    class Solver
    {
        public const int N = 30;

		int n;
		int[] t;
		SegNode root;

		public Solver(int[] a)
		{
			n = a.Length;
			t = (int[])a.Clone();
			root = SegNode.Build(0, n, a);
		}

		public static void InsertBasis(int[] a, int x)
		{
			for (int i = N; i >= 0; i--)
				if ((x & (1 << i)) > 0)
				{
					if (a[i] == 0)
					{
						a[i] = x;
						return;
					}
					x ^= a[i];
				}
		}

		public static int[] CombineBasis(int[] a, int[] b, int[] c = null)
		{
			int[] res;
			if (c == null) res = a;
			else
			{
				res = c;
				a.CopyTo(c, 0);
			}
			for (int i = 0; i <= N; i++) InsertBasis(res, b[i]);
			return res;
		}

		public void Update(int l, int r, int x)
		{
			for (int i = l; i < r; i++) t[i] ^= x;
			root.UpdateXor(x, l, r, 0, n);
			root.UpdateBasis(x, l, 0, n);
			if (r < n) root.UpdateBasis(x, r, 0, n);
		}

		public int Query(int l, int r)
		{
			int[] res = new int[N + 1];
			if (l < r - 1) root.QueryBasis(l + 1, r, 0, n, res);
			InsertBasis(res, root.QueryXor(l, 0, n));
			return (int)Math.Pow(2, res.Count(x => x != 0));
		}
    }

	class SegNode
	{
		int a;
		int[] b;
		SegNode l, r;

		public SegNode(SegNode l, SegNode r)
		{
			this.l = l;
			this.r = r;
			b = new int[Solver.N + 1];
			MaintainBasis();
		}

		public SegNode(int x, int y)
		{
			a = x;
			b = new int[Solver.N + 1];
			if (y != 0) b[(int)Math.Log(y, 2)] = y;
		}

		public static SegNode Build(int l, int r,int[] a)
		{
			if (l == r - 1) return new SegNode(a[l], l > 0 ? a[l] ^ a[l - 1] : a[l]);
			else
			{
				int mid = (l + r) / 2;
				return new SegNode(Build(l, mid, a), Build(mid, r, a));
			}
		}

		public void MaintainBasis() { Solver.CombineBasis(l.b, r.b, b); }

		public void PushDownXor()
		{
			l.a ^= a;
			r.a ^= a;
			a = 0;
		}

		public void UpdateXor(int x, int ql, int qr, int l, int r)
		{
			int mid = (l + r) / 2;
			if (l == ql && r == qr) a ^= x;
			else
			{
				PushDownXor();
				if (qr <= mid) this.l.UpdateXor(x, ql, qr, l, mid);
				else if (ql >= mid) this.r.UpdateXor(x, ql, qr, mid, r);
				else
				{
					this.l.UpdateXor(x, ql, mid, l, mid);
					this.r.UpdateXor(x, mid, qr, mid, r);
				}
			}
		}

		public int QueryXor(int k, int l, int r)
		{
			if (l == r - 1) return a;
			PushDownXor();
			int mid = (l + r) / 2;
			if (k < mid) return this.l.QueryXor(k, l, mid);
			else return this.r.QueryXor(k, mid, r);
		}

		public void UpdateBasis(int x, int k, int l, int r)
		{
			if (l == r - 1)
			{
				for (int i = 0; i <= Solver.N; i++)
					if (b[i] != 0)
					{
						x ^= b[i];
						b[i] = 0;
						break;
					}
				if (x != 0) b[(int)Math.Log(x, 2)] = x;
			}
			else
			{
				int mid = (l + r) / 2;
				if (k < mid) this.l.UpdateBasis(x, k, l, mid);
				else this.r.UpdateBasis(x, k, mid, r);
				MaintainBasis();
			}
		}

		public void QueryBasis(int ql, int qr, int l, int r, int[] res)
		{
			if (l == ql && r == qr) Solver.CombineBasis(res, b);
			else
			{
				int mid = (l + r) / 2;
				if (qr <= mid) this.l.QueryBasis(ql, qr, l, mid, res);
				else if (ql >= mid) this.r.QueryBasis(ql, qr, mid, r, res);
				else
				{
					this.l.QueryBasis(ql, mid, l, mid, res);
					this.r.QueryBasis(mid, qr, mid, r, res);
				}
			}
		}
	}
}
