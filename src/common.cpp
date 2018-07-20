#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include<iomanip> //for width()

#include "common.h"

Common::Common() {};

string Common::hashfile(ifstream & file)
{ 
    stringstream ss;
    // Hashing
    uint32_t magic = 5381;
    char c;
    while (file.get(c)) {
        magic = ((magic << 5) + magic) + c; // magic * 33 + c
    }
    file.clear(); //clear EOF flag
    file.seekg(0); //reset get() pointer to beginning
    ss << hex << setw(8) << setfill('0') << magic;
    return ss.str();
}
int Common::sizefile(ifstream & file) {
    streampos begin,end;
    begin = file.tellg();
    file.seekg (0, ios::end);
    end = file.tellg();
    file.seekg(0); // voltando pro início do arquivo
    return end-begin;
}

double Common::cmprssratio(int total, int totalComp) {
    return ((((float)total - (float)totalComp) / (float)total) * ((float)100));
}

void Common::Startcount() {
    init = time(NULL);
}
double Common::Endcount() {
    return difftime(time(NULL),init);
}