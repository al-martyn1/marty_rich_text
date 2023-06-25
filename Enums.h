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
    image           = 0x00004000 /*!< картинка */,
    style           = 0x00008000 /*!< кастомный стиль */

}; // enum class BasicStyleFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(BasicStyleFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( BasicStyleFlags, std::map, 0 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::unknown      , "Unknown"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::pre          , "Pre"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::clean        , "Clean"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::image        , "Image"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::strong       , "Strong"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::emphasis     , "Emphasis"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::code         , "Code"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::sub          , "Sub"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::teletype     , "Teletype"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::sup          , "Sup"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::style        , "Style"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::bold         , "Bold"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::italic       , "Italic"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::underlined   , "Underlined" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::strikeout    , "Strikeout"  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::link         , "Link"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::color        , "Color"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( BasicStyleFlags::font         , "Font"       );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( BasicStyleFlags, std::map, 0 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( BasicStyleFlags, std::map, 0 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "unknown"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "Unknown"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "UNKNOWN"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "invalid"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "Invalid"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::unknown      , "INVALID"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::pre          , "pre"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::pre          , "Pre"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::pre          , "PRE"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "clean"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "Clean"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "CLEAN"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "blank"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "Blank"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::clean        , "BLANK"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::image        , "image"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::image        , "Image"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::image        , "IMAGE"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strong       , "strong"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strong       , "Strong"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strong       , "STRONG"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::emphasis     , "emphasis"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::emphasis     , "Emphasis"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::emphasis     , "EMPHASIS"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::code         , "code"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::code         , "Code"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::code         , "CODE"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sub          , "sub"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sub          , "Sub"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sub          , "SUB"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::teletype     , "teletype"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::teletype     , "Teletype"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::teletype     , "TELETYPE"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sup          , "sup"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sup          , "Sup"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::sup          , "SUP"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::style        , "style"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::style        , "Style"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::style        , "STYLE"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::bold         , "bold"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::bold         , "Bold"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::bold         , "BOLD"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::italic       , "italic"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::italic       , "Italic"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::italic       , "ITALIC"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::underlined   , "underlined"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::underlined   , "Underlined"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::underlined   , "UNDERLINED"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "strikeout"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "Strikeout"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "STRIKEOUT"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "strikethrough" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "Strikethrough" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::strikeout    , "STRIKETHROUGH" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::link         , "link"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::link         , "Link"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::link         , "LINK"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::color        , "color"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::color        , "Color"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::color        , "COLOR"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::font         , "font"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::font         , "Font"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( BasicStyleFlags::font         , "FONT"          );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( BasicStyleFlags, std::map, 0 )

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

} // namespace marty_rich_text

