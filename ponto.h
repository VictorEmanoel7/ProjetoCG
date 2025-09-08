#ifndef PONTO_H
#define PONTO_H

#include "matrix.h"

class Ponto : public Matrix {
public:
    Ponto(double x = 0.0, double y = 0.0);

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);
};

#endif // PONTO_H
