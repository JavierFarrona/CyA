#include "point_types.h"
#include "sub_tree.h"
#include <cmath>
#include <algorithm>

double euclidean_distance(const CyA::arc& a) {
    return std::sqrt(std::pow(a.first.first - a.second.first, 2) +
                     std::pow(a.first.second - a.second.second, 2));
}

void compute_arc_vector(const CyA::point_vector& points, CyA::arc_vector& av) {
    av.clear();
    const int n = points.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = euclidean_distance({points[i], points[j]});
            av.emplace_back(dist, std::make_pair(points[i], points[j]));
        }
    }
    std::sort(av.begin(), av.end());
}

void kruskal_EMST(const CyA::point_vector& points, CyA::tree& emst) {
    CyA::arc_vector av;
    compute_arc_vector(points, av);

    EMST::sub_tree_vector forest;
    for (const auto& p : points) {
        EMST::sub_tree st;
        st.add_point(p);
        forest.push_back(st);
    }

    for (const auto& a : av) {
        int i = -1, j = -1;
        for (size_t k = 0; k < forest.size(); ++k) {
            if (forest[k].contains(a.second.first)) i = k;
            if (forest[k].contains(a.second.second)) j = k;
        }

        if (i != j) {
            forest[i].merge(forest[j], a);
            forest.erase(forest.begin() + j);
        }
    }

    emst = forest[0].get_arcs();
}
