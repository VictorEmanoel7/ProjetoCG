/**
 * @file ponto.cpp
 * @brief Implementação da classe Ponto.
 *
 * Este arquivo contém a implementação da classe Ponto, que herda de Matrix
 * para representar um ponto 2D em coordenadas homogêneas.
 *
 */

#include "ponto.h"

/**
 * @brief Construtor da classe Ponto.
 *
 * Cria um ponto no espaço 2D a partir de suas coordenadas x e y.
 * Internamente, o ponto é armazenado como uma matriz coluna 3x1
 * no formato de coordenadas homogêneas [x, y, 1]. A coordenada homogênea
 * (o valor 1.0 na terceira linha) é essencial para que as transformações
 * de translação funcionem corretamente através da multiplicação de matrizes.
 *
 * @param x A coordenada no eixo X.
 * @param y A coordenada no eixo Y.
 */
Ponto::Ponto(double x, double y) : Matrix(3, 1) {
    data[0][0] = x;
    data[1][0] = y;
    data[2][0] = 1.0;
}

/**
 * @brief Retorna a coordenada X do ponto.
 * @return O valor double da coordenada X.
 * @note Este é um método const, o que significa que ele não modifica o estado do objeto.
 */
double Ponto::getX() const {
    return data[0][0];
}

/**
 * @brief Retorna a coordenada Y do ponto.
 * @return O valor double da coordenada Y.
 * @note Este é um método const, o que significa que ele não modifica o estado do objeto.
 */
double Ponto::getY() const {
    return data[1][0];
}

/**
 * @brief Define (modifica) a coordenada X do ponto.
 * @param x O novo valor para a coordenada X.
 */
void Ponto::setX(double x) {
    data[0][0] = x;
}

/**
 * @brief Define (modifica) a coordenada Y do ponto.
 * @param y O novo valor para a coordenada Y.
 */
void Ponto::setY(double y) {
    data[1][0] = y;
}
