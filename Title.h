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

    std::vector<Para> toParas(const StyleSheet &sh, std::size_t secLevel=0) const
    {
        auto res = paras;

        for(auto &p : res)
        {
            p.paraType = EParaType::title;
        }

        if (!res.empty())
        {
            res.emplace_back(Para::emptyLine());
        }
        
        return res;
    }

}; // struct Title


} // namespace marty_rich_text

