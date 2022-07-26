#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Funciones.h"
#include "Inputs.h"

int obtenerID(void)
{
	static int idIncremental = 1000;
	return idIncremental++;
}

void init_Pacientes_Empty_For_Hardcode(sConsultas listaPacientes[], int sizePacientes, sEspecialidadMedico listaEspecialidad[], sMedico listaMedicos[])
{
	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado == LLENO)
		{
			find_specialty(listaPacientes[i], &listaPacientes[i].idEspecialidad, listaEspecialidad, listaMedicos);
		}
	}
}

sConsultas add_One_Patient(sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sMedico listaMedicos[], sUrgencia listaUrgencias[])
{
	sConsultas unPaciente;

	utn_getNombre(unPaciente.nombrePaciente, 50, "\nIngrese su nombre para la consulta: \n", "Nombre incorrecto...\n", 5);
	strlwr(unPaciente.nombrePaciente);
	unPaciente.nombrePaciente[0] = toupper(unPaciente.nombrePaciente[0]);

	printf("\nIngrese la fecha de atencion: \n");
	utn_getNumero(&unPaciente.fechaConsulta.dia, "Dia: ", "No es un dia valido.\n", 1, 31, 5);
	utn_getNumero(&unPaciente.fechaConsulta.mes, "Mes: ", "No es un mes valido.\n", 1, 12, 5);
	utn_getNumero(&unPaciente.fechaConsulta.anio, "Año: ", "No es un año valido (2022-2030).\n", 2015, 2030, 5);

	printClinica(listaClinicas);
	utn_getNumero(&unPaciente.idClinica, "\nIngrese el ID de la clinica que desee: ", "\nError... esa no es una opcion.\n", 1, 4, 5);

	printDoctors(listaMedicos, listaEspecialidad);
	utn_getNumero(&unPaciente.idMedico, "Ingrese el ID del medico que desee: ", "\nError... esa no es una opcion.\n", 1, 5, 5);

	printf("Elija un nivel de urgencia.\nSiendo el Nivel I el MAS urgente y el Nivel V el MENOS urgente\n");
	printUrgencias(listaUrgencias);
	utn_getNumero(&unPaciente.idUrgencia, "\nIngrese el nivel de la urgencia que tenga: ", "\nError... esa no es una opcion.\n", 1, 5, 5);

	find_specialty(unPaciente,&unPaciente.idEspecialidad, listaEspecialidad, listaMedicos);

	return unPaciente;
}
void find_specialty(sConsultas unPaciente ,int* idEspecialidad, sEspecialidadMedico listaEspecialidad[], sMedico listaMedicos[])
{
	int indexEspecialidad;

	findMedico(unPaciente, &indexEspecialidad, listaMedicos, listaEspecialidad);

	*idEspecialidad = listaEspecialidad[indexEspecialidad].idEspecialidad;
}
int find_Index_Free(sConsultas lista[], int size)
{
	int index;
	index=-1;
	for(int i=0; i<size; i++)
	{
		if(lista[i].estado==VACIO)
		{
			index=i;
			break;
		}
	}

	return index;
}
int add_One_Patient_On_List(sConsultas lista[], int size, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int index;
	sConsultas auxiliar;
	int retorno = -1;

	index = find_Index_Free(lista, size);

	if(index != -1)
	{
		auxiliar = add_One_Patient(listaEspecialidad, listaClinicas, listaMedicos, listaUrgencias);

		auxiliar.idPaciente = obtenerID();

		printf("\nEl ID de su consulta es: %d\n", auxiliar.idPaciente);

		auxiliar.estado = LLENO;
		auxiliar.idDiagnostico = NO_DIAGNOSTICADO;

		lista[index] = auxiliar;

		retorno = 0;
	}

	return retorno;
}
void printClinica(sClinica listaClinicas[])
{
	printf("\n");
	for(int i=0;i<TAM_CLINICAS;i++)
	{
		printf("%d. %s.\n",listaClinicas[i].idClinica, listaClinicas[i].descripcion);
	}
}
void printUrgencias(sUrgencia listaUrgencias[])
{
	printf("\n");
	for(int i=0;i<TAM_URGENCIAS;i++)
	{
		printf("%d. %s.\n",listaUrgencias[i].idUrgencia, listaUrgencias[i].descripcion);
	}
}
int printDoctors(sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[])
{
	int indexEspecialidad;
	int retorno = -1;

	printf("==============================\n");
	for(int i=0;i<5;i++)
	{
		indexEspecialidad = findEspecialidad(listaMedicos[i], listaEspecialidad);

		printf("%d. %s, %s\n",listaMedicos[i].idMedico,
							listaMedicos[i].nombreMedico,
							listaEspecialidad[indexEspecialidad].descripcion);
		retorno = 0;
	}
	printf("==============================\n");

	return retorno;
}
int findEspecialidad(sMedico unMedico, sEspecialidadMedico listaEspecialidad[])
{
	int index;

	for(int i=0; i<TAM_ESPECIALIDAD; i++)
	{
		if(unMedico.idEspecialidad == listaEspecialidad[i].idEspecialidad)
		{
			index=i;
			break;
		}
	}

	return index;
}
int print_Full_Queries(sConsultas listaPacientes[],int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int retorno = 0;
	int contador = 0;

	printf("|%-5s |%-10s |%-12s | %-15s | %-15s | %-20s | %-20s| %-10s|\n", "ID", "Nombre",
													"Fecha", "Medico",
													"Especialidad","Diagnostico",
													"Clinica", "Urgencia");
	printf("=======|===========|=============|=================|=================|======================|=====================|===========|\n");

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==LLENO)
		{
			print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
			contador++;
		}
	}
	if(contador > 0)
	{
		retorno = 1;
	}
	printf("===============================================================================================================================\n");
	return retorno;
}
int findMedico(sConsultas unPaciente,int* indexEspecialidad, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[])
{
	int index;
	index=-1;

	for(int i=0; i<TAM_MEDICOS; i++)
	{
		if(unPaciente.idMedico == listaMedicos[i].idMedico)
		{
			*indexEspecialidad = findEspecialidad(listaMedicos[i], listaEspecialidad);
			index=i;
			break;
		}
	}

	return index;
}
void print_One_Patient(sConsultas unPaciente, sMedico medico, sDiagnostico diagnostico, sEspecialidadMedico especialidad, sClinica clinica, sUrgencia urgencia)//Recibo como parametro la lista de pacientes en una posicion de array y el medico en la posicion donde los id coinciden.
{
	printf("|%-5d |%-10s |%2d/%2d/%-6d | %-15s | %-15s | %-20s | %-20s| %-10s|\n", unPaciente.idPaciente, unPaciente.nombrePaciente,
												unPaciente.fechaConsulta.dia, unPaciente.fechaConsulta.mes,
												unPaciente.fechaConsulta.anio, medico.nombreMedico,
												especialidad.descripcion,diagnostico.descripcion,
												clinica.descripcion, urgencia.descripcion);//Muestro los datos.
}
sConsultas edit_One_Patient(sConsultas listaPacientes,int sizePacientes, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[])
{
	int opcion;
	sConsultas auxiliar = listaPacientes;

	do
	{
		printf("Ingrese lo que desee modificar.\n");
		printf("1. Nombre del paciente.\n");
		printf("2. Medico asignado.\n");
		printf("3. Fecha ingresada.\n");
		printf("4. Volver.\n");
		scanf("%d", &opcion);

		switch(opcion)
		{
			case 1:
				utn_getNombre(auxiliar.nombrePaciente, 50, "Ingrese su nombre para la consulta: \n", "Nombre incorrecto...\n", 5);//Pido nuevo nombre y lo guardo en un auxiliar.
				strlwr(auxiliar.nombrePaciente);
				auxiliar.nombrePaciente[0] = toupper(auxiliar.nombrePaciente[0]);
				printf("Nuevo nombre modificado con exito.\n");
			break;

			case 2:
				printDoctors(listaMedicos, listaEspecialidad);
				utn_getNumero(&auxiliar.idMedico, "Ingrese el medico que lo va a atender.\n", "ERROR...\n", 1, 5, 5);
				printf("\nNuevo medico modificado con exito.\n");
			break;

			case 3:
				printf("Ingrese la fecha de atencion: \n");
				utn_getNumero(&auxiliar.fechaConsulta.dia, "Dia: ", "No es un dia valido.\n", 1, 31, 5);
				utn_getNumero(&auxiliar.fechaConsulta.mes, "Mes: ", "No es un mes valido.\n", 1, 12, 5);
				utn_getNumero(&auxiliar.fechaConsulta.anio, "Año: ", "No es un año valido (2022-2030).\n", 2022, 2030, 5);
				printf("\nNueva fecha modificado con exito.\n");
			break;
			case 4:
				printf("Volviendo....\n");
			break;

			default:
				printf("\n ERROR: Opcion incorrecta.\n");
			break;
		}

	}while(opcion!=4);

	return auxiliar;
}
int edit_Patient(sConsultas listaPacientes[] ,int sizePacientes, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sDiagnostico listaDiagnosticos[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int index;
	int verificacion;
	sConsultas auxiliar;
	int retorno = -1;
	int rtnPrint;
	int idEdit;

	rtnPrint = print_Full_Queries(listaPacientes, sizePacientes, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
	if(rtnPrint == 1)
	{
		utn_getNumero(&idEdit, "Ingrese un ID de la lista para modificar: ", "\nEse ID no existe.\n", 0, 1000000, 5);
		index = find_Patient_By_ID(listaPacientes, sizePacientes, idEdit);

		while(index == -1)
		{
			printf("Ese ID no existe.\n");
			utn_getNumero(&idEdit, "Ingrese un ID de la lista para modificar: ", "\nEse ID no existe.\n", 0, 1000000, 5);
			index = find_Patient_By_ID(listaPacientes, sizePacientes, idEdit);
		}

		utn_getNumero(&verificacion, "\n¿Está seguro que desea modificar este pasajero?\n1. Si\n2. No\n", "Opcion invalida...\n", 1, 2, 5);

		if(verificacion == 1)
		{
			auxiliar = edit_One_Patient(listaPacientes[index], sizePacientes, listaMedicos, listaEspecialidad);
			listaPacientes[index] = auxiliar;
			retorno = 0;
		}
		else
		{
			retorno = 1;
		}
	}

	return retorno;
}
int find_Patient_By_ID(sConsultas listaPacientes[], int sizePacientes, int idIngresado)
{
	int index;

	index=-1;

	for(int i=0; i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==LLENO && listaPacientes[i].idPaciente==idIngresado)
		{
			index=i;
			break;
		}
	}
	return index;
}
int removePatient(sConsultas lista[], int len, int idAux)
{
	int retorno = -1;

	for(int i = 0; i < len; i++)
	{
		if(lista[i].estado == LLENO && lista[i].idPaciente == idAux)
		{
			lista[i].estado = VACIO;
			retorno = 0;
			break;
		}
	}

	return retorno;
}
int remove_One_Patient(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int indexPaciente;
	int retorno = -1;
	int verificacion;
	int rtnPrint;
	int idRemove;

	rtnPrint = print_Full_Queries(listaPacientes, sizePacientes, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
	if(rtnPrint == 1)
	{
		utn_getNumero(&idRemove, "Ingrese un ID de la lista para eliminar: ", "\nEse ID no existe.\n", 0, 1000000, 5);
		indexPaciente = find_Patient_By_ID(listaPacientes, sizePacientes, idRemove);

		while(indexPaciente == -1)
		{
			printf("Ese ID no existe.\n");
			utn_getNumero(&idRemove, "Ingrese un ID de la lista para eliminar: ", "\nEse ID no existe.\n", 0, 1000000, 5);
			indexPaciente = find_Patient_By_ID(listaPacientes, sizePacientes, idRemove);
		}

		utn_getNumero(&verificacion, "\n¿Está seguro que desea eliminar este pasajero?\n1. Si\n2. No\n", "Opcion invalida...\n", 1, 2, 5);
		if(verificacion == 1)
		{
			removePatient(listaPacientes, sizePacientes, idRemove);
			retorno = 0;
		}
		else
		{
			retorno = 1;
		}
	}

	return retorno;
}
void print_Diagnoses(sDiagnostico listaDiagnosticos[])
{
	printf("Listas de diagnosticos disponibles: \n\n");
	for(int i=1;i<TAM_DIAGNOSTICO;i++)
	{
		printf("%d. %s\n",listaDiagnosticos[i].idDiagnostico, listaDiagnosticos[i].descripcion);
	}
}
int diagnose_One(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnostico[], sEspecialidadMedico listaEspecialidad[])
{
	int indexMedico;
	int idPaciente;
	int indexPaciente;
	int retorno = -1;
	int rtnPrint;

	indexMedico = find_And_Valid_Medic(listaMedicos, listaEspecialidad);

	rtnPrint = print_Patient_Without_Diagnose(listaPacientes, sizePacientes, indexMedico, listaMedicos, listaDiagnostico);
	if(rtnPrint == 0)
	{
		utn_getNumero(&idPaciente, "\nIngrese ID del paciente que desea diagnosticar: ", "\nERROR...\n", 999, 3000, 5);
		indexPaciente = find_Patient_By_ID(listaPacientes, sizePacientes, idPaciente);

		while(listaMedicos[indexMedico].idMedico != listaPacientes[indexPaciente].idMedico)
		{
			printf("\nERROR... el ID ingresado no es valido o no corresponde a un paciente de este medico.\n");
			utn_getNumero(&idPaciente, "\nIngrese ID del paciente que desea diagnosticar: ", "\nERROR...\n", 999, 3000, 5);
			indexPaciente = find_Patient_By_ID(listaPacientes, sizePacientes, idPaciente);
		}

		print_Diagnoses(listaDiagnostico);
		utn_getNumero(&listaPacientes[indexPaciente].idDiagnostico, "\nIngrese el diagnostico correspondiente del paciente: ", "\nERROR...\n", 1, 4, 5);

		if(listaPacientes[indexPaciente].idDiagnostico != NO_DIAGNOSTICADO)
		{
			retorno = 0;
		}
	}

	return retorno;
}
int find_Diagnose(sConsultas unPaciente, sDiagnostico listaDiagnosticos[])
{
	int indexDiagnostico=-1;

	for(int i=0; i<TAM_DIAGNOSTICO;i++)
	{
		if(unPaciente.idDiagnostico == listaDiagnosticos[i].idDiagnostico)
		{
			indexDiagnostico = i;
			break;
		}
	}

	return indexDiagnostico;
}
int findMedicById(int idIngresado, sMedico listaMedicos[])
{
	int retorno = -1;

	for(int i=0;i<TAM_MEDICOS;i++)
	{
		if(listaMedicos[i].idMedico == idIngresado)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}
int print_Patient_Without_Diagnose(sConsultas listaPacientes[], int sizePacientes, int indexMedico, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[])
{
	int indexDiagnostico;
	int retorno = -1;

	printf("\nLista de pacientes de %s:\n",listaMedicos[indexMedico].nombreMedico);

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].idDiagnostico == NO_DIAGNOSTICADO && listaMedicos[indexMedico].idMedico == listaPacientes[i].idMedico)
		{
			indexDiagnostico = find_Diagnose(listaPacientes[i], listaDiagnosticos);
			if(indexDiagnostico != -1)
			{
				printf("|%-5d |%-10s |%-10s\n",listaPacientes[i].idPaciente,listaPacientes[i].nombrePaciente,
													listaDiagnosticos[indexDiagnostico].descripcion);

				retorno = 0;
			}

		}
	}

	return retorno;
}
void printMenuListado(sConsultas listaPacientes[],int sizePacientes, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sDiagnostico listaDiagnosticos[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int opcion;
	int idEspecialidad;
	int order;

	do
	{
		opcion = menuListado();

		switch(opcion)
		{
			case 1:
				if(printDoctors(listaMedicos, listaEspecialidad) == 0)
				{
					printf("\nLista de medicos mostrada exitosamente... \n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 2:
				printf("\nLista de consultas: \n\n");
				if(print_Full_Queries(listaPacientes, sizePacientes, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias) == 1)
				{
					printf("\nLista mostrada exitosamente... \n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 3:
				print_Doctors_With_Diagnostic(listaPacientes, sizePacientes, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
			break;

			case 4:
				order = criterioOrdenamiento();
				if(sort_By_Date(listaPacientes, sizePacientes, order) == 0)
				{
					printf("\nLista ordenada correctamente...\n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema al ordenar la lista...\n\n");
				}
			break;

			case 5:
				if(print_List_Diagnosed_Queries(listaPacientes, sizePacientes, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias) == 0)
				{
					printf("\nLista mostrada exitosamente... \n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 6:
				printf("\nLista de consultas con COVID-19 despues de la pandemia: \n");
				if(print_Patient_After_Pandemic(listaPacientes, sizePacientes, listaDiagnosticos, listaMedicos, listaEspecialidad, listaClinicas, listaUrgencias) == 0)
				{
					printf("\nLista mostrada exitosamente... \n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 7:
				if(sort_By_Specialty(listaPacientes, sizePacientes) == 0)
				{
					printf("\nLista ordenada correctamente...\n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema al ordenar la lista...\n\n");
				}
			break;

			case 8:
				idEspecialidad = print_Specialty_to_Choose(listaEspecialidad);
				if(print_Month_April_July(listaPacientes, sizePacientes, idEspecialidad, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias) == 0)
				{
					printf("\nLista mostrada exitosamente... \n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 9:
				if(percentage_Queries_Diagnosed(listaPacientes, sizePacientes, listaMedicos) == 0)
				{
					printf("\nListado de porcentaje mostrado exitosamente...\n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 10:
				if(print_Less_Diagnosed(listaPacientes, sizePacientes, TAM_DIAGNOSTICO, listaDiagnosticos) == 0)
				{
					printf("\nEnfermedad menos diagnosticada mostrada exitosamente...\n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 11:
				if(print_Most_Studied_Specialty(TAM_ESPECIALIDAD, TAM_MEDICOS, listaMedicos, listaEspecialidad) == 0)
				{
					printf("\nEspecialidad mas estudiada mostrada exitosamente...\n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n\n");
				}
			break;

			case 12:
				printf("\nLista de consultas diagnosticadad en la Clinica Boedo despues de la final del Mundial: \n");
				if(print_Patient_In_Boedo_After_Qatar(listaPacientes, sizePacientes, listaClinicas, listaDiagnosticos, listaMedicos, listaEspecialidad, listaUrgencias) == 0)
				{
					printf("\nLista mostrada exitosamente... \n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n");
					printf("La lista ha sido ordenada por fecha y por eso no se puede mostrar esta lista.\n\n");
				}
			break;

			case 13:
				if(sort_By_Urgency_Patient(listaPacientes, sizePacientes) == 0)
				{
					printf("\nLista ordenada exitosamente... \n\n\n");
				}
				else
				{
					printf("\nHa ocurrido un problema...\n");
				}
			break;

			case 14:
				printf("\n\n=====================================\n");
				printf("Volviendo al menu principal...\n");
				printf("=====================================\n\n");
			break;
		}

	}while(opcion != 14);
}
int print_Most_Studied_Specialty(int sizeEspecialidad, int sizeMedicos, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[])
{
	int contadorEspecialidad1 = 0;
	int contadorEspecialidad2 = 0;
	int contadorEspecialidad3 = 0;
	int retorno = -1;

	for(int i=0; i < sizeMedicos; i++)
	{
		if(listaMedicos[i].idEspecialidad == 1)
		{
			contadorEspecialidad1++;
		}
		else
		{
			if(listaMedicos[i].idEspecialidad == 2)
			{
				contadorEspecialidad2++;
			}
			else
			{
				contadorEspecialidad3++;
			}
		}
	}

	if(contadorEspecialidad1 > contadorEspecialidad2 && contadorEspecialidad1 > contadorEspecialidad3)
	{
		printf("\n\n============================================\n");
		printf("La especialidad mas estudiada es %s.\n",listaEspecialidad[0].descripcion);
		printf("============================================\n\n\n");
		retorno = 0;
	}
	else
	{
		if(contadorEspecialidad2 > contadorEspecialidad3)
		{
			if(contadorEspecialidad1 == contadorEspecialidad2)
			{
				printf("\n\n=================================================================\n");
				printf("Las especialidades mas estudiadas son %s y %s.\n",listaEspecialidad[0].descripcion,listaEspecialidad[1].descripcion);
				printf("=================================================================\n\n\n");
				retorno = 0;
			}
			else
			{
				printf("\n\n==============================================\n");
				printf("La especialidad mas estudiada es %s.\n",listaEspecialidad[1].descripcion);
				printf("==============================================\n\n\n");
				retorno = 0;
			}

		}
		else
		{
			if(contadorEspecialidad1 == contadorEspecialidad3)
			{
				printf("\n\n================================================================\n");
				printf("Las especialidades mas estudiadas son %s y %s.\n",listaEspecialidad[0].descripcion,listaEspecialidad[2].descripcion);
				printf("================================================================\n\n\n");
				retorno = 0;
			}
			else
			{
				if(contadorEspecialidad2 == contadorEspecialidad3)
				{
					printf("\n\n=================================================================\n");
					printf("Las especialidades mas estudiadas son %s y %s.\n",listaEspecialidad[1].descripcion,listaEspecialidad[2].descripcion);
					printf("=================================================================\n\n\n");
					retorno = 0;
				}
				else
				{
					printf("\n\n=============================================\n");
					printf("La especialidad mas estudiada es %s.\n",listaEspecialidad[2].descripcion);
					printf("=============================================\n\n\n");
					retorno = 0;
				}
			}

		}
	}

	return retorno;
}
int print_Less_Diagnosed(sConsultas listaPacientes[], int sizePacientes, int sizeDiagnostico, sDiagnostico listaDiagnosticos[])
{
	int contadorPorEnfermedad1 = 0;
	int contadorPorEnfermedad2 = 0;
	int contadorPorEnfermedad3 = 0;
	int retorno = -1;

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].idDiagnostico == 1)
		{
			contadorPorEnfermedad1++;
		}
		else
		{
			if(listaPacientes[i].idDiagnostico == 2)
			{
				contadorPorEnfermedad2++;
			}
			else
			{
				if(listaPacientes[i].idDiagnostico == 3)
				{
					contadorPorEnfermedad3++;
				}
			}
		}
	}

	if(contadorPorEnfermedad1 < contadorPorEnfermedad2 && contadorPorEnfermedad1 < contadorPorEnfermedad3)
	{
		printf("\n\n==============================================\n");
		printf("La enfermedad menos diagnosticada es %s.\n",listaDiagnosticos[1].descripcion);
		printf("==============================================\n\n\n");
		retorno = 0;
	}
	else
	{
		if(contadorPorEnfermedad2 < contadorPorEnfermedad3)
		{
			if(contadorPorEnfermedad1 == contadorPorEnfermedad2)
			{
				printf("\n\n============================================================\n");
				printf("Las enfermedades menos diagnosticada son %s y %s.\n",listaDiagnosticos[1].descripcion,listaDiagnosticos[2].descripcion);
				printf("============================================================\n\n\n");
				retorno = 0;
			}
			else
			{
				printf("\n\n=============================================\n");
				printf("La enfermedad menos diagnosticada es %s.\n",listaDiagnosticos[2].descripcion);
				printf("=============================================\n\n\n");
				retorno = 0;
			}

		}
		else
		{
			if(contadorPorEnfermedad1 == contadorPorEnfermedad3)
			{
				printf("\n\n================================================================\n");
				printf("Las enfermedades menos diagnosticada son %s y %s.\n",listaDiagnosticos[1].descripcion,listaDiagnosticos[3].descripcion);
				printf("================================================================\n\n\n");
				retorno = 0;
			}
			else
			{
				if(contadorPorEnfermedad2 == contadorPorEnfermedad3)
				{
					printf("\n\n===============================================================\n");
					printf("Las enfermedades menos diagnosticada son %s y %s.\n",listaDiagnosticos[2].descripcion,listaDiagnosticos[3].descripcion);
					printf("===============================================================\n\n\n");
					retorno = 0;
				}
				else
				{
					printf("\n\n==================================================\n");
					printf("La enfermedad menos diagnosticada es: %s.\n",listaDiagnosticos[3].descripcion);
					printf("==================================================\n\n\n");
					retorno = 0;
				}
			}
		}
	}

	return retorno;
}
int percentage_Queries_Diagnosed(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[])
{
	int contadorConsultasDiagnosticadas = 0;
	int contadorPorMedico[TAM_MEDICOS];
	int retorno = -1;

	for(int i=0;i<TAM_MEDICOS;i++)
	{
		contadorPorMedico[i] = contarConsultasDiagnosticadasPorMedico(listaMedicos[i].idMedico,listaPacientes, sizePacientes, &contadorConsultasDiagnosticadas);
	}
	if(print_Promedio(contadorConsultasDiagnosticadas, contadorPorMedico, listaMedicos) == 0)
	{
		printf("=====================================================================\n");
		retorno = 0;
	}

	return retorno;
}
int print_Promedio(int contadorConsultasDiagnosticadas,int contadorPorMedico[], sMedico listaMedicos[])
{
	float porcentaje;
	int retorno = -1;

	for(int i=0;i<TAM_MEDICOS;i++)
	{
		porcentaje = ((float)contadorPorMedico[i]) * 100 / contadorConsultasDiagnosticadas;
		printf("=====================================================================\n");
		printf("El porcentaje de consultas diagnosticadas de %s es: %.2f%%\n", listaMedicos[i].nombreMedico, porcentaje);
		retorno = 0;
	}

	return retorno;
}
int contarConsultasDiagnosticadasPorMedico(int idMedico, sConsultas listaPacientes[], int sizePacientes, int* contadorConsultasDiagnosticadas )
{
	int contador = 0;

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado == LLENO && listaPacientes[i].idDiagnostico != NO_DIAGNOSTICADO && idMedico == listaPacientes[i].idMedico)
		{
			contador++;
			*contadorConsultasDiagnosticadas = *contadorConsultasDiagnosticadas + 1;
		}
	}

	return contador;
}
int print_Month_April_July(sConsultas listaPacientes[], int sizePacientes, int idEspecialidad, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int retorno = -1;

	printf("|%-5s |%-10s |%-12s | %-15s | %-15s | %-20s | %-20s| %-10s|\n", "ID", "Nombre",
														"Fecha", "Medico",
														"Especialidad","Diagnostico",
														"Clinica", "Urgencia");
	printf("=======|===========|=============|=================|=================|======================|=====================|===========|\n");

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].idEspecialidad == idEspecialidad)
		{
			if(listaPacientes[i].fechaConsulta.mes > 3 && listaPacientes[i].fechaConsulta.mes < 8)
			{
				print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
				//sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[],
				//sClinica listaClinicas[], sUrgencia listaUrgencias[])
				retorno = 0;
			}
		}
	}

	printf("===============================================================================================================================\n");

	return retorno;
}
int print_Specialty_to_Choose(sEspecialidadMedico listaEspecialidad[])
{
	int opcion;

	printf("\nLista de especialidades: \n");

	for(int i=0;i<TAM_ESPECIALIDAD;i++)
	{
		printf("%d. %s.\n",listaEspecialidad[i].idEspecialidad,listaEspecialidad[i].descripcion);
	}

	utn_getNumero(&opcion, "Ingrese una especialidad: ", "\nError... opcion no valida\n", 1, 3, 5);

	return opcion;
}

int sort_By_Specialty(sConsultas listaPacientes[],int sizePacientes)
{
	sConsultas aux;
	int retorno = -1;

	for(int i=0; i< sizePacientes - 1; i++)
	{
		for(int j = i+1; j < sizePacientes; j++)
		{
			if(listaPacientes[i].idEspecialidad > listaPacientes[j].idEspecialidad)
			{
				aux = listaPacientes[i];
				listaPacientes[i] = listaPacientes[j];
				listaPacientes[j] = aux;
				retorno = 0;
			}
		}
	}

	return retorno;
}
int sort_By_Date(sConsultas listaPacientes[], int sizePacientes, int order)
{
	sConsultas aux;
	int retorno = -1;

	switch(order)
	{
		case 1:
			for(int i=0;i<sizePacientes - 1;i++)
			{
				for(int j=i+1;j<sizePacientes;j++)
				{
					if(listaPacientes[i].fechaConsulta.anio < listaPacientes[j].fechaConsulta.anio)
					{
						aux= listaPacientes[i];
						listaPacientes[i]=listaPacientes[j];
						listaPacientes[j]=aux;
					}
					if(listaPacientes[i].fechaConsulta.anio == listaPacientes[j].fechaConsulta.anio)
					{
						if(listaPacientes[i].fechaConsulta.mes < listaPacientes[j].fechaConsulta.mes)
						{
							aux= listaPacientes[i];
							listaPacientes[i]=listaPacientes[j];
							listaPacientes[j]=aux;
						}
						if(listaPacientes[i].fechaConsulta.mes == listaPacientes[j].fechaConsulta.mes)
						{
							if(listaPacientes[i].fechaConsulta.dia < listaPacientes[j].fechaConsulta.dia)
							{
								aux= listaPacientes[i];
								listaPacientes[i]=listaPacientes[j];
								listaPacientes[j]=aux;
							}
						}
					}
				}
			}
			retorno = 0;
		break;

		case 0:
			for(int i=0;i<sizePacientes - 1;i++)
			{
				for(int j=i+1;j<sizePacientes;j++)
				{
					if(listaPacientes[i].fechaConsulta.anio > listaPacientes[j].fechaConsulta.anio)
					{
						aux= listaPacientes[i];
						listaPacientes[i]=listaPacientes[j];
						listaPacientes[j]=aux;
					}
					if(listaPacientes[i].fechaConsulta.anio == listaPacientes[j].fechaConsulta.anio)
					{
						if(listaPacientes[i].fechaConsulta.mes > listaPacientes[j].fechaConsulta.mes)
						{
							aux= listaPacientes[i];
							listaPacientes[i]=listaPacientes[j];
							listaPacientes[j]=aux;
						}
						if(listaPacientes[i].fechaConsulta.mes == listaPacientes[j].fechaConsulta.mes)
						{
							if(listaPacientes[i].fechaConsulta.dia > listaPacientes[j].fechaConsulta.dia)
							{
								aux= listaPacientes[i];
								listaPacientes[i]=listaPacientes[j];
								listaPacientes[j]=aux;
							}
						}
					}
				}
			}
			retorno = 0;
		break;
	}

	return retorno;
}
int print_Patient_After_Pandemic(sConsultas listaPacientes[],int sizePacientes, sDiagnostico listaDiagnosticos[], sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int retorno = -1;

	printf("|%-5s |%-10s |%-12s | %-15s | %-15s | %-20s | %-20s| %-10s|\n", "ID", "Nombre",
														"Fecha", "Medico",
														"Especialidad","Diagnostico",
														"Clinica", "Urgencia");
	printf("=======|===========|=============|=================|=================|======================|=====================|===========|\n");

	for(int i=0; i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==LLENO && listaPacientes[i].idDiagnostico == listaDiagnosticos[1].idDiagnostico)
		{
			if(listaPacientes[i].fechaConsulta.anio == 2020)
			{
				if(listaPacientes[i].fechaConsulta.mes > 2)
				{
					if(listaPacientes[i].fechaConsulta.mes == 3)
					{
						if(listaPacientes[i].fechaConsulta.dia > 18)
						{
							print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
							//sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[],
							//sClinica listaClinicas[], sUrgencia listaUrgencias[])

							retorno = 0;
						}
					}
					else
					{
						print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
						retorno = 0;
					}
				}
			}
			else
			{
				if(listaPacientes[i].fechaConsulta.anio > 2020)
				{
					print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
					retorno = 0;
				}
			}
		}
	}

	printf("===============================================================================================================================\n");

	return retorno;
}
void print_Doctors_With_Diagnostic(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int rtnDiagnostico;

	for(int i=0;i<TAM_MEDICOS;i++)
	{
		rtnDiagnostico = print_Diagnosed_Patient(listaMedicos[i], listaPacientes, sizePacientes, listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);

		if(rtnDiagnostico == -1)
		{
			printf("El medico no tiene diagnosticos.\n");
		}
	}

	printf("==============================================================================================================\n\n");
}
int print_Diagnosed_Patient(sMedico unMedico, sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int retorno = -1;

	printf("============================================================================================================================");
	printf("\nLista de pacientes diagnosticados de %s:\n\n", unMedico.nombreMedico);
	printf("|%-5s |%-10s |%-12s | %-15s | %-15s | %-20s | %-20s| %-10s|\n", "ID", "Nombre",
														"Fecha", "Medico",
														"Especialidad","Diagnostico",
														"Clinica", "Urgencia");

	printf("=======|===========|=============|=================|=================|======================|=====================|===========|\n");

	for(int i=0; i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==LLENO && unMedico.idMedico==listaPacientes[i].idMedico && listaPacientes[i].idDiagnostico!=NO_DIAGNOSTICADO)
		{
			retorno = 0;
			print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
		}
	}

	return retorno;
}
int print_List_Diagnosed_Queries(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int retorno = -1;

	printf("|%-5s |%-10s |%-12s | %-15s | %-15s | %-20s | %-20s| %-10s|\n", "ID", "Nombre",
														"Fecha", "Medico",
														"Especialidad","Diagnostico",
														"Clinica", "Urgencia");
	printf("=======|===========|=============|=================|=================|======================|=====================|===========|\n");

	for(int i=0;i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==LLENO && listaPacientes[i].idDiagnostico != NO_DIAGNOSTICADO)
		{
			print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
			retorno = 0;
		}
	}

	printf("===============================================================================================================================\n");

	return retorno;
}
void print_All_Patients(sConsultas unPaciente, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[])
{
	int indexMedico;
	int indexEspecialidad;

	indexMedico = findMedico(unPaciente,&indexEspecialidad, listaMedicos, listaEspecialidad);

	for(int i=0; i<TAM_DIAGNOSTICO; i++)
	{
		for(int j=0; j<TAM_CLINICAS; j++)
		{
			for(int k=0; k<TAM_URGENCIAS; k++)
			{
				if((unPaciente.idDiagnostico == listaDiagnosticos[i].idDiagnostico) && (unPaciente.idClinica == listaClinicas[j].idClinica) && (unPaciente.idUrgencia == listaUrgencias[k].idUrgencia))
				{
					print_One_Patient(unPaciente,listaMedicos[indexMedico],
											listaDiagnosticos[i],
											listaEspecialidad[indexEspecialidad],
											listaClinicas[j],
											listaUrgencias[k]);
				}
			}
		}
	}
}
int find_And_Valid_Medic(sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[])
{
	int idMedico;
	int index;

	printDoctors(listaMedicos, listaEspecialidad);

	utn_getNumero(&idMedico, "Ingrese Medico para diagnosticar al paciente: ", "\nERROR...\n", 1, 5, 5);

	index = findMedicById(idMedico, listaMedicos);

	while(index == -1)
	{
		printf("\nNo se ha encontrado el ID.\n");

		printDoctors(listaMedicos, listaEspecialidad);

		utn_getNumero(&idMedico, "Ingrese Medico para diagnosticar al paciente: ", "\nERROR...\n", 1, 5, 5);

		index = findMedicById(idMedico, listaMedicos);
	}

	return index;
}
int criterioOrdenamiento()
{
	int opcion;

	printf("\n¿Como quiere ordenar?\n"
	"0. Ordenar en ASCENDENTE\n"
	"1. Ordenar en DESCENDENTE\n\n");

	utn_getNumero(&opcion, "Elija una opcion: ", "\nOpcion invalida...\n", 0, 1, 5);

	return opcion;
}
int print_Patient_In_Boedo_After_Qatar(sConsultas listaPacientes[],int sizePacientes, sClinica listaClinicas[], sDiagnostico listaDiagnosticos[], sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sUrgencia listaUrgencias[])
{
	int retorno = -1;

	printf("|%-5s |%-10s |%-12s | %-15s | %-15s | %-20s | %-20s| %-10s|\n", "ID", "Nombre",
														"Fecha", "Medico",
														"Especialidad","Diagnostico",
														"Clinica", "Urgencia");
	printf("=======|===========|=============|=================|=================|======================|=====================|===========|\n");

	for(int i=0; i<sizePacientes;i++)
	{
		if(listaPacientes[i].estado==LLENO && listaPacientes[i].idClinica == listaClinicas[2].idClinica && listaDiagnosticos[i].idDiagnostico != NO_DIAGNOSTICADO)
		{
			if(listaPacientes[i].fechaConsulta.anio == 2022)
			{
				if(listaPacientes[i].fechaConsulta.mes > 11)
				{
					if(listaPacientes[i].fechaConsulta.dia > 18)
					{
						print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
						retorno = 0;
					}
				}
			}
			else
			{
				if(listaPacientes[i].fechaConsulta.anio > 2022)
				{
					print_All_Patients(listaPacientes[i], listaMedicos, listaDiagnosticos, listaEspecialidad, listaClinicas, listaUrgencias);
					retorno = 0;
				}
			}
		}
	}

	printf("===============================================================================================================================\n");

	return retorno;
}
int sort_By_Urgency_Patient(sConsultas listaPacientes[], int sizePacientes)
{
	sConsultas aux;
	int retorno = -1;

	for(int i=0; i<sizePacientes - 1; i++)
	{
		for(int j=i+1; j<sizePacientes; j++)
		{
			if(listaPacientes[i].idUrgencia > listaPacientes[j].idUrgencia)
			{
				aux = listaPacientes[i];
				listaPacientes[i] = listaPacientes[j];
				listaPacientes[j] = aux;
				retorno = 0;
			}
			if(listaPacientes[i].idUrgencia == listaPacientes[j].idUrgencia)
			{
				if(strcmp(listaPacientes[i].nombrePaciente, listaPacientes[j].nombrePaciente) > 0)
				{
					aux = listaPacientes[i];
					listaPacientes[i] = listaPacientes[j];
					listaPacientes[j] = aux;
					retorno = 0;
				}
			}
		}
	}

	return retorno;
}
