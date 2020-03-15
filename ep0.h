#include <iostream>
#ifndef AEROPORTO_H
#define AEROPORTO_H
using namespace std;

class Aviao {
    public:
        Aviao(string compArea, int numAviao, bool pous, bool emerg, 
        string aeroDestOrig, int quantComb, int durVoo, int tempEsp, int prioridade);
        void printaAviao(int exibir_pouso);
        void printaElemento();
        /*Gets*/
        string getCompanhiaAerea();
        int getPrioridade();
        bool getPouso();
        int getQuantCombust();
        int getDuracaoDoVoo();
        int getTempoDeEspera();
        /*Sets*/
        void setPrioridade(int prio);
        void setQuantCombust(int quant);
        void setTempoDeEspera(int tempo);
        
    private:
        string companhiaAerea;
        int prioridade;
        int numeroDoAviao;
        bool pouso;
        bool emergencia;
        string aeroportoDestOrig;
        int quantCombust;
        int duracaoDoVoo;
        int tempoDeEspera;
};

Aviao :: Aviao(string compArea, int numAviao, bool pous, bool emerg, 
string aeroDestOrig, int quantComb, int durVoo, int tempEsp, int pri) {
    companhiaAerea = compArea;
    numeroDoAviao = numAviao;
    pouso = pous;
    emergencia = emerg;
    aeroportoDestOrig = aeroDestOrig;
    quantCombust = quantComb;
    duracaoDoVoo = durVoo;
    tempoDeEspera = tempEsp;
    prioridade = pri;
}
string Aviao :: getCompanhiaAerea() {
    return companhiaAerea;
}
int Aviao :: getPrioridade() {
    return prioridade;
}
bool Aviao :: getPouso() {
    return pouso;
}
int Aviao :: getQuantCombust() {
    return quantCombust;
}
int Aviao :: getDuracaoDoVoo() {
    return duracaoDoVoo;
}
int Aviao :: getTempoDeEspera() {
    return tempoDeEspera;
}
void Aviao :: setPrioridade(int prio) {
    prioridade = prio;
}
void Aviao :: setQuantCombust(int quant) {
    quantCombust = quant;
}
void Aviao :: setTempoDeEspera(int tempo) {
    tempoDeEspera = tempo;
}
void Aviao :: printaAviao(int exibirPouso) {
    if(exibirPouso && pouso)
        cout << companhiaAerea << numeroDoAviao << "; ";
    else if(!pouso && !pouso)
        cout << companhiaAerea << numeroDoAviao << "; ";
}
void Aviao :: printaElemento() {
    cout << companhiaAerea << numeroDoAviao <<
    " , pri: " << prioridade << " , emg: " << emergencia <<
    " , pouso: " << pouso << " , qCom: " << quantCombust <<
    " , durVoo: " << duracaoDoVoo << " , tEsp: " << tempoDeEspera <<
    " , dest: "<< aeroportoDestOrig << endl;
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
1- aviões esperando por mais de 10% do tempo esperado de vôo para decolar
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
        /*Checa se é possível inserir os aviões na fila e insere se possível*/
        void contatoComATorre(Aviao* aviao);
        /*Libera os voos de acordo com a disponibilidade das pistas*/
        void liberaVoos();
        /*Rearranja os elementos da fila de acordo com suas prioridades*/
        void atualizaSituacaoDosAvioesNaFila();
        void atualizaDispDePista();
        void coletaEstatisticasEPrinta();

    private:
        /*DADOS*/

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
        double quantCombTotalAvPousaram;
        int quantVoosEmerg;
        int nAvioesQueDecolaram;
        int numAvioesCairam;

        /*Controle das filas*/
        int numElem;
        /*Informa a quantidade de aviões de cada prioridade*/
        int numElemPrio[4];

        /*Torre de controle - cabeça que aponta para as quatro filas com prioridades distintas*/
        cabecaTorreDeControle* torreDeControle;
    
        /*MÉTODOS*/
        /*Caso não haja possibilidade de entrar na fila, o avião é enviado ao aeroporto mais próximo*/
        void envioParaOutroAeroporto(Aviao* aviao);
        /*Informa se o avião consegue utilizar alguma pista ou não*/
        bool solicDePousoDec(Aviao* aviao);
        bool haPistaLivre();
        
        /*Métodos de exibição*/
        /*tipoDePrintagem(0-exibe elemento completo, 1-exibe o ID do aviao se atender aos parametros - pouso ou não)*/
        void printaFila(int tipoDePrintagem, int pouso);
        void printaFilaCompleta();
    
        /*Métodos de manipulação das filas*/
        void insere(Aviao* aviao);
        Aviao* remove(elementoDaFila* elm);
        void liberaAviao(Aviao* aviao);

};

Aeroporto :: Aeroporto() {

    pista1Disponivel = pista2Disponivel = pista3Disponivel = true;

    todasPistasOcupadas = false;

    tempLibPista1 = tempLibPista2 = tempLibPista3 = 0;

    nAvioesQuePousaram = 0;
    nAvioesAPousar = 0;
    tMedioEsperaPouso = 0;
    tMedioEsperaDecolagem = 0;
    quantMediaCombAvAPousar = 0;
    quantMediaCombAvPousaram = 0;
    quantCombTotalAvPousaram = 0;
    quantVoosEmerg = 0;
    nAvioesQueDecolaram = 0;
    numAvioesCairam = 0;

    numElem = 0;
    for (int i = 0; i < 4; i++) 
        numElemPrio[i] = 0;

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
        while (aux != nullptr) {
            torreDeControle->primerElmPrioridade[i] = aux->atras;
            //Apaga o aviao
            delete aux->aviao;
            //Apaga o elemento que contém o ponteiro para o avião
            delete aux;
            aux = torreDeControle->primerElmPrioridade[i];
        }    
    }
    //Deleta a cabeça
    delete torreDeControle;
}

/*Aviões contatam a torre de comando*/
void Aeroporto :: contatoComATorre(Aviao* aviao) {
    if(aviao->getPrioridade() == 2 && numElemPrio[2] >= 9)
        envioParaOutroAeroporto(aviao);
    /*O aeroporto só possue 3 pistas, leva-se uma unidade de tempo para decolar/pousar e
    mais 2 unidades para a liberação da pista, logo um avião de emergência precisa de no mínimo
    quantAvioesEmergenciaFila/3 * 3unidades de tempo + 2 unidades = numElemPrio[2] + 2 de combustível,
    pois quando o avião entrar na fila pode ser que a pista já esteja indisponível por 2 segundo */
    else if(aviao->getPrioridade() == 2 && (aviao->getQuantCombust() < numElemPrio[2]+2))
        envioParaOutroAeroporto(aviao);
    else if(aviao->getPrioridade() == 0 && aviao->getPouso() && aviao->getQuantCombust() < numElem+2)
        envioParaOutroAeroporto(aviao);
    else
        insere(aviao);
}

void Aeroporto :: envioParaOutroAeroporto(Aviao* aviao) {
    /*
    cout << "O avião: " << aviao->companhiaArea << aviao->numeroDoAviao << 
    "foi enviado para outro aeroporto" << endl;*/
    delete aviao;
}

bool Aeroporto :: solicDePousoDec(Aviao* aviao) {
    if(aviao == nullptr) return false;
    /*Se o avião tiver prioridade 0 e quiser pousar, não poderá utilizar a pista 3*/
    if(pista3Disponivel && (aviao->getPrioridade() == 0 && aviao->getPouso() == 1) == false) {
        /*Aumenta o número de voos de emergência realizados*/
        if (aviao->getPrioridade() == 2) /*Emergência*/
            quantVoosEmerg++;
        if (aviao->getPouso()) {
            quantCombTotalAvPousaram += aviao->getQuantCombust();
            nAvioesQuePousaram++;
        }
        else nAvioesQueDecolaram++;

        pista3Disponivel = false;
        tempLibPista3 = 2;
        return true;
    }
    else if (pista2Disponivel) {
        if (aviao->getPouso()) {
            quantCombTotalAvPousaram += aviao->getQuantCombust();
            nAvioesQuePousaram++;
        }
        else nAvioesQueDecolaram++;
        pista2Disponivel = false;
        tempLibPista2 = 2;
        return true;
    }
    else if (pista1Disponivel) {
        if (aviao->getPouso()) {
            quantCombTotalAvPousaram += aviao->getQuantCombust();
            nAvioesQuePousaram++;
        }
        else nAvioesQueDecolaram;
        pista1Disponivel = false;
        tempLibPista1 = 2;
        return true;
    }
    else
        return false;
}

/*Atualiza o tempo para a liberação de cada pista e a disponibilidade das mesmas*/
void Aeroporto :: atualizaDispDePista() {
    if(!pista1Disponivel) 
        if(--tempLibPista1 == 0) pista1Disponivel = true;
    if(!pista2Disponivel) 
        if(--tempLibPista2 == 0) pista2Disponivel = true;
    if(!pista3Disponivel)
        if(--tempLibPista3 == 0) pista3Disponivel = true;
}

/*Informa se há alguma pista está disponível ou se todas já estão ocupadas*/
bool Aeroporto :: haPistaLivre() {
    return (pista1Disponivel || pista2Disponivel || pista3Disponivel);
}

void Aeroporto :: insere(Aviao* aviao) {
    elementoDaFila* aux;
    int prioridade = aviao->getPrioridade();

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
    }
    else if(numElemPrio[prioridade] > 0) {
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
    int prioridade = elm->aviao->getPrioridade();
    elementoDaFila* aux;
    Aviao* aviaoRemovido = elm->aviao;

    aux = torreDeControle->primerElmPrioridade[prioridade];
    while(aux != nullptr) {
        if(aux == elm) {
            /*Não é o primeiro elemento da fila*/
            if(aux->frente != nullptr) {
                aux->frente->atras = aux->atras;
            }
            /*É o primeiro elemento da fila*/
            else {
                torreDeControle->primerElmPrioridade[prioridade] = aux->atras;
            }
            if(aux->atras != nullptr) {
                aux->atras->frente = aux->frente;
            }
            /*Se o elemento é o último da fila, atualiza o ponteiro
            que aponta para o último elemento*/
            else {
                torreDeControle->ultElmPrioridade[prioridade] = elm->frente;
            }
        }
        aux = aux->atras;
    }
    
    /*Checar se só exclue o elemento ou o avião também*/
    delete elm;
    numElem--;  
    numElemPrio[prioridade]--;
    return aviaoRemovido;
}

void Aeroporto :: liberaAviao(Aviao* aviao) {
    delete aviao;
}

void Aeroporto :: atualizaSituacaoDosAvioesNaFila() {
    elementoDaFila *aux, *troca;
    Aviao* aviaoComNovaPrioridade;
    int prioridade;
    int nAvioesComRiscoDeComb = 0;
    int nAvioesComFuturoRiscoDeComb = 0;
    
    for (prioridade = 0; prioridade < 4; prioridade++) {
        aux = torreDeControle->primerElmPrioridade[prioridade];
        while(aux != nullptr) {
            //Somente os aviões que querem pousar possuem seu combustível reduzido com o tempo
            if(aux->aviao->getPouso())
                aux->aviao->setQuantCombust(aux->aviao->getQuantCombust() - 1); 
            aux->aviao->setTempoDeEspera(aux->aviao->getTempoDeEspera() + 1);

           
            if(aux->aviao->getQuantCombust() < 0) {
                cout << "O avião caiu" << endl;
                liberaAviao(remove(aux));
                numAvioesCairam++;
            }
            else if( prioridade == 0 && aux->aviao->getQuantCombust() <= 5 && aux->aviao->getQuantCombust() > 2)
                nAvioesComFuturoRiscoDeComb++;
            else if( prioridade == 0 && aux->aviao->getQuantCombust() <= 2 && nAvioesComRiscoDeComb <= 3) {
                nAvioesComRiscoDeComb++;
                //troca armazena o aviao que esta atras do atual
                troca = aux->atras;
                //O aviao que mudou de prioridade ira mudar de fila
                aviaoComNovaPrioridade = remove(aux);
                aviaoComNovaPrioridade->setPrioridade(3);
                contatoComATorre(aviaoComNovaPrioridade);
                aux = troca;
                continue;
            }
            else if ( prioridade == 0 && aux->aviao->getQuantCombust() <= 5 && nAvioesComFuturoRiscoDeComb > 3) {
                troca = aux->atras;
                //O aviao que mudou de prioridade ira mudar de fila
                aviaoComNovaPrioridade = remove(aux);
                envioParaOutroAeroporto(aviaoComNovaPrioridade);
                aux = troca;
                continue;
            }
            
            else if( prioridade == 0 && !aux->aviao->getPouso() && (aux->aviao->getTempoDeEspera() > aux->aviao->getDuracaoDoVoo()/10) ) {
                troca = aux->atras;
                //O aviao que mudou de prioridade ira mudar de fila
                aviaoComNovaPrioridade = remove(aux);
                aviaoComNovaPrioridade->setPrioridade(1);
                contatoComATorre(aviaoComNovaPrioridade);
                aux = troca;
                continue;    
            }
            
            aux = aux->atras;
        }
    }
    
}
void Aeroporto :: liberaVoos() {

    while(haPistaLivre() == true) {
        if(torreDeControle->primerElmPrioridade[3] != nullptr && solicDePousoDec(torreDeControle->primerElmPrioridade[3]->aviao)) 
            liberaAviao(remove(torreDeControle->primerElmPrioridade[3]));

        else if(torreDeControle->primerElmPrioridade[2] != nullptr && solicDePousoDec(torreDeControle->primerElmPrioridade[2]->aviao))
            liberaAviao(remove(torreDeControle->primerElmPrioridade[2]));
            
        else if(torreDeControle->primerElmPrioridade[1] != nullptr && solicDePousoDec(torreDeControle->primerElmPrioridade[1]->aviao)) 
            liberaAviao(remove(torreDeControle->primerElmPrioridade[1])); 
        
        else if(torreDeControle->primerElmPrioridade[0] != nullptr && solicDePousoDec(torreDeControle->primerElmPrioridade[0]->aviao)) 
            liberaAviao(remove(torreDeControle->primerElmPrioridade[0])); 
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
            if(aux->aviao->getPouso() == 1) {
                tMedioEsperaPouso += aux->aviao->getTempoDeEspera();
                quantMediaCombAvAPousar += aux->aviao->getQuantCombust();
                nAvioesAPousar++;
            }
            else if(aux->aviao->getPouso() == 0)
                tMedioEsperaDecolagem += aux->aviao->getTempoDeEspera();

            aux = aux->atras;
        }
    }

    if(nAvioesAPousar != 0) {
        tMedioEsperaPouso /= nAvioesAPousar;
        quantMediaCombAvAPousar = quantMediaCombAvAPousar / nAvioesAPousar;
    }
    /*Não há informações acerca dos aviões*/
    else {
        tMedioEsperaPouso = 0;
        quantMediaCombAvAPousar = -1;
    }
    ((numElem-nAvioesAPousar) != 0) ? tMedioEsperaDecolagem /= (numElem - nAvioesAPousar) : tMedioEsperaDecolagem = 0;
    ((nAvioesQuePousaram != 0)) ? quantMediaCombAvPousaram = quantCombTotalAvPousaram/nAvioesQuePousaram : quantMediaCombAvPousaram = -1;
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
    cout << " * A quantidade total de aviões que já pousaram é: " << nAvioesQuePousaram << endl << endl;
    cout << " * A quantidade total de aviões que já decolaram é: " << nAvioesQueDecolaram << endl << endl;
    cout << " * A quantidade de aviões que cairam é: " << numAvioesCairam << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}
/*
void Aeroporto :: printaAviao(Aviao* aviao, int pouso) {
    if(pouso && aviao->pouso)
        cout << aviao->companhiaArea << aviao->numeroDoAviao << "; ";
    else if(!pouso && !aviao->pouso)
        cout << aviao->companhiaArea << aviao->numeroDoAviao << "; ";
}
void Aeroporto :: printaElemento(Aviao* aviao) {
    cout << aviao->companhiaArea << aviao->numeroDoAviao <<
    " , pri: " << aviao->prioridade << " , emg: " << aviao->emergencia <<
    " , pouso: " << aviao->pouso << " , qCom: " << aviao->quantCombust <<
    " , durVoo: " << aviao->duracaoDoVoo << " , tEsp: " << aviao->tempoDeEspera <<
    " , dest: "<< aviao->aeroportoDestOrig << endl;
}
*/
void Aeroporto :: printaFila(int tipoDePrintagem, int pouso) {
    int nPouso, nDec;
    nPouso = nDec = 0;
    elementoDaFila* aux;

    for (int i = 0; i < 4; i++) {
        aux = torreDeControle->primerElmPrioridade[i];
        while (aux != nullptr) {
            if(tipoDePrintagem == 0)
                aux->aviao->printaElemento();
            else {
                /*Quebra a linha na printagem do terminal*/
                if(pouso && aux->aviao->getPouso()) nPouso++;
                else if(!pouso && !aux->aviao->getPouso()) nDec++;

                if( (nPouso+1 % 5) == 0 || (nDec+1 % 5) == 0) cout << endl << "   ";
                aux->aviao->printaAviao(pouso);
                //printaAviao(aux->aviao, pouso);
            }
            aux = aux->atras;
        }    
    }
    cout << endl;
}
void Aeroporto :: printaFilaCompleta() {
    elementoDaFila* aux;
    for (int i = 3; i >= 0; i--) {
        aux = torreDeControle->primerElmPrioridade[i];
        cout << "Voos de prioridade" << i << ": " << endl;
        while(aux != nullptr) {
            aux->aviao->printaElemento();
            aux = aux->atras;
        }    
    }
}
#endif  
/*O codigo tinha 644 linhas de codigo*/