#include <string>

using namespace std;

class Rule
{
private:
	void encode(ifstream & infile, ofstream & outfile);
	void decode(ifstream & infile, ofstream & outfile);

public:
	Rule();
	void Start(string ifile);
};