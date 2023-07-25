#pragma once


#include "Enums.h"
#include "Para.h"
#include "utils.h"

#include "marty_pugixml/marty_pugixml.h"

#include <unordered_map>


namespace marty_rich_text {





struct PugixmlGenericRichParaWalker : public marty_pugixml::tree_walker
{

    // Normal HTML
    // <img src="img_girl.jpg" alt="Girl in a jacket" width="500" height="600">
    // <a href="https://example.com">Website</a>


    // FB2

    // <style>
    // https://github.com/koreader/koreader/issues/6622
    // http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_stylesheet
    // <p>Normal text <style name="semi-condensed">Semi-condensed text</style> Normal text</p>

    // <a>
    // http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_a
    // Для сносок сам текст каждой сноски должен находиться отдельной <section>, расположенной в <body> с атрибутом name="notes".
    // <a type="note">
    // <a l:href="#note1" type="note">[1]</a>
    // <a l:href="#app1">приложении 1</a>.</p>

    // <image>
    // Атрибуты
    //   xlink:type (опциональный)
    //   xlink:href - ссылка на собственно графические данные, обычно содержащиеся в элементе <binary>;
    //   alt (опциональный);
    //   title (опциональный, для inline недопустимый) - подпись к картинке;
    //   id (опциональный, для inline недопустимый) - для ссылок на картинку.
    // http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_image
    // <image l:href="#picture.jpg"/>

    // Вроде аналогично обычному HTML
    // <strong>, <emphasis>, <style>, <a>, <strikethrough>, <sub>, <sup>, <code>, <image>


    // Упрощенный HTML типа https://www.viksoe.dk/code/minihtml.htm
    // <FONT>...</FONT> - The font tag with several attributes, such as FACE="xyz", SIZE=n and COLOR="#rrggbb".

    // Упрощенный HTML, моё
    // <color value="">


public:

    Para                                                          para;


protected:

    TextAttributes                                                curTagAttributes;

    std::vector<BasicStyleFlags>                                  styleFlagsStack ; // opened tags
    std::vector< std::unordered_map<std::string, VariantValue> >  styleValuesStack; // opened tags

    std::unordered_map<std::string, BasicStyleFlags>              tagFlagMap;


public:

    PugixmlGenericRichParaWalker(const std::unordered_map<std::string, BasicStyleFlags> &tfm)
    : tagFlagMap(tfm)
    {}


protected:

    BasicStyleFlags getTagFlag(const std::string &t)
    {
        //const std::unordered_map<std::string, BasicStyleFlags>& m = getFb2TagFlagsMap();

        std::unordered_map<std::string, BasicStyleFlags>::const_iterator it = tagFlagMap.find(toLower(t));

        if (it!=tagFlagMap.end())
        {
            return it->second;
        }

        return BasicStyleFlags::blank;
    }


    bool hasFlagOnStack(BasicStyleFlags f) const
    {
        for(auto sf: styleFlagsStack)
        {
            //if (sf==f)
            if ((sf&f)!=0)
                return true;
        }

        return false;
    }

    BasicStyleFlags mergeStackFlags() const
    {
        BasicStyleFlags flagsRes = BasicStyleFlags::blank;
        for(auto sf: styleFlagsStack)
        {
            flagsRes |= sf;
        }

        return flagsRes;
    }

    static
    bool skipNodeProcessing(pugi::xml_node_type nodeType)
    {
        if ( nodeType==pugi::node_element
          || nodeType==pugi::node_pcdata
          || nodeType==pugi::node_cdata
           )
        {
            return false;
        }

        return true;
    }

    static
    bool skipNodeProcessing(pugi::xml_node node)
    {
        return skipNodeProcessing(node.type());
    }

    // static
    // bool isSpace(char ch)
    // {
    //     return ch==' ' || ch=='\t' || ch=='\r' || ch=='\n';
    // }

    static
    std::string trimBack(std::string str, bool keepOneSpace = true)
    {
        char lastSpace = 0;
        while(!str.empty() && isSpace(str.back()))
        {
            lastSpace = str.back();
            str.erase(str.size()-1, 1);
        }

        if (lastSpace!=0 && keepOneSpace)
        {
            str.append(1, lastSpace);
        }

        return str;
    }

    static
    std::string trimFront(std::string str, bool keepOneSpace = true)
    {
        std::string::size_type nspPos = 0;
        while(nspPos!=str.size())
        {
            if (!isSpace(str[nspPos]))
                break;
            ++nspPos;
        }

        if (nspPos && keepOneSpace)
        {
            --nspPos;
        }

        str.erase(0, nspPos);

        return str;
    }

    bool debugSplitToFragments() const
    {
        #if defined(DEBUG) || defined(_DEBUG)

            // Вроде отладились, пока не нужно зырить на фрагменты

            // std::vector<TextFragment> fragments = para.splitToFragments();
            // return fragments.empty(), true;

            return true;

        #else

            return true;

        #endif
    }

    virtual bool begin(pugi::xml_node& node) override
    {
        pugi::xml_node_type nodeType = node.type();

        if (skipNodeProcessing(nodeType))
            return true;

        if (nodeType!=pugi::node_element)
            return true;

        std::string nodeName = node.name();
        if (nodeName.empty())
            return true;

        BasicStyleFlags tagFlag = getTagFlag(nodeName);
        if (tagFlag==BasicStyleFlags::blank)
            return true;

        curTagAttributes.values.clear();

        // curTagAttributes
        // Тут надо извлечь инфу из тэга style, image, a, font, color etc
        // И всунуть в curTagAttributes.values

        //TODO: !!! Отпроцессить следующие тэги

        // Но пока ничего не делаем
        if ( tagFlag==BasicStyleFlags::link
          || tagFlag==BasicStyleFlags::image
          || tagFlag==BasicStyleFlags::style
           )
        {
            return true;
        }


        BasicStyleFlags prevFlags = mergeStackFlags();

        styleFlagsStack .push_back(tagFlag)                ; // запендюрили флаги стилей на стек
        styleValuesStack.push_back(curTagAttributes.values); // запендюрили доп атрибуты стилей на стек

        curTagAttributes.style = mergeStackFlags(); // cur flags
        curTagAttributes.diff  = tagFlag;
        if (prevFlags==curTagAttributes.style)
        {
            //TODO: !!! Тут может быть нюанс, что идут два одинаковых тэга с доп параметрами, их надо проверить, пока не сделано (теперь вроде сделано)
            // Или вложенные тэги - хотя, вложенность, по идее, схлопывается

            if (!para.attrs.empty() && para.attrs.back().styleEqual(curTagAttributes))
            {
                curTagAttributes.diff = BasicStyleFlags::blank;
            }
        }

        return true; // continue traversal
    }

    virtual bool end(pugi::xml_node& node) override
    {
        pugi::xml_node_type nodeType = node.type();

        if (skipNodeProcessing(nodeType))
            return true;

        if (nodeType!=pugi::node_element)
            return true;

        std::string nodeName = node.name();
        if (nodeName.empty())
            return true;

        BasicStyleFlags tagFlag = getTagFlag(nodeName);
        if (tagFlag==BasicStyleFlags::blank)
            return true;

        if (styleFlagsStack.size()!=styleValuesStack.size())
        {
            throw std::runtime_error("marty_rich_text::PugixmlGenericRichParaWalker::end: stack sizes mismatch");
        }

        BasicStyleFlags prevFlags = mergeStackFlags();

        if (!styleFlagsStack.empty())
        {
            styleFlagsStack.pop_back();
            styleValuesStack.pop_back();
        }

        curTagAttributes.style = mergeStackFlags(); // cur flags
        curTagAttributes.diff  = tagFlag;
        if (styleValuesStack.empty())
        {
            curTagAttributes.values.clear();
        }
        else
        {
            curTagAttributes.values = styleValuesStack.back();
        }

        if (prevFlags==curTagAttributes.style)
        {
            //TODO: !!! Тут может быть нюанс, что идут два одинаковых тэга с доп параметрами, их надо проверить, пока не сделано (теперь вроде сделано)
            // Или вложенные тэги - хотя, вложенность, по идее, схлопывается

            if (!para.attrs.empty() && para.attrs.back().styleEqual(curTagAttributes))
            {
                curTagAttributes.diff = BasicStyleFlags::blank;
            }
        }



        return true; // continue traversal
    }

    virtual bool inner(pugi::xml_node& node) override
    {
        std::string value = node.value();
        // str.append(value);

        if (hasFlagOnStack(BasicStyleFlags::code | BasicStyleFlags::teletype | BasicStyleFlags::pre))
        {
            // лишние пробелы для кода, телетайпа и pre - допустимы
        }
        else
        {
            // надо убрать лишние пробелы

            value = trimBack(value, true /* keepOneSpace */ );

            bool keepSpaceAtValueFront = true;

            // Если текст пуст, то в добавляемом фрагменте надо удалить все ведущие пробелы
            // Если текст содержит на последнем месте пробел - надо удалить все ведущие пробелы

            if (para.text.empty() || isSpace(para.text.back()))
            {
                // Уже собранный текст не пуст, и последний элемент - пробел
                keepSpaceAtValueFront = false;
            }

            value = trimFront(value, keepSpaceAtValueFront /* keepOneSpace */ );

        }

        bool forceAddEmpty = false;
        if (!value.empty() || forceAddEmpty)
        {
            curTagAttributes.pos = para.text.size();
            curTagAttributes.len = value.size();
            para.text.append(value);
            para.attrs.push_back(curTagAttributes);
        }

        // return true; // continue traversal

        return debugSplitToFragments();
    }


}; // struct PugixmlGenericRichParaWalker




} // namespace marty_rich_text

