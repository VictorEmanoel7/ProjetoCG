#ifndef CLIPPING_H
#define CLIPPING_H

#include "ponto.h"
#include "windowgrafica.h"

class Clipping {
public:
    Clipping();

    enum RegionCode {
        INSIDE = 0, // 0000
        LEFT = 1,   // 0001
        RIGHT = 2,  // 0010
        BOTTOM = 4, // 0100
        TOP = 8     // 1000
    };

    bool clipReta(Ponto& p1, Ponto& p2, const LimitesWindow& limites) const;
    bool clipPonto(const Ponto& p, const LimitesWindow& limites) const;

private:
    int computeCode(const Ponto& p, const LimitesWindow& limites) const;
};

#endif // CLIPPING_H
