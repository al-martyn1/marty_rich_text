#pragma once

#include "marty_cpp/marty_enum.h"
#include "marty_cpp/marty_flag_ops.h"
#include "marty_cpp/marty_flags.h"

#include <exception>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>



namespace marty_rich_text{


/*!  Базовые стили, флаги */
enum class BasicStyleFlags : std::uint32_t
{
    unknown         = (std::uint32_t)(-1),
    invalid         = (std::uint32_t)(-1),
    undefined       = (std::uint32_t)(-1),
    clean           = 0,
    blank           = 0,
    strong          = 0x00000001 /*!< выделение типа "важно", логический стиль, обычно это bold */,
    emphasis        = 0x00000002 /*!< выделение типа "некоторый акцент", логический стиль, обычно это italic */,
    code            = 0x00000004 /*!< код, логический стиль, обычно monospace шрифт */,
    teletype        = 0x00000008 /*!< клавиатурный ввод, логический стиль, обычно monospace шрифт */,
    pre             = 0x00000010 /*!< преформатированный текст */,
    sub             = 0x00000020 /*!< нижний индекс */,
    sup             = 0x00000040 /*!< верхний индекс */,
    bold            = 0x00000080 /*!< жирный - явный стиль, не логический */,
    italic          = 0x00000100 /*!< курсив - явный стиль, не логический */,
    strikeout       = 0x00000200 /*!< зачеркнутый - явный стиль, не логический */,
    strikethrough   = 0x00000200 /*!< зачеркнутый - явный стиль, не логический */,
    underlined      = 0x00000400 /*!< подчеркнутый - явный стиль, не логический */,
    link            = 0x00000800 /*!< гиперссылка */,
    color           = 0x00001000 /*!< цвет задан явно */,
    font            = 0x00002000 /*!< фонт задан явно */,
    image           = 0x00004000 /*!< картинка, к ней нет никакого текста в параграфе - длина фрагмента нулевая */,
    style           = 0x00008000 /*!< кастомный стиль */

}; // enum class BasicStyleFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(BasicStyleFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( BasicStyleFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::unknown      , "unknown"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::pre          , "pre"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::clean        , "clean"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::image        , "image"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::strong       , "strong"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::emphasis     , "emphasis"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::code         , "code"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::sub          , "sub"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::teletype     , "teletype"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::sup          , "sup"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::style        , "style"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::bold         , "bold"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::italic       , "italic"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::underlined   , "underlined" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::strikeout    , "strikeout"  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::link         , "link"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::color        , "color"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::font         , "font"       );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( BasicStyleFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( BasicStyleFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "unknown"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "invalid"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "undefined"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::pre          , "pre"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "clean"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "blank"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::image        , "image"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strong       , "strong"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::emphasis     , "emphasis"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::code         , "code"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sub          , "sub"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::teletype     , "teletype"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sup          , "sup"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::style        , "style"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::bold         , "bold"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::italic       , "italic"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::underlined   , "underlined"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "strikeout"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "strikethrough" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::link         , "link"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::color        , "color"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::font         , "font"          );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( BasicStyleFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(BasicStyleFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(BasicStyleFlags, std::set)


enum class EVariantValueType : std::uint32_t
{
    unknown        = (std::uint32_t)(-1),
    invalid        = (std::uint32_t)(-1),
    undefined      = (std::uint32_t)(-1),
    typeString     = 0,
    typeInt        = 1,
    typeUnsigned   = 2

}; // enum class EVariantValueType : std::uint32_t


enum class EParaType : std::uint32_t
{
    unknown      = (std::uint32_t)(-1),
    invalid      = (std::uint32_t)(-1),
    undefined    = (std::uint32_t)(-1),
    normal       = 0 /*!< Обычный параграф */,
    code         = 1 /*!< Все атрибуты частей параграфа содержат флаг code */,
    teletype     = 2 /*!< Все атрибуты частей параграфа содержат флаг teletype */,
    pre          = 3 /*!< Все атрибуты частей параграфа содержат флаг pre */,
    image        = 4 /*!< Имеется один атрибут с флагом image, сам para не содержит текста */,
    emptyLine    = 5 /*!< для FB2 тэга <empty-line> используется обычный параграф с типом emptyLine и пустым содержимым */,
    title        = 6 /*!< Один из параграфов Title. Пока параграфы лежат в Title, нет нужды так маркировать параграфы. Когда производится экспорт в плоский список параграфов, то экспортируемым параграфам назначается данный тип. */,
    subtitle     = 7 /*!< Title содержит в себе параграфы и пустые строки, а Subtitle - это единственный параграф */,
    textAuthor   = 8 /*!< Автор текста цитаты или стихотворения. */,
    stanzaV      = 9 /*!< Элемент строфы стихотворения (строчка) */

}; // enum class EParaType : std::uint32_t


enum class EBlockType : std::uint32_t
{
    unknown     = (std::uint32_t)(-1),
    invalid     = (std::uint32_t)(-1),
    undefined   = (std::uint32_t)(-1),
    para        = 0,
    poem        = 1,
    cite        = 2,
    epigraph    = 3,
    table       = 4,
    code        = 5,
    teletype    = 6,
    pre         = 7

}; // enum class EBlockType : std::uint32_t


enum class EAlign : std::uint32_t
{
    unknown     = (std::uint32_t)(-1),
    invalid     = (std::uint32_t)(-1),
    undefined   = (std::uint32_t)(-1),
    left        = 0,
    center      = 1,
    right       = 2,
    width       = 3

}; // enum class EAlign : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EAlign::unknown  , "unknown" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EAlign::left     , "left"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EAlign::center   , "center"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EAlign::right    , "right"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EAlign::width    , "width"   );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EAlign, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EAlign::unknown  , "unknown"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EAlign::unknown  , "invalid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EAlign::unknown  , "undefined" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EAlign::left     , "left"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EAlign::center   , "center"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EAlign::right    , "right"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EAlign::width    , "width"     );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EAlign, std::map, 1 )


enum class EVertAlign : std::uint32_t
{
    unknown     = (std::uint32_t)(-1),
    invalid     = (std::uint32_t)(-1),
    undefined   = (std::uint32_t)(-1),
    top         = 0,
    center      = 1,
    mid         = 1,
    middle      = 1,
    bottom      = 2

}; // enum class EVertAlign : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EVertAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EVertAlign::unknown  , "unknown" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EVertAlign::center   , "center"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EVertAlign::top      , "top"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EVertAlign::bottom   , "bottom"  );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EVertAlign, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EVertAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::unknown  , "unknown"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::unknown  , "invalid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::unknown  , "undefined" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::center   , "center"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::center   , "mid"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::center   , "middle"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::top      , "top"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EVertAlign::bottom   , "bottom"    );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EVertAlign, std::map, 1 )


enum class ETdThType : std::uint32_t
{
    unknown     = (std::uint32_t)(-1),
    invalid     = (std::uint32_t)(-1),
    undefined   = (std::uint32_t)(-1),
    td          = 0,
    th          = 1

}; // enum class ETdThType : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( ETdThType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ETdThType::th       , "th"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ETdThType::unknown  , "unknown" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ETdThType::td       , "td"      );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( ETdThType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( ETdThType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ETdThType::th       , "th"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ETdThType::unknown  , "unknown"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ETdThType::unknown  , "invalid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ETdThType::unknown  , "undefined" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ETdThType::td       , "td"        );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( ETdThType, std::map, 1 )

} // namespace marty_rich_text

