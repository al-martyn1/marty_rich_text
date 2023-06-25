#pragma once

#include <string>


namespace marty_rich_text {


static bool    isLower( char ch )     { return (ch>='a' && ch<='z'); }
static bool    isUpper( char ch )     { return (ch>='A' && ch<='Z'); }

static bool    isLower( wchar_t ch )  { return (ch>=L'a' && ch<=L'z'); }
static bool    isUpper( wchar_t ch )  { return (ch>=L'A' && ch<=L'Z'); }

static char    toLower( char ch )     { return isUpper(ch) ? ch-'A'+'a' : ch; }
static char    toUpper( char ch )     { return isLower(ch) ? ch-'a'+'A' : ch; }

static wchar_t toLower( wchar_t ch )  { return isUpper(ch) ? ch-L'A'+L'a' : ch; }
static wchar_t toUpper( wchar_t ch )  { return isLower(ch) ? ch-L'a'+L'A' : ch; }

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
static std::basic_string< CharT, Traits, Allocator >
toLower( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr; resStr.reserve(str.size());
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toLower(*it) );
    }

    return resStr;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
static std::basic_string< CharT, Traits, Allocator >
toUpper( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr; resStr.reserve(str.size());
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toUpper(*it) );
    }

    return resStr;
}


template<typename MapType, typename ValueEqual> inline
bool mapEqual(const MapType &m1, const MapType &m2, ValueEqual valueEqual)
{
    if (m1.size()!=m2.size())
    {
        return false;
    }

    typename MapType::const_iterator it1 = m1.begin();
    for(; it1!=m1.end(); ++it1)
    {
        typename MapType::const_iterator it2 = m2.find(it1->first);
        if (it2==m2.end())
            return false;

        if (!valueEqual(it1->second, it2->second))
            return false;
    }

    return true;
}

inline
bool isSpace(char ch)
{
    return ch==' ' || ch=='\t' || ch=='\r' || ch=='\n';
}

template<typename IsSpace> inline
std::string trimBack(std::string str, IsSpace isSpace)
{
    while(!str.empty() && isSpace(str.back()))
    {
        str.erase(str.size()-1, 1);
    }

    return str;
}

template<typename IsSpace> inline
std::string trimFront(std::string str, IsSpace isSpace)
{
    std::string::size_type nspPos = 0;
    while(nspPos!=str.size())
    {
        if (!isSpace(str[nspPos]))
            break;
        ++nspPos;
    }

    str.erase(0, nspPos);

    return str;
}

template<typename IsSpace> inline
std::string trimBoth(std::string str, IsSpace isSpace)
{
    return trimFront(trimBack(str, isSpace), isSpace);
}


} // namespace marty_rich_text

