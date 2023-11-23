#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int vertices = 0;
const int MaxVerstappen = 100;
int matriz[MaxVerstappen][MaxVerstappen];
int grado[MaxVerstappen];
bool visitado[MaxVerstappen];

// Funcion encargada de leer la matriz de adyacencia de un archivo dado
void Input() {
    ifstream inputFile("matriz.txt");

    if (!inputFile) {
        cerr << "Error abriendo el archivo." << endl;
        return;
    }

    inputFile >> vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            inputFile >> matriz[i][j];
            if (matriz[i][j] != 0) {
                grado[i]++;
            }
        }
    }

    inputFile.close();
}

// Algoritmo Depth First Search. Encargado de encontrar si el grafo es conexo
void DFS(int v, vector<int>& componente) {
    visitado[v] = true;
    componente.push_back(v);

    for (int i = 0; i < vertices; i++) {
        if (matriz[v][i] && !visitado[i]) {
            DFS(i, componente);
        }
    }
}

// Encuentra el numero de componentes conexos de un dado grafo
// y de cuales vertices se conforma cada uno de ellos
vector<vector<int>> ComponentesConexos() {
    vector<vector<int>> componentes;

    for (int i = 0; i < vertices; i++) {
        visitado[i] = false;
    }

    for (int i = 0; i < vertices; i++) {
        if (!visitado[i]) {
            vector<int> componente;
            DFS(i, componente);
            componentes.push_back(componente);
        }
    }

    return componentes;
}

// Funcion para escribir el resultado en un archivo de salida
void Output() {
    freopen("output.txt", "w", stdout);
    cout << "Matriz de adyacencia del grafo dado" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    vector<vector<int>> componentes = ComponentesConexos();

    if (componentes.size() == 1) {
        cout << "El grafo proporcionado es conexo." << endl;
    } else {
        cout << "El grafo proporcionado no es conexo." << endl;
        cout << "Número de componentes conexos: " << componentes.size() << endl;
        cout << "Vértices en cada componente:" << endl;
        int componenteNum = 1;
        for (const auto& componente : componentes) {
            cout << "Componente " << componenteNum << ": ";
            for (int v : componente) {
                cout << v << " ";
            }
            cout << endl;
            componenteNum++;
        }
    }
    fclose(stdout); // Cerrar el archivo de salida
}

int main() {
    Input();
    Output();
    return 0;
}
