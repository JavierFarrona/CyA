#pragma once

#include "point_types.h"

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
        void add_point(const CyA::point& p);
        bool contains(const CyA::point& p) const;
        void merge(const sub_tree& st, const CyA::weighted_arc& a);

        inline const CyA::tree& get_arcs() const { return arcs_; }
        inline double get_cost() const { return cost_; }
    };

    typedef std::vector<sub_tree> sub_tree_vector;
}
