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
    elementoDaFila* elmPrioridade3Primer;
    elementoDaFila* elmPrioridade3Ult;
    /*
    elementoDaFila* elmPrioridade2;
    elementoDaFila* elmPrioridade1;
    elementoDaFila* elmPrioridade0;
    */
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
        
        
        

        elementoDaFila* cab;
        elementoDaFila* ult;
    private:
        /*Métodos*/
        void insere(Aviao* aviao);
        void insereNoFim(Aviao* aviao);
        void insereNoInicio(Aviao* aviao); 
        Aviao* remove(elementoDaFila* elm);
    public:
        /*Rearranja os elementos da fila de acordo com suas prioridades*/
        void atualizaFilaDeVoos();
        /*Libera os voos de acordo com a disponibilidade das pistas*/
        void liberaVoos();
        void coletaEstatisticasEPrinta();
        void printaAviao(Aviao* aviao, int pouso);
        void printaElemento(Aviao* aviao);
        /*tipoDePrintagem(0-exibe elemento completo, 1-exibe o ID do aviao se atender aos parametros - pouso ou não)*/
        void printaFila(int tipoDePrintagem, int pouso);

};

Aeroporto::Aeroporto() {
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
    elementoDaFila* aux = cab->atras;
    while (aux != nullptr) {
        if(tipoDePrintagem == 0)
            printaElemento(aux->aviao);
        else {
            /*Quebra a linha na printagem do terminal*/
            if(pouso && aux->aviao->pouso) nPouso++;
            else if(!pouso && !aux->aviao->pouso) nDec++;
            if(nPouso == 5 || nDec == 5) cout << endl << "   ";

            printaAviao(aux->aviao, pouso);
        }
        aux = aux->atras;
    }
    cout << endl;
}
/*somente haverá inserções no fim das filas*/
void Aeroporto :: insere(Aviao* aviao) {

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
        //cout << "Colocar no inicio" << endl;
        insereNoInicio(aviao);
    }
    else {
        //cout << "Colocar no fim" << endl;
        insereNoFim(aviao);
    }
}
bool Aeroporto :: solicDePousoDec(Aviao* aviao) {
    /*Pode pousar/decolar em qualquer pista*/
        if(pista3Disponivel && (aviao->emergencia || aviao->pouso == false) ) {
            /*Aumenta o número de voos de emergência realizados*/
            if(aviao->emergencia) quantVoosEmerg++;
            if(aviao->pouso) {
                quantMediaCombAvPousaram += aviao->quantCombust;
                nAvioesQuePousaram++;
            }
            pista3Disponivel = false;
            tempLibPista3 = 2;
            return true;
        }
        else if(pista2Disponivel) {
            if(aviao->pouso) {
                quantMediaCombAvPousaram += aviao->quantCombust;
                nAvioesQuePousaram++;
            }
            pista2Disponivel = false;
            tempLibPista2 = 2;
            return true;
        }
        else if(pista1Disponivel) {
            if(aviao->pouso) {
                quantMediaCombAvPousaram += aviao->quantCombust;
                nAvioesQuePousaram++;
            }
            pista1Disponivel = false;
            tempLibPista1 = 2;
            return true;
        }
        else return false;
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
void Aeroporto :: atualizaFilaDeVoos() {
    elementoDaFila* aux = cab->atras;

}
void Aeroporto :: liberaVoos() {
    elementoDaFila* aux = cab->atras;
    elementoDaFila* troca;
    while(aux != nullptr && haPistaLivre() == true) {
        if(solicDePousoDec(aux->aviao) == true) {
            troca = aux->atras;
            remove(aux);
            aux = troca;
        }
        else {
            aux = aux->atras;
        }
    }
    //printaFila();   
}
void Aeroporto :: coletaEstatisticasEPrinta() {
    elementoDaFila* aux = cab->atras;

    tMedioEsperaPouso = 0;
    tMedioEsperaDecolagem = 0;
    quantMediaCombAvAPousar = 0;
    nAvioesAPousar = 0;

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
    cout << "--------------------------------------------------------------------------------" << endl;
}

#endif 