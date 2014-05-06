#include<iostream>
#include<fstream>
using namespace std;

ifstream f("Kruskal.in");
ofstream g("Kruskal.out");

int n, m, F[100];

// Declaram o structura numita "Edge"
// care va retine caracteristicile
// muchiei
struct Edge{
    int vertex1;
    int vertex2;
    int cost;
};
Edge graph[100];

// Functia readIn (citeste datele din fisier)
void readIn() {
    f>>n>>m;
    for(int i=1;i<=m;i++) f>>graph[i].vertex1>>graph[i].vertex2>>graph[i].cost;
    f.close();
} // END OF readIn FUNCTION

// Functie care sorteaza muchiile crescator dupa sort
void graphSort() {

    Edge aux;
    int isFinished = 0;
    while(isFinished==0) {
        isFinished=1;
        for(int i=1;i<m;i++) {
            if(graph[i].cost>graph[i+1].cost) {
                aux=graph[i];
                graph[i]=graph[i+1];
                graph[i+1]=aux;
                isFinished=0;
            }// END OF if
        }// END OF for LOOP
    }// END OF while LOOP
}// END OF graphSort FUNCTION

// Functie care cauta radacina unui nod dat
int findRoot(int vertex) {

    while(F[vertex]) vertex=F[vertex];
    return vertex;
}// END OF findRoot FUNCTION

// Functie care uneste doi arbori disjuncti
void uniteTrees(int root1, int root2) {

    F[root2] = root1;
}// END OF uniteTrees FUNCTION

int main() {

    readIn();
    graphSort();

    for(int i=1;i<=n;i++) F[i]=0;

    int k=1;
    int i=1;
    uniteTrees(graph[i].vertex1,graph[i].vertex2);

    while(k<n-1) {
        i++;
        if(findRoot(graph[i].vertex1)!=findRoot(graph[i].vertex2)) {

            uniteTrees(graph[i].vertex1,graph[i].vertex2);
            k++;
        }
    }

    for(i=1;i<=n;i++) if(F[i]!=0) cout<<i<<" "<<F[i]<<"\n";
    return 0;
}// END OF main FUNCTION
