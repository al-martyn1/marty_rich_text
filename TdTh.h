#pragma once

#include "Enums.h"
#include "Para.h"

namespace marty_rich_text {


// th
//   Атрибуты
//     id (опциональный);
//     style (опциональный);
//     colspan (опциональный);
//     rowspan (опциональный);
//     align (опциональный) - "left"/"right"/"center"
//     valign (опциональный) - "top"/"middle"/"bottom"
//     xml:lang (опциональный) - язык.
//   Подчиненные элементы
//     Аналогично <p>

// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_td
// http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_th

//! В FB2 тэги td/th содержат непосредственно один абзац, без тэга <p>, но во многих других форматах абзацев в ячейке может быть несколько
struct TdTh
{
    ETdThType        tdthType = ETdThType::td; //!< По-умолчанию - обычная ячейка, не хидерная
    std::string      id     ;
    std::string      style  ;
    std::string      lang   ;

    // https://www.w3schools.com/html/html_table_colspan_rowspan.asp
    std::size_t      colspan    = 0; //!< 0/1 - нет спана
    std::size_t      rowspan    = 0; //!< 0/1 - нет спана

    EAlign           align      = EAlign::left; //!< Выравнивание, по умолчанию - по левому краю. Или - undefined?
    EVertAlign       vertAlign  = EVertAlign::top;

    std::vector<Para>   paras;

    bool empty() const
    {
        return paras.empty();
    }

    std::vector<Para> toParas(const StyleSheet &sh, std::size_t secLevel=0) const
    {
        MARTY_ARG_USED(sh);
        MARTY_ARG_USED(secLevel);
        return paras;
    }




}; // struct TdTh

} // namespace marty_rich_text


