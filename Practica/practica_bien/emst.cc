#include "emst.h"
#include <map>

namespace CyA {
    std::ostream& operator<<(std::ostream& os, const point& p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
}

namespace EMST {
    sub_tree::sub_tree() : cost_(0) {}
    sub_tree::~sub_tree() {}

    void sub_tree::add_arc(const CyA::arc& a) {
        arcs_.push_back(a);
        points_.insert(a.first);
        points_.insert(a.second);
    }

    bool sub_tree::contains(const CyA::point& p) const {
        return points_.find(p) != points_.end();
    }

    void sub_tree::merge(const sub_tree& st, const CyA::weighted_arc& a) {
        arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
        arcs_.push_back(a.second);
        points_.insert(st.points_.begin(), st.points_.end());
        cost_ += a.first + st.get_cost();
    }

    const CyA::tree& sub_tree::get_arcs() const {
        return arcs_;
    }

    double sub_tree::get_cost() const {
        return cost_;
    }
}

point_set::point_set(const std::vector<CyA::point>& points)
    : std::vector<CyA::point>(points) {}

double point_set::euclidean_distance(const CyA::arc& a) const {
    const auto& [p1, p2] = a;
    return std::sqrt(std::pow(p1.first - p2.first, 2) + std::pow(p1.second - p2.second, 2));
}

void point_set::compute_arc_vector(CyA::arc_vector& av) const {
    av.clear();
    for (size_t i = 0; i < size() - 1; ++i) {
        for (size_t j = i + 1; j < size(); ++j) {
            double dist = euclidean_distance({(*this)[i], (*this)[j]});
            av.emplace_back(dist, CyA::arc((*this)[i], (*this)[j]));
        }
    }
    std::sort(av.begin(), av.end());
}

void point_set::EMST() {
    CyA::arc_vector av;
    compute_arc_vector(av);

    EMST::forest st;

    for (const auto& p : *this) {
        EMST::sub_tree s;
        s.add_arc({p, p}); // El arco dummy es eliminado en las funciones de salida
        st.push_back(s);
    }

    for (const auto& a : av) {
        size_t i = 0, j = 0;
        for (; i < st.size(); ++i)
            if (st[i].contains(a.second.first)) break;
        for (; j < st.size(); ++j)
            if (st[j].contains(a.second.second)) break;

        if (i != j) {
            st[i].merge(st[j], a);
            st.erase(st.begin() + j);
        }
    }

    emst_ = st[0].get_arcs();
}

const CyA::tree& point_set::get_tree() const {
    return emst_;
}

double point_set::get_cost() const {
    double total_cost = 0;
    for (const auto& arc : emst_) {
        total_cost += euclidean_distance(arc);
    }
    return total_cost;
}

void point_set::write_tree(std::ostream& os) const {
    for (const auto& arc : emst_) {
        if (arc.first != arc.second) {
            os << arc.first << " -> " << arc.second << "\n";
        }
    }
    os << "Total Cost: " << get_cost() << "\n";
}

void point_set::write_dot(std::ostream& os) const {
    os << "graph G {\n";
    int node_id = 0;
    std::map<CyA::point, int> node_map;

    // Asignar un ID único a cada nodo
    for (const auto& point : *this) {
        node_map[point] = node_id++;
        os << "  " << node_map[point] << " [label=\"" << point.first << "," << point.second << "\"];\n";
    }

    // Escribir las conexiones (arcos)
    for (const auto& arc : emst_) {
        if (arc.first != arc.second) {
            os << "  " << node_map[arc.first] << " -- " << node_map[arc.second] << ";\n";
        }
    }

    os << "}\n";
}


