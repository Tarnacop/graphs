#include<iostream>
#include<fstream>
using namespace std;

ifstream f("toTD.in");
ofstream g("toTD.out");

int n;

// Structura care tine locul a 2 vectori: S si D
struct Father{
    int leftSon; // Memoreaza fiul stang al tatalui i
    int rightSon; // Memoreaza fiul drept al tatalui i
};

// Vector de tati. Indexul fiecaruia
// reprezinta numele unui tata
Father fathers[100];

// Structura care tine locul a 2 vectori: T si Dir
struct Son{
    int father; // Memoreaza tatal fiului i
    int type; // Memoreaza tipul fiului i (stang -1 sau drept 1)
};

// Vector de fii. Indexul fiecaruia
// reprezinta numele unui fiu
Son sons[100];

// Functie care citeste datele de intrare
void readIn() {

    f>>n;
    for(int i=1;i<=n;i++)
        f>>fathers[i].leftSon>>fathers[i].rightSon;
    f.close();
}// END OF readIn FUNCTION

// Functie care transforma din SD in TD
void toTD() {

    for(int i=1;i<=n;i++) {
        if(fathers[i].leftSon!=0) {
            sons[fathers[i].leftSon].father=i;
            sons[fathers[i].leftSon].type=-1;
        }
        if(fathers[i].rightSon!=0) {
            sons[fathers[i].rightSon].father=i;
            sons[fathers[i].rightSon].type=1;
        }
    }
}// END OF toTD FUNCTION

// Functie care afiseaza "Legatura la tata"
void setOutput(){

    for(int i=1;i<=n;i++) g<<sons[i].father<<" ";
    g<<"\n";
    for(int i=1;i<=n;i++) g<<sons[i].type<<" ";
    g.close();
}// END OF setOutput FUNCTION

int main() {

    readIn();
    toTD();
    setOutput();
    return 0;
}// END OF maine FUNCTION
