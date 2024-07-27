#include "libxml/xmlstring.h"
#include <cstddef>
#include <funchelper.hpp>
#include <unistd.h>

int xmlChartoi(xmlChar *__from) {
  int ret{0};
  for (int i = 0; __from[i] != '\0'; i++) {
    int digit = __from[i] - (unsigned char)'0';
    ret = ret * 10 + digit;
  }

  return ret;
}

uString::uString(unsigned char *str) {
  for (std::size_t i = 0; str[i] != '\0'; i++)
    size_str++;
};

unsigned char *uString::begin() { return str; }

unsigned char *uString::end() { return str + size_str; }
