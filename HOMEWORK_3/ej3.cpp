#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <fstream>
using namespace std;

//creo la clase para generar las matrices con double y strings.
class GeneradorDatos {
private:
    vector<double> vecDoubles;
    vector<string> palabras;
    vector<vector<int>> listas;

public:
    template<typename T>
    void agregar(const T& valor) {
        if constexpr (is_same_v<T, double>) {
            vecDoubles.push_back(valor);
        } else if constexpr (is_same_v<T, string>) {
            palabras.push_back(valor);
        }
    }

    void agregarLista(const vector<int>& lista) {
        listas.push_back(lista);
    }

    const vector<double>& getDoubles() const {
        return vecDoubles; }
    const vector<string>& getPalabras() const {
        return palabras; }
    const vector<vector<int>>& getListas() const {
        return listas; }
};

//creo clase para generar el json.
class GeneradorJSON {
private:
    const GeneradorDatos& datos;

    //primero hago los metodos para imprimir por terminal y despues hago los metodos para crear el json.
    void imprimirVectorDouble(const vector<double>& v) const {
        cout << "  \"vec_doubles\" : [";
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i];
            if (i != v.size() - 1) cout << ", ";
        }
        cout << "]," << endl;
    }

    void imprimirVectorString(const vector<string>& v) const {
        cout << "  \"palabras\" : [";
        for (size_t i = 0; i < v.size(); ++i) {
            cout << "\"" << v[i] << "\"";
            if (i != v.size() - 1) cout << ", ";
        }
        cout << "]," << endl;
    }

    void imprimirMatrizEnteros(const vector<vector<int>>& listas) const {
        cout << "  \"listas\" : [" << endl;
        for (size_t i = 0; i < listas.size(); ++i) {
            cout << "                [";
            for (size_t j = 0; j < listas[i].size(); ++j) {
                cout << listas[i][j];
                if (j != listas[i].size() - 1) cout << ", ";
            }
            cout << "]";
            if (i != listas.size() - 1) cout << "," << endl;
            else cout << endl;
        }
        cout << "             ]" << endl;
    }

public:
    GeneradorJSON(const GeneradorDatos& datos_) : datos(datos_) {}

    void imprimirJSON() const {
        cout << "{" << endl;
        imprimirVectorDouble(datos.getDoubles());
        imprimirVectorString(datos.getPalabras());
        imprimirMatrizEnteros(datos.getListas());
        cout << "}" << endl;
    }

    void generarArchivoJSON(const string& nombreArchivo) const {
        ofstream ofs(nombreArchivo);
        if (!ofs) {
            cerr << "Error al abrir el archivo para escritura." << endl;
            return;
        }

        ofs << "{" << endl;

        //genero para doubles, strings y las listas.
        ofs << "  \"vec_doubles\" : [";
        const auto& vd = datos.getDoubles();
        for (size_t i = 0; i < vd.size(); ++i) {
            ofs << vd[i];
            if (i != vd.size() - 1) ofs << ", ";
        }
        ofs << "]," << endl;

        ofs << "  \"palabras\" : [";
        const auto& ps = datos.getPalabras();
        for (size_t i = 0; i < ps.size(); ++i) {
            ofs << "\"" << ps[i] << "\"";
            if (i != ps.size() - 1) ofs << ", ";
        }
        ofs << "]," << endl;

        ofs << "  \"listas\" : [" << endl;
        const auto& listas = datos.getListas();
        for (size_t i = 0; i < listas.size(); ++i) {
            ofs << "                [";
            for (size_t j = 0; j < listas[i].size(); ++j) {
                ofs << listas[i][j];
                if (j != listas[i].size() - 1) ofs << ", ";
            }
            ofs << "]";
            if (i != listas.size() - 1) ofs << "," << endl;
            else ofs << endl;
        }
        ofs << "             ]" << endl;

        ofs << "}" << endl;
        ofs.close();
    }
};

int main() {
    GeneradorDatos datos;

    //prubeo con ele ejemplo que esta en la consigna.
    datos.agregar(1.3);
    datos.agregar(2.1);
    datos.agregar(3.2);
    datos.agregar(string("Hola"));
    datos.agregar(string("Mundo"));
    datos.agregarLista({1, 2});
    datos.agregarLista({3, 4});

    //imprimo por terminal y genero el json con los metodos de mi clase.
    GeneradorJSON generador(datos);
    generador.imprimirJSON();
    generador.generarArchivoJSON("archivo.json");
    return 0;
}