#include "table.h"

TRecord& TRecord::operator=(const TRecord& rec)
{
	this->key = rec.key;
	this->val = rec.val;
	return *this;
}


istream& operator>>(istream& is, TRecord& rec)
{
	string _key, _val;
	is >> _key;
	is >> _val;
	rec.key = _key;
	rec.val = _val;
	return is;
}

ostream& operator<<(ostream& os, const TRecord& rec)
{
	string _key = rec.key;
	string _val = rec.val;
	os << " " << _key << "   | " << _val << "   | " << " " << endl;
	return os;
}

void TTable::Print()
{
	cout << "_______|________" << endl;
	for (Reset(); !IsEnd(); GoNext())
	{
		cout << GetCurr();
	}
	cout << "_______|_______" << endl;
}

TArrayTable::TArrayTable(int size)
{
	maxSize = size;
	pRec = new TRecord[maxSize];
	curr = -1;
	DataCount = 0;
	Eff = 0;
}

std::size_t TArrayTable::GetSize()const {
	return size;
}

bool TScanTable::Find(TKey key)
{
	bool fl(false);
	curr = DataCount;
	for (int i = 0; i < DataCount; i++)
	{
		Eff++;
		if (pRec[i].GetKey() == key)
		{
			fl = true;
			curr = i;
			break;
		}
	}
	return fl;

}

void TScanTable::InsRec(TRecord rec)
{
	if (IsFull())
	{
		throw 0;
	}
	if (!Find(rec.GetKey()))
	{
		pRec[curr] = rec;
		DataCount++;
		Eff++;
	}
	else
	{
		cout << " Entry is  in the table" << endl;
	}
}

void TScanTable::DelRec(TKey key)
{
	if (IsEmpty())
	{
		throw 0;
	}
	if (Find(key))
	{
		pRec[curr] = pRec[DataCount - 1];
		DataCount--;
		Eff++;
	}
	else
	{
		cout << "There is no entry in the table" << endl;
	}
}

bool TSortTable::Find(TKey key)
{
	int left = 0, right = DataCount - 1;
	int pos;
	while (left <= right)
	{
		Eff++;
		pos = (std::size_t)((left + right) * 0.5);
		if (pRec[pos].GetKey() == key)
		{
			curr = pos;
			return true;
		}
		else if (pRec[pos].GetKey() > key)
			right = pos - 1;
		else
			left = pos + 1;
	}
	curr = left;
	return false;
}

void TSortTable::InsRec(TRecord rec)
{
	if (IsFull())
	{
		throw - 1;
	}
	if (!Find(rec.GetKey()))
	{
		for (int pos = DataCount; pos > curr; pos--)
		{
			pRec[pos] = pRec[pos - 1];
			Eff++;
		}
		pRec[curr] = rec;
		DataCount++;
	}
	else
	{
		cout << " Entry is  in the table" << endl;
	}
}

void TSortTable::DelRec(TKey key)
{
	if (IsEmpty())
	{
		throw - 1;
	}
	if (Find(key))
	{
		for (int pos = curr; pos < DataCount - 1; pos++)
		{
			pRec[pos] = pRec[pos + 1];
			Eff++;
		}
		DataCount--;
	}
	else
	{
		cout << "There is no entry in the table" << endl;
	}
}

void TSortTable::SortInsert()
{
	TRecord _curr;
	for (int i = 1; i < DataCount; i++)
	{
		_curr = pRec[i];
		for (int j = 0; j < i; j++)
		{
			if (pRec[j] > _curr)
			{
				for (int k = i; k > j; k--)
					pRec[k] = pRec[k - 1];
				pRec[j] = _curr;
				break;
			}
		}
	}
}

void TSortTable::SortHoar(int start, int end, TKey mid)
{
	int st = start, en = end;
	while (st < en)
	{
		if (pRec[st].GetKey() < mid)
			st++;
		else if (pRec[en].GetKey() > mid)
			en--;
		else
		{
			TKey tmp = pRec[st].GetKey();
			pRec[st].SetKey(pRec[en].GetKey());
			pRec[en].SetKey(tmp);
		}
	}
	TKey mid1 = pRec[(st + start) / 2].GetKey();
	TKey mid2 = pRec[(en + end) / 2].GetKey();
	if (st - start > 1)
		SortHoar(start, st, mid1);
	if (end - en > 1)
		SortHoar(en, end, mid2);
}

TSortTable::TSortTable(TScanTable& sc_tab) : TArrayTable(sc_tab.GetMaxSize())
{
	int i = 0;
	for (sc_tab.Reset(); !sc_tab.IsEnd(); sc_tab.GoNext())
	{
		pRec[i] = sc_tab.GetCurr();
		i++;
		DataCount++;
	}
	SortHoar(0, DataCount - 1, pRec[DataCount / 2].GetKey());
}

TRecord TTreeNode::GetRec() const
{
	return rec;
}
void TTreeNode::InsRec(const TRecord& r)
{
	rec = r;
}

bool TTreeTable::Find(TKey key)
{
	pCurr = pRoot;
	pRef = &pRoot;
	while (pCurr != NULL)
	{
		Eff++;
		if (pCurr->rec.GetKey() == key)
			return true;
		if (pCurr->rec.GetKey() < key)
			pRef = &(pCurr->pRight);
		else
			pRef = &(pCurr->pLeft);
		pCurr = *pRef;
	}
	return false;
}

void TTreeTable::InsRec(TRecord rec)
{
	if (!Find(rec.GetKey()))
	{
		TTreeNode* tmp = new TTreeNode(rec);
		*pRef = tmp;
		DataCount++;
		Eff++;
	}
	else
	{
		cout << " Entry is  in the table" << endl;
	}
}

void TTreeTable::DelRec(TKey key)
{
	if (IsEmpty())
		throw 0;
	if (!Find(key))
	{
		cout << "There is no entry in the table" << endl;
		return;
	}
	TTreeNode* p = *pRef;
	if ((*pRef)->pLeft != NULL || (*pRef)->pRight != NULL)
	{
		if ((*pRef)->pLeft == NULL)
			*pRef = (*pRef)->pRight;
		else if ((*pRef)->pRight == NULL)
			*pRef = (*pRef)->pLeft;
		else
		{
			TTreeNode** tmp = &((*pRef)->pLeft);
			(*pRef)->rec = (*tmp)->rec;
			p = *tmp;
			while ((*tmp)->pRight != NULL)
			{
				tmp = &((*tmp)->pRight);
				Eff++;
				(*pRef)->rec = (*tmp)->rec;
				p = *tmp;
			}
			*tmp = (*tmp)->pLeft;
		}
	}
	else
		*pRef = NULL;
	delete p;
	DataCount--;
	Eff++;
}

void TTreeTable::Reset()
{
	pCurr = pRoot;
	st.Clear();
	pos = 0;
	while (pCurr != NULL)
	{
		st.Push(pCurr);
		pCurr = pCurr->pLeft;
	}
	pCurr = st.Pop();
}

void TTreeTable::GoNext()
{
	if (pCurr != NULL)
	{
		pos++;
		pCurr = pCurr->pRight;
		while (pCurr != NULL)
		{
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
		if (!st.IsEmpty())
			pCurr = st.Pop();
	}
}

int THashTable::HashFunc(TKey key)
{
	int k = 1, R = 0;
	for (int i = 0; i < key.length(); i++)
	{
		R += key[i] * k;
		k *= 2;
	}
	return R;
}

THashTable::THashTable(int _size, int _step)
{
	maxSize = _size;
	step = _step;
	pRec = new TRecord[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		pRec[i].SetKey("");
		pRec[i].SetValue("");
	}
	curr = -1;
	DataCount = 0;
	Eff = 0;
}

bool THashTable::Find(TKey key)
{
	curr = HashFunc(key) % maxSize;
	free = -1;
	for (int i = 0; i < maxSize; i++)
	{
		Eff++;
		if (pRec[curr].GetKey() == key)
			return true;
		if (pRec[curr].GetKey() == "&" && free == -1)
			free = curr;
		if (pRec[curr].GetKey() != "")
		{
			curr = (step + curr) % maxSize;
		}
		else break;
	}
	if (free != -1)
		curr = free;
	return false;
}

void THashTable::InsRec(TRecord rec)
{
	if (IsFull())
		throw 0;
	if (!Find(rec.GetKey()))
	{
		pRec[curr] = rec;
		DataCount++;
		Eff++;
	}
	else
	{
		cout << " Entry is  in the table" << endl;
	}
}

void THashTable::DelRec(TKey key)
{
	if (IsEmpty())
		throw 0;
	if (Find(key))
	{
		pRec[curr].SetKey("&");
		DataCount--;
		Eff++;
	}
	else
	{
		cout << "There is no entry in the table" << endl;
	}
}

void THashTable::Reset()
{
	curr = 0;
	while (curr < maxSize && (pRec[curr].GetKey() == "&" || pRec[curr].GetKey() == ""))
		curr++;
}

void THashTable::GoNext()
{
	curr++;
	while (curr < maxSize && (pRec[curr].GetKey() == "&" || pRec[curr].GetKey() == ""))
		curr++;
}

