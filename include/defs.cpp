#include "libxml/xmlstring.h"
#include <defs.hpp>

const char *rootFileName = "home.xml";

const xmlChar *predefinedRootTag = (const xmlChar *)"TUIEngine";
const xmlChar *predefinedGlobalMap[] = {
    (const xmlChar *)"Module", (const xmlChar *)"Navigation",
    (const xmlChar *)"Screen", (const xmlChar *)"NavigationBar", nullptr};
const xmlChar *predefinedRenderMap[] = {(const xmlChar *)"View",
                                        (const xmlChar *)"ScrollView",
                                        (const xmlChar *)"Text",
                                        (const xmlChar *)"Touchables",
                                        (const xmlChar *)"Progress",
                                        (const xmlChar *)"Icon",
                                        nullptr};
const xmlChar *tagProp[] = {(const xmlChar *)"id",
                            (const xmlChar *)"flex",
                            (const xmlChar *)"justifyContent",
                            (const xmlChar *)"alignSelf",
                            (const xmlChar *)"backgroundColor",
                            (const xmlChar *)"margin",
                            (const xmlChar *)"padding",
                            (const xmlChar *)"position",
                            (const xmlChar *)"borderColor",
                            nullptr};
const xmlChar *predefinedAlignAttributes[] = {
    (const xmlChar *)"center",       (const xmlChar *)"flex-end",
    (const xmlChar *)"flex-start",   (const xmlChar *)"space-between",
    (const xmlChar *)"space-around", nullptr};
