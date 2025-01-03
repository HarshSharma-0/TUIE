#ifndef __TUIE_PARSER__
#define __TUIE_PARSER__

#include "Tokens.hpp"
#include <filesystem>

class OPEN_APP {
public:
  int parser(std::filesystem::path &);
  void parserClean();
  void parserCleanXml();
  node *renderNodes{nullptr};

private:
  xmlDoc *rootXml{nullptr};
  xmlNode *rootNode{nullptr};
};

#endif // !__TUIE_PARSER__
