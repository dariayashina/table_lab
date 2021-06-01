#pragma once
template <class T>
class T_Stack
{
protected:
	int MaxSize;
	int Index;
	T* mas;
public:
	T_Stack(int len = 10)  //конструктор
	{
		if (len <= 0)
			throw len;
		MaxSize = len;
		Index = -1;
		mas = new T[MaxSize];
	};
	virtual ~T_Stack() { delete[] mas; };

	T_Stack(const T_Stack& s)  //конструктор копирования
	{
		MaxSize = s.MaxSize;
		Index = s.Index;
		mas = new T[MaxSize];
		for (int i = 0; i <= Index; i++)
			mas[i] = s.mas[i];
	};
	T_Stack& operator=(const T_Stack& s)  //оператор присваивания
	{
		if (MaxSize != s.MaxSize)
		{
			delete[] mas;
			MaxSize = s.MaxSize;
			mas = new T[MaxSize];
		}
		Index = s.Index;
		for (int i = 0; i <= Index; i++)
			mas[i] = s.mas[i];
		return *this;
	};
	bool IsEmpty() { return Index == -1; };  //проверка на пустоту стека

	bool IsFull() { return Index == MaxSize - 1; }  //проверка на заполненность стека

	T Top()  //чтение без удаления
	{
		if (Index == -1)
			throw Index;
		return mas[Index];
	}
	T Pop()  //чтение с удалением
	{
		if (Index == -1)
			throw Index;
		return mas[Index--];
	}
	void Push(const T n) //запись в стек
	{
		if (Index == MaxSize - 1)
			throw Index;
		mas[++Index] = n;
	}
	void Clear()  //очистка стека
	{
		Index = -1;
	}
};
