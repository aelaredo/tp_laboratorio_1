#include "Calculadora.h"

float SumarNumeros (float primerOperando, float segundoOperando){

float resultado;

resultado = primerOperando + segundoOperando;

return resultado;

}

////////////////////////////////////////////////////////////////////


float RestarNumeros (float primerOperando, float segundoOperando){

float resultado;

resultado = primerOperando - segundoOperando;

return resultado;
}

////////////////////////////////////////////////////////////////////

float DividirNumeros (float primerOperando, float segundoOperando){

float resultado;

resultado = primerOperando / segundoOperando;

return resultado;

}

////////////////////////////////////////////////////////////////////////

float MultiplicarNumeros (float primerOperando, float segundoOperando){

float resultado;

resultado = primerOperando * segundoOperando;

return resultado;

}

////////////////////////////////////////////////////////////////////////

int FactorialNumero (float numero){

    int resultado;
    int multiplicador;


    resultado = 1;



    for (int i = 1; i <= numero ; i++ )
    {
        multiplicador = numero - i;

        resultado += resultado * multiplicador;

    }

    return resultado;
}

