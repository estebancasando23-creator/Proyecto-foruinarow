#include <iostream>
using namespace std;

void t_inicial(string tablero[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            tablero[i][j] = "_|";
        }
    }
}
void mostrar_t(string tablero[6][7]) {
    cout << "\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << tablero[i][j];
        }
        cout<<endl;
    }
    for (int j=0; j<7; j++) cout <<j+ 1<<" ";
    cout<<endl;
}
bool validacion_col(string tablero[6][7], int columna) {
    if (columna<1||columna>7||tablero[0][columna-1] != "_|"){
        return false;
    }else{
        return true;
    }
}
int colocacion_ficha(string tablero[6][7],int columna,string jugador_actual) {
    for (int i=5; i>=0; i--) {
        if (tablero[i][columna-1] == "_|") {
            tablero[i][columna-1] =jugador_actual;
            return i;
        }
    }
    return -1;
}
bool verificacion_vic(string tablero[6][7], string jugador_actual) {
    for (int i=0; i<6; i++) {
        for (int j= 0; j <7; j++) {
            if (tablero[i][j] == jugador_actual) {
                
                if (j <= 3 && tablero[i][j +1] == jugador_actual &&
                    tablero[i][j +2] == jugador_actual && tablero[i][j+3] == jugador_actual)
                    return true;

                
                if (i <= 2 && tablero[i+1][j] == jugador_actual &&
                    tablero[i+ 2][j] == jugador_actual && tablero[i+3][j] ==jugador_actual)
                    return true;

                
                if (i <= 2 && j <= 3 && tablero[i +1][j+1] == jugador_actual &&
                    tablero[i+2][j+2] == jugador_actual && tablero[i+3][j+3] == jugador_actual)
                    return true;

                
                if (i >= 3 && j <= 3 && tablero[i-1][j+ 1] == jugador_actual &&
                    tablero[i-2][j+ 2] == jugador_actual && tablero[i-3][j+3] == jugador_actual)
                    return true;
            }
        }
    }
    return false;
}
string alternancia_turno(string jugador_actual) {
    return (jugador_actual == "X ") ? "O " : "X ";
}
bool verificacion_empate(string tablero[6][7]) {
    for (int j = 0; j < 7; j++) {
        if (tablero[0][j] == "_|") return false;
    }
    return true;
}

int main() {
    string tablero[6][7];
    string jugador_actual = "X ";
    bool juegoTerminado = false;

    t_inicial(tablero);

    while (true) {

        cout << " Nuevo juego iniciado!";
        while (juegoTerminado== false) {
            mostrar_t(tablero);
            string entrada;
            int columna;
            
            cout <<"En que columna pondra la ficha (1 al 7 o 'R' para reiniciar), jugador de "<<jugador_actual<<": ";
            cin >> entrada;
            if (entrada == "R" || entrada == "r") {
                cout <<endl<<"Reiniciando el juego..."<<endl;
                t_inicial(tablero);
                jugador_actual = "X ";
                break;
            }
            try { columna = stoi(entrada);
            } catch (...) {
                cout << "Entrada inválida. Por favor ingrese un número del 1 al 7 o 'R' para reiniciar." << endl;
                continue; 
            }
            if (validacion_col(tablero, columna)== false) {
                cout << "Columna inválida o llena. Intente nuevamente."<<endl;
                continue;
            }
            colocacion_ficha(tablero,columna,jugador_actual);
            if (verificacion_vic(tablero,jugador_actual)) {
                mostrar_t(tablero);
                cout <<endl<<"El jugador " << jugador_actual << " ha ganado.";
                juegoTerminado = true;
            } else if (verificacion_empate(tablero)) {
                mostrar_t(tablero);
                cout <<endl<<"quedaron empate, el tablero está lleno.";
                juegoTerminado=true;
            } else {
                jugador_actual=alternancia_turno(jugador_actual);
            }
        }
        string opcion;
        cout << "\n¿Desea jugar de nuevo? (si/no): ";
        cin >> opcion;
        if (opcion == "SI" || opcion == "si"|| opcion == "Si") {
            t_inicial(tablero);
            continue;
        } else {
            cout<<"Gracias por jugar";
            break;
        }
    }
    return 0;
}