#pragma once
#include "stdafx.h"

template<class Type>
class List
{
private:
	Type* Elements;
	int Size;

public:
	List()
	{
		this->Size = 0;
		this->Elements = NULL;
	}
	List(const int size)
	{
		this->Size = size;
		this->Elements = new Type [this->Size];
	}
	List(const List& L)
	{
		this->Size = L.Size;
		this->Elements = new Type[this->Size];

		for (int i = 0; i < this->Size; i++)
		{
			this->Elements[i] = L.Elements[i];
		}
	}
	~List()
	{
		delete[] this->Elements;
	}

	List operator=(const List& L)
	{
		delete[] this->Elements;
		this->Size = L.Size;
		this->Elements = new Type[this->Size];

		for (int i = 0; i < this->Size; i++)
		{
			this->Elements[i] = L.Elements[i];
		}
		return *this;

	}
	void Add(const Type& Element)
	{
		Type* Elements2 = new Type[this->Size];
		for (int i = 0; i < this->Size; i++)
		{
			Elements2[i] = this->Elements[i];
		}
		if (this->Elements != NULL) delete[] this->Elements;

		this->Elements = new Type[this->Size + 1];
		for (int i = 0; i < this->Size; i++)
		{
			this->Elements[i] = Elements2[i];
		}

		this->Elements[this->Size++] = Element;
	}
	void Delete(const int K)
	{
		if ((K < this->Size) && (K >= 0))
		{
			Type* Elements2 = new Type[this->Size];

			for (int i = 0; i < this->Size; i++)
			{
				Elements2[i] = this->Elements[i];
			}
			if (this->Elements != NULL ) delete[] this->Elements;

			if (this->Size > 1)
			{
				int j = 0;
				this->Elements = new Type[--this->Size];
				for (int i = 0; i <this->Size; i++)
				{
					if (K == i) j++;
					this->Elements[i] = Elements2[i + j];
				}
			}
			else
			{
				this->Elements = NULL;
			    this->Size = 0;
			}
		}
	}

	int size() const
	{
		return Size;
	}
	Type& operator[](const int K)
	{
		if ((K < this->Size) && (K >= 0))
			return this->Elements[K];
	}
	Type operator[](const int K) const
	{
		if ((K < this->Size) && (K >= 0))
			return this->Elements[K];
	}
};