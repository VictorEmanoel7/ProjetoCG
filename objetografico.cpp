#include "objetografico.h"

QString tipoParaString(TipoObjeto tipo) {
    switch (tipo) {
    case TipoObjeto::PONTO: return "Ponto";
    case TipoObjeto::RETA: return "Reta";
    case TipoObjeto::POLIGONO: return "Polígono";
    default: return "Desconhecido";
    }
}

ObjetoGrafico::ObjetoGrafico(QString nome, TipoObjeto tipo)
    : nome(nome), tipo(tipo), visivel(true)
{}

QString ObjetoGrafico::getNome() const { return nome; }
TipoObjeto ObjetoGrafico::getTipo() const { return tipo; }
QVector<Ponto>& ObjetoGrafico::getPontos() { return pontos; }

void ObjetoGrafico::setVisivel(bool v) {
    visivel = v;
}

bool ObjetoGrafico::isVisivel() const {
    return visivel;
}

void ObjetoGrafico::aplicarTransformacao(const Matrix& matriz) {
    for (Ponto& p : pontos) {
        Matrix pontoComoMatriz = p;
        Matrix resultado = matriz * pontoComoMatriz;
        p.setX(resultado.at(0, 0));
        p.setY(resultado.at(1, 0));
    }
}

PontoGrafico::PontoGrafico(QString nome, const Ponto& p)
    : ObjetoGrafico(nome, TipoObjeto::PONTO) {
    pontos.append(p);
}

void PontoGrafico::desenhar(QPainter& painter) const {
    if (pontos.isEmpty()) return;

    painter.save();

    const Ponto& p = pontos.first();
    painter.setPen(QPen(painter.pen().color(), 5));
    painter.drawPoint(p.getX(), p.getY());

    painter.restore();
}

Ponto PontoGrafico::calcularCentro() const {
    if (pontos.isEmpty()) return Ponto(0, 0);
    return pontos.first();
}

RetaGrafica::RetaGrafica(QString nome, const Ponto& p1, const Ponto& p2)
    : ObjetoGrafico(nome, TipoObjeto::RETA) {
    pontos.append(p1);
    pontos.append(p2);
}

void RetaGrafica::desenhar(QPainter& painter) const {
    if (pontos.size() < 2) return;
    const Ponto& p1 = pontos[0];
    const Ponto& p2 = pontos[1];
    painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

Ponto RetaGrafica::calcularCentro() const {
    if (pontos.size() < 2) return Ponto(0, 0);
    const Ponto& p1 = pontos[0];
    const Ponto& p2 = pontos[1];
    return Ponto((p1.getX() + p2.getX()) / 2.0, (p1.getY() + p2.getY()) / 2.0);
}

PoligonoGrafico::PoligonoGrafico(QString nome, const QVector<Ponto>& vertices)
    : ObjetoGrafico(nome, TipoObjeto::POLIGONO) {
    pontos = vertices;
}

void PoligonoGrafico::desenhar(QPainter& painter) const {
    if (pontos.size() < 2) return;
    for (int i = 0; i < pontos.size() - 1; ++i) {
        const Ponto& p1 = pontos[i];
        const Ponto& p2 = pontos[i+1];
        painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
    if (pontos.size() > 2) {
        painter.drawLine(pontos.last().getX(), pontos.last().getY(), pontos.first().getX(), pontos.first().getY());
    }
}

Ponto PoligonoGrafico::calcularCentro() const {
    if (pontos.isEmpty()) return Ponto(0, 0);
    double somaX = 0, somaY = 0;
    for (const Ponto& p : pontos) {
        somaX += p.getX();
        somaY += p.getY();
    }
    return Ponto(somaX / pontos.size(), somaY / pontos.size());
}
