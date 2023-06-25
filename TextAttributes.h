#pragma once

#include "VariantValue.h"
#include "utils.h"

#include <string>
#include <unordered_map>



/*
    По стилям.

    Базовые стили хранятся в виде флагов.

    Расширенные стили - именованные. Пока не запариваемся?

*/


namespace marty_rich_text{


struct TextAttributes
{
    BasicStyleFlags    style = BasicStyleFlags::blank;
    BasicStyleFlags    diff  = BasicStyleFlags::blank; //! Разница со стилем предыдущего фрагмента

    std::size_t        pos   = 0; //! Начальная позиция, с которой применяются атрибуты
    std::size_t        len   = 0; //! Длина фрагмента, к которому применяются атрибуты

    //! Некоторые дополнительные данные
    /*! Так, для стиля BasicStyleFlags::Link должно быть задано extra-значение 'link-target'.
        Если задан стиль BasicStyleFlags::Color - должно быть задано extra-значение 'color'
    */
    std::unordered_map<std::string, VariantValue> values;


    bool styleEqual(const TextAttributes &other) const
    {
        if (style!=other.style)
        {
            return false;
        }

        return mapEqual( values, other.values
                       , [](const VariantValue &v1, const VariantValue &v2) // ValueEqual
                         {
                             return v1==v2;
                         }
                       );
    }


}; // struct TextAttributes


} // namespace marty_rich_text

