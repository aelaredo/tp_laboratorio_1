#include <stdio_ext.h>
#include <stdlib.h>
#include "ArrayEmployees.h"
#include "Menu.h"
#include <ctype.h>
#include <string.h>
#define MaxEmployees 1000
#include "utn_getData.h"



int main()
{
    int option;
    Employee employees[MaxEmployees];
    Employee auxEmployee;
    int arrayState;
    int idEdit;
    int editState;
    int idDelete;
    int editOption;
    int lastID;


    lastID = 0;



    if(initEmployees(employees , MaxEmployees)==0)///// formateo el array con el flag de estar vacio verdadero 1 y con el ID 0
    {


    do {
    if (getNumero (&option, "\n 1. ALTAS \n 2. MODIFICAR \n 3. BAJA \n 4. Listar Empleados, ordenarlos y promediar sueldos \n 10. Salir \n Elija una opcion: ", "\nOpcion no valida, intente nuevamente \n", 0, 10, 10)==0)
    {
        switch (option){
            case 1: ///// ALTAS
                arrayState = arrayEstado(employees, MaxEmployees); // siempre que entro a una opcion, voy a consultar como esta el array employees que me informa los espacios libres
                if(arrayState == 0) ///// si me devuelve 0 significa que esta lleno el array por lo que no puedo cargar mas empleados
                {
                    printf("\n El array esta lleno. Volviendo al menu... \n");
                } else
                {
                    auxEmployee = addOneEmployee(); //// si tengo espacio empiezo la carga esta funcion me va a permitir que el usuario cargue datos
                    lastID++;//// esta variable es unica e incremental en la ejecucion del programa.
                    auxEmployee.id = lastID; ///// estos dos datos no pueden ser ingresados por el usuario por lo que los seteo aca.
                    auxEmployee.isEmpty = 0; //// Indico que es falso que este vacio. Mi flag de ocupacion es el 0
                    employees[emptyIndex(employees, MaxEmployees)] = auxEmployee; ///// Llamo a mi funcion empty index que me da el primer lugar vaciuo en el array y ese index le asigno el empleado aux que arme

                }
                break;
            case 2: ////// MODIFICAR
                arrayState = arrayEstado(employees, MaxEmployees); ////// consulto nuevamente el estado  del array
                if (arrayState == MaxEmployees) ////// en esta ocasion necesito preguntar si el array esta vacio. arrayState tiene como valor los lugares libre. Si hay tantos espacios libres como posiciones posibles el array esta vacio y no puedo editar nada
                    {
                    printf("\n No hay empleados en la nomina.... ");
                    }else{
                        if (printEmployees ( employees , MaxEmployees)==0)
                        {
                                do
                                {
                                getNumero(&idEdit, "\nIngrese ID a editar", "La id no se encuentra dada de alta", 0, MaxEmployees, 10);
                                editState =  findEmployeeById(employees, MaxEmployees,idEdit);
                                }while ( editState == -1);

                                if((getNumero (&editOption, "\n ingrese que dato desea editar : \n 1. Para editar el nombre \n 2. Para editar el apellido \n 3. Para editar salario \n 4. Para editar el sector\n", "\nError opcion", 1, 4, 10)==0)
                                &&(editEmployee(employees, MaxEmployees, idEdit, editOption)==-1))
                                {
                                printf("\n Ocurrio un error en el proceso de borrado intente nuevamente.... ");
                                }

                        } ///// fin del if else print employees
                    } ///// fin del if else arrayState
            break;
            case 3:
                arrayState = arrayEstado(employees, MaxEmployees);
                if (arrayState == MaxEmployees) ////// en esta ocasion necesito preguntar si el array esta vacio. arrayState tiene como valor los lugares libre. Si hay tantos espacios libres como posiciones posibles el array esta vacio y no puedo editar nada
                {
                printf("\n No hay empleados en la nomina.... ");
                }else{
                    if (printEmployees ( employees , MaxEmployees)==0)
                    {
                        do{ /////// en este do trabo el programa para que solo se pueda ingresar un ID existente
                        printf("\n ingrese el ID a borrar : ");
                        scanf("%d",&idDelete);
                        }while (findEmployeeById(employees, MaxEmployees,idDelete ) == -1); ///// la funcion me devuelve -1 cuando no se encuentra el id en el array employyes

                    if (removeEmployee(employees, MaxEmployees, idDelete)==-1)
                        {
                        printf("\n Ocurrio un error en el proceso de borrado intente nuevamente.... ");
                        }
                    }///// fin del if else print employees
                }
            break;
            case 4 :
                arrayState = arrayEstado(employees, MaxEmployees);
                if (arrayState == MaxEmployees) ////// en esta ocasion necesito preguntar si el array esta vacio. arrayState tiene como valor los lugares libre. Si hay tantos espacios libres como posiciones posibles el array esta vacio y no puedo editar nada
                    {
                    printf("\n No hay empleados en la nomina.... ");
                    }else{
                        if((sortEmployees(employees, MaxEmployees)==0)  ) /////// solo si el ordenamiento me da bien, entro en la condicion para  imprimir los empleados e informar los salarios
                        {
                            printEmployees ( employees , MaxEmployees);
                            infoSalary (employees, MaxEmployees );

                        }else {
                        printf("Ocurrio un problema al ordenar el array de empleados intente nuevamente...");
                        }
                    }
            break;
            case 10:
                printf("\nSaliendo de la aplicacion.... \n");
                break;
            default:
                printf("\nOpcion no valida, intente nuevamente \n");
                break;
        } ///////// corchete de switch de menu
    }else{
        printf("\nOpcion no valida, intente nuevamente \n");
    }


    }while(option != 10);

    }
}
