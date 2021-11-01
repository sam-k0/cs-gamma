#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#define csvec vector<string>* 

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

	void container_cleanUp()
	{
		for (auto vec : container)
		{
			delete vec;
		}
		cout << "Cleaned all vectors!" << endl;
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

		cout << "Vector " << index << " has " << res->size() << " elements" << endl;
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

		if (position >= (int)res->size())
		{
			cout << "Vector index OOB " << index << endl;
			return "";
		}

		cout << "Vector " << index << " at position " << position << " has value: " << res->at(position) << endl;
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

		cout << "Popped last element of vec " << index << endl;
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

		if ((int)res->empty())
		{
			cout << "Vector already empty " << index << endl;
			return false;
		}

		if ((int)res->size() < position)
		{
			cout << "Vector position OOB" << index << endl;
			return false;
		}

		res->erase(res->begin() + position);
		cout << "Successfully removed element from vec " << index << " at pos " << position << endl;
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

		if (position >= (int)res->size())
		{
			position = (int)res->size()-1;
		}

		res->insert(res->begin() + position, value);
		cout << "Successfully inserted " << value << " in vec " << index << " at pos " << position << endl;
		return true;
	}

	vector<string>* container_search(int id)
	{
		if (id > (int)container.size())
		{
			cout << "Could not find vector with id " << id << endl;
			return nullptr;
		}
		else
		{
			return container.at(id);
		}

	}

	bool vvec_print(int id)
	{
		csvec res = container_search(id);
		if (!res)
		{
			cout << "Vector not found " << id << endl;
			return false;
		}

		cout << "Printing vector " << id <<":" <<endl;

		for (int i = 0; i < res->size(); i ++)
		{
			cout << i << " : "<< res->at(i) << endl;
		}
	}

	bool container_delVector(int index)
	{
		vector<string>* res = container_search(index);
		if (!res)
		{
			cout << "Vector not found " << index << endl;
			return false;
		}

		delete res;
		container.at(index) = nullptr;
		cout << "Successfully deleted vector " << index << endl;
		return true;
	}

	bool save_to(string filepath, int index)
	{
		vector<string>* res = container_search(index);
		if (!res)
		{
			cout << "Vector not found " << index << endl;
			return false;
		}

		cout << "Writing text to file: " << filepath << endl;

		// Create the file
		ofstream outfile(filepath.c_str(), ios::out);

		if (!outfile)
		{
			// Something went wrong creating the file
			return false;
		}
		// Create stream
		stringstream outstream;

		// Loop over entries
		for (int i = 0; i < res->size(); i ++)
		{
			outstream << res->at(i);
			outstream << endl;
		}

		outfile << outstream.rdbuf();
		outfile.close();
		return true;
	}

	bool load_from(string filepath, int index)
	{
		char buffer[500];
		ifstream source;
		source.open(filepath.c_str(), ios::in);

		if (!source)
		{
			cout << "Something went wrong reading the file." << endl;
			return false;
		}

		string data;
		while (source.getline(buffer, 499))
		{
			if (source.eof())
			{
				source.close();
				cout << "End of file" << endl;
				return true;
			}

			data = buffer;

			vvec_pushBack(index, data);
		}

		source.close();
		return true;
	}
};