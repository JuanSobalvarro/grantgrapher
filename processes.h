#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <windows.h>
#include <math.h>
#include <string>

using namespace std;

bool loadProcesses(char *filename);
bool sortProcesses(int index);
bool printProcesses();

vector<string> getmodes();
void FCFS();
void SJF();
void BP();
void RR();