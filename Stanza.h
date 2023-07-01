#pragma once

#include "Title.h"

namespace marty_rich_text {

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

//! Строфа стихотворения
struct Stanza
{
    Title   title   ;
    Para    subtitle;

    std::vector<Para>  lines; // FB2 v-tag

};


} // namespace marty_rich_text


