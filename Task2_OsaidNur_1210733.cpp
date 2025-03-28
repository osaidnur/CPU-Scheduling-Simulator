/*
Name : Osaid Hasan Nur
ID : 1210733
*/

#include <bits/stdc++.h>
#include <iostream>
#define TimeQuantum 5
using namespace std;

// struct of process ( PCB )
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime ;
    int comesAfter;
    int priority;
    int readyQueueArrival ;
    int counter ;
};


// to compare the processes depending on the arrival time 
bool compareArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}
bool compareBurst(Process a , Process b){
    return a.burstTime < b.burstTime ; 
}
bool CompareProcesses(const Process& a, const Process& b) {
    // Prioritize processes with earlier arrival times
    if (a.remainingTime != b.remainingTime) {
        return a.remainingTime < b.remainingTime;
    }

    // If arrival times are equal, favor those with shorter remaining time
    return a.readyQueueArrival < b.readyQueueArrival;
}

bool comparePriority(const Process& a, const Process& b) {
    // Prioritize processes with earlier arrival times
    if (a.priority != b.priority) {
        return a.priority < b.priority;
    }

    // If arrival times are equal, favor those with shorter remaining time
    return a.readyQueueArrival < b.readyQueueArrival;
}

calculateTime(map<int,int> waitingTime,map<int,int> lastTime, map<int,int>arrival ,int size ) {
     double avgWaitingTime=0 ;
    double avgTurnAroundTime=0 ;    
    for (int i = 1; i <= 7; i++)
    {
        avgWaitingTime+=waitingTime[i];
    }
    
    for (auto i : lastTime)
    {
        avgTurnAroundTime+= (i.second-arrival[i.first]);
    }
    
    cout << "Average waiting time = " << avgWaitingTime/size << endl;
    cout << "Average turnaround time = " << avgTurnAroundTime/size << endl;
    cout << "\n-----------------------------------------------------------------------\n" ;

}



void FCFS(vector<Process> processes){
 
 sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
    
    queue<Process> readyQueue;
    int time = 0 , size=processes.size();
    map<int,int> waitingTime ;
    map<int,int> lastTime , arrival ;
    vector<pair<int,int>> progress ;
    

    for (int i = 1; i <= 7; i++)
    {
        waitingTime[i] = 0; 
        arrival[processes[i].id] = processes[i].arrivalTime;  
    }
    
    cout << ">>>>> First Come First Served <<<<<" << endl; 
    while (time < 200 && (!readyQueue.empty() || !processes.empty())) {
        // Add processes that have arrived to the ready queue
        if (!processes.empty() && processes.front().arrivalTime <= time) {
            processes.front().readyQueueArrival = time ;
            readyQueue.push(processes.front());
            processes.erase(processes.begin());
        }

        // If there are processes in the ready queue, execute the process at the top
        if (!readyQueue.empty()) {
            Process current = readyQueue.front();
            readyQueue.pop();
            cout << "Time " << time << ": P" << current.id << " has started running\n";
            //progress.push_back({current.id,time})
            
            waitingTime[current.id]+=(time -current.arrivalTime) ;

            
            int remainingTime = current.burstTime;
            while (remainingTime > 0) {
               
                remainingTime--;
                time++;

                if(!processes.empty() && processes.front().arrivalTime == time){
                    processes.front().readyQueueArrival = time ; 
                    readyQueue.push(processes.front());  
                    processes.erase(processes.begin());
                }
            }
            lastTime[current.id] = time;
         
            
            current.arrivalTime = time + current.comesAfter;  
            current.readyQueueArrival = current.arrivalTime  ;
            processes.push_back(current);
            sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time

        } else cout << "DONE" <<endl; 
    }
    calculateTime(waitingTime,lastTime,arrival,size) ;
}

void SJF(vector<Process> processes){
     sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
    
    vector<Process> readyQueue;
    int time = 0 , size = processes.size();
   map<int,int> waitingTime ;
    map<int,int> lastTime , arrival ;
    vector<pair<int,int>> progress ;
    
cout << ">>>>> Shortest Job First <<<<< " << endl; 
    for (int i = 1; i <= 7; i++)
    {
        waitingTime[i] = 0; 
        arrival[processes[i].id] = processes[i].arrivalTime;  
    }

    while (time < 200 && (!readyQueue.empty() || !processes.empty())) {
        // Add processes that have arrived to the ready queue
        while (!processes.empty() && processes.front().arrivalTime <= time) {
            readyQueue.push_back(processes.front());
            processes.erase(processes.begin());
        }

        // If there are processes in the ready queue, execute the process at the top
        if (!readyQueue.empty()) {
            Process current = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            cout << "Time " << time << ": P" << current.id << " has started running\n";
            
            waitingTime[current.id]+=(time -current.arrivalTime) ;

            int remainingTime = current.burstTime;
            while (remainingTime > 0) {
                remainingTime--;
                time++;

                if(!processes.empty() && processes.front().arrivalTime == time){
                    readyQueue.push_back(processes.front());  
                    processes.erase(processes.begin());
                }
            }
            lastTime[current.id] = time;
            sort(readyQueue.begin(),readyQueue.end(),compareBurst);
            current.arrivalTime = time + current.comesAfter;  // Update return time
            processes.push_back(current);
            sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time

        } else {
            time++; 
        }
    }
  calculateTime(waitingTime,lastTime,arrival,size);
}

void SRTF(vector<Process>processes){

sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
    
    vector<Process> readyQueue;
    
    int time = 0,size=processes.size();
   map<int,int> waitingTime ;
    map<int,int> lastTime , arrival ;
    vector<pair<int,int>> progress ;
    
cout << ">>>>> Shortest Remaining Time First <<<<<" << endl; 
    for (int i = 1; i <= 7; i++)
    {
        waitingTime[i] = 0; 
        arrival[processes[i].id] = processes[i].arrivalTime;  
    }
    
    while (time < 200 && (!readyQueue.empty() || !processes.empty())) {
        // Add processes that have arrived to the ready queue
        while (!processes.empty() && processes.front().arrivalTime <= time) {
            processes.front().readyQueueArrival = time ; 
            readyQueue.push_back(processes.front());
            processes.erase(processes.begin());

        }
        sort(readyQueue.begin(),readyQueue.end(),CompareProcesses);

        // If there are processes in the ready queue, execute the first one
        if (!readyQueue.empty()) {
            Process current = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            cout << "Time " << time << ": P" << current.id << " has started running\n";
            waitingTime[current.id]+=(time -current.arrivalTime) ;
            
            int remainingTime = current.remainingTime;
            while (remainingTime > 0) {
                //cout << "Time " << time << ": Process " << current.id << " is running\n";
                remainingTime--;
                time++;

                if(!processes.empty() && processes.front().arrivalTime == time){
                    processes.front().readyQueueArrival = time ;
                    readyQueue.push_back(processes.front()); 
                    sort(readyQueue.begin(),readyQueue.end(),CompareProcesses); 
                    if(processes.front().remainingTime < remainingTime)
                    {
                        current.remainingTime = remainingTime ;
                        current.readyQueueArrival = time ;
                        readyQueue.push_back(current);
                        sort(readyQueue.begin(),readyQueue.end(),CompareProcesses); 
                        processes.erase(processes.begin());
                        break;
                    }
                    processes.erase(processes.begin());   
                }
            }
            
            // Process has finished its burst time, move to vector of processes again
            if(remainingTime == 0)
            {
            lastTime[current.id] = time;
            current.arrivalTime = time + current.comesAfter;
            current.remainingTime = current.burstTime;  // Update return time
            processes.push_back(current);
            sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
            }
        } else {
            time++; 
        }
    }
calculateTime(waitingTime,lastTime,arrival,size );
}

void RR(vector <Process> processes) {
    
    sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
    
    queue<Process> readyQueue;
    
    int time = 0 , size=processes.size();
     map<int,int> waitingTime ;
    map<int,int> lastTime , arrival ;
    vector<pair<int,int>> progress ;
    
    cout << ">>>>> Round Robin with Quantum = 5 <<<<<" << endl; 
    for (int i = 1; i <= 7; i++)
    {
        waitingTime[i] = 0; 
        arrival[processes[i].id] = processes[i].arrivalTime;  
    }

    while (time < 200 && (!readyQueue.empty() || !processes.empty())) {
        // Add processes that have arrived to the ready queue
        while (!processes.empty() && processes.front().arrivalTime <= time) {
            processes.front().readyQueueArrival = time ; 
            readyQueue.push(processes.front());
            processes.erase(processes.begin());
        }
        

        // If there are processes in the ready queue, execute the first one
        if (!readyQueue.empty()) {
            Process current = readyQueue.front();
            readyQueue.pop();
            cout << "Time " << time << ": P" << current.id << " has started running\n";
            waitingTime[current.id]+=(time -current.arrivalTime) ;
            int remainingTime = current.remainingTime;
            int limit = min(TimeQuantum,remainingTime) ;
            for(int i = 0 ; i < limit ; i++ ) {
                remainingTime--;
                time++;

                if(!processes.empty() && processes.front().arrivalTime == time){
                     processes.front().readyQueueArrival = time ;
                    readyQueue.push(processes.front()); 
                  
                    processes.erase(processes.begin());   
                }
            }
                       
            if(remainingTime == 0)
            {
            lastTime[current.id] = time;
            current.arrivalTime = time + current.comesAfter;
            current.remainingTime = current.burstTime;  // Update return time
            current.readyQueueArrival = current.arrivalTime ;
            processes.push_back(current);
            sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
            }
            else{
              current.remainingTime = remainingTime ;
              readyQueue.push(current);  
            }
        } else {
            time++; 
        }
    }
calculateTime(waitingTime,lastTime,arrival,size) ;

}


void Priority_prem(vector <Process> processes) {
    sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
    
    vector<Process> readyQueue;
    map<int,int> waitingTime ;
    map<int,int> lastTime , arrival ;
    vector<pair<int,int>> progress ;
    map<int,int> priority ;
    for (int i = 1; i <= 7; i++)
    {
        waitingTime[i] = 0;
        arrival[processes[i].id] = processes[i].arrivalTime; 
        priority[processes[i-1].id] = processes[i-1].priority; 
    }
    int time = 0 , size=processes.size();
  cout << ">>>>> Preemptive Priority Scheduling <<<<<" << endl; 

    while (time < 200 && (!readyQueue.empty() || !processes.empty())) {
        // Add processes that have arrived to the ready queue
        while (!processes.empty() && processes.front().arrivalTime <= time) {
            processes.front().readyQueueArrival = time ; 
            readyQueue.push_back(processes.front());
            processes.erase(processes.begin());

        }
        sort(readyQueue.begin(),readyQueue.end(),comparePriority);

        // If there are processes in the ready queue, execute the first one
        if (!readyQueue.empty()) {
            Process current = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            cout << "Time " << time << ": P" << current.id << " has started running\n";
            waitingTime[current.id]+=(time -current.arrivalTime) ;

            int remainingTime = current.remainingTime;
            while (remainingTime > 0) {
                remainingTime--;
                time++;
                
                for (int i = 0; i < readyQueue.size(); i++)
                {
                readyQueue[i].counter ++ ;
                if(readyQueue[i].counter ==5 ){
                    readyQueue[i].priority -- ;
                    readyQueue[i].counter = 0 ; 
                    if (readyQueue[i].priority <0) readyQueue[i].priority = 0 ;
                }
                }
                sort(readyQueue.begin(),readyQueue.end(),comparePriority);
                if(readyQueue.front().priority < current.priority )
                    {
                        current.remainingTime = remainingTime ;
                        current.readyQueueArrival = time ;
                        readyQueue.push_back(current);
                        sort(readyQueue.begin(),readyQueue.end(),comparePriority); 
                        break ;
                    }
                if(!processes.empty() && processes.front().arrivalTime == time){
                    processes.front().readyQueueArrival = time ;
                    readyQueue.push_back(processes.front()); 
                    sort(readyQueue.begin(),readyQueue.end(),comparePriority); 
                    if(processes.front().priority < current.priority)
                    {
                        current.remainingTime = remainingTime ;
                        current.readyQueueArrival = time ;
                        readyQueue.push_back(current);
                        sort(readyQueue.begin(),readyQueue.end(),comparePriority); 
                        processes.erase(processes.begin());
                        break;
                    }
                    processes.erase(processes.begin());   
                }

            }
            
            sort(readyQueue.begin(),readyQueue.end(),comparePriority);
            
            if(remainingTime == 0)
            {
      
            lastTime[current.id] = time;
            current.arrivalTime = time + current.comesAfter;  // Update return time
            current.readyQueueArrival = current.arrivalTime ;
            current.priority = priority[current.id] ;
            current.counter= 0 ;
            current.remainingTime = current.burstTime ; 
            processes.push_back(current);
            sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
            
            }
        } else {
            time++; 
        }
    }
calculateTime(waitingTime,lastTime,arrival,size) ;

}


void Priority_non(vector <Process> processes) {
     sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
    
    vector<Process> readyQueue;
    
    int time = 0 , size=processes.size();
     map<int,int> waitingTime,priority ;
    map<int,int> lastTime , arrival ;
    vector<pair<int,int>> progress ;
    
    cout << ">>>>> Non-preemptive Priority Scheduling <<<<< " << endl ;
    for (int i = 1; i <= 7; i++)
    {
        waitingTime[i] = 0; 
        arrival[processes[i].id] = processes[i].arrivalTime;  
        priority[processes[i-1].id] = processes[i-1].priority; 
    }


    while (time < 200 && (!readyQueue.empty() || !processes.empty())) {
        // Add processes that have arrived to the ready queue
        while (!processes.empty() && processes.front().arrivalTime <= time) {
            processes.front().readyQueueArrival = time ; 
            readyQueue.push_back(processes.front());
            processes.erase(processes.begin());
        }
        sort(readyQueue.begin(),readyQueue.end(),comparePriority);
        // If there are processes in the ready queue, execute the first one
        if (!readyQueue.empty()) {
            Process current = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            cout << "Time " << time << ": P" << current.id << " has started running\n";
            waitingTime[current.id]+=(time -current.arrivalTime) ;


            int remainingTime = current.burstTime;
            while (remainingTime > 0) {
                remainingTime--;
                time++;

                if(!processes.empty() && processes.front().arrivalTime == time){
                     processes.front().readyQueueArrival = time ; 
                    readyQueue.push_back(processes.front());  
                    processes.erase(processes.begin());
                }
            }
            sort(readyQueue.begin(),readyQueue.end(),comparePriority);
            lastTime[current.id] = time;
            current.arrivalTime = time + current.comesAfter;  // Update return time
            current.readyQueueArrival = current.arrivalTime ;
            current.priority = priority[current.id] ;
            processes.push_back(current);
            sort(processes.begin(), processes.end(), compareArrival);  // Sort by arrival time
            for (int i = 0; i < readyQueue.size(); i++)
            {
                if(time - readyQueue[i].readyQueueArrival >=5){
                    readyQueue[i].priority -= ((time - readyQueue[i].readyQueueArrival)/5);
                    if (readyQueue[i].priority <0) readyQueue[i].priority = 0 ;
                }
            }
            sort(readyQueue.begin(),readyQueue.end(),comparePriority); 
        } else {
            time++; 
        }
    }
calculateTime(waitingTime,lastTime,arrival,size );



}

int main() {
    vector<Process> processes = {
        {1, 0, 10, 10, 2, 3}, 
        {2, 1, 8, 8, 4, 2},
        {3, 3, 14, 14, 6, 3},
        {4, 4, 7, 7, 8, 1},
        {5, 6, 5, 5, 3, 0},
        {6, 7, 4, 4, 6, 1},
        {7, 8, 6, 6, 9, 2} ,
    };


    FCFS(processes);
    
    SJF(processes);
    SRTF(processes);
    
    RR(processes) ;
    
    Priority_prem(processes) ;
    
    Priority_non(processes) ;


    return 0;
}
