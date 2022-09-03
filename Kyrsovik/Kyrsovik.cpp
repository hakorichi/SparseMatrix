// Kyrsovik.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Matrix.h"
#include "List.cpp"


int _tmain(int argc, _TCHAR* argv[])
{

	Matrix M(7);
	Matrix M1(4);
	Matrix M2(5);

	++M;
	M1 = M;
	if (M++ == M1) printf("+\n");
	if (M == ++M1) printf("+\n");
	--M;
	M--;

	M *= 2;
	M.PrintfMatrix();
	M.Printf();

	M1 = --M1 * Matrix(7);
	M1.PrintfMatrix();
	M1.Printf();

	M.PrintfMatrix();
	M.Printf();

	Matrix M4 = Matrix(4) - Matrix(4);
	M4.PrintfMatrix();
	M4.Printf();

	M4(1, 2) = 4;
	M4(1, 1) = 7;
	M4(3, 2) = 4;
	M4(2, 1) = 7;
	M4(4, 2) = 4;
	M4.PrintfMatrix();
	M4.Printf();

	return 1;
}

