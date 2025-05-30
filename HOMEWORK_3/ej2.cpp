#include <iostream>
#include <cmath>

using namespace std;

//creo el punto con sus coordenadas, getters y setters.
class Punto {
private:
    float x, y;

public:
    Punto(float x = 0.0f, float y = 0.0f)
        : x(x), y(y) {}

    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }
    void setX(float x_) {
        x = x_;
    }
    void setY(float y_) {
        y = y_;
    }};

//hago lo mismo con el circulo que tiene centro en el punto anterior.
class Circulo {
private:
    Punto centro;
    float radio;

public:
    Circulo(Punto c, float r)
        : centro(c), radio(r) {}

    Punto getCentro() const {
        return centro;
    }

    float getRadio() const {
        return radio;
    }
    void setCentro(Punto p) {
        centro = p;
    }
    void setRadio(float r) {
        radio = r;
    }};

//lo mismo que con circulo pero con la elipse.
class Elipse {
private:
    Punto centro;
    float a, b;

public:
    Elipse(Punto c, float a_, float b_)
        : centro(c), a(a_), b(b_) {}

    Punto getCentro() const {
        return centro;
    }

    float getA() const {
        return a;
    }
    float getB() const {
        return b;
    }
    void setCentro(Punto c) {
        centro = c;
    }
    void setA(float a_) {
        a = a_;
    }
    void setB(float b_) {
        b = b_;
    }};

//lo mismo pero el punto en el rectangulo e suno de los vertices.
class Rectangulo {
private:
    Punto verticeInferiorIzquierdo;
    float ancho, largo;

public:
    Rectangulo(Punto v, float an, float lar)
        : verticeInferiorIzquierdo(v), ancho(an), largo(lar) {}

    Punto getVertice() const {
        return verticeInferiorIzquierdo;
    }

    float getAncho() const {
        return ancho;
    }
    float getLargo() const {
        return largo;
    }
    void setVertice(Punto v) {
        verticeInferiorIzquierdo = v;
    }
    void setAncho(float a) {
        ancho = a;
    }
    void setLargo(float l) {
        largo = l;
    }};

//creo mi template para calcular areas que va a depender del tipo T de figura.
template<typename T>
class ProcesadorFigura {
public:
    float calcularArea(const T& figura);
};

//para el circulo.
template<>
class ProcesadorFigura<Circulo> {
public:
    float calcularArea(const Circulo& c) {
        return static_cast<float>(M_PI) * c.getRadio() * c.getRadio();
    }
};

//para la elipse.
template<>
class ProcesadorFigura<Elipse> {
public:
    float calcularArea(const Elipse& e) {
        return static_cast<float>(M_PI) * e.getA() * e.getB();
    }
};

//para el rectangulo.
template<>
class ProcesadorFigura<Rectangulo> {
public:
    float calcularArea(const Rectangulo& r) {
        return r.getAncho() * r.getLargo();
    }
};

int main() {
    //pruebo uno para cada figura.
    Punto centro(0.0f, 0.0f);
    Circulo circulo(centro, 2.0f);
    Elipse elipse(centro, 3.0f, 1.5f);
    Rectangulo rect(Punto(0, 0), 4.0f, 5.0f);

    ProcesadorFigura<Circulo> procCirc;
    cout << "Área del círculo: " << procCirc.calcularArea(circulo) << endl;
    
    ProcesadorFigura<Elipse> procElip;
    cout << "Área de la elipse: " << procElip.calcularArea(elipse) << endl;

    ProcesadorFigura<Rectangulo> procRect;
    cout << "Área del rectángulo: " << procRect.calcularArea(rect) << endl;
    return 0;}