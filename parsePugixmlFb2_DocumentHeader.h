#pragma once

#include "DocumentHeader.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace marty_rich_text {



//----------------------------------------------------------------------------
inline
AuthorInfo parsePugixmlFb2_AuthorInfo(pugi::xml_node& node)
{
    AuthorInfo ai;

    ai.firstName  = marty_pugixml::get_node_all_text(node.child("first-name" ));
    ai.middleName = marty_pugixml::get_node_all_text(node.child("middle-name"));
    ai.lastName   = marty_pugixml::get_node_all_text(node.child("last-name"  ));
    ai.nickName   = marty_pugixml::get_node_all_text(node.child("nickname"   ));
    ai.id         = marty_pugixml::get_node_all_text(node.child("id"         ));

    std::string email = marty_pugixml::get_node_all_text(node.child("email"));
    if (!email.empty())
    {
        ai.contacts["email"] = email;
    }

    return ai;
}

//----------------------------------------------------------------------------
inline
TranslaterInfo parsePugixmlFb2_TranslaterInfo(pugi::xml_node& node)
{
    return parsePugixmlFb2_AuthorInfo(node);
}

//----------------------------------------------------------------------------
inline
DateInfo parsePugixmlFb2_DateInfo(pugi::xml_node& node)
{
    DateInfo di;

    di.displayValue = marty_pugixml::get_node_all_text(node);
    di.value        = node.attribute("value").value();

    return di;
}

//----------------------------------------------------------------------------
inline
DateRangeInfo parsePugixmlFb2_DateRangeInfo(pugi::xml_node& node)
{
    DateInfo di = parsePugixmlFb2_DateInfo(node);
    DateRangeInfo dri;
    dri.date = di;
    return dri;
}

//----------------------------------------------------------------------------
//! ArtworkInfo извлекается из тэга FictionBook/description/title-info. Тут на входе мы ожидаем description узел, так как наши представления об иерархии данных отличаются от дизайнеров FB2.
inline
ArtworkInfo parsePugixmlFb2_ArtworkInfo(pugi::xml_node& fb2DescriptionNode)
{
    ArtworkInfo ai;

    pugi::xml_node titleInfoNode = fb2DescriptionNode.child("title-info");

    // multiple genres
    for(pugi::xml_node genreNode=titleInfoNode.child("genre"); genreNode; genreNode=genreNode.next_sibling("genre"))
    {
        std::string genreName = marty_pugixml::get_node_all_text(genreNode);
        ai.genres.insert(genreName);
    }

    // multiple authors
    for(pugi::xml_node authorNode=titleInfoNode.child("author"); authorNode; authorNode=authorNode.next_sibling("author"))
    {
        AuthorInfo authorInfo = parsePugixmlFb2_AuthorInfo(authorNode);
        if (authorInfo.empty())
        {
            continue;
        }

        ai.authors.emplace_back(authorInfo);
    }

    // ai.series      - В FB2 вроде нет аналога
    // Не совсем то - серия издательства - есть, нет авторской серии: series="Звездные войны", title="Империя наносит ответный удар"
    //   <sequence name="Великая поэзия (АСТ)"/>
    // В заголовках обычно пишется в виде "Серия: Название" - "Звездные войны: Империя наносит ответный удар", 
    // или "Звездные войны. Империя наносит ответный удар"

    // ai.subTitle    - В FB2 вроде нет аналога
    // title    ="Ходение по букам"
    // subTitle ="Жизнь и похождения матроса Ивана Тельняшкина"
    // Последнее пишется (иногда в скобках) мелким шрифтом ниже основного названия
    //               Ходение по букам
    // (Жизнь и похождения матроса Ивана Тельняшкина)

    ai.title.title = marty_pugixml::get_node_all_text(titleInfoNode.child("book-title"));
    
    ai.lang  = marty_pugixml::get_node_all_text(titleInfoNode.child("lang"));

    // ai.dateStart - в FB2 вроде нет аналога
    ai.date.date  = parsePugixmlFb2_DateInfo(titleInfoNode.child("date")); // дата окончания создания произведения/дата выпуска релиза-принта, и тп


    // std::vector<Para>             annotation ; // Пока так, не читаем, возможно, поменяется

    ai.orgLang  = marty_pugixml::get_node_all_text(titleInfoNode.child("src-lang"));

    // FB2 не поддерживает?
    // std::string                   orgTitle   ;

    // multiple translaters
    for(pugi::xml_node translatorNode=titleInfoNode.child("translator"); translatorNode; translatorNode=translatorNode.next_sibling("translator"))
    {
        TranslaterInfo translaterInfo = parsePugixmlFb2_TranslaterInfo(translatorNode);
        if (translaterInfo.empty())
        {
            continue;
        }

        ai.translaters.emplace_back(translaterInfo);
    }


    return ai;

}

//----------------------------------------------------------------------------
//! DocumentInfo извлекается из тэга FictionBook/description/document-info. Тут на входе мы ожидаем description узел, так как наши представления об иерархии данных отличаются от дизайнеров FB2.
inline
DocumentInfo parsePugixmlFb2_DocumentInfo(pugi::xml_node& fb2DescriptionNode)
{
    DocumentInfo di;

    //TODO: !!!
    // Тут надо бы распарсить содержимое document-info, но это пока никому не нужно

    // <publish-info>
    //   <book-name>Верховный алгоритм: как машинное обучение изменит наш мир</book-name>
    //   <publisher>Манн, Иванов и Фербер</publisher>
    //   <city>Москва</city>
    //   <year>2016</year>
    //   <isbn>978-5-00100-172-0</isbn>
    // </publish-info>

    // <publish-info>
    //   <book-name>Виртуальные  машины: несколько компьютеров в  одном (+CD)</book-name>
    //   <publisher>ЗАО Издательский дом «Питер»</publisher>
    //   <city>Санкт-Петербург</city>
    //   <year>2006</year>
    //   <isbn>5-469-01338-3</isbn>
    // </publish-info>

    // <publish-info>
    //   <publisher>Издательский дом "Питер"</publisher>
    //   <year>2018</year>
    //   <isbn>978-5-496-02689-5</isbn>
    // </publish-info>

    // <publisher>
    //   <first-name>Литагент</first-name>
    //   <last-name>Эксмо (новый каталог ОСНОВНОЙ)</last-name>
    //   <id>3a54c9f9-d10d-11ec-876c-0cc47af30fe4</id>
    // </publisher>

    // <document-info>
    //   <author>
    //     <nickname>cleed</nickname>
    //   </author>
    //   <publisher>
    //     <first-name>Литагент</first-name>
    //     <last-name>Эксмо (новый каталог ОСНОВНОЙ)</last-name>
    //     <id>3a54c9f9-d10d-11ec-876c-0cc47af30fe4</id>
    //   </publisher>
    // </document-info>

    return di;
}

//----------------------------------------------------------------------------
inline
PublishingInfo parsePugixmlFb2_PublishingInfo(pugi::xml_node& fb2DescriptionNode)
{
    PublishingInfo pi;

    pugi::xml_node publishInfoNode = fb2DescriptionNode.child("publish-info");

    pi.title.title  = marty_pugixml::get_node_all_text(publishInfoNode.child("book-name"));

    pi.publisher    = marty_pugixml::get_node_all_text(publishInfoNode.child("publisher"));
    pi.year         = marty_pugixml::get_node_all_text(publishInfoNode.child("year"));
    pi.city         = marty_pugixml::get_node_all_text(publishInfoNode.child("city"));
    pi.isbn         = marty_pugixml::get_node_all_text(publishInfoNode.child("isbn"));

    // ??? <sequence name="Мировой компьютерный бестселлер"/>

    return pi;
}

//----------------------------------------------------------------------------
inline
DocumentHeader parsePugixmlFb2_DocumentHeader(pugi::xml_node& fb2DescriptionNode)
{
    DocumentHeader dh;

    dh.artworkInfo    = parsePugixmlFb2_ArtworkInfo(fb2DescriptionNode);
    dh.documentInfo   = parsePugixmlFb2_DocumentInfo(fb2DescriptionNode);
    dh.publishingInfo = parsePugixmlFb2_PublishingInfo(fb2DescriptionNode);

    return dh;
}


// struct DocumentHeader
// {
//     ArtworkInfo      artworkInfo   ;
//     DocumentInfo     documentInfo  ;
//     PublishingInfo   publishingInfo;
//
// }; // struct DocumentHeader


} // namespace marty_rich_text

