#pragma once


static Integer modulo(Integer k, int n) 
{
	if (k < 0)k = n - (-k) % n;
	if (k >= n) return k % n;
	return k;
}

static int cmmdc(int a, int b)
{
	int r;
	while (b != 0)
	{
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return a;
}

static Integer a_la_b_mod_c(Integer a, int b, int c)
{
	Integer p = 1;
	a = modulo(a, c);
	while (b > 0)
	{
		if (b % 2)
			p = modulo((p * a), c);
		a = modulo((a * a), c);
		b /= 2;
	}
	return p;
}

static bool test_Fermat(int n, int nr_incercari)
{
	if (n == 2) 
		return 1;
	if (n % 2 == 0) 
		return 0;
	for (; nr_incercari > 0; nr_incercari--) 
	{
		int b = rand();
		b = 2 + b % (n - 2);
		if (cmmdc(b, n) != 1) 
			return 0;
		if (a_la_b_mod_c(b, n - 1, n) != 1) 
			return 0;
	}
	return 1;
}

static bool test_Miller_Rabin(int n, int nr_incercari)
{
	if (n == 2) 
		return 1;
	if (n % 2 == 0) 
		return 0;
	for (; nr_incercari > 0; nr_incercari--)
	{
		int s = 0, t = n - 1, b = rand();
		b = 2 + b % (n - 2);
		while (t % 2 == 0)
		{
			s++;
			t /= 2;
		}
		t = a_la_b_mod_c(b, t, n);//in t pastram acum puterile b^t,b^(2t),...
		if (t != 1)
		{
			while ((t != n - 1) && (--s > 0))
			{
				t = (t * t) % n;
				if (t == 1) 
					return 0;
			}
			if (t != n - 1) 
				return 0;
		}
	}
	return 1;
}