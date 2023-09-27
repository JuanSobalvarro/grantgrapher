#include "processes.h"

class process
{
    public:
        string name;
        int exectime;
        int priority;
        // color is set at the print
        int color;
        
        void print()
        {
            cout << name << "\t" << exectime << "\t" << priority << endl;
        }
};

vector<process> processes;

vector<string> modes = {"FCFS", "SJF", "BP", "RR"};
int sortmodeind;

const int grant_width = 100;

bool loadProcesses(char *filename)
{
    // clear processes vector to avoid errors
    processes.clear();

    // open file stream as input
    fstream file;
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cout << "Error opening the file\n";
        return false;
    }

    vector<string> row;
    string line, word;

    // omit the first line of the csv
    getline(file, line);

    // while getline gets a line we add the process
    for (int i = 0; getline(file, line); i++)
    {
        process p;
        row.clear();

        stringstream str(line);

        // get word with separation of comma
        while(getline(str, word, ','))
            row.push_back(word);
        
        // once we get the row we add values to the process p
        p.name = row[0];
        //cout << row[1] << endl;
        p.exectime = stoi(row[1]);
        p.priority = stoi(row[2]);
        //at the end we add p to the vector or processes
        processes.push_back(p);
    }   

    return true;
}

bool sortProcesses(int index)
{

    cout << "uwu" << index << endl;
    sortmodeind = index;
    switch (index)
    {
    case 0:
        //FCFS();
        break;
    case 1:
        SJF();
        break;
    case 2:
        BP();
        break;
    case 3:
        RR();
        break;
    default:
        return false;
    }
    return true;
}

bool printProcesses()
{
    // for (int i = 0; i < processes.size(); i++)
    // {
    //     processes[i].print();
    // }

    HANDLE col;
    col =  GetStdHandle(STD_OUTPUT_HANDLE);

    // get console colour information
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(col, &csbi);

    int len = 0, n = n;
    for (int i = 0; i < n; i++)
    {
        len += processes[i].exectime; 
    }
    
    cout << "Sorted processes using " << modes[sortmodeind] << endl; 

    // first put names
    for (int i = 0; i < n; i++)
    {
        // draws set the width of the process
        int draws = processes[i].exectime * grant_width / len;
        // here we set the attribute of the console text
        SetConsoleTextAttribute(col, i%16 + 1);
        cout << processes[i].name;
        for (int j = 0; j < draws - processes[i].name.size(); j++)
        {
            cout << " ";
        }
    }

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        // len -> width draw squares
        // process time -> x draw squares
        // x = pt * width / len
        int draws = processes[i].exectime * grant_width / len;
        SetConsoleTextAttribute(col, i%16 + 1);

        for (int j = 0; j < draws; j++)
        {
            // using unicode █
            cout << "\u2588";
        }
    }
    cout << endl;

    // second line
    // for (int i = 0; i < n; i++)
    // {
    //     // len -> width draw squares
    //     // process time -> x draw squares
    //     // x = pt * width / len
    //     int draws = processes[i].exectime * grant_width / len;
    //     SetConsoleTextAttribute(col, i%16 + 1);

    //     for (int j = 0; j < draws; j++)
    //     {
    //         // using unicode █
    //         cout << "\u2588";
    //     }
    // }
    // cout << endl;

    int time = 0, timeraro = 0;
    for (int i = 0; i < n; i++)
    {
        // len -> width draw squares
        // process time -> x draw squares
        // x = pt * width / len
        int draws = processes[i].exectime * grant_width / len;
        SetConsoleTextAttribute(col, i%16 + 1);
        
        cout << time;
        time += processes[i].exectime;
        draws -= log10(time);
        timeraro += time;

        for (int j = 0; j < draws; j++)
        {
            // using unicode █
            cout << " ";
        }
    }
    cout << time;
    cout << endl;


    SetConsoleTextAttribute(col, 9);
    cout << "Tiempo total de exec: " << time << " ms"<< endl;
    cout << "Tiempo prom de espera por proceso: " << time / n << " ms"<< endl;
    cout << "Tiempo raro ese: " << timeraro / n << " ms" << endl;

    // set default values
    SetConsoleTextAttribute(col, csbi.wAttributes);
    processes.clear();
    return true;
}

vector<string> getmodes()
{
    return modes;
}

void FCFS()
{

}

void SJF()
{
    //bool swapped;
    int n = processes.size();
    //cout << n << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (processes[j].exectime > processes[i].exectime)
            {
                process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void BP()
{
    bool swapped;
    int n = processes.size();
    //cout << n << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (processes[j].priority > processes[i].priority)
            {
                process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void RR()
{
    return;
}
