#pragma once
#include<iostream>
#include<fstream>
#include<algorithm>
#include<stack>
#include <string>
#include"stack.h"
using namespace std;

#ifndef _T_RECORD_H_
#define _T_RECORD_H_

typedef string TKey;
typedef string TValue;

class TRecord
{
private:
	TKey key;//ключ записи
	TValue val;//указатель на значение
public:
	TRecord(TKey k = "", TValue v = "")//конструктор
	{
		key = k;
		val = v;
	}
	void SetKey(TKey k)//установить значение ключа
	{
		key = k;
	}
	void SetValue(TValue v)//установить указатель на данные
	{
		val = v;
	}
	TKey GetKey()//получить значение ключа
	{
		return key;
	}
	TValue GetValue()//получить указатель на данные
	{
		return val;
	}

	bool operator==(const TRecord& rec) { return this->key == rec.key; };//сравнение =
	bool operator<(const TRecord& rec) { return this->key < rec.key; };//сравнение <
	bool operator>(const TRecord& rec) { return this->key > rec.key; };//сравнение >
	TRecord& operator=(const TRecord& rec);//присваивание

	friend istream& operator>>(istream& is, TRecord& rec);
	friend ostream& operator<<(ostream& os, const TRecord& rec);
};
#endif

#ifndef _T_TABLE_H_
#define _T_TABLE_H_

class TTable
{
protected:
	int DataCount;//количество записей в таблице
	int Eff;//показатель эффективности выполнения операции
public:
	TTable() { DataCount = 0; Eff = 0; };//конструктор
	virtual ~TTable() {};//деструктор
	//информационные методы
	int GetDataCount() const { return DataCount; };//количество записей
	int GetEff() const { return Eff; };//эффективность
	void ResetEff() { Eff = 0; };//сброс эффективности
	bool IsEmpty() { return DataCount == 0; };//пуста?
	virtual bool IsFull() = 0;//заполнена?
	//основные методы
	virtual bool Find(TKey key) = 0;//найти запись
	virtual void DelRec(TKey key) = 0;//удалить запись
	virtual void InsRec(TRecord rec) = 0;//вставить запись
	//навигация
	virtual void Reset() = 0;//установить на первую запись
	virtual void GoNext() = 0;//переход к следующей записи
	virtual bool IsEnd() = 0;//таблица завершена?

	virtual TRecord GetCurr() = 0;
	void Print();//печать
};
#endif
#ifndef _T_ARRAY_TABLE_H_
#define _T_ARRAY_TABLE_H_

class TArrayTable :public TTable
{
protected:
	TRecord* pRec;//память для записей таблицы
	int curr;//номер текущей записи( нумерация с 0)
	int maxSize;//максимально возможное количество записей в таблице
	std::size_t size;

public:
	TArrayTable(int size);//конструктор
	virtual ~TArrayTable() {};//деструктор
	//информационные метода
	virtual bool IsFull() { return maxSize == DataCount; };//заполнена?
	virtual TRecord GetCurr() { return pRec[curr]; };//получить номер текущей записи
	int GetMaxSize() const { return maxSize; };//количество записей
	 //навигация
	virtual void Reset() { curr = 0; }//установить на первую запись
	virtual void GoNext() { curr++; }//переход к следующей записи
	virtual bool IsEnd() { return curr == DataCount; };//таблица завершена?

	std::size_t GetSize() const;
};
#endif
#ifndef _T_SCAN_TABLE_H_
#define _T_SCAN_TABLE_H_

class TScanTable :public TArrayTable
{
public:
	TScanTable(int size = 0) :TArrayTable(size) {};//констуктор
	virtual ~TScanTable() {};//деструктор
	//основные методы
	virtual bool Find(TKey key);//найти запись
	virtual void InsRec(TRecord rec);//вставить запись
	virtual void DelRec(TKey key);//удалить запись
};
#endif
#ifndef _T_SORT_TABLE_H_
#define _T_SORT_TABLE_H_

class TSortTable :public TArrayTable
{
private:
	void SortInsert();//сортировка вставка
	void SortHoar(int start, int end, TKey mid);//

public:
	TSortTable(int size = 0) :TArrayTable(size) {};//конструктор
	TSortTable(TScanTable& sc_tab);//из просматриваемой таблицы
	virtual ~TSortTable() {};//деструктор
	//основные методы
	virtual bool Find(TKey key);//найти запись
	virtual void InsRec(TRecord rec);//вставить запись
	virtual void DelRec(TKey key);//удалить запись

};
#endif
#ifndef _T_TREE_NODE_H_
#define _T_TREE_NODE_H_

class TTreeNode
{
public:
	TRecord rec;
	TTreeNode* pLeft, * pRight;//указатели на поддеревья

	TTreeNode(TRecord _rec, TTreeNode* pL = NULL, TTreeNode* pR = NULL)
	{
		rec = _rec;
		pLeft = pL;
		pRight = pR;
	};//конструктор
	~TTreeNode() {};//деструктор
	TRecord GetRec() const;
	void InsRec(const TRecord& r);
};
#endif

#ifndef _T_TREE_TABLE_H_
#define _T_TREE_TABLE_H_

class TTreeTable :public TTable
{
protected:
	TTreeNode* pRoot;//указатель на корень дерева
	TTreeNode* pCurr;//указатель на текущую вершину 
	TTreeNode* pPrev;//указатель на предыдущую вершину
	T_Stack <TTreeNode*> st;//стек для интератора
	TTreeNode** pRef;//адрес указателя на вершину-результата в FindRecord
	int pos;//номер текущей	 вершины

public:
	TTreeTable() :TTable(), st(100)
	{
		pRoot = NULL;
		pCurr = NULL;
		pRef = NULL;
	}
	virtual ~TTreeTable() {
		if (pRoot)
		{
			while (!st.IsEmpty())
				st.Pop();
			pCurr = pRoot;
			st.Push(pCurr);
			while (!st.IsEmpty())
			{
				pCurr = st.Top();
				st.Pop();
				if (pCurr->pLeft)
					st.Push(pCurr->pLeft);
				else if (pCurr->pRight)
					st.Push(pCurr->pRight);
				delete pCurr;
			}
		}
	}//деструктор
	//информационные методы
	virtual bool IsFull() { return false; };//заполнена?
	//основные методы
	virtual bool Find(TKey key);//найти запись
	virtual void InsRec(TRecord rec);//вставить запись
	virtual void DelRec(TKey key);//удалить запись
	//навигация
	virtual void Reset();//установить на первую запись
	virtual void GoNext();//переход к следующей записи
	virtual bool IsEnd() { return pos == DataCount; };//таблица завершена?
	virtual TRecord GetCurr() { return pCurr->rec; };//

};
#endif
#ifndef _T_HASH_TABLE_H_
#define _T_HASH_TABLE_H_

class THashTable :public TTable
{
protected:
	int HashFunc(TKey key);

	int maxSize;//максимально возможное количество записей
	int curr;//строка памяти при завершении поиска
	int step;//шаг вторичного перемешивания
	int free; //первая свободная строка, обнаруженная при поиске
	TRecord* pRec;//память для записей таблицы

public:
	THashTable(int _size = 0, int _step = 0);//конструктор
	virtual ~THashTable() { delete[] pRec; pRec = NULL; };//деструктор
	//информационные методы
	virtual bool IsFull() { return maxSize == DataCount; };//заполнена?
	//основные методы
	virtual bool Find(TKey key);//найти запись
	virtual void InsRec(TRecord rec);//вставить запись
	virtual void DelRec(TKey key);//удалить запись
	//навигация
	virtual void Reset();//установить на первую запись
	virtual void GoNext();//переход к следующей записи
	virtual bool IsEnd() { return curr == maxSize; };//таблица завершена?
	virtual TRecord GetCurr() { return pRec[curr]; };
};
#endif
