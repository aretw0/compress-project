#include <fstream>

using namespace std;

class Common
{
    private:
        time_t init;
    public:
        Common();
        string hashfile(ifstream & file);
        int sizefile(ifstream & file);
        double cmprssratio(int total,int totalComp);
        void Startcount();
        double Endcount();
};