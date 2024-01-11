#include <iostream>

using namespace std;

class Punto {

   //private (Default)
   int m_x; // X coordinate
   int m_y; // Y coordiante

public:
    Punto () {
        m_x = 0;
        m_y = 0;
        cout << "objeto Punto inicializado" << endl;
    }
    Punto (int, int); //otro constriuctor
//resto de las funciones
};

Punto::Punto(int x, int y) {
    m_x = x;
    m_y = y;
}


int main () {

    Punto p1;
    Punto *pPto;
    pPto = new Punto(2, 4);
    delete pPto;

    return 0;
}
