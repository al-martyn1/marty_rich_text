#pragma once

#include "CiteEpigraphPoemSection.h"
#include "DocumentHeader.h"

#include <unordered_map>

namespace marty_rich_text {


struct Document
{
    DocumentHeader                               header    ;
    Section                                      body      ;
    Section                                      notes     ;
    std::unordered_map<std::string, Section*>    notesById ; //!< Небезопасно, при копировании и присваивании надо пересобирать из notes
                                                             //!< Теоретически, можно бы сделать замут на shared_pointer, но что-то неохота уже переделывать то, что есть
                                                             //!< Еще вопрос - примечания теоретически могут быть с одинаковым id но с разными языками. Или не может? Типа, id должен быть уникальным?
    bool empty() const
    {
        return header.empty() && body.empty() && notes.empty();
    }

    void buildNotesByIdMap()
    {
        notesById.clear();

        for(auto &secNote : notes.subsections)
        {
            if (secNote.id.empty())
            {
                continue;
            }

            notesById[secNote.id] = &secNote;
        }
    }


    Document() = default;

    Document(const Document &d)
    : header(d.header)
    , body  (d.body  )
    , notes (d.notes )
    {
        buildNotesByIdMap();
    }

    Document(Document &&d)
    : header(d.header)
    , body  (d.body  )
    , notes (d.notes )
    {
        // В исходном объекте особо ничего не надо очищать, само очистится
        // Но на всякий случай очистим id map
        buildNotesByIdMap();
        d.notesById.clear();
    }

    Document& operator=(const Document &d)
    {
        if (&d!=this)
        {
            header  = d.header;
            body    = d.body  ;
            notes   = d.notes ;
            buildNotesByIdMap();
        }

        return *this;
    }

    Document& operator=(Document &&d)
    {
        if (&d!=this)
        {
            header  = d.header;
            body    = d.body  ;
            notes   = d.notes ;
            buildNotesByIdMap();
        d.notesById.clear();
        }

        return *this;
    }

};



} // namespace marty_rich_text


