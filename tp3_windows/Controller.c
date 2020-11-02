#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "validaciones.h"
#include "Controller.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 0;

	if (pArrayListEmployee != NULL && path != NULL && ll_isEmpty(pArrayListEmployee) == 1)
	{
		FILE* fpArchivo;
		fpArchivo = fopen(path, "r");
		if (fpArchivo != NULL)
		{
			if(parser_EmployeeFromText(fpArchivo , pArrayListEmployee)==0)
			{
			fclose(fpArchivo);
			retorno = 1;
			}
		}
	}else
	{
		printf("\n Hubo un error al cargar la linked list desde texto");
	}

    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int isEmpty = ll_isEmpty(pArrayListEmployee);
	if (pArrayListEmployee != NULL && path != NULL && isEmpty == 1)
	{
		FILE* fpArchivo;
		fpArchivo = fopen(path, "rb");
		if (fpArchivo != NULL)
		{
			if(parser_EmployeeFromBinary(fpArchivo , pArrayListEmployee)==0)
			{
			retorno = 1;
			}
			fclose(fpArchivo);
		}else{
			printf("\nHubo un error con el path del archivo binario\n");
		}
	}else
	{
		printf("\nHubo un error al cargar la linked list desde archivo binario\n ");
	}

    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_addEmployee(LinkedList* pArrayListEmployee, int id)
{
	int retorno = 0;
	int isEmpty = ll_isEmpty(pArrayListEmployee);
	if (pArrayListEmployee != NULL && id > 0 && isEmpty == 0)
{

	Employee* localEmployee;
	int flagCheck = 0;
	char idStr[50];
	char nombreStr[50];
	char horasTrabajadasStr[50];
	int horasTrabajadas;
	char sueldoStr[50];
	int sueldo;

	sprintf(idStr, "%d", id);

	printf("\nIngrese el nombre");
	fflush(stdout);
	fflush(stdin);

	if(myGets(nombreStr, 20)==0){
	flagCheck++;
	}

	if (getNumero(&horasTrabajadas,"\nIngrese las horas trabajadas", "opcion no valida", 1, 100000, 20)==0){
		sprintf(horasTrabajadasStr, "%d", horasTrabajadas);
		flagCheck++;
	}

	if (getNumero(&sueldo,"\nIngrese el sueldo", "opcion no valida", 1, 10000000, 20)==0){
		sprintf(sueldoStr, "%d", sueldo);
		flagCheck++;
	}

	if (flagCheck == 3){
	localEmployee = employee_newParametros(idStr, nombreStr , horasTrabajadasStr, sueldoStr);
	ll_add(pArrayListEmployee, localEmployee);
	retorno = 1;
	}

}else if(isEmpty == 1)
{
	printf("\nEl array esta vacio, por favor carguelo desde la opcion 1 o 2\n");
}
else{
	printf("\nHubo un error al agregar un nuevo empleado\n");
}


    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int isEmpty =ll_isEmpty(pArrayListEmployee);
if (pArrayListEmployee != NULL && isEmpty == 0)
{
	Employee* localEmployee;
	int flagCheck = 0;
	int idEditar;
	int indexToEdit;
	char idStr[50];
	char nombreStr[50];
	char horasTrabajadasStr[50];
	int horasTrabajadas;
	char sueldoStr[50];
	int sueldo;

	controller_ListEmployee(pArrayListEmployee);

	getNumero(&idEditar,"\nIngrese el ID a ser editado", "Opcion no valida", 1, (controller_getNewId(pArrayListEmployee)-1), 20);
	indexToEdit = controller_findIndexOfEmployeeById(pArrayListEmployee, idEditar);

	if (indexToEdit!= -1)
	{
		printf("\nIngrese el nombre");
		fflush(stdout);
		fflush(stdin);

		if(myGets(nombreStr, 20)==0)
		{
		flagCheck++;
		}

		if (getNumero(&horasTrabajadas,"\nIngrese las horas trabajadas", "opcion no valida", 1, 100000, 20)==0)
		{
		sprintf(horasTrabajadasStr, "%d", horasTrabajadas);
		flagCheck++;
		}

		if (getNumero(&sueldo,"\nIngrese el sueldo", "opcion no valida", 1, 10000000, 20)==0)
		{
		sprintf(sueldoStr, "%d", sueldo);
		flagCheck++;
		}

		if (flagCheck==3)
		{
		sprintf(idStr, "%d", idEditar);
		localEmployee = employee_newParametros(idStr, nombreStr, horasTrabajadasStr, sueldoStr);

				if (localEmployee !=NULL)
				{
					ll_set(pArrayListEmployee, indexToEdit, localEmployee);
					retorno = 1;
				}
		}

	}else
	{
	printf("\nNo se encuentra el id en la lista de empleados");
	}

}else if(isEmpty == 1)
{
	printf("\nEl array esta vacio, por favor carguelo desde la opcion 1 o 2\n");
}else
{
	printf("\nHubo un error al editar un nuevo empleado\n");
}

    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int isEmpty = ll_isEmpty(pArrayListEmployee);
	if (pArrayListEmployee != NULL && isEmpty == 0)
	{
		int idToDelete;
		int indexToDelete;
		Employee* employeeToDelete;

		controller_ListEmployee(pArrayListEmployee);

		if(getNumero(&idToDelete,"\nIngrese el ID a ser borrado", "\nOpcion no valida", 1, (controller_getNewId(pArrayListEmployee)-1), 20)==0)
		{
			indexToDelete = controller_findIndexOfEmployeeById(pArrayListEmployee, idToDelete);
			employeeToDelete = ll_get(pArrayListEmployee, indexToDelete);

			if (indexToDelete!= -1)
			{
				showEncabezado();
				employee_showEmpleado(employeeToDelete);
					if(confirmEdit(idToDelete)==1)
					{
						ll_remove(pArrayListEmployee, indexToDelete);
						employee_delete(employeeToDelete);
					}
			retorno = 1;
			}
			else
			{
				printf("\nNo se encuentra el id en la lista de empleados\n");
			}
		}
	}
	else if(isEmpty == 1)
	{
		printf("\nEl array esta vacio, por favor carguelo desde la opcion 1 o 2\n");
	}else{
		printf("\nHubo un error al borrar un nuevo empleado\n");
	}

    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int isEmpty = ll_isEmpty(pArrayListEmployee);
	if (pArrayListEmployee != NULL && isEmpty == 0)
	{
		int i;
		int len;
		Employee* aux;
		len = ll_len(pArrayListEmployee);
		showEncabezado();
		for(i=0; i<len; i++)
		{
			aux =  ll_get(pArrayListEmployee,i);
			employee_showEmpleado(aux);
		}
		retorno = 1;
	}else if(isEmpty == 1)
	{
		printf("\nEl array esta vacio, por favor carguelo desde la opcion 1 o 2\n");
	}else{
		printf("\nHubo un error al listar un nuevo empleado\n");
	}
    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int isEmpty = ll_isEmpty(pArrayListEmployee);
	if (pArrayListEmployee != NULL && isEmpty == 0)
	{
		ll_sort(pArrayListEmployee, compareById, 0);
		retorno = 1;
	}else if(isEmpty == 1)
	{
		printf("\nEl array esta vacio, por favor carguelo desde la opcion 1 o 2\n");
	}else{
		printf("\nHubo un error al listar un nuevo empleado\n");
	}

    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int isEmpty = ll_isEmpty(pArrayListEmployee);
	if (pArrayListEmployee != NULL && path != NULL && isEmpty == 0)
	{
		int i;
		int len;
		Employee* aux;
		FILE* fpArchivo;
		int auxId;
		char auxNombre[50];
		int auxHorasTrabajadas;
		int auxSueldo;

			len = ll_len(pArrayListEmployee);
			fpArchivo = fopen(path, "w");
			if(fpArchivo != NULL)
			{

				fprintf(fpArchivo,"id,nombre,horasTrabajadas,sueldo\n");
				for(i=0; i<len; i++)
				{
					aux =  ll_get(pArrayListEmployee,i);

					if (employee_getId(aux, &auxId)&&
						employee_getNombre(aux, auxNombre)&&
						employee_getHorasTrabajadas(aux, &auxHorasTrabajadas) &&
						employee_getSueldo(aux, &auxSueldo))
					{
					fprintf(fpArchivo,"%d,%s,%d,%d\n", auxId, auxNombre, auxHorasTrabajadas, auxSueldo);
					retorno = 1;
					}
				}

			}

	}else if(isEmpty == 1)
	{
		printf("\nEl array esta vacio, por favor carguelo desde la opcion 1 o 2\n");
	}else{
		printf("\nHubo un problema al guardar en texto\n");
	}
    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int isEmpty = ll_isEmpty(pArrayListEmployee);
	if (pArrayListEmployee != NULL && path != NULL && isEmpty == 0)
	{
		int i;
		int len;
		Employee* aux;
		FILE* fpArchivo;
		len = ll_len(pArrayListEmployee);
		fpArchivo = fopen(path, "wb");

			if(fpArchivo != NULL)
			{

				for(i=0; i<len; i++)
				{
					aux =  ll_get(pArrayListEmployee,i);
					fwrite(aux,sizeof(Employee),1, fpArchivo);
					retorno = 1;

				}
			}
	}else if(isEmpty == 1)
	{
		printf("\nEl array esta vacio, por favor carguelo desde la opcion 1 o 2\n");
	}else{

		printf("\nHubo un problema al guardar en binario\n");
	}



    return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_getNewId(LinkedList* pArrayListEmployee)
{

	int newId = 0;
	if (pArrayListEmployee != NULL && ll_isEmpty(pArrayListEmployee) == 0)
	{
		Employee* aux;
		LinkedList* miListaOrdenada;

		miListaOrdenada = ll_clone(pArrayListEmployee);
		controller_sortEmployee(miListaOrdenada);
		aux = ll_get(miListaOrdenada, 0);
		newId = aux->id;
	}

	return newId+1;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_findIndexOfEmployeeById(LinkedList* pArrayListEmployee, int idToFind)
{
	int retorno = -1;
	if (pArrayListEmployee != NULL)
	{
		int i;
		int len;
		len = ll_len(pArrayListEmployee);
		Employee* localEmployee;

		for(i=0; i<len; i++)
		{
			localEmployee =  ll_get(pArrayListEmployee,i);
			if(localEmployee->id == idToFind)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int controller_showMenu ()
{
	int retorno = 0;
	int menu;
	char textoMenu [512];
	char textoError [128];

	strcpy(textoMenu,"1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
					"2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n"
		     	 	"3. Alta de empleado\n"
		     	 	"4. Modificar datos de empleado\n"
		     	 	"5. Baja de empleado\n"
					"6. Listar empleados\n"
					"7. Ordenar empleados\n"
					"8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
					"9. Guardar los datos de los empleados en el archivo data.bin (modo binario).\n"
					"10. Salir\n");
	strcpy(textoError, "Opcion no valida, por favor digite una opcion listada\n");

	if (getNumero(&menu,textoMenu, textoError, 1, 10, 20)==0)
	{
		retorno = menu;
	}

	return retorno;
}

