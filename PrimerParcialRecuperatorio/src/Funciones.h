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
int find_And_Valid_Medic();
int findEspecialidad(sMedico unMedico, sEspecialidadMedico listaEspecialidad[]);
void find_specialty(sConsultas unPaciente ,int* idEspecialidad, sEspecialidadMedico listaEspecialidad[], sMedico listaMedicos[]);
int percentage_Queries_Diagnosed(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[]);
int contarConsultasDiagnosticadasPorMedico(int idMedico, sConsultas listaPacientes[], int sizePacientes, int* contadorConsultasDiagnosticadas );
int criterioOrdenamiento();

int sort_By_Specialty(sConsultas listaPacientes[],int sizePacientes);
int sort_By_Date(sConsultas listaPacientes[], int sizePacientes, int order);
int sort_By_Urgency_Patient(sConsultas listaPacientes[], int sizePacientes);


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
int print_Full_Queries(sConsultas listaPacientes[],int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
void print_One_Patient(sConsultas unPaciente, sMedico medico, sDiagnostico diagnostico, sEspecialidadMedico especialidad, sClinica clinica, sUrgencia urgencia);
int print_Patient_Without_Diagnose(sConsultas listaPacientes[], int sizePacientes, int indexMedico, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[]);
void print_Doctors_With_Diagnostic(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
int print_Promedio(int contadorConsultasDiagnosticadas,int contadorPorMedico[], sMedico listaMedicos[]);
int print_Diagnosed_Patient(sMedico unMedico,sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
int print_List_Diagnosed_Queries(sConsultas listaPacientes[], int sizePacientes, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
int print_Patient_After_Pandemic(sConsultas listaPacientes[],int sizePacientes, sDiagnostico listaDiagnosticos[], sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
int print_Patient_In_Boedo_After_Qatar(sConsultas listaPacientes[],int sizePacientes, sClinica listaClinicas[], sDiagnostico listaDiagnosticos[], sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[], sUrgencia listaUrgencias[]);
int print_Most_Studied_Specialty(int sizeEspecialidad, int sizeMedicos, sMedico listaMedicos[], sEspecialidadMedico listaEspecialidad[]);
int print_Less_Diagnosed(sConsultas listaPacientes[], int sizePacientes, int sizeDiagnostico, sDiagnostico listaDiagnosticos[]);
int print_Month_April_July(sConsultas listaPacientes[], int sizePacientes, int idEspecialidad, sMedico listaMedicos[], sDiagnostico listaDiagnosticos[], sEspecialidadMedico listaEspecialidad[], sClinica listaClinicas[], sUrgencia listaUrgencias[]);
int print_Specialty_to_Choose(sEspecialidadMedico listaEspecialidad[]);

#endif
