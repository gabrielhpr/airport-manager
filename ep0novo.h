#include <bits/stdc++.h>
#ifndef AEROPORTO_H
#define AEROPORTO_H
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
    elementoDaFila* primerElmPrioridade[4];
    elementoDaFila* ultElmPrioridade[4];
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
        int numElemPrio[4];
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

    for (int i = 0; i < 4; i++) 
        numElemPrio[i] = 0;
    
    numAvioesCairam = 0;

    /*Inicializa a cabeça torre de controle */
    torreDeControle = new cabecaTorreDeControle;

    for(int i=0; i < 4; i++) {
       torreDeControle->primerElmPrioridade[i] = nullptr;
       torreDeControle->ultElmPrioridade[i] = nullptr;
    }
}
Aeroporto::~Aeroporto() {
    elementoDaFila* aux;
    
    for (int i = 0; i < 4; i++) {
        aux = torreDeControle->primerElmPrioridade[i];
        while(aux != nullptr && aux->atras != nullptr) {
            torreDeControle->primerElmPrioridade[i] = aux->atras;
            //Apaga o aviao
            delete aux->aviao;
            //Apaga o elemento que contém o avião
            delete aux;
            aux = torreDeControle->primerElmPrioridade[i];
        }    
    }
    //Deleta a cabeça
    delete torreDeControle;
}

/*Avioes contatam a torre de comando*/
void Aeroporto :: contatoComATorre(Aviao* aviao) {
    insere(aviao);
}

bool Aeroporto :: solicDePousoDec(Aviao* aviao) {
    if(aviao == nullptr) return false;
    /*Se o avião tiver prioridade 0 e quiser pousar, não poderá utilizar a pista 3*/
    if(pista3Disponivel && !(aviao->prioridade == 0 && aviao->pouso == 1)) {
        cout << "entrou na solicitacao de pouso" << endl;
        cout << "prioridade: " << aviao->prioridade << endl; 
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

    if(numElemPrio[prioridade] == 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = nullptr;
        torreDeControle->primerElmPrioridade[prioridade] = aux;
        //Se o elemento inserido é o primeiro e único da fila, então o
        //ponteiro do último passa a apontar para ele
        torreDeControle->ultElmPrioridade[prioridade] = aux;
        numElem++;
        numElemPrio[prioridade]++;
        cout << "inseriu com sucesso" << endl; 
    }
    else if(numElemPrio[prioridade] != 0) {
        aux = new elementoDaFila;
        aux->aviao = aviao;
        aux->atras = nullptr;
        aux->frente = torreDeControle->ultElmPrioridade[prioridade];
        //aux->frente = torreDeControle->ultElmPrioridade3;
        torreDeControle->ultElmPrioridade[prioridade]->atras = aux;
        //torreDeControle->ultElmPrioridade3->atras = aux;
        torreDeControle->ultElmPrioridade[prioridade] = aux;
        //torreDeControle->ultElmPrioridade3 = aux;
        numElem++;
        numElemPrio[prioridade]++;
    }
}
/*Remove o avião da posição em que está na fila, dessa maneira será possível
reorganizar a fila conforme os níveis de prioridades(Ex. Avião sem combustível)*/
Aviao* Aeroporto :: remove(elementoDaFila* elm) {
    int prioridade = elm->aviao->prioridade;
    elementoDaFila* ult;
    Aviao* aviaoRemovido = elm->aviao; 
    
    /*Se o elemento é o último da fila, atualiza o ponteiro
    que aponta para o último elemento*/
    if(elm == torreDeControle->ultElmPrioridade[prioridade])
        torreDeControle->ultElmPrioridade[prioridade] = elm->frente;

    /*O elemento removido sempre e o primeiro*/
    torreDeControle->primerElmPrioridade[prioridade] = elm->atras;

    /*Checar se só exclue o elemento ou o avião também*/
    delete elm;
    numElem--;
    numElemPrio[prioridade]--;
    return aviaoRemovido;
}
void Aeroporto :: atualizaSituacaoDosAvioesNaFila() {
    elementoDaFila *aux, *troca;
    Aviao* aviaoComNovaPrioridade;
    int prioridade;

    for (prioridade = 0; prioridade < 4; prioridade++) {
        aux = torreDeControle->primerElmPrioridade[prioridade];
        while(aux != nullptr) {
            aux->aviao->quantCombust--;
            aux->aviao->tempoDeEspera++;
            if(aux->aviao->quantCombust < 0) {
                cout << "O avião caiu" << endl;
                remove(aux);
                numAvioesCairam++;
            }
            else if( prioridade == 0 && aux->aviao->quantCombust == 0) {
                aux->aviao->prioridade = 3;
                //troca armazena o aviao que esta atras do atual
                troca = aux->atras;
                //O aviao que mudou de prioridade ira mudar de fila
                aviaoComNovaPrioridade = remove(aux);
                contatoComATorre(aviaoComNovaPrioridade);
                aux = troca;
                continue;
            }
            else if( prioridade == 0 && !aux->aviao->pouso && aux->aviao->tempoDeEspera*10 > aux->aviao->duracaoDoVoo)
                aux->aviao->prioridade = 1;

            aux = aux->atras;
        }
    }
}
void Aeroporto :: liberaVoos() {

    while(haPistaLivre() == true) {
        if(numElemPrio[3] != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade[3]->aviao)) 
            remove(torreDeControle->primerElmPrioridade[3]);

        else if(numElemPrio[2] != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade[2]->aviao))
            remove(torreDeControle->primerElmPrioridade[2]);
            
        else if(numElemPrio[1] != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade[1]->aviao)) 
            remove(torreDeControle->primerElmPrioridade[1]); 
        
        else if(numElemPrio[0] != 0 && solicDePousoDec(torreDeControle->primerElmPrioridade[0]->aviao)) 
            remove(torreDeControle->primerElmPrioridade[0]); 
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

    for (int i = 0; i < 4; i++) {
        aux = torreDeControle->primerElmPrioridade[i];
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
void Aeroporto :: printaAviao(Aviao* aviao, int pouso) {
    if(pouso && aviao->pouso)
        cout << aviao->companhiaArea << aviao->numeroDoAviao << "; ";
    else if(!pouso && !aviao->pouso)
        cout << aviao->companhiaArea << aviao->numeroDoAviao << "; ";
}
void Aeroporto :: printaElemento(Aviao* aviao) {
    cout << aviao->companhiaArea << aviao->numeroDoAviao <<
    " emerg: " << aviao->emergencia << " , quantCombus: " << aviao->quantCombust <<
    " , durVoo: " << aviao->duracaoDoVoo << " , tempDeEspera: " << aviao->tempoDeEspera <<
    " , destino: "<< aviao->aeroportoDestOrig << endl;
}
void Aeroporto :: printaFila(int tipoDePrintagem, int pouso) {
    int nPouso, nDec;
    nPouso = nDec = 0;
    elementoDaFila* aux;

    for (int i = 0; i < 4; i++) {
        aux = torreDeControle->primerElmPrioridade[i];
        while (aux != nullptr) {
            if(tipoDePrintagem == 0)
                printaElemento(aux->aviao);
            else {
                /*Quebra a linha na printagem do terminal*/
                if(pouso && aux->aviao->pouso) nPouso++;
                else if(!pouso && !aux->aviao->pouso) nDec++;

                if( (nPouso+1 % 5) == 0 || (nDec+1 % 5) == 0) cout << endl << "   ";
                
                printaAviao(aux->aviao, pouso);
            }
            aux = aux->atras;
        }    
    }
    cout << endl;
}
#endif
/*O codigo tinha 644 linhas de codigo*/