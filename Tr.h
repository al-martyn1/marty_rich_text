#pragma once

#include "TdTh.h"

#include "utils.h"

namespace marty_rich_text {


// tr
//   Атрибуты
//     align (опциональный) - выравнивание "left"/"right"/"center"
//   Подчиненные элементы
//     Произвольный набор (в произвольном количестве) из следующих элементов:
//     <th>;
//     <td>.

// Не совсем понятно, что значит тут выравнивание. Задание выравнивания для всех дочерних ячеек?

struct Tr
{
    EAlign             align = EAlign::left;

    std::vector<TdTh>  trLine;


    std::vector<Para> toParas(const StyleSheet &sh, std::size_t secLevel=0) const
    {
        std::vector<Para> paras;

        MARTY_RICH_TEXT_UTILS_H_RICH_ELEMENT_VECTOR_TO_PARAS(paras, trLine, sh, secLevel);

        return paras;
    }

};


} // namespace marty_rich_text

