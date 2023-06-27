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

}; // struct DocumentHeader


} // namespace marty_rich_text

