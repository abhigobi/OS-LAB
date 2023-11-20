#include<iostream>
#include <queue>
using namespace std;

struct process{
  int id;
  int at;
  int bt;
  int wt;
  int tat;
};

int main(){

int n,tq;
int i=0;
int count=0;
cout<<"Enter the number of processes ";
cin>>n;
cout<<"Enter the time-quntum";
cin>>tq;

struct process p[10];
for(int i=0;i<n;i++){
    p[i].id=i;
    cout<<"Enter the arraval time";
    cin>>p[i].at;
    cout<<"Enter the burst time";
    cin>>p[i].bt;
}

queue<process> q;

q.push(p[i]);

while(!q.empty()){

process exe = q.front();
    if(exe.bt > tq){
      count+=tq;
      exe.bt-=tq;
    }
    else{
      count+=exe.bt;
      exe.bt=0;
      for(int j=0;j<n;j++){
          if(p[j].id==exe.id){
            
            p[j].wt= count - p[j].at - p[j].bt;
            p[j].tat = p[j].wt+p[j].bt;
          }
          cout<<"Process"<<exe.id<<"Ended at = "<<count<<endl;
      }
    }
    
    if(p[i+1].at<=count){
        for(int x=i+1;x<n;x++){
            if(p[x].at<=count){
              q.push(p[x]);
              i++;
            }
        }
    }
    if(exe.bt>0){
      q.push(exe);
      q.pop();
    }
    else{
      q.pop();
    }
  
}

float avgwt=0;
float avgtat=0;

cout<<"id\tat\tbt\twt\ttat"<<endl;
for(int j=0;j<n;j++){
    process pr = p[j];
    cout<<pr.id<<"\t"<<pr.at<<"\t"<<pr.bt<<"\t"<<pr.wt<<"\t"<<pr.tat<<endl;
    avgwt+=pr.wt;
    avgtat+=pr.tat;
}
avgwt = avgwt/n;
avgtat = avgtat/n;

cout<<"Avreage wating time = "<<avgwt<<endl;
cout<<"Average tat"<<avgtat<<endl;
}
