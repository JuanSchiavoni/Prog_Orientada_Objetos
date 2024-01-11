#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <utility>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

//variables globales
int i = -1;
int c = 0;
/************************************************************************************************************************************/


//Clase cache
template <class T>
class CacheManager{
    int capacity;
    map<string, pair<T, int>>cache_data; //map donde almaceno la cache
    void write_file(string, T); //Funcion que escribe en el archivo

public:
    CacheManager(int);//constructor
    ~CacheManager();//destructor
    T get(string, T); //Funcion que va a buscar los objetos y retornar
    void set(string, T); //Funcion que inserta claves y objetos
    template<class Q> friend ostream& operator<<(ostream&, CacheManager<Q>);
    int reemplazo(string, T);    //Funcion de reemplazos en el archivo
};


/************************************************************************************************************************************/


//Sobrecargo para mostrar la cache
template <class Q>
ostream& operator<<(ostream& os, CacheManager<Q> c){
    os << "Nivel de uso\t\tKey\t\tObjeto\n";
    for(auto it =  c.cache_data.begin(); it != c.cache_data.end(); it++){
        os <<  (*it).second.second  << "                    " << (*it).first << "\t\t"  << (*it).second.first << endl;
    }
return os;
}


/************************************************************************************************************************************/


//Funcion que guarda la capacidad del cache
template <class T>
CacheManager<T>::CacheManager(int cap){
    capacity = cap;
}


/************************************************************************************************************************************/


template <class T>
CacheManager<T>:: ~CacheManager(){}


/************************************************************************************************************************************/


// Función que escribe en el archivo
template <class T>
void CacheManager<T>::write_file(string key, T obj){
    char k[key.length() + 1];
    strcpy(k, key.c_str());
    int claveInt = -1;
    const char* esp = "\n";

    ofstream Archivo("OBJETOS.txt", ios::app);
    if (!Archivo){
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    if (c > 0){
        int replace = reemplazo(key, obj);
        if (replace == 1){
            return;
        } else {
            Archivo << k;
            Archivo << obj;
            c++;
        }
    } else{
        Archivo << k;
        Archivo << obj;
        c++;
    }
}


/************************************************************************************************************************************/


//Funcion de reemplazos en el archivo
template <class T>
int CacheManager<T>::reemplazo(string key, T obj) {
    ifstream Archivo("OBJETOS.txt");
    if (!Archivo){
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    // Leer el archivo línea por línea
    vector<string> lines;
    string line;
    while (getline(Archivo, line)){
        lines.push_back(line);
    }
    Archivo.close();
    ofstream NuevoArchivo("OBJETOS.txt");
    if (!NuevoArchivo){
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    bool reemplazado = false;
    for (const string& currentLine : lines){
        size_t keyPos = currentLine.find(key);
        if (keyPos == string::npos){
            // La línea no contiene la clave, se mantiene igual
            NuevoArchivo << currentLine << endl;
        } else{
            // La línea contiene la clave, se reemplaza con el nuevo objeto
            NuevoArchivo << key + T::class_name + ": " + to_string(obj.id) + ", " + to_string(obj.value) + ", " + obj.data << endl;
            reemplazado = true;
        }
    }
    // Si no se reemplazó ninguna línea, se agrega el nuevo objeto al final del archivo
    NuevoArchivo.close();
return reemplazado ? 1 : 0;
}


/************************************************************************************************************************************/


//Funcion que inserta claves y objetos
template<class T>
void CacheManager<T>::set(string key, T obj){
    int lru; //Declaro la variable lru
    int mru = 0;
    i++; //Aumento el contador
    char n[key.length() + 1]; //Array de char donde voy a ir ingresando las key

    strcpy(n, key.c_str());

    cout << "Insertando el obj: " << key << "|| " << obj << endl;

    //inserto en el archivo
    write_file(key, obj);

    //si la cache no esta llena
    if(cache_data.size() != capacity){
    for(auto t = cache_data.begin(); t != cache_data.end(); t++){ //recorro, si la clave ya se encuentra, actualizo
        if(t->first == key){
            t->second.first = obj;
            t->second.second = i;
            return;
        }
    }

    cache_data.insert(make_pair(key, make_pair(obj,i))); //si la cache no esta llena y la clave no se encuentra, inserto la nueva

    } else{
    //Si la cache esta llena
        for(auto t = cache_data.begin(); t != cache_data.end(); t++){ //recorro la cache, si la clave ya se encuentra, actualizo
            if(t->first == key){
                mru = t->second.second;      //Inicializo la variable lru
                for(auto j = cache_data.begin(); j != cache_data.end(); j++){ // busco el MRU
                    if(mru <= j->second.second){
                    mru = j->second.second;
                    }
                }
                t->second.first = obj;
                t->second.second = mru+1;
                return;
           }
        }

        auto k = cache_data.begin(); //Defino k con el principio de la cache
        lru = k->second.second;      //Inicializo la variable lru

        for(auto j = cache_data.begin(); j != cache_data.end(); j++){ //obtengo el LRU mas chico
            if(lru >= j->second.second){
                lru = j->second.second;
            }
        }

        for(auto h = cache_data.begin(); h != cache_data.end(); h++){  // busco el MRU
            if(mru <= h->second.second){
                mru = h->second.second;
            }
        }

        for(auto m = cache_data.begin(); m != cache_data.end(); m++){ //borro la clave con el lru e inserto la nueva
            if(m->second.second == lru){
                cache_data.erase(m);
                cache_data.insert(make_pair(key, make_pair(obj,i)));
                return;
            }
        }
    }
}


/************************************************************************************************************************************/


//Funcion que va a buscar los objetos y retornar
template<class T>
T CacheManager<T>::get(string key, T obj){
    int k = stoi(key);  // Convierto la clave a int
    int lru;
    int mru = 0;
    int claveInt = -1;
    char clave;
    cout << "Buscando el obj con Key: " << key << "|| " << obj << endl;
    // Busco la key en la cache
    for(auto t = cache_data.begin(); t != cache_data.end(); t++){ //recorro la cache, si la clave ya se encuentra, actualizo
            if(t->first == key){
                cout << "La clave existe en la cache\n" << endl;
                mru = t->second.second;      //Inicializo la variable lru
                for(auto j = cache_data.begin(); j != cache_data.end(); j++){ // busco el MRU
                    if(mru <= j->second.second){
                    mru = j->second.second;
                    }
                }
                t->second.first = obj;
                t->second.second = mru+1;
                return obj;
            }
    }

    // Busco la key en el archivo
    ifstream Archivo("OBJETOS.txt"); // Abro el archivo para leer (modo de texto por defecto)
    if (!Archivo){
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    } else{
        string line;
        while (getline(Archivo, line)) {
            if (line.find(key) != string::npos) {
                cout << "La clave NO existe en la cache pero SI existe en el archivo\n" << endl;

                auto k = cache_data.begin(); //Defino k con el principio de la cache
                lru = k->second.second;      //Inicializo la variable lru

                for(auto j = cache_data.begin(); j != cache_data.end(); j++){ //obtengo el LRU mas chico
                    if(lru >= j->second.second){
                        lru = j->second.second;
                    }
                }

                for(auto h = cache_data.begin(); h != cache_data.end(); h++){  // busco el MRU
                    if(mru <= h->second.second){
                        mru = h->second.second;
                    }
                }

                for(auto m = cache_data.begin(); m != cache_data.end(); m++){ //borro la clave con el lru e inserto la nueva
                    if(m->second.second == lru){
                        cache_data.erase(m);
                        cache_data.insert(make_pair(key, make_pair(obj,mru+1)));
                        return obj;
                    }
                }
            }
        }
        Archivo.close();
    }
    cout << "La clave no existe en la cache y tampoco en el archivo\n" << endl;
return obj;
}
