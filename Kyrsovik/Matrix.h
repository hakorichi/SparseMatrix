#pragma once
#include "List.cpp"
using namespace std;

class Matrix
{   
private:
	struct ElementMatrix
	{
	public:
		int i;
		int j;
		double Value;
	};
	int X;
	int Y;
	List<ElementMatrix> Elements;
	void Normalized();
	Matrix(const int, const int, const List<ElementMatrix>&);

public:
	Matrix();
	Matrix(const Matrix&);
	Matrix(const int);
	Matrix(const int, const int);
	~Matrix();
	void operator=(const Matrix&);

	void Scanf();
	void Printf() const;
	void ScanfElements();
	void PrintfMatrix() const;

	Matrix transpose() const;
	Matrix operator+ (const Matrix&) const;
	Matrix operator- (const Matrix&) const;
	Matrix operator* (const Matrix&) const;
	Matrix operator* (const double&) const;
	Matrix operator/ (const double&) const;
	friend Matrix operator*(const double&,const Matrix&);

	void operator+= (const Matrix&);
	void operator-= (const Matrix&);
	void operator*= (const Matrix&);
	void operator*= (const double&);
	void operator/= (const double&);

	Matrix& operator++();
	Matrix& operator--();
	Matrix operator++ (const int);
	Matrix operator-- (const int);

	bool operator== (const Matrix&) const;
	bool operator!= (const Matrix&) const;

	double& operator()(const int, const int);
	double  operator()(const int, const int) const;
};

