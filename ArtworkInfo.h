#pragma once


#include "AuthorInfo.h"
#include "DateInfo.h"
#include "Para.h"
#include "TranslaterInfo.h"
#include "utils.h"

#include <set>
#include <string>


namespace marty_rich_text {



struct ArtworkInfo
{
    std::vector<AuthorInfo>       authors    ;
    std::string                   series     ;
    std::string                   title      ;
    std::string                   subTitle   ;
    std::set<std::string>         genres     ;

    std::string                   lang       ; // langTag, ru-RU, en-US, en-GB

    DateInfo                      dateStart  ;
    DateInfo                      date       ; // End date

    std::vector<Para>             annotation ; // Пока так, не читаем, возможно, поменяется


    std::string                   orgTitle   ;
    std::string                   orgLang    ; // язык оригинала, для переводных документов
    std::vector<TranslaterInfo>   translaters; // переводчики

    DateInfo                      translateDateStart ;
    DateInfo                      translateDate      ;


    std::string makeFullTitleString() const
    {
        std::string composedTitle;

        if (!series.empty())
        {
            composedTitle = series + ": " + title;
        }
        else
        {
            composedTitle = title;
        }

        if (composedTitle.empty())
        {
            composedTitle = subTitle;
        }
        else
        {
            if (!subTitle.empty())
            {
                composedTitle += " (" + subTitle + ")";
            }
        }

        return composedTitle;
    }


}; // struct ArtworkInfo


// For debug output
// Типа вроде распарсил FB2 нормально, пока больше не паримся
template<typename StreamType> inline
StreamType& operator<<(StreamType &oss, const ArtworkInfo &ai)
{
    //oss << ai.makeFullName(true); // force add nick

    oss << "Title: " << ai.makeFullTitleString() << "\n";

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
        oss << "Authors:\n";

    for(auto author : ai.authors)
        oss << "  " << author << "\n";

    return oss;
}


} // namespace marty_rich_text

