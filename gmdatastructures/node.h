#pragma once
#include <string>
using namespace std;
class Node {
private:
	Node* next;
	Node* prev;
	double value;
	string key;
	int type = 0;
public:
	Node(){
		next = NULL;
		prev = NULL;
		value = 0.0;
		key = "";
	}

	Node(string _key, double _value)
	{
		next = nullptr;
		prev = nullptr;
		value = _value;
		key = _key;
	}

	virtual void setKey(string _key)
	{
		key = _key;
	}

	virtual void setValue(double val)
	{
		value = val;
	}

	virtual void setPrev(Node* p)
	{
		prev = p;
	}

	virtual void setNext(Node* n)
	{
		next = n;
	}

	virtual Node* getPrev()
	{
		return prev;
	}

	virtual Node* getNext()
	{
		return next;
	}

	virtual bool hasPrev()
	{
		return (bool)prev;
	}

	virtual bool hasNext()
	{
		return (bool)next;
	}

	double getValue()
	{
		return value;
	}

};

class NodeWithString : public Node
{
	Node* next;
	Node* prev;
	string key;
	string value;
	int type = 1;
public:
	NodeWithString(string _key, string _value)
	{
		NodeWithString::key = _key;
		NodeWithString::value = _value;
		NodeWithString::next = nullptr;
		NodeWithString::prev = nullptr;
	}

	void setKey (string _key) override
	{
		NodeWithString::key = _key;
	}

	void setValue(string val)
	{
		NodeWithString::value = val;
	}

	void setPrev(Node* p) override
	{
		NodeWithString::prev = p;
	}
	void setNext(Node* n) override
	{
		NodeWithString::next = n;
	}



	Node* getPrev() override
	{
		return NodeWithString::prev;
	}

	Node* getNext() override
	{
		return NodeWithString::next;
	}
	bool hasPrev() override
	{
		return (bool)NodeWithString::prev;
	}

	bool hasNext() override
	{
		return (bool)NodeWithString::next;
	}

	string getValue()
	{
		return value;
	}
};