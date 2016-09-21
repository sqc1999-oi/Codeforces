using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Duff_as_a_Queen
{

    class Program
    {
        static void Main()
        {
            var n = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            var a = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

        }
    }

    class Solver
    {
        public const int N = 30;

		int n, q;
		SegNode root;

		public Solver(int[] a, int q)
		{
			this.q = q;
			n = a.Length;
			root = SegNode.Build(0, n, a);
		}

		public static void InsertBasis(int[] a, int x)
		{
			for (int i = (int)Math.Floor(Math.Log(x, 2)); i >= 0; i--)
				if (a[i] == 0) a[i] = x;
				else x ^= a[i];
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
			for (int i = 0; i <= N; i++)
				InsertBasis(c, b[i]);
			return c;
		}

		public void Update(int l, int r, int x)
		{
			root.UpdateXor(x, l, r, 0, n);
			root.UpdateBasis(x, l, 0, n);
			root.UpdateBasis(x, r, 0, n);
		}

		public int Query(int l, int r)
		{
			int[] res = new int[N];
			root.QueryBasis(l + 1, r, 0, n, res);
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
			b = new int[Solver.N];
			Solver.CombineBasis(l.b, r.b, b);
		}

		public SegNode(int x)
		{
			a = x;
			b = new int[Solver.N];
			b[(int)Math.Floor(Math.Log(x, 2))] = x;
		}

		public static SegNode Build(int l, int r,int[] a)
		{
			if (l == r - 1)
				return new SegNode(a[l]);
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
			if (l == ql && r == qr)
				a ^= x;
			else
			{
				PushDownXor();
				if (qr <= mid)
					this.l.UpdateXor(x, ql, qr, l, mid);
				else if (ql >= mid)
					this.r.UpdateXor(x, ql, qr, mid, r);
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
			if (k < mid)
				return this.l.QueryXor(k, l, mid);
			else
				return this.r.QueryXor(k, mid, r);
		}

		public void UpdateBasis(int x, int k, int l, int r)
		{
			if (l == r - 1)
				for (int i = 0; i <= Solver.N; i++)
					b[i] ^= x;
			else
			{
				int mid = (l + r) / 2;
				if (k < mid)
					this.l.UpdateBasis(x, k, l, mid);
				else
					this.r.UpdateBasis(x, k, mid, r);
				MaintainBasis();
			}
		}

		public void QueryBasis(int ql, int qr, int l, int r, int[] res)
		{
			if (l == ql && r == qr)
				Solver.CombineBasis(res, b);
			else
			{
				int mid = (l + r) / 2;
				if (qr <= mid)
					this.l.QueryBasis(ql, qr, l, mid, res);
				if (ql >= mid)
					this.r.QueryBasis(ql, qr, mid, r, res);
				else
				{
					this.l.QueryBasis(ql, mid, l, mid, res);
					this.l.QueryBasis(mid, qr, mid, r, res);
				}
			}
		}
	}
}
