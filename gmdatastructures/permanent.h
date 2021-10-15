#pragma once
#include "node.h"
using namespace std;
class permanentContainer {
private:
     double num = 0;
     Node* first = NULL;
     Node* last = NULL;
     Node* current = NULL;
public:
    permanentContainer()
    {
        num = 0;
    }

    int getNum()
    {
        return num;
    }

    void del(Node* n)
    {
        bool iscurr = (n == current);

        Node* np = n->getPrev();
        Node* nn = n->getNext();

        if (np && nn)
        {
            np->setNext(nn);
            nn->setPrev(np);   
        }
        else if (np && !nn)
        {
            np->setNext(nullptr);
            last = np;
        }
        else if (!np && nn)
        {
            nn->setPrev(nullptr);
            first = nn;
        }
        else
        {
            last = nullptr;
            first = nullptr;
            current = nullptr;
        }

        cout << "Deleting node with value " << n->getValue() << endl;
        delete n;
        if (iscurr)
        {
            if(np)
            { 
                current = np;
            }
            else
            {
                current = first;
            }        
        }
    }

    void addTo(Node* n)
    {
        reset();
        
        if (isEmpty())
        {
            first = n;
            last = n;
            current = n;
            cout << "Added node as first" << endl;
            return;
        }
        
        Node* cn = current->getNext();

        current->setNext(n);
        n->setNext(cn);

        if (current == last)
        {
            last = n;
        }

        current = n;
    }

    void addNode(string key, double value)
    {
        Node* n = new Node(key, value);
        addTo(n);
        cout << "Successfully added to list (IntNode)!" << endl;
    }

    void addNode(string key, string value)
    {
        Node* n = new NodeWithString(key, value);
        addTo(n);
        cout << "Successfully added to list (StringNode)!" << endl;
    }

    void clearAll()
    {
        if (isEmpty())
        {
            cout << "Container is empty." << endl;
            return;
        }

        reset();
       
        while (current->hasNext())
        {
            current = current->getNext();
            delete current->getPrev();
        }

        delete current;

        cout << "Clearing success." << endl;
    }

    void reset()
    {
        current = first;
    }

    bool retreat()
    {
        if (current->hasPrev())
        {
            current = current->getNext();
            return true;
        }
        return false;
    }

    bool advance()
    {
        if (current->hasNext())
        {
            current = current->getNext();
            return true;
        }
        cout << "cannot advance: End of List" << endl;
        return false;
    }

    Node* getCurrent()
    {
        return current;
    }

    Node* getLast()
    {
        return last;
    }

    Node* getFirst()
    {
        return first;
    }

    bool isEmpty()
    {
        if (!first)
        {
            return true;
        }
        return false;
    }
};
