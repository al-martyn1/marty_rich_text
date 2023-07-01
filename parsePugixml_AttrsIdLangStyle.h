#pragma once

#include "Enums.h"
#include "Para.h"
#include "PugixmlGenericRichParaWalker.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"


namespace marty_rich_text {

template<typename ElementType> inline
void parsePugixml_AttrsIdLangStyle(ElementType &el, pugi::xml_node& node)
{
    el.id    = node.attribute("id").value();
    el.lang  = node.attribute("lang").value();
    if (el.lang.empty())
        el.lang  = node.attribute("xml:lang").value();
    el.style = node.attribute("style").value();
}

template<typename ElementType> inline
void parsePugixml_AttrsIdLang(ElementType &el, pugi::xml_node& node)
{
    el.id    = node.attribute("id").value();
    el.lang  = node.attribute("lang").value();
    if (el.lang.empty())
        el.lang  = node.attribute("xml:lang").value();
}

template<typename ElementType> inline
void parsePugixml_AttrsId(ElementType &el, pugi::xml_node& node)
{
    el.id    = node.attribute("id").value();
}

template<typename ElementType> inline
void parsePugixml_AttrsIdStyle(ElementType &el, pugi::xml_node& node)
{
    el.id    = node.attribute("id").value();
    el.style = node.attribute("style").value();
}



} // namespace marty_rich_text

