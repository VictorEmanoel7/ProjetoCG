#ifndef WINDOWGRAFICA_H
#define WINDOWGRAFICA_H

#include "objetografico.h"

struct LimitesWindow {
    double xmin, ymin, xmax, ymax;
};

class WindowGrafica : public ObjetoGrafico {
public:
    WindowGrafica(QString nome, const Ponto& p1, const Ponto& p2);

    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
    ObjetoGrafico* clone() const override { return new WindowGrafica(*this); }

    LimitesWindow getLimites() const;

    void atualizarLimites(double xmin, double ymin, double xmax, double ymax);
};

#endif // WINDOWGRAFICA_H
