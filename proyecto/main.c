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

    int totalCeldas = FILAS * COL;
    monedasTotales = contarCaracteres(&mapa[0][0 ], totalCeldas, 'C'); 
    int celdasLibres = contarCeldasLibres(&mapa[0][0], totalCeldas);
    while(1){
        imprimirTablero(mapa, posJugador_fila, posJugador_columna);
        printf("Pasos: %d\n", pasos);
        printf("Celdas libres: %d\n", celdasLibres);
        printf("Monedas recogidas: %d/%d\n", monedasRecogidas, monedasTotales);
        movimiento = _getch(); 

        int nuevaPosFila = posJugador_fila;
        int nuevaPosColumna = posJugador_columna;

        if(movimiento == 'w' || movimiento == 'W') nuevaPosFila--;
        else if(movimiento == 's' || movimiento == 'S') nuevaPosFila++;
        else if(movimiento == 'a' || movimiento == 'A') nuevaPosColumna--;
        else if(movimiento == 'd' || movimiento == 'D') nuevaPosColumna++;
        else if(movimiento == 'q' || movimiento == 'Q') break;

        int valido = validarMovimiento(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna);
        
        if(valido){
            int tocoSalida =detectarObjeto(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna, 'S');
            if(tocoSalida){
                mapa[posJugador_fila][posJugador_columna] = '.';
                posJugador_fila = nuevaPosFila;
                posJugador_columna = nuevaPosColumna;
                mapa[posJugador_fila][posJugador_columna] = 'P';
                imprimirTablero(mapa, posJugador_fila, posJugador_columna);
                printf("Nivel 1\n");
                printf("Pasos: %d\n", pasos);
                printf("Monedas recogidas: %d/%d\n", monedasRecogidas, monedasTotales);
                printf("\n¡Felicidades! Llegaste a la salida!\n");
                break;
            }

            int tocoMoneda = detectarObjeto(&mapa[0][0], COL, nuevaPosFila, nuevaPosColumna, 'C');
            if(tocoMoneda){
                monedasRecogidas++;
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