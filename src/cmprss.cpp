#include <locale.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>

#include "rule.h"
#include "huff.h"
#include "shfe.h"

void showUsage(string name, bool flag);
void Start(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); // so funciona aqui
	
    Start(argc, argv); // trabalhando parametros

    Rule rulen;

    Huff huffm;
    Shfe shafe;

    string alg = argv[1];
    string ifile = argv[2];

    cout << alg << "\t" << ifile << endl;

    // cout << ifile.substr(ifile.rfind('/')+1,ifile.size()) << endl;

    /* int a = 255;

    char b = a;

    char c = (char)a;

    int d = (int)b;

    int e = a & 0xff;

    int f = b;

    int g = b & 0xff;

    cout << a << " " << b << " " << c << " " << d << " " << e << " " << f  << " " << g << std::endl;
 */



    time_t now = time(NULL);

    if (alg == "rule") {
        rulen.Start(ifile);
    } else if (alg == "huff") {
        huffm.Start(ifile);
    } else if (alg == "shfe") {
        shafe.Start(ifile);
    } else {
        cout << alg << endl;
    }


    cout << "\n[Finalizado em "<< difftime(time(NULL),now) << "s]\n";
    
    // cin.ignore(1024, '\n'); // caso seja preciso
    cout << "Pressione enter para continuar ...";
    cin.get();
    return 0;
}
void Start(int argc, char* argv[]) {	

 	// Checando o número de parâmetros
    if (argc == 1) {
        // Conte ao usuário como rodar o programa
        showUsage(argv[0], true);
        exit(EXIT_FAILURE);
    }

    string args1 = argv[1];
    
    if ((args1 == "--help") || (args1 == "-h")){ // se for help
        // Conte ao usuário como rodar o programa
        showUsage(argv[0], false);
        exit(EXIT_SUCCESS);
    }

    if (argc < 3) {
        showUsage(argv[0], true);
        exit(EXIT_FAILURE);
    }

    // params
    /* cout << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    } */

}

void showUsage(string name, bool flag) // função para mostrar uso
{
    string usage = "Usage: " + name + " <alg> <inputfile>\nDetails:\n-h\t\tShow this message\n<alg>\t\tAlgorithm: rule, huff or shfe\n<inputfile>\t\tInput file to compression/descompression\n";

    if (flag) {
        cerr << usage;
    } else {
        cout << usage;
    }
}