#include <iostream>
#include <vector>

using namespace std;

class Persona{
private:
    string nombre;
public:
    Persona() {} // Constructor predeterminado
    Persona(string n) {nombre=n;}
    string getNombre() {return nombre;}
};

class Oferta {
private:
    float monto;
    Persona ofertante;
public:
    Oferta(float m, Persona p) {
        monto = m;
        ofertante = p;}
    float getMonto() {return monto;}
    Persona getOfertante() {return ofertante;}
};

class Lote {
private:
    int numero;
    string nombre;
    vector<Oferta> ofertas;
public:
    Lote(int n, string nom) {
        numero = n;
        nombre = nom;
    }
    void agregarOferta(Oferta o) {ofertas.push_back(o);}
    Oferta getOfertaMasGrande() {
        if (ofertas.size() == 0) {throw "No hay ofertas para este lote";}
        Oferta max = ofertas[0];
        for (int i = 1; i < ofertas.size(); i++) {
            if (ofertas[i].getMonto() > max.getMonto()) {
                max = ofertas[i];
            }
        }
        return max;
    }
    string getNombre() {return nombre;}
};

class Subasta {
private:
    vector<Lote> lotes;
public:
    void agregarLote(Lote l) {lotes.push_back(l);}
    int getCantidadLotes() {return lotes.size();}
};


int main() {
    // Creamos 4 personas
    Persona persona1("lucas");
    Persona persona2("German");
    Persona persona3("Alfredo");
    Persona persona4("Roberto");

    // Creamos 4 ofertas para 3 lotes
    Oferta oferta1_1(100, persona1);
    Oferta oferta1_2(130, persona2);
    Oferta oferta1_3(105, persona3);
    Oferta oferta1_4(110, persona4);

    Oferta oferta2_1(1500,persona2);
    Oferta oferta2_2(2360,persona1);
    Oferta oferta2_3(1790,persona3);
    Oferta oferta2_4(2000,persona4);

    Oferta oferta3_1(700,persona2);
    Oferta oferta3_2(690,persona1);
    Oferta oferta3_3(680,persona3);
    Oferta oferta3_4(650,persona4);

    // Creamos 3 lotes y agregamos las ofertas
    Lote l1(1, "Reloj");
    l1.agregarOferta(oferta1_1);
    l1.agregarOferta(oferta1_2);
    l1.agregarOferta(oferta1_3);
    l1.agregarOferta(oferta1_4);

    Lote l2(2, "Cofre");
    l2.agregarOferta(oferta2_1);
    l2.agregarOferta(oferta2_2);
    l2.agregarOferta(oferta2_3);
    l2.agregarOferta(oferta2_4);

    Lote l3(3, "Moneda Antigua");
    l3.agregarOferta(oferta3_1);
    l3.agregarOferta(oferta3_2);
    l3.agregarOferta(oferta3_3);
    l3.agregarOferta(oferta3_4);

    // Creamos una subasta y agregamos el lote
    Subasta s1;
    s1.agregarLote(l1);
    s1.agregarLote(l2);
    s1.agregarLote(l3);

    // Mostramos la cantidad de lotes de la subasta
    cout << "La subasta tiene " << s1.getCantidadLotes() << " lotes" << endl;

    // Mostramos la oferta más grande del lote
    cout << "La oferta mas grande para el lote " << l1.getNombre() << " es de " << l1.getOfertaMasGrande().getMonto() << endl;
    cout << "La oferta mas grande para el lote " << l2.getNombre() << " es de " << l2.getOfertaMasGrande().getMonto() << endl;
    cout << "La oferta mas grande para el lote " << l3.getNombre() << " es de " << l3.getOfertaMasGrande().getMonto() << endl;

    return 0;
}
