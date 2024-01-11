#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<pair<char, char>, int> arista; //v1, v2 y costo entre ellos

typedef struct _Conjunto_CE {
    map<char, pair<char, char>> nombres;
    map<char, pair<int, char>> encabezados;
} Conjunto_CE;

class MenorValor {
public:
    bool operator()(arista e1, arista e2) {
        return e1.second > e2.second;
    }
};

typedef priority_queue<arista, vector<arista>, MenorValor> arbol;

class Grafo {
private:
    vector<char> V; // Conjunto de vertices
    vector<arista> E; // Conjunto de aristas
    Conjunto_CE CE; // Estructura para el analisis de adyacencias
    arbol grafo_ordenado; // Cola de prioridad
    vector<arista> arbol_minimo; // Arbol minimo

public:
    Grafo() {} // Constructor
    ~Grafo() {} // Destructor
    void mostrar_arbol_minimo();
    void insertar_vertice(const char&); // Guarda los vertices en el conjunto V
    void insertar_arista(const char&, const char&, const int&); // Guarda aristas en el conjunto E
    void inicial(const char&, const char&); // Inicializa a las estructuras de conjunto combina_encuentra
    void combina(const char&, const char&); // Combina las aristas que se encuentran formando el arbol
    char encuentra(const char&); // Encuentra vertices dentro del conjunto_CE
    void kruskal(); // Algoritmo generador del arbol recubridor minimo
};
