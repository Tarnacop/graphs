#include<iostream>
#include<fstream>
using namespace std;

ifstream f("toFD.in");
ofstream g("toFD.out");

int n;

// Structura care tine locul a 2 vectori: S si D
struct Father {
    int leftSon; // Memoreaza fiul stang al tatalui i
    int rightSon; // Memoreaza fiul drept al tatalui i
};

// Vector de tati. Indexul fiecaruia
// reprezinta numele unui tata
Father fathers[100];

// Structura care tine locul a 2 vectori: T si Dir
struct Son {
    int father; // Memoreaza tatal fiului i
    int type; // Memoreaza tipul fiului i (stang -1 sau drept 1)
};

// Vector de fii. Indexul fiecaruia
// reprezinta numele unui fiu
Son sons[100];

// Functie care citeste datele de intrare
void readIn(){

    f>>n;
    for(int i=1;i<=n;i++)
        f>>sons[i].father>>sons[i].type;
    f.close();
}// END OF readIn FUNCTION

// Functie care transforma din TD in SD
void toTD() {

    for(int i=1;i<=n;i++) {

        if(sons[i].father!=0) {
            if(sons[i].type==-1)
            fathers[sons[i].father].leftSon=i;
            else if(sons[i].type==1)
            fathers[sons[i].father].rightSon=i;
        }
    }
}// END OF toTD FUNCTION

// Functie care afiseaza "Fii stangi, fii drepti"
void setOutput() {

    for(int i=1;i<=n;i++) g<<fathers[i].leftSon<<" ";
    g<<"\n";
    for(int i=1;i<=n;i++) g<<fathers[i].rightSon<<" ";
} // END OF setOutput FUNCTION

int main(){

    readIn();
    toTD();
    setOutput();
    return 0;
} // END OF main FUNCTION
