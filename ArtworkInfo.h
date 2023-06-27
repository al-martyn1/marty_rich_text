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

}; // struct ArtworkInfo




} // namespace marty_rich_text

