#include <iostream>
#include <fstream>
#include <list>
#include <conio.h>
#include <string>

using namespace std;
void equals(char out[20], char(&arto)[20])
{


	const int c_size = 20;
	for (int i = 0; i < c_size; ++i)
	{
		arto[i] = out[i];
	}
}

class entry
{
private:
	int emp_number;
	char fname[20], lname[20];
public:
	entry()
	{
		emp_number = 0;
	}
	entry(int num, char o[20], char t[20])
	{
		
		emp_number = num;
		equals(o, fname);
		equals(t, lname);
	}
	void get_emp_number()
	{
		cout << "Enter the employee number" << endl;
		cin >> emp_number;
	}
	void get_name()
	{
		cout << "Enter the employee name" << endl;
		cin >> fname >> lname;
	}
	char* ret_fname()
	{
		return fname;
	}
	char* ret_lname()
	{
		return lname;
	}
	int ret_emp_number()
	{
		return emp_number;
	}

};





list<entry> get_from_file()
{
	
	ifstream fin("data_base1.txt", ios::binary );
	list<entry> base_list;
	if (fin.is_open())
	{
		int size_of_db;
		fin.read((char*)&size_of_db, sizeof(int));
		for (int i = 0; i < size_of_db; ++i)
		{
			int emp_n;
			char fn[100], ln[100];
			fin.read((char*)&emp_n, sizeof(int));
			fin.read((char*)&fn, 20);
			fin.read((char*)&ln, 20);
			entry form(emp_n, fn, ln);
			base_list.push_back(form);
		}
	}
	fin.close();
	return base_list;
	
}
void save_to_file(list<entry> &DB)
{
	
	
	ofstream fout("data_base1.txt", ios::binary | ios::trunc);
	try {
		if (fout.is_open())
		{
			int size_db = DB.size();
			fout.write((char*)&size_db, sizeof(int));
			auto itr = DB.begin();
			for (; itr != DB.end(); ++itr)
			{
				int en;
				char* fnm;
				char* lnm;
				en = itr->ret_emp_number();
				fnm = itr->ret_fname();
				lnm = itr->ret_lname();
				fout.write((char*)&en, sizeof(int));
				fout.write((char*)fnm, 20);
				fout.write((char*)lnm, 20);
			}
		}
		else
		throw 1;
	}
	catch (int n)
	{
		cout << "save_to_file_function_fail... ERROR" << n << endl;
	}
	fout.close();
}
int main()
{
	
	list<entry> main;
	string choice;
	main = get_from_file();
	cout << "/////////////////////////////" << endl;
	cout << "/////////////////////////////" << endl;
	cout << "CORPORATE DATABASE" << endl;
	cout << "/////////////////////////////" << endl;
	cout << "/////////////////////////////" << endl;
	cout << "Press any key to continue..." << endl;
	_getch();
	do
	{
		system("cls");
		cout << "Commands:" << endl;
		cout << "Add" << endl;
		cout << "Delete" << endl;
		cout << "Clear" << endl;
		cout << "Print" << endl;
		cout << "Exit" << endl;

		cin >> choice;

		if (choice == "Add")
		{
			entry form;
			form.get_emp_number();
			form.get_name();
			main.push_back(form);
			cout << "Object added succefully" << endl;
			_getch();
		}
		else if (choice == "Delete")
		{
			int emp_num;
			bool deleted = false;
			cout << "Enter the number of the employee to be deleted" << endl;
			cin >> emp_num;
			auto itr = main.begin();
			for (; itr != main.end(); ++itr)
			{
				if (itr->ret_emp_number() == emp_num)
				{
					main.erase(itr);
					deleted = true;
					cout << "Object deleted succefully." << endl;
					break;
				}
			}
			if (deleted = false)
			{
				cout << "Failed to delete. Object does not exist." << endl;
			}
			_getch();
		}
		else if (choice == "Clear")
		{
			main.clear();
			ofstream clear_up_file("data_base1.txt", ios::trunc);
			if (clear_up_file.is_open())
			{
				cout << "Data base file cleared." << endl;
			}
			clear_up_file.close();
			_getch();
		}
		else if (choice == "Print")
		{
			if (main.size() != 0)
			{
				cout << "________________________________________________________" << endl;
				for (entry shell : main)
				{
					cout << "| " << shell.ret_emp_number() << " | " << shell.ret_fname() << " | " << shell.ret_lname() << " |" << endl;
				}
				cout << "________________________________________________________" << endl;
			}			else
				cout << "The data base is empty." << endl;
			_getch();
		}
		else if (choice == "Exit")
		{
			
			save_to_file(main);

			cout << "Data saved to file" << endl;
			
			
		}

	} while (choice != "Exit");

	return 0;
}
