#include "libxml/xmlstring.h"
#include <funchelper.hpp>

int xmlChartoi(xmlChar *__from) {
  int ret{0};
  for (int i = 0; __from[i] != '\0'; i++) {
    int digit = __from[i] - (unsigned char)'0';
    ret = ret * 10 + digit;
  }

  return ret;
}
