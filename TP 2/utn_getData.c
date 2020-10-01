#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utn_getData.h"

//////static int myGets (char* cadena, int longitud);


int myGets (char* cadena, int longitud)
{
    int retorno = -1;
    char bufferString [4096];


    if(cadena!=NULL && longitud >0)
    {
        __fpurge(stdin);
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


