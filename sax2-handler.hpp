#include <stack>

#include <xercesc/sax2/DefaultHandler.hpp>

class SAX2Handler : public xercesc::DefaultHandler {
public:
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
    std::stack<std::string> state;
    std::string text;
};
