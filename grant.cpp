#include <vector>
#include <algorithm>

#include "processes.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage is: grant MODE FILENAME.csv\n";
        return 1;
    }

    vector<string> modes = getmodes();

    int index = find(modes.begin(), modes.end(), argv[1]) - modes.begin();

    //cout << index << endl;

    if (index == modes.size())
    {
        cout << "Incorrect mode name\n";
        return 1;
    }
    
    //cout << argv[1] << endl;

    if (!loadProcesses(argv[2]))
    {
        cout << "Error loading processes from file\n";
        return 1; 
    }

    if (!sortProcesses(index))
    {
        cout << "Error sorting processes/n";
        return 1;
    }

    if (!printProcesses())
    {
        cout << "Error printing the processes\n";
        return 1;
    }
    
    return 0;
}