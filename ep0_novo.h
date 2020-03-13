#include <bits/stdc++.h>
#ifndef AEROPORTO_H_NOVO
#define AEROPORTO_H_NOVO
using namespace std;

class Aviao {
    public:
        Aviao(string compArea, int numAviao, bool pous, bool emerg, 
        string aeroDestOrig, int quantComb, int durVoo, int tempEsp, int prioridade);
        //~Aviao();
        string companhiaArea;
        int numeroDoAviao;
        bool pouso;
        bool emergencia;
        string aeroportoDestOrig;
        int quantCombust;
        int duracaoDoVoo;
        int tempoDeEspera;
        int prioridade;
};

Aviao :: Aviao(string compArea, int numAviao, bool pous, bool emerg, 
string aeroDestOrig, int quantComb, int durVoo, int tempEsp, int pri) {
    companhiaArea = compArea;
    numeroDoAviao = numAviao;
    pouso = pous;
    emergencia = emerg;
    aeroportoDestOrig = aeroDestOrig;
    quantCombust = quantComb;
    duracaoDoVoo = durVoo;
    tempoDeEspera = tempEsp;
    prioridade = pri;
}
struct elementoDaFila {
    Aviao *aviao; 
    struct elementoDaFila *atras;
    struct elementoDaFila *frente;
};
typedef struct elementoDaFila elementoDaFila;

/*
Os níveis de prioridade foram definidos da seguinte forma:
3- avião sem combustível;
2- emergências;
1- aviões esperando por mais de 10% do tempo esperado de vôo
0- vôos normais
*/
struct cabecaTorreDeControle {
    elementoDaFila* primerElmPrioridade3;
    elementoDaFila* ultElmPrioridade3;

    elementoDaFila* primerElmPrioridade2;
    elementoDaFila* ultElmPrioridade2;

    elementoDaFila* primerElmPrioridade1;
    elementoDaFila* ultElmPrioridade1;

    elementoDaFila* primerElmPrioridade0;
    elementoDaFila* ultElmPrioridade0;
};
typedef struct cabecaTorreDeControle cabecaTorreDeControle;


class Aeroporto {
    public: 
        Aeroporto();
        ~Aeroporto();
        /*Controle das pistas*/
        bool pista1Disponivel;
        bool pista2Disponivel;
        bool pista3Disponivel;
        bool todasPistasOcupadas;

        int tempLibPista1;
        int tempLibPista2;
        int tempLibPista3;

        /*Dados estatísticos*/
        int nAvioesQuePousaram;
        int nAvioesAPousar;
        double tMedioEsperaPouso;
        double tMedioEsperaDecolagem;
        double quantMediaCombAvAPousar;
        double quantMediaCombAvPousaram;
        int quantVoosEmerg;

        /*Insere os aviões na fila*/
        void contatoComATorre(Aviao* aviao);
        /*Informa se o avião consegue utilizar alguma pista ou não*/
        bool solicDePousoDec(Aviao* aviao);
        void atualizaDispDePista();
        bool haPistaLivre();

        /*Controle das filas*/
        int numElem;
        int numElemPrio3;
        int numElemPrio2;
        int numElemPrio1;
        int numElemPrio0;
        int numAvioesCairam;

        /*Cabeça torre de controle*/
        cabecaTorreDeControle* torreDeControle;

    private:
        /*Métodos*/
        void insere(Aviao* aviao);
        Aviao* remove(elementoDaFila* elm);

    public:
        /*Rearranja os elementos da fila de acordo com suas prioridades*/
        void atualizaSituacaoDosAvioesNaFila();
        /*Libera os voos de acordo com a disponibilidade das pistas*/
        void liberaVoos();
        void coletaEstatisticasEPrinta();
        void printaAviao(Aviao* aviao, int pouso);
        void printaElemento(Aviao* aviao);
        /*tipoDePrintagem(0-exibe elemento completo, 1-exibe o ID do aviao se atender aos parametros - pouso ou não)*/
        void printaFila(int tipoDePrintagem, int pouso);

};

Aeroporto :: Aeroporto() {
    pista1Disponivel = true;
    pista2Disponivel = true;
    pista3Disponivel = true;
    todasPistasOcupadas = false;

    tempLibPista1 = 0;
    tempLibPista2 = 0;
    tempLibPista3 = 0;

    nAvioesQuePousaram = 0;
    nAvioesAPousar = 0;
    tMedioEsperaPouso = 0;
    tMedioEsperaDecolagem = 0;
    quantMediaCombAvAPousar = 0;
    quantMediaCombAvPousaram = 0;
    quantVoosEmerg = 0;

    numElem = 0;
    numElemPrio3 = 0;
    numElemPrio2 = 0;
    numElemPrio1 = 0;
    numElemPrio0 = 0;
    numAvioesCairam = 0;

    /*Inicializa a cabeça torre de controle */
    torreDeControle = new cabecaTorreDeControle;

    torreDeControle->primerElmPrioridade3 = nullptr;
    torreDeControle->ultElmPrioridade3 = nullptr;

    torreDeControle->primerElmPrioridade2 = nullptr;
    torreDeControle->ultElmPrioridade2 = nullptr;

    torreDeControle->primerElmPrioridade1 = nullptr;
    torreDeControle->ultElmPrioridade1 = nullptr;

    torreDeControle->primerElmPrioridade0 = nullptr;
    torreDeControle->ultElmPrioridade0 = nullptr;
}
Aeroporto::~Aeroporto() {
    elementoDaFila* aux;

    aux = torreDeControle->primerElmPrioridade3;
    while(aux->atras != nullptr) {
        torreDeControle->primerElmPrioridade3 = aux->atras;
        /*Apaga o aviao*/
        delete aux->aviao;
        /*Apaga o elemento que contém o avião*/
        delete aux;
        aux = torreDeControle->primerElmPrioridade3;
    }

    aux = torreDeControle->primerElmPrioridade2;
    while(aux->atras != nullptr) {
        torreDeControle->primerElmPrioridade2 = aux->atras;
        /*Apaga o aviao*/
        delete aux->aviao;
        /*Apaga o elemento que contém o avião*/
        delete aux;
        aux = torreDeControle->primerElmPrioridade2;
    }

    aux = torreDeControle->primerElmPrioridade1;
    while(aux->atras != nullptr) {
        torreDeControle->primerElmPrioridade1 = aux->atras;
        /*Apaga o aviao*/
        delete aux->aviao;
        /*Apaga o elemento que contém o avião*/
        delete aux;
        aux = torreDeControle->primerElmPrioridade1;
    }

    aux = torreDeControle->primerElmPrioridade0;
    while(aux->atras != nullptr) {
        torreDeControle->primerElmPrioridade0 = aux->atras;
        /*Apaga o aviao*/
        delete aux->aviao;
        /*Apaga o elemento que contém o avião*/
        delete aux;
        aux = torreDeControle->primerElmPrioridade0;
    }

    /*Deleta a cabeça*/
    delete torreDeControle;
}

/*Avioes contatam a torre de comando*/
void Aeroporto :: contatoComATorre(Aviao* aviao) {
    insere(aviao);
}

bool Aeroporto :: solicDePousoDec(Aviao* aviao) {

    /*Se o avião tiver prioridade 0 e quiser pousar, não poderá utilizar a pista 3*/
    if(pista3Disponivel && !(aviao->prioridade == 0 && aviao->pouso == 1)) {
        /*Aumenta o número de voos de emergência realizados*/
        if (aviao->prioridade == 2) /*Emergência*/
            quantVoosEmerg++;
        if (aviao->pouso) {
            quantMediaCombAvPousaram += aviao->quantCombust;
            nAvioesQuePousaram++;
        }
        pista3Disponivel = false;
        tempLibPista3 = 2;
        return true;
    }
    else if (pista2Disponivel) {
        if (aviao->pouso) {
            quantMediaCombAvPousaram += aviao->quantCombust;
            nAvioesQuePousaram++;
        }
        pista2Disponivel = false;
        tempLibPista2 = 2;
        return true;
    }
    else if (pista1Disponivel) {
        if (aviao->pouso) {
            quantMediaCombAvPousaram += aviao->quantCombust;
            nAvioesQuePousaram++;
        }
        pista1Disponivel = false;
        tempLibPista1 = 2;
        return true;
    }
    else
        return false;
}

void Aeroporto :: atualizaDispDePista() {
    if(!pista1Disponivel) 
        if(--tempLibPista1 == 0) pista1Disponivel = true;
    if(!pista2Disponivel) 
        if(--tempLibPista2 == 0) pista2Disponivel = true;
    if(!pista3Disponivel)
        if(--tempLibPista3 == 0) pista3Disponivel = true;
}

bool Aeroporto :: haPistaLivre() {
    return (pista1Disponivel || pista2Disponivel || pista3Disponivel);
}
void Aeroporto :: insere(Aviao* aviao) {
    int prioridade;
    elementoDaFila* aux;
    prioridade = aviao->prioridade;

    if(prioridade == 3 && numElemPrio3 == 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = nullptr;
        torreDeControle->primerElmPrioridade3 = aux;
        /*Se o elemento inserido é o primeiro e único da fila, então o
        ponteiro do último passa a apontar para ele*/   
        torreDeControle->ultElmPrioridade3 = aux;
        numElem++;
        numElemPrio3++;
    }
    else if(prioridade == 3 && numElemPrio3 != 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = torreDeControle->ultElmPrioridade3;
        torreDeControle->ultElmPrioridade3 = aux;
        numElem++;
        numElemPrio3++;
    }
    else if(prioridade == 2 && numElemPrio2 == 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = nullptr;
        torreDeControle->primerElmPrioridade2 = aux;
        /*Se o elemento inserido é o primeiro e único da fila, então o
        ponteiro do último passa a apontar para ele*/   
        torreDeControle->ultElmPrioridade2 = aux;
        numElem++;
        numElemPrio2++;
    }
    else if(prioridade == 2 && numElemPrio2 != 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = torreDeControle->ultElmPrioridade2;
        torreDeControle->ultElmPrioridade2 = aux;
        numElem++;
        numElemPrio2++;
    }
    else if(prioridade == 1 && numElemPrio1 == 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = nullptr;
        torreDeControle->primerElmPrioridade1 = aux;
        /*Se o elemento inserido é o primeiro e único da fila, então o
        ponteiro do último passa a apontar para ele*/   
        torreDeControle->ultElmPrioridade1 = aux;
        numElem++;
        numElemPrio1++;
    }
    else if(prioridade == 1 && numElemPrio1 != 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = torreDeControle->ultElmPrioridade1;
        torreDeControle->ultElmPrioridade1 = aux;
        numElem++;
        numElemPrio1++;
    }
    else if(prioridade == 0 && numElemPrio0 == 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = nullptr;
        torreDeControle->primerElmPrioridade0 = aux;
        /*Se o elemento inserido é o primeiro e único da fila, então o
        ponteiro do último passa a apontar para ele*/   
        torreDeControle->ultElmPrioridade0 = aux;
        numElem++;
        numElemPrio0++;
    }
    else if(prioridade == 0 && numElemPrio0 != 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = torreDeControle->ultElmPrioridade0;
        torreDeControle->ultElmPrioridade0 = aux;
        numElem++;
        numElemPrio0++;
    }
}
/*Remove o avião da posição em que está na fila, dessa maneira será possível
reorganizar a fila conforme os níveis de prioridades(Ex. Avião sem combustível)*/
Aviao* Aeroporto :: remove(elementoDaFila* elm) {
    Aviao* aviaoRemovido;
    int prioridade = elm->aviao->prioridade;
    elementoDaFila* ult;
    aviaoRemovido = elm->aviao;
    
    /*Se o elemento é o último da fila, atualiza o ponteiro
    que aponta para o último elemento*/
    if(elm == torreDeControle->ultElmPrioridade3)
        torreDeControle->ultElmPrioridade3 = elm->frente;
    else if(elm == torreDeControle->ultElmPrioridade2)
        torreDeControle->ultElmPrioridade2 = elm->frente;
    else if(elm == torreDeControle->ultElmPrioridade1)
        torreDeControle->ultElmPrioridade1 = elm->frente;
    else if(elm == torreDeControle->ultElmPrioridade0)
        torreDeControle->ultElmPrioridade0 = elm->frente;

    /*Se o elemento é o primeiro da fila, a torre irá apontar para nullptr*/
    if(elm == torreDeControle->primerElmPrioridade3)
        torreDeControle->primerElmPrioridade3 = nullptr;
    else if(elm == torreDeControle->primerElmPrioridade2)
        torreDeControle->primerElmPrioridade2 = nullptr;
    else if(elm == torreDeControle->primerElmPrioridade1)
        torreDeControle->primerElmPrioridade1 = nullptr;
    else if(elm == torreDeControle->primerElmPrioridade0)
        torreDeControle->primerElmPrioridade0 = nullptr;

    if(elm->frente != nullptr)
        elm->frente->atras = elm->atras;
    /*Se o elemento atrás do elm não é null, então atualiza o seu
    ponteiro da frente*/
    if(elm->atras != nullptr)
        elm->atras->frente = elm->frente;
    /*Checar se só exclue o elemento ou o avião também*/
    delete elm;
    numElem--;
    switch (prioridade) {
        case 3:
            numElemPrio3--;
        break;

        case 2:
            numElemPrio2--;
        break;

        case 1:
            numElemPrio1--;
        break;

        case 0:
            numElemPrio0--;
        break;
        
        default:
        break;
    }
    return aviaoRemovido;
}
void Aeroporto :: atualizaSituacaoDosAvioesNaFila() {
    elementoDaFila* aux;

    aux = torreDeControle->primerElmPrioridade3;
    while(aux != nullptr) {
        aux->aviao->quantCombust--;
        aux->aviao->tempoDeEspera++;
        if(aux->aviao->quantCombust < 0) {
            cout << "O avião caiu" << endl;
            remove(aux);
            numAvioesCairam++;
        }
        aux = aux->atras;
    }

    aux = torreDeControle->primerElmPrioridade2;
    while(aux != nullptr) {
        aux->aviao->quantCombust--;
        aux->aviao->tempoDeEspera++;
        if(aux->aviao->quantCombust < 0) {
            cout << "O avião caiu" << endl;
            remove(aux);
            numAvioesCairam++;
        }
        aux = aux->atras;
    }

    aux = torreDeControle->primerElmPrioridade1;
    while(aux != nullptr) {
        aux->aviao->quantCombust--;
        aux->aviao->tempoDeEspera++;
        if(aux->aviao->quantCombust < 0) {
            cout << "O avião caiu" << endl;
            remove(aux);
            numAvioesCairam++;
        }
        aux = aux->atras;
    }

    aux = torreDeControle->primerElmPrioridade0;
    while(aux != nullptr) {
        aux->aviao->quantCombust--;
        aux->aviao->tempoDeEspera++;
        if(aux->aviao->quantCombust < 0) {
            cout << "O avião caiu" << endl;
            remove(aux);
            numAvioesCairam++;
        }
        else if(aux->aviao->quantCombust == 0) 
            aux->aviao->prioridade = 3;

        else if(!aux->aviao->pouso && aux->aviao->tempoDeEspera*10 > aux->aviao->duracaoDoVoo)
            aux->aviao->prioridade = 1;

        aux = aux->atras;
    }
    
}
void Aeroporto :: liberaVoos() {
    elementoDaFila* aux;

    while(haPistaLivre() == true) {

        if(numElemPrio3 != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade3->aviao)) 
            remove(torreDeControle->primerElmPrioridade3);

        else if(numElemPrio2 != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade2->aviao)) 
            remove(torreDeControle->primerElmPrioridade2);
            
        else if(numElemPrio1 != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade1->aviao)) 
            remove(torreDeControle->primerElmPrioridade1); 
        
        else if(numElemPrio0 != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade0->aviao)) 
            remove(torreDeControle->primerElmPrioridade0); 

        /*Caso não haja mais nem aviões para pousar nem para decolar*/
        else break;
    }
    //printaFila();   
}

void Aeroporto :: coletaEstatisticasEPrinta() {
    elementoDaFila* aux;

    tMedioEsperaPouso = 0;
    tMedioEsperaDecolagem = 0;
    quantMediaCombAvAPousar = 0;
    nAvioesAPousar = 0;

    aux = torreDeControle->primerElmPrioridade3;
    while(aux != nullptr) {
        if(aux->aviao->pouso == 1) {
            tMedioEsperaPouso += aux->aviao->tempoDeEspera;
            quantMediaCombAvAPousar += aux->aviao->quantCombust;
            nAvioesAPousar++;
        }
        else if(aux->aviao->pouso == 0)
            tMedioEsperaDecolagem += aux->aviao->tempoDeEspera;

        aux = aux->atras;
    }

    aux = torreDeControle->primerElmPrioridade2;
    while(aux != nullptr) {
        if(aux->aviao->pouso == 1) {
            tMedioEsperaPouso += aux->aviao->tempoDeEspera;
            quantMediaCombAvAPousar += aux->aviao->quantCombust;
            nAvioesAPousar++;
        }
        else if(aux->aviao->pouso == 0)
            tMedioEsperaDecolagem += aux->aviao->tempoDeEspera;

        aux = aux->atras;
    }

    aux = torreDeControle->primerElmPrioridade1;
    while(aux != nullptr) {
        if(aux->aviao->pouso == 1) {
            tMedioEsperaPouso += aux->aviao->tempoDeEspera;
            quantMediaCombAvAPousar += aux->aviao->quantCombust;
            nAvioesAPousar++;
        }
        else if(aux->aviao->pouso == 0)
            tMedioEsperaDecolagem += aux->aviao->tempoDeEspera;

        aux = aux->atras;
    }

    aux = torreDeControle->primerElmPrioridade0;
    while(aux != nullptr) {
        if(aux->aviao->pouso == 1) {
            tMedioEsperaPouso += aux->aviao->tempoDeEspera;
            quantMediaCombAvAPousar += aux->aviao->quantCombust;
            nAvioesAPousar++;
        }
        else if(aux->aviao->pouso == 0)
            tMedioEsperaDecolagem += aux->aviao->tempoDeEspera;

        aux = aux->atras;
    }

    if(nAvioesAPousar != 0) {
        tMedioEsperaPouso /= nAvioesAPousar;
        quantMediaCombAvAPousar /= nAvioesAPousar;
    }
    /*Não há informações acerca dos aviões*/
    else {
        tMedioEsperaPouso = -1;
        quantMediaCombAvAPousar = -1;
    }
    ((numElem-nAvioesAPousar) != 0) ? tMedioEsperaDecolagem /= (numElem - nAvioesAPousar) : tMedioEsperaDecolagem = -1;
    ((nAvioesQuePousaram != 0)) ? quantMediaCombAvPousaram /= nAvioesQuePousaram : quantMediaCombAvPousaram = -1;

    cout << "-----------------------------ESTATÍSTICAS DO AEROPORTO--------------------------" << endl << endl;
    cout << " * Os aviões que estão esperando para pousar são: ";
    printaFila(1, 1);
    cout << endl;
    cout << " * Os aviões que estão esperando para decolar são: ";
    printaFila(1, 0);
    cout << endl;
    cout << " * O tempo médio de espera para pouso é: " << tMedioEsperaPouso << endl << endl;
    cout << " * O tempo médio de espera para decolagem é: " << tMedioEsperaDecolagem << endl << endl;
    cout << " * A quantidade média de combustível dos aviões esperando para pousar é: " << quantMediaCombAvAPousar << endl << endl;
    cout << " * A quantidade média de combustível dos aviões que pousaram: " << quantMediaCombAvPousaram << endl << endl;
    cout << " * A quantidade de aviões pousando/decolando em condições de emergência é: " << quantVoosEmerg << endl << endl;
    cout << " * A quantidade de aviões que cairam é: " << numAvioesCairam << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}
#endif