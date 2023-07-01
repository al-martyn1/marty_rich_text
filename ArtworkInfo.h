#pragma once


#include "AuthorInfo.h"
#include "DateInfo.h"
#include "Para.h"
#include "TitleInfo.h"
#include "TranslaterInfo.h"
#include "utils.h"

#include <set>
#include <string>


namespace marty_rich_text {



struct ArtworkInfo
{
    std::vector<AuthorInfo>       authors    ;
    TitleInfo                     title      ;

    std::set<std::string>         genres     ;

    std::string                   lang       ; // langTag, ru-RU, en-US, en-GB

    DateRangeInfo                 date       ;

    std::vector<Para>             annotation ; // Пока так, не читаем, возможно, поменяется


    TitleInfo                     orgTitle   ;
    std::string                   orgLang    ; // язык оригинала, для переводных документов
    std::vector<TranslaterInfo>   translaters; // переводчики

    DateRangeInfo                 translateDate;

}; // struct ArtworkInfo


// For debug output
// Типа вроде распарсил FB2 нормально, пока больше не паримся
template<typename StreamType> inline
StreamType& operator<<(StreamType &oss, const ArtworkInfo &ai)
{
    //oss << ai.makeFullName(true); // force add nick

    oss << "Title: " << ai.title.makeFullTitle() << "\n";

    bool 
    bFirst = true;
    for(auto genre: ai.genres)
    {
        if (bFirst)
            oss << "Genres: ";
        else
            oss << ", ";

        oss << genre;
        bFirst = false;
    }

    if (!ai.genres.empty())
        oss << "\n";


    if (!ai.authors.empty())
    {
        oss << "Authors:\n";
        for(auto author : ai.authors)
        {
            oss << "  " << author << "\n";
        }
    }

    oss << "Lang: " << ai.lang << "\n";

    if (!ai.date.empty())
    {
        oss << "Date: " << ai.date.getDisplayValue() << "\n";
    }

    if (!ai.orgTitle.makeFullTitle().empty())
    {
        oss << "Title (original): " << ai.orgTitle.makeFullTitle() << "\n";
    }

    if (!ai.orgLang.empty())
    {
        oss << "Lang (original): " << ai.orgLang << "\n";
    }

    if (!ai.translaters.empty())
    {
        oss << "Translaters:\n";
        for(auto translater : ai.translaters)
        {
            oss << "  " << translater << "\n";
        }
    }

    if (!ai.translateDate.empty())
    {
        oss << "Date (translation): " << ai.translateDate.getDisplayValue() << "\n";
    }

    return oss;
}


} // namespace marty_rich_text

