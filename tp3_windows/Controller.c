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
		printf("\n Hubo un error al cargar la linked list desde texto\n");
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
	char idStr[50];
	char nombreStr[50];
	char horasTrabajadasStr[50];
	int horasTrabajadas;
	char sueldoStr[50];
	int sueldo;

	sprintf(idStr, "%d", id);

	printf("\nIngrese el nombre\n");
	fflush(stdout);
	fflush(stdin);

	if(myGets(nombreStr, 20)==0)
	{
		if (getNumero(&horasTrabajadas,"\nIngrese las horas trabajadas: ", "\nopcion no valida\n", 1, 100000, 20)==0)
		{
		sprintf(horasTrabajadasStr, "%d", horasTrabajadas);
			if (getNumero(&sueldo,"\nIngrese el sueldo: ", "\nopcion no valida\n", 1, 10000000, 20)==0)
			{
				sprintf(sueldoStr, "%d", sueldo);
				localEmployee = employee_newParametros(idStr, nombreStr , horasTrabajadasStr, sueldoStr);
				ll_add(pArrayListEmployee, localEmployee);
				retorno = 1;
			}
			else
			{
				printf("\nHubo un error al setear el sueldo\n");
			}
		}
		else
		{
			printf("\nHubo un error al setear las hrs. trabajadas\n");
		}
	}else
	{
		printf("\nHubo un error al setear el nombre\n");
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
	int menu;
	int idEditar;
	int indexToEdit;
	char idStr[50];
	char nombreStr[50];
	char horasTrabajadasStr[50];
	int horasTrabajadas;
	char sueldoStr[50];
	int sueldo;

	controller_ListEmployee(pArrayListEmployee);

	getNumero(&idEditar,"\nIngrese el ID a ser editado\n", "\nOpcion no valida\n", 1, (controller_getNewId(pArrayListEmployee)-1), 20);
	indexToEdit = controller_findIndexOfEmployeeById(pArrayListEmployee, idEditar);

	if (indexToEdit!= -1)
	{
		menu = controller_showMenuEdit();
		sprintf(idStr, "%d", idEditar);
		switch (menu)
		{
			case 1:
				printf("\nIngrese el nuevo nombre\n");
				fflush(stdout);
				fflush(stdin);
				if(myGets(nombreStr, 20)==0)
				{
				localEmployee = ll_get(pArrayListEmployee, indexToEdit);
					if(employee_getHorasTrabajadas(localEmployee,&horasTrabajadas)==1)
					{
					sprintf(horasTrabajadasStr, "%d", horasTrabajadas);
						if(employee_getSueldo(localEmployee,&sueldo)==1)
						{
							sprintf(sueldoStr, "%d", sueldo);
							localEmployee = employee_newParametros(idStr, nombreStr, horasTrabajadasStr, sueldoStr);
							ll_set(pArrayListEmployee, indexToEdit, localEmployee);
							retorno = 0;
						}
						else
						{
							printf("\nHubo un error al setear el sueldo\n");
						}
					}else
					{
					printf("\nHubo un error al setear las horas trabajadas\n");
					}
				}
				else
				{
					printf("\nHubo un error al setear el nuevo nombre\n");
				}
			break;
			case 2:
				if (getNumero(&horasTrabajadas,"\nIngrese las horas trabajadas\n", "\nopcion no valida\n", 1, 100000, 20)==0)
				{
				localEmployee = ll_get(pArrayListEmployee, indexToEdit);
				sprintf(horasTrabajadasStr, "%d", horasTrabajadas);
						if (employee_getNombre(localEmployee, nombreStr)==1)
						{
							if (employee_getSueldo(localEmployee, &sueldo)==1)
							{
								sprintf(sueldoStr, "%d", sueldo);
								localEmployee = employee_newParametros(idStr, nombreStr, horasTrabajadasStr, sueldoStr);
								ll_set(pArrayListEmployee, indexToEdit, localEmployee);
								retorno = 0;
							}
							else
							{
								printf("\nHubo un error al setear el sueldo\n");
							}
						}
						else
						{
							printf("\nHubo un error al setear el nombre\n");
						}
				}
				else
				{
					printf("\nHubo un error al setear las horas trabajadas\n");
				}
			break;
			case 3:
				if (getNumero(&sueldo,"\nIngrese el sueldo\n", "\nopcion no valida\n", 1, 10000000, 20)==0)
				{
				localEmployee = ll_get(pArrayListEmployee, indexToEdit);
				sprintf(sueldoStr, "%d", sueldo);
					if (employee_getNombre(localEmployee, nombreStr)==1)
					{
						if(employee_getHorasTrabajadas(localEmployee,&horasTrabajadas)==1)
						{
							sprintf(horasTrabajadasStr, "%d", horasTrabajadas);
							localEmployee = employee_newParametros(idStr, nombreStr, horasTrabajadasStr, sueldoStr);
							ll_set(pArrayListEmployee, indexToEdit, localEmployee);
							retorno = 0;
						}
						else
						{
							printf("\nHubo un error al setear las horas trabajadas\n");
						}
					}
					else
					{
						printf("\nHubo un error al setear el nombre\n");
					}
				}
				else
				{
					printf("\nHubo un error al setear el sueldo\n");
				}
		}
	}else
	{
	printf("\nNo se encuentra el id en la lista de empleados\n");
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

		if(getNumero(&idToDelete,"\nIngrese el ID a ser borrado\n", "\nOpcion no valida\n", 1, (controller_getNewId(pArrayListEmployee)-1), 20)==0)
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
		int menu;
		menu = controller_showMenuSort();
		switch (menu)
		{
			case 1:
				if(ll_sort(pArrayListEmployee, compareById, 1)==0)
				{
					printf("\nSe ordeno la lista exitosamente\n");
					retorno = 1;
				}
				else
				{
					printf("\nHubo un error al ordenar la lista\n");
				}
				break;
			case 2:
				if(ll_sort(pArrayListEmployee, compareById, 0)==0)
				{
					printf("\nSe ordeno la lista exitosamente\n");
					retorno = 1;
				}
				else
				{
					printf("\nHubo un error al ordenar la lista\n");
				}
				break;
			case 3:
				if (ll_sort(pArrayListEmployee, compareByNombre, 1)==0)
				{
					printf("\nSe ordeno la lista exitosamente\n");
					retorno = 1;
				}
				else
				{
					printf("\nHubo un error al ordenar la lista\n");
				}
				break;
			case 4:
				if(ll_sort(pArrayListEmployee, compareByNombre, 0)==0)
				{
					printf("\nSe ordeno la lista exitosamente\n");
					retorno = 1;
				}
				else
				{
					printf("\nHubo un error al ordenar la lista\n");
				}
				break;
		}
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
		ll_sort(miListaOrdenada, compareById, 0);
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
		int id;
		len = ll_len(pArrayListEmployee);
		Employee* localEmployee;

		for(i=0; i<len; i++)
		{
			localEmployee =  ll_get(pArrayListEmployee,i);
			if (employee_getId(localEmployee,&id)==1)
			{
				if(id == idToFind)
				{
				retorno = i;
				break;
				}
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

int controller_showMenuEdit ()
{
	int retorno = 0;
	int menu;
	char textoMenu [512];
	char textoError [128];

	strcpy(textoMenu, "\nElija que desea editar\n1.Editar Nombre\n2.Editar Horas Trabajadas\n3.Editar Sueldo\n");

	strcpy(textoError, "Opcion no valida, por favor digite una opcion listada\n");

	fflush(stdout);
	fflush(stdin);

	if (getNumero(&menu,textoMenu, textoError, 1, 3, 20)==0)
		{
			retorno = menu;
		}

	return retorno;
}

int controller_showMenuSort ()
{
	int retorno = 0;
	int menu;
	int menu2;
	char textoMenuSort [512];
	char textoError [128];
	char textoMenuSort2 [512];

	strcpy(textoMenuSort, "\nElija criterio a ordenar \n1.Ordenar por ID\n2.Ordenar por nombre\n");

	strcpy(textoMenuSort2, "\nElija orden \n1.Ascendente\n2.Descendente\n");

	strcpy(textoError, "Opcion no valida, por favor digite una opcion listada\n");

	fflush(stdout);
	fflush(stdin);

	if (getNumero(&menu,textoMenuSort, textoError, 1, 2, 20)==0)
	{
		retorno = menu;
	}

	switch(menu)
	{
	case 1:
		if (getNumero(&menu2,textoMenuSort2, textoError, 1, 2, 20)==0)
				{
					if (menu2 == 1)
					{
						retorno = 1;
					}
					else
					{
						retorno = 2;
					}
				}
		break;
	case 2:
		if (getNumero(&menu2,textoMenuSort2, textoError, 1, 2, 20)==0)
				{
					if (menu2 == 1)
					{
						retorno = 3;
					}
					else
					{
					    retorno = 4;
					}
				}
		break;
	}

	return retorno;
}

