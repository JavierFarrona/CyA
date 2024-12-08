#include "point_types.h"
#include "kruskal.cc"
#include <iostream>
#include <fstream>
#include <string>

void write_to_dot(const CyA::tree& emst, const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << " para escribir el DOT.\n";
        return;
    }

    ofs << "graph EMST {\n";
    for (const auto& arc : emst) {
        ofs << "    \"" << arc.first.first << "," << arc.first.second << "\" -- \""
            << arc.second.first << "," << arc.second.second << "\";\n";
    }
    ofs << "}\n";
    ofs.close();
    std::cout << "Archivo DOT generado: " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    CyA::point_vector points;
    std::cin >> points;

    CyA::tree emst;
    kruskal_EMST(points, emst);

    // Mostrar el árbol generador mínimo en la consola
    std::cout << "Árbol Generador Mínimo:\n";
    for (const auto& arc : emst) {
        std::cout << "(" << arc.first.first << ", " << arc.first.second << ") -- ("
                  << arc.second.first << ", " << arc.second.second << ")" << std::endl;
    }

    // Generar archivo DOT si se proporciona la opción -d
    if (argc > 1 && std::string(argv[1]) == "-d") {
        std::string filename = argc > 2 ? argv[2] : "emst.dot";
        write_to_dot(emst, filename);
    }

    return 0;
}
