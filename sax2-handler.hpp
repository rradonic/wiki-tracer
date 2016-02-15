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

private:
    // a stack to track where in the XML document we are since we're using SAX2 parsing
    std::stack<std::string> state;

    // page data we want to collect. we reset this after every page element is parsed.
    std::string title;
    std::vector<std::string> links;

    // is the current page a redirect page? we want to discard those. reset after every page element.
    bool redirect;

    // buffer for text content of current element being parsed. reset after every element.
    std::string text;
};
