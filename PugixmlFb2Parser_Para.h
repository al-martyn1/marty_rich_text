#pragma once

#include "Enums.h"
#include "Para.h"
#include "PugixmlGenericRichParaWalker.h"
#include "parsePugixml_AttrsIdLangStyle.h"
#include "utils.h"
#include "PugixmlFb2Parser.h"

#include "marty_pugixml/marty_pugixml.h"

#include <unordered_map>


namespace marty_rich_text {


inline
const std::unordered_map<std::string, BasicStyleFlags>&
getFb2TagFlagsMap()
{
    static std::unordered_map<std::string, BasicStyleFlags> m =
    { { "strong"       , BasicStyleFlags::strong    }
    , { "emphasis"     , BasicStyleFlags::emphasis  }
    , { "style"        , BasicStyleFlags::style     }
    , { "strikethrough", BasicStyleFlags::strikeout }
    , { "a"            , BasicStyleFlags::link      }
    , { "sub"          , BasicStyleFlags::sub       }
    , { "sup"          , BasicStyleFlags::sup       }
    , { "code"         , BasicStyleFlags::code      }
    , { "image"        , BasicStyleFlags::image     }

    // HTML
    // , { "b"  , BasicStyleFlags::bold          }
    // , { "i"  , BasicStyleFlags::italic        }
    // , { "u"  , BasicStyleFlags::underlined    }
    // , { "s"  , BasicStyleFlags::strikethrough }
    // , { "tt" , BasicStyleFlags::teletype      }

    // HTML (My simple extentions)
    // , { "strikeout" , BasicStyleFlags::strikeout }
    // , { "font"      , BasicStyleFlags::font      }
    // , { "color"     , BasicStyleFlags::color     }

    //, { "", BasicStyleFlags:: }

    };

    return m;
}

// inline
// BasicStyleFlags getFb2TagFlag(const std::string &t)
// {
//     const std::unordered_map<std::string, BasicStyleFlags>& m = getFb2TagFlagsMap();
//
//     std::unordered_map<std::string, BasicStyleFlags>::const_iterator it = m.find(toLower(t));
//
//     if (it!=m.end())
//     {
//         return it->second;
//     }
//
//     return BasicStyleFlags::blank;
// }




struct Fb2ParaWalker : public PugixmlGenericRichParaWalker // marty_pugixml::tree_walker
{
    Fb2ParaWalker()
    : PugixmlGenericRichParaWalker(getFb2TagFlagsMap())
    {}

}; // struct Fb2ParaWalker


inline
Para PugixmlFb2Parser::parsePara(pugi::xml_node node, std::unordered_set<std::string> *pProceseedAttrs)
{
    Fb2ParaWalker walker;
    marty_pugixml::traverse_node(node, walker);
    walker.para.mergeEqualAttrs();
    walker.para.fixAttrs();

    if (pProceseedAttrs)
    {
        parsePugixml_AttrsIdLangStyle(walker.para, node, pProceseedAttrs);
    }

    return walker.para;
}




} // namespace marty_rich_text


