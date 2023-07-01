#pragma once

#include "DocumentHeader.h"
#include "Stanza.h"
#include "Table.h"
#include "TdTh.h"
#include "Title.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"


namespace marty_rich_text {

/*
  [X]  title
  [X]  subtitle    : para
  [X]  text-author : para
  [ ]  cite
  [ ]  epigraph
  [ ]  poem
  [ ]  section
  [ ]  table
  [ ]  td
  [ ]  th
  [ ]  tr
*/

//----------------------------------------------------------------------------
inline
Title parsePugixmlFb2_Title(pugi::xml_node& node)
{
    Title t;

    for(pugi::xml_node pNode=node.first_child(); pNode; pNode=pNode.next_sibling())
    {
        std::string pNodeName = pNode.name();
        if (pNodeName!="p" && pNodeName!="empty-line")
            continue;

        if (pNodeName=="empty-line")
        {
            t.paras.emplace_back(Pata::emptyLine());
            continue;
        }
        
        auto para = marty_rich_text::parsePugixmlFb2_Para(pNode);
        if (!para.empty())
        {
            para.paraType = EParaType::normal;
        }
        else
        {
            para.paraType = EParaType::emptyLine;
        }

        t.paras.emplace_back(para);
    }

    return t;
}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_subtitle
inline
Para parsePugixmlFb2_Subtitle(pugi::xml_node& node)
{
    Para p     = parsePugixmlFb2_Para(node);
    p.paraType = EParaType::subtitle;
    return p;
}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_text-author
inline
Para parsePugixmlFb2_TextAuthor(pugi::xml_node& node)
{
    Para p     = parsePugixmlFb2_Para(node);
    p.paraType = EParaType::textAuthor;
    return p;
}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_v
inline
Para parsePugixmlFb2_StanzaV(pugi::xml_node& node)
{
    Para p     = parsePugixmlFb2_Para(node);
    p.paraType = EParaType::stanzaV;
    return p;
}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_stanza
// Атрибуты
// Нет атрибутов.
//  
// Подчиненные элементы
// Должен содержать последовательность элементов в таком порядке:
//  
// <title> 0..1 (опционально);
// <subtitle> 0..1 (опционально);
// <v> 1..n (любое число, обязательно).
inline
Stanza parsePugixmlFb2_Stanza(pugi::xml_node& node)
{
    Stanza s;

    pugi::xml_node titleNode = node.child("title");
    if (titleNode)
    {
        s.title = parsePugixmlFb2_Title(titleNode);
    }

    pugi::xml_node subtitleNode = node.child("subtitle");
    if (subtitleNode)
    {
        s.subtitle = parsePugixmlFb2_Subtitle(subtitleNode);
    }

    for(pugi::xml_node vNode=node.first_child(); vNode; vNode=vNode.next_sibling())
    {
        std::string vNodeName = vNode.name();
        if (pNodeName!="v")
            continue;

        auto v = parsePugixmlFb2_StanzaV(vNode);
        s.lines.emplace_back();
    }

    return s;
}





} // namespace marty_rich_text

