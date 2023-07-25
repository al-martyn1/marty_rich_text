#pragma once

#include "ArtworkInfo.h"
#include "AuthorInfo.h"
#include "CiteEpigraphPoemSection.h"
#include "DateInfo.h"
#include "Document.h"
#include "DocumentHeader.h"
#include "DocumentInfo.h"
#include "Enums.h"
#include "Para.h"
#include "PublishingInfo.h"
#include "Stanza.h"
#include "Table.h"
#include "TdTh.h"
#include "TextAttributes.h"
#include "TextAuthor.h"
#include "TextFragment.h"
#include "Title.h"
#include "TitleInfo.h"
#include "Tr.h"
#include "TranslaterInfo.h"
#include "VariantValue.h"

#include <unordered_set>



namespace marty_rich_text {


class PugixmlFb2Parser
{

public:

    template<typename StreamType> static
    StreamType& printTagAttrs(StreamType &s, pugi::xml_node node)
    {
        for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
        {
            s << "  " << attr.name() << "=" << attr.value();
        }

        return s;
    }


public:

    Para             parsePara(pugi::xml_node node, std::unordered_set<std::string> *pProceseedAttrs);

    Para             parseSubtitle       (pugi::xml_node node);
    Para             parseImage          (pugi::xml_node node);
    Para             parseTextAuthor     (pugi::xml_node node);
    Para             parseStanzaV        (pugi::xml_node node);

    ArtworkInfo      parseArtworkInfo    (pugi::xml_node fb2DescriptionNode);
    DocumentInfo     parseDocumentInfo   (pugi::xml_node fb2DescriptionNode);
    PublishingInfo   parsePublishingInfo (pugi::xml_node fb2DescriptionNode);
    DocumentHeader   parseDocumentHeader (pugi::xml_node fb2DescriptionNode);

    TdTh             parseTdTh           (pugi::xml_node node, const std::string &tagName);

    AuthorInfo       parseAuthorInfo     (pugi::xml_node node);
    TranslaterInfo   parseTranslaterInfo (pugi::xml_node node);
    DateInfo         parseDateInfo       (pugi::xml_node node);
    DateRangeInfo    parseDateRangeInfo  (pugi::xml_node node);
    Title            parseTitle          (pugi::xml_node node);
    Stanza           parseStanza         (pugi::xml_node node);
    Tr               parseTr             (pugi::xml_node node);
    Table            parseTable          (pugi::xml_node node);
    Poem             parsePoem           (pugi::xml_node node);
    CiteEpigraph     parseCite           (pugi::xml_node node);
    CiteEpigraph     parseEpigraph       (pugi::xml_node node);
    Section          parseSection        (pugi::xml_node node);

    Document         parseDocument       (pugi::xml_node fbXmlRoot);


// Real meat goes here
#if 0
    Para parsePara(pugi::xml_node node, std::unordered_set<std::string> *pProceseedAttrs);
    Para parseSubtitle(pugi::xml_node node);
    Para parseImage(pugi::xml_node node);
    Para parseTextAuthor(pugi::xml_node node);
    Para parseStanzaV(pugi::xml_node node);
    ArtworkInfo parseArtworkInfo(pugi::xml_node fb2DescriptionNode);
    DocumentInfo parseDocumentInfo(pugi::xml_node fb2DescriptionNode);
    PublishingInfo parsePublishingInfo(pugi::xml_node fb2DescriptionNode);
    DocumentHeader parseDocumentHeader(pugi::xml_node fb2DescriptionNode);
    TdTh parseTdTh(pugi::xml_node node, const std::string &tagName);
    AuthorInfo parseAuthorInfo(pugi::xml_node node);
    TranslaterInfo parseTranslaterInfo(pugi::xml_node node);
    DateInfo parseDateInfo(pugi::xml_node node);
    DateRangeInfo parseDateRangeInfo(pugi::xml_node node);
    Title parseTitle(pugi::xml_node node);
    Stanza parseStanza(pugi::xml_node node);
    Tr parseTr(pugi::xml_node node);
    Table parseTable(pugi::xml_node node);
    Poem parsePoem(pugi::xml_node node);
    CiteEpigraph parseCite(pugi::xml_node node);
    CiteEpigraph parseEpigraph(pugi::xml_node node);
    Section parseSection(pugi::xml_node node);
#endif

}; // class PugixmlFb2Parser



} // namespace marty_rich_text

#include "PugixmlFb2Parser_Document.h"
#include "PugixmlFb2Parser_DocumentHeader.h"
#include "PugixmlFb2Parser_Para.h"
#include "parsePugixml_AttrsIdLangStyle.h"