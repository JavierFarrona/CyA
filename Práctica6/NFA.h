/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* C:\Users\javie\Documents\GitHub\ULL-2.1\CyA\Práctica6\p06-automata-simulator
* Autor: Javier Farrona Cabrera
* Correo: alu0101541983@ull.edu.es
* Fecha 16 Oct 2024
* Archivo: NFA.h
* Referencias: 
*     Enunciado de la práctica
* Historial de revisiones
*     16 Oct 2024 - Creación (primera versión) del código
*/



#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <set>
#include <string>

// #include "state.cc"
// #include "alphabet.cc"
#include "sequence.cc"
#include "transition.cc"

/** 
 *  @brief Esta clase se usa para guardar un NFA
 *         Guarda los siguientes datos:
 *            - Alfabeto del NFA (alphabet_)
 *            - Conjunto de estados (states_)
 *            - Número de estados (num_)
 *            - Estado inicial (initial_)
 *            - Conjunto de estados de aceptación (finals_)
 *            - Función de transición (transitions_)
 */
class NFA {
 private:
  Alphabet alphabet_;
  std::set<State> states_;
  // std::set<std::set<State>> epsilon_states_;
  unsigned int num_;
  State initial_;
  std::set<State> finals_;
  std::vector<Transition> transitions_;

 public:
  /// Constructores
  NFA() {};
  NFA(const NFA& nfa);

  /// Getters y setters
  Alphabet getAlphabet() const { return alphabet_; };
  void setAlphabet(const Alphabet& alphabet) { alphabet_ = alphabet; };
  std::set<State> getStates() const { return states_; };
  void setStates(std::set<State> states) { states_ = states; };
  unsigned int getNum() const { return num_; };
  void setNum(unsigned int num) { num_ = num; }; 
  State getInitial() const { return initial_; };
  void setInitial(State initial) { initial_ = initial; };
  std::set<State> getFinals() const { return finals_; };
  void setFinals(std::set<State> finals) { finals_ = finals; };
  std::vector<Transition> getTransitions() const { return transitions_; };
  void setTransitions(std::vector<Transition> transitions) { transitions_ = transitions; };

  /// Funciones
  bool accepted(const Sequence& sequence);
  State find_state(unsigned int id);
  void epsilon_transition(std::vector<State>& states);

  /// Sobrecargas
  friend std::ostream& operator<<(std::ostream& out, const NFA& nfa);

};

#endif