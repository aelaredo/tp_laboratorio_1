#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "validaciones.h"

void employee_delete(Employee* this)
{
    if(this!=NULL)
    {
    		free(this);
    	}



}

Employee* employee_new(){

	Employee* localEmployee;

	localEmployee = (Employee*) malloc(sizeof(Employee));

	return localEmployee;
}

Employee* employee_newParametros(char idStr[],char nombreStr[],char horasTrabajadasStr[], char sueldoStr[]){

	Employee* retornoEmployee;
	if(idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL)
	{
		Employee* localEmployee;

		int id;
		id = atoi(idStr);
		int horasTrabajadas;
		horasTrabajadas = atoi(horasTrabajadasStr);
		int sueldo;
		sueldo = atoi(sueldoStr);

		localEmployee = employee_new();
		if(!(setNewEmployee(localEmployee, id, nombreStr , horasTrabajadas, sueldo))){
			free(localEmployee);
			retornoEmployee = NULL;
		}else{
			retornoEmployee = localEmployee;

		}
	}

	return retornoEmployee;
}


int setNewEmployee (Employee* employeeACargar, int id,char* nombre,int horasTrabajadas, int sueldo){

	int retorno = 0;
	int comprobacion = 0;

	comprobacion += employee_setId(employeeACargar, id);
	comprobacion += employee_setNombre(employeeACargar, nombre);
	comprobacion += employee_setHorasTrabajadas(employeeACargar, horasTrabajadas);
	comprobacion += employee_setSueldo(employeeACargar, sueldo);

		if (comprobacion == 4)
		{
			retorno = 1;
		}

return retorno;
}


int employee_setId(Employee* this,int id){

	int setter = 0;

	if (this != NULL && id > 0)
	{
		this->id = id;
		setter = 1;
	}

	return setter;
}

int employee_getId(Employee* this,int* id){
	int getter = 0;

	if (this != NULL && id > 0)
	{
		*id = this->id;
		getter = 1;
	}

	return getter;
}

int employee_setNombre(Employee* this,char* nombre){

	int setter = 0;

	if (this != NULL && nombre != NULL)
	{
		strcpy(this->nombre, nombre);
		setter = 1;
	}

	return setter;

}

int employee_getNombre(Employee* this,char* nombre){
	int getter = 0;

	if (this != NULL && nombre != NULL){

		strcpy(nombre, this->nombre);
		getter = 1;
	}
	return getter;
}


int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas){
	int setter = 0;

	if (this != NULL && horasTrabajadas > 0){
		this->horasTrabajadas = horasTrabajadas;
		setter = 1;
		}
	return setter;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas){
	int getter = 0;

	if (this != NULL && horasTrabajadas > 0)
	{
		*horasTrabajadas = this->horasTrabajadas;
		getter = 1;
	}

	return getter;
}

int employee_setSueldo(Employee* this,int sueldo){
	int setter = 0;

	if (this != NULL && sueldo > 0)
	{
		this->sueldo = sueldo;
		setter = 1;
	}

	return setter;
}


int employee_getSueldo(Employee* this,int* sueldo){
	int getter = 0;

	if (this != NULL && sueldo > 0)
	{
		*sueldo = this->sueldo;
		getter = 1;
	}

	return getter;
}

int employee_showEmpleado(Employee* this)
{

	printf(" %4d|| %13s|| %13d|| %10d||\n",  this->id, this->nombre, this->horasTrabajadas, this->sueldo);
	return 0;
}


int compareByWorkedHours (void* uno, void* dos){

	int retorno=0;

	Employee* empleadoUno = (Employee*) uno;

	Employee* empleadoDos = (Employee*) dos;

	if (empleadoUno->id > empleadoDos->id)
	{
	retorno = 1;
	}else if(empleadoUno->id < empleadoDos->id){
	retorno = -1;
	}

	return retorno;
}

void showEncabezado(){

	printf("   ID||        Nombre||Hrs Trabajadas||     Sueldo||\n");
}






