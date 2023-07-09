#pragma once

#include "ArtworkInfo.h"
#include "DocumentInfo.h"
#include "PublishingInfo.h"


namespace marty_rich_text {

struct DocumentHeader
{
    ArtworkInfo      artworkInfo   ;
    DocumentInfo     documentInfo  ;
    PublishingInfo   publishingInfo;

    bool empty() const
    {
        return artworkInfo.empty() && documentInfo.empty() && publishingInfo.empty();
    }

}; // struct DocumentHeader


} // namespace marty_rich_text

