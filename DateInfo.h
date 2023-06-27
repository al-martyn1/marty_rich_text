#pragma once

#include <string>


namespace marty_rich_text {


struct DateInfo
{
    std::string  value;
    std::string  displayValue;

    bool empty() const
    {
        return value.empty() && displayValue.empty();
    }

    std::string getDisplayValue() const
    {
        if (!displayValue.empty())
        {
            return displayValue;
        }

        return value;
    }

}; // struct DateInfo

} // namespace marty_rich_text

