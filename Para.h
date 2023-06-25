#pragma once

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
    std::string                    text ; //!< Текст параграфа
    std::vector<TextAttributes>    attrs; //!< Атрибуты параграфа

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
            attrs.emplace_back(attr);
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


} // namespace marty_rich_text

