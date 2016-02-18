#pragma once

#include <stack>
#include <vector>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/TransService.hpp>

#include <unicode/unistr.h>

class SAX2Handler : public xercesc::DefaultHandler {
    public:
        SAX2Handler();

        void startElement(
            const XMLCh* const uri,
            const XMLCh* const localname,
            const XMLCh* const qname,
            const xercesc::Attributes& attrs);

        void endElement(
            const XMLCh* const uri,
            const XMLCh* const localname,
            const XMLCh* const qname);

        void characters(const XMLCh* const chars,
            const XMLSize_t length);

        bool allowed(icu::UnicodeString text) const;

    private:
        // a stack to track where in the XML document we are since we're using SAX2 parsing
        std::stack<icu::UnicodeString> state;

        // per-page data, reset after every page element is parsed
        icu::UnicodeString title;
        icu::UnicodeString content;
        bool redirect;

        static const char* languages[];
};
