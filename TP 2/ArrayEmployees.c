#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayEmployees.h"
#include "utn_getData.h"


int initEmployees (Employee employees[], int leng) //////esta funcion debe ejecutarse solo cuando se inicializa el programa una vez
{
    int retorno = -1;
    int i;
    if (employees !=  NULL && leng > 0){


    for(i=0;i<leng;i++)
    {
        employees[i].isEmpty = 1; ////// pongo a todos los espacios con verdadero a la pregunta estaVacio
        employees[i].id = 0; ///// pongo el valor de ID 0 que no existe
    }
    retorno = 0;
    }

    return retorno;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int emptyIndex (Employee employees[], int leng)
{
    int i;
    int index = -1;

    for (i=0; i<leng;i++)
    {
        if (employees[i].isEmpty == 1) //////// cuando encontramos un lugar vacio, cortamos la iteracion
        {
            index = i;
            break;
        }
    }
/*
    if (i == leng)  ///// si llegamos al final del array porq nunca entramos al break, cargamos con -1 que indica que esta lleno
    {
        index = -1;
    }
*/
    return index; ///// la i va a hacer el dato que nos vuelva, en el caso de ser un espacio vacio o en el caso de estar todo lleno el array va a ser igual que el leng

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Employee addOneEmployee() ///// esta funcion me carga las estructuras de un empleado solo
{
    Employee localEmployee;
    char auxName[50];
    char auxLastName[50];
    float auxSalary;
    int auxSector;


    printf("\nIngrese nombre: \n");

    __fpurge(stdin);
    if((myGets(auxName, 50)==0) && (PrimeraLetraUpper(auxName) == 0))
    {
        strncpy(localEmployee.name, auxName, 50);
    }else{
        printf("\nHubo un error en la carga del nombre,  intente nuevamente \n");
    }

    printf("\nIngrese apellido: \n");

    __fpurge(stdin);
    if((myGets(auxLastName, 50)==0) && (PrimeraLetraUpper(auxLastName) == 0))
    {
        strncpy(localEmployee.lastName, auxLastName, 50);
    }else{
        printf("\nHubo un error en la carga del apellido,  intente nuevamente \n");
    }


    if (getNumeroFlotante (&auxSalary, "\nIngrese el salario del empleado: \n", "\nError salario no valido", 0, 10000000, 5)==0)
    {
        localEmployee.salary = auxSalary;
    }else{
        printf("\nHubo un error en la carga del salario,  intente nuevamente \n");
    }


    if (getNumero (&auxSector, "\nIngrese el sector del empleado: \n", "\nError sector no valido", 0, 1000, 5)==0)
    {
        localEmployee.sector = auxSector;
    }else{
        printf("\nHubo un error en la carga del sector, intente nuevamente \n");
    }



    return localEmployee;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int arrayEstado (Employee employees[], int leng)
{
    int i;
    int employeeCounter;
    int arrayState;

    employeeCounter = 0;
    if(employees != NULL && leng >0){
    for (i=0; i<leng;i++)
    {
        if (employees[i].isEmpty == 0) ///// si isEmpty es 0 significa que cargue un empleado en ese lugar
        {
        employeeCounter++; ///// aca cuento cuantos empleados tengo en el array
        }
    }

    arrayState = leng - employeeCounter; //// resto el largo del array con la cantidad de empleados que tengo. La variable arrayState tendra ahora los lugares vacios

    /////// [si (arrayState == 0) => array esta lleno], [si array state  ==  largo del array] => array esta vacio
    } else {
    arrayState = -1;
    }
    return arrayState;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int findEmployeeById(Employee employees [], int leng , int searchID)
{
    int retorno;
    int i;

    for(i=0;i<leng;i++) ///// recorro el array
    {
        if (employees[i].id == searchID && employees[i].isEmpty == 0) ///// pregunto si el ID es el mismo que se paso por parametro y si es un empleado activo
        {
            retorno = i;
            break; ///// si es asi corto la iteracion y devuelvo el valor de i en esta instante
        }
    }

    if(i==leng) //// si recorri toda la iteracion sin encontrarlo
    {
        retorno = -1; ////// devuelvo un -1
        printf("La id %d no se encuentra dada de alta", searchID);
    }

    return retorno;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int editEmployee (Employee employees[], int leng , int idEdit, int option )
{
    int retorno = -1;
    int indexToEdit;
    int stateConfirm;
    char newName [51];
    char newLastName [51];
    float newSalary;
    int newSector;

    if(employees != NULL && leng >0)
    {

        switch (option) /////// hago un switch a partir de la opcion que me pasaron por parametro
        {

            case 1: //// caso 1 es para modificar el nombre

                indexToEdit = findEmployeeById(employees, leng, idEdit); // guardo en una variable el la posicion en array que esta el id a modificar
                if (indexToEdit != -1){
                printf("\n Usted esta a punto de modificar el apellido del siguiente empleado: \n");
                printOneEmployee (employees[indexToEdit]);

                printf("\nIngrese el nuevo nombre: \n");

                __fpurge(stdin);

                    if((myGets(newName, 50)==0)&& (PrimeraLetraUpper(newName) == 0)) //// llamo a mi funcion de entrada de datos. Si da bien la operacion pido confirmacion
                    {
                    stateConfirm = confirmEdit(idEdit); //// pido una confirmacion y la guardo en una variabla para evaluarla despues
                    }else{
                    printf("\nHubo un error en la carga del nombre,  intente nuevamente \n");
                    }

                    if (stateConfirm == 1){
                    strncpy (employees[indexToEdit].name, newName, 50);////// copio datos (newName) en el lugar a reemplazar
                    printf("\n El ID %d, se ha editado con exito\n", idEdit);
                    break;
                    }else{////// si confirmEdit me devuelve otra cosa quiere decir que se cancela la edicion.
                    printf("\n Accion cancelada, volviendo al menu \n");

                    break; //// hago un break y vuelvo al menu
                }
                }else{
                printf("ID No encontrado");

                }
        break;

        case 2 : // caso 2 es para editar apellido la logica es identica a lo anterior

                indexToEdit = findEmployeeById(employees, leng, idEdit);
                printf("\n Usted esta a punto de modificar el apellido del siguiente empleado: \n");
                printOneEmployee (employees[indexToEdit]);

                printf("\nIngrese el nuevo apellido: \n");
                __fpurge(stdin);

                if((myGets(newLastName, 50)==0) && (PrimeraLetraUpper(newLastName) == 0)) //// llamo a mi funcion de entrada de datos. Si da bien la operacion pido confirmacion
                {
                    stateConfirm = confirmEdit(idEdit); //// pido una confirmacion y la guardo en una variabla para evaluarla despues
                }else{
                printf("\nHubo un error en la carga del apellido,  intente nuevamente \n");
                }

                if (stateConfirm == 1){
                    strncpy (employees[indexToEdit].lastName, newLastName, 50);////// copio datos (newName) en el lugar a reemplazar
                    printf("\n El ID %d, se ha editado con exito\n", idEdit);
                    break;
                }else////// si confirmEdit me devuelve otra cosa quiere decir que se cancela la edicion.
                {
                    printf("\n Accion cancelada, volviendo al menu \n");
                    break; //// hago un break y vuelvo al menu
                }
        break;

        case 3 : //// caso 3 modifica el salario
                indexToEdit = findEmployeeById(employees, leng, idEdit);
                printf("\n Usted esta a punto de modificar el salario del siguiente empleado: \n");
                printOneEmployee (employees[indexToEdit]);

                __fpurge(stdin);
                if(getNumeroFlotante (&newSalary, "\nIngrese el nuevo salario del empleado: \n", "\nError salario no valido", 0, 10000000, 5)==0) //// llamo a mi funcion de entrada de datos. Si da bien la operacion pido confirmacion
                {

                    stateConfirm = confirmEdit(idEdit); //// pido una confirmacion y la guardo en una variabla para evaluarla despues
                }else{
                printf("\nHubo un error en la carga del salario,  intente nuevamente \n");
                }

                if (stateConfirm == 1){
                    employees[indexToEdit].salary = newSalary ;////// copio datos (newName) en el lugar a reemplazar
                    printf("\n El ID %d, se ha editado con exito\n", idEdit);
                    break;
                }else////// si confirmEdit me devuelve otra cosa quiere decir que se cancela la edicion.
                {
                    printf("\n Accion cancelada, volviendo al menu \n");
                    break; //// hago un break y vuelvo al menu
                }



        break;

        case 4: //// caso 4 modifica el sector

                indexToEdit = findEmployeeById(employees, leng, idEdit);
                printf("\n Usted esta a punto de modificar el sector del siguiente empleado: \n");
                printOneEmployee (employees[indexToEdit]);

                __fpurge(stdin);
              if(getNumero (&newSector, "\nIngrese el nuevo sector del empleado: \n", "\nError sector no valido", 0, 1000, 5)==0) //// llamo a mi funcion de entrada de datos. Si da bien la operacion pido confirmacion
                {
                    stateConfirm = confirmEdit(idEdit); //// pido una confirmacion y la guardo en una variabla para evaluarla despues
                }else{
                printf("\nHubo un error en la carga del sector,  intente nuevamente \n");
                }

                if (stateConfirm == 1){
                    employees[indexToEdit].sector = newSector ;////// copio datos (newName) en el lugar a reemplazar
                    printf("\n El ID %d, se ha editado con exito\n", idEdit);
                    break;
                }else////// si confirmEdit me devuelve otra cosa quiere decir que se cancela la edicion.
                {
                    printf("\n Accion cancelada, volviendo al menu \n");
                    break; //// hago un break y vuelvo al menu
                }


        break;
    }/////// fin de switch de opcion
    retorno = 0;
}/////// fin del if else

return retorno;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int removeEmployee (Employee employees [], int leng , int deleteID)
{
     int indexToRemove;
     int retorno = -1;

if(employees != NULL && leng >0)
    {

            indexToRemove = findEmployeeById(employees, leng, deleteID);

            printf("\n Usted esta a punto de eliminar el siguiente empleado: \n");
            printOneEmployee (employees[indexToRemove]);
            //////printf("\n El siguiente id %d sera removido  \n", deleteID);

                if (confirmEdit(deleteID) == 1)
                {
                    employees[indexToRemove].isEmpty = 1;
                    printf("\n El ID %d, se ha editado con exito\n", deleteID);

                } else
                {
                printf("\n Accion cancelada, volviendo al menu \n");

                }
                retorno = 0;
    }
return  retorno;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int confirmEdit(int editID)
{
    int confirmEdit;
    int confirmState = -1;

    do{
        printf("\n Reingrese el ID a modificar para confirmar la accion. Ingrese 0 para volver al menu \n");
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int getNewID (int lastID )
{
    int newID;

    newID = lastID++;

    return newID;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void printOneEmployee (Employee localEmployee)
{
    printf("\n ID Empleado   Nombre     Apellido   Sueldo     Sector ");
    printf("\n %-12d  %-10s %-10s %-10.2f %-10d ",localEmployee.id, localEmployee.name, localEmployee.lastName, localEmployee.salary, localEmployee.sector);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int printEmployees (Employee employees [] ,int leng)
{
    int retorno = -1;
    int i;
  if(employees != NULL && leng >0)
  {
    printf("\n ID Empleado   Nombre     Apellido   Sueldo     Sector ");

    for (i=0; i<leng;i++)
    {
        if (employees[i].isEmpty == 0)
        {
        printf("\n %-12d  %-10s %-10s %-10.2f %-10d ",employees[i].id, employees[i].name, employees[i].lastName, employees[i].salary, employees[i].sector);
        }
    }
    retorno = 0;
  }
  return retorno;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int infoSalary (Employee employees [], int leng)
{
    int i;
    int retorno = -1;
    float totalSalaries;
    int employeeCounter;
    float averageSalary;
    int employeeAboveAverage;

    totalSalaries = 0;
    employeeCounter = 0;
    employeeAboveAverage = 0;

if(employees != NULL && leng >0)
{


    for (i=0; i<leng;i++) //// recorro el array para extraer info
    {
            if (employees[i].isEmpty == 0){ //////si estan ocupados los lugares
            totalSalaries += employees[i].salary; /////// acumulo el salario en la variable totalSalaries
            employeeCounter++; ////// cuento la cantidad para luego sacar el promedio
        }
    }

    averageSalary = totalSalaries / employeeCounter; //////// calculo el promedio

    for (i=0; i<leng;i++) //////// recorro nuevamente el array
    {
        if (employees[i].isEmpty == 0 && employees[i].salary > averageSalary) //////// pregunto si esta ocupado y si tiene un salario mayor al premios
        {
            employeeAboveAverage++; //////// si el empleado supera el promedio lo cuento en la variable
        }

    }

    printf("\n El total de todos los sueldos es :%f \n El promedio de los salarios es: %f \n Hay %d empleados que tienen un sueldo mayor al promedio. \n", totalSalaries, averageSalary, employeeAboveAverage);
    retorno = 0;
}

return retorno;

}


int sortEmployees (Employee employees [], int leng)
{
    int retorno = -1;
    int flagSwap;
    int i;
    Employee auxEmployee;
    int nuevoLimite;

    nuevoLimite = leng-1; //// asigno el limite de mi iteracion para ordenar
if(employees != NULL && leng >0)
{
    do
    {
        flagSwap=0; ////// seteo para que salga del do while
        for(i=0;i<nuevoLimite;i++)
        {
            if(strcmp(employees[i].lastName, employees[i+1].lastName)> 0)
            {
                flagSwap = 1;
                auxEmployee = employees[i];
                employees[i] = employees[i+1];
                employees[i+1] = auxEmployee;
            }

            if(strcmp(employees[i].lastName, employees[i+1].lastName)== 0)
            {
                if (employees[i].sector<employees[i+1].sector)
                {
                flagSwap = 1;
                auxEmployee = employees[i];
                employees[i] = employees[i+1];
                employees[i+1] = auxEmployee;
                flagSwap = 1;
                }

            }
        }
        nuevoLimite--;
    }while (flagSwap);

retorno = 0;
}

return retorno;
}

int PrimeraLetraUpper  (char* data )
{
    int retorno = -1;
    int i;
    int leng;
    leng = strlen(data);

    if (data != NULL)
    {

        data[0] = toupper(data[0]);
        retorno = 0;
    }
    return retorno;
}



