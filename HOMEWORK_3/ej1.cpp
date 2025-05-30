#include <iostream>
#include <fstream>
#include <memory>
#include <string>

using namespace std;

//con esta clase represento un instante de tiempo con métodos de serialización y deserialización.
class Tiempo {
private:
    float instante;

public:
    Tiempo(float instante) : instante(instante) {}

    float getInstante() const {
        return instante;
    }
    void setInstante(float i) {
        instante = i;
    }
    void serializar(ostream& os) const {
        os.write(reinterpret_cast<const char*>(&instante), sizeof(instante));
    }
    void deserializar(istream& is) {
        is.read(reinterpret_cast<char*>(&instante), sizeof(instante));
    }
    void imprimir() const {
        cout << "Tiempo: " << instante << " s" << endl;
    }};

//es la clase abstracta que me pide el uml para representar la medicion con un tiempo asociado.
class MedicionBase {
protected:
    unique_ptr<Tiempo> tiempoMedicion;

public:
    MedicionBase(float t) : tiempoMedicion(make_unique<Tiempo>(t)) {}

    virtual ~MedicionBase() = default;

    virtual void imprimir() const = 0;

    virtual void serializar(ostream& os) const = 0;

    virtual void deserializar(istream& is) = 0;

    const Tiempo& getTiempo() const {
        return *tiempoMedicion;
    }
};

//con la clase posicion que hereda de medicionbase hago una posicion en un momento de tiempo.
class Posicion : public MedicionBase {
private:
    float x, y, z;

public:
    Posicion(float x_, float y_, float z_, float t)
        : MedicionBase(t), x(x_), y(y_), z(z_) {}

    Posicion() : MedicionBase(0.0f), x(0), y(0), z(0) {}

    void imprimir() const override {
        cout << "Posicion: (" << x << ", " << y << ", " << z << ") ";
        tiempoMedicion->imprimir();
    }

    void serializar(ostream& os) const override {
        os.write(reinterpret_cast<const char*>(&x), sizeof(x));
        os.write(reinterpret_cast<const char*>(&y), sizeof(y));
        os.write(reinterpret_cast<const char*>(&z), sizeof(z));
        tiempoMedicion->serializar(os);
    }

    void deserializar(istream& is) override {
        is.read(reinterpret_cast<char*>(&x), sizeof(x));
        is.read(reinterpret_cast<char*>(&y), sizeof(y));
        is.read(reinterpret_cast<char*>(&z), sizeof(z));
        tiempoMedicion = make_unique<Tiempo>(0.0f);
        tiempoMedicion->deserializar(is);
    }
};

//hago parecido a la posicion pero con la funcion especifica de presion que muestra las presiones. 
class Presion : public MedicionBase {
private:
    float estatica, dinamica;

public:
    Presion(float estatica_, float dinamica_, float t)
        : MedicionBase(t), estatica(estatica_), dinamica(dinamica_) {}

    Presion() : MedicionBase(0.0f), estatica(0), dinamica(0) {}

    void imprimir() const override {
        cout << "Presion estatica: " << estatica << ", dinamica: " << dinamica << " ";
        tiempoMedicion->imprimir();
    }

    void serializar(ostream& os) const override {
        os.write(reinterpret_cast<const char*>(&estatica), sizeof(estatica));
        os.write(reinterpret_cast<const char*>(&dinamica), sizeof(dinamica));
        tiempoMedicion->serializar(os);
    }

    void deserializar(istream& is) override {
        is.read(reinterpret_cast<char*>(&estatica), sizeof(estatica));
        is.read(reinterpret_cast<char*>(&dinamica), sizeof(dinamica));
        tiempoMedicion = make_unique<Tiempo>(0.0f);
        tiempoMedicion->deserializar(is);
    }
};

//aca cuardo muchas mediciones y esta es la clase que me va a permitir serializarlas y decerializarlas.
class SaveFlightData {
public:
    void guardar(const Posicion& pos, const Presion& pres, const string& archivo) {
        ofstream os(archivo, ios::binary);
        if (!os) {
            cerr << "No se pudo abrir el archivo para escritura\n";
            return;
        }

        pos.serializar(os);
        pres.serializar(os);
        os.close();
    }

    void cargar(Posicion& pos, Presion& pres, const string& archivo) {
        ifstream is(archivo, ios::binary);
        if (!is) {
            cerr << "No se pudo abrir el archivo para lectura\n";
            return;
        }

        pos.deserializar(is);
        pres.deserializar(is);
        is.close();
    }
};

int main() {
    //creo objetos como los que pide la consigna y pruebo imprimir los originales y los recuperados.
    Posicion posicion(-34.6f, -58.4f, 950.0f, 5.3f);
    Presion presion(101.3f, 5.8f, 6.1f);

    cout << "Original:\n";
    posicion.imprimir();
    presion.imprimir();
    SaveFlightData saver;
    saver.guardar(posicion, presion, "datos_vuelo.dat");

    Posicion posicion2;
    Presion presion2;
    saver.cargar(posicion2, presion2, "datos_vuelo.dat");
    cout << "\nRecuperado:\n";
    posicion2.imprimir();
    presion2.imprimir();
    return 0;}