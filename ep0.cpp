#include <iostream>
#include <unistd.h>
#include "ep0.h"
#define SECOND 1000000

using namespace std;

Aviao* geradorDeAvioes(int C, int V) {

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
    int quantidadeCombustivel = 1 + rand()%C;
    int durVoo = 1 + rand()%V;
    int tempoDeEspera = 0;
    int prioridade = 0;

    if(emergencia) prioridade = 2;
    /*Se o avião for decolar, seu combustível deve ser de no mínimo o tempo de voo*/
    if(!pouso) quantidadeCombustivel = durVoo;
    /*Aviões que irão pousar não possuem duração de voo*/
    else durVoo = 0;

    if(pouso) aeroportoDestOrigem = aeroportos[0];

    return new Aviao( compAerea, numeroDoAviao, pouso, emergencia, aeroportoDestOrigem, quantidadeCombustivel, durVoo, tempoDeEspera, prioridade);
}
/*Uma transição entre as exibições dos dados do aeroporto*/
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
        //usleep(50000);
    } 
}

int main(int argc, char* argv[]) {
    /* T - Tempo de simulação, K - Número máximo de aviões que se comunicam com a torre por unid de tempo, 
    C - número máximo de tempo de combustível, V - Tempo máximo estimado de voo */
    int T, K , C, V;
    T = stoi(argv[1]); K = stoi(argv[2]); C = stoi(argv[3]); V = stoi(argv[4]); 
    int i, j, k; /*Iteradores*/
    int time = 8*60; /*Horário*/

    /*SEMENTE*/
    int semente = stoi(argv[5]);
    srand(semente);

    Aeroporto aeroporto;
    Aviao* aviao;    

    for (i = 0; i < T; i++) {
        cout << "*****************************AEROPORTO DE CONGONHAS*****************************" << endl << endl;
        printf("----------------------------------HORÁRIO %02d:%02d---------------------------------\n\n", time/60, time%60); 
        time++;

        for (j = 0; j < rand()%K; j++) {
            /*Objeto avião*/
            aviao = geradorDeAvioes(C, V);
                
            /*Tenta inserir os novos aviões na fila*/
            aeroporto.contatoComATorre(aviao);
        }
        aeroporto.liberaVoos();
        aeroporto.atualizaSituacaoDosAvioesNaFila();
        aeroporto.atualizaDispDePista();
        aeroporto.coletaEstatisticasEPrinta();
        
        //transicaoEntreExibicoes();
        //usleep(1000000);
    }

    return 0;
}