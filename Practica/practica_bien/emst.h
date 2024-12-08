#ifndef EMST_H
#define EMST_H

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <utility>

// Operador genérico para imprimir std::pair
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

// Espacio de nombres para tipos básicos
namespace CyA {
    typedef std::pair<double, double> point;
    typedef std::pair<point, point> arc;
    typedef std::pair<double, arc> weighted_arc;
    typedef std::vector<weighted_arc> arc_vector;
    typedef std::vector<arc> tree;
    typedef std::set<point> point_collection;

    // Declaración del operador para imprimir puntos
    std::ostream& operator<<(std::ostream& os, const point& p);
}

// Espacio de nombres para algoritmos de EMST
namespace EMST {
    class sub_tree {
    private:
        CyA::tree arcs_;
        CyA::point_collection points_;
        double cost_;

    public:
        sub_tree();
        ~sub_tree();

        void add_arc(const CyA::arc& a);
        bool contains(const CyA::point& p) const;
        void merge(const sub_tree& st, const CyA::weighted_arc& a);

        const CyA::tree& get_arcs() const;
        double get_cost() const;
    };

    typedef std::vector<sub_tree> forest;
}

// Clase principal que contiene los puntos y calcula el EMST
class point_set : public std::vector<CyA::point> {
private:
    CyA::tree emst_;

    double euclidean_distance(const CyA::arc& a) const;
    void compute_arc_vector(CyA::arc_vector& av) const;

public:
    point_set(const std::vector<CyA::point>& points);

    void EMST();
    const CyA::tree& get_tree() const;
    double get_cost() const;

    void write_tree(std::ostream& os) const;
    void write_dot(std::ostream& os) const;
};

#endif
