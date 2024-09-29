#include "libxml/xmlstring.h"
#include <defs.hpp>

const char *rootFileName = "home.xml"; // root filename of the app

const xmlChar *predefinedRootTag =
    (const xmlChar *)"TUIEngine"; // root tag of the root file
const xmlChar *predefinedGlobalMap[] = {
    (const xmlChar *)"Module", (const xmlChar *)"Navigation",
    (const xmlChar *)"Screen", (const xmlChar *)"NavigationBar",
    nullptr}; // tags that are used under the predefined root tag

// entire predefined Render Map are used within the predefined Global Map
const xmlChar *predefinedRenderMap[] = {(const xmlChar *)"Module",
                                        (const xmlChar *)"View",
                                        (const xmlChar *)"ScrollView",
                                        (const xmlChar *)"TUIEText",
                                        (const xmlChar *)"Touchables",
                                        (const xmlChar *)"Progress",
                                        (const xmlChar *)"Icon",
                                        (const xmlChar *)"ModuleUse",
                                        nullptr};

// tags Prop defines what attributes a specifec tag can be assigned
const xmlChar *tagProp[] = {(const xmlChar *)"id",
                            (const xmlChar *)"flex",
                            (const xmlChar *)"justifyContent",
                            (const xmlChar *)"alignSelf",
                            (const xmlChar *)"backgroundColor",
                            (const xmlChar *)"margin",
                            (const xmlChar *)"padding",
                            (const xmlChar *)"position",
                            (const xmlChar *)"borderColor",
                            (const xmlChar *)"flexDirection",
                            (const xmlChar *)"textColor",
                            nullptr};

// it define alignment prop
const xmlChar *predefinedAlignAttributes[] = {
    (const xmlChar *)"center",       (const xmlChar *)"flex-end",
    (const xmlChar *)"flex-start",   (const xmlChar *)"space-between",
    (const xmlChar *)"space-around", nullptr};

const xmlChar *importAttributes[] = {(const xmlChar *)"ModuleName",
                                     (const xmlChar *)"fileName", nullptr};
