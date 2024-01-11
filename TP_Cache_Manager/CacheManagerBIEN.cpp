#include <iostream>
#include "CMBIEN.h"

using namespace std;

class Student{
public:
    int id;
    int value;
    const char* data;

    static const string class_name; // Cada clase tiene un static llamado : class_name

    Student(int _key, int _value, const char* _data):id( _key), value( _value), data( _data){}
    ~Student(){};
};


//Sobrecargo escriben la clase estudiante
ostream& operator <<(ostream &o, const Student s){
          o << "Estudiante: " << s.id << ", " << s.value << ", " << s.data << endl;
          return o;
}



const string Student::class_name = "Estudiante";

int main(){
    CacheManager <Student> my_cache(3);
    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;

    my_cache.set("0 ", Student (0 ,22 , "student 1" ));
    my_cache.set("1 ", Student (1 ,23 , "student 2" ));
    my_cache.set("2 ", Student (2 ,25 , "student 3" ));
    my_cache.set("3 ", Student (3 ,29 , "student 4" ));

    cout << my_cache;
    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<< UPDATE <<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;

    my_cache.set ("2 ", Student(22, 222, "EZE"));
    cout << my_cache;

    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;
    my_cache.set ("2 ", Student (2, 25, "EZE"));

    cout << my_cache;
    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;

    my_cache.set ("9 ", Student (1, 5, "Nine"));
    my_cache.set ("9 ", Student (1, 5, "Nine"));
    cout << my_cache;
    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;

    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;
    my_cache.get ("3 ", Student (3 ,29 , "student 4" ));
    my_cache.get ("14 ", Student (14 ,140 , "student 14" ));

    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;
    cout << my_cache;

    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;
    my_cache.get ("1 ", Student (1 ,23 , "student 2" ));

    cout << "<<<<<< <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<< <<<<<<\n" << endl;
    cout << my_cache;

return 0;
}




