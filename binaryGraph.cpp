#include<iostream>
#include<fstream>
using namespace std;

ifstream f("binaryGraph.in");

int n; // Numarul de noduri
struct Vertex{ // Structura care defineste un nod
    int info; // Informatia nodului
    Vertex *lSon; // Adresa fiului stang
    Vertex *rSon; // Adresa fiului drept
};

Vertex *firstRoot; // Radacina arborelui

// ~~~~~~~~~~~~~~~~~~~~~~~~~ FUNCTION DECLARATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Functiile esentiale
Vertex *buildRoot(Vertex *rootVariable, int information);
Vertex *searchRoot(Vertex *rootVariable, int information);
Vertex *deleteSimpleRoot(Vertex *rootVariable, Vertex *rootDeleted);

// Functii auxiliare
void readIn();
void showGraph(Vertex* showRoot);
Vertex *crossingGraph(Vertex *rootVariable, int information);
Vertex *searchFatherOf(Vertex *rootVariable, int information);

// ~~~~~~~~~~~~~~~~~~~~~ END OF FUNCTION DECLARATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {

    readIn();
    showGraph(firstRoot);

    Vertex *foundRoot=searchRoot(firstRoot, 40);
    if(foundRoot==NULL) cout<<"\n0";
    else cout<<"\n"<<foundRoot->info;

    //Vertex *foundFather=searchFatherOf(firstRoot, foundRoot->info);
    //if(foundFather==NULL) cout<<"\n0";
    //else cout<<"\n"<<foundFather->info;

    firstRoot=deleteSimpleRoot(firstRoot, foundRoot);
    cout<<"\n";
    showGraph(firstRoot);

    return 0;
}// END OF main FUNCTION

// Functie care parcurge graful si returneaza
Vertex *crossingGraph(Vertex *rootVariable, int information) {

    Vertex *aux;
    aux=rootVariable;
    if((aux->info>information)&&(aux->lSon!=NULL))
        aux=crossingGraph(aux->lSon, information);
    else if((aux->info<information)&&(aux->rSon!=NULL))
        aux=crossingGraph(aux->rSon, information);
    else return rootVariable;

}// END OF crossingGraph FUNCTION

// Functie care citeste din fisierul text
void readIn() {
    int information;
    f>>n;
    firstRoot = new Vertex;
    f>>firstRoot->info;
    firstRoot->lSon=NULL;
    firstRoot->rSon=NULL;
    for(int i=2;i<=n;i++){
        f>>information;
        firstRoot=buildRoot(firstRoot, information);
    }
    f.close();
}// END OF readIn FUNCTION

// Functie RSD pentru parcurgere
void showGraph(Vertex* showRoot) {
    if(showRoot != NULL) {
        cout<<showRoot->info<<" ";
        showGraph(showRoot->lSon);
        showGraph(showRoot->rSon);
    }
}// END OF showGraph FUNCTION

// Functie care returneaza tatal unui nod
// folosita la eliminarea unui nod
Vertex *searchFatherOf(Vertex *rootVariable, int information) {

    Vertex *aux = rootVariable;

    if(aux==NULL) return NULL;
    if(aux->info>information) {
        if(aux->lSon->info==information) return aux;
        else searchFatherOf(aux->lSon, information);
    }
    else if(aux->info<information) {
        if(aux->rSon->info==information) return aux;
        else searchFatherOf(aux->rSon, information);
    }
}// END OF searchFatherOf FUNCTION

// Functie de construire a unui arbore binar de cautare alocat dinamic
Vertex *buildRoot(Vertex *rootVariable, int information){

    Vertex *aux;
    aux=rootVariable;

    aux=crossingGraph(aux, information);

    if(aux->info<information) {
        aux->rSon=new Vertex;
        aux=aux->rSon;
        aux->info=information;
        aux->rSon=NULL;
        aux->lSon=NULL;
    }
    if(aux->info>information) {
        aux->lSon=new Vertex;
        aux=aux->lSon;
        aux->info=information;
        aux->lSon=NULL;
        aux->rSon=NULL;
    }
    return rootVariable;
}// END OF buildRoot FUNCTION

// Functia de cautare a unui nod dintr-un arbore binar de cautare alocat dinamic
Vertex *searchRoot(Vertex *rootVariable, int information) {

    Vertex *aux = rootVariable;
    aux=crossingGraph(aux, information);

    if(aux->info==information) return aux;
    else return NULL;

    /*if(rootVariable==NULL) return NULL;
    else if(rootVariable->info==information) return rootVariable;
    else if(rootVariable->info>information) searchRoot(rootVariable->lSon, information);
    else if(rootVariable->info<information) searchRoot(rootVariable->rSon, information);*/
}// END OF searchRoot FUNCTION

// Functie care sterge un nod simplu de eliminat
Vertex *deleteSimpleRoot(Vertex *rootVariable, Vertex *rootDeleted) {

    Vertex *aux, *father;
    aux = rootVariable;

    // Testam daca nodul este frunza
    if(rootDeleted->lSon==NULL&&rootDeleted->rSon==NULL) {
        father=searchFatherOf(aux, rootDeleted->info);

        if(father->info>rootDeleted->info)
            father->lSon=NULL;
        else if(father->info<rootDeleted->info)
            father->rSon=NULL;
    }

    // Testam daca nodul are fiu unic
    if(rootDeleted->lSon!=NULL&&rootDeleted->rSon==NULL) {
        father=searchFatherOf(aux, rootDeleted->info);
        cout<<"\n"<<father->info;
        if(father->info>rootDeleted->info)
            father->lSon==rootDeleted->lSon;
        else if(father->info<rootDeleted->info)
            father->rSon==rootDeleted->lSon;
    }

    if(rootDeleted->lSon==NULL&&rootDeleted->rSon!=NULL) {
        father=searchFatherOf(aux, rootDeleted->info);

        if(father->info>rootDeleted->info)
            father->lSon==rootDeleted->rSon;
        else if(father->info<rootDeleted->info)
            father->rSon==rootDeleted->rSon;
    }
    delete rootDeleted;
    return rootVariable;
}// END OF deleteSimpleRoot FUNCTION
