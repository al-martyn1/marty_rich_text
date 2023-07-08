#pragma once

#include "Enums.h"
#include "DateInfo.h"
#include "Para.h"
#include "Stanza.h"
#include "Table.h"
#include "TextAuthor.h"
#include "Title.h"

namespace marty_rich_text {


// enum class EEpigraphPoemCiteType : std::uint32_t
// {
//     unknown    = (std::uint32_t)(-1),
//     para       = 0,
//     epigraph   = 1,
//     poem       = 2,
//     cite       = 3,
//     subtitle   = 4
//  
// }; // enum class EEpigraphPoemCiteType : std::uint32_t


// Элемент <cite>
// Атрибуты
// id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
// xml:lang (опциональный) - язык.
// Подчиненные элементы
// Содержит в указанном порядке следующие элементы:
//  
// Произвольный набор (в произвольном количестве):
// <p>;
// <subtitle>;
// <empty-line/>;
// <poem>;
// <table> (с версии 2.1);
// <text-author> 0..n (любое число, опционально) - подпись, автор цитируемого текста.


// Элемент <poem>
// Атрибуты
// id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
// xml:lang (опциональный) - язык.
// Подчиненные элементы
// Должен содержать последовательность элементов в таком порядке:
//  
// <title> 0..1 (опционально) - название;
// <epigraph> 0..n (любое число, опционально) - эпиграф;
// <stanza> 1..n (любое число, обязательно) - стихотворные строфы;
// <text-author> 0..n (любое число, опционально) - автор стиха;
// <date> 0..1 (опционально) - дата написания.


// Элемент <epigraph>
// Атрибуты
// id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
// Подчиненные элементы
// Содержит в перечисленном порядке элементы:
//  
// Произвольный набор (в произвольном количестве)
// <p>;
// <poem>;
// <cite>;
// <empty-line>;
// <text-author> 0..n (любое число, опционально).



// Тэг сite может содержать poem
// Тэг poem может содержать epigraph
// Тэг epigraph может содержать poem и cite

// Понятно, что epigraph не будет содержать poem или cite, которые, в свою очередь, могут содержать epigraph
// Но этот цикл добавляет гемора



//struct Para;
struct Block;
struct Poem;
struct CiteEpigraph; // Cite or Epigraph
//struct Section;
// struct Table;


//! Некий блок содержимого из Para, Poem, Table...

struct Block
{
    EBlockType  blockType;

    // Тут лежит макс по одному элементу, в зависимости от blockType,
    // Но даже если blockType соответствует, то может не быть соотв содержимого
    // Или любой blockType может содержать не по одному элементу?

    //NOTE: !!! blockType::code, blockType::teletype и blockType::pre
    //          могут содержать произвольное количество para - для группировки с одним фоном
    //          Но могут и по одному para содержать

    std::vector<Para>            para        ;
    std::vector<Poem>            poem        ;
    std::vector<CiteEpigraph>    citeEpigraph;
    std::vector<Table>           table;

}; // struct Block


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
struct Poem
{
    std::string                 id          ;
    std::string                 lang        ;

    Title                       title       ; //!< Заголовок, есть метод empty(), optional не нужен
    std::vector<Block>          epigraphs   ;
    std::vector<Stanza>         stanzas     ;
    std::vector<TextAuthor>     textAuthors ; //!< Это Para на самом деле
    DateRangeInfo               date        ; //!< Диапазон дат, есть метод empty(), optional не нужен

}; // struct Poem




// cite
//   Subelements: Содержит в указанном порядке следующие элементы:
//     1 Произвольный набор (в произвольном количестве):
//       p, subtitle, empty-line, poem, table
//     2 text-author - 0..n (любое число, опционально) - подпись, автор цитируемого текста.
//   Dependant  : annotation, epigraph, history, section
//   Атрибуты
//   id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
//   xml:lang (опциональный) - язык.

// epigraph
//   Subelements: Содержит в перечисленном порядке элементы:
//     1 Произвольный набор (в произвольном количестве): p, poem, cite, empty-line
//     2 text-author - 0..n (любое число, опционально).
//   Dependant  : body, section, poem
//   Атрибуты
//   id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент

struct CiteEpigraph
{
    std::string                 id          ;
    std::string                 lang        ;

    EBlockType                  blockType   ; //!< Только EBlockType::cite или EBlockType::epigraph

    std::vector<Block>          blocks      ;
    std::vector<TextAuthor>     textAuthors ; //!< Это Para на самом деле

}; // struct Cite


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

struct Section
{
    std::string                 id          ;
    std::string                 lang        ;

    Title                       title       ; //!< Заголовок, есть метод empty(), optional не нужен
    std::vector<CiteEpigraph>   epigraphs   ; //!< Эпиграфы
    // Image также есть в content
    // Para                        image       ; //!< Строго Para с типом EParaType::image (или EParaType::emptyLine, пока разбор image не налажен)
    std::vector<Block>          annotation  ; //!< p, subtitle, empty-line - Para; poem, cite, table - Block

    std::vector<Block>          content     ; //!< В FB2 секция либо только с непосредственным содержимым, либо только с подсекциями
                                              //!< Мы позволим и то и другое, при отображении непосредственное содержимое идёт до подсекций
    std::vector<Section>        subsections ; //!< Подсекции/подразделы

}; // struct Section



} // namespace marty_rich_text


