#include <iostream>

#include <fstream>   // for input and output file

#include <string>     // these 3 libraries for string

#include <conio.h>    // getline(,)

#include <vector>     // for vector of struct

#include <windows.h>

#include <ctime>

#include <map>


using namespace std;

struct date
{
	int day;
	int month;
	int year;
};
struct task
{
	string task_name;
	date deadline;
	int priority;
	string details;
	bool Done;
};
time_t now;
struct tm nowlocal;

int counter = 0;

vector < task > Task;
// to read all the data from the file to the vector

vector < task > SortedByDateTasks(Task);
// to store the orderd -by date- tasks in it

void reading();

void Add();

void View();

void Edit();

int Edit_search();

void search();

void View_Priority();

void DisplayTasksSortedbyDate();

void Mark_Done();

void Input();

void updating();

void today_tasks();

void overdue_Tasks();

void delete_task();

void delete_search();

void done(int);

void setcolor(unsigned short color);

void design();

void display_done();

void tasks_to_mark_done();

//**********************************************************************

void main(){
	design();
	reading();
	today_tasks();
	Input();
}


//************************************************************************



void reading(){
	ifstream File;
	File.open("File.txt", ios::app);
	// i is the iterator for the vector
	int i = 0;
	// File.eof() is a bool marks the end of the file
	// the if statement inside the loop because it makes 1 extra iteration without it
	while (!File.eof()){
		char ch;
		string S;
		// pushed a struct in the vector and then input the data in it
		Task.push_back(task());
		getline(File, Task[i].task_name);
		File >> Task[i].deadline.day >> ch >> Task[i].deadline.month >> ch >> Task[i].deadline.year;
		File.ignore();
		File >> Task[i].priority;
		File.ignore();
		getline(File, Task[i].details);
		File >> Task[i].Done;
		File.ignore();
		getline(File, S);
		i++;
	}
	// the loop makes 1 more iteration and pushes an empty struct in the vector so pop_back removes the last one
	Task.pop_back();
}
void View(){
	if (Task.size() == 0){
		cout << "Sorry !! There are no tasks to view \n";
	}
	else {
		for (int i = 0; i<Task.size(); i++){
			cout << "Task Number [" << i + 1 << "]\n";
			cout << "Task title : " << Task[i].task_name << endl;
			cout << "Task deadline : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << endl;
			cout << "Task Priority : " << Task[i].priority << endl;
			cout << "Task Details : " << Task[i].details << endl;
			if (Task[i].Done){
				cout << "Task is Done \n";
			}
			else {
				cout << "Task is not Done \n";
			}
			cout << "*************************\n";
		}
	}
}
void Add(){
	cout << "\t\t\t\t\t\t\t\t\t\t\tPress '0' To Cancel\r";
	char answer;
	string c = "0";//variable to cancel
	int i = Task.size();
	do{
		Task.push_back(task());
		//cout << "**********************" << endl;
		cout << "\nEnter task title : ";
		cin.ignore();
		getline(cin, Task[i].task_name);
		//To Cancel..->
		if (Task[i].task_name.compare(c) == 0){
			Task.pop_back();
			break;
		}
		cout << "\nEnter Deadline (seperated by spaces )  : ";
		cin >> Task[i].deadline.day;
		//To Cancel..->
		if (Task[i].deadline.day == 0){
			Task.pop_back();
			break;
		}
		cin >> Task[i].deadline.month;
		//To Cancel..->
		if (Task[i].deadline.month == 0){
			Task.pop_back();
			break;
		}
		cin >> Task[i].deadline.year;
		//To Cancel..->
		if (Task[i].deadline.year == 0){
			Task.pop_back();
			break;
		}
		if (Task[i].deadline.day / 32 != 0 || Task[i].deadline.month / 13 != 0 || Task[i].deadline.year / 3000 != 0){
			do{
				cout << "please Enter available date (DD MM YYYY) : ";
				cin >> Task[i].deadline.day;
				//To Cancel..->
				if (Task[i].deadline.day == 0){
					Task.pop_back();
					break;
				}
				cin >> Task[i].deadline.month;
				//To Cancel..->
				if (Task[i].deadline.month == 0){
					Task.pop_back();
					break;
				}
				cin >> Task[i].deadline.year;
				//To Cancel..->
				if (Task[i].deadline.year == 0){
					Task.pop_back();
					break;
				}
			} while (Task[i].deadline.day / 32 != 0 || Task[i].deadline.month / 13 != 0 || Task[i].deadline.year / 3000 != 0);

		}
		cout << "\nEnter  Priority (from 1 To 3) : ";
		cin >> Task[i].priority;
		if (Task[i].priority == 0){
			Task.pop_back();
			break;
		}
		if (Task[i].priority<1 || Task[i].priority>3){
			do{
				cout << "Please enter the priority of task within the displayed range(from 1 To 3) : ";
				cin >> Task[i].priority;
				if (Task[i].priority == 0){
					Task.pop_back();
					break;
				}
			} while (Task[i].priority<1 || Task[i].priority>3);
		}
		cout << "\nEnter task Details (Press {Enter} when finish) : ";
		cin.ignore();
		getline(cin, Task[i].details);
		if (Task[i].details.compare(c) == 0){
			Task.pop_back();
			break;
		}
		Task[i].Done = 0;
		//updating();//for saving data
		cout << "\n*************** Task added successfully ?? ***************\n\n";
		i++;
		cout << "Do you want to add more tasks ? (Y/N) ";
		cin >> answer;
	} while (answer == 'y' || answer == 'Y');

}
void Input(){

	// this variable to receive the process that the user want to make
	char Proccess;
	//char Pros;
	// the choices that the user can make each of which is connected to a function called by input function

	cout << "\t\t\t\t************To Do List************" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\tTo Exit Program Press '0'\n\n";
	cout << " 1-> Add new task" << endl << endl;
	cout << " 2-> Edit task" << endl << endl;
	cout << " 3-> Delete task" << endl << endl;
	cout << " 4-> Display tasks" << endl << endl;
	cout << " 5-> Display today's tasks" << endl << endl;
	cout << " 6-> Display the Done tasks" << endl << endl;
	cout << " 7-> Display overdue tasks" << endl << endl;
	cout << " 8-> Search for a specific task" << endl << endl;
	cout << " 9-> Display tasks sorted by there Priority" << endl << endl;
	cout << " 10->Display tasks sorted by Due time" << endl << endl;
	cout << " 11->Mark tasks as done" << endl << endl;
	// << endl << endl;
	cout << "************************" << endl;
	cout << "Enter your choice : ";
	cin >> Proccess;
	cout << "\n************************\n" << endl;

	
	 if (Proccess == '1'){
		Add();
		// clears the screen after the user press enter
		system("CLS");
		// so that the user can make another choice
		Input();
	}
	else if (Proccess == '2')
	{
		Edit();
		system("pause");
		system("cls");
		Input();
	}
	else if (Proccess == '3')
	{
		delete_task();
		system("pause");
		system("cls");
		Input();
	}
	else if (Proccess == '4'){
		View();
		system("pause");
		system("cls");
		Input();
	}
	else if (Proccess == '5')
	{
		system("cls");
		today_tasks();
		system("cls");
		Input();
	}
	else if (Proccess == '6'){
		system("cls");
		display_done();
		system("pause");
		system("cls");
		Input();
	}
	else if (Proccess == '7')
	{
		system("cls");
		overdue_Tasks();

	}
	else if (Proccess == '8')
	{
		search();
		system("cls");
		Input();

	}
	else if (Proccess == '9'){
		View_Priority();
		system("pause");
		system("cls");
		Input();
	}
	else if (Proccess == '10'){
		DisplayTasksSortedbyDate();
		system("pause");
		system("cls");
		Input();
	}
	else if (Proccess == '11'){
		Mark_Done();
	}
	else if (Proccess == '0')
	{
		//cout << Task.size();
		//system("pause");
		//PlaySound(TEXT("chimes.wav"), NULL, SND_SENTRY);
		updating();
		exit(0);

	}
	else {
		
		cout << " Unknown Number please make another choice \n" << endl;
		// so the user can see the data on the screen
		system("pause");
		// clears the screen after the user press enter
		system("cls");
		// so that the user can make another choice
		Input();

	}

}
void updating(){
	ofstream file;
	file.open("File.txt",ofstream::trunc);
	for (int i = 0; i<Task.size(); i++){
		file << Task[i].task_name << "\n";
		file << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n";
		file << Task[i].priority << "\n";
		file << Task[i].details << "\n";
		file << Task[i].Done << "\n";
		file << "*************************\n";
	}
	file.close();
}
void Edit()
{
	while (true){
		int task_Editnum;
		string c = "0";//variable to cancel
		//cout<<"\n \n \t \t \t \t \t*******************************\n \n";
		View();
		cout << "\t\t\t\t\t\t\t\t\t\t\tPress '0' To Cancel\r";
		cout << "\n\t\tPlease Enter The Number Of The Task You Wont To Edit :) : ";
		cin >> task_Editnum;
		if (task_Editnum == 0){
			return;
		}
		system("cls");
		cout << "\t\t\t\t\t\t\t\t\t\tPress '0' To Cancel\r";
		cout << "\t\tEditing Task Number [" << task_Editnum << "]\n\n";
		cout << "Task title : " << Task[task_Editnum - 1].task_name << endl;
		cout << "Task deadline : " << Task[task_Editnum - 1].deadline.day << " " << Task[task_Editnum - 1].deadline.month << " " << Task[task_Editnum - 1].deadline.year << endl;
		cout << "Task Priority : " << Task[task_Editnum - 1].priority << endl;
		cout << "Task Details : " << Task[task_Editnum - 1].details << endl << endl;
		cout << "*************************\n\n";

		int new_task;
		cout << "To edit title press [1]\n";
		cout << "To edit deadline press [2]\n";
		cout << "To edit priority press [3]\n";
		cout << "To edit details press [4]\n";
		cout << "To edit the whole task press [5]\n";
		cout << "\n\n************************" << endl;
		cout << "Enter your choice : ";
		cin >> new_task;
		cout << "\n************************\n" << endl;

		if (new_task == 0){
			system("cls");
			return;
		}
		switch (new_task)
		{
		case 1:
		{
			string new_title;
			cout << "Enter new title : ";
			cin.ignore();
			getline(cin, new_title);
			if (new_title.compare(c) == 0){//to cancel
				PlaySound(TEXT("yooooo ba2a.wav"), NULL, SND_SENTRY);

				system("cls");
				return;
			}
			else
				Task[task_Editnum - 1].task_name = new_title;
			break;
		};
		case 2:
		{
			int new_day, new_month, new_year;
			cout << "Enter new deadline : ";
			cin >> new_day;
			if (new_day == 0){//to cancel
				system("cls");
				return;
			}
			cin >> new_month;
			if (new_month == 0){//to cancel
				system("cls");
				return;
			}
			cin >> new_year;
			if (new_year == 0){//to cancel
				system("cls");
				return;
			}

			else{
				Task[task_Editnum - 1].deadline.day = new_day;
				Task[task_Editnum - 1].deadline.month = new_month;
				Task[task_Editnum - 1].deadline.year = new_year;
			}
			break;
		};
		case 3:
		{
			int new_priority;
			cout << "Enter new priority(from 1 To 3) : ";
			cin >> new_priority;
			if (new_priority == 0){//to cancel
				system("cls");
				return;
			}
			else {
				Task[task_Editnum - 1].priority = new_priority;
				if (Task[task_Editnum - 1].priority < 1 || Task[task_Editnum - 1].priority>3){
					do{
						cout << "Please enter the Priority of Task within the displayed range(from 1 To 3) : ";
						cin >> new_priority;
						if (new_priority == 0){//to cancel
							system("cls");
							return;
						}
						else {
							Task[task_Editnum - 1].priority = new_priority;
						}
					} while (Task[task_Editnum - 1].priority < 1 || Task[task_Editnum - 1].priority>3);
				}

			}


			break;

		};
		case 4:
		{
			string new_details;
			cout << "Enter new details : ";
			cin.ignore();
			getline(cin, new_details);
			if (new_details.compare(c) == 0){//to cancel
				system("cls");
				return;
			}
			else{
				Task[task_Editnum - 1].details = new_details;
			}
			break;

		};
		case 5:
		{
			string new_title;
			cout << "Enter new title : ";
			cin.ignore();
			getline(cin, new_title);
			if (new_title.compare(c) == 0){//to cancel
				system("cls");
				return;
			}
			else{
				Task[task_Editnum - 1].task_name = new_title;
			}
			int new_day, new_month, new_year;
			cout << "Enter new deadline : ";
			cin >> new_day;
			if (new_day == 0){//to cancel
				system("cls");
				return;
			}
			cin >> new_month;
			if (new_month == 0){//to cancel
				system("cls");
				return;
			}
			cin >> new_year;
			if (new_year == 0){//to cancel
				system("cls");
				return;
			}
			else{
				Task[task_Editnum - 1].deadline.day = new_day;
				Task[task_Editnum - 1].deadline.month = new_month;
				Task[task_Editnum - 1].deadline.year = new_year;
			}
			int new_priority;
			cout << "Enter new priority : ";
			cin >> new_priority;
			if (new_priority == 0){//to cancel
				system("cls");
				return;
			}
			else{
				Task[task_Editnum - 1].priority = new_priority;
			}
			string new_details;
			cout << "Enter new details : ";
			cin.ignore();
			getline(cin, new_details);
			if (new_details.compare(c) == 0){//to cancel
				system("cls");
				return;
			}
			else{
				Task[task_Editnum - 1].details = new_details;
			}
			break;
		};
		}
		//updating(); //updfating new edtion
		cout << "\t\t\tTask " << task_Editnum << " Edited successfuly :)\n";

		char respons;
		cout << "Do You Want To Edit Another Task? (y/n)";
		cin >> respons;
		if (respons == 'y' || respons == 'Y'){
			system("cls");
			continue;
		}
		else if (respons == 'n' || respons == 'N'){
			return;
		}
		else{
			cout << "Please Press 'y' For Agree ,Or 'n' For Disagree !!";
			do{
				cin >> respons;
				if (respons == 'y' || respons == 'Y'){
					system("cls");
					break;
				}
				else if (respons == 'n' || respons == 'N'){
					return;
				}
			} while (respons != 'y' || respons != 'Y' || respons != 'n' || respons != 'N');
		}
	}
}
int Edit_search()
{
	int task_Editnum;
	string c = "0";//variable to cance
	cout << "\t\t\t\t\t\t\t\t\t\t\tPress '0' To Cancel\r";
	cout << "\t\tPleas Enter The Number Of The Task You Wont To Edit :)\n";
	cin >> task_Editnum;
	if (task_Editnum == 0){
		return 0;
	}
	system("cls");
	cout << "\t\t\t\t\t\t\t\tPress '0' To Cancel\r";
	cout << "\t\tEditing Task Number [" << task_Editnum << "]\n";
	cout << "Task title : " << Task[task_Editnum - 1].task_name << endl;
	cout << "Task deadline : " << Task[task_Editnum - 1].deadline.day << " " << Task[task_Editnum - 1].deadline.month << " " << Task[task_Editnum - 1].deadline.year << endl;
	cout << "Task Priority : " << Task[task_Editnum - 1].priority << endl;
	cout << "Task Details : " << Task[task_Editnum - 1].details << endl;
	cout << "*************************\n";

	int new_task;
	cout << "To edit title press [1]\n";
	cout << "To edit deadline press [2]\n";
	cout << "To edit priority press [3]\n";
	cout << "To edit details press [4]\n";
	cout << "To edit the whole task press [5]\n";
	cin >> new_task;

	if (new_task == 0){
		return 0;
	}
	switch (new_task)
	{
	case 1:
	{
		string new_title;
		cout << "Enter new title : ";
		cin.ignore();
		getline(cin, new_title);
		if (new_title.compare(c) == 0){//to cancel
			return 0;
		}
		else
			Task[task_Editnum - 1].task_name = new_title;
		break;
	};
	case 2:
	{
		int new_day, new_month, new_year;
		cout << "Enter new deadline : ";
		cin >> new_day;
		if (new_day == 0){//to cancel
			return 0;
		}
		cin >> new_month;
		if (new_month == 0){//to cancel
			return 0;
		}
		cin >> new_year;
		if (new_year == 0){//to cancel
			return 0;
		}

		else{
			Task[task_Editnum - 1].deadline.day = new_day;
			Task[task_Editnum - 1].deadline.month = new_month;
			Task[task_Editnum - 1].deadline.year = new_year;
		}
		break;
	};
	case 3:
	{
		int new_priority;
		cout << "Enter new priority(from 1 To 3) : ";
		cin >> new_priority;
		if (new_priority == 0){//to cancel
			return 0;
		}
		else {
			Task[task_Editnum - 1].priority = new_priority;
			if (Task[task_Editnum - 1].priority < 1 || Task[task_Editnum - 1].priority>3){
				do{
					cout << "Please enter the priority of task within the displayed range(from 1 To 3) : ";
					cin >> new_priority;
					if (new_priority == 0){//to cancel
						return 0;
					}
					else {
						Task[task_Editnum - 1].priority = new_priority;
					}
				} while (Task[task_Editnum - 1].priority < 1 || Task[task_Editnum - 1].priority>3);
			}

		}


		break;

	};
	case 4:
	{
		string new_details;
		cout << "Enter new details : ";
		cin.ignore();
		getline(cin, new_details);
		if (new_details.compare(c) == 0){//to cancel
			return 0;
		}
		else{
			Task[task_Editnum - 1].details = new_details;
		}
		break;

	};
	case 5:
	{
		string new_title;
		cout << "Enter new title : ";
		cin.ignore();
		getline(cin, new_title);
		if (new_title.compare(c) == 0){//to cancel
			return 0;
		}
		else{
			Task[task_Editnum - 1].task_name = new_title;
		}
		int new_day, new_month, new_year;
		cout << "Enter new deadline : ";
		cin >> new_day;
		if (new_day == 0){//to cancel
			return 0;
		}
		cin >> new_month;
		if (new_month == 0){//to cancel
			return 0;
		}
		cin >> new_year;
		if (new_year == 0){//to cancel
			return 0;
		}
		else{
			Task[task_Editnum - 1].deadline.day = new_day;
			Task[task_Editnum - 1].deadline.month = new_month;
			Task[task_Editnum - 1].deadline.year = new_year;
		}
		int new_priority;
		cout << "Enter new priority : ";
		cin >> new_priority;
		if (new_priority == 0){//to cancel
			return 0;
		}
		else{
			Task[task_Editnum - 1].priority = new_priority;
		}
		string new_details;
		cout << "Enter new details : ";
		cin.ignore();
		getline(cin, new_details);
		if (new_details.compare(c) == 0){//to cancel
			return 0;
		}
		else{
			Task[task_Editnum - 1].details = new_details;
		}
		break;
	};
	}
	//updating(); //updfating new edtion
	cout << "\t\t\tTask " << task_Editnum << " Edited successfuly :)\n";
	system("pause");
	return task_Editnum;
}
void search(){
	bool dont_edit = false;
	char cont;
	char press;
	int Task_number;
	string search_title;
	string  c = "0";//for canceling
	int D, M, Y;
	while (true){
		system("cls");
		cout << "\t\t\t\t\t\t\t\t\t\t\tPress '0' To Cancel\r";
		cout << "1- To Search by title . \n \n";
		cout << "2- To Search by deadline . \n \n";
		cout << "3- To Search by number . \n \n";
		cout << "\n ******************************\n\n";
		bool check = false;
		cout << "  Enter your choice : ";
		cin >> press;
		cout << "\n ******************************\n\n";
		if (press == '1')
		{
			cout << "Enter the task Title : ";
			cin.ignore();
			getline(cin, search_title);
			if (search_title.compare(c) == 0){//to cancel
				system("cls");
				break;
			}
			cout << endl << endl;
			int v = 0;//if there ar mor than one task with the same title or date will be a change in edite option 
			bool flag = false;
			for (int i = 0; i < Task.size(); i++)
			{
				if (search_title == Task[i].task_name)
				{

					cout << "\t \t *******************************\n\n";
					cout << "Task number [" << i + 1 << "]" << endl << endl;
					cout << "Title : " << Task[i].task_name << "\n\n";
					cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
					cout << "Priority : " << Task[i].priority << "\n\n";
					cout << "Details : " << Task[i].details << "\n\n";
					cout << "\t \t *******************************\n\n";
					check = true;
					//break;
				}
			}
			if (check == false)
			{
				cout << "\t \t *******************************\n\n";
				cout << "  \t \t\tNo Task to found \n \n";
				cout << "\t \t *******************************\n\n";
			}
		}
		else if (press == '2')
		{
			cout << "Enter the Task Due time (seperated by spaces) : ";
			cin >> D;
			if (D == 0){//to cancel
				system("cls");
				break;
			}
			cin >> M;
			if (M == 0){//to cancel
				system("cls");
				break;
			}
			cin >> Y;
			if (Y == 0){//to cancel
				system("cls");
				break;
			}

			cout << endl << endl;
			for (int i = 0; i < Task.size(); i++)

			{
				if (D == Task[i].deadline.day&& M == Task[i].deadline.month && Y == Task[i].deadline.year)
				{

					cout << "\t \t *******************************\n\n";
					cout << "Task number [" << i + 1 << "]" << endl << endl;
					cout << "Title : " << Task[i].task_name << "\n\n";
					cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
					cout << "Priority : " << Task[i].priority << "\n\n";
					cout << "Details : " << Task[i].details << "\n\n";
					cout << "\t \t *******************************\n\n";
					check = true;
					//break;
				}
			}
			if (check == false)
			{
				cout << "\t \t *******************************\n\n";
				cout << "  \t \t\tNo Task to found \n \n";
				cout << "\t \t *******************************\n\n";
			}
		}
		else if (press == '3')
		{
			cout << "Enter the Task number : ";
			cin >> Task_number;
			if (Task_number == 0){
				system("cls");
				break;
			}
			for (int i = 0; i < Task.size(); i++)
			{
				if (Task_number == i + 1)
				{

					cout << "\t \t *******************************\n\n";
					cout << "Task number [" << i + 1 << "]" << endl << endl;
					cout << "Title : " << Task[i].task_name << "\n\n";
					cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
					cout << "Priority : " << Task[i].priority << "\n\n";
					cout << "Details : " << Task[i].details << "\n\n";
					cout << "\t \t *******************************\n\n";
					check = true;
					//break;
				}
			}
			if (check == false)
			{
				cout << "\t \t *******************************\n\n";
				cout << "  \t \t\tNo Task to found \n \n";
				cout << "\t \t *******************************\n\n";
			}
		}
		else if (press == '0'){//to cancel
			system("cls");
			Input();
		}
		else{

			cout << "\t\t\t\t\t\t\tNo such Choice !  :(" << endl << endl;
			system("pause");
			break;
			search();
			
		}
		cout << "\t\t\t\t\t\t\t\t\tpress 'e' to edit\n\t\t\t\t\t\t\t\t\tpress 'd' To Delete \r";
		cout << " Do you want To Search for another Task (Y/N) : \n";
		cin >> cont;
		if (cont == 'y' || cont == 'Y'){
			system("cls");
			continue;
		}
		else if (cont == 'n' || cont == 'N'){
			system("cls");
			return;
		}
		else if (cont == 'd' || cont == 'D'){
			delete_search();
			system("pause");
		}
		else if (cont == 'e' || cont == 'E'){
			int N;
			N = Edit_search();
			system("cls");
			cout << "\t \t *******************************\n\n";
			cout << "Task number [" << N << "]" << endl << endl;
			cout << "Title : " << Task[N - 1].task_name << "\n\n";
			cout << "Due time : " << Task[N - 1].deadline.day << "/" << Task[N - 1].deadline.month << "/" << Task[N - 1].deadline.year << "\n\n";
			cout << "Priority : " << Task[N - 1].priority << "\n\n";
			cout << "Details : " << Task[N - 1].details << "\n\n";
			cout << "\t \t *******************************\n\n";
			cout << " Do you want To Search for another Task (Y/N) : \n";
			cin >> cont;
			if (cont == 'y' || cont == 'Y'){
				system("cls");
				continue;
			}
			else if (cont == 'n' || cont == 'N'){
				system("cls");
				return;
			}
		}


		else{
			do{
				cout << "Please Press 'y' For Agree ,Or 'n' For Disagree !!\n\n";
				cin >> cont;
				if (cont == 'y' || cont == 'Y'){
					system("cls");
					break;
				}
				else if (cont == 'n' || cont == 'N'){
					system("cls");
					return;
				}
				else if (cont == 'd' || cont == 'D'){
					delete_search();
					system("pause");
				}
				else if (cont == 'e' || cont == 'E'){
					int N;
					N = Edit_search();
					system("cls");
					cout << "\t \t *******************************\n\n";
					cout << "Task number [" << N << "]" << endl << endl;
					cout << "Title : " << Task[N - 1].task_name << "\n\n";
					cout << "Due time : " << Task[N - 1].deadline.day << "/" << Task[N - 1].deadline.month << "/" << Task[N - 1].deadline.year << "\n\n";
					cout << "Priority : " << Task[N - 1].priority << "\n\n";
					cout << "Details : " << Task[N - 1].details << "\n\n";
					cout << "\t \t *******************************\n\n";
					cout << " Do you want To Search for another Task (Y/N) : \n";
					cin >> cont;
					if (cont == 'y' || cont == 'Y'){
						system("cls");
						break;
					}
					else if (cont == 'n' || cont == 'N'){
						system("cls");
						return;
					}

				}
			} while (cont != 'Y' || cont != 'y' || cont != 'n' || cont != 'N' || cont != 'e' || cont != 'E');
		}
	}
}
void today_tasks(){
	/*for (int i=0; i<Task.size(); i++){
	Task[i].Done=0;
	}*/
	char enter;
	bool found = false;
	now = time(NULL);
	nowlocal = *localtime(&now);
	//cout<<"\t \t \t **********************************\n";
	cout << "\n Today Tasks  :- \n";
	cout << " *******************\n\n";
	//cout<<"Today is : "<<nowlocal.tm_mday<<" "<<nowlocal.tm_mon+1<<" "<<nowlocal.tm_year+1900<<endl;
	for (int i = 0; i<Task.size(); i++)
	{
		if (nowlocal.tm_mday == Task[i].deadline.day&& nowlocal.tm_mon + 1 == Task[i].deadline.month &&nowlocal.tm_year + 1900 == Task[i].deadline.year&&Task[i].Done != 1)
		{
			if (Task[i].Done != 1){
				cout << "Press 'y' Key If you done your Task & 'n' if not " << endl;
				cout << "\t \t *******************************\n\n";
				cout << "Task number is : " << i + 1 << endl << endl;
				cout << "Title : " << Task[i].task_name << "\n\n";
				cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
				cout << "Priority : " << Task[i].priority << "\n\n";
				cout << "Details : " << Task[i].details;
				cout << "\t \t \t \t \t  "; done(i);
				cout << endl << endl;
				cout << "\t \t\t\t\t\ \t        *******************************\n\n";
				setcolor(15);

				found = true;
			}
		}
	}
	if (found == false)
	{
		cout << "\t \t *******************************\n\n";
		cout << "  \t \t\tNo Task to found \n \n";
		cout << "\t \t *******************************\n\n";
	}
	system("pause");
	//cout<<"prees [Enter]to go to list";
	system("cls");
	updating();
}
void DisplayTasksSortedbyDate()
{
	system("cls");
	SortedByDateTasks.clear();
	//this for copying the original tasks file to another file to sort them
	for (int i = 0; i<Task.size(); i++)
		SortedByDateTasks.push_back(Task[i]);
	
	// this for sorting tasks by years in ascending order
	for (int i = 0; i < SortedByDateTasks.size(); i++)
	{
		for (int j = i + 1; j<SortedByDateTasks.size(); j++) {
			if (SortedByDateTasks[i].deadline.year > SortedByDateTasks[j].deadline.year)
			{
				swap(SortedByDateTasks[i], SortedByDateTasks[j]);
			}
		}
	}

	//this for sorting tasks by months in ascending order
	for (int i = 0; i < SortedByDateTasks.size(); i++)
	{
		for (int j = i + 1; j<SortedByDateTasks.size(); j++) {
			if (SortedByDateTasks[i].deadline.year == SortedByDateTasks[j].deadline.year)
			{
				if (SortedByDateTasks[i].deadline.month > SortedByDateTasks[j].deadline.month)
				{
					swap(SortedByDateTasks[i], SortedByDateTasks[j]);
				}
			}
		}
	}
	for (int i = 0; i < SortedByDateTasks.size(); i++)
	{
		for (int j = i + 1; j<SortedByDateTasks.size(); j++) {
			if (SortedByDateTasks[i].deadline.year == SortedByDateTasks[j].deadline.year)
			{
				if (SortedByDateTasks[i].deadline.month == SortedByDateTasks[j].deadline.month)
				{
					if (SortedByDateTasks[i].deadline.day > SortedByDateTasks[j].deadline.day)
					{
						swap(SortedByDateTasks[i], SortedByDateTasks[j]);
					}
				}
			}
		}
	}
	cout << "**************Tasks sorted by date**************\n";
	for (int i = 0; i<SortedByDateTasks.size(); i++) {
		cout << "Task Number [" << i + 1 << "]";
		cout << "Task title : " << SortedByDateTasks[i].task_name << endl;
		cout << "Task deadline : " << SortedByDateTasks[i].deadline.day << " " << SortedByDateTasks[i].deadline.month << " " << SortedByDateTasks[i].deadline.year << endl;
		cout << "Task Priority : " << SortedByDateTasks[i].priority << endl;
		cout << "Task Details : " << SortedByDateTasks[i].details << endl;
		if (Task[i].Done){
			cout << "Task is Done \n";
		}
		else {
			cout << "Task is not Done \n";
		}
		cout << "*************************\n";
	}
	return;
}
void View_Priority(){
	system("cls");
	map <int, vector < int >>P;
	for (int i = 0; i<Task.size(); i++){
		P[Task[i].priority].push_back(i);
	}

	for (int i = 1; i <= 3; i++){
		cout << "\n\nTasks of Priority #" << i << " are : \n";
		if (P[i].size() == 0){
			cout << "Sorry !! No tasks are found with this Priority \n";
		}
		else {
			for (int j = 0; j < P[i].size(); j++){
				cout << "Task title : " << Task[j].task_name << endl;
				cout << "Task deadline : " << Task[j].deadline.day << "/" << Task[j].deadline.month << "/" << Task[j].deadline.year << endl;
				cout << "Task Details : " << Task[j].details << endl;
				if (Task[j].Done){
					cout << "Task is Done \n";
				}
				else {
					cout << "Task is not Done \n";
				}
				cout << "**********************\n";
			}
		}


	}
}
void overdue_Tasks(){
	char contin;
	bool check = false;
	now = time(NULL);
	nowlocal = *localtime(&now);
	for (int i = 0; i<Task.size(); i++)
	{
		if (Task[i].deadline.year <= nowlocal.tm_year + 1900 && Task[i].Done == 0)
		{
			cout << "\t \t *******************************\n\n";
			cout << "Task number is : " << "[" << i + 1 << "]" << endl << endl;
			cout << "Title : " << Task[i].task_name << "\n\n";
			cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
			cout << "Priority : " << Task[i].priority << "\n\n";
			cout << "Details : " << Task[i].details << "\n\n";
			cout << "\t \t *******************************\n\n";
			check = true;
		}
		else if (Task[i].deadline.year == nowlocal.tm_year + 1900 && nowlocal.tm_mon + 1 >= Task[i].deadline.month&&Task[i].Done == 0)
		{
			cout << "\t \t *******************************\n\n";
			cout << "Task number is : " << "[" << i + 1 << "]" << endl << endl;
			cout << "Title : " << Task[i].task_name << "\n\n";
			cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
			cout << "Priority : " << Task[i].priority << "\n\n";
			cout << "Details : " << Task[i].details << "\n\n";
			cout << "\t \t *******************************\n\n";
			check = true;
		}
		else if (Task[i].deadline.year == nowlocal.tm_year + 1900 && nowlocal.tm_mon + 1 == Task[i].deadline.month&&Task[i].deadline.day <= nowlocal.tm_mday&&Task[i].Done == 0)
		{
			cout << "\t \t *******************************\n\n";
			cout << "Task number is : " << "[" << i + 1 << "]" << endl << endl;
			cout << "Title : " << Task[i].task_name << "\n\n";
			cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
			cout << "Priority : " << Task[i].priority << "\n\n";
			cout << "Details : " << Task[i].details << "\n\n";
			cout << "\t \t *******************************\n\n";
			check = true;
		}


	}
	if (check == false){
		cout << "No Overdue Tasks\n";
	}
	cout << "Enter 'e' to edit the overdue tasks or '0' to go to the list : ";
	cin >> contin;
	if (contin == 'e')
	{
		Edit_search();
	}
	else if (contin == '0')
	{
		system("cls");
		Input();
	}
}
void delete_task(){
	char choice;
	do{
		View();
		int deleted;
		cout << "\n\t\t\t\t\t\t\tPress '0' To Cancel \r";
		cout << "Please Enter Number Of Task you want to delete : ";
		cin >> deleted;
		if (deleted == 0){//to cancel
			return;
		}
		else if (deleted > Task.size()){
			cout << "\t\t\tNo Task Found ! , Please Try Again :)\n";
			continue;
		}
		else{
			for (int i = deleted - 1; i<Task.size() - 1; i++)
			{
				Task[i].task_name = Task[i + 1].task_name;
				Task[i].deadline.day = Task[i + 1].deadline.day;
				Task[i].deadline.month = Task[i + 1].deadline.month;
				Task[i].deadline.year = Task[i + 1].deadline.year;
				Task[i].priority = Task[i + 1].priority;
				Task[i].details = Task[i + 1].details;
			}
			Task.pop_back();
			cout << "\t\t\t Task" << deleted << " Deleted succeefully :) \n";
		}
		cout << "Do you want to delete another task (Y/N)? ";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}
void done(int i)
{
	char y = 251;
	char x;
	x = _getch();
	if (x == 'y' || x == 'Y')
	{
		
		Task[i].Done = 1;
		setcolor(14); cout << y << " DONE :) ";
	}
	else if (x == 'n' || x == 'N')
	{
		Task[i].Done = 0;
		setcolor(12); cout << " x  :) :) ";
	}
}
void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
void design(){
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	//std::cout << "Font: Consolas, Size: 24\n";
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
void display_done(){
	if (Task.size() == 0){
		cout << "Sorry !! There are no tasks to view \n";
	}
	for (int i = 0; i<Task.size(); i++){
		if (Task[i].Done){
			cout << "Task Number [" << i + 1 << "]\n";
			cout << "Task title : " << Task[i].task_name << endl;
			cout << "Task deadline : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << endl;
			cout << "Task Priority : " << Task[i].priority << endl;
			cout << "Task Details : " << Task[i].details << endl;
			cout << "\t\t\tDone :)\n";

		}
		cout << "*************************\n";
	}

}
void delete_search(){
	char choice;

	int deleted;
	cout << "\n\t\t\t\t\t\t\tPress '0' To Cancel \r";
	cout << "Please Enter Number Of Task you want to delete : ";
	cin >> deleted;
	if (deleted == 0){//to cancel
		return;
	}
	else if (deleted > Task.size()){
		cout << "\t\t\tNo Task Found ! , Please Try Again :)\n";
		delete_search();
	}
	else{
		for (int i = deleted - 1; i < Task.size() - 1; i++)
		{
			Task[i].task_name = Task[i + 1].task_name;
			Task[i].deadline.day = Task[i + 1].deadline.day;
			Task[i].deadline.month = Task[i + 1].deadline.month;
			Task[i].deadline.year = Task[i + 1].deadline.year;
			Task[i].priority = Task[i + 1].priority;
			Task[i].details = Task[i + 1].details;
		}
		Task.pop_back();
		cout << "\t\t\t Task" << deleted << " Deleted succeefully :) \n";
	}
}
void Mark_Done(){
	int Num;
	char ans;
	bool found = false;
	while (true){
		system("cls");
		if (Task.size() == 0){

			cout << "\t \t *******************************\n\n";
			cout << "  \t \t\tNo Task to found \n \n";
			cout << "\t \t *******************************\n\n";
			system("pause");
			system("cls");
			Input();
		}
		if (Task.size() != 0){
			tasks_to_mark_done();
			//cout << "Sorry !! There are no tasks to view \n";

			cout << "Enter the number of the task you want to mark as done : ";
			cout << "\t\t\t\t\t\t press '0' to cancel" << endl;
			cin >> Num;
			if (Num <= Task.size() && Num > 0){
				Task[Num - 1].Done = 1;
				cout << "Task [" << Num << "] is done :)" << endl;
			}
			else if (Num>Task.size() || Num < 0){
				cout << "No task is found by this number " << endl;
			}
			else if (Num == 0){
				system("cls");
				Input();
			}
			cout << "Do you want to mark another task as done (Y/N) ? ";
			cin >> ans;
			if (ans == 'y' || ans == 'Y'){

				for (int i = 0; i < Task.size(); i++)
				{
					if (Task[i].Done != 1)
					{

						cout << "\t \t *******************************\n\n";
						cout << "Task number [" << i + 1 << "]" << endl << endl;
						cout << "Title : " << Task[i].task_name << "\n\n";
						cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
						cout << "Priority : " << Task[i].priority << "\n\n";
						cout << "Details : " << Task[i].details << "\n\n";
						cout << "\t \t *******************************\n\n";
						found = true;

					}
				}
				if (found == false)
				{
					system("cls");
					cout << "\n\t\t\t*********************\n";
					cout << "\n\t\t\t   No Tasks to view\n\n";
					cout << "\n\t\t\t*********************\n";
					system("pause");
					system("cls");
					Input();
				}
			}
			else if (ans == 'n' || ans == 'N'){
				system("cls");
				Input();
				//return ;
			}
			else {
				while (true){
					cout << "Please Enter 'Y' to continue or 'N' to go the menu";
					cin >> ans;
					if (ans == 'y' || ans == 'Y'){
						break;
					}
					else if (ans == 'n' || ans == 'N'){
						system("cls");
						Input();
					}
					else {
						continue;
					}
				}

			}


		}
	}
}
void tasks_to_mark_done(){

	for (int i = 0; i < Task.size(); i++)
	{
		if (Task[i].Done != 1)
		{

			cout << "\t \t *******************************\n\n";
			cout << "Task number [" << i + 1 << "]" << endl << endl;
			cout << "Title : " << Task[i].task_name << "\n\n";
			cout << "Due time : " << Task[i].deadline.day << "/" << Task[i].deadline.month << "/" << Task[i].deadline.year << "\n\n";
			cout << "Priority : " << Task[i].priority << "\n\n";
			cout << "Details : " << Task[i].details << "\n\n";
			cout << "\t \t *******************************\n\n";

		}
	}

}

