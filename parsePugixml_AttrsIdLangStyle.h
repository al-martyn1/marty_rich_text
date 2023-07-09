#pragma once

#include "Enums.h"
#include "Para.h"
#include "PugixmlGenericRichParaWalker.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"

#include <exception>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace marty_rich_text {


inline
void parsePugixml_AttrCheckAllProcessed(pugi::xml_node& node, const std::string &tag, const std::unordered_set<std::string> &proceseedAttrs)
{
    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
    {
        std::string attrName = attr.name();
        if (proceseedAttrs.find(attrName)==proceseedAttrs.end())
        {
            std::string attrVal = attr.value();
            throw std::runtime_error("FB2: tag: " + tag + ": not processed attribute: " + attrName + ", attr value: " + attrVal);
        }
        // std::cout << " " << attr.name() << "=" << attr.value();
    }
}

inline
pugi::xml_attribute parsePugixml_AttrGetHelper(pugi::xml_node& node, const char* attrName, std::unordered_set<std::string> *pProceseedAttrs)
{
    if (pProceseedAttrs)
    {
        pProceseedAttrs->insert(attrName);
    }

    return node.attribute(attrName);
}

inline
std::string parsePugixml_AttrGetStrHelper(pugi::xml_node& node, const char* attrName, std::unordered_set<std::string> *pProceseedAttrs)
{
    return parsePugixml_AttrGetHelper(node, attrName, pProceseedAttrs).value();
}

template<typename ElementType> inline
void parsePugixml_AttrsIdLangStyle(ElementType &el, pugi::xml_node& node, std::unordered_set<std::string> *pProceseedAttrs=0)
{
    el.id    = parsePugixml_AttrGetStrHelper(node, "id", pProceseedAttrs);
    el.lang  = parsePugixml_AttrGetStrHelper(node, "lang", pProceseedAttrs);
    if (el.lang.empty())
        el.lang  = parsePugixml_AttrGetStrHelper(node, "xml:lang", pProceseedAttrs);
    el.style = parsePugixml_AttrGetStrHelper(node, "style", pProceseedAttrs);
}

template<typename ElementType> inline
void parsePugixml_AttrsIdLang(ElementType &el, pugi::xml_node& node, std::unordered_set<std::string> *pProceseedAttrs=0)
{
    el.id    = parsePugixml_AttrGetStrHelper(node, "id", pProceseedAttrs);
    el.lang  = parsePugixml_AttrGetStrHelper(node, "lang", pProceseedAttrs);
    if (el.lang.empty())
        el.lang  = parsePugixml_AttrGetStrHelper(node, "xml:lang", pProceseedAttrs);
}

template<typename ElementType> inline
void parsePugixml_AttrsId(ElementType &el, pugi::xml_node& node, std::unordered_set<std::string> *pProceseedAttrs=0)
{
    el.id    = parsePugixml_AttrGetStrHelper(node, "id", pProceseedAttrs);
}

template<typename ElementType> inline
void parsePugixml_AttrsIdStyle(ElementType &el, pugi::xml_node& node, std::unordered_set<std::string> *pProceseedAttrs=0)
{
    el.id    = parsePugixml_AttrGetStrHelper(node, "id", pProceseedAttrs);
    el.style = parsePugixml_AttrGetStrHelper(node, "style", pProceseedAttrs);
}



} // namespace marty_rich_text

