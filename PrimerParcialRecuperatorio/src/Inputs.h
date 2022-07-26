#ifndef FUNCIONUTN_H_
#define FUNCIONUTN_H_

int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getNombre(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos);
int utn_getDescripcion(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos);
int utn_getAlphaNumeric(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos);
int getString(char* cadena, int longitud);
int esNumerica(char* cadena, int limite);
int getInt(int* pResultado);
int esFlotante(char* cadena, int limite);
int getFloat(float* pResultado);
int getNombre(char* pResultado, int longitud);
int esNombre(char* cadena, int longitud);
int getDescripcion(char* pResultado, int longitud);
int esDescripcion(char* cadena, int longitud);
int getAlphaNumeric(char* pResultado, int longitud);
int esAlphaNumeric(char* cadena, int longitud);
int menu();
int menuListado();
#endif

