#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h> 

using namespace std;

void textoVerde() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main() {
    string nombreArchivo = "texto.txt";
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    string palabra;
    cout << "Ingrese la palabra a buscar: ";
    getline(cin, palabra);
    transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
    
    string linea;
    int nLinea = 0;
    int total = 0;
    bool repetidos = false;  

    cout << "\nResultados de la busqueda:\n" << endl;
    
    while (getline(archivo, linea)) {
        nLinea++;
        string lineaOriginal = linea; 
        string lineaMinusculas = linea;
        transform(lineaMinusculas.begin(), lineaMinusculas.end(), lineaMinusculas.begin(), ::tolower);
        
        size_t pos = 0;
        size_t lastPos = 0;
        bool lRepetidas = false;
        
        while ((pos = lineaMinusculas.find(palabra, pos)) != string::npos) {
            if (!lRepetidas) {
                cout << "Linea " << nLinea << ": ";
                lRepetidas = true;
                repetidos = true;  // Actualizado para usar 'repetidos'
            }
            
            cout << lineaOriginal.substr(lastPos, pos - lastPos);
            
            textoVerde();
            cout << lineaOriginal.substr(pos, palabra.length());
            resetColor();
            
            total++;
            pos += palabra.length();
            lastPos = pos;
        }

        if (lRepetidas) {
            if (lastPos < lineaOriginal.length()) {
                cout << lineaOriginal.substr(lastPos);
            }
            cout << endl;
        }
    }
    
    if (!repetidos) {  
        cout << "No se encontraron repeticiones." << endl;
    } else {
        cout << "\nTotal de repeticiones encontradas: ";
        textoVerde();
        cout << total << endl;
        resetColor();
    }
    
    archivo.close();
    return 0;
}
