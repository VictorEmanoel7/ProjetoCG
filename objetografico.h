#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#include <QString>
#include <QVector>
#include <QPainter>
#include "ponto.h"
#include "matrix.h"

enum class TipoObjeto { PONTO, RETA, POLIGONO };

QString tipoParaString(TipoObjeto tipo);

class ObjetoGrafico {
public:
    ObjetoGrafico(QString nome, TipoObjeto tipo);
    virtual ~ObjetoGrafico() = default;

    virtual void desenhar(QPainter& painter) const = 0;
    virtual Ponto calcularCentro() const = 0;

    void aplicarTransformacao(const Matrix& matriz);

    QString getNome() const;
    TipoObjeto getTipo() const;
    QVector<Ponto>& getPontos();

    void setVisivel(bool visivel);
    bool isVisivel() const;

protected:
    QString nome;
    TipoObjeto tipo;
    QVector<Ponto> pontos;
    bool visivel;
};

class PontoGrafico : public ObjetoGrafico {
public:
    PontoGrafico(QString nome, const Ponto& p);
    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
};

class RetaGrafica : public ObjetoGrafico {
public:
    RetaGrafica(QString nome, const Ponto& p1, const Ponto& p2);
    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
};

class PoligonoGrafico : public ObjetoGrafico {
public:
    PoligonoGrafico(QString nome, const QVector<Ponto>& vertices);
    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
};

#endif // OBJETOGRAFICO_H
