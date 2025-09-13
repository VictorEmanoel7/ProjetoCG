#include "matrix.h"
#include <stdexcept>
#include <cmath> // Necessário para M_PI, cos e sin

Matrix::Matrix() : rows(3), cols(3) {
    data.resize(3, std::vector<double>(3, 0.0));
    for (int i = 0; i < 3; ++i) {
        data[i][i] = 1.0;
    }
}

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(r, std::vector<double>(c, 0.0));
}

double& Matrix::at(int row, int col) {
    return data[row][col];
}

const double& Matrix::at(int row, int col) const {
    return data[row][col];
}

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

Matrix Matrix::criarMatrizTranslacao(double dx, double dy) {
    Matrix t;
    t.data[0][2] = dx;
    t.data[1][2] = dy;
    return t;
}

Matrix Matrix::criarMatrizEscala(double sx, double sy) {
    Matrix s;
    s.data[0][0] = sx;
    s.data[1][1] = sy;
    return s;
}

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
