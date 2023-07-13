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

    std::vector<Para> toParas(const StyleSheet &sh, std::size_t secLevel=0) const
    {
        std::vector<Para> paras;

        MARTY_RICH_TEXT_UTILS_H_RICH_ELEMENT_VECTOR_TO_PARAS(paras, rows, sh, secLevel);

        return paras;
    }

}; // struct Table


} // namespace marty_rich_text

