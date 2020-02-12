#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <iomanip>
#include <time.h>
#define PI 3.14159265359

using namespace std;

double numeroAleatorio(double menor, double maior) {
    return maior + menor*((double)(rand())/RAND_MAX); // Apenas gera numeros aleatorios.
}

double Easom (int d, double * aux){
        double resul, x1 = aux[0], x2 = aux[1]; // guardando os valores x1 e x2 nas determinadas posicoes do vetor
            double fator1 = -cos(x1) * cos(x2); // realizo o calculo por partes, nesta, calculo o cosseno de x1 * o cosseno de x2
            double fator2 = exp(-((x1 - PI)*(x1 - PI)) - ((x2-PI)*(x2-PI))); // Nesta parte, pego o expoente de (x1 - PI) elevado ao quadrado, e o (x2 - PI) elevado ao quadrado.
            resul = fator1 * fator2; // Calculo a multiplicação delas e guardo em uma variavel
        return resul; // retorno o valor de TODO o calculo feito
}
void EncontrarGbest(double ** pbest, double * gbest, int nP, int d){
    for(int i = 0 ; i < nP; i++){
        if(Easom(d,pbest[i]) < Easom(d,gbest)){ // Se a minha melhor posicao local for menor que a posicao Global,
                                                      // entao: gBest recebe pBest
                                                      // Ou seja, a melhor posicao global foi atualizada
            for(int j = 0; j < d; j++){
                gbest[j] = pbest[i][j];
            }
        }
    }
}
void PreencherPbest (double ** pbest, double ** matrixP, int nP, int d){
    for(int i = 0 ; i < nP; i++){
        for(int j = 0; j < d; j++){
            pbest[i][j] = matrixP[i][j]; // Aqui só é feito o preenchimento da pBest
        }
    }
}
void PSO(double ** vP,double ** matrixP, double ** pbest, int nP, int d,int n, double * gbest){ ///CALCULO DO PSO
    int CriterioDParada = 0;
    do{
        int w = 0.9 - (CriterioDParada *((0.9 - 0.4)/n));     /// FATOR DE INERCIA
        // W é o fator de inercia

        for(int i = 0; i < nP; i++){
            if(Easom(d,matrixP[i]) < Easom(d,pbest[i])){  /// SE O RESULTADO DA PARTICULA FOR MENOR QUE O MELHOR
                                                          // RESULTADO JA FEITO POR ELA, TROCA-SE OS VALORES
                for(int j = 0; j < d; j++){
                    pbest[i][j] = matrixP[i][j];

                    if(Easom(d,matrixP[i]) < Easom(d,gbest)){   /// SE O VALOR DA PARTICULA FOR MENOR QUE O GBEST, O GEST RECEBE ESSE VALOR
                        gbest[j] = pbest[i][j];
                    }
                }
            }

            for(int j = 0; j < d; j++){
                double r1 = numeroAleatorio(0,1); /// r1 e r2 recebem um numero aleatorio como 1 ou 0
                double r2 = numeroAleatorio(0,1);
                int con = 2; /// CONSTANTE INDICADA NO SLIDE

                double part1 = (w*vP[i][j]); ///PRIMEIRA PARTE

                double part2 = (con * r1 * (pbest[i][j] - matrixP[i][j])); ///SEGUNDA PARTE

                double part3 = (con * r2 *(gbest[j] - matrixP[i][j])); ///TERCEIRA PARTE

                vP[i][j] = (part1+part2+part3); /// SOMA AS TRES PARTES NA QUAL É DADA O VALOR DA VELOCIDADE DA PARTICULA

                if(vP[i][j]> 1) // Caso a velocidade seja maior que 20, será alterada para 20, que é o valor normal
                    vP[i][j] = 1;
                if(vP[i][j] < -1)
                    vP[i][j] = -1;

                matrixP[i][j] += vP[i][j]; // velocidade da particula é atualizada

                if(matrixP[i][j] > 100)
                    matrixP[i][j] = 100;
                else if(matrixP[i][j] < -100)
                    matrixP[i][j] = -100;
            }
        }

        cout << "Iteração : " << CriterioDParada << "\n" << Easom(d,gbest)  << "\n";
        CriterioDParada++;
    }while(CriterioDParada != n);
}

void imprimirM (double ** matrix, int nP, int d){ ///IMPRIMIR A MATRIZ PARA TESTES
    for(int i = 0 ; i <nP; i++){
        for(int j = 0; j < d; j++){
            cout <<matrix[i][j] << " ";
        }
        cout<<endl;
    }
}
void imprimirV (double * matrix, int d){ ///IMPRIMIR A VETORES PARA TESTES
    for(int i = 0 ; i < d; i++){
        cout << matrix[i] << " ";
    }
}
void preencher(double ** arr, int nP,int d){
    for(int i = 0; i < nP; i++){
        for(int j = 0; j < d; j++){
            arr[i][j] = numeroAleatorio(-100,100); // Preenche o vetor com os numeros indicados 
        }
    }
}
void preencherNulo(double ** arr, int nP,int d){
    for(int i = 0; i < nP; i++){
        for(int j = 0; j< d; j++){
            arr[i][j] = 0;
        }
    }
}