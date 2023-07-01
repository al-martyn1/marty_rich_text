#pragma once

#include "TdTh.h"
#include "Tr.h"

namespace marty_rich_text {

// table
//   Атрибуты
//     id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
//     style (опциональный) - стиль таблицы
//   Подчиненные элементы
//     Должен содержать элементы:
//     <tr> 1..n (любое число, один обязательно).


struct Table
{
    std::string        id   ;
    std::string        style;

    std::vector<Tr>    rows;

}; // struct Table


} // namespace marty_rich_text

