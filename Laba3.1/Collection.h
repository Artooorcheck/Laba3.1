#pragma once
#include "Node.h"
#include <list>
#include<functional>
#include<algorithm>
#include<string>

struct Filter
{
	std::string param;
	std::string value;
	Filter(std::string param, std::string value)
	{
		this->param = param;
		this->value = value;
	}
};

template<typename T, typename = std::enable_if_t<std::is_base_of_v<Node, T>>>
class Bank
{
	std::list<Node*> accounts;
	std::string db = "saveData.txt";
	std::list<std::list<Node*>::iterator> selected;
	std::string login = "Admin";
	std::string password = "Admin";


	std::list<Filter> ParsReq(std::string req)
	{
		std::vector<std::string> coef = Split(req, " AND ");

		std::list<Filter> filters;
		for (auto i : coef)
		{
			std::vector<std::string> coe = Split(i, "=");
			filters.push_back(Filter(Trim(ToLower(coe[0]), " "), Trim(coe[1], " ")));
		}
		return filters;
	}

	static bool CheckParams(Node* elem, std::list<Filter>& filters)
	{
		for (Filter f : filters)
		{
			if (!elem->CheckField(f.param, f.value))
				return false;
		}
		return true;
	}

	void SetField(std::list<Node*>::iterator elem, std::list<Filter>& newData)
	{
		for (Filter f : newData)
		{
			(*elem)->SetField(f.param, f.value);
		}
	}

	void Print(std::ostream& stream, std::list<std::list<Node*>::iterator>::iterator begin, std::list<std::list<Node*>::iterator>::iterator end)
	{
		for (auto i = begin; i != end; i++)
		{
			(**i)->Print(stream);
		}
	}

	void Print(std::ostream& stream, std::list<Node*>::iterator begin, std::list<Node*>::iterator end)
	{
		for (auto i = begin; i != end; i++)
		{
			i->Print(stream);
		}
	}

	void Search(std::list<Filter> filters)
	{
		for (auto i = accounts.begin(); i != accounts.end(); i++)
		{
			if (CheckParams(*i, filters))
				selected.push_back(i);
		}
	}

public:

	bool CheckRoot(std::string login, std::string password)
	{
		return login == this->login && password == this->password;
	}

	void Read()
	{
		Read(db);
	}

	void Read(std::string fileName)
	{
		std::ifstream file(fileName);
		while (file)
		{
			std::string str;
			std::getline(file, str, ';');
			if (!file.fail())
			{
				Node* obj = new T();
				obj->ParseString(str);
				accounts.push_front(obj);
			}
			auto y = 1;
		}

		file.close();
	}

	void Print(std::ostream& stream)
	{
		for (Node* elem : accounts)
		{
			elem->Print(stream);
		}
	}

	void PrintSelected(std::ostream& stream)
	{
		Print(stream, selected.begin(), selected.end());
	}

	void Add(T* elem)
	{
		accounts.push_back(elem);
	}

	void Remove()
	{
		auto i = selected.end();

		do
		{
			i--;
			accounts.erase(*i);
		} while (i != selected.begin());

		selected.clear();
	}

	std::list<T> Select(std::string req)
	{
		std::list<Filter> filters = ParsReq(req);
		selected.clear();

		Search(filters);
		return GetSelected();
	}

	void Update(std::string req)
	{
		std::list<Filter> newData = ParsReq(req);
		for (auto i = selected.begin(); i != selected.end(); i++)
		{
			SetField(*i, newData);
		}
	}

	std::list<T> GetSelected()
	{
		std::list<T> res;
		for (auto i : selected)
		{
			T* e = dynamic_cast<T*>(*i);
			res.push_back(*e);
		}
		return res;
	}

	void SaveFile(std::string fileName)
	{
		std::ofstream file(fileName);

		for (Node* acc : accounts)
		{
			file << acc->GetString() + ';';
		}

		file.close();
	}

	~Bank()
	{
		SaveFile(db);
		for (auto elem : accounts)
		{
			delete elem;
		}
	}
};
