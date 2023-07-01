#pragma once

#include <string>

namespace marty_rich_text {


struct TitleInfo
{
    std::string                   series     ;
    std::string                   title      ;
    std::string                   subTitle   ;

    std::string                   fullTitle  ; // Overrides composed from series/title/subTitle  (filltitle - прикольное слово из вертикальных палочек)


    std::string makeFullTitle() const
    {
        if (!fullTitle.empty())
        {
            return fullTitle;
        }

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

};


} // namespace marty_rich_text

