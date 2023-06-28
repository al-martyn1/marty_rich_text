#pragma once

#include "AuthorInfo.h"
#include "DateInfo.h"

#include <set>
#include <string>


namespace marty_rich_text {



struct PublishingInfo
{
    std::string                   title      ;
    std::string                   publisher  ;
    std::string                   year       ;
    std::string                   city       ;
    std::string                   isbn       ;

};


template<typename StreamType> inline
StreamType& operator<<(StreamType &oss, const PublishingInfo &pi)
{
    if (!pi.title.empty())
        oss << "  Title    : " << pi.title << "\n";

    if (!pi.publisher.empty())
        oss << "  Publisher: " << pi.publisher << "\n";

    if (!pi.year.empty())
        oss << "  Year     : " << pi.year << "\n";

    if (!pi.city.empty())
        oss << "  City     : " << pi.city << "\n";

    if (!pi.isbn.empty())
        oss << "  ISBN     : " << pi.isbn << "\n";

    return oss;

}


} // namespace marty_rich_text

