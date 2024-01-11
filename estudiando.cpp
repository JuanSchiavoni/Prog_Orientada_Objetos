#include <iostream>

using namespace std;

class Costo {
    int valor;
public:
    void setValor(int valor) {
        this->valor= valor;
    }
    Costo& incremento() {
        valor++;
        return *this;
    }
};

int main() {
    Costo c;
    c.setValor(20);
    c.incremento();
}