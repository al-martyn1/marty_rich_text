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

    std::string getValue() const
    {
        if (!value.empty())
        {
            return value;
        }

        return displayValue;
    }

}; // struct DateInfo


struct DateRangeInfo
{
    DateInfo    date     ; // single date value or date range end
    DateInfo    startDate;

    std::string getDisplayValue() const
    {
        if (startDate.empty())
        {
            return date.getDisplayValue();
        }

        return startDate.getDisplayValue() + " - " + date.getDisplayValue();
    }

    bool empty() const
    {
        return date.empty();
    }

};


} // namespace marty_rich_text

