#pragma once

#include "utils.h"

#include <string>


namespace marty_rich_text {

struct AuthorInfo
{
    std::string    firstName ;
    std::string    middleName;
    std::string    lastName  ;

    std::string    nickName  ;

    std::string    id        ; // Уникальный (?) идентификатор автора (в какой-то системе; обычно вроде UUID)

    std::unordered_map<std::string, std::string>  contacts; // email

    bool empty() const
    {
        return firstName.empty() && middleName.empty() && lastName.empty() && nickName.empty();
    }

    //! Makes human readable full name with optional nick
    std::string makeFullName(bool addNick) const
    {
        std::string fullName;

        std::vector<std::string> nameParts;

        appendIfNonEmpty(nameParts, firstName );
        appendIfNonEmpty(nameParts, middleName);
        appendIfNonEmpty(nameParts, lastName  );

        for(std::size_t i=0u; i!=nameParts.size(); ++i)
        {
            if (i) fullName.append(1, ' ');
            fullName.append(nameParts[i]);
        }

        if (fullName.empty())
        {
            addNick = true;
        }

        if (!addNick)
        {
            return fullName;
        }

        if (!nickName.empty())
        {
            if (nameParts.empty())
            {
                fullName.append(nickName);
            }
            else
            {
                fullName.append(" (");
                fullName.append(nickName);
                fullName.append(")");
            }
        }

        return fullName;

    }

}; // struct AuthorInfo


// For debug output
template<typename StreamType> inline
StreamType& operator<<(StreamType &oss, const AuthorInfo &ai)
{
    oss << ai.makeFullName(true); // force add nick
    return oss;
}


} // namespace marty_rich_text

