#include "stdafx.h"
#include "Matrix.h"
#include "List.cpp"

void Matrix::Normalized()
{
	for (int i = 0; i < this->Elements.size(); i++)
		if (this->Elements[i].Value == 0)
		{
			this->Elements.Delete(i);
			i--;
		}
}

Matrix::Matrix()
{
	this->X = 0;
	this->Y = 0;
}
Matrix::Matrix(const int x)
{
	this->X = x;
	this->Y = x;
	this->Elements = List<ElementMatrix>(x);
	for (int i = 0; i < this->Elements.size(); i++)
	{
		this->Elements[i].i = i + 1;
		this->Elements[i].j = i + 1;
		this->Elements[i].Value = 1;
	}
}
Matrix::Matrix(const int x, const int y)
{
	this->X = x;
	this->Y = y;
}
Matrix::Matrix(const int x, const int y, const List<ElementMatrix>& M)
{
	this->X = x; 
	this->Y = y;
	this->Elements = List<ElementMatrix>(M);
    Normalized();
}
Matrix::Matrix(const Matrix& Mat)
{
	this->X = Mat.X; this->Y = Mat.X;
	this->Elements = List<ElementMatrix>(Mat.Elements);
	Normalized();
}
Matrix::~Matrix()
{
}

void Matrix::operator=(const Matrix& M)
{
	this->X = M.X;
	this->Y = M.Y;
	this->Elements = List<ElementMatrix>(M.Elements);
}

void Matrix::Scanf()
{
	printf("M N\n");
	scanf_s("%d", &this->X);
	scanf_s("%d", &this->Y);

	printf("Size !=0 elements = ");
	int K;
	scanf_s("%d", &K);
	if (K != 0)
	{
		printf("M  N  Value\n");

		this->Elements = List<ElementMatrix>(K);

		for (int i = 0; i < K; i++)
		{
			scanf_s("%d", &Elements[i].i);
			scanf_s("%d", &Elements[i].j);
			scanf_s("%lf", &Elements[i].Value);
		}

	}
	Normalized();
	printf("Success!\n");
}
void Matrix::ScanfElements()
{
	printf("Size !=0 elements = ");
	int K;
	scanf_s("%d", &K);
	if (K != 0)
	{
		this->Elements = List<ElementMatrix>(K);
		printf("M  N  Value\n");
		for (int i = 0; i < K; i++)
		{
			cin >> this->Elements[i].i;
			cin >> this->Elements[i].j;
			cin >> this->Elements[i].Value;
		}
	}
	Normalized();
	printf("Success!\n");
}
void Matrix::PrintfMatrix() const
{
	double** Mat = new double*[this->X];
	for (int i = 0; i < this->X; i++)
		Mat[i] = new double[this->Y];

	for (int i = 0; i < this->X; i++)
		for (int j = 0; j < this->Y; j++)
			Mat[i][j] = 0;

	for (int i = 0; i < this->Elements.size(); i++)
		Mat[this->Elements[i].i - 1][this->Elements[i].j - 1] = this->Elements[i].Value;

	printf("\n Matrix:\n");
	for (int i = 0; i < this->X; i++)
	{
		for (int j = 0; j < this->Y; j++)
			printf("%lf  ", Mat[i][j]);
		printf("\n");
	}

	for (int i = 0; i < this->X; i++)
		delete[] Mat[i];
	delete[] Mat;
}
void Matrix::Printf() const
{
	printf("\n Matrix:\n");
	printf("M  N  Value\n");
	for (int i = 0; i < this->Elements.size(); i++)
		printf("%d  %d  %lf\n", this->Elements[i].i, this->Elements[i].j, this->Elements[i].Value);
}

Matrix Matrix::transpose() const
{
	List<ElementMatrix> Elements2(this->Elements);
	for (int i = 0; i < this->Elements.size(); i++)
	{
		int A = Elements2[i].i;
		Elements2[i].i = Elements2[i].j;
		Elements2[i].j = A;
	}
	Matrix M(this->Y, this->X, Elements2);
	return M;
}

Matrix Matrix::operator+ (const Matrix& Mat) const
{
	if ((this->X != Mat.X) || (this->Y != Mat.Y))
	{
		printf("error");
		return Matrix();
	}

	int N = 0;
	for (int i = 0; i < this->Elements.size(); i++)
		for (int j = 0; j < Mat.Elements.size(); j++)
		{
			if ((this->Elements[i].i == Mat.Elements[j].i) && (this->Elements[i].j == Mat.Elements[j].j))
				N++;
		}
	int K = this->Elements.size() + Mat.Elements.size() - N;
	List<ElementMatrix> Elements2(K);
	for (int i = 0; i < this->Elements.size(); i++)
	{
		Elements2[i] = this->Elements[i];
	}
    N = 0;
	for (int i = 0; i < Mat.Elements.size(); i++)
	{
		int j;
		for (j = 0; j < this->Elements.size(); j++)
		{
			if ((Mat.Elements[i].i == this->Elements[j].i) && (Mat.Elements[i].j == this->Elements[j].j))
			{
				Elements2[j].Value = Mat.Elements[i].Value + Elements[j].Value;
				break;
			}
		}
		if (j >= this->Elements.size())
		{
			Elements2[this->Elements.size() + N] = Mat.Elements[i];
			N++;
		}
	}
	return Matrix(this->X, this->Y, Elements2);
}
Matrix Matrix::operator- (const Matrix& Mat) const
{
	if ((X != Mat.X) || (Y != Mat.Y))
	{
		printf("error");
		return Matrix();
	}
	int N = 0;
	for (int i = 0; i < Elements.size(); i++)
		for (int j = 0; j < Mat.Elements.size(); j++)
		{
			if ((Elements[i].i == Mat.Elements[j].i) && (Elements[i].j == Mat.Elements[j].j))
				N++;
		}
	int K = Elements.size() + Mat.Elements.size() - N;
	List<ElementMatrix> Elements2(K);
	for (int i = 0; i < this->Elements.size(); i++)
	{
		Elements2[i] = Elements[i];
	}
	N = 0;
	for (int i = 0; i < Mat.Elements.size(); i++)
	{
		int j;
		for (j = 0; j < this->Elements.size(); j++)
		{
			if ((Mat.Elements[i].i == Elements[j].i) && (Mat.Elements[i].j == Elements[j].j))
			{
				Elements2[j].Value = Elements[j].Value - Mat.Elements[i].Value;
				break;
			}
		}
		if (j >= this->Elements.size())
		{
			Elements2[this->Elements.size() + N] = Mat.Elements[i];
			N++;
		}
	}
	return Matrix(this->X, this->Y, Elements2);
}
Matrix Matrix::operator* (const Matrix& Mat) const
{
	if (this->Y != Mat.X)
		return Matrix();

	bool** BM1 = BM1 = new bool*[this->X];
	for (int i = 0; i < this->X; i++)
	{
		BM1[i] = new bool[this->Y];
		for (int j = 0; j < this->Y; j++) BM1[i][j] = false;
	}

	bool** BM2 = BM2 = new bool*[Mat.X];
	for (int i = 0; i < Mat.X; i++) 
	{
		BM2[i] = new bool[Mat.Y];
		for (int j = 0; j < Mat.Y; j++) BM2[i][j] = false;
	}

	for (int i = 0; i < this->Elements.size(); i++)
		BM1[this->Elements[i].i-1][this->Elements[i].j-1] = true;

	for (int i = 0; i < Mat.Elements.size(); i++)
		BM2[Mat.Elements[i].i-1][Mat.Elements[i].j-1] = true;

	int size = 0;
	bool** BM3 = BM3 = new bool*[this->X];
	for (int i = 0; i < this->X; i++)
	{
		BM3[i] = new bool[Mat.Y];
		for (int j = 0; j < Mat.Y; j++)
		{
			BM3[i][j] = false;
			for (int k = 0; k < this->Y; k++)
			{
				if (BM1[i][k] && BM2[k][j] )
				{
					BM3[i][j] = true;  size++;  k = this->Y;
				}
			}
		}
	}
	if (size == 0) return Matrix(this->X, Mat.Y);
	int N = 0;
	List<ElementMatrix> Elements2(size);
	for (int i = 0; i < this->X; i++)
		for (int j = 0; j < Mat.Y; j++)
			if (BM3[i][j])
		{
			Elements2[N].i = i+1;
			Elements2[N].j = j+1;
			Elements2[N].Value = 0;
			N++;
		}

	for (int k = 0; k < size; k++)
		for (int i = 0; i < this->Elements.size(); i++)
			for (int j = 0; j < Mat.Elements.size(); j++)
				if ((this->Elements[i].j == Mat.Elements[j].i) && (Elements2[k].j == Mat.Elements[j].j) && (this->Elements[i].i == Elements2[k].i))
					Elements2[k].Value += this->Elements[i].Value * Mat.Elements[j].Value;

	return Matrix(this->X, Mat.Y, Elements2);
}
Matrix Matrix::operator* (const double& D) const
{
	List<ElementMatrix> Elements2(this->Elements.size());
	for (int i = 0; i < this->Elements.size(); i++)
			{
				Elements2[i].i = this->Elements[i].i;
				Elements2[i].j = this->Elements[i].j;
				Elements2[i].Value = this->Elements[i].Value * D;
			}
	return Matrix(this->X, this->Y, Elements2);
}
Matrix Matrix::operator/ (const double& D) const
{
	List<ElementMatrix> Elements2(this->Elements.size());
	for (int i = 0; i < this->Elements.size(); i++)
	{
		Elements2[i].i = this->Elements[i].i;
		Elements2[i].j = this->Elements[i].j;
		Elements2[i].Value = this->Elements[i].Value / D;
	}
	return Matrix(this->X, this->Y, Elements2);
}
Matrix operator*(const double& D, const Matrix& M)
{
	List<Matrix::ElementMatrix> Elements2(M.Elements.size());
	for (int i = 0; i < M.Elements.size(); i++)
	{
		Elements2[i].i = M.Elements[i].i;
		Elements2[i].j = M.Elements[i].j;
		Elements2[i].Value = M.Elements[i].Value * D;
	}
	return Matrix(M.X, M.Y, Elements2);
}

void Matrix::operator+= (const Matrix& Mat)
{
	if ((X != Mat.X) || (Y != Mat.Y))
	{
		printf("error");
		return;
	}

	int N = 0;
	for (int i = 0; i < Elements.size(); i++)
		for (int j = 0; j < Mat.Elements.size(); j++)
		{
			if ((Elements[i].i == Mat.Elements[j].i) && (Elements[i].j == Mat.Elements[j].j))
				N++;
		}
	int K = Elements.size() + Mat.Elements.size() - N;
	List<ElementMatrix> Elements2(K);
	for (int i = 0; i < Elements.size(); i++)
	{
		Elements2[i] = Elements[i];
	}
	N = 0;
	for (int i = 0; i < Mat.Elements.size(); i++)
	{
		int j;
		for (j = 0; j < Elements.size(); j++)
		{
			if ((Mat.Elements[i].i == Elements[j].i) && (Mat.Elements[i].j == Elements[j].j))
			{
				Elements2[j].Value = Mat.Elements[i].Value + Elements[j].Value;
				break;
			}
		}
		if (j >= Elements.size())
		{
			Elements2[Elements.size() + N] = Mat.Elements[i];
			N++;
		}
	}

	this->Elements = Elements2;
	Normalized();
}
void Matrix::operator-= (const Matrix& Mat)
{
	if ((X != Mat.X) || (Y != Mat.Y))
	{
		printf("error");
		return;
	}
	int N = 0;
	for (int i = 0; i < Elements.size(); i++)
		for (int j = 0; j < Mat.Elements.size(); j++)
		{
			if ((Elements[i].i == Mat.Elements[j].i) && (Elements[i].j == Mat.Elements[j].j))
				N++;
		}
	int K = Elements.size() + Mat.Elements.size() - N;
	List<ElementMatrix> Elements2(K);
	for (int i = 0; i < Elements.size(); i++)
	{
		Elements2[i] = Elements[i];
	}
	N = 0;
	for (int i = 0; i < Mat.Elements.size(); i++)
	{
		int j;
		for (j = 0; j < Elements.size(); j++)
		{
			if ((Mat.Elements[i].i == Elements[j].i) && (Mat.Elements[i].j == Elements[j].j))
			{
				Elements2[j].Value = Elements[j].Value - Mat.Elements[i].Value;
				break;
			}
		}
		if (j >= Elements.size())
		{
			Elements2[Elements.size() + N] = Mat.Elements[i];
			N++;
		}
	}


	this->Elements = Elements2;
	Normalized();
}
void Matrix::operator*= (const Matrix& Mat)
{
	if (this->Y != Mat.X)
		return;

	bool** BM1 = BM1 = new bool*[this->X];
	for (int i = 0; i < this->X; i++)
	{
		BM1[i] = new bool[this->Y];
		for (int j = 0; j < this->Y; j++) BM1[i][j] = false;
	}

	bool** BM2 = BM2 = new bool*[Mat.X];
	for (int i = 0; i < Mat.X; i++)
	{
		BM2[i] = new bool[Mat.Y];
		for (int j = 0; j < Mat.Y; j++) BM2[i][j] = false;
	}

	for (int i = 0; i < this->Elements.size(); i++)
		BM1[this->Elements[i].i - 1][this->Elements[i].j - 1] = true;
	for (int i = 0; i < Mat.Elements.size(); i++)
		BM2[Mat.Elements[i].i - 1][Mat.Elements[i].j - 1] = true;

	int size = 0;
	bool** BM3 = BM3 = new bool*[this->X];
	for (int i = 0; i < this->X; i++)
	{
		BM3[i] = new bool[Mat.Y];
		for (int j = 0; j < Mat.Y; j++)
		{
			BM3[i][j] = false;
			for (int k = 0; k < this->Y; k++)
			{
				if (BM1[i][k] && BM2[k][j])
				{
					BM3[i][j] = true;  size++;  k = this->Y;
				}
			}
		}
	}
	int N = 0;
	List<ElementMatrix> Elements2(size);
	for (int i = 0; i < this->X; i++)
		for (int j = 0; j < Mat.Y; j++)
			if (BM3[i][j])
			{
				Elements2[N].i = i + 1;
				Elements2[N].j = j + 1;
				Elements2[N].Value = 0;
				N++;
			}

	for (int k = 0; k < size; k++)
		for (int i = 0; i < this->Elements.size(); i++)
			for (int j = 0; j < Mat.Elements.size(); j++)
				if ((this->Elements[i].j == Mat.Elements[j].i) && (Elements2[k].j == Mat.Elements[j].j) && (this->Elements[i].i == Elements2[k].i))
					Elements2[k].Value += this->Elements[i].Value * Mat.Elements[j].Value;

	
	this->Elements = Elements2;
	Normalized();
}
void Matrix::operator*= (const double& D)
{
	for (int i = 0; i < this->Elements.size(); i++)
		this->Elements[i].Value *= D;
	Normalized();
}
void Matrix::operator/= (const double& D)
{
	for (int i = 0; i < this->Elements.size(); i++)
		this->Elements[i].Value /= D;
	Normalized();
}

Matrix& Matrix::operator++ ()
{
	for (int i = 0; i < this->Elements.size(); i++)
	{
		this->Elements[i].Value++;
	}
	Normalized();
	return *this;
}
Matrix& Matrix::operator-- ()
{
	for (int i = 0; i < this->Elements.size(); i++)
	{
		this->Elements[i].Value--;
	}
	Normalized();
	return *this;
}
Matrix Matrix::operator++ (const int)
{
	Matrix A(*this);
	for (int i = 0; i < this->Elements.size(); i++)
	{
		A.Elements[i] = this->Elements[i];
		this->Elements[i].Value++;
	}
	Normalized();
	return A;
}
Matrix Matrix::operator-- (const int)
{
	Matrix A(*this);
	for (int i = 0; i < this->Elements.size(); i++)
	{
		this->Elements[i].Value--;
	}
	Normalized();
	return A;
}

bool Matrix::operator== (const Matrix& M) const
{
	if (this->Elements.size() != M.Elements.size()) return false;

	bool* B = new bool[this->Elements.size()];
	for (int i = 0; i < Elements.size(); i++)
		B[i] = false;

	for (int i = 0; i < this->Elements.size(); i++)
		for (int j = 0; j < this->Elements.size(); j++)
		{
			if ((this->Elements[i].i == M.Elements[j].i)
				&& (this->Elements[i].j == M.Elements[j].j)
				&& (this->Elements[i].Value == M.Elements[j].Value))
			{
			 B[i] = true;
			}

		}

	for (int i = 0; i < this->Elements.size(); i++)
		if (B[i] == false)
		{
			return false;
		}
	return true;
}
bool Matrix::operator!= (const Matrix& M) const
{
	if (*this == M) return false;
	return true;
}

double& Matrix::operator()(const int A, const  int B)
{
	double S = 0;
	if ((this->X < A) || (this->Y < B)) return S;

	for (int i = 0; i < this->Elements.size(); i++)
		if ((this->Elements[i].i == A) && (this->Elements[i].j == B))
		{
			return Elements[i].Value;
		}
	ElementMatrix E;
	E.i = A;  
	E.j = B;
	E.Value = 0;
	this->Elements.Add(E);
	return this->Elements[this->Elements.size() - 1].Value;
}
double Matrix::operator()(const int A, const  int B) const
{
	double S = 0;
	if ((this->X < A) || (this->Y < B)) return S;

	for (int i = 0; i < this->Elements.size(); i++)
		if ((this->Elements[i].i == A) && (this->Elements[i].j == B))
		{
			return this->Elements[i].Value;
		}
	return S;
}
