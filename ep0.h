#include <bits/stdc++.h>
#ifndef AEROPORTO_H
#define AEROPORTO_H
using namespace std;

class Aviao {
    public:
        Aviao(string compArea, int numAviao, bool pous, bool emerg, 
        string aeroDestOrig, int quantComb, int durVoo, int tempEsp);
        //~Aviao();
        string companhiaArea;
        int numeroDoAviao;
        bool pouso;
        bool emergencia;
        string aeroportoDestOrig;
        int quantCombust;
        int duracaoDoVoo;
        int tempoDeEspera;
};

Aviao :: Aviao(string compArea, int numAviao, bool pous, bool emerg, 
string aeroDestOrig, int quantComb, int durVoo, int tempEsp) {
    companhiaArea = compArea;
    numeroDoAviao = numAviao;
    pouso = pous;
    emergencia = emerg;
    aeroportoDestOrig = aeroDestOrig;
    quantCombust = quantComb;
    duracaoDoVoo = durVoo;
    tempoDeEspera = tempEsp;
}
struct elementoDaFila {
    Aviao *aviao; 
    struct elementoDaFila *atras;
    struct elementoDaFila *frente;
};
typedef struct elementoDaFila elementoDaFila;

class Aeroporto {
    public: 
        Aeroporto();
        ~Aeroporto();
        /*Controle das pistas*/
        bool pista1Disponivel;
        bool pista2Disponivel;
        bool pista3Disponivel;

        int tempLibPista1;
        int tempLibPista2;
        int tempLibPista3;

        void contatoComATorre(Aviao* aviao);
        bool solicDePousoDec(Aviao* aviao);
        void atualizaDispDePista();

        /*Controle das filas*/
        int numElem;
        elementoDaFila* cab;
        elementoDaFila* ult;
    private:
        /*Métodos*/
        void insereNoFim(Aviao* aviao);
        void insereNoInicio(Aviao* aviao); 
    public:
        Aviao* remove(elementoDaFila* elm);
        void checa();
        void printaElemento(Aviao* aviao);
        void printaFila();
};

Aeroporto::Aeroporto() {
    pista1Disponivel = true;
    pista2Disponivel = true;
    pista3Disponivel = true;

    tempLibPista1 = 0;
    tempLibPista2 = 0;
    tempLibPista3 = 0;

    numElem = 0;
    /*Inicializa a cabeça da fila */
    cab = new elementoDaFila;
    cab->atras = nullptr;
    /*A cabeça também é o último elemento da fila*/
    ult = cab;
}

Aeroporto::~Aeroporto() {
    elementoDaFila* aux = cab->atras;
    while(cab->atras != nullptr) {
        cab->atras = aux->atras;
        /*Apaga o aviao*/
        delete aux->aviao;
        /*Apaga o elemento que contém o avião*/
        delete aux;
        aux = cab->atras;
    }
    /*Deleta a cabeça*/
    delete cab;
}
void Aeroporto :: printaElemento(Aviao* aviao) {
    cout << "N: " << aviao->numeroDoAviao << " comp: " << aviao->companhiaArea <<
    " emerg: " << aviao->emergencia << " quantCombus: " << aviao->quantCombust <<
    " durVoo: " << aviao->duracaoDoVoo << endl;
}
void Aeroporto :: printaFila() {
    elementoDaFila* aux = cab->atras;
    while (aux != nullptr) {
        printaElemento(aux->aviao);
        aux = aux->atras;
    }
    cout << endl << endl;
}

/*Voos sem prioridade são colocados no final da fila*/
void Aeroporto :: insereNoFim(Aviao* aviao) {
    elementoDaFila* aux = new elementoDaFila;
    aux->aviao = aviao;
    aux->atras = ult->atras;
    aux->frente = ult;
    ult->atras = aux;
    /*Atualiza o último elemento da fila*/
    ult = aux;
    numElem++;
}
/*Voos com prioridade são colocados no início da fila*/
void Aeroporto :: insereNoInicio(Aviao* aviao) {
    elementoDaFila* aux = new elementoDaFila;
    aux->aviao = aviao;
    aux->atras = cab->atras;
    aux->frente = cab;
    cab->atras = aux;
    /*Se o elemento inserido é o primeiro e único da fila, então o
    ponteiro do último passa a apontar para ele*/   
    if(ult == cab) ult = aux;
    numElem++;
}
/*Remove o avião da posição em que está na fila, dessa maneira será possível
reorganizar a fila conforme os níveis de prioridades(Ex. Avião sem combustível)*/
Aviao* Aeroporto :: remove(elementoDaFila* elm) {
    Aviao* aviaoRemovido;
    aviaoRemovido = elm->aviao;
    /*Se o elemento é o último da fila, atualiza o ponteiro
    que aponta para o último elemento*/
    if(elm == ult) ult = elm->frente;
    elm->frente->atras = elm->atras;
    /*Se o elemento atrás do elm não é null, então atualiza o seu
    ponteiro da frente*/
    if(elm->atras != nullptr)
        elm->atras->frente = elm->frente;
    /*Checar se só exclue o elemento ou o avião também*/
    delete elm;
    numElem--;
    return aviaoRemovido;
}
/*Avioes contatam a torre de comando*/
void Aeroporto :: contatoComATorre(Aviao* aviao) {
    if(aviao->emergencia || aviao->quantCombust == 0) {
        /*Coloca na fila*/
        cout << "Colocar no inicio" << endl;
        insereNoInicio(aviao);
    }
    else {
        cout << "Colocar no fim" << endl;
        insereNoFim(aviao);
    }
}
bool Aeroporto :: solicDePousoDec(Aviao* aviao) {
    /*Pode pousar/decolar em qualquer pista*/
        if(pista3Disponivel && (aviao->emergencia || aviao->pouso == false) ) {
            pista3Disponivel = false;
            tempLibPista3 = 2;
            return true;
        }
        else if(pista2Disponivel) {
            pista2Disponivel = false;
            tempLibPista2 = 2;
            return true;
        }
        else if(pista1Disponivel) {
            pista1Disponivel = false;
            tempLibPista1 = 2;
            return true;
        }
        else return false;
}

#endif 