#include <iostream>
#include <string>
using namespace std;

class Chain
{
public:
	struct Block
	{
		string name;
		string password;
		string key = "Chain";
		double fiat = 0;
		double crypto = 0;
		bool admin;
		Block* next;
	};

	Block* head;

	Chain()
	{
		head = nullptr;
	}

	~Chain()
	{
		Block* curr;
		while (head)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}

	bool isEmpty()
	{
		if (head)
			return true;
		else
			return false;
	}

	void insertBlock(string n, string pass, string key, bool admin)
	{
		Block* newNode = new Block;
		newNode->name = n;
		newNode->password = pass;
		newNode->key = key;

		if (isEmpty())
		{
			head = newNode;
			newNode->next = nullptr;
		}
		else
		{
			Block* curr = head;
			while (curr->next != nullptr)
			{
				curr = curr->next;
			}

			curr->next = newNode;
			newNode->next = nullptr;
		}
	}

	void deleteBlock(string key)
	{
		Block* curr, * prev;

		if (isEmpty())
		{
			cout << "Nothing to delete.";
			return;
		}
		else
		{
			curr = head;
			prev = nullptr;

			while (curr->key != key)
			{
				prev = curr;
				curr = curr->next;
			}

			prev->next = curr->next;
			curr->next = nullptr;
			delete curr;

		}
	}

	// bool login(string name, string pass, string key)
	// {
	//	Block *curr;
	//	bool found = false;

	//	if (isEmpty())
	//	{
	//		cout << "Chain Empty. Please try again.";
	//	}
	//	else
	//	{
	//		while (curr)
	//		{
	//			if (curr->name == name && curr->password == pass && curr->key == key)
	//			{
	//				found = true;
	//			}
	//			else
	//			{
	//				curr = curr->next;
	//			}
	//		}
	//	}

	//	return found;
	//}

	bool findBlock(string name, string pass)
	{
		Block* curr = nullptr;

		if (isEmpty())
		{
			return false;
		}
		else
		{
			curr = head;
			while (curr)
			{
				if (curr->name == name && curr->password == pass)
					return true;
				else
					curr = curr->next;
			}

			return false;
		}
	}
};