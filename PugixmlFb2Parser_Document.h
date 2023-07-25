#pragma once

#include "PugixmlFb2Parser_DocumentBody.h"
#include "PugixmlFb2Parser_DocumentHeader.h"


namespace marty_rich_text {


inline
Document PugixmlFb2Parser::parseDocument(pugi::xml_node fbXmlRoot)
{
    pugi::xml_node fbNode = fbXmlRoot.child("FictionBook");
    if (!fbNode)
    {
        return Document();
    }

    Document doc;

    doc.header = parseDocumentHeader(fbNode.child("description"));

    // http://www.fictionbook.org/index.php/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82_body 
    // body - может быть несколько, основной текст только в первом.
    // <body name="notes">
    // Хотя формально количество и порядок экземпляров <body> не ограничены, но для совместимости с существующим софтом рекомендуется:
    //   Помещать весь основной текст документа в первом <body> (сразу после <description>).
    //   При наличии в тексте сносок (<a type="note">) сам текст сносок должен размещаться во втором <body> с атрибутом name="notes".
    //   При наличии кроме сносок также комментариев и т.п., что в оригинале размещено в конце книги - создается третье <body> с атрибутом name="comments" или без атрибута name.
    //   При отсутствии сносок второе и третье <body> должно отсутствовать, а весь текст размещаться в первом.

    unsigned bodyCount = 0;
    for(pugi::xml_node bodyNode=fbNode.child("body"); bodyNode; bodyCount++, bodyNode=bodyNode.next_sibling("body"))
    {
        if (!bodyCount)
        {
            // Parse main body here
            doc.body = parseSection(bodyNode);
        }
        else
        {
            if (std::string(bodyNode.attribute("name").value())=="notes")
            {
                // Parse notes here
                doc.notes = parseSection(bodyNode);
                doc.buildNotesByIdMap();
            }
            else
            {
                // Что-то еще, какие-то коментарии, но встречается не особо часто, поэтому пока не паримся
            }
        }
    }

    // Тут надо ещё что-то сделать, раздать id тем элементам, у которых нет id

    return doc;
}

// struct Document
// {
//     DocumentHeader                               header;
//     Section                                      body  ;
//     std::unordered_map<std::string, Section>     notes ;




} // namespace marty_rich_text






