#include <iostream>

using namespace std;

int factorial(int num) { return num == 0 ? 1 : num * factorial(num-1); }

int comb(int n, int r) { return factorial(n) / (factorial (n-r) * factorial(r)); }

int main() {
    cout << "Num linhas: ";
    
    int nLinhas;
    cin >> nLinhas;

    for (int i = 0; i < nLinhas; i++) {
        for (int j = 0; j < i + 1; j++)
            cout << comb(i,j) << " ";
        cout << endl;
    }

    return 0;
}







