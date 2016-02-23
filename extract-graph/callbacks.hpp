#pragma once

#include <stack>

#include <xercesc/sax2/DefaultHandler.hpp>

#include <wt/ufile.hpp>

class Callbacks : public xercesc::DefaultHandler {
    public:
        Callbacks(const char* outFilePath);

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
        void cleanUp();

    private:
        // a stack to track where in the XML document we are since we're using SAX2 parsing
        std::stack<icu::UnicodeString> state;

        // per-page data, reset after every page element is parsed
        icu::UnicodeString title;
        icu::UnicodeString content;
        bool redirect;

        wt::UFile outFile;
};
