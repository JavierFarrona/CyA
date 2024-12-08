#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <iomanip>

#define MAX_SZ 3
#define MAX_PREC 0

namespace CyA {
    typedef std::pair<double, double> point;                // Representa un punto en 2D
    typedef std::vector<point> point_vector;                // Vector de puntos
    typedef std::pair<point, point> arc;                    // Arco entre dos puntos
    typedef std::pair<double, arc> weighted_arc;            // Arco ponderado
    typedef std::vector<weighted_arc> arc_vector;           // Vector de arcos ponderados
    typedef std::set<point> point_collection;               // Conjunto de puntos
    typedef std::vector<arc> tree;                          // Árbol representado como un vector de arcos
}

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);
std::ostream& operator<<(std::ostream& os, const CyA::point& ps);
std::istream& operator>>(std::istream& is, CyA::point_vector& ps);
std::istream& operator>>(std::istream& is, CyA::point& ps);
