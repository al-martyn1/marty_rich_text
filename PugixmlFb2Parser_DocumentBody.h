#pragma once

#include "CiteEpigraphPoemSection.h"
#include "DocumentHeader.h"
#include "Para.h"
#include "PugixmlFb2Parser_DocumentHeader.h"
#include "Stanza.h"
#include "Table.h"
#include "TdTh.h"
#include "Title.h"
#include "Tr.h"
#include "parsePugixml_AttrsIdLangStyle.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"

#include <exception>
#include <stdexcept>


// Links -
// Add external xml subtree (e.g. given in string format) to existing xml tree - http://www.gerald-fahrnholz.eu/sw/DocGenerated/HowToUse/html/group___grp_pugi_xml.html

// Pugixml manual - https://pugixml.org/docs/manual.html#access.nodedata



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
Title PugixmlFb2Parser::parseTitle(pugi::xml_node node)
{
    Title t;

    std::unordered_set<std::string> proceseedAttrs;

    for(pugi::xml_node pNode=node.first_child(); pNode; pNode=pNode.next_sibling())
    {
        std::string pNodeName = pNode.name();
        if (pNodeName!="p" && pNodeName!="empty-line")
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: title: found unknown tag: " + pNodeName);
            #endif
            continue;
        }

        if (pNodeName=="empty-line")
        {
            t.paras.emplace_back(Para::emptyLine());
            continue;
        }

        auto para = parsePara(pNode, &proceseedAttrs);
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

    parsePugixml_AttrCheckAllProcessed(node, "title", proceseedAttrs);

    return t;
}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_subtitle
inline
Para PugixmlFb2Parser::parseSubtitle(pugi::xml_node node)
{
    std::unordered_set<std::string> proceseedAttrs;
    Para p     = parsePara(node, &proceseedAttrs);
    p.paraType = EParaType::subtitle;
    parsePugixml_AttrCheckAllProcessed(node, "subtitle", proceseedAttrs);
    return p;
}

//----------------------------------------------------------------------------
//TODO: !!! Пока изображение представляем, как пустой параграф, но надо доделать
inline
Para PugixmlFb2Parser::parseImage(pugi::xml_node node)
{
    MARTY_ARG_USED(node);
    return Para::emptyLine();
}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_text-author
inline
Para PugixmlFb2Parser::parseTextAuthor(pugi::xml_node node)
{
    std::unordered_set<std::string> proceseedAttrs;

    Para p     = PugixmlFb2Parser::parsePara(node, &proceseedAttrs);
    p.paraType = EParaType::textAuthor;

    parsePugixml_AttrCheckAllProcessed(node, "tr", proceseedAttrs);

    return p;
}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_v
inline
Para PugixmlFb2Parser::parseStanzaV(pugi::xml_node node)
{
    std::unordered_set<std::string> proceseedAttrs;

    Para p     = PugixmlFb2Parser::parsePara(node, &proceseedAttrs);
    p.paraType = EParaType::stanzaV;

    parsePugixml_AttrCheckAllProcessed(node, "v", proceseedAttrs);

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
Stanza PugixmlFb2Parser::parseStanza(pugi::xml_node node)
{
    Stanza s;

    pugi::xml_node titleNode = node.child("title");
    if (titleNode)
    {
        s.title = PugixmlFb2Parser::parseTitle(titleNode);
    }

    pugi::xml_node subtitleNode = node.child("subtitle");
    if (subtitleNode)
    {
        s.subtitle = PugixmlFb2Parser::parseSubtitle(subtitleNode);
    }

    for(pugi::xml_node vNode=node.first_child(); vNode; vNode=vNode.next_sibling())
    {
        std::string vNodeName = vNode.name();
        if (vNodeName!="v")
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: stanza: found unknown tag: " + vNodeName);
            #endif
            continue;
        }
        auto v = PugixmlFb2Parser::parseStanzaV(vNode);
        s.lines.emplace_back();
    }

    return s;
}

//----------------------------------------------------------------------------
inline
TdTh PugixmlFb2Parser::parseTdTh(pugi::xml_node node, const std::string &tagName)
{
    TdTh tdth;

    std::unordered_set<std::string> proceseedAttrs;

    // id (опциональный);
    // style (опциональный);
    // xml:lang (опциональный) - язык.
    parsePugixml_AttrsIdLangStyle(tdth, node);

    // align (опциональный) - "left"/"right"/"center"
    tdth.align      = enum_deserialize(parsePugixml_AttrGetStrHelper(node, "align", &proceseedAttrs)  /* node.attribute("align") */ , EAlign::left);

    // valign (опциональный) - "top"/"middle"/"bottom"
    tdth.vertAlign  = enum_deserialize(parsePugixml_AttrGetStrHelper(node, "valign", &proceseedAttrs) /* node.attribute("valign") */ , EVertAlign::top);

    // colspan (опциональный);
    tdth.colspan = (std::size_t)parsePugixml_AttrGetHelper(node, "colspan", &proceseedAttrs).as_uint(0); //  node.attribute("colspan").as_uint(0);

    // rowspan (опциональный);
    tdth.rowspan = (std::size_t)parsePugixml_AttrGetHelper(node, "rowspan", &proceseedAttrs).as_uint(0); // node.attribute("rowspan").as_uint(0);


    Para p = parsePara(node, &proceseedAttrs);
    if (!p.empty())
    {
        p.align = tdth.align;
        tdth.paras.emplace_back(p);
    }

    parsePugixml_AttrCheckAllProcessed(node, tagName, proceseedAttrs);

    return tdth;

}

//----------------------------------------------------------------------------
// tr
//   Атрибуты
//     align (опциональный) - выравнивание "left"/"right"/"center"
//   Подчиненные элементы
//     Произвольный набор (в произвольном количестве) из следующих элементов:
//     <th>;
//     <td>.

// Не совсем понятно, что значит тут выравнивание. Задание выравнивания для всех дочерних ячеек?
inline
Tr PugixmlFb2Parser::parseTr(pugi::xml_node node)
{
    Tr tr;

    std::unordered_set<std::string> proceseedAttrs;

    EAlign align =  enum_deserialize(parsePugixml_AttrGetStrHelper(node, "align", &proceseedAttrs) /* node.attribute("align") */ , EAlign::undefined);
    if (align!=EAlign::undefined)
    {
        tr.align = align;
    }

    for(pugi::xml_node tdthNode=node.first_child(); tdthNode; tdthNode=tdthNode.next_sibling())
    {
        std::string tdthName = tdthNode.name();
        // if (tdthName!="td" && tdthName!="th")
        //     continue;

        ETdThType tdThType = enum_deserialize(tdthName, ETdThType::unknown);

        if (tdThType==ETdThType::unknown)
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: tr: found unknown tag: " + tdthName);
            #endif
            continue;
        }
        TdTh tdth     = PugixmlFb2Parser::parseTdTh(tdthNode, tdthName);
        tdth.tdthType = tdThType;

        if (align!=EAlign::undefined)
        {
            tdth.align = align;
        }

        tr.trLine.emplace_back(tdth);
    }

    parsePugixml_AttrCheckAllProcessed(node, "tr", proceseedAttrs);

    return tr;

}

//----------------------------------------------------------------------------
// table
//   Атрибуты
//     id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
//     style (опциональный) - стиль таблицы
//   Подчиненные элементы
//     Должен содержать элементы:
//     <tr> 1..n (любое число, один обязательно).
inline
Table PugixmlFb2Parser::parseTable(pugi::xml_node node)
{
    Table table;
    std::unordered_set<std::string> proceseedAttrs;

    parsePugixml_AttrsIdStyle(table, node, &proceseedAttrs);
    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();
        if (childName!="tr")
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: table: found unknown tag: " + childName);
            #endif
            continue;
        }

        Tr tr = PugixmlFb2Parser::parseTr(childNode);
        table.rows.emplace_back(tr);
    }

    parsePugixml_AttrCheckAllProcessed(node, "table", proceseedAttrs);

    return table;
}

//----------------------------------------------------------------------------
// poem
//   Subelements: Должен содержать последовательность элементов в таком порядке:
//     1 <title> 0..1 (опционально) - название;
//     2 <epigraph> 0..n (любое число, опционально) - эпиграф;
//     3 <stanza> 1..n (любое число, обязательно) - стихотворные строфы;
//     4 <text-author> 0..n (любое число, опционально) - автор стиха;
//     5 <date> 0..1 (опционально) - дата написания.
//   Dependant  : section, cite, epigraph, annotation, history
//   Атрибуты
//   id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
//   xml:lang (опциональный) - язык.
inline
Poem PugixmlFb2Parser::parsePoem(pugi::xml_node node)
{
    Poem  poem;

    std::unordered_set<std::string> proceseedAttrs;

    parsePugixml_AttrsIdLang(poem, node, &proceseedAttrs);

    pugi::xml_node titleNode = node.child("title");
    if (titleNode)
    {
        poem.title = PugixmlFb2Parser::parseTitle(titleNode);
    }

    for(pugi::xml_node epNode=node.child("epigraph"); epNode; epNode=epNode.next_sibling("epigraph"))
    {
        CiteEpigraph epigraph = PugixmlFb2Parser::parseEpigraph(epNode);
        epigraph.blockType    = EBlockType::epigraph; // EBlockType::cite

        Block block;
        block.blockType       = epigraph.blockType;
        block.citeEpigraph.emplace_back(epigraph) ;

        poem.epigraphs.emplace_back(block);
    }

    for(pugi::xml_node stanzaNode=node.child("stanza"); stanzaNode; stanzaNode=stanzaNode.next_sibling("stanza"))
    {
        Stanza stanza = PugixmlFb2Parser::parseStanza(stanzaNode);
        poem.stanzas.emplace_back(stanza);
    }

    for(pugi::xml_node authorNode=node.child("text-author"); authorNode; authorNode=authorNode.next_sibling("text-author"))
    {
        TextAuthor textAuthor = PugixmlFb2Parser::parseTextAuthor(authorNode);
        poem.textAuthors.emplace_back(textAuthor);
    }

    pugi::xml_node dateNode = node.child("date");
    if (dateNode)
    {
        poem.date = PugixmlFb2Parser::parseDateRangeInfo(dateNode);
    }

    std::unordered_set<std::string> processedTafs = { "title", "epigraph", "stanza", "text-author", "date" };
    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();
        if (processedTafs.find(childName)==processedTafs.end())
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: poem: found unknown tag: " + childName);
            #endif
        }
    }

    parsePugixml_AttrCheckAllProcessed(node, "poem", proceseedAttrs);

    return poem;

}

//----------------------------------------------------------------------------
// cite
//   Subelements: Содержит в указанном порядке следующие элементы:
//     1 Произвольный набор (в произвольном количестве):
//       p, subtitle, empty-line, poem, table
//     2 text-author - 0..n (любое число, опционально) - подпись, автор цитируемого текста.
//   Dependant  : annotation, epigraph, history, section
//   Атрибуты
//   id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
//   xml:lang (опциональный) - язык.
inline
CiteEpigraph PugixmlFb2Parser::parseCite(pugi::xml_node node)
{
    CiteEpigraph  ce;

    std::unordered_set<std::string> proceseedAttrs;

    parsePugixml_AttrsIdLang(ce, node, &proceseedAttrs);
    ce.blockType    = EBlockType::cite;

    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();

        Block block;

        if (childName=="p" || childName=="subtitle" || childName=="empty-line")
        {
            std::unordered_set<std::string> childProceseedAttrs;

            block.blockType = EBlockType::para;
            auto para = parsePara(childNode, &childProceseedAttrs);

            if (childName=="subtitle")
            {
                para.paraType = EParaType::subtitle;
            }
            else if (childName=="empty-line")
            {
                para = Para::emptyLine();
            }
            else
            {
                if (!para.empty())
                {
                    para.paraType = EParaType::normal;
                }
                else
                {
                    para.paraType = EParaType::emptyLine;
                }
            }

            parsePugixml_AttrCheckAllProcessed(childNode, childName, childProceseedAttrs);

            block.para.emplace_back(para);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="poem")
        {
            block.blockType = EBlockType::poem;

            Poem poem = PugixmlFb2Parser::parsePoem(childNode);
            block.poem.emplace_back(poem);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="table")
        {
            block.blockType = EBlockType::table;

            Table table = PugixmlFb2Parser::parseTable(childNode);
            block.table.emplace_back(table);
            ce.blocks.emplace_back(block);
        }
        else if (childName=="text-author")
        {
            TextAuthor textAuthor = parseTextAuthor(childNode);
            ce.textAuthors.emplace_back(textAuthor);
        }
        else
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: cite: found unknown tag: " + childName);
            #endif
        }

    }

    parsePugixml_AttrCheckAllProcessed(node, "cite", proceseedAttrs);

    return ce;

}

//----------------------------------------------------------------------------
// epigraph
//   Subelements: Содержит в перечисленном порядке элементы:
//     1 Произвольный набор (в произвольном количестве): p, poem, cite, empty-line
//     2 text-author - 0..n (любое число, опционально).
//   Dependant  : body, section, poem
//   Атрибуты
//   id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
inline
CiteEpigraph PugixmlFb2Parser::parseEpigraph(pugi::xml_node node)
{
    CiteEpigraph  ce;

    std::unordered_set<std::string> proceseedAttrs;
    parsePugixml_AttrsId(ce, node, &proceseedAttrs);

    ce.blockType    = EBlockType::epigraph;

    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();

        Block block;

        if (childName=="p" ||  /* childName=="subtitle" || */  childName=="empty-line")
        {
            block.blockType = EBlockType::para;

            std::unordered_set<std::string> childProceseedAttrs;

            auto para = marty_rich_text::PugixmlFb2Parser::parsePara(childNode, &childProceseedAttrs);

             /* if (childName=="subtitle")
            {
                para.paraType = EParaType::subtitle;
            }
            else */  if (childName=="empty-line")
            {
                para = Para::emptyLine();
            }
            else
            {
                if (!para.empty())
                {
                    para.paraType = EParaType::normal;
                }
                else
                {
                    para.paraType = EParaType::emptyLine;
                }
            }

            parsePugixml_AttrCheckAllProcessed(childNode, "title", childProceseedAttrs);

            block.para.emplace_back(para);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="poem")
        {
            block.blockType = EBlockType::poem;

            Poem poem = PugixmlFb2Parser::parsePoem(childNode);
            block.poem.emplace_back(poem);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="cite")
        {
            block.blockType = EBlockType::cite;

            CiteEpigraph cite = PugixmlFb2Parser::parseCite(childNode);
            block.citeEpigraph.emplace_back(cite);
            ce.blocks.emplace_back(block);

        }
        // else if (childName=="table")
        // {
        //     block.blockType = EBlockType::table;
        //
        //     Table table = PugixmlFb2Parser::parseTable(childNode);
        //     block.table.emplace_back(table);
        //     ce.blocks.emplace_back(block);
        // }
        else if (childName=="text-author")
        {
            TextAuthor textAuthor = parseTextAuthor(childNode);
            ce.textAuthors.emplace_back(textAuthor);
        }
        else
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: epigraph: found unknown tag: " + childName);
            #endif
        }

    }

    parsePugixml_AttrCheckAllProcessed(node, "epigraph", proceseedAttrs);

    return ce;

}

//----------------------------------------------------------------------------
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_section
// section - Секция, основной структурный блок книги. Не содержит собственно текста.
//   Subelements: Должен содержать последовательность элементов в таком порядке:
//                1 <title> - 0..1 (опционально);
//                2 <epigraph> - 0..n (любое число, опционально);
//                3 <image> - 0..1 (опционально);
//                4 <annotation> - 0..1 (опционально);
//                5 Один из вариантов,
//                  1 либо вложенные секции:
//                    <section> - (любое число, обязательно);
//                  2 либо произвольный набор (в произвольном количестве) из следующих элементов:
//                    p, image, poem, subtitle, cite, empty-line, table
//                      p, image, subtitle, empty-line - это всё разные виды p
//                      poem, cite, table - это набор из Block, куда также входит и Para <p>
//   Атрибуты
//     id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
//     xml:lang (опциональный) - язык.

inline
Section PugixmlFb2Parser::parseSection(pugi::xml_node node)
{
    Section sec;

    std::unordered_set<std::string> secProceseedAttrs;
    parsePugixml_AttrsIdLang(sec, node, &secProceseedAttrs);

    // Хотя FB2 деклрарирует определенный порядок тэгов, нам-то в принципе похуй
    // Единственное - все теги, кроме section, будут отображаться до вложенных секций,
    // даже если они встретятся после вложенных секций.
    // Но такая ситуация маловероятна, FB2 такой микс не позволяет.
    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();

        if (childName=="title")
        {
            sec.title = PugixmlFb2Parser::parseTitle(childNode);
        }
        else if (childName=="epigraph")
        {
            sec.epigraphs.emplace_back(PugixmlFb2Parser::parseEpigraph(childNode));
        }
        else if (childName=="annotation")
        {
            //TODO: !!!
            // std::vector<Block>          annotation
        }


        else if (childName=="section")
        {
            sec.subsections.emplace_back(PugixmlFb2Parser::parseSection(childNode));
        }


        else if (childName=="image")
        {
            Block block;
            block.blockType = EBlockType::para;
            block.para.emplace_back(PugixmlFb2Parser::parseImage(childNode));
            sec.content.emplace_back(block);
            // image = PugixmlFb2Parser::parseImage(childNode);
        }
        else if (childName=="p")
        {
            Block block;
            block.blockType = EBlockType::para;
            std::unordered_set<std::string> childProceseedAttrs;
            Para p = parsePara(childNode, &childProceseedAttrs);
            parsePugixml_AttrCheckAllProcessed(childNode, "p", childProceseedAttrs);
            block.para.emplace_back(p);
            sec.content.emplace_back(block);
        }
        else if (childName=="subtitle")
        {
            Block block;
            block.blockType = EBlockType::para;
            block.para.emplace_back(PugixmlFb2Parser::parseSubtitle(childNode));
            sec.content.emplace_back(block);
        }
        else if (childName=="empty-line")
        {
            Block block;
            block.blockType = EBlockType::para;
            block.para.emplace_back(Para::emptyLine());
            sec.content.emplace_back(block);
        }
        else if (childName=="poem")
        {
            Block block;
            block.blockType = EBlockType::poem;
            block.poem.emplace_back(PugixmlFb2Parser::parsePoem(childNode));
            sec.content.emplace_back(block);
        }
        else if (childName=="cite")
        {
            Block block;
            block.blockType = EBlockType::cite;
            block.citeEpigraph.emplace_back(PugixmlFb2Parser::parseCite(childNode));
            sec.content.emplace_back(block);
        }
        else if (childName=="table")
        {
            Block block;
            block.blockType = EBlockType::table;
            block.table.emplace_back(PugixmlFb2Parser::parseTable(childNode));
            sec.content.emplace_back(block);
        }
        else
        {
            #if defined(DEBUG) || defined(_DEBUG)
                throw std::runtime_error( "Processing FB2 tag: section: found unknown tag: " + childName);
            #endif
        }

    }

    std::string nodeName = node.name();
    if (nodeName=="section")
    {
        parsePugixml_AttrCheckAllProcessed(node, "section", secProceseedAttrs);
    }

    return sec;

}


        // for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
        // {
        //     std::cout << " " << attr.name() << "=" << attr.value();
        // }


} // namespace marty_rich_text

