#include <iostream>
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
    bool pouso = rand()%2;
    bool emergencia = rand()%2;
    string aeroportoDestOrigem = aeroportos[rand()%33];
    int quantidadeCombustivel = 40 + rand()%40;
    int durVoo = 30 + rand()%50;
    int tempoDeEspera = 0;
    int prioridade = 0;

    if(emergencia) prioridade = 2;

    cout << "pouso: " << rand()%2 << endl;

    return new Aviao( compAerea, numeroDoAviao, pouso, emergencia, aeroportoDestOrigem, quantidadeCombustivel, durVoo, tempoDeEspera, prioridade);
}

int main() {
    int T = 10; /*Tempo de simulação*/
    /*K - Número máximo de aviões que se comunicam com a torre por unid de tempo, 
    C - número máximo de tempo de combustível, V - Tempo máximo estimado de voo */
    int K = 15, C, V;
    long long i;
    int time=8*60; /*Horário*/
    int j, k; /*Iterador*/

    /*SEMENTE*/
    int semente = 23;
    srand(semente);

    Aeroporto aeroporto;

    Aviao* aviao;    
    /*Delay na exibição*/
    for (i = 0; i < 6/*T*/; i++) {
        //if(i % SECOND == 0) {
            cout << "*****************************AEROPORTO DE CONGONHAS*****************************" << endl << endl;
            printf("----------------------------------HORÁRIO %02d:%02d---------------------------------\n\n", time/60, time%60); 
            time++;

            for (j = 0; j < 5/*K*/; j++) {
                /*Objeto avião*/
                aviao = geradorDeAvioes();
                //cout << "Novo aviao: ";
                //aeroporto.printaElemento(aviao);
                
                /*Insere os novos avioes na fila*/
                aeroporto.contatoComATorre(aviao);

                /*OUTPUT*/
                /*Quais avioes estao esperando para decolar e pousar*/
                //aeroporto.printaFila(0, 0);
            }
            //aeroporto.atualizaFilaDeVoos();
            aeroporto.liberaVoos();
            aeroporto.atualizaDispDePista();
            aeroporto.coletaEstatisticasEPrinta();


            cout << "********************************************************************************" << endl << endl;
            int num = 27;
            bool parou = false;
            for(j = 0; j < num && !parou; j++) {
                for ( k = 0; k < num; k++) {
                    if(k == num/2 && j == (num/2) )
                        cout << "   ";
                    else if ( k <= j && j < (num/2)+1 )
                        cout << "   ";
                    else if( k >= num-j-1 && j < (num/2)+1 )
                        cout << "   ";
                    else if(j < (num/2) ) 
                        cout << " * ";
                    else
                        parou = true;
                }
                cout << endl;
            }
                
        //}
    }
    
    
    

    return 0;
}