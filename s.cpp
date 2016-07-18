#include<bits/stdc++.h>
using namespace std;
struct task
{
  int bt,at,mem,pid;
};

bool compare(task a,task b)
{
  return a.at<b.at;
}

int main()
{
  int choice=1,n,overall;
  float waitTime,turnaroundTime;

  while(choice)
  {
    cout<<"\nEnter the number of process:";
    cin>>n;
    vector<int>list;
    vector<int>listTime;
    cout<<"\nOverall memory:";
    cin>>overall;
    const int constoverall=overall;
    vector<task> a(n);

    for(int i=0;i<n;i++)
    {
      cout<<"\nEnter bt for task "<<i+1<<":";
      cin>>a[i].bt;
      cout<<"\nEnter at for task"<<i+1<<":";
      cin>>a[i].at;
      cout<<"\nEnter memory for task"<<i+1<<":";
      cin>>a[i].mem;
      a[i].pid=i+1;
    }
    int time=0,k=0;
    sort(a.begin(),a.end(),compare);
    for(int i=0;i<n;i++)
    {
      if(a[i].mem<=constoverall)
      {
      if(a[i].at<=time)
        {
          waitTime=waitTime+(time-a[i].at);
          list.push_back(i);
          time+=a[i].bt;
          turnaroundTime=turnaroundTime+time-a[i].at;
          listTime.push_back(time);
          k++;
        }
        else
        {
          time=a[i].at;
          listTime.push_back(time);
          list.push_back(i);
          time+=a[i].bt;
          listTime.push_back(time);
        }
      }
      else
        continue;

    }

    vector<int>::iterator it1,it2;
    k=0;
    float size=a.end()-a.begin();

    cout<<"\nwaiting time:"<<waitTime/size<<" turnaround:"<<turnaroundTime/size;

    cout<<endl;

    for( it1=listTime.begin(),it2=list.begin();it1!=listTime.end(),it2!=list.end();it1++,it2++)
      cout<<"->P"<<*it2<<"->"<<*it1;
  }
}
