#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Main Chain Bot.h"
using namespace std;

class User : public Chain
{
public:
	Block* u;

	User(string n, string pass, string key, bool admin)
	{
		u->name = n;
		u->password = pass;
		u->key = " "; //change this once done with hash algo
		u->fiat = 0;
		u->crypto = 0;
		u->admin = admin;
	}

	Block* findUser(string key)
	{
		Block* curr = nullptr;

		if (isEmpty())
		{
			return curr;
		}
		else
		{
			curr = head;
			while (curr)
			{
				if (curr->key == key)
					return curr;
				else
					curr = curr->next;
			}

			return curr;
		}
	}

	void displayStat(string key)
	{
		Block* curr = findUser(key);

		cout << "Username: " << curr->name << endl;
		cout << "Key: " << curr->key << endl;
		cout << "Fiat: " << curr->fiat << endl;
		cout << "Crypto: " << curr->crypto << endl;
	}

	void addFiat(double f, string key)
	{
		Block* curr = findUser(key);

		curr->fiat = f;
	}

	void buyCrypto(double rate, string key)
	{
		Block* curr = findUser(key);

		double f, amount;
		cout << "Enter the amount you want to exchange: ";
		cin >> f;

		while (f > curr->fiat)
		{
			cout << "Amount invalid! Input has to be less than or equal to your current balance." << endl;
			cout << "Re-enter amount: ";
			cin >> f;
		}

		curr->fiat -= f;
		amount = f * rate;
		curr->crypto = amount;

		cout << "Exchange complete!" << endl;
		cout << "Current balance: " << curr->fiat;
		cout << "Crypto balance: " << curr->crypto;
	}

	void changeName(string key)
	{
		string input, newName;
		cout << "Enter current password: ";
		cin >> input;

		Block* curr = findUser(key);

		if (input == curr->password)
		{
			cout << "Password correct! Enter the new name: ";
			cin >> newName;
			curr->name = newName;
			cout << "Name change done! Returning to Main Menu.";
		}
		else
		{
			while (input != curr->password)
			{
				cout << "Wrong password! Try again (or enter 0 to stop): ";
				cin >> input;
				if (input == curr->password)
				{
					cout << "Password correct! Enter the new name: ";
					cin >> newName;
					curr->name = newName;
					cout << "Name change done! Returning to Main Menu.";
					break;
				}
				else if (input == "0")
				{
					cout << "Cancelling Name Change! Returning to Main Menu.";
					break;
				}
			}
		}
	}

	void changePass(string key)
	{
		string input, newPass, confPass;
		cout << "Enter current password: ";
		cin >> input;

		Block* curr = findUser(key);

		if (input == curr->password)
		{
			cout << "Password correct! Enter the new password: ";
			cin >> newPass;
			cout << "Re-enter the password: ";
			cin >> confPass;
			if (confPass == newPass)
			{
				curr->password = newPass;
				cout << "Password change done! Returning to Main Menu.";
			}
			else
			{
				while (confPass != newPass)
				{
					cout << "Confirming password failed. C'mon man just copy the new pass above: ";
					cin >> confPass;
					if (confPass == newPass)
					{
						curr->password = newPass;
						cout << "Password change done! Returning to Main Menu.";
						break;
					}
				}
			}
		}
		else
		{
			while (input != curr->password)
			{
				cout << "Wrong password! Try again (or enter 0 to stop): ";
				cin >> input;
				if (input == curr->password)
				{
					cout << "Password correct! Enter the new password: ";
					cin >> newPass;
					cout << "Re-enter the password: ";
					cin >> confPass;
					if (confPass == newPass)
					{
						curr->password = newPass;
						cout << "Password change done! Returning to Main Menu.";
					}
					else
					{
						while (confPass != newPass)
						{
							cout << "Confirming password failed. C'mon man just copy the new pass above: ";
							cin >> confPass;
							if (confPass == newPass)
							{
								curr->password = newPass;
								cout << "Password change done! Returning to Main Menu.";
								break;
							}
						}
					}
				}
				else if (input == "0")
				{
					cout << "Cancelling Password Change! Returning to Main Menu.";
					break;
				}
			}
		}
	}

	void deleteAcc(string key)
	{
		Block* curr = findUser(key);

		char confirm;
		string input;
		bool succ = false;
		cout << "Warning! Deleting the account means you will lose all your crypto and fiat! Please think thoroughly before proceeding." << endl;
		cout << "Enter Y to confirm deletion or enter anything else to cancel: ";
		cin >> confirm;

		if (confirm == 'Y' || confirm == 'y')
		{
			cout << "Re-enter your password to continue: ";
			cin >> input;

			if (input == curr->password)
			{
				deleteBlock(curr->key);
				cout << "Deletion done! Returning to Main Menu.";
			}
			else
			{
				while (input != curr->password)
				{
					cout << "Wrong password! Try again (or enter 0 to stop): ";
					cin >> input;
					if (input == curr->password)
					{
						deleteBlock(curr->key);
						cout << "Deletion done! Returning to Main Menu.";
						break;
					}
					else if (input == "0")
					{
						cout << "Cancelling account deletion! Returning to Main Menu.";
						break;
					}
				}
			}
		}
		else
		{
			cout << "Cancelling account deletion! Returning to Main Menu.";
		}
	}

	void main_U(string key)
	{
		Block* curr = findUser(key);

	Main_Menu:
		cout << "Welcome " << curr->name << " ! What would you like to do? Select and option from the ones below: " << endl;
		cout << "1. Info Check" << endl << "2. Add Fiat" << endl << "3. Buy Crypto" << endl << "4. Delete Account" << endl
			<< "5. Return to Main Menu" << endl << "6. Exit Simulation" << endl;

		int inp;
		cin >> inp;

		switch (inp)
		{
		case 1:
		{
			displayStat(key);
			break;
		}
		case 2:
		{
			cout << "Add Fiat selected." << endl << "Enter the amount you want to add: ";
			double f;
			cin >> f;

			addFiat(f, key);
			break;
		}
		case 3:
		{
			double rate;
			srand(time(NULL));
			rate = ((double)rand() / (RAND_MAX));
			cout << "Buy Crypto selected." << endl << "The current exchange rate is: " << rate;
			buyCrypto(rate, key);
			break;
		}
		case 4:
		{
			cout << "Delete Account selected." << endl << "Are you sure? Enter Y for yes or anything else to return: ";
			char inp;
			cin >> inp;

			if (inp == 'Y' || inp == 'y')
			{
				deleteAcc(key);
			}
			else
			{
				cout << "Deletion cancelled. Returning to Main Menu.";
				goto Main_Menu;
			}

			break;
		}
		case 5:
		{
			cout << "Returning to Main Menu.";
			goto Main_Menu;
			break;
		}
		case 6:
		{
			cout << "Goodbye.";
			break;
		}
		}
	}
};