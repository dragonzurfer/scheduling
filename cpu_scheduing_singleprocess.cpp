#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

struct task {
	int pid, bt, at, prio;
	float mem;
};

//comparator functions for sorting the tasks
bool prSort(task a, task b)
{
	if (a.prio == b.prio)
		return(a.pid < b.pid);

	else return(a.prio < b.prio);
}

bool sjfSort(task a, task b)
{
	if (a.at == b.at)
		return(a.pid < b.pid);

	else return(a.at < b.at);
}

bool fcfsSort(task a, task b)
{
	if (a.at == b.at)
		return a.pid<b.pid;

	else
		return a.at<b.at;
}

//comparator for set toEx
struct taskCompare {
	bool operator() (const task a, const task b) const {
		
		if (a.bt == b.bt)
			return(a.pid < b.pid);
		
		else return a.bt < b.bt;
	}
};

void fcfs()
{
	float overallMemory; int n, totalWait = 0, totalTA = 0, flag=0, currTime = 0, flag2=0, prevPrint=0;
	cout << "\nEnter the number of processes: ";
	cin >> n;
	cout << "\nEnter Overall memory: ";
	cin >> overallMemory;
	vector<task> a(n);
	for (int i = 0; i < n; i++) {
		cout << "\nEnter burst time for task " << i + 1 << ":";
		cin >> a[i].bt;
		cout << "\nEnter arrival time for task " << i + 1 << ":";
		cin >> a[i].at;
		cout << "\nEnter memory for task " << i + 1 << ":";
		cin >> a[i].mem;
		a[i].pid = i + 1;
	}

	sort(a.begin(), a.end(), fcfsSort);

	for (int i = 0; i < n; i++)
	{
		if (a[i].mem <= overallMemory)
		{
			if (a[i].at > currTime)
			{
				currTime = a[i].at;
			}
			totalWait += currTime-a[i].at;
			if (flag == 0)
			{
				cout << 0; flag = 1;
			}

			if (prevPrint != currTime)
				cout <<"->"<< currTime;

			cout << "->" << 'p' << a[i].pid;

			cout << "->" << currTime + a[i].bt;

			prevPrint = currTime + a[i].bt;

			currTime += a[i].bt;
			totalTA += currTime - a[i].at;
		}
	}

	cout << "\nAverage Turnaround time is " << (float)totalTA / (float)n << " sec(s)\n";
	cout << "Average Waiting time is " << (float)totalWait / (float)n << " sec(s)\n";
}

void ps()
{
	float overallMemory; int n, currTime = 0, totalWait = 0, totalTA = 0;
	cout << "Enter number of processes ";
	cin >> n;
	vector<task> p(n);
	for (int i = 0; i < n; i++)
	{
		cout << "\nburst time: ";
		cin >> p[i].bt;
		cout << "priority: ";
		cin >> p[i].prio;
		cout << "memory: ";
		cin >> p[i].mem;
		p[i].pid = i + 1;
	}

	cout << "Enter available memory"; cin >> overallMemory;

	sort(p.begin(), p.end(),prSort);

	int flag = 0;
	
	for (int i = 0; i < n; i++)
	{
		totalWait += currTime;

		if (p[i].mem <= overallMemory)
		{
			if (flag == 0)
			{
				cout << "0"; flag = 1;
			}

			//the current time is incremented by the burst time of th executed task
			currTime += p[i].bt; totalTA += currTime;

			cout << "->p" << p[i].pid << "->" << currTime;
		}
	}

	cout << "\nAverage Turnaround time is " << (float)totalTA / (float)n << " sec(s)\n";
	cout << "Average Waiting time is " << (float)totalWait / (float)n << " sec(s)\n";
	
}

void sjf()
{
	float overallMemory; int n, currTime = 0, maxTime = 0;
	cout << "Enter number of processes ";
	cin >> n;
	//burstAr to maintain the original burst times of all tasks as we'll be changing the burst times of tasks in the vector 
	//of tasks
	vector<int> burstAr; burstAr.push_back(0);
	vector<task> p(n); vector<task>::iterator it;
	for (int i = 0; i < n; i++)
	{
		cout << "arrival time: ";
		cin >> p[i].at;
		cout << "burst time: ";
		cin >> p[i].bt;
		burstAr.push_back(p[i].bt);
		maxTime += p[i].bt;
		cout << "memory: ";
		cin >> p[i].mem;
		p[i].pid = i + 1;
	}

	cout << "Enter available memory: "; cin >> overallMemory;

	sort(p.begin(), p.end(), sjfSort); it = p.begin();

	//toEx is the bst that maintains all the tasks that have arrived at or 
	//before a given instance of time sorted by burst times of the tasks
	set<task, taskCompare> toEx; set<task, taskCompare>::iterator curr; task currCopy; 
	int i = 0, tasksCompl=0, flag = 0, prevPid = -1, ifTaskCompl = 0;
	int prevPrinted, totalTA=0, totalWait = 0;

	while(1)
	{
		//as & when tasks arrive push into bst
		while (it->at == i)
		{
			if (it->mem <= overallMemory)
				toEx.insert(*it);

			else
				tasksCompl++;

			if(next(it,1)!=p.end())
			it++;

			else
				break;
		}

		if(toEx.size() != 0)
		{
			//In the first iteration print 0
			if (flag == 0)
			{
				flag = 1;
				cout << "0";
				prevPrinted = 0;
			}

			curr = toEx.begin();	

			//To handle cases where numbers are printed like 0->0 etc.
			if (curr->pid != prevPid&&prevPrinted!=i)
			cout << "->" << i;
		
			if(curr->pid!=prevPid)
			cout << "->p" << curr->pid;

			//decrement the burst time of currently executing task and reinsert into bst
			prevPid = curr->pid; 
			currCopy = *curr; toEx.erase(curr); currCopy.bt--; toEx.insert(currCopy);

			//Task is completed
			if (currCopy.bt == 0)
			{
				tasksCompl++;
				cout << "->" << i+1;
				curr = toEx.find(currCopy);
				//Erase current copy from the bst toEx
				toEx.erase(curr);
				prevPrinted = i + 1;

				totalTA += i + 1 - currCopy.at;
				totalWait += i + 1 - currCopy.at - burstAr[currCopy.pid];
			}
		}

		i++;

		if (tasksCompl == n)
			break;
	}

	cout << "\nAverage Turnaround time is " << (float)totalTA / (float)n << " sec(s)\n";
	cout << "Average Waiting time is " << (float)totalWait / (float)n << " sec(s)\n";
}

int main()
{
	int choose=1;

	while (choose) 
	{
		cout << "Select scheduling option\nFirst Come First Serve (1)\nShortest Job First (2)\nPriority Scheduling (3)\nExit (0)\n";
		
		cin >> choose;

		switch (choose)
		{
		case 1:
			fcfs(); break;
		case 2:
			sjf(); break;
		case 3:
			ps(); break;
		case 0:
			break;
		default:
			cout << "No such option available\n"; continue;
		}
	}

}