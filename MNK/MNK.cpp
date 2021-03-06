// 
//Метод наиментших квадратов, для аппроксимации полимномом n-ой степени

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <cmath>
template < typename T> //вспомогательный класс матрицы с методом Гаусса
class Matrix
{
protected:
	T * * mat;
	int high;
	int thickness;
public:
	Matrix()
	{
		high = 2;
		thickness = 2;
		T** = new T[2];
		for (int i = 0; i < 2; i++)
		{
			T[i] = new T[2];

		}
	}
	Matrix(int h, int t)
	{
		high = h;
		thickness = t;
		mat = new T*[high];
		for (int i = 0; i < high; i++)
		{
			mat[i] = new T[thickness];

		}
		for (int i = 0; i < high; i++)
		{
			for (int j = 0; j < thickness; j++)
			{
				mat[i][j] = 0;
			}

		}
	}
	void get()
	{
		for (int i = 0; i < high; i++)
		{
			for (int j = 0; j < thickness; j++)
			{
				cin >> mat[i][j];
			}

		}
	}
	void show()
	{
		for (int i = 0; i < high; i++)
		{
			for (int j = 0; j < thickness; j++)
			{
				cout << mat[i][j] << ' ';
			}
			cout << endl;
		}
	}
	void triangular()
	{
		if (high != (thickness - 1))
		{
			cout << "QuantityExeption" << endl;
			return;
		}
		for (int i = 0; i<high; i++)
		{
			if (mat[i][i] == 0)
			{
				cout << "ZeroDiagArgument" << endl;
				return;
			}
		}

		for (int opornaya = 0; opornaya < high; opornaya++)
		{
			T cash = mat[opornaya][opornaya];
			for (int leg = opornaya; leg<thickness; leg++)
			{
				mat[opornaya][leg] /= cash;
			}
			for (int j = opornaya + 1; j < high; j++)
			{
				T cash2 = mat[j][opornaya];
				for (int i = opornaya; i < thickness; i++)
				{

					mat[j][i] -= (mat[opornaya][i] * cash2);
				}
			}
			//cout << endl; // tests stuff
		}

	}
	Matrix <T> solution()
	{
		triangular();
		Matrix<T> answer(high, 1);
		for (int i = high - 1; i >= 0; i--)
		{
			T mem = 0;
			for (int j = 0; j < high; j++)
			{
				mem += (mat[i][high - j - 1] * answer.mat[high - j - 1][0]);
				//cout<<j<< ' ' << mem << " " << mat[i][j] << endl;
			}

			answer.mat[i][0] = (mat[i][high] - mem);
			//cout << mat[high - i][high] << ' ';
		}
		return answer;

	}
	static void show_residular_vector(Matrix <T> matr, Matrix <T> solution)
	{
		if (matr.thickness - 1 != solution.high)
		{
			cout << "Wrong high!";
			return;
		}
		T buff;
		cout << "nevyazka" << endl;
		for (int i = 0; i <solution.high; i++)
		{
			buff = 0;
			for (int j = 0; j < solution.high; j++)
			{
				buff += matr.mat[i][j] * solution.mat[j][0];
			}
			cout << buff - matr.mat[i][matr.thickness - 1] << endl;
		}
	}

};


template < typename T>
class MNK : private Matrix<T>
{
private:
	std::vector<double> X;
	std::vector<double> Y;
	int n; // порядок полинома 
	int m; // колво точек
	T summX(int p)
	{
		T sum = 0;
		for (int i = 0; i < m; i++)
		{
			sum += pow(X[i], p);
		}
		return sum;
	}
	T summY(int p)
	{
		T sum = 0;
		for (int i = 0; i < m; i++)
		{
			sum += pow(X[i], p)*Y[i];
		}
		return sum;
	}

public:
	MNK(int N, int M): Matrix<T>(N+1,N+2)
	{
		n = N+1;
		m = M;
	}
	void get_X()
	{
		T mem;
		for (int i = 0; i < m; i++)
		{
			cin >> mem;
			X.push_back (mem);
		}
	}
	void get_Y()
	{
		T mem;
		for (int i = 0; i < m; i++)
		{
			cin >> mem;
			Y.push_back(mem);
		}
	}
	void make_matr()
	{
		if (X.size() != Y.size())
		{
			cout << "X!=Y" << endl;
			return;
		}
		for (int i=0;i<n;i++)
		{
			for (int j = 0; j < n; j++)
			{
				this->mat[i][j] = summX(i + j);
					this->mat[j][n] = summY(j);
			}
		}
	}
	void show()
	{
		/*for (size_t i = 0; i < Y.size(); i++)
		{
			cout << Y[i];
		}*/
		Matrix<T>::show();
	}
	void result()
	{
		cout << "rate = " << n-1<<endl;

		Matrix<T>::solution().show();
	}
	void copyXY(MNK<T>* par)
	{
		X = par->X;
		Y = par->Y;
	}
};

using namespace std;
int main()
{
	
	MNK <double> test(4,11);  // аппроксимация полиномом 4 степени 11 значений 
	test.get_X();
	test.get_Y();
	test.make_matr();
	test.result();	// коэффициенты выводятся в порядке возрастания степени x, при котором они стоят
	
	MNK <double> test2(2, 11); // аппроксимация полиномом 4 степени 11 значений
	test2.copyXY(&test);
	test2.make_matr();
	test2.result();
	_getch();
	return 0;
}
