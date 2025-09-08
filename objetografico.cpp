/**
 * @file objetografico.cpp
 * @brief Implementação das classes que representam objetos gráficos na cena.
 *
 * Este arquivo contém a implementação da classe base abstrata ObjetoGrafico e
 * suas classes derivadas: PontoGrafico, RetaGrafica e PoligonoGrafico.
 * Cada classe sabe como se desenhar, se transformar e calcular seu centro.
 *
 */

#include "objetografico.h"

/**
 * @brief Construtor da classe base ObjetoGrafico.
 * @param nome O nome do objeto a ser exibido na lista (ex: "Reta 1").
 * @param tipo O tipo do objeto (PONTO, RETA, ou POLIGONO).
 */
ObjetoGrafico::ObjetoGrafico(QString nome, TipoObjeto tipo) : nome(nome), tipo(tipo) {}

/**
 * @brief Retorna o nome do objeto.
 * @return O nome do objeto como um QString.
 */
QString ObjetoGrafico::getNome() const { return nome; }

/**
 * @brief Retorna o tipo do objeto.
 * @return O tipo do objeto (PONTO, RETA ou POLIGONO) como um enum TipoObjeto.
 */
TipoObjeto ObjetoGrafico::getTipo() const { return tipo; }

/**
 * @brief Retorna a lista de pontos (vértices) que definem o objeto.
 * @return Uma referência ao QVector de Pontos do objeto.
 * @note Retorna uma referência não-constante, permitindo a modificação direta dos pontos.
 */
QVector<Ponto>& ObjetoGrafico::getPontos() { return pontos; }

/**
 * @brief Aplica uma matriz de transformação a todos os pontos do objeto.
 *
 * Itera através de cada Ponto na lista de pontos do objeto, multiplica-o
 * pela matriz de transformação fornecida e atualiza as coordenadas do ponto
 * com o resultado. É assim que as operações de translação, escala e rotação
 * são efetivamente aplicadas ao objeto.
 *
 * @param matriz A matriz de transformação 3x3 a ser aplicada.
 */
void ObjetoGrafico::aplicarTransformacao(const Matrix& matriz) {
    for (Ponto& p : pontos) {
        Matrix pontoComoMatriz = p;
        Matrix resultado = matriz * pontoComoMatriz;
        p.setX(resultado.at(0, 0));
        p.setY(resultado.at(1, 0));
    }
}

/**
 * @brief Construtor para um objeto do tipo PontoGrafico.
 * @param nome O nome do objeto.
 * @param p O Ponto que representa a localização deste objeto gráfico.
 */
PontoGrafico::PontoGrafico(QString nome, const Ponto& p)
    : ObjetoGrafico(nome, TipoObjeto::PONTO) {
    pontos.append(p);
}

/**
 * @brief Desenha o ponto na tela.
 *
 * Implementação do método virtual `desenhar`. Utiliza `QPainter::drawPoint()`
 * para renderizar o ponto no canvas.
 *
 * @param painter A referência ao `QPainter` que será usado para o desenho.
 */
void PontoGrafico::desenhar(QPainter& painter) const {
    if (pontos.isEmpty()) return;
    const Ponto& p = pontos.first();
    painter.drawPoint(p.getX(), p.getY());
}

/**
 * @brief Calcula o centro geométrico do ponto.
 *
 * Para um objeto PontoGrafico, o centro é sua própria localização.
 *
 * @return O Ponto que representa o centro do objeto.
 */
Ponto PontoGrafico::calcularCentro() const {
    if (pontos.isEmpty()) {
        return Ponto(0, 0);
    }
    return pontos.first();
}

/**
 * @brief Construtor para um objeto do tipo RetaGrafica.
 * @param nome O nome do objeto.
 * @param p1 O ponto inicial da reta.
 * @param p2 O ponto final da reta.
 */
RetaGrafica::RetaGrafica(QString nome, const Ponto& p1, const Ponto& p2)
    : ObjetoGrafico(nome, TipoObjeto::RETA) {
    pontos.append(p1);
    pontos.append(p2);
}

/**
 * @brief Desenha a reta na tela.
 *
 * Implementação do método virtual `desenhar`. Utiliza `QPainter::drawLine()`
 * para renderizar a reta conectando seus dois pontos.
 *
 * @param painter A referência ao `QPainter` que será usado para o desenho.
 */
void RetaGrafica::desenhar(QPainter& painter) const {
    if (pontos.size() < 2) return;
    const Ponto& p1 = pontos[0];
    const Ponto& p2 = pontos[1];
    painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

/**
 * @brief Calcula o centro geométrico da reta.
 *
 * O centro de uma reta é o ponto médio entre seus pontos inicial e final.
 * É calculado pela média das coordenadas X e Y dos dois pontos.
 *
 * @return O Ponto que representa o centro do objeto.
 */
Ponto RetaGrafica::calcularCentro() const {
    if (pontos.size() < 2) {
        return Ponto(0, 0);
    }
    const Ponto& p1 = pontos[0];
    const Ponto& p2 = pontos[1];
    double centroX = (p1.getX() + p2.getX()) / 2.0;
    double centroY = (p1.getY() + p2.getY()) / 2.0;
    return Ponto(centroX, centroY);
}


/**
 * @brief Construtor para um objeto do tipo PoligonoGrafico.
 * @param nome O nome do objeto.
 * @param vertices Um vetor de Pontos que representam os vértices do polígono.
 */
PoligonoGrafico::PoligonoGrafico(QString nome, const QVector<Ponto>& vertices)
    : ObjetoGrafico(nome, TipoObjeto::POLIGONO) {
    pontos = vertices;
}

/**
 * @brief Desenha o polígono na tela.
 *
 * Implementação do método virtual `desenhar`. Converte a lista de `Ponto`
 * para um `QPolygon` e utiliza `QPainter::drawPolygon()` para renderizá-lo.
 *
 * @param painter A referência ao `QPainter` que será usado para o desenho.
 */
void PoligonoGrafico::desenhar(QPainter& painter) const {
    if (pontos.size() < 2) return;

    QPolygon qpoly;
    for(const Ponto& p : pontos) {
        qpoly << QPoint(p.getX(), p.getY());
    }
    painter.drawPolygon(qpoly);
}

/**
 * @brief Calcula o centro geométrico (baricentro) do polígono.
 *
 * O centro é calculado pela média aritmética das coordenadas de todos
 * os seus vértices.
 *
 * @return O Ponto que representa o centro do objeto.
 */
Ponto PoligonoGrafico::calcularCentro() const {
    if (pontos.isEmpty()) {
        return Ponto(0, 0);
    }
    double somaX = 0, somaY = 0;
    for (const Ponto& p : pontos) {
        somaX += p.getX();
        somaY += p.getY();
    }
    return Ponto(somaX / pontos.size(), somaY / pontos.size());
}
