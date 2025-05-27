
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<vector>
#include <map>
#include <queue>
#include<string>
#include<climits>
#include<algorithm>
#include <iomanip>

using namespace std;

struct Schedule
{
    string company;
    float start;
    float end;
    int panel;
    int round;

};

struct Student{
    string id;
    map<string,int> interviews;// company name -> rounds to be completed
    float currentTime;
};

struct CompanyParams{
    int rounds;
    int panels;
    int usedPanels;
    float duration;
    float currentTime;
};


struct CompareStudent {
    bool operator()(const Student& a, const Student& b) {
        return a.currentTime > b.currentTime;  
    }
};



float scheduleInterviews(priority_queue<Student, vector<Student>, CompareStudent>& students,map<string , CompanyParams>& companies, map<string ,vector<Schedule>>& InterviewSchedules){
      float totalTimeTaken = 0;
      while(!students.empty()){
            Student s = students.top();
            students.pop();
            float companyTime = float(INT_MAX);
            string company;
            Schedule schedule;
            float time, currCompanyTime;
             for (const auto& [c, r] : s.interviews) {
                  currCompanyTime = companies[c].currentTime;
                  if(currCompanyTime < companyTime){
                        companyTime = currCompanyTime;
                        company = c;
                  }
            }

            time = max(companyTime, s.currentTime);

            schedule.company = company;
            schedule.end = time+companies[company].duration;
            
            totalTimeTaken = max(schedule.end,totalTimeTaken);

            schedule.start = time;
            schedule.panel = companies[company].panels - companies[company].usedPanels+1;
            schedule.round = companies[company].rounds-s.interviews[company]+1;
            InterviewSchedules[s.id].push_back(schedule);
            if(schedule.panel == companies[company].panels){
                companies[company].currentTime = schedule.end;
                companies[company].usedPanels = companies[company].panels;
            }else{
                companies[company].currentTime = time;
                companies[company].usedPanels -= 1;
            }
            s.currentTime = schedule.end;
            s.interviews[company] = s.interviews[company] -1;
            if(s.interviews[company] == 0){
                  s.interviews.erase(company);
            }
            if(s.interviews.size() != 0){
                students.push(s);
            }

      }
      
      return totalTimeTaken;

}

int main() {
    float startTime , endTime;
    map<string ,vector<Schedule>> InterviewSchedules;
    cout << "Enter start and end time (separated by space): ";
    cin >> startTime >> endTime;
    startTime *= 60;
    endTime *= 60;
    cin.ignore(); // Clear newline after reading times

    map<string, CompanyParams> companies;
    string name;

    // Input for companies
    while (true) {
        cout << "\nEnter company name (or type 'stop' to finish): ";
        getline(cin, name);

        if (name == "stop") break;
        
        CompanyParams c;

        cout << "Enter number of rounds: ";
        cin >> c.rounds;

        cout << "Enter number of panels: ";
        cin >> c.panels;

        cout << "Enter interview duration (in minutes): ";
        cin >> c.duration;

        c.usedPanels = c.panels;
        c.currentTime = startTime;

        companies[name] = c;

        cin.ignore(); // Ignore leftover newline after numeric input
    }

    // Input for students
    priority_queue<Student, vector<Student>, CompareStudent> students;
    while (true) {
        string studentId;
        cout << "\nEnter student ID (or type 'stop' to finish): ";
        getline(cin, studentId);

        if (studentId == "stop") break;

        Student s;
        s.id = studentId;
        s.currentTime = startTime;

        while (true) {
            string compName;
            cout << "Enter company name student is selected in (or 'done' to stop): ";
            getline(cin, compName);

            if (compName == "done") break;

            if (companies.find(compName) != companies.end()) {
                s.interviews[compName] = companies[compName].rounds;
            } else {
                cout << "Company not found!\n";
            }
        }

        students.push(s);
    }


    float totalTimeTaken = scheduleInterviews(students, companies,InterviewSchedules);

    if(totalTimeTaken > endTime){
            cout<<"The interviews cannot be scheduled with the given requirements"<<endl;
            return 0;
      }
    for(const auto& pair: InterviewSchedules){
        const string& student = pair.first;
        const vector<Schedule>& schedules = pair.second;
        cout<<"Student: "<<student<<endl;
        cout<<"Company "<<" Round "<<" Start "<<" End "<<" Panel "<<endl;
        for(const Schedule& schedule: schedules){
            int startTime = (int)schedule.start;
            int endTime = (int)schedule.end;
        cout<<schedule.company<<" "<<" "<<schedule.round<<" "<<startTime/60<<":"<< setw(2) << setfill('0')<<startTime%60<<" "<<endTime/60<<":"<< setw(2) << setfill('0')<<endTime%60<<" "<<schedule.panel<<endl;
        }
        cout<<endl;
    }

    return 0;
}
















