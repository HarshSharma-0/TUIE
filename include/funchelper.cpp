#include "NavigationManager.hpp"
#include "defs.hpp"
#include "libxml/xmlstring.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <funchelper.hpp>
#include <iostream>
#include <unistd.h>

float xmlChartoi(xmlChar *__from) {
  float ret{0};
  char *endPtr{nullptr};
  ret = strtof((const char *)__from, &endPtr);
  return ret;
}

bool layoutCalculator(Node *main, int &height, int &width) {
  double totalFlex = 0;
  for (Node *loopNode = main; loopNode != nullptr;
       loopNode = loopNode->nodeNext) {
    totalFlex += loopNode->nodeStyle->flex;
  }

  for (Node *loopNode = main; loopNode != nullptr;
       loopNode = loopNode->nodeNext) {
    double nodeFlex = loopNode->nodeStyle->flex;
    double dimensionProportion = nodeFlex / totalFlex;
    double nodeDimension{0.0};
    if (loopNode->nodeStyle->flexDirection == RenderTypes::FLEX_DIRECTION_ROW) {
      nodeDimension = width * dimensionProportion;
      loopNode->nodeStyle->height = height;
      loopNode->nodeStyle->width = floor(nodeDimension);
    }
    if (loopNode->nodeStyle->flexDirection == RenderTypes::FLEX_DIRECTION_COL) {
      nodeDimension = height * dimensionProportion;
      loopNode->nodeStyle->width = width;
      loopNode->nodeStyle->height = floor(nodeDimension);
    }

    std::cout << "Parameters calculated for node: "
              << "Height: " << floor(nodeDimension)
              << ", Proportion: " << dimensionProportion
              << ", Total Height: " << height << ", Width: " << width
              << std::endl;
    if (loopNode->nodeChild != nullptr) {
      bool next =
          layoutCalculator(loopNode->nodeChild, loopNode->nodeStyle->height,
                           loopNode->nodeStyle->width);
    }
    nodeDimension = 0.0;
  }

  return true;
}
