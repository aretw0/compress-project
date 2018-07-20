#include <iostream>
#include <fstream>
#include <time.h>
#include "rule.h"
#include "common.h"

Rule::Rule(){}

void Rule::encode(ifstream & infile, ofstream & outfile) {
   
    char c;
    char cSet;

    if (infile.get(c)) {
         cSet = c;
        int size = 1;
        while(infile.get(c)) {
            if (cSet == c) {
                ++size;
                if (size > 255) {
                    outfile.put(size-1);
                    outfile.put(c);
                    size = 1;
                }
            } else {
                outfile.put(size);
                outfile.put(cSet);
                cSet = c;
                size = 1;
            }
        }
        outfile.put(size);
        outfile.put(cSet);

    } else {
        cout << "Arquivo vazio!" << endl;
        exit(EXIT_FAILURE);
    }
}
void Rule::decode(ifstream & infile, ofstream & outfile) {
    
    char c;
    char cSet;
    unsigned char ch;

    while(infile.get(c)) {
        ch = c;
        int size = ch & 0xff;
        infile.get(c);
        for (int i = 0; i < size; ++i) {
            outfile.put(c);
        }
    }
}

void Rule::Start(string ifile) {
    
    ifstream infile(ifile.c_str(), ios::in|ios::binary);

    if(!infile)
    {
        cerr <<ifile <<" nao pode ser aberto!" << endl;
        exit(EXIT_FAILURE);
    }

    Common tool;
    string ext = ".rule";

    string hash1 = tool.hashfile(infile);

    int total = tool.sizefile(infile);

    string ofile = ifile.substr(ifile.rfind('/')+1,ifile.size()) + ext;

    if(ifstream(ofile.c_str()))
    {
        cerr<<ofile<<" ja existe!"<<endl;
        exit(EXIT_FAILURE);
    }

    //open the output file
    ofstream outfile(ofile.c_str(), ios::out|ios::binary);
    if(!outfile)
    {
        cerr<<ofile<<" nao pode ser aberto!"<<endl;
        exit(EXIT_FAILURE);
    }
    // tudo pronto para comprimir

    tool.Startcount();
    encode(infile,outfile);
    double finalTime = tool.Endcount();

    infile.close();
    outfile.close();

    infile.open(ofile, ios::in|ios::binary);

    int totalComp = tool.sizefile(infile);

    cout << "\n[Compressao Finalizada]\n";
    cout << "\tEm "<< finalTime << "s\n";
    cout << "\tCompressao de "<< tool.cmprssratio(total,totalComp) << "%\n";

    string decompFile = ofile.substr(0,ofile.size()-ext.size());

    outfile.open(decompFile,ios::out|ios::binary);

    decode(infile,outfile);

    infile.close();
    outfile.close();

    infile.open(decompFile, ios::in|ios::binary);
    string hash2 = tool.hashfile(infile);
    if (hash1 == tool.hashfile(infile)) {
        cout << "\tArquivos identicos\n";
    } else {
        cout << "\tArquivos diferentes\n";
    }
    cout << hash1 << endl;
    cout << hash2 << endl;
}