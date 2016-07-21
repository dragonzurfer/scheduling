#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <iterator>
using namespace std;
//pid is the process id, bt is the burst time, at is the arrival time, prio is
//the priority(if required) and mem is the memory required for this process
struct task {
	int pid, bt, at, prio;
	float mem;
};

//the function to sort an array of tasks based on priority
bool prSort(task a, task b)
{
	if (a.prio == b.prio)
		return(a.pid < b.pid);

	else return(a.prio < b.prio);
}

// function to sort array of tasks based on arrival time
bool sjfSort(task a, task b)
{
	if (a.at == b.at)
		return(a.pid < b.pid);

	else return(a.at < b.at);
}

//function to sort array of tasks based on arrival time
bool fcfsSort(task a, task b)
{
	if (a.at == b.at)
		return a.pid<b.pid;

	else
		return a.at<b.at;
}

//To compare the processes according to burst time and memory
struct taskCompare {
	bool operator() (const task a, const task b) const {

		if (a.bt == b.bt&&a.mem == b.mem)
			return(a.pid < b.pid);

		else if (a.bt == b.bt)
			return(a.mem < b.mem);

		else return a.bt < b.bt;
	}
};

void sjf()
{
	float availMem, overallMemory; int n;
	cout << "Enter number of processes ";
	cin >> n;
	vector<task> p(n); vector<task>::iterator it; vector<int> btOrig(n + 1, 0);
	for (int i = 0; i < n; i++)
	{
		cout << "arrival time";
		cin >> p[i].at;
		cout << "burst time:";
		cin >> p[i].bt;
		cout << "memory:";
		cin >> p[i].mem;
		p[i].pid = i + 1;
		btOrig[i+1] = p[i].bt;
	}

	cout << "Enter available memory\n"; cin >> overallMemory;

	sort(p.begin(), p.end(), sjfSort); it = p.begin();

	availMem = overallMemory;

	set<task, taskCompare> toEx; set<task, taskCompare>::iterator curr, its; task currCopy;
	//totalTA=totalTurnAround
	int flag = 0, totalTA = 0, ifTaskAlloc = 0, totalWait = 0, tasksCompl = 0, i = 0, flag2 = 0, flag3 = 0;
	list<task> activeProc; list<task>::iterator itl;
	//the bst currEx is based on the burst times of tasks that have arrived
	//the list activeProc maintains the tasks active at the given moment
	//the set currEx maintains the new processes starting at any instant and map prevEx is maintained
	//to acertain which processes have been paused. the element.second=0 if process is paused
	set<int>currEx; map<int, int>  prevEx; map<int, int>::iterator itm; set<int>::iterator setit;
	
	//again bsts used to minimise find times

	while (1)
	{
		int ifPrevEnd = 0, flag3 = 0; flag2 = 0;
		//On the first run print 0
		if (flag == 0)
		{
			cout << "0";
			flag = 1;
		}

		//vector of tasks has been sorted based on arrival time. So it can pick up from where the loop broke
		// in a previous iteration.
		while (it->at == i)
		{
			if (it->mem <= overallMemory)
				toEx.insert(*it);
				
			else
				tasksCompl++;

			if (next(it, 1) != p.end())
				it++;

			else
				break;
		}

		//activeProc is a std::list to make deletions easier
		itl = activeProc.begin();

		while (itl != activeProc.end())
		{
			curr = toEx.find(*itl);

			if (itl->bt - 1 == 0)
			{
				if (ifPrevEnd == 0)
					cout << "->";
				ifPrevEnd = 1;
				cout << 'p' << itl->pid << ',';
				totalTA += i - itl->at;
				totalWait += i - itl->at - btOrig[itl->pid];
				availMem += itl->mem;
				itm = prevEx.find(curr->pid);
				if (itm != prevEx.end())
					prevEx.erase(itm);
				//if current job is finished erase it from the bst of jobs 	
				toEx.erase(curr);
				itl = activeProc.erase(itl);
				tasksCompl++;
			}

			else
			{
				currCopy = *curr;
				toEx.erase(curr);
				prevEx.insert(make_pair(currCopy.pid, 0));
				//decrement burst times and reinsert into bst to sort correctly according to burst times
				currCopy.bt--;
				itl->bt--;
				toEx.insert(currCopy);
				itl++;
			}
		}

		if (ifPrevEnd == 1)
			cout << i;

		its = toEx.begin();

		availMem = overallMemory;

		while (availMem >= 0)
		{
			ifTaskAlloc = 0;

			if (its == toEx.end())
				break;

			if (its->mem <= availMem)
			{
				ifTaskAlloc = 1;
				availMem -= its->mem;

				itm = prevEx.find(its->pid);

				if (itm == prevEx.end())
				{
					currEx.insert(its->pid);

					activeProc.push_back(*its);
				}

				else
				{
					itm->second = 1;
				}

				its++;
			}

			if (ifTaskAlloc == 0)
				break;
		}

		//print the processes that have been paused
		for (itm = prevEx.begin(); itm != prevEx.end(); itm++)
		{
			if (itm->second == 0)
			{
				if (flag2 == 0)
					cout << "->";
				cout << "p" << itm->first << ',';
				flag2 = 1;
			}
		}

		if (flag2 == 1)
			cout << i;

		//print the processes that are starting
		for (setit = currEx.begin(); setit != currEx.end(); setit++)
		{
			if (flag3 == 0 && i != 0)
				cout << "->" << i;
			flag3 = 1;
			cout << ",p" << *setit;
		}

		currEx.clear();
		prevEx.clear();

		i++;

		if (tasksCompl == n)
			break;
	}

	cout << "\nAverage Turnaround time is " << (float)totalTA / (float)n << " sec(s)\n";
	cout << "Average Waiting time is " << (float)totalWait / (float)n << " sec(s)\n";
	
}

void fcfs()
{
	int n, overall;
	float turnaroundTime = 0, waitTime = 0, burstTotal = 0;
	cout << "\nEnter the number of process:";
	cin >> n;
	vector<int>list;
	vector<int>listTime;
	cout << "\nOverall memory:";
	cin >> overall;
	vector<task> a(n);
	for (int i = 0; i<n; i++) {
		cout << "\nEnter bt for task " << i + 1 << ":";
		cin >> a[i].bt;
		burstTotal += a[i].bt;
		cout << "\nEnter at for task" << i + 1 << ":";
		cin >> a[i].at;
		cout << "\nEnter memory for task" << i + 1 << ":";
		cin >> a[i].mem;
		a[i].pid = i;
	}
	//t is the time since start of the scheduler, mem is the memory that is
	//currently used, Set is the set that stores all the pids that are in the
	//memory buffer
	int time = 0, k = 0, i = 0, j = 0, t = 0, mem = 0;
	set <int> Set;
	sort(a.begin(), a.end(), fcfsSort);
	for (int i = 0; i<n; ++i) {
		if (a[i].mem > overall) {
			++k;
		}
	}
	if (a[0].at != 0)
		cout << 0;
	else
		cout << 0 << ",P" << a[0].pid + 1;
	//k shows the no of processes that are over
	while (k<n) {
		//i is the no of processes that have been pushed inside memory ie it is
		//the sum of processes that have already been executed and are being executed
		while (i<n) {
			if (a[i].at <= t) {
				if (a[i].mem > overall) {
					++i;
				}
				else if (a[i].mem + mem <= overall) {
					if (mem == 0) {
						if (a[i].at != 0)
							cout << " -> " << t << ",P" << a[i].pid + 1;
						else if (i != 0 && a[i].at > t)
							cout << t;
						else if(i != 0)
							cout << " -> " << t << ",P" << a[i].pid + 1;
					}
					mem += a[i].mem;
					if (mem - a[i].mem != 0)
						cout << " -> " << t << ",P" << a[i].pid + 1;
					Set.insert(i);
					++i;
				}
				else break;
			}
			else break;
		}
		//this is the loop that checks each and every process if it is over, if they
		//are, then they are removed from the memory and memory is freed
		for (set<int>::iterator it = Set.begin(); it != Set.end();) {
			a[*it].bt--;
			if (a[*it].bt == 0) {
				mem -= a[*it].mem;
				k++;
				//k is no of operations that are outputed
				cout << " -> P" << a[*it].pid + 1 << "," << t + 1;
				set<int>::iterator temp = it;
				++temp;
				turnaroundTime += t + 1 - a[*it].at;
				Set.erase(it);
				it = temp;
			}
			else
				++it;
		}
		t++;
	}
	waitTime = turnaroundTime - burstTotal;
	cout << "\nAverage turnaround time is: " << turnaroundTime / n;
	cout << "\nAverage wait time is: " << waitTime / n << "\n";
}

//Function for priority sort
void ps()
{
	float overallMemory; int n, currTime = 0, totalWait = 0, totalTA = 0;
	cout << "Enter number of processes ";
	cin >> n;
	vector<task> p(n); vector<task>::iterator itv;
	for (int i = 0; i < n; i++)
	{
		cout << "\nburst time:";
		cin >> p[i].bt;
		cout << "priority:";
		cin >> p[i].prio;
		cout << "memory:";
		cin >> p[i].mem;
		p[i].pid = i + 1;
	}

	cout << "Enter available memory"; cin >> overallMemory;

	sort(p.begin(), p.end(), prSort);

	int flag = 0, availMem = overallMemory;

	int time = 0, listIndex = 0, tasksCompl = 0, ifTaskAlloc = 0, index = 0,
		stFlag = 0, ifTaskCl = 0;
	list<task> activeProc; list<task>::iterator itl;

	while (1)
	{
		//Only for initial iteration
		if (flag == 0)
		{
			cout << "0"; flag = 1;
		}

		ifTaskCl = 0;

		itl = activeProc.begin();

		while (itl != activeProc.end())
		{
			itl->bt--;

			//When a process is completed, memory is freed and the process is removed
			//from the list
			if (itl->bt == 0)
			{
				if (ifTaskCl == 0)
					cout << "->";

				availMem += itl->mem;
				cout << 'p' << itl->pid << ',';
				ifTaskCl = 1;
				itl = activeProc.erase(itl);
				tasksCompl++;
				totalTA += time;
			}

			else
				itl++;			
		}

		if (ifTaskCl == 1)
			cout << time;
			
		//To check whether a new task can be added to the list
		stFlag = 0;
		while (availMem >0)
		{
			ifTaskAlloc = 0;

			if (index >= n)
				break;

			//If the memory required for the process is more than total memory available
			//skip the process
			if (p[index].mem > overallMemory)
			{
				index++; tasksCompl++; continue;
			}

			//If memory of the new task is less than available memory, then push the
			//process into the list
			else if (p[index].mem <= availMem)
			{
				ifTaskAlloc = 1;

				availMem -= p[index].mem;
				activeProc.push_back(p[index]);
				totalWait += time;

				if (stFlag == 0 && time != 0)
					cout << "->" << time;

				cout << ",p" << p[index].pid;
				index++;
				stFlag = 1;
			}

			if (ifTaskAlloc == 0)
				break;
		}

		time++;

		//Exit loop on completion of all the tasks
		if (tasksCompl == n)
			break;
	}

	cout << "\nAverage Turnaround time is " << (float)totalTA / (float)n << "sec(s)\n";
	cout << "Average Waiting time is " << (float)totalWait / (float)n << "sec(s)\n";

}

int main()
{
	int choose = 1;

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
