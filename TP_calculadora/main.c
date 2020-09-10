#include <stdio.h>
#include <stdlib.h>
#include "Calculadora.h"

int main()
{
    int opcion;
    float primerOperando;
    float segundoOperando;
    float resultadoSuma;
    float resultadoResta;
    float resultadoMultiplicacion;
    float resultadoDivision;
    int factorialPrimer;
    int factorialSegundo;
    int flagOperandos;
    int flagCalculos;

    flagOperandos = 0;
    flagCalculos = 0;

    do{

        opcion = PedirEntero("\nElegi un numero \n 1. Ingrese el primer operando\n 2. Ingrese el segundo operando\n 3. Calcular las operaciones \n 4. Informar resultados de numeros\n 5. Salir\n");

        switch(opcion)
        {
        case 1:
            printf("\n Ingrese el primer operando ");
            scanf("%f", &primerOperando);
            flagOperandos++;
            break;
        case 2:
            printf("\n Ingrese el segundo operando ");
            scanf("%f", &segundoOperando);
            flagOperandos++;
            break;
        case 3:
            if (flagOperandos == 0){
                printf("Primero debe ingresar dos operandos");
            } else if (flagOperandos == 1){
                printf("Le falta ingresar un operando");
            } else{
            printf("\n Se calcularan las siguientes operaciones");

            printf("\n a) La suma %.2f + %.2f",primerOperando, segundoOperando);
            resultadoSuma = SumarNumeros(primerOperando, segundoOperando);

            printf("\n b) La resta %.2f - %.2f ",primerOperando, segundoOperando);
            resultadoResta = RestarNumeros(primerOperando, segundoOperando);

            if (primerOperando == 0 || segundoOperando == 0){
                printf("\n c) No se puede dividir por cero ");
            }else{
            printf("\n c) La division %.2f / %.2f", primerOperando, segundoOperando);
            }
            resultadoDivision = DividirNumeros(primerOperando, segundoOperando);

            printf("\n d) La multiplicacion %.2f * %.2f", primerOperando, segundoOperando);
            resultadoMultiplicacion = MultiplicarNumeros(primerOperando, segundoOperando);

            if(primerOperando < 0 ){
                printf("\n e) El factorial de %.2f no se púede calcular por ser negativo ", primerOperando);
            }else{
                printf("\n e) El factorial de la parte entera del numero %.2f ", primerOperando);
                factorialPrimer = FactorialNumero(primerOperando);
            }

             if(segundoOperando < 0 ){
             printf("\n f) El factorial de %.2f no se puede calcular por que es negativo ", segundoOperando);
            }else {
                printf("\n f) El factorial de la parte entera del numero %.2f ", segundoOperando);
                factorialSegundo = FactorialNumero(segundoOperando);
            }

            flagCalculos = 1;
            }
            break;
        case 4:
            if (flagOperandos == 0){
                printf("Primero debe ingresar dos operandos");
            } else if (flagOperandos == 1){
                printf("Le falta ingresar un operando");
            } else if (flagCalculos == 0){
                printf("Le falta calcular las operaciones elija la opcion 3 por favor");
            } else{
            printf("\n Los resultados son los siguientes");
            printf("\n a) El resultado de %.2f + %.2f es %.2f ", primerOperando, segundoOperando, resultadoSuma);
            printf("\n b) El resultado de %.2f - %.2f es %.2f ", primerOperando, segundoOperando, resultadoResta);
            }

            if (primerOperando == 0 || segundoOperando == 0){
                printf("\n c) No se puede dividir por cero ");
            }else {
                printf("\n c) El resultado de %.2f / %.2f es %.2f ", primerOperando, segundoOperando, resultadoDivision);
            }

            printf("\n d) El resultado de %.2f * %.2f es %.2f ", primerOperando, segundoOperando, resultadoMultiplicacion);


            if(primerOperando < 0 ){
                printf("\n e) El factorial de %.2f no se púede calcular por ser negativo ", primerOperando);
            }else{
                printf("\n e) El factorial de %.2f es %d ", primerOperando, factorialPrimer);
            }

            if(segundoOperando < 0 ){
             printf("\n f) el factorial de %.2f no se puede calcular por que es negativo ", segundoOperando);
            }else {
                printf("\n f) el factorial de %.2f es %d \n", segundoOperando, factorialSegundo);
            }

        break;

        }
    }while (opcion != 5);


    return 0;
}
