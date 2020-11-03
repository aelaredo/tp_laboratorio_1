#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "validaciones.h"

/**********************************************************************************
 *
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.bin (modo binario).
    10. Salir
**********************************************************************************/



int main()
{
	int   menu = 0;
	LinkedList* miLista;
	int id;
	miLista = ll_newLinkedList();
	id = controller_getNewId(miLista);

	do{
			fflush(stdout);
		    menu = controller_showMenu();

			switch(menu)
			{
			case 1:
					if (controller_loadFromText("data.csv" , miLista) == 1)
					{
						id = controller_getNewId(miLista);
						printf("\nSe cargo la linked list exitosamente\n");
					}
				break;
			case 2:
					if (controller_loadFromBinary("data.bin", miLista)== 1)
					{
						id = controller_getNewId(miLista);
						printf("\nSe cargo la linked list exitosamente\n");
					}
				break;
			case 3:
				if (controller_addEmployee(miLista, id)==1)
				{
					id = controller_getNewId(miLista);
					printf("\nSe agrego un empleado con exito\n");
				}
				break;
			case 4:
				controller_editEmployee(miLista);
				break;
			case 5:
				controller_removeEmployee(miLista);
				break;
			case 6:
				controller_ListEmployee(miLista);
				break;
			case 7:
				controller_sortEmployee(miLista);
				break;
			case 8:
				if(controller_saveAsText("datanuevo.csv",miLista) == 1){
					printf("\nSe guardo en texto con exito\n");
				}
				break;
			case 9:
				if(controller_saveAsBinary("data.bin", miLista)== 1){
					printf("\nSe guardo en binario con exito\n");
				}
				break;
			case 10:
				break;
			}

			  }while (menu != 10);


		return 0;
}





