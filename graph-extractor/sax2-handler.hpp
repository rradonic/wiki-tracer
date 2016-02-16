#pragma once

#include <stack>
#include <vector>

#include <xercesc/sax2/DefaultHandler.hpp>

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

    bool allowedTitle(std::string title) const;
    bool allowedLink(std::string link) const;
    bool allowed(std::string link, std::size_t pos) const;

private:
    // a stack to track where in the XML document we are since we're using SAX2 parsing
    std::stack<std::string> state;

    // per-page data, reset after every page element is parsed
    std::string title;
    std::string content;
    bool redirect;

    static const char* languages[];
};
