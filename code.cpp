/*
-> Author - Edwin Nduti
-> Description - The code is a simulation and reads the 
                processList.txt file using the ifstream type,
                creates a process, schedules its execution order using a queue.
*/


// imported libs
#include<iostream>
#include<queue>
#include<string>
#include<fstream>

using namespace std;

class Process;

queue<Process> procList;

// Process class that defines a process object
class Process{
    private:
        int ID;
        int execTime;
    public:
        Process(int newID, int newTime){
            ID = newID;
            execTime = newTime;
        }
        // execute method for executing a process
        void execute(){
            if(execTime == 0){
                cout<<"Process with ID : "<<ID<<" is Complete! "<<endl;
            }
            else{
                execTime--;
                cout<<"Process with ID : "<<ID<<" needs "<<execTime<<" more ms of execution"<<endl;
                procList.push(*this);
            }
        }
        // getID method to return the ID
        int getID(){
            return ID;
        }
        // getTime method to give the execution time
        int getTime(){
            return execTime;
        }
        // print method to display remaining time
        void Print(){
            cout<<"Process : "<<ID<<" Remaining Time : "<<execTime<<endl;
        }
};

// the main function
int main(){
    string line;
    ifstream fin ("processList.txt"); // similar to fin.open("processList.txt");

    vector<Process> record;
    if (fin.is_open()) {
        cout << "file opened"<<endl;
    }

    // Read a Line from File
    while (getline(fin, line)) {    // you can use while(!fin.eof){getline(fin, line);....}
        // check if line exists
        if(line.size() > 0) {
            string id="";
            string t="";
            int i=1;
            for(char c : line){
                if(c == ' '){
                    i=2;
                    continue;
                }
                if(i == 1){
                    id+=c;
                }
                if(i == 2){
                   t+=c;
                }
            }
            Process p(stoi(id),stoi(t));
            procList.push(p);
            record.push_back(p);
            
        }
    }
    // Close the file
    fin.close();

    //Displaying all the processes
    for(auto i=record.begin();i!=record.end();i++){
        i->Print();
    }

    //Scheduling
    while(!procList.empty()){
        Process p = procList.front();
        procList.pop();
        p.execute();
    }

    // exit program
    return 0;
}
