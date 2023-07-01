#pragma once

#include "Enums.h"
#include "Para.h"

#include <vector>


namespace marty_rich_text {


struct Title
{
    std::vector<Para>   paras;

    bool empty() const
    {
        return paras.empty();
    }

}; // struct Title


} // namespace marty_rich_text

