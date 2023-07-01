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


// epigraph
//   Subelements: Содержит в перечисленном порядке элементы:
//     1 Произвольный набор (в произвольном количестве): p, poem, cite, empty-line
//     2 text-author - 0..n (любое число, опционально).
//   Dependant  : body, section, poem
//  
// poem
//   Subelements: Должен содержать последовательность элементов в таком порядке:
//     1 <title> 0..1 (опционально) - название;
//     2 <epigraph> 0..n (любое число, опционально) - эпиграф;
//     3 <stanza> 1..n (любое число, обязательно) - стихотворные строфы;
//     4 <text-author> 0..n (любое число, опционально) - автор стиха;
//     5 <date> 0..1 (опционально) - дата написания.
//   Dependant  : section, cite, epigraph, annotation, history
//  
// cite
//   Subelements: Содержит в указанном порядке следующие элементы:
//     1 Произвольный набор (в произвольном количестве):
//       p, subtitle, empty-line, poem, table
//     2 text-author - 0..n (любое число, опционально) - подпись, автор цитируемого текста.
//   Dependant  : annotation, epigraph, history, section


struct Epigraph;


struct Poem
{
    Title                       title       ; //!< Заголовок, есть метод empty(), optional не нужен
    std::vector<Epigraph>       epigraphs   ;
    std::vector<Stanza>         stanzas     ;
    std::vector<TextAuthor>     textAuthors ; //!< Это Para на самом деле
    DateRangeInfo               date        ; //!< Диапазон дат, есть метод empty(), optional не нужен

}; // struct Poem


// cite
// Subelements: Произвольный набор: p, subtitle, empty-line, poem, table
// p, p, subtitle, empty-line - это один класс Para
// Итого у нас выбор подэлементов из Para, Poem, Table
struct Cite;






struct Cite
{


}; // struct Cite

// EpigraphPoemCite.h


} // namespace marty_rich_text


