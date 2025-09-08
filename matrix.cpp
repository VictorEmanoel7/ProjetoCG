/**
 * @file matrix.cpp
 * @brief Implementação da classe Matrix para transformações geométricas 2D.
 *
 * Este arquivo contém a implementação dos métodos da classe Matrix, que é usada
 * para representar e aplicar transformações como translação, escala e rotação
 * em um ambiente de computação gráfica 2D, utilizando coordenadas homogêneas.
 *
 */

#include "matrix.h"
#include <stdexcept>
#include <cmath> // Necessário para M_PI, cos e sin

/**
 * @brief Construtor padrão.
 *
 * Cria uma matriz identidade 3x3. A matriz identidade é a base para as
 * transformações, pois representa "nenhuma alteração". Multiplicar qualquer
 * matriz por uma identidade resulta na própria matriz.
 */
Matrix::Matrix() : rows(3), cols(3) {
    data.resize(3, std::vector<double>(3, 0.0));
    for (int i = 0; i < 3; ++i) {
        data[i][i] = 1.0;
    }
}

/**
 * @brief Construtor parametrizado.
 *
 * Cria uma matriz com 'r' linhas e 'c' colunas, com todos os elementos
 * inicializados em zero.
 *
 * @param r O número de linhas da matriz.
 * @param c O número de colunas da matriz.
 */
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(r, std::vector<double>(c, 0.0));
}

/**
 * @brief Acessa um elemento da matriz para leitura ou escrita.
 * @param row O índice da linha (base 0).
 * @param col O índice da coluna (base 0).
 * @return Uma referência ao elemento na posição especificada.
 */
double& Matrix::at(int row, int col) {
    return data[row][col];
}

/**
 * @brief Acessa um elemento da matriz apenas para leitura (versão const).
 *
 * Permite a leitura de um elemento de uma matriz constante, sem permitir modificação.
 *
 * @param row O índice da linha (base 0).
 * @param col O índice da coluna (base 0).
 * @return Uma referência constante ao elemento na posição especificada.
 */
const double& Matrix::at(int row, int col) const {
    return data[row][col];
}

/**
 * @brief Sobrecarga do operador de multiplicação (*).
 *
 * Realiza a multiplicação de matrizes. A multiplicação é a operação fundamental
 * para aplicar e compor transformações geométricas.
 *
 * @param other A matriz à direita do operador (a matriz a ser multiplicada).
 * @return Uma nova matriz que é o resultado da multiplicação `this * other`.
 * @throw std::runtime_error Lança uma exceção se as dimensões das matrizes forem
 * incompatíveis para multiplicação (colunas da primeira != linhas da segunda).
 */
Matrix Matrix::operator*(const Matrix& other) const {
    if (this->cols != other.rows) {
        throw std::runtime_error("Erro de multiplicação: Dimensões de matriz incompatíveis.");
    }

    Matrix result(this->rows, other.cols);
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < this->cols; ++k) {
                sum += this->data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

/**
 * @brief Cria e retorna uma matriz de translação 2D.
 *
 * Transladar um objeto significa movê-lo sem alterar sua orientação ou tamanho.
 *
 * @param dx O deslocamento a ser aplicado no eixo X.
 * @param dy O deslocamento a ser aplicado no eixo Y.
 * @return A matriz de translação 3x3 correspondente.
 */
Matrix Matrix::criarMatrizTranslacao(double dx, double dy) {
    Matrix t;
    t.data[0][2] = dx;
    t.data[1][2] = dy;
    return t;
}

/**
 * @brief Cria e retorna uma matriz de escala 2D.
 *
 * Escalar um objeto significa alterar seu tamanho, expandindo ou contraindo.
 *
 * @param sx O fator de escala no eixo X (1.0 = sem alteração).
 * @param sy O fator de escala no eixo Y (1.0 = sem alteração).
 * @return A matriz de escala 3x3 correspondente.
 */
Matrix Matrix::criarMatrizEscala(double sx, double sy) {
    Matrix s;
    s.data[0][0] = sx;
    s.data[1][1] = sy;
    return s;
}

/**
 * @brief Cria e retorna uma matriz de rotação 2D.
 *
 * Rotacionar um objeto significa girá-lo em torno de um ponto. Esta matriz
 * representa uma rotação em torno da origem (0,0).
 *
 * @param anguloGraus O ângulo de rotação em graus. Ângulos positivos
 * resultam em rotação no sentido anti-horário.
 * @return A matriz de rotação 3x3 correspondente.
 * @note O ângulo de entrada em graus é convertido para radianos internamente,
 * pois as funções trigonométricas da biblioteca <cmath> operam em radianos.
 */
Matrix Matrix::criarMatrizRotacao(double anguloGraus) {
    Matrix r;
    double anguloRad = anguloGraus * M_PI / 180.0;
    double cosA = cos(anguloRad);
    double sinA = sin(anguloRad);

    r.data[0][0] = cosA;
    r.data[0][1] = -sinA;
    r.data[1][0] = sinA;
    r.data[1][1] = cosA;

    return r;
}
