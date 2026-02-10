#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

enum class Priority {
	Less = 1,
	Medium,
	Crucial,
};

class Task {
public:
	int taskID;
	string title;
	string description;
	Priority priority;
	bool isCompleted;
	time_t deadline;

	Task(int id, string t, string d, Priority p, time_t dl, bool status = false)
	{
		taskID = id;
		title = t;
		description = d;
		priority = p;
		isCompleted = status;
		deadline = dl;
	}
};

class taskManager {
private:
	vector<Task> tasks;
	string priorityconvert(Priority p)
	{
		switch (p)
		{
		case Priority::Less: return "Less";
		case Priority::Medium: return "Medium";
		case Priority::Crucial: return "Crucial";
		default: return	"Invalid.";
		}
	}

public:
	void addTask()
	{
		int taskID;
		string title, description;
		int choice;
		int day, month, year;

		cout << "ID of the task: " << "\n";
		cin >> taskID;
		cin.ignore();

		cout << "Title of the task: " << "\n";
		getline(cin, title);

		cout << "Description of the task: " << "\n";
		getline(cin, description);

		cout << "Priority of the task: [1: Less | 2: Medium | 3: Crucial]" << "\n";
		cin >> choice;

		Priority priority;
		if (choice == 1)
			priority = Priority::Less;
		else if (choice == 2)
			priority = Priority::Medium;
		else if (choice == 3)
			priority = Priority::Crucial;
		else {
			cout << "Invalid request." << "\n";
			return;
		}

		cout << "Deadline of the task: [DD MM YYYY]";
		cin >> day >> month >> year;

		tm deadlinetime = {};
		deadlinetime.tm_mday = day;
		deadlinetime.tm_mon = month - 1;
		deadlinetime.tm_year = year - 1900;

		time_t deadline = mktime(&deadlinetime);

		tasks.emplace_back(Task(taskID, title, description, priority, deadline,false));
		cout << "Successful.\n";
	}

	void removeTask()
	{
		int taskID;

		if (tasks.empty())
		{
			cout << "No tasks exists in system." << "\n";
			return;
		}

		cout << "ID of the task: " << "\n";
		cin >> taskID;

		for (auto x = tasks.begin(); x != tasks.end(); ++x)
		{
			if (x->taskID == taskID)
			{
				tasks.erase(x);
				cout << "Successful." << "\n";
				return;
			}
		}
		cout << "Task not found." << "\n";
	}

	void markCompleted()
	{
		int taskID;

		if (tasks.empty())
		{
			cout << "No tasks exists in system." << "\n";
			return;
		}

		cout << "ID of the task: " << "\n";
		cin >> taskID;
		cin.ignore();

		for (auto& Task : tasks)
		{
			if (Task.taskID == taskID)
			{
				if (!Task.isCompleted)
				{
					Task.isCompleted = true;
					cout << "Task marked completed." << "\n";
					return;
				}
				else
				{
					cout << "Task already has been completed." << "\n";
					return;
				}
			}
		}

		cout << "Task not found." << "\n";
	}

	void displayTasks()
	{
		if (tasks.empty())
		{
			cout << "No tasks exists in system." << "\n";
			return;
		}
		for (const auto& Task : tasks)
		{
			cout << "ID: " << Task.taskID << "\n";
			cout << "Title: " << Task.title << "\n";
			cout << "Description: " << Task.description << "\n";
			cout << "Priority: " << priorityconvert(Task.priority) << "\n";
			cout << "Status: " << (Task.isCompleted ? "Completed." : "Not Completed.") << "\n";
			tm timeinfo;
			localtime_s(&timeinfo, &Task.deadline);
			cout << "Date: " << timeinfo.tm_mday << "/" << (timeinfo.tm_mon + 1) << "/" << (timeinfo.tm_year + 1900) << "\n";
		}
	}

	void sortPriority()
	{
		if (tasks.empty())
		{
			cout << "No tasks exists in system." << "\n";
			return;
		}

		sort(tasks.begin(), tasks.end(),
			[](const Task& x, const Task& y)
			{
				return static_cast<int>(x.priority) > static_cast<int>(y.priority);
			});

		cout << "Sorted successfully." << "\n";
	}


	void sortDeadline()
	{
		if (tasks.empty())
		{
			cout << "No tasks exists in system." << "\n";
			return;
		}

		sort(tasks.begin(), tasks.end(),
			[](const Task& x, const Task& y)
			{
				return x.deadline < y.deadline;
			});

		cout << "Sorted successfully." << "\n";
	}

	void saveFile()
	{
		ofstream file("tasks.txt");
		if (!file.is_open())
		{
			cout << "Failed to open the file." << "\n";
			return;
		}

		for (const auto& Task : tasks)
		{
			file << Task.taskID << " | ";
			file << Task.title << " | ";
			file << Task.description << " | ";
			file << static_cast<int>(Task.priority) << " | ";
			file << Task.isCompleted << " | ";
			file << Task.deadline << "\n";
		}
		file.close();

		cout << "File saved successfully." << "\n";
	}

	void loadFile()
	{
		ifstream file("tasks.txt");
		if (!file.is_open())
		{
			cout << "No tasks found saved in the file, opening a new one..." << "\n";
			return;
		}

		tasks.clear();
		string task;

		while (getline(file, task))
		{
			int taskID;
			string title;
			string description;
			int priority;
			bool isCompleted;
			time_t deadline;

			size_t size;

			size = task.find('|');
			taskID = stoi(task.substr(0, size));
			task.erase(0, size + 1);

			size = task.find('|');
			title = task.substr(0, size);
			task.erase(0, size + 1);

			size = task.find('|');
			description = task.substr(0, size);
			task.erase(0, size + 1);

			size = task.find('|');
			priority = stoi(task.substr(0, size));
			task.erase(0, size + 1);


			size = task.find('|');
			isCompleted = stoi(task.substr(0, size));
			task.erase(0, size + 1);

			deadline = stoll(task);

            tasks.emplace_back(Task(taskID, title, description, static_cast<Priority>(priority), isCompleted, deadline));
		}

		file.close();
		cout << "Tasks loaded successfully." << "\n";
	}
};


void menu()
{
	cout << "\n"<< "----- TASK MANAGER -----" << "\n";
	cout << "1. Add Task		2. Remove Task" << "\n";
	cout << "3. Mark Task Complete		4. List Tasks" << "\n";
	cout << "5. Sort by Priority		6. Sort by Deadline" << "\n";
	cout << "7. Exit" << "\n";
	cout << "Choice: ";
}

int main()
{
	taskManager task_Manager;
	int choice;
	task_Manager.loadFile();
	do {
		menu();
		cin >> choice;
		cin.ignore();

		switch (choice)
		{
		case 1:
			task_Manager.addTask();
			break;
		case 2:
			task_Manager.removeTask();
			break;
		case 3:
			task_Manager.markCompleted();
			break;
		case 4:
			task_Manager.displayTasks();
			break;
		case 5:
			task_Manager.sortPriority();
			break;
		case 6:
			task_Manager.sortDeadline();
			break;
		case 7:
			cout << "Exiting the program..";
			break;
		default:
			cout << "Invalid.";
			break;
		}
	} while (choice != 7);

	task_Manager.saveFile();
	return 0;
}

