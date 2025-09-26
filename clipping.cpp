#include "clipping.h"

Clipping::Clipping() {}

int Clipping::computeCode(const Ponto& p, const LimitesWindow& limites) const {
    int code = INSIDE;

    if (p.getX() < limites.xmin)
        code |= LEFT;
    else if (p.getX() > limites.xmax)
        code |= RIGHT;

    if (p.getY() < limites.ymin)
        code |= BOTTOM;
    else if (p.getY() > limites.ymax)
        code |= TOP;

    return code;
}

bool Clipping::clipReta(Ponto& p1, Ponto& p2, const LimitesWindow& limites) const {
    int code1 = computeCode(p1, limites);
    int code2 = computeCode(p2, limites);
    bool aceito = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            aceito = true;
            break;
        } else if (code1 & code2) {
            aceito = false;
            break;
        } else {
            int code_out = (code1 != 0) ? code1 : code2;
            double x, y;
            if (code_out & TOP) {
                x = p1.getX() + (p2.getX() - p1.getX()) * (limites.ymax - p1.getY()) / (p2.getY() - p1.getY());
                y = limites.ymax;
            } else if (code_out & BOTTOM) {
                x = p1.getX() + (p2.getX() - p1.getX()) * (limites.ymin - p1.getY()) / (p2.getY() - p1.getY());
                y = limites.ymin;
            } else if (code_out & RIGHT) {
                y = p1.getY() + (p2.getY() - p1.getY()) * (limites.xmax - p1.getX()) / (p2.getX() - p1.getX());
                x = limites.xmax;
            } else if (code_out & LEFT) {
                y = p1.getY() + (p2.getY() - p1.getY()) * (limites.xmin - p1.getX()) / (p2.getX() - p1.getX());
                x = limites.xmin;
            }
            if (code_out == code1) {
                p1.setX(x);
                p1.setY(y);
                code1 = computeCode(p1, limites);
            } else {
                p2.setX(x);
                p2.setY(y);
                code2 = computeCode(p2, limites);
            }
        }
    }
    return aceito;
}
