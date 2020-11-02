#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pLinkedListEmployee)
{
	int retorno = 0;
	if (pFile != NULL && pLinkedListEmployee != NULL)
	{
	Employee* localEmployee;
	char auxIdStr [128];
	char auxHorasTrabajadasStr[128];
	char auxSueldoStr[128];
	char auxNombreStr [128];

	while(!feof(pFile))
	{
		if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxIdStr,auxNombreStr, auxHorasTrabajadasStr,auxSueldoStr )==4)
		{
				localEmployee = employee_newParametros(auxIdStr,auxNombreStr,auxHorasTrabajadasStr, auxSueldoStr);
				if (localEmployee != NULL)
				{
					ll_add(pLinkedListEmployee, localEmployee);
				}
		}
	}
	fclose(pFile);
	}

    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{

	int retorno = 0;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{

		Employee* localEmployee;

		while(!feof(pFile))
		{
			localEmployee = employee_new();
			fread(localEmployee,sizeof(Employee), 1, pFile);

					if (feof(pFile))
					{
						break;
			    	}

					if (localEmployee != NULL)
					{
						ll_add(pArrayListEmployee, localEmployee);
					}

		}

			fclose(pFile);
	}

    return retorno;
}
