/*===================================
 * RECUPERATORIO PRIMER PARCIAL
 * MONTENEGRO FERNANDO THOMAS DIV C
 * ==================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Funciones.h"
#include "Inputs.h"


int main(void)
{
	setbuf(stdout, NULL);

	sConsultas listaPacientes[TAM_PACIENTES] = {{obtenerID(),"Fernando",{19,3,2020},3,1,1,1,2},
												{obtenerID(),"German",{12,12,2021},1,1,2,2,3},
												{obtenerID(),"Marta",{1,2,2023},2,1,2,3,1},
												{obtenerID(),"Roberto",{28,5,2023},4,1,3,3,1},
												{obtenerID(),"Tomas",{18,6,2021},5,1,2,2,5},
												{obtenerID(),"Jonathan",{23,7,2021},4,1,3,3,4},
												{obtenerID(),"Martin",{11,7,2023},2,1,1,1,2},
												{obtenerID(),"Taiel",{4,6,2021},3,1,2,3,3}};

	sMedico listaMedicos[TAM_MEDICOS] = {{1, "Dr. Rodriguez", 1},{2,"Dr. Osvaldo", 3},{3,"Dr. Perez", 1},{4,"Dr. Torres", 2},{5,"Dr. Domingo", 2}};

	sDiagnostico listaDiagnosticos[TAM_DIAGNOSTICO]={{0,"No Diagnosticado"},{1,"Covid-19"},{2,"Gripe A"},{3,"Pre infarto"}};

	sEspecialidadMedico listaEspecialidad[TAM_ESPECIALIDAD] = {{1,"Cardiologia"},{2,"Dermatologia"},{3,"Odontologia"}};

	sClinica listaClinicas[TAM_CLINICAS] = {{1,"Clinica Estrada"},{2,"Clinica Banfield"},{3,"Clinica Boedo"},{4,"Clinica 2 De Abril"}};

	sUrgencia listaUrgencias[TAM_URGENCIAS] = {{1,"Nivel I"},{2,"Nivel II"},{3,"Nivel III"},{4,"Nivel IV"},{5,"Nivel V"}};


	init_Pacientes_Empty_For_Hardcode(listaPacientes, TAM_PACIENTES, listaEspecialidad, listaMedicos);

	int opcion;
	int banderaAlta;
	int rtnEdit;
	int rtnRemove;
	int rtnAdd;
	int rtnDiagnostico;

	banderaAlta=0;

	do
	{
		opcion = menu();

		switch(opcion)
		{
		case 1:
			rtnAdd = add_One_Patient_On_List(listaPacientes, TAM_PACIENTES, listaMedicos, listaEspecialidad, listaClinicas, listaUrgencias);
			if(rtnAdd == 0)
			{
				printf("\nConsulta agregada con exito...\n\n");
				banderaAlta = 1;
			}
			else
			{
				printf("\nNo hay lugar para agregar la consulta...\n\n");
			}
			break;
		case 2:
			rtnEdit = edit_Patient(listaPacientes, TAM_PACIENTES, listaMedicos, listaEspecialidad, listaDiagnosticos, listaClinicas, listaUrgencias);
			if(rtnEdit == 0)
			{
				printf("\nConsulta modificada exitosamente...\n\n");
			}
			else
			{
				if(rtnEdit == 1)
				{
					printf("\nModificacion cancelada...\n\n");
				}
				else
				{
					printf("\nNo hay consultas para modificar...\n\n");
				}
			}
			break;
		case 3:
			rtnRemove = remove_One_Patient(listaPacientes, TAM_PACIENTES, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
			if(rtnRemove == 0)
			{
				printf("\nConsulta dada de baja exitosamente...\n\n");
			}
			else
			{
				if(rtnRemove == 1)
				{
					printf("\nDada de baja cancelada...\n\n");
				}
				else
				{
					printf("\nNo hay consultas para dar de baja...\n\n");
				}
			}
			break;
		case 4:
			rtnDiagnostico = diagnose_One(listaPacientes, TAM_PACIENTES, listaMedicos, listaDiagnosticos, listaEspecialidad);
			if(rtnDiagnostico == 0)
			{
				printf("\nDiagnostico agregado a la consulta exitosamente...\n\n");
			}
			else
			{
				if(rtnDiagnostico == -1)
				{
					printf("\nHubo un problema para diagnosticar la consulta.\n\n");
				}
			}
			break;
		case 5:
			if(banderaAlta==1)
			{
				printMenuListado(listaPacientes, TAM_PACIENTES, listaMedicos, listaEspecialidad, listaDiagnosticos, listaClinicas, listaUrgencias);
			}
			else
			{
				printf("\nTodavia no se ingreso ningun paciente.\n\n");
			}
			break;
		case 6:
			printf("\n\n=====================================\n");
			printf("Programa finalizado con exito...\n");
			printf("=====================================\n");
			break;
		}

	}while(opcion != 6);

	return 0;
}
