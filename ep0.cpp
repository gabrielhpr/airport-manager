#include <iostream>
#include <unistd.h>
#include "ep0novo.h"
#define SECOND 1000000

using namespace std;

Aviao* geradorDeAvioes() {

    /********TESTES*******/
    /*O nosso aeroporto é o de CONGONHAS*/

    /*As companhias aéreas são AZUL, GOL, LATAM, AVIANCA, AIR FRANCE, EMIRATES
    COPA AIRLINES*/
    string companhiasAereas[7] = {"AZ", "GO", "LA", "AV", "AF", "EM", "CA"};

    /*Os aeroportos são Congonhas, São José dos Campos, Bento Gonçalves, 
    Itaqui, Costa Marques, Pimenta Bueno, Florianópolis, Ubatuba, Jundiaí,
    Araçatuba, Assis, Avaré-Arandu, Bauru-Arealva, Dracena, Franca, Marília,
    Presidente Prudente, Ribeirão Preto, São Carlos, São José do Rio Preto, Sorocaba,
    Votuporanga, Barretos, Bauru, Botocatu, Dianópolis, Gurupi, Miracema do Tocantins,
    Porto Nacional, Santa Isabel do Morro, Olavo Cecco Rigon, Blumenau, Feijó */
    string aeroportos[33] = {"CGH", "SJK", "BGV", "ITQ", "CQS", "PBQ", "FLN", "UBT",
    "QDV", "ARU", "AIF", "QVP", "JTC", "QDC", "FRC", "MII", "PPB", "RAO", "QSC",
    "SJP", "SOD", "VOT", "BAT", "BAU", "QCP", "DNO", "GRP", "NTM", "PNB", "IDO",
     "CCI", "BNU", "FEJ"};

    string compAerea = companhiasAereas[rand()%7];
    /*Número de 3 dígitos*/
    int numeroDoAviao = rand()%900+100;
    bool pouso = (rand()%2);
    /*Os vôos de emergência ocorrem com probabilidade de 10%*/
    bool emergencia = ( (rand()%10) == 0 ) ? 1 : 0;
    string aeroportoDestOrigem = aeroportos[rand()%33];
    int quantidadeCombustivel = 4 + rand()%5;
    int durVoo = 30 + rand()%20;
    int tempoDeEspera = 0;
    int prioridade = 0;

    if(emergencia) prioridade = 2;
    if(!pouso) quantidadeCombustivel = durVoo;
    else durVoo = 0;
    if(pouso) aeroportoDestOrigem = aeroportos[0];

    return new Aviao( compAerea, numeroDoAviao, pouso, emergencia, aeroportoDestOrigem, quantidadeCombustivel, durVoo, tempoDeEspera, prioridade);
}

void transicaoEntreExibicoes() {
    int num = 27;
    bool parou = false;
    int j, k;
    cout << "********************************************************************************" << endl
    << endl;
    for (j = 0; j < num && !parou; j++) {
        for (k = 0; k < num; k++) {
            if (k == num / 2 && j == (num / 2))
                cout << "   ";
            else if (k <= j && j < (num / 2) + 1)
                cout << "   ";
            else if (k >= num - j - 1 && j < (num / 2) + 1)
                cout << "   ";
            else if (j < (num / 2))
                cout << " * ";
            else
                parou = true;
        }
        cout << endl;
        usleep(50000);
    } 
}

int main() {
    int T = 100; /*Tempo de simulação*/
    /*K - Número máximo de aviões que se comunicam com a torre por unid de tempo, 
    C - número máximo de tempo de combustível, V - Tempo máximo estimado de voo */
    int K = 10, C, V;
    int i, j, k; /*Iterador*/
    int time = 8*60; /*Horário*/

    /*SEMENTE*/
    int semente = 23;
    srand(semente);

    Aeroporto aeroporto;
    Aviao* aviao;    

    /*Delay na exibição*/
    for (i = 0; i < T; i++) {
        cout << "*****************************AEROPORTO DE CONGONHAS*****************************" << endl << endl;
        printf("----------------------------------HORÁRIO %02d:%02d---------------------------------\n\n", time/60, time%60); 
        time++;

        for (j = 0; j < rand()%3+1; j++) {
            /*Objeto avião*/
            aviao = geradorDeAvioes();
            //cout << "Novo aviao: ";
            //aeroporto.printaElemento(aviao);
                
            /*Tenta inserir os novos avioes na fila*/
            aeroporto.contatoComATorre(aviao);
        }
        //aeroporto.printaFilaCompleta();
        aeroporto.liberaVoos();
        aeroporto.atualizaSituacaoDosAvioesNaFila();
        aeroporto.atualizaDispDePista();
        //aeroporto.printaFilaCompleta();
        aeroporto.coletaEstatisticasEPrinta();
        
        transicaoEntreExibicoes();
        usleep(1000000);
    }

    return 0;
}