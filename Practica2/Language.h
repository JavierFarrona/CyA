#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <set>
#include <string>

#include "Alphabet.h"
#include "Chain.h"
#include "Symbols.h"

class Language {
 public:
  Language(const Alphabet& alphabet, const std::string& chain);
  Alphabet getAlphabet() const;
  std::string getChain() const;
  void addSymbolToAlphabet(Symbol symbol);
  void addChain(const std::string& chain);
  friend std::ostream& operator<<(std::ostream& out, const Language& language);

 private:
  Alphabet alphabet_;
  std::string chain_;
};

#endif  // LANGUAGE_H