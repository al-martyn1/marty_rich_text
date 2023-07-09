#pragma once

#include "AuthorInfo.h"
#include "DateInfo.h"

#include <set>
#include <string>


namespace marty_rich_text {



struct DocumentInfo
{
    std::vector<AuthorInfo>       creators   ;
    std::string                   id         ;
    std::string                   version    ;

    DateInfo                      creationDateStart;
    DateInfo                      creationDate     ; // End date

    std::vector<std::string>      creationSoftware ;

    std::vector<Para>             history ; // Пока так, не читаем, возможно, поменяется


    bool empty() const
    {
        return creators.empty() && id.empty() && version.empty() && creationDateStart.empty() && creationDate.empty() && creationSoftware.empty() && history.empty();
    }


}; // struct DocumentInfo


} // namespace marty_rich_text

