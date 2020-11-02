#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "validaciones.h"


int myGets (char* cadena, int longitud)
{
    int retorno = -1;
    char bufferString [50];


    if(cadena!=NULL && longitud >0)
    {
    	fflush(stdin);
        fflush(stdout);
        if(fgets(bufferString, sizeof(bufferString), stdin) != NULL) ////fgets necesita saber a donde va a escribir, la longitud y de donde
        {
            if (bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
            {
                bufferString[strnlen(bufferString, sizeof(bufferString))-1] = '\0';
            }
            if (strnlen(bufferString, sizeof(bufferString)) <= longitud)
            {
                strncpy(cadena, bufferString, longitud);
                retorno = 0;
            }
        }
    }

    return retorno;
}

int getInt (int* pResultado)
{
    int retorno = -1;
    char bufferString [50];


    if(pResultado != NULL &&
       myGets(bufferString, sizeof(bufferString)) == 0 &&
       esNumerica(bufferString, sizeof(bufferString))==1)
        {

            retorno = 0;
            *pResultado = atoi(bufferString);
        }

    return retorno;
}

char getChar(char message[],char errorMessage[])
{
    char aux;

    puts(message);
    fflush(stdin);
    fflush(stdout);
    scanf("%c",&aux);


    while (aux != 'f' && aux !='m' && aux!='F'&& aux!='M')
    {
    puts(errorMessage);
    fflush(stdin);
    fflush(stdout);
    scanf("%c",&aux);
    };

    return aux;
}


int esNumerica (char* cadena, int limite)
{
    int retorno = 1;
    int i;

    for (i=0; i < limite && cadena[i] != '\0'; i++)
    {
        if (i==0 && (cadena[i] == '+' || cadena[i] == '-'))
        {

            continue;
        }
        if(cadena[i] < '0' || cadena [i] >'9' )
        {

            retorno = 0;
            break;
         }
    }

    return retorno;
}

int getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int retorno = -1;
    int bufferInt;

    while(reintentos >0)
    {
        reintentos--;
        printf("%s", mensaje);
        if(getInt(&bufferInt)==0)
        {
            if (bufferInt >= minimo && bufferInt <= maximo)
            {
                *pResultado = bufferInt;
                retorno=0;
                break;
            }
        }
        printf("%s", mensajeError);
    }

return retorno;

}

int getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int retorno = -1;
    float bufferFloat;

    while(reintentos >0)
    {
        reintentos--;
        printf("%s", mensaje);
        if(getFloat(&bufferFloat)==0)
        {
            if (bufferFloat >= minimo && bufferFloat <= maximo)
            {
                *pResultado = bufferFloat;
                retorno=0;
                break;
            }
        }
        printf("%s", mensajeError);
    }

return retorno;

}



int getFloat (float* pResultado)
{
    int retorno = -1;
    char bufferString [50];


        if(pResultado != NULL &&
       myGets(bufferString, sizeof(bufferString)) == 0 &&
       esFlotante(bufferString, sizeof(bufferString))==1)
        {

            retorno = 0;
            *pResultado = atof(bufferString);
        }

    return retorno;

}

int esFlotante (char* cadena, int limite)
{
    int retorno = 1;
    int pointFlag = 0;
    int i;

    for (i=0; i < limite && cadena[i] != '\0'; i++)
    {
        if (i==0 && (cadena[i] == '+' || cadena[i] == '-'))
        {

            continue;
        }

        if (cadena[i]== '.' && pointFlag == 0 )
        {

            pointFlag = 1;
            continue;
        }

        if(cadena[i] < '0' || cadena [i] >'9' || pointFlag == 2 )
        {

            retorno = 0;
            break;
         }
    }
return retorno;

}

int esSoloLetras(char str[])
{
   int retorno = -1;
   int i=0;
   while(str[i] != '\0')
   {
       if((str[i] != ' ') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
        retorno = 0;
       i++;
   }
   return retorno;
}

int confirmEdit(int editID)
{
    int confirmEdit;
    int confirmState = -1;

    do{
        printf("\n Reingrese el ID para confirmar la accion. Ingrese 0 para volver al menu \n");
        fflush(stdout);
        scanf("%d",&confirmEdit);  ///// escaneo la confirmacion que ingresa el usario
        if (confirmEdit == editID) ///// comparo lo que esbribio el usuario con el parametro de confirmacion
        {
        confirmState = 1; ////// si es asi devuelvo 1 como exito


        }else if (confirmEdit == 0) ///// si ingreso 0 cancelo la opeacion
        {
        confirmState = confirmEdit;   /////cargo el 0 como valor de retorno
        break; ////// salgo del bucle sin necesidad de comprobar que sea lo que yo quiero
        }

    }while (confirmEdit != editID); //// mientras no ingrese el valor necesario para la confirmacion ó no salgo al apretar 0

 return confirmState; //// este valo va a ser siempre 0 si se cancelo la accion o 1 si se paso la confirmacion.
}
