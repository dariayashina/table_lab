#include "table.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int maxSize, step;
	cout << "Enter the maximum table size:" << endl;
	cin >> maxSize;
	cout << "Hash table step:" << endl;
	cin >> step;
	TScanTable* scan = new TScanTable(maxSize);
	TSortTable* sort = new TSortTable(maxSize);
	THashTable* hash = new THashTable(maxSize, step);
	TTreeTable* tree = new TTreeTable;
	TRecord rec;
	TKey key;
	TValue val;
	int op = 1;
	int tab_num = 1;
	int size;
	int r = 0;
	do
	{
		switch (op)
		{
		case 1: scan = new TScanTable(maxSize);
			sort = new TSortTable(maxSize);
			hash = new THashTable(maxSize, step);
			tree = new TTreeTable;
			cout << "Number of elements:" << endl;
			cin >> size;
			for (int i = 0; i < size; i++)
			{
				key = "";
				val = "";
				int j = 0;
				while (j < 3)
				{
					key += (rand() % 10 + '0');
					val += (rand() % 10 + '0');
					j++;
				}
				rec.SetKey(key);
				rec.SetValue(val);
				scan->InsRec(rec);
				sort->InsRec(rec);
				hash->InsRec(rec);
				tree->InsRec(rec);
			}
			break;

		case 2: cout << "Types of tables" << endl;
			cout << "1) ScanTable" << endl;
			cout << "2) SortTable" << endl;
			cout << "3) HashTable" << endl;
			cout << "4) TreeTable" << endl;
			cin >> tab_num;
			break;

		case 3: switch (tab_num)
			{
			case 1:
				cout << "ScanTable:" << endl;
				scan->Print();
				break;
			case 2:
				cout << "SortTable:" << endl;
				sort->Print();
				break;
			case 3:
				cout << "HashTable:" << endl;
				hash->Print();
				break;
			case 4:
				cout << "TreeTable:" << endl;
				tree->Print();
				break;
			default: cout << "Error" << endl;
			}
			  break;
		case 4: cout << "Enter the key:" << endl;
			cin >> key;
			switch (tab_num)
			{
			case 1:scan->ResetEff();
				if (scan->Find(key))
					cout << "Found : " << scan->GetCurr() << endl;
				else
					cout << "Not found" << endl;
				cout << "Eff = " << scan->GetEff() << endl;
				break;
			case 2: sort->ResetEff();
				if (sort->Find(key))
					cout << "Found : " << sort->GetCurr() << endl;
				else
					cout << "Not found" << endl;
				cout << "Eff = " << sort->GetEff() << endl;
				break;
			case 3: hash->ResetEff();
				if (hash->Find(key))
					cout << "Found : " << hash->GetCurr() << endl;
				else
					cout << "Not found" << endl;
				cout << "Eff = " << hash->GetEff() << endl;
				break;
			case 4: tree->ResetEff();
				if (tree->Find(key))
					cout << "Found : " << tree->GetCurr() << endl;
				else
					cout << "Not found" << endl;
				cout << "Eff = " << tree->GetEff() << endl;
				break;
			default: cout << "Error.Return enter" << endl;
			}
			break;

		case 5: cout << "Enter the item you want to insert" << endl;
			cin >> rec;
			switch (tab_num)
			{
			case 1: scan->ResetEff();
				scan->InsRec(rec);
				cout << "Eff = " << scan->GetEff() << endl;
				break;

			case 2: sort->ResetEff();
				sort->InsRec(rec);
				cout << "Eff = " << sort->GetEff() << endl;
				break;

			case 3: hash->ResetEff();
				hash->InsRec(rec);
				cout << "Eff = " << hash->GetEff() << endl;
				break;

			case 4: tree->ResetEff();
				tree->InsRec(rec);
				cout << "Eff = " << tree->GetEff() << endl;
				break;
			}
			break;

		case 6: cout << "Enter the item you want to delete:" << endl;
			cin >> key;
			switch (tab_num)
			{
			case 1: scan->ResetEff();
				scan->DelRec(key);
				cout << " " << scan->GetEff() << endl;
				break;
			case 2: sort->ResetEff();
				sort->DelRec(key);
				cout << "Eff =" << sort->GetEff() << endl;
				break;
			case 3: hash->ResetEff();
				hash->DelRec(key);
				cout << "Eff = " << hash->GetEff() << endl;
				break;
			case 4: tree->ResetEff();
				tree->DelRec(key);
				cout << "Eff = " << tree->GetEff() << endl;
				break;
			}
			break;

		case 7: break;

		default: cout << "invalid input" << endl;
		}
		cout << "operations" << endl;
		cout << "1)Filling in the table" << endl;
		cout << "2)Select the desired table view " << endl;
		cout << "3)Output table to the screen" << endl;
		cout << "4)Search" << endl;
		cout << "5)Insert" << endl;
		cout << "6)Delete" << endl;
		cout << "7)Exit" << endl;
		cin >> op;
	} while (op != 7);

	return 0;
}
