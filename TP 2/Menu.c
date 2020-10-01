

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Menu.h"
#include "utn_getData.h"

int Menu (char opciones [500])
{


    int eleccion;


        printf("%s \n ", opciones);

        scanf("%d", &eleccion);


    return eleccion;
}
