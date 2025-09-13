#include "ponto.h"

Ponto::Ponto(double x, double y) : Matrix(3, 1) {
    data[0][0] = x;
    data[1][0] = y;
    data[2][0] = 1.0;
}

double Ponto::getX() const {
    return data[0][0];
}

double Ponto::getY() const {
    return data[1][0];
}

void Ponto::setX(double x) {
    data[0][0] = x;
}

void Ponto::setY(double y) {
    data[1][0] = y;
}
