#include<iostream>
#include<fstream>
using namespace std;

ifstream f("binaryGraph.in");
ofstream g("binaryGraph.out");

int n;
struct root{
    int info;
    root *lSon;
    root *rSon;
};

root *firstRoot;

root *buildRoot(root *rootVariable, int information){

    root *aux;
    aux=rootVariable;

    while((aux->info<information)&&(aux->rSon!=NULL)) {
        aux=aux->rSon;
    }
    while((aux->info>information)&&(aux->lSon!=NULL)) {
        aux=aux->lSon;
    }
    if(aux->info<information) {
        aux->rSon=new root;
        aux=aux->rSon;
        aux->info=information;
        aux->rSon=NULL;
        aux->lSon=NULL;
    }
    if(aux->info>information) {
        aux->lSon=new root;
        aux=aux->lSon;
        aux->info=information;
        aux->lSon=NULL;
        aux->rSon=NULL;
    }
    return rootVariable;
}// END OF buildRoot FUNCTION

void readIn() {
    int information;
    f>>n;
    firstRoot = new root;
    f>>firstRoot->info;
    firstRoot->lSon=NULL;
    firstRoot->rSon=NULL;
    for(int i=2;i<=n;i++){
        f>>information;
        firstRoot=buildRoot(firstRoot, information);
    }
}// END OF readIn FUNCTION

void showGraph() {

    root *aux = firstRoot;
    cout<<firstRoot->info<<" ";
    while(aux->lSon!=NULL) {
        aux=aux->lSon;
        cout<<aux->info<<" ";
    }
    while(aux->rSon!=NULL) {
        aux=aux->rSon;
        cout<<aux->info<<" ";
    }
    aux = firstRoot;
    while(aux->rSon!=NULL) {
        aux=aux->rSon;
        cout<<aux->info<<" ";
    }
    while(aux->lSon!=NULL) {
        aux=aux->lSon;
        cout<<aux->info<<" ";
    }
}// END OF showGraph FUNCTION

root *searchRoot(root *rootVariable, int information) {

    if(rootVariable==NULL) return NULL;
    if(rootVariable->info==information) return rootVariable;
    root *aux=rootVariable;
    while((aux->info<information)&&(aux->lSon!=NULL)) {
        aux=aux->lSon;
    }
    while((aux->info>information)&&(aux->rSon!=NULL)) {
        aux=aux->rSon;
    }
    if(aux->lSon->info==information) return aux->lSon;
    if(aux->rSon->info==information) return aux->rSon;
}// END OF searchRoot FUNCTION

int main() {

    readIn();
    showGraph();
    root *auxRoot = searchRoot(firstRoot,4);
    cout<<"\n"<<auxRoot->info;
    return 0;
}// END OF main FUNCTION
