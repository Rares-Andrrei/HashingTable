#include <iostream>
#include <array>
#include <list>
#include<fstream>
class HashTable
{
private:
	int size = 0;
	int elemente = 0;
	std::list<std::pair<int, int>>* table;
public:
	HashTable(int size = 30)
	{
		this->size = size;
		table = new std::list<std::pair<int, int>>[size];
	}
	void insert(std::pair<int, int> x)
	{
		int key = x.first;
		int val = x.second;
		float factorIncarcare = float(elemente + 1) / float(size);
		if (factorIncarcare > 1.0)
		{
			int oldSize = size;
			size *= 2;
			std::list<std::pair<int, int>>* table2 = new std::list<std::pair<int, int>>[size];
			for (int i = 0; i < oldSize; i++)
			{
				while (table[i].size())
				{
					table2[hash(table[i].front().first)].push_back(table[i].front());
					table[i].pop_front();
				}
			}
			delete[] table;
			table = table2;	
		}
		std::pair<int, int> aux = {key, val};
		table[hash(key)].push_back(aux);
		elemente++;
	}
	std::pair<int, int> find(int key)
	{
		if (table[hash(key)].size())
		{
			for (auto it = table[hash(key)].begin(); it != table[hash(key)].end(); ++it)
			{
				if (it->first == key)
				{
					return *it;
				}
			}
		}
		std::pair<int, int> aux= { NULL,NULL };
		return aux;
	}
	void erase(int key)
	{
		std::pair<int, int> aux = find(key);
		if (aux.first != NULL && aux.second != NULL)
		{
			table[hash(aux.first)].remove(aux);
			elemente--;
		}
	}
	int hash(int val)
	{
		return val % size;
	}
	~HashTable()
	{
		delete[] table;
	}
	void afisareTable()
	{
		for (int i = 0; i < size; i++)
		{
			std::list < std::pair<int, int>> aux = table[i];
			while (!aux.empty())
			{
				std::cout << i << " " << aux.front().first << " " << aux.front().second << std::endl;
				aux.pop_front();
			}
		}
	}
};


class HashTableStr
{
private:
	int size = 0;
	int elemente = 0;
	std::list<std::pair<std::string, int>>* table;
public:
	HashTableStr(int size = 30)
	{
		this->size = size;
		table = new std::list<std::pair<std::string, int>>[size];
	}
	void insert(std::pair<std::string, int> x)
	{
		std::string key = x.first;
		int val = x.second;
		float factorIncarcare = float(elemente + 1) / float(size);
		if (factorIncarcare > 1.0)
		{
			int oldSize = size;
			size *= 2;
			std::list<std::pair<std::string, int>>* table2 = new std::list<std::pair<std::string, int>>[size];
			for (int i = 0; i < oldSize; i++)
			{
				while (table[i].size())
				{
					table2[hashCaractere(table[i].front().first)].push_back(table[i].front());
					table[i].pop_front();
				}
			}
			delete[] table;
			table = table2;
		}
		std::pair<std::string, int> aux = { key, val };
		table[hashCaractere(key)].push_back(aux);
		elemente++;
	}
	std::pair<std::string, int> find(std::string key)
	{
		if (table[hashCaractere(key)].size())
		{
			for (auto it = table[hashCaractere(key)].begin(); it != table[hashCaractere(key)].end(); ++it)
			{
				if (it->first == key)
				{
					return *it;
				}
			}
		}
		std::pair<std::string, int> aux = { NULL,NULL };
		return aux;
	}
	void erase(std::string key)
	{
		std::pair<std::string, int> aux = find(key);
		if (!aux.first.empty() && aux.second != NULL)
		{
			table[hashCaractere(aux.first)].remove(aux);
			elemente--;
		}
	}
	int hashCaractere(std::string key)
	{
		int val = 0;
		for (char i : key)
		{
			val += i;
		}
		return val % size;
	}
	void afisareTable()
	{
		for (int i = 0; i < size; i++)
		{
			std::list < std::pair<std::string, int>> aux = table[i];
			while (!aux.empty())
			{
				std::cout << i << " " << aux.front().first << " " << aux.front().second << std::endl;
				aux.pop_front();
			}
		}
	}
};



int main()
{
	std::string numeFis;
	std::cout << "Introdu numele fisierului: ";
	std::cin >> numeFis;
	std::fstream file;
	file.open(numeFis);
	if (!file.is_open())
	{
		return 0;
	}
	int n;
	file >> n;
	HashTable T(n);
	std::pair<int, int> aux;
	for (int i = 0; i < n; i++)
	{
		file >> aux.first;
		file >> aux.second;
		T.insert(aux);
	}
	bool start = true;
	std::cout << "0 - exit, 1 - adauga element, 2 - sterge element, 3 - cauta element\n";
	int optiune;
	while (start)
	{

		std::cin >> optiune;
		if (optiune == 0)
		{
			start = false;
		}
		else if (optiune == 1)
		{
			int key, val;
			std::cout << "key = ";
			std::cin >> key;
			std::cout << "val = ";
			std::cin >> val;
			std::pair<int, int> aux = { key, val };
			T.insert(aux);
			std::cout << "Adaugare realizata cu succes!\n";
		}
		else if (optiune == 2)
		{
			int key, val;
			std::cout << "key = ";
			std::cin >> key;
			T.erase(key);
			std::cout << "Stergere realizata cu succes!\n";
		}
		else if (optiune == 3)
		{
			int key, val;
			std::cout << "key = ";
			std::cin >> key;
			std::pair<int, int> aux = T.find(key);
			if (aux.first == NULL && aux.second == NULL)
			{
				std::cout << "Elementul nu exista!\n";
			}
			else
			{
				std::cout << "Elementul cu key = " << key << " are valoarea " << aux.second << std::endl;
			}
		}
		else
		{
			std::cout << "Comanda invlaida!\n";
		}
	}
	file.close();
	return 0;
}