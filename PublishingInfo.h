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


} // namespace marty_rich_text

