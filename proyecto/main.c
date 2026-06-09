#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "mapas.h"

#define VISTA_FILAS 20
#define VISTA_COL 20

//Prototipo de funciones obligatorias implementadas en NASM
int validarMovimiento(char* mapa, int columnas, int nuevaFila, int nuevaColumna);
int contarCaracteres(char* mapa, int columnas, int caracter);
int contarCeldasLibres(char* mapa, int totalCeldas);
int detectarObjeto(char* mapa, int columnas, int filaJugador, int columnaJugador, char objeto);
int calcularPuntaje(int monedas, int pasos, int niveles);

//Prototipo de funciones en c
void menu();
void juego();
void imprimirTablero(char mat[FILAS][COL], int jugadorFila, int jugadorColumna);
void cargarMapaArchivo(char* nombreMapa, char mapa[FILAS][COL]);

int main(){
    //mandamos ejecutar el manu principal
    menu();
    return 0;
}

//-----------------------Implementacion de funciones de c--------------------------------
//Funcion que contiene el manejo del menu principal
void menu(){
    //limpiamos pantalla
    system("cls");

    //Ciclo while para siempre mantener abierto el menu y un switch para comprobar seleccion
    int opc = 0;
    do{
        printf("\n\tMenu principal BitQuest.");
        printf("\n 1.Jugar.");
        printf("\n 0.Salir.");
        printf("\n\n Opcion: ");
        scanf(" %d", &opc);
        switch(opc){
            case 1:
                juego();
                break;
            case 0:
                //mensaje al salir
                printf("\n Saliendo... \n ");
                break;
            default:
                break;
        }
    }while(opc!=0);
}

//Funcion que contiene la logica y ejecucion de todo el juego
void juego(){
    //limpiamos pantalla
    system("cls");

    //Declaramos la matriz que contendra el mapa de los niveles
    char mapa[FILAS][COL];
    //Comenzamos el juego con el mapa del nivel 1 (asi que lo cargamos del archivo de texto)
    cargarMapaArchivo("mapas/mapaNivel1.txt", mapa);

    //Inicializamos datos de la partida
    int posJugador_fila = 1;
    int posJugador_columna = 1;
    char movimiento;
    int monedasRecogidas = 0;
    int monedasTotales = 0;
    int pasos = 0;
    int llaves=0;
    int totalCeldas = FILAS * COL;
    int totalPuertas = contarCaracteres(&mapa[0][0], totalCeldas, 'D');
    int puertasAbiertas = 0;

    totalPuertas = contarCaracteres(&mapa[0][0], totalCeldas, 'D');
    monedasTotales = contarCaracteres(&mapa[0][0 ], totalCeldas, 'C'); 
    int celdasLibres = contarCeldasLibres(&mapa[0][0], totalCeldas);
    
    //Ciclo de ejecucion del juego
    while(1){
        imprimirTablero(mapa, posJugador_fila, posJugador_columna);
        printf("Pasos: %d\n", pasos);
        printf("Celdas libres: %d\n", celdasLibres);
        printf("Monedas recogidas: %d/%d\n", monedasRecogidas, monedasTotales);
        printf("Llaves: %d\n", llaves); 
        movimiento = _getch(); 

        int nuevaPosFila = posJugador_fila;
        int nuevaPosColumna = posJugador_columna;

        if(movimiento == 'w' || movimiento == 'W') nuevaPosFila--;
        else if(movimiento == 's' || movimiento == 'S') nuevaPosFila++;
        else if(movimiento == 'a' || movimiento == 'A') nuevaPosColumna--;
        else if(movimiento == 'd' || movimiento == 'D') nuevaPosColumna++;
        else if(movimiento == 'q' || movimiento == 'Q') break;

        int valido = validarMovimiento(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna);
        int tocoPuerta = detectarObjeto(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna, 'D');
        if(tocoPuerta == 1 && llaves == 0){
            valido = 0;
        }
        if(valido){
            if (tocoPuerta == 1){
                llaves--;
                puertasAbiertas++;
                celdasLibres++;
            }
            int tocoSalida =detectarObjeto(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna, 'S');
            if(tocoSalida){
                mapa[posJugador_fila][posJugador_columna] = '.';
                posJugador_fila = nuevaPosFila;
                posJugador_columna = nuevaPosColumna;
                mapa[posJugador_fila][posJugador_columna] = 'P';
                pasos++;

                imprimirTablero(mapa, posJugador_fila, posJugador_columna);
                printf("Nivel 1 Completado\n");
                printf("Pasos Realizados: %d\n", pasos);
                printf("Puertas abiertas: %d/%d\n", puertasAbiertas, totalPuertas);
                printf("Monedas recogidas: %d/%d\n", monedasRecogidas, monedasTotales);
                int puntaje = calcularPuntaje(monedasRecogidas, pasos, 1);
                printf("Puntaje Final del Nivel: %d\n", puntaje);
                printf("\n¡Felicidades! Llegaste a la salida!\n");
                break;
            }

            int tocoMoneda = detectarObjeto(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna, 'C');
            if(tocoMoneda){
                monedasRecogidas++;
                celdasLibres++;
            }

            int tocoLlave = detectarObjeto(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna, 'K');
            if(tocoLlave){
                llaves++;
                celdasLibres++;
            }

            mapa[posJugador_fila][posJugador_columna] = '.';
            posJugador_fila = nuevaPosFila;
            posJugador_columna = nuevaPosColumna;
            mapa[posJugador_fila][posJugador_columna] = 'P';

            // Condicionales para que solo si es un movimiento valido sume pasos 
            if(movimiento == 'w' || movimiento == 'W') pasos++;
            else if(movimiento == 's' || movimiento == 'S') pasos++;
            else if(movimiento == 'a' || movimiento == 'A') pasos++;
            else if(movimiento == 'd' || movimiento == 'D') pasos++;
        }
    }
}

//Funcion que imprime el mapa del nivel cargado en la matriz
void imprimirTablero(char mat[FILAS][COL], int jugadorFila, int jugadorColumna){
    
    // Para que el puntero vaya al inicio de la consola y reescriba para evitar el parpadeo
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);

    int inicioFilas = jugadorFila - (VISTA_FILAS/2);
    int inicioColumnas = jugadorColumna - (VISTA_COL/2);

    if(inicioFilas < 0) inicioFilas = 0;
    if(inicioColumnas < 0) inicioColumnas = 0;
    if(inicioFilas > FILAS - VISTA_FILAS) inicioFilas = FILAS - VISTA_FILAS;
    if(inicioColumnas > COL - VISTA_COL) inicioColumnas = COL - VISTA_COL;

    for(int i = inicioFilas; i < inicioFilas + VISTA_FILAS; i++){
        for(int j = inicioColumnas; j < inicioColumnas + VISTA_COL; j++){
            if(mat[i][j]=='#') printf("# ");
            else printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}

//Funcion que lee el mapa del archivo de texto para guardarlo en la matriz del juego
void cargarMapaArchivo(char* nombreMapa, char mapa[FILAS][COL]){
    //vector de char que contendra linea leida
    char linea[256];

    //definimos puntero al archivo
    FILE *archivoTxt;

    //abrimos el archivo modo lectura
    archivoTxt = fopen(nombreMapa,"r");

    //verificamos existencia del archivo (terminamos pograma si no existe)
    if(archivoTxt == NULL){
        printf("\nError al abrir archivo modo lectura. ");
        exit(1);
    }

    //leemos el archivo linea por linea (mientras alla algo que leer o recorramos el tam 60)
    int filaMapa = 0;
    while(fgets(linea,sizeof(linea),archivoTxt) != NULL && filaMapa < FILAS){
        int colMapa = 0;
        for(int j=0; linea[j]!='\0' && linea[j] != '\n' && colMapa < COL; j++){
            //si es espacio lo ignoramos sino lo guardamos en matriz
            if(linea[j]!=' '){
                //no hacemos nada
                mapa[filaMapa][colMapa] = linea[j];
                colMapa++;
            }
            j++; //desplazamiento horizontal en el renglon
        }
        filaMapa++;
    }

    //cerramos el archivo
    fclose(archivoTxt);
}