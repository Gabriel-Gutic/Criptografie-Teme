#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>


int modulo(int k, int n)
{
	if (k < 0)k = n - (-k) % n;
	if (k >= n) return k % n;
	return k;
}

int cmmdc(int a, int b)
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

bool prim(int n)
{
	if (n == 0 || n == 1)
		return false;
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	int s = (int)sqrt(n);
	for (int d = 3; d <= s; d++)
	{
		if (n % d == 0)
			return false;
	}
	return true;
}

int a_la_b_mod_c(int a, int b, int c)
{
	int p = 1;
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

bool test_Fermat(int n, int nr_incercari)
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

bool test_Miller_Rabin(int n, int nr_incercari)
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

int** factor(unsigned int n, int& nr)
{
	int** descompunere = new int* [2];
	descompunere[0] = new int[n];
	descompunere[1] = new int[n];
	for (unsigned long long i = 0; i < n; i++)
		descompunere[0][i] = descompunere[1][i] = 0;
	if (n % 2 == 0)
	{
		descompunere[0][0] = 2;
		nr++;
		while (n % 2 == 0)
		{
			descompunere[1][0]++;
			n /= 2;
		}
	}
	for (unsigned long long i = 3; i <= n; i += 2)
	{
		if (n % i == 0)
		{
			descompunere[0][nr] = i;
			while (n % i == 0)
			{
				descompunere[1][nr]++;
				n /= i;
			}
			nr++;
		}
	}
	return descompunere;
}

char* citeste_din_fisier(std::ifstream& in)
{
	char* mesaj = new char[100];
	char c;
	int i = 0;
	if (in.good())
	{
		std::cout << "Fisierul a fost deschis cu succes.\n Continutul acestuia este:\n\n";
		while (!in.eof()) // cat timp nu s-a ajuns la sfarsitul fisierului sursa
		{
			in >> std::noskipws >> c;
			mesaj[i] = c;
			i++;
		}
		mesaj[--i] = '\0';
	}
	else
		std::cout << "Eroare la deschiderea fisierului.";
	return mesaj;
}

void scrie_in_fisier(const char* mesaj)
{
	//vom scrie caracter cu caracter
	std::ofstream out("destinatie.txt"); //deschidem fisierul pentru scriere
	//echivalent cu:
	//fstream out("destinatie.txt",ios::out);)
	//pentru a adauga text intr-un fisier:
	//fstream out("destinatie.txt",ios::app);
	int i = 0;
	while (mesaj[i] != '\0') // cat timp nu s-a ajuns la sfarsitul mesajului
	{
		out << mesaj[i];
		i++;
	}
	out.close();//inchidem fisierul
}

struct bloc
{
	char c;
	int nr;
};
bloc character[100] = { 0 };
int N = 0;
int da_cod(char c)
{
	for (int i = 0; i < N; i++)
		if (character[i].c == c)
			return i;
	return -1;
}
char da_caracter(int cod)
{
	return character[cod % N].c;
}

void citeste_alfabet(std::ifstream& in)
{
	if (!in.good())
		perror("Fisier inexistent");
	char c;
	while (in >> std::noskipws >> c)
	{
		character[N].c = c;
		N++;
	}
	if (N == 0)
		std::cout << "Alfabetul dat are 0 caractere" << std::endl;
}

void frecv(std::ifstream& fin)
{
	if (!fin.good())
		perror("Fisier inexistent");
	char c;
	while (fin >> std::noskipws >> c)
	{
		int cod = da_cod(c);
		if (cod >= 0 && cod < N)
			character[cod].nr++;
	}
	int ordonat = 0;
	while (!ordonat)
	{
		ordonat = 1;
		for (int i = 0; i < N - 1; i++)
		{
			if (character[i].nr < character[i + 1].nr)
			{
				ordonat = 0;
				bloc temp = character[i];
				character[i] = character[i + 1];
				character[i + 1] = temp;
			}
		}
	}
}