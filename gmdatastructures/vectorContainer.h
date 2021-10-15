#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class VectorContainer {
private:
	vector<vector<string>*> container;
	
public:
	int container_addVector()
	{
		int id = container.size();
		container.push_back(new vector<string>);
		return id;
	}

	bool vvec_pushBack(int index, string value)
	{
		vector<string>* res = container_search(index);
		
		if (!res) // vector not found
		{
			cout << "Cannot push back: Vector not found! ("<<index<<") " << endl;
			return false;
		}


		res->push_back(value);
		cout << "Successfully added " << value << " to vector " << index << endl;
		return true;
	}

	int vvec_getSize(int index)
	{
		vector<string>* res = container_search(index);

		if (!res)
		{
			cout << "Vector not found " << index << endl;
			return -1;
		}

		return res->size();
	}

	string vvec_at(int index, int position)
	{
		vector<string>* res = container_search(index);

		if (!res)
		{
			cout << "Vector not found " << index << endl;
			return "";
		}

		if (position > res->size())
		{
			cout << "Vector index OOB " << index << endl;
			return "";
		}

		return res->at(position);
	}

	bool vvec_popBack(int index)
	{
		vector<string>* res = container_search(index);
		if (!res)
		{
			cout << "Vector not found " << index << endl;
			return false;
		}

		if (res->empty())
		{
			cout << "Vector already empty " << index << endl;
			return false;
		}

		res->pop_back();
		return true;
	}

	bool vvec_erase(int index, int position)
	{
		vector<string>* res = container_search(index);
		if (!res)
		{
			cout << "Vector not found " << index << endl;
			return false;
		}

		if (res->empty())
		{
			cout << "Vector already empty " << index << endl;
			return false;
		}

		if (res->size() < position)
		{
			cout << "Vector position OOB" << index << endl;
			return false;
		}

		res->erase(res->begin() + position);
		return true;
	}

	bool vvec_insert(int index, int position, string value)
	{
		vector<string>* res = container_search(index);
		if (!res)
		{
			cout << "Vector not found " << index << endl;
			return false;
		}

		if (position >= res->size())
		{
			position = res->size()-1;
		}

		res->insert(res->begin() + position, value);
		return true;
	}

	vector<string>* container_search(int id)
	{
		if (id > container.size())
		{
			cout << "Could not find vector with id " << id << endl;
			return nullptr;
		}
		else
		{
			return container.at(id);
		}

	}


};