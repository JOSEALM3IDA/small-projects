#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

#define MOVIES_FILE "movies.txt"

vector<string> readFile(string fileName) {
    ifstream file(fileName);

    if (!file) {
        cerr << "Ficheiro " << fileName << " nao existe :(" << endl;
        exit(-1);
    }

    vector<string> rtn;
    string line;
    while (getline(file, line)) {
        rtn.push_back(line);
    }

    if (rtn.size() <= 0) {
        cerr << "Ficheiro " << fileName << " esta vazio :(" << endl;
        exit(-1);
    }
    
    return rtn;
}

void printMovies(vector<string> movies) {
    for (int i = 0; i < movies.size(); i++) {
        cout << i + 1 << ". " << movies.at(i) << endl;
    }
}

int main() {
    vector<string> movies = readFile(MOVIES_FILE);

    cout << endl;
    printMovies(movies);

    srand(time(NULL));
    string input;
    while (true) {
        cout << endl << "Escolher filme aleatorio? (S/N): ";
        cin >> input;

        if (input != "s" && input != "S")
            break;

        cout << endl << "Filme escolhido: " <<  movies.at(rand() % movies.size()) << "!" << endl;
        cout << "Boa sessao :)" << endl;
        cin.get();
        exit(1);
    }

    cout << "Xau entao :|" << endl;

    return 0;
}