#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

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
    int total = 0;
    bool repetidos = false;

    cout << "\nResultados de la busqueda:\n" << endl;
    
    while (getline(archivo, linea)) {
        string lineaMinusculas = linea;
        transform(lineaMinusculas.begin(), lineaMinusculas.end(), lineaMinusculas.begin(), ::tolower);
        
        size_t pos = 0;
        bool lRepetidas = false;
        
        while ((pos = lineaMinusculas.find(palabra, pos)) != string::npos) {
            if (!lRepetidas) {
                lRepetidas = true;
                repetidos = true;
            }
            total++;
            pos += palabra.length();
        }

        if (lRepetidas) {
            cout << linea << endl;
        }
    }
    
    if (!repetidos) {
        cout << "No se encontraron repeticiones." << endl;
    } else {
        cout << "\nTotal de repeticiones encontradas: " << total << endl;
    }
    
    archivo.close();
    return 0;
}
