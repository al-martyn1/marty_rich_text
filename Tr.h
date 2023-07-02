#pragma once

#include "TdTh.h"

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

};


} // namespace marty_rich_text

