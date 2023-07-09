#pragma once

#include "AuthorInfo.h"
#include "DateInfo.h"
#include "TitleInfo.h"

#include <set>
#include <string>


namespace marty_rich_text {



struct PublishingInfo
{
    TitleInfo                     title      ;
    std::string                   publisher  ;
    std::string                   year       ;
    std::string                   city       ;
    std::string                   isbn       ;

    bool empty() const
    {
        return title.empty() && publisher.empty() && year.empty() && city.empty() && isbn.empty();
    }

};


template<typename StreamType> inline
StreamType& operator<<(StreamType &oss, const PublishingInfo &pi)
{
    if (!pi.title.makeFullTitle().empty())
        oss << "  Title    : " << pi.title.makeFullTitle() << "\n";

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

