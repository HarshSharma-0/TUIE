#ifndef FUNC_HELPER_H
#define FUNC_HELPER_H

#include "libxml/xmlstring.h"
#include <cstddef>
int xmlChartoi(xmlChar *);

class uString {
public:
  uString(unsigned char *);
  ~uString();
  unsigned char *begin();
  unsigned char *end();

private:
  unsigned char *str = nullptr;
  std::size_t size_str{0};
};

#endif // !FUNC_HELPER_H
