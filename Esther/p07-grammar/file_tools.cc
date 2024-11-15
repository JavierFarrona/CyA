/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 7
 *
 * @author Esther M. Quintero (alu0101434780@ull.edu.es)
 * @date 05 Nov 2022
 * @brief Archivo: file_tools.cc
 *        Funciones para facilitar la lectura y el tratamiento de archivos
 * 
 * @details 
 *    05/11/2022 - Creación del fichero
 *    12/11/2022 - Adaptado a la práctica 7
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream> // stringstream

#include "automata.cc"

/** 
 *  @brief Muestra el mensaje de error de formato
 *  @return void, pero termina el programa
 */
void error_formato() {
  std::cout << "El fichero de especificacion no tiene el formato correcto." << std::endl;
  std::cout << "Use la opcion --help para mas informacion." << std::endl;
  exit(EXIT_SUCCESS);
}

/** 
 *  @brief Cuenta las líneas de un fichero
 *  @param[in] file
 *  @return Número de líneas del fichero
 */
int count_lines(std::string& file) {
  std::ifstream input_file{file, std::ios_base::in};
  std::string line;
  int num_lines = 0;
  while (getline(input_file, line)) {
    ++num_lines;
  }
  return num_lines;
}

/** 
 *  @brief Convierte una línea del fichero en alfabeto
 *  @param[in] line
 *  @return El alfabeto creado
 */
Alphabet line_to_alphabet(std::string& line) {
  Alphabet alphabet;
  for (const auto& elem : line) {
    if (elem != ' ') alphabet.add(elem);
  }
  return alphabet;
}

/** 
 *  @brief Convierte una línea del fichero en estado
 *  @param[in] line
 *  @return El estado creado
 */
State line_to_state(std::string& line) {
  State state;
  std::string elem;
  std::stringstream new_line(line);
  /// Extraemos el id
  getline(new_line, elem, ' ');
  state.setID(stoi(elem));
  /// Extraemos si es de aceptacion
  getline(new_line, elem, ' ');
  state.setFinal(stoi(elem) == 1);
  /// Extraemos el número de transiciones
  std::vector<Transition> transitions;
  getline(new_line, elem, ' ');
  int num = stoi(elem);
  for (int i = 0; i < num; i++) {
    /// Extraemos el símbolo
    getline(new_line, elem, ' ');
    Symbol symbol = elem;
    /// Extraemos a dónde transita
    getline(new_line, elem, ' ');
    int state = stoi(elem);
    /// Creamos la transición
    Transition transition(symbol, state);
    transitions.push_back(transition);
  }
  state.setTranstions(transitions);
  return state;
}

/** 
 *  @brief Pasa de un fichero .fa a DFA
 *  @param[in] file_name
 *  @return El DFA creado
 */
DFA FileToDFA(std::string& file_name) {
  std::ifstream input_file{file_name, std::ios_base::in};
  std::string line;
  /// Comprobamos que tiene al menos las 2 líneas obligatorias 
  int num_lines = count_lines(file_name);
  if (num_lines < 2) error_formato();
  /// Extraemos el alfabeto
  getline(input_file, line);
  Alphabet alphabet(line_to_alphabet(line));
  /// Extraemos el número de estados
  getline(input_file, line);
  int num_states = stoi(line);
  /// Comprobamos que, si tiene al menos un estado, están definidos
  if (num_lines != num_states + 3)  error_formato();
  /// Extraemos el estado inicial
  getline(input_file, line);
  int initial_state = stoi(line);
  State initial;
  /// Extraemos los estados y las transiciones
  std::set<State> states;
  std::set<State> finals;
  while (getline(input_file, line)) {
    State state(line_to_state(line));
    states.insert(state);
    if (state.getFinal()) finals.insert(state);
    if (int(state.getID()) == initial_state) initial = state;
  }
  /// Creamos el DFA
  DFA dfa;
  dfa.setAlphabet(alphabet);
  dfa.setStates(states);
  dfa.setNum(num_states);
  dfa.setInitial(initial);
  dfa.setFinals(finals);
  /// Comprobamos que es DFA
  dfa.is_dfa();
  return dfa;
}

/** 
 *  @brief Pasa de un fichero .fa a DFA
 *  @param[in] kStringsFileName Fichero de cadenas
 *  @param[in] nfa
 *  @return void
 */
void CheckStrings(std::string& kStringsFileName, DFA& nfa) {
  std::ifstream input_file{kStringsFileName, std::ios_base::in};
  std::string line;
  while (getline(input_file, line)) {
    // nfa.accepted(line);
    std::cout << line << " --- ";
    if (nfa.accepted(line)) std::cout << "Accepted" << std::endl;
    else std::cout << "Rejected" << std::endl;
  }
}