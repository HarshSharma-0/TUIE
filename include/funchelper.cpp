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

/**
 * Function layoutCalculator , calculate the layout and resolve the colours fron
 * Hex code to the R,G,B format that we can use to tell the terminal what color
 * should be given to specific position on the screen
 * **/

void layoutCalculator(Node *main, int &height, int &width) {

  double totalFlex = 0;
  int tempCordX{0}, tempCordY{0};
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
    if (loopNode->nodeChild != nullptr)
      layoutCalculator(loopNode->nodeChild, loopNode->nodeStyle->height,
                       loopNode->nodeStyle->width);
    nodeDimension = 0.0;
  }

  for (Node *cordNode = main; cordNode != nullptr;
       cordNode = cordNode->nodeNext) {
    if (cordNode->nodeStyle->flexDirection == RenderTypes::FLEX_DIRECTION_ROW) {
      if (cordNode->nodePrev != nullptr) {
        tempCordX += cordNode->nodePrev->nodeStyle->width;
        cordNode->nodeStyle->offSetX = tempCordX;
        cordNode->nodeStyle->offSetY = 0;
        continue;
      }
      cordNode->nodeStyle->offSetX = 0;
      cordNode->nodeStyle->offSetY = 0;
      continue;
    }
    if (cordNode->nodeStyle->flexDirection == RenderTypes::FLEX_DIRECTION_COL) {
      if (cordNode->nodePrev != nullptr) {
        tempCordY += cordNode->nodePrev->nodeStyle->height;
        cordNode->nodeStyle->offSetY = tempCordY;
        cordNode->nodeStyle->offSetX = 0;
        continue;
      }
      cordNode->nodeStyle->offSetX = 0;
      cordNode->nodeStyle->offSetY = 0;
      continue;
    }
  }
  return;
}
