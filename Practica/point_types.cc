#include "point_types.h"

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps) {
    os << ps.size() << std::endl;
    for (const CyA::point& p : ps) {
        os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC)
           << p.first << "\t" << std::setw(MAX_SZ) << p.second << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CyA::point& p) {
    os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC)
       << p.first << "\t" << std::setw(MAX_SZ) << p.second;
    return os;
}

std::istream& operator>>(std::istream& is, CyA::point_vector& ps) {
    int n;
    is >> n;
    ps.clear();
    for (int i = 0; i < n; ++i) {
        CyA::point p;
        is >> p.first >> p.second;
        ps.push_back(p);
    }
    return is;
}

std::istream& operator>>(std::istream& is, CyA::point& p) {
    is >> p.first >> p.second;
    return is;
}
