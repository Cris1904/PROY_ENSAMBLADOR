#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "mapas.h"

#define VISTA_FILAS 20
#define VISTA_COL 20

extern int validarMovimiento(char* mapa, int columnas, int nuevaFila, int nuevaColumna);
extern int contarCaracteres(char* mapa, int columnas, int caracter);
extern int contarCeldasLibres(char* mapa, int totalCeldas);
extern int detectarObjeto(char* mapa, int columnas, int filaJugador, int columnaJugador, char objeto);
extern int calcularPuntaje(int monedas, int pasos, int niveles);

void imprimirTablero(char mat[FILAS][COL], int jugadorFila, int jugadorColumna){
    system("cls");
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

int main(){
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

            pasos++;
        }
    }
    return 0;
}