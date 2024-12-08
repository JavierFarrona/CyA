#include "sub_tree.h"

EMST::sub_tree::sub_tree() : cost_(0) {}

EMST::sub_tree::~sub_tree() {}

void EMST::sub_tree::add_arc(const CyA::arc& a) {
    arcs_.push_back(a);
    points_.insert(a.first);
    points_.insert(a.second);
}

void EMST::sub_tree::add_point(const CyA::point& p) {
    points_.insert(p);
}

bool EMST::sub_tree::contains(const CyA::point& p) const {
    return points_.find(p) != points_.end();
}

void EMST::sub_tree::merge(const sub_tree& st, const CyA::weighted_arc& a) {
    arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
    arcs_.push_back(a.second);
    points_.insert(st.points_.begin(), st.points_.end());
    cost_ += a.first + st.get_cost();
}
