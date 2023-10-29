#include <iostream>
#include "Main Chain Bot.h"
#include "User Interface.h"
using namespace std;

int main()
{
Start:
	cout << "Welcome to BlockChain Simulator! A simple simulation made by yours truly." << endl;
	cout << "Menu: " << endl << "1. Sign up for an account." << endl << "2. Login to an account" << endl << "3. Exit" << endl;
	cout << "Select what you would like to do. Remember to only enter the number corresponding with each option." << endl;
	cout << "Enter option here: ";

	int selection;
	cin >> selection;

	Chain user;

	switch (selection)
	{
	Case_1:
	case 1:
	{
		cout << "Sign up selected." << endl << "Are you an administrator? Enter 'Y' for Yes or 'N' for No, anything else to return to previous menu. ";
		char inp;
		cin >> inp;

		bool admin;
		if (inp == 'Y' || inp == 'y')
		{
			string admin_pass = "SimpleBlockSim", admin_inp;
		Admin_Login:
			cout << "Enter the administrative password: ";
			cin >> admin_inp;

			if (admin_inp == admin_pass)
			{
				admin = true;
				string name, password, key = " ";
				cout << "Enter a username: ";
				cin >> name;
				cout << "Enter your password: ";
				cin >> password;

				user.insertBlock(name, password, key, admin);
			}
			else
			{
				cout << "Password incorrect! Enter 'Y' to retry or anything else to go back. ";
				char inp;
				cin >> inp;

				if (inp == 'Y' || inp == 'y')
					goto Admin_Login;
				else
					goto Case_1;
			}

			//create a hash from password and store as key;


		}
		else if (inp == 'N' || inp == 'n')
		{
			admin = false;
			string name, password, key;
			cout << "Enter a username: ";
			cin >> name;
			cout << "Enter your password: ";
			cin >> password;

			user.insertBlock(name, password, key, admin);
		}
		else
		{
			cout << "Going back to previous options.";
			goto Start;
		}

		break;
	}

Case_2:
	case 2:
	{
		cout << "Login Selected." << "Are you an administrator? Enter 'Y' for Yes or 'N' for No, anything else to return to previous menu. ";
		char inp;
		cin >> inp;

		bool admin, found;
		if (inp == 'Y' || inp == 'y')
		{
			string admin_pass = "SimpleBlockSim", admin_inp;
		Admin_Login_2:
			cout << "Enter the administrative password: ";
			cin >> admin_inp;

			if (admin_inp == admin_pass)
			{
			Login_A:
				admin = true;
				string name, password, key = " ";
				cout << "Enter your username: ";
				cin >> name;
				cout << "Enter your password: ";
				cin >> password;

				found = user.findBlock(name, password);

				if (found)
				{
					//open admin window
				}
				else
				{
					cout << "User not found! Check your inputs and try again.";
					goto Login_A;
				}
			}
			else
			{
				cout << "Password incorrect! Enter 'Y' to retry or anything else to go back. ";
				char inp;
				cin >> inp;

				if (inp == 'Y' || inp == 'y')
					goto Admin_Login_2;
				else
					goto Case_2;
			}
		}
		else if (inp == 'N' || inp == 'n')
		{
		Login_U:
			admin = false;
			string name, password, key = " ";
			cout << "Enter your username: ";
			cin >> name;
			cout << "Enter your password: ";
			cin >> password;

			found = user.findBlock(name, password);

			if (found)
			{
				User acc(name, password, key, admin);
				acc.main_U(key); // opens user interface
			}
			else
			{
				cout << "User not found! Check your inputs and try again.";
				goto Login_U;
			}
		}
		else
		{
			cout << "Going back to previous options.";
			goto Start;
		}

		break;
	}

	case 3:
	{
		cout << "Goodbye.";
		break;
	}
	default:
	{
		cout << "Invalid selection! Try again.";
		goto Start;
		break;
	}
	}
}