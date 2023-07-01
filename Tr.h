#pragma once

#include "TdTh.h"

namespace marty_rich_text {


// tr
//   Атрибуты
//     align (опциональный) - вырабнивание "left"/"right"/"center"
//   Подчиненные элементы
//     Произвольный набор (в произвольном количестве) из следующих элементов:
//     <th>;
//     <td>.

struct Tr
{
    EAlign             align = EAlign::left;

    std::vector<TdTh>  trLine;

};


} // namespace marty_rich_text

