#include <iostream>
#include "ep0.h"
#define SECOND 1000000

using namespace std;

int main() {
    int T = 10; /*Tempo de simulação*/
    /*K - Número máximo de aviões que se comunicam com a torre por unid de tempo, 
    C - número máximo de tempo de combustível, V - Tempo máximo estimado de voo */
    int K = 15, C, V;
    long long i;
    int time=8*60; /*Horário*/
    int j; /*Iterador*/

    /********TESTES*******/
    /*O nosso aeroporto é o de CONGONHAS*/

    /*SEMENTE*/
    int semente = 23;
    srand(semente);

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

    /*Número de 3 dígitos*/
    int numeroDoAviao;

    /*********************/
    Aeroporto aeroporto;

    Aviao* aviao;    
    /*Delay na exibição*/
    for (i = 0; i < 1/*T*/; i++) {
        //if(i % SECOND == 0) {
            cout << "**********AEROPORTO DE CONGONHAS**********" << endl << endl;
            printf("--------------HORÁRIO %02d:%02d--------------\n\n", time/60, time%60); 
            time++;

            for (j = 0; j < 10/*K*/; j++) {
                /*Objeto avião*/
                aviao = new Aviao(companhiasAereas[rand()%7], rand()%900 + 100, false, rand()%2, aeroportos[rand()%33], rand()%2, 40, 0);
                cout << "Novo aviao: ";
                aeroporto.printaElemento(aviao);
                
                aeroporto.contatoComATorre(aviao);
                
                aeroporto.printaFila();
            }
            
            cout << "******************************************" << endl << endl;
        //}
    }
    
    
    

    return 0;
}