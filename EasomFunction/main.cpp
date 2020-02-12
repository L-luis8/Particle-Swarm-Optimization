#include "Funcoes.h"

int main(){

    setlocale(LC_ALL, "");

    srand(time(NULL));
    int nP = 1500; // Melhor 1500
    int d = 2;
    int n = 100; // Melhor 100 | n = numero de iteraçoes

    // Abaixo nada de novo, só alocando as matrizes e vetores

    double **  matrixP= new double * [nP];
    double **  vP = new double * [nP];
    double ** pbest = new double *[nP]; 
    double * gbest = new double[d];

    for(int i = 0; i< nP; i++){
        matrixP[i] = new double[d];
        vP[i] = new double[d];
        pbest[i] = new double[d];
    }

    preencher(matrixP,nP,d);
    preencherNulo(vP,nP,d);
    PreencherPbest(pbest,matrixP,nP,d);
    EncontrarGbest(pbest,gbest,nP,d);

    /*
    cout << "MATRIZ DE PARTICULAS" << endl;
    imprimirM(matrixP,nP,d);
    cout << "\n--------------------"<<endl;

    cout << "VELOCIDADE DAS PARTICULAS" << endl;
    imprimirM(vP,nP,d);
    cout << "\n--------------------"<<endl;

    cout << "MATRIZ DE PBEST" << endl;
    imprimirM(pbest,nP,d);
    cout << "\n--------------------"<<endl;

    cout<< "GBEST"<<endl;
    imprimirV(gbest,d);
    cout << "\n--------------------"<<endl;
    */

    PSO(vP,matrixP,pbest,nP,d,n,gbest);

    cout << fixed << setprecision(4);
    //Define a precisão decimal a ser usada para 
    //formatar valores de ponto flutuante nas operações de saída.
    
    imprimirV(gbest,d); // Imprimindo melhor posição global

    for(int i = 0; i < nP; i++){ // Desalocando a memória
        delete matrixP[i];
        delete vP[i];
        delete pbest[i];
    }
    delete vP;
    delete matrixP;
    delete pbest;
    delete gbest;
}