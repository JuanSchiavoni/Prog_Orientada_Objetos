#include "head.h"

void Grafo::insertar_vertice(const char& v) {
    this->V.push_back(v);
    cout << "Insertando vertice " << v << endl;
}

void Grafo::insertar_arista(const char& v1, const char& v2, const int& costo) {
    arista _arista = {{v1, v2}, costo};
    this->E.push_back(_arista);
    cout << "Insertando arista " << v1 << " -- " << v2 << "  || Costo: " << costo << endl;
}

void Grafo::inicial(const char& c, const char& v) {
    this->CE.nombres.insert({v, {c, '\0'}});
    this->CE.encabezados.insert({v, {1, c}});
}

void Grafo::combina(const char& c1, const char& c2) {
    // Cantidad de elementos de c1
    int cc1 = this->CE.encabezados[c1].first;
    // Cantidad de elementos de c2
    int cc2 = this->CE.encabezados[c2].first;
    // Primer elemento de c1
    char elemc1 = this->CE.encabezados[c1].second;
    // Primer elemento de c2
    char elemc2 = this->CE.encabezados[c2].second;

    if (cc1 > cc2) {
        // cc1 > cc2
        this->CE.encabezados[c1].first += this->CE.encabezados[c2].first;
        this->CE.encabezados[c2].first = 0;
        this->CE.encabezados[c2].second = '\0';

        this->CE.nombres[c1].second = c2;

        this->CE.nombres[c2].first = c1;
    } else {
        // cc1 <= cc2
        this->CE.encabezados[c2].first += this->CE.encabezados[c1].first;
        this->CE.encabezados[c1].first = 0;
        this->CE.encabezados[c1].second = '\0';

        this->CE.nombres[c2].second = c1;

        this->CE.nombres[c1].first = c2;
    }
}

char Grafo::encuentra(const char& v) {
    return this->CE.nombres[v].first;
}

void Grafo::kruskal() {
    int c = 0; // cantidad de vertices despues del bucle A
    int d = 0; // cantidad de aristas despues del bucle B

    // Asigna valor inicial a cada vertice
    for (auto itr = this->V.begin(); itr != this->V.end(); itr++) { //bucle A
        this->inicial(*itr, *itr);
        c++;
    }
    cout << "--> Cantidad de vertices: " << c << endl;

    // Asigna valor en la cola de prioridad grafo_ordenado
    for (auto itr = this->E.begin(); itr != this->E.end(); itr++) { //bucle B
        this->grafo_ordenado.push(*itr);
        d++;
    }
    cout << "--> Cantidad de aristas: " << d << endl;

    arista _arista; // Almacena primer elemento de la cola en la variable arista
    char conj_1;
    char conj_2;

    while (c >= 1) {
        _arista = this->grafo_ordenado.top();
        this->grafo_ordenado.pop();
        // componente 1 de la arista
        conj_1 = this->encuentra(_arista.first.first);
        // componente 2 de la arista
        conj_2 = this->encuentra(_arista.first.second);

        if (conj_1 != conj_2) {
            this->combina(conj_1, conj_2);
            this->arbol_minimo.push_back(_arista);
        }
        c--;
    }
}

void Grafo::mostrar_arbol_minimo() {
    cout << "--> Aristas del árbol abarcador de costo mínimo:" << endl;
    int costo = 0;
    for (auto e : arbol_minimo) {
        cout << "Arista: " << e.first.first << " - " << e.first.second << "  || Costo: " << e.second << endl;
        costo += e.second;
    }
    cout << "\nEl costo del arbol abarcador de costo minimo es " << costo << endl;
}

int main() {
    Grafo G;

    G.insertar_vertice('A');
    G.insertar_vertice('B');
    G.insertar_vertice('C');
    G.insertar_vertice('D');
    G.insertar_vertice('E');
    G.insertar_vertice('F');

    cout << "\n--------------------------------------------------------------------------------\n" << endl;

    G.insertar_arista('A', 'B', 6);
    G.insertar_arista('A', 'C', 1);
    G.insertar_arista('B', 'C', 5);
    G.insertar_arista('B', 'E', 3);
    G.insertar_arista('A', 'D', 5);
    G.insertar_arista('C', 'D', 5);
    G.insertar_arista('C', 'E', 6);
    G.insertar_arista('D', 'F', 2);
    G.insertar_arista('C', 'F', 4);
    G.insertar_arista('E', 'F', 6);

    cout << "\n--------------------------------------------------------------------------------\n" << endl;

    G.kruskal();

    cout << "\n--------------------------------------------------------------------------------\n" << endl;

    G.mostrar_arbol_minimo();

    cout << "\n--------------------------------------------------------------------------------\n" << endl;

    return 0;
}

