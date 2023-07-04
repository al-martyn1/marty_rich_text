#pragma once

#include "DocumentHeader.h"
#include "Stanza.h"
#include "Table.h"
#include "TdTh.h"
#include "Tr.h"
#include "Title.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"
#include "parsePugixmlFb2_DocumentHeader.h"


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

//----------------------------------------------------------------------------
inline
TdTh parsePugixmlFb2_TdTh(pugi::xml_node& node)
{
    TdTh tdth;

    // id (опциональный);
    // style (опциональный);
    // xml:lang (опциональный) - язык.
    parsePugixml_AttrsIdLangStyle(tdth, node);

    // align (опциональный) - "left"/"right"/"center"
    tdth.align      = enum_deserialize(node.attribute("align"), EAlign::left);

    // valign (опциональный) - "top"/"middle"/"bottom"
    tdth.vertAlign  = enum_deserialize(node.attribute("valign"), EVertAlign::top);

    // colspan (опциональный);
    tdth.colspan = (std::size_t)node.attribute("colspan").as_uint(0);
    
    // rowspan (опциональный);
    tdth.rowspan = (std::size_t)node.attribute("rowspan").as_uint(0);


    Para p = parsePugixmlFb2_Para(node);
    if (!p.empty())
    {
        p.align = tdth.align;
        tdth.paras.emplace_back(p);
    }

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
Tr parsePugixmlFb2_Tr(pugi::xml_node& node)
{
    Tr tr;

    // std::string strAlign = 

    EAlign align =  enum_deserialize(node.attribute("align"), EAlign::undefined);
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
            continue;

        TdTh tdth     = parsePugixmlFb2_TdTh(tdthNode);
        tdth.tdthType = tdThType;

        if (align!=EAlign::undefined)
        {
            tdth.align = align;
        }

        tr.trLine.emplace_back(tdth);
    }

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
Table parsePugixmlFb2_Table(pugi::xml_node& node)
{
    Table table;
    parsePugixml_AttrsIdStyle(table, node);
    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();
        if (childName!="tr")
        {
            continue;
        }

        Tr tr = parsePugixmlFb2_Tr(childNode);
        table.emplace_back(tr);
    }

    return table;
}

//----------------------------------------------------------------------------
Poem parsePugixmlFb2_Poem(pugi::xml_node& node);
CiteEpigraph parsePugixmlFb2_Cite(pugi::xml_node& node);
CiteEpigraph parsePugixmlFb2_Epigraph(pugi::xml_node& node);
// Table parsePugixmlFb2_(pugi::xml_node& node);

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
Poem parsePugixmlFb2_Poem(pugi::xml_node& node)
{
    Poem  poem;
    parsePugixml_AttrsIdLang(poem, node);

    pugi::xml_node titleNode = node.child("title");
    if (titleNode)
    {
        poem.title = parsePugixmlFb2_Title(titleNode);
    }

    for(pugi::xml_node epNode=node.child("epigraph"); epNode; epNode=epNode.next_sibling("epigraph"))
    {
        CiteEpigraph epigraph = parsePugixmlFb2_Epigraph(epNode);
        epigraph.blockType    = EBlockType::epigraph; // EBlockType::cite

        Block block;
        block.blockType       = epigraph.blockType;
        block.citeEpigraph.emplace_back(epigraph) ;

        poem.epigraphs.emplace_back(block);
    }

    for(pugi::xml_node stanzaNode=node.child("stanza"); stanzaNode; stanzaNode=stanzaNode.next_sibling("stanza"))
    {
        Stanza stanza = parsePugixmlFb2_Stanza(stanzaNode);
        poem.stanzas.emplace_back(stanza);
    }
    
    for(pugi::xml_node authorNode=node.child("text-author"); authorNode; authorNode=authorNode.next_sibling("text-author"))
    {
        TextAuthor textAuthor = parsePugixmlFb2_TextAuthor(authorNode);
        poem.textAuthors.emplace_back(textAuthor);
    }

    pugi::xml_node dateNode = node.child("date");
    if (dateNode)
    {
        poem.date = parsePugixmlFb2_DateRangeInfo(dateNode);
    }

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
CiteEpigraph parsePugixmlFb2_Cite(pugi::xml_node& node)
{
    CiteEpigraph  ce;
    parsePugixml_AttrsIdLang(ce, node);
    ce.blockType    = EBlockType::cite;

    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();

        Block block;

        if (childName=="p" || childName=="subtitle" || childName=="empty-line")
        {
            block.blockType = EBlockType::para;
            auto para = marty_rich_text::parsePugixmlFb2_Para(childNode);

            if (childName=="subtitle")
            {
                para.paraType = EParaType::subtitle;
            }
            else if (childName=="empty-line")
            {
                para = Pata::emptyLine();
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

            block.para.emplace_back(para);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="poem")
        {
            block.blockType = EBlockType::poem;

            Poem poem = parsePugixmlFb2_Poem(childNode);
            block.poem.emplace_back(poem);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="table")
        {
            block.blockType = EBlockType::table;

            Table table = parsePugixmlFb2_Table(childNode);
            block.table.emplace_back(table);
            ce.blocks.emplace_back(block);
        }
        else if (childName=="text-author")
        {
            TextAuthor textAuthor = parsePugixmlFb2_TextAuthor(authorNode);
            ce.textAuthors.emplace_back(textAuthor);
        }

    }

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
CiteEpigraph parsePugixmlFb2_Epigraph(pugi::xml_node& node)
{
    CiteEpigraph  ce;
    parsePugixml_AttrsIdLang(ce, node);
    ce.blockType    = EBlockType::epigraph;

    for(pugi::xml_node childNode=node.first_child(); childNode; childNode=childNode.next_sibling())
    {
        std::string childName = childNode.name();

        Block block;

        if (childName=="p" ||  /* childName=="subtitle" || */  childName=="empty-line")
        {
            block.blockType = EBlockType::para;
            auto para = marty_rich_text::parsePugixmlFb2_Para(childNode);

             /* if (childName=="subtitle")
            {
                para.paraType = EParaType::subtitle;
            }
            else */  if (childName=="empty-line")
            {
                para = Pata::emptyLine();
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

            block.para.emplace_back(para);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="poem")
        {
            block.blockType = EBlockType::poem;

            Poem poem = parsePugixmlFb2_Poem(childNode);
            block.poem.emplace_back(poem);
            ce.blocks.emplace_back(block);

        }
        else if (childName=="cite")
        {
            block.blockType = EBlockType::cite;

            CiteEpigraph cite = parsePugixmlFb2_Cite(node);
            block.citeEpigraph.emplace_back(cite);
            ce.blocks.emplace_back(block);

        }
        // else if (childName=="table")
        // {
        //     block.blockType = EBlockType::table;
        //  
        //     Table table = parsePugixmlFb2_Table(childNode);
        //     block.table.emplace_back(table);
        //     ce.blocks.emplace_back(block);
        // }
        else if (childName=="text-author")
        {
            TextAuthor textAuthor = parsePugixmlFb2_TextAuthor(authorNode);
            ce.textAuthors.emplace_back(textAuthor);
        }

    }

    return ce;

}



        // for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
        // {
        //     std::cout << " " << attr.name() << "=" << attr.value();
        // }


} // namespace marty_rich_text

