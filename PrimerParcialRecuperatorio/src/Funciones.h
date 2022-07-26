#ifndef FUNCIONES_H_
#define FUNCIONES_H_
#define LLENO 1
#define VACIO 0
#define NO_DIAGNOSTICADO 0
#define TAM_MEDICOS 5
#define TAM_DIAGNOSTICO 4
#define TAM_ESPECIALIDAD 3
#define TAM_CLINICAS 4
#define TAM_URGENCIAS 5
#define TAM_PACIENTES 2000

typedef struct
{
	int dia;
	int mes;
	int anio;

}sFecha;

typedef struct
{
	int idPaciente;
	char nombrePaciente[50];
	sFecha fechaConsulta;
	int idMedico;
	int estado;
	int idDiagnostico;
	int idClinica;
	int idUrgencia;
	int idEspecialidad;

}sConsultas;

typedef struct
{
	int idMedico;
	char nombreMedico[50];
	int idEspecialidad;

}sMedico;

typedef struct
{
	int idEspecialidad;
	char descripcion[50];
}sEspecialidadMedico;

typedef struct
{
	int idDiagnostico;
	char descripcion[50];

}sDiagnostico;

typedef struct
{
	int idClinica;
	char descripcion[50];

}sClinica;

typedef struct
{
	int idUrgencia;
	char descripcion[20];

}sUrgencia;
/// @brief genera un ID autoincremental a partir de 1000
///
/// @return retorna el ID
int obtenerID(void);
/// @brief A los pacientes con estado LLENO les encuentra una especialidad
///
/// @param listaPacientes, array de consultas
/// @param sizePacientes, tamaño del array de pacientes
/// @param listaEspecialidad, array de especialidad
/// @param listaMedicos, array de medicos
void init_Pacientes_Empty_For_Hardcode(sConsultas listaPacientes[], int sizePacientes, sEspecialidadMedico listaEspecialidad[], sMedico listaMedicos[]);
/// @brief busca un lugar libre
///
/// @param lista, array de consultas
/// @param size, tamaño del array
/// @return retorna el INDEX libre
int find_Index_Free(sConsultas lista[], int size);
/// @brief busca un medico mediante el ID pasado como parametro
///
/// @param idIngresado, Id del medico para buscarlo
/// @param listaMedicos, array de medicos
/// @return retorna la posicion en la cual encontro al medico
int findMedicById(int idIngresado, sMedico listaMedicos[]);
/// @brief  añade un paciente a la lista, con la funcion add_One_Patient
///
/// @param lista, array de pacientes
/// @param size, tamaño del array
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return retorna 0 si se pudo cargar un paciente correctamente
/// @return sino retorna -1
int add_One_Patient_On_List(sConsultas lista[], int size, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief se ingresan los datos requeridos para la consulta y se encuentra una especialidad
///
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaMedicos, array de medicos
/// @param listaUrgencias, array de urgencias
/// @return retorna a el PACIENTE pero en un auxiliar
sConsultas add_One_Patient(sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sMedico listaMedicos[], sUrgencia listaUrgencias[]);

/// @brief recorre el array de pacientes y si coincide con el ID pasado como parametro lo elimina
///
/// @param lista, array de pacientes
/// @param len, tamaño del array de pacientes
/// @param idAux, ID a eliminar
/// @return retorna 0 si se pudo eliminar, y -1 si no se pudo
int removePatient(sConsultas lista[], int len, int idAux);
/// @brief muestra los pacientes y se pide un ID para eliminar junto con la funcion removePatient
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño del array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return retorna 0 si se elimina al paciente, 1 si se cancela.
int remove_One_Patient(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);

/// @brief Se pide un ID y se lo modifica
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño del aray de pacientes
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return retorna 0 si se pudo modificar, 1 se se cancela.
int edit_Patient(sConsultas listaPacientes[] ,int sizePacientes, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sDiagnostico listaDiagnosticos[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief Se muetra el menu de modificaciones y se elije uno y se modifica los datos de la consulta.
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño del array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @return retorna al auxiliar del paciente modificado
sConsultas edit_One_Patient(sConsultas listaPacientes,int sizePacientes, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[]);

/// @brief recorre el array de medicos y coincide el ID se busca la especialidad
///
/// @param unPaciente, LE PASO UN PACIENTE PARA QUE VEA EL ID INGRESADO, LO VERIFIQUE Y LE ENCUENTRE LA ESPECIALIDAD
/// @param indexEspecialidad, le paso la direccion de memoria de indexespecialidad asi lo busca y le asigna la especialidad
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @return retorna el index encontrado
int findMedico(sConsultas unPaciente,int* indexEspecialidad, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[]);
/// @brief muestra los medicos, encontrandoles la especialidad depende el medico
///
/// @param listaMedicos
/// @param listaEspecialidad
/// @return retorna 0 si salio bien, sino -1 si hubo un error.
int printDoctors(sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[]);
/// @brief recorre el array de diagnosticos y lo trata de encontrar
///
/// @param unPaciente, le paso EL PACIENTE donde tiene guardada el id del diagnostico elegido
/// @param listaDiagnosticos, array de diagnosticos
/// @return retorna la posicion del index encontrado.
int find_Diagnose(sConsultas unPaciente, sDiagnostico listaDiagnosticos[]);
/// @brief recorro el array y muestro las clinicas
///
/// @param listaClinicas, array de clinica
void printClinica(sClinica listaClinicas[]);
/// @brief recorro el array y muestro las urgencias
///
/// @param listaUrgencias, array de urgencias
void printUrgencias(sUrgencia listaUrgencias[]);
/// @brief recorro el array y muestro los diagnosticos
///
/// @param listaDiagnosticos, array de diagnosticos
void print_Diagnoses(sDiagnostico listaDiagnosticos[]);

/// @brief recorro el array de pacientes y busco el ID pasado como parametro
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param idIngresado, ID que quiero encontrar
/// @return retorna la posicion del index encontrado
int find_Patient_By_ID(sConsultas listaPacientes[], int sizePacientes, int idIngresado);
/// @brief diagnostica un paciente sin diagnostico previo
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaDiagnostico, array de diagnostico
/// @param listaEspecialidad, array de especialidad
/// @return retorna 0 si se pudo diagnosticar, -1 si hubo un problema y no se pudo.
int diagnose_One(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnostico[], sEspecialidadMedico listaEspecialidad[]);
/// @brief busca y valida un medico ingresado
///
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @return retorna el index del medico encontrado
int find_And_Valid_Medic(sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[]);
/// @brief recorre el array y encuentra el ID de UN MEDICO pasado por parametro
///
/// @param unMedico, un MEDICO de la lista
/// @param listaEspecialidad, array de especialidad
/// @return retorna el index encontrado
int findEspecialidad(sMedico unMedico, sEspecialidadMedico listaEspecialidad[]);
/// @brief encuentra la especialidad del medico que elijio el paciente
///
/// @param unPaciente, le paso el paciente que tiene el id del medico que elijio
/// @param idEspecialidad, direccion de memoria donde se guarda la id de especialidad
/// @param listaEspecialidad, array de especialidad
/// @param listaMedicos, array de medicos
void find_specialty(sConsultas unPaciente ,int* idEspecialidad, sEspecialidadMedico listaEspecialidad[], sMedico listaMedicos[]);
/// @brief recorre array de medicos y muestra los porcentajes de consultas diagnosticadas por medico
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaMedicos, array de medicos
/// @return  retorna 0 si se pudo mostrar el porcentaje, sino retorna -1
int percentage_Queries_Diagnosed(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[]);
/// @brief cuenta las consultas diagnosticadas y las consultas diagnosticadas por cada medico
///
/// @param idMedico, id del medico para sacar la cantidad de consultas que tiene cada medico
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array pacientes
/// @param contadorConsultasDiagnosticadas, direccion de memoria donde quiero que se guarde todas las consultas diagnosticadas
/// @return retorna el contador de consultas diagnosticadas para cada medico
int contarConsultasDiagnosticadasPorMedico(int idMedico, sConsultas listaPacientes[], int sizePacientes, int* contadorConsultasDiagnosticadas );
/// @brief pregunta al paciente el criterio por el cual quiere ordenar ASCENDENTE O DESCENDENTE
///
/// @return retorna 0 si es ASCENDENTE y 1 si es DESCENDENTE
int criterioOrdenamiento();

/// @brief ordena las consultas por especialidad alfabeticamente
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @return retorna 0 si se pudo ordenar sino retorna -1
int sort_By_Specialty(sConsultas listaPacientes[],int sizePacientes);
/// @brief ordena las consultas por fecha
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param order, 1 para DESCENDENTE 0 si es DESCENDENTE
/// @return retorna 0 si se pudo ordenar sino retorna -1
int sort_By_Date(sConsultas listaPacientes[], int sizePacientes, int order);
/// @brief ordena las consultas por urgencia del paciente y por nombre alfabeticamente
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @return retorna 0 si se pudo ordenar sino retorna -1
int sort_By_Urgency_Patient(sConsultas listaPacientes[], int sizePacientes);


/// @brief printea todos los pacientes recorriendo todas las listas pasadas como parametros
///
/// @param unPaciente, le paso UN PACIENTE para encontrar el index del medico
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, aarray de urgencias
void print_All_Patients(sConsultas unPaciente, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief menu con las opciones de listados
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidades
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
void printMenuListado(sConsultas listaPacientes[],int sizePacientes, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sDiagnostico listaDiagnosticos[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief muestra TODAS LAS CONSULTAS junto con la funcion print_All_Patients
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return retorna 1 si se pudo mostrar sino retorna 0
int print_Full_Queries(sConsultas listaPacientes[],int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief imprime SOLO UN PACIENTE
///
/// @param unPaciente, le paso UN PACIENTE que quiero imprimir
/// @param medico, le paso un medico que quiero imprimir
/// @param diagnostico, le paso un diagnostico que quiero imprimir
/// @param especialidad, le paso una especialidad que quiero imprimir
/// @param clinica, le paso una clinica que quiero imprimir
/// @param urgencia, le paso una urgencia que quiero imprimir
void print_One_Patient(sConsultas unPaciente, sMedico medico, sDiagnostico diagnostico, sEspecialidadMedico especialidad, sClinica clinica, sUrgencia urgencia);
/// @brief imprime los pacientes SIN DIAGNOSTICOS
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param indexMedico, indice del medico que quiero mostrar
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @return retorna 0 si se pudo motrar sino retorna -1
int print_Patient_Without_Diagnose(sConsultas listaPacientes[], int sizePacientes, int indexMedico, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[]);
/// @brief imprime los medicos con diagnosticos junto con la funcion print_Diagnosed_Patient
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
void print_Doctors_With_Diagnostic(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief imprime el porcentaje de consultas diagnosticadas por medico
///
/// @param contadorConsultasDiagnosticadas, contador total de consultas diagnosticadas
/// @param contadorPorMedico, contador de consultas diagnosticadas POR MEDICO
/// @param listaMedicos, array de medicos
/// @return 0 si se pudo mostrar sino retorna -1
int print_Promedio(int contadorConsultasDiagnosticadas,int contadorPorMedico[], sMedico listaMedicos[]);
/// @brief imprime todas las consultas DIAGNOSTICADAS para mostrar los medicos con cada diagnostico
///
/// @param unMedico, le paso el medico que quiero imprimir
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return 0 si se pudo mostrar sino retorna -1
int print_Diagnosed_Patient(sMedico unMedico,sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief imprime la lista de consultas diagnosticadas
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return 0 si se pudo mostrar sino retorna -1
int print_List_Diagnosed_Queries(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief recorre el array de consultas y verifica el año, mes y dia y que sea COVID-19
/// para que sea despues de la pandemia y mostrar la lista.
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return 0 si se pudo mostrar sino retorna -1
int print_Patient_After_Pandemic(sConsultas listaPacientes[],int sizePacientes, sDiagnostico listaDiagnosticos[], sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief recorre el array de consultas y verifica que sea clinica BOEDO y despues de la final del mundial y muestra las consultas
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param listaClinicas, array de clinicas
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @param listaUrgencias, array de urgencias
/// @return 0 si se pudo mostrar sino retorna -1
int print_Patient_In_Boedo_After_Qatar(sConsultas listaPacientes[],int sizePacientes, sClinica listaClinicas[], sDiagnostico listaDiagnosticos[], sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sUrgencia listaUrgencias[]);
/// @brief muestra la especialidad menos estudiada por los medicos, con contadores y demas
///
/// @param sizeEspecialidad, tamaño de array especialidad
/// @param sizeMedicos, tamaño de array de  medicos
/// @param listaMedicos, array de medicos
/// @param listaEspecialidad, array de especialidad
/// @return 0 si se pudo mostrar sino retorna -1
int print_Most_Studied_Specialty(int sizeEspecialidad, int sizeMedicos, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[]);
/// @brief muestra la enfermedad menos diagnosticadas con contadores y demas
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param sizeDiagnostico, tamaño de array de diagnosticos
/// @param listaDiagnosticos, array de diagnosticos
/// @return 0 si se pudo mostrar sino retorna -1
int print_Less_Diagnosed(sConsultas listaPacientes[], int sizePacientes, int sizeDiagnostico, sDiagnostico listaDiagnosticos[]);
/// @brief recorre  el array de consultas y verifica que este entre abril y julio y mostrar de una especialidad
///
/// @param listaPacientes, array de pacientes
/// @param sizePacientes, tamaño de array de pacientes
/// @param idEspecialidad, id de especialidad para mostrar depende de que sea el ID de la especialidad
/// @param listaMedicos, array de medicos
/// @param listaDiagnosticos, array de diagnosticos
/// @param listaEspecialidad, array de especialidad
/// @param listaClinicas, array de clinicas
/// @param listaUrgencias, array de urgencias
/// @return 0 si se pudo mostrar sino retorna -1
int print_Month_April_July(sConsultas listaPacientes[], int sizePacientes, int idEspecialidad, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
/// @brief recorre el array de especialidad y se elije uno para usarlo en la funcion print_Month_April_July
///
/// @param listaEspecialidad, array de especialidad
/// @return retorna el ID  de la especialidad elegida
int print_Specialty_to_Choose(sEspecialidadMedico listaEspecialidad[]);

#endif
