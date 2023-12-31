#pragma once

#include "StyleSheet.h"
#include "TextAttributes.h"
#include "TextFragment.h"
#include "VariantValue.h"
#include "utils.h"

#include <string>
#include <unordered_map>
#include <utility>



namespace marty_rich_text{


//! Параграф/абзац (блок) текста
/*! Абзац - это то, что не содержит принудительных переводов строки.

    Абзац — отрезок письменной речи, состоящий из одного или нескольких предложений,
    зачастую объединённых общей мыслью. Это привычное нам определение.

    Параграф в HTML совсем другой. Параграфы в HTML — это всего лишь неразрывная
    последовательность фразовых элементов, то есть чисто структурная, а не смысловая сущность.

    Абзац и параграф - https://nqst.livejournal.com/2571.html

    Абзац, Строфа, фрагмент, параграф, глава - http://www.nazaykin.ru/lekcii/copywriting/sozdanie_texta/abzac.htm

    Данный класс - некое подобие параграфа HTML.

*/
struct Para
{
    EParaType                      paraType = EParaType::normal; //!< Тип параграфа: normal, code, emptyLine
    EAlign                         align    = EAlign::left     ; //!< Выравнивание, по умолчанию - по левому краю. Или - undefined?

    std::string                    id;    //!< (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
    std::string                    style; //!< (опциональный) - стиль параграфа
    std::string                    lang;  //!< xml:lang (опциональный) - язык.

    std::string                    text ; //!< Текст параграфа
    std::vector<TextAttributes>    attrs; //!< Атрибуты параграфа


    Para toPlainPara() const
    {
        if (empty())
        {
            return emptyLine();
        }

        Para paraRes; // = *this

        if (isCode())
        {
            paraRes.paraType = EParaType::code;
        }
        else if (isTeletype())
        {
            paraRes.paraType = EParaType::teletype;
        }
        else if (isPre())
        {
            paraRes.paraType = EParaType::pre;
        }
        else
        {
            paraRes.paraType = paraType; // EParaType::normal;
        }

        // image        = 4 /*!< Имеется один атрибут с флагом image, сам para не содержит текста */,


        paraRes.align = align;

        paraRes.id    = id   ;
        paraRes.style = style;
        paraRes.lang  = lang ;

        // if (attrs.size()<2)
        // {
        //     paraRes.attrs = attrs;
        // }

        for(const auto &attr: attrs)
        {
            auto textSize = text.size();
            auto attrPosB = attr.pos;
            auto attrPosE = attr.pos + attr.len;

            if (attrPosB>=textSize || attrPosE>textSize)
            {
                continue; // что-то пошло не так, но агриться не будет, потому что такого не должно быть, а если и есть, то пох, будет заметно в пропаданиях текста.
            }

            // Тут считаем, что ссылки на сноски не имеют внутри какого-либо форматирования и идут одним блоком
            if ((attr.style&BasicStyleFlags::link)!=0)
            {
                if (attr.len>1 && text[attrPosB]=='[' && text[attrPosE-1]==']')
                {
                    continue; // Это ссылка на сноску, пропускаем
                }
            }
            else if ((attr.style&BasicStyleFlags::image)!=0)
            {
                continue; // Пропускаем картинки
            }

            paraRes.text.append(text, attr.pos, attr.len);
        
        }
        
        switch(paraRes.paraType)
        {
            case EParaType::code      : paraRes.attrs.emplace_back(TextAttributes{BasicStyleFlags::code    , BasicStyleFlags::code    , 0, paraRes.text.size() }); break;
            case EParaType::teletype  : paraRes.attrs.emplace_back(TextAttributes{BasicStyleFlags::teletype, BasicStyleFlags::teletype, 0, paraRes.text.size() }); break;
            case EParaType::pre       : paraRes.attrs.emplace_back(TextAttributes{BasicStyleFlags::pre     , BasicStyleFlags::pre     , 0, paraRes.text.size() }); break;
            case EParaType::unknown   : [[fallthrough]];
            case EParaType::normal    : [[fallthrough]];
            case EParaType::image     : [[fallthrough]];
            case EParaType::emptyLine : [[fallthrough]];
            case EParaType::title     : [[fallthrough]];
            case EParaType::subtitle  : [[fallthrough]];
            case EParaType::textAuthor: [[fallthrough]];
            case EParaType::stanzaV   : [[fallthrough]];
            default                   : paraRes.attrs.emplace_back(TextAttributes{BasicStyleFlags::blank   , BasicStyleFlags::blank   , 0, paraRes.text.size() });
        }

        return paraRes;
    }

    std::string toPlainText() const
    {
        return toPlainPara().text;
    }

    std::vector<Para> toPlainParas() const
    {
        std::vector<Para> res;
        res.emplace_back(toPlainPara());
        return res;
    }

    std::vector<Para> toParas(const StyleSheet &sh, std::size_t secLevel=0) const
    {
        MARTY_ARG_USED(secLevel);
        MARTY_ARG_USED(sh);
        std::vector<Para> res;
        res.emplace_back(*this);
        return res;
    }

    static
    Para emptyLine()
    {
        Para p;
        p.paraType = EParaType::emptyLine;
        //paraRes.attrs.emplace_back(TextAttributes{BasicStyleFlags::blank   , BasicStyleFlags::blank   , 0, 0 });
        return p;
    }

    static
    Para normalPara(const std::string &t)
    {
        Para p;
        p.paraType = EParaType::normal;
        p.text     = t;
        p.attrs.emplace_back(TextAttributes{BasicStyleFlags::blank   , BasicStyleFlags::blank   , 0, p.text.size() });
        return p;
    }

    bool empty() const
    {
        if (paraType==EParaType::emptyLine)
            return true;

        if (text.empty() && attrs.empty())
            return true;

        for(const auto &attr: attrs)
        {
            if ((attr.style&BasicStyleFlags::image)!=0)
                return false;
        }

        // Параграф с единственным пробелом является пустым
        if (text==" ")
        {
            return true;
        }

        // Или параграф из одних пробелов - пустой? Потом разберёмся

        return false;
    }

    bool allAttrsHasFlags(BasicStyleFlags f) const
    {
        if (attrs.empty() || f==BasicStyleFlags::blank)
        {
            return false;
        }

        for(const auto &attr: attrs)
        {
            if ((attr.style&f)==f)
                continue;

            return false;
        }

        return true;
    }

    bool isCode() const
    {
        return allAttrsHasFlags(BasicStyleFlags::code);
    }

    bool isTeletype() const
    {
        return allAttrsHasFlags(BasicStyleFlags::teletype);
    }

    bool isPre() const
    {
        return allAttrsHasFlags(BasicStyleFlags::pre);
    }

    //TODO: !!! isImage - содержит только img/image и ничего больше. Также завести ещё одно значение EParaType для Image


    // Тут надо что-то сделать, проверки, чтобы атрибуты не перекрывались, может, что-то ещё
    // Или - пофиг? Поверим на слово

    //! Проверяем, покрывают ли атрибуты весь текст
    bool checkAttrs() const
    {
        if (attrs.empty())
            return false;

        if (attrs.front().pos>0)
            return false;

        std::size_t lastAttrEnd = attrs.back().pos + attrs.back().len;
        if (lastAttrEnd<text.size())
            return false;

        return true;
    }

    // Фиксим атрибуты, чтобы они покрывали весь текст
    void fixAttrs()
    {
        // дополняем атрибуты слева и справа, если не вся строка ими покрыта

        if (attrs.empty())
        {
            TextAttributes attr; // style is blank by default
            attr.pos = 0;
            attr.len = text.size();
            attrs.emplace_back(attr);
            return;
        }

        if (attrs.front().pos>0)
        {
            TextAttributes attr; // style is blank by default
            attr.pos = 0;
            attr.len = attrs[0].pos;
            attrs.insert(attrs.begin(), attr);
        }

        std::size_t lastAttrEnd = attrs.back().pos + attrs.back().len;

        if (lastAttrEnd<text.size())
        {
            TextAttributes attr; // style is blank by default
            attr.pos = lastAttrEnd;
            attr.len = text.size()-lastAttrEnd;

            #if defined(_MSC_VER)
                #pragma warning(push)
                #pragma warning(disable:5045) // warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
            #endif

            attrs.emplace_back(attr);

            #if defined(_MSC_VER)
                #pragma warning(pop)
            #endif

        }

    }

    std::vector<TextFragment> splitToFragments() const
    {
        if (!checkAttrs())
        {
            throw std::runtime_error("marty_rich_text::Para::splitToFragments: not all text covered by attributes, please call fixAttrs() first");
        }

        std::vector<TextFragment> fragments;

        for(const auto &attr: attrs)
        {
            // А надо ли проверять на перекрытие?

            fragments.emplace_back(TextFragment{trimBoth(std::string(text, attr.pos, attr.len), isSpace), attr});

        }

        return fragments;
    }

    void mergeEqualAttrs()
    {
        std::vector<TextAttributes> newAttrs; newAttrs.reserve(attrs.size());

        std::vector<TextAttributes>::const_iterator ait = attrs.begin();

        for(; ait!=attrs.end(); ++ait)
        {
            if (newAttrs.empty())
            {
                newAttrs.emplace_back(*ait);

            }
            else
            {
                if (newAttrs.back().styleEqual(*ait))
                {
                    newAttrs.back().len += ait->len;
                }
                else
                {
                    newAttrs.emplace_back(*ait);
                }
            }
        }

        std::swap(attrs, newAttrs);

    }


}; // struct Para


inline
void appendParas(std::vector<Para> &appendTo, const std::vector<Para> &parasToAppend)
{
    appendTo.insert(appendTo.end(), parasToAppend.begin(), parasToAppend.end());
}


inline
std::string toPlainText(const Para &p)
{
    return p.toPlainText();
}

inline
std::vector<std::string> toPlainText(const std::vector<Para> &pv)
{
    std::vector<std::string> textVec;

    for(const auto &p : pv)
    {
        textVec.emplace_back(p.toPlainText());
    }

    return textVec;
}


//! Раздвигаем список параграфов, добавлем по необходимости пустые
inline
std::vector<Para> expandParas(const std::vector<Para> &paras)
{
    std::vector<Para> resParas;

    for(const auto &p: paras)
    {
        resParas.emplace_back(p);

        if (p.paraType==EParaType::subtitle)
        {
            resParas.emplace_back(Para::emptyLine());
        }
    }

    return resParas;
}

inline
std::vector<Para> compressEmptyParas(const std::vector<Para> &paras)
{
    std::vector<Para> resParas;

    for(const auto &p: paras)
    {
        if (p.empty() && !resParas.empty() && resParas.back().empty())
        {
            continue;
        }

        resParas.emplace_back(p);
    }

    return resParas;
}

inline
std::vector<Para> expandCompressParas(const std::vector<Para> &paras)
{
    return compressEmptyParas(expandParas(paras));
}


/*
    Параграфы типа EParaType::pre, EParaType::code и EParaType::teletype
    это на самом деле отдельные строки кода, после них не нужно делать отбивку
    отдельной строкой.

    В противном случае, после каждого параграфа надо добавлять пустой параграф

    В итоге - добавляем пустой параграф после каждого параграфа всегда, кроме:
      empty()
      code
      teletype
      pre
      title
      subtitle
      stanzaV

*/
//! Текстифицирование - преобразование в простой текст
inline
std::vector<Para> textifyParas(const std::vector<Para> &paras)
{
    std::vector<Para> resParas;

    for(const auto &p : paras)
    {
        resParas.emplace_back(p);

        if (p.empty())
        {
            continue;
        }

        switch(p.paraType)
        {
            case EParaType::emptyLine : break;
            case EParaType::code      : break;
            case EParaType::teletype  : break;
            case EParaType::pre       : break;
            case EParaType::title     : break;
            case EParaType::subtitle  : break;
            case EParaType::stanzaV   : break;

            case EParaType::invalid   : break;

            case EParaType::image     : [[fallthrough]];
            case EParaType::normal    : [[fallthrough]];
            case EParaType::textAuthor: [[fallthrough]];
            
            default:
                resParas.emplace_back(Para::emptyLine());
        }
    }

    return compressEmptyParas(resParas); // compress - на всякий случай
}



} // namespace marty_rich_text

