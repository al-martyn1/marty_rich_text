#pragma once

#include "DocumentHeader.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace marty_rich_text {



//----------------------------------------------------------------------------
inline
AuthorInfo parsePugixmlFb2_AuthorInfo(pugi::xml_node& node)
{
    AuthorInfo ai;

    ai.firstName  = marty_pugixml::get_node_all_text(node.child("first-name" ));
    ai.middleName = marty_pugixml::get_node_all_text(node.child("middle-name"));
    ai.lastName   = marty_pugixml::get_node_all_text(node.child("last-name"  ));
    ai.nickName   = marty_pugixml::get_node_all_text(node.child("nickname"   ));
    ai.id         = marty_pugixml::get_node_all_text(node.child("id"         ));

    std::string email = marty_pugixml::get_node_all_text(node.child("email"));
    if (!email.empty())
    {
        ai.contacts["email"] = email;
    }

    return ai;
}

//----------------------------------------------------------------------------
inline
DateInfo parsePugixmlFb2_DateInfo(pugi::xml_node& node)
{
    DateInfo di;

    di.displayValue = marty_pugixml::get_node_all_text(node);
    di.value        = node.attribute("value").value();

    return di;
}



// struct DocumentHeader
// {
//     ArtworkInfo      artworkInfo   ;
//     DocumentInfo     documentInfo  ;
//     PublishingInfo   publishingInfo;
//
// }; // struct DocumentHeader


} // namespace marty_rich_text

