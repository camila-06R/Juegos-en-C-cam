/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

#define FILAS 6
#define COLUMNAS 7

typedef struct {
    char tablero[FILAS][COLUMNAS];
    char jugador1;
    char jugador2;
    char jugadorActual;
} CuatroEnLinea;

void inicializarTablero(CuatroEnLinea *juego) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            juego->tablero[i][j] = ' ';
        }
    }
}

void imprimirTablero(CuatroEnLinea *juego) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("| %c ", juego->tablero[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < COLUMNAS; j++) {
        printf("--- ");
    }
    printf("\n");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("  %d ", j);
    }
    printf("\n");
}

int comprobarVictoria(CuatroEnLinea *juego) {
    // verifica si hay cuatro fichas del mismo jugador consecutivas en una misma fila horizontal del tablero
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (juego->tablero[i][j] == juego->jugadorActual &&
                juego->tablero[i][j + 1] == juego->jugadorActual &&
                juego->tablero[i][j + 2] == juego->jugadorActual &&
                juego->tablero[i][j + 3] == juego->jugadorActual) {
                return 1;
            }
        }
    }
      
//verifica si hay cuatro fichas del mismo jugador consecutivas en una misma columna del tablero    
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (juego->tablero[i][j] == juego->jugadorActual &&
                juego->tablero[i + 1][j] == juego->jugadorActual &&
                juego->tablero[i + 2][j] == juego->jugadorActual &&
                juego->tablero[i + 3][j] == juego->jugadorActual) {
                return 1;
            }
        }
    }
    // Comprueba diagonal de superior a inferior 
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (juego->tablero[i][j] == juego->jugadorActual &&
                juego->tablero[i + 1][j + 1] == juego->jugadorActual &&
                juego->tablero[i + 2][j + 2] == juego->jugadorActual &&
                juego->tablero[i + 3][j + 3] == juego->jugadorActual) {
                return 1;
            }
        }
    }
    // Comprueba diagonal de inferior a superior
    for (int i = 3; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (juego->tablero[i][j] == juego->jugadorActual &&
                juego->tablero[i - 1][j + 1] == juego->jugadorActual &&
                juego->tablero[i - 2][j + 2] == juego->jugadorActual &&
                juego->tablero[i - 3][j + 3] == juego->jugadorActual) {
                return 1;
            }
        }
    }
    return 0;
}

int dejarCaerFicha(CuatroEnLinea *juego, int columna) {
    if (columna < 0 || columna >= COLUMNAS || juego->tablero[0][columna] != ' ') {
        return 0; // Movimiento inválido
    }
    for (int i = FILAS - 1; i >= 0; i--) {
        if (juego->tablero[i][columna] == ' ') {
            juego->tablero[i][columna] = juego->jugadorActual;
            return 1; // Movimiento válido
        }
    }
    return 0; // Columna llena
}

void cambiarJugador(CuatroEnLinea *juego) {
    juego->jugadorActual = (juego->jugadorActual == juego->jugador1) ? juego->jugador2 : juego->jugador1;
}

void jugar(CuatroEnLinea *juego) {
    int columna;
    while (1) {
        imprimirTablero(juego);
        printf("Jugador %c, ingrese la columna (0 a 6): ", juego->jugadorActual);
        scanf("%d", &columna);

        if (dejarCaerFicha(juego, columna)) {
            if (comprobarVictoria(juego)) {
                imprimirTablero(juego);
                printf("¡Jugador %c gana!\n", juego->jugadorActual);
                break;
            }
            cambiarJugador(juego);
        } else {
            printf("Movimiento inválido. Inténtelo de nuevo.\n");
        }
    }
}

int main() {
    CuatroEnLinea juego;
    juego.jugador1 = 'X';
    juego.jugador2 = 'O';
    juego.jugadorActual = juego.jugador1;

    inicializarTablero(&juego);
    jugar(&juego);

    return 0;
}
