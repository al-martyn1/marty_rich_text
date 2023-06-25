#pragma once

#include "enums.h"

#include <cstdint>
#include <exception>
#include <stdexcept>
#include <string>
#include <utility>


namespace marty_rich_text{


class VariantValue
{

protected:

    EVariantValueType valueType    = EVariantValueType::undefined;

    std::string            valueString  ;
    std::int64_t           valueInt     ;
    std::uint64_t          valueUnsigned;


public:

    bool operator==(const VariantValue &other) const
    {
        if (valueType!=other.valueType)
        {
            return false;
        }

        switch(valueType)
        {
            case EVariantValueType::typeString  :  return valueString   == other.valueString  ;
            case EVariantValueType::typeInt     :  return valueInt      == other.valueInt     ;
            case EVariantValueType::typeUnsigned:  return valueUnsigned == other.valueUnsigned;
            default: throw std::runtime_error("VariantValue::operator== - unknown variant type");
        }

        return false;
    }


    VariantValue()
    : valueType(EVariantValueType::typeInt)
    , valueString()
    , valueInt(0)
    , valueUnsigned(0)
    {
    }

    VariantValue(const VariantValue& vv)
    : valueType(vv.valueType)
    , valueString(vv.valueString)
    , valueInt(vv.valueInt)
    , valueUnsigned(vv.valueUnsigned)
    {
    }

    VariantValue(const std::string &str)
    : valueType(EVariantValueType::typeString)
    , valueString(str)
    , valueInt(0)
    , valueUnsigned(0)
    {
    }

    VariantValue(std::int64_t i)
    : valueType(EVariantValueType::typeInt)
    , valueString()
    , valueInt(i)
    , valueUnsigned(0)
    {
    }

    VariantValue(std::uint64_t u)
    : valueType(EVariantValueType::typeUnsigned)
    , valueString()
    , valueInt(0)
    , valueUnsigned(u)
    {
    }

    void swap(VariantValue& vv)
    {
        std::swap(valueType    , vv.valueType    );
        std::swap(valueString  , vv.valueString  );
        std::swap(valueInt     , vv.valueInt     );
        std::swap(valueUnsigned, vv.valueUnsigned);
    }

    VariantValue& operator=(const VariantValue& vv)
    {
        VariantValue tmp = vv;
        swap(tmp);
        return *this;
    }

    VariantValue& operator=(const std::string &v)
    {
        VariantValue tmp = v;
        swap(tmp);
        return *this;
    }

    VariantValue& operator=(std::int64_t v)
    {
        VariantValue tmp = v;
        swap(tmp);
        return *this;
    }

    VariantValue& operator=(std::uint64_t v)
    {
        VariantValue tmp = v;
        swap(tmp);
        return *this;
    }


    std::string asString() const
    {
        switch(valueType)
        {
            case EVariantValueType::typeString  : return valueString;
            case EVariantValueType::typeInt     : return std::to_string(valueInt     );
            case EVariantValueType::typeUnsigned: return std::to_string(valueUnsigned);
            default: throw std::runtime_error("VariantValue::asString - unknown variant type");
        }

        return std::string();
    }

    std::int64_t asInt() const
    {
        switch(valueType)
        {
            case EVariantValueType::typeString  :
                    {
                        // https://en.cppreference.com/w/cpp/string/basic_string/stol
                        std::size_t pos = 0;
                        std::int64_t res = stoll(valueString, &pos);
                        if (pos!=valueString.size())
                        {
                            throw std::runtime_error("VariantValue::asInt - failed to convert string to int");
                        }
                        return res;
                    }

            case EVariantValueType::typeInt     :  return               valueInt     ;
            case EVariantValueType::typeUnsigned:  return (std::int64_t)valueUnsigned;
            default: throw std::runtime_error("VariantValue::asInt - unknown variant type");
        }

        return 0;
    }

    std::uint64_t asUnsigned() const
    {
        switch(valueType)
        {
            case EVariantValueType::typeString  :
                    {
                        // https://en.cppreference.com/w/cpp/string/basic_string/stoul
                        std::size_t pos = 0;
                        std::uint64_t res = stoull(valueString, &pos);
                        if (pos!=valueString.size())
                        {
                            throw std::runtime_error("VariantValue::asUnsigned - failed to convert string to unsigned");
                        }
                        return res;
                    }
            case EVariantValueType::typeInt     : return (std::uint64_t)valueInt     ;
            case EVariantValueType::typeUnsigned: return                valueUnsigned;
            default: throw std::runtime_error("VariantValue::asUnsigned - unknown variant type");
        }

        return 0;
    }

}; // class VariantValue


} // namespace marty_rich_text

