#include "emst.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " input.txt [-d output.dot]\n";
        return 1;
    }

    std::string input_file = argv[1];
    std::string dot_file;
    bool generate_dot = false;

    if (argc == 4 && std::string(argv[2]) == "-d") {
        generate_dot = true;
        dot_file = argv[3];
    }

    std::ifstream in(input_file);
    if (!in.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << input_file << "\n";
        return 1;
    }

    int n;
    in >> n;
    std::vector<CyA::point> points(n);
    for (int i = 0; i < n; ++i) {
        in >> points[i].first >> points[i].second;
    }
    in.close();

    point_set ps(points);
    ps.EMST();

    std::ofstream out("output1.txt");
    ps.write_tree(out);
    out.close();

    if (generate_dot) {
        std::ofstream dot_out(dot_file);
        ps.write_dot(dot_out);
        dot_out.close();
    }

    return 0;
}
