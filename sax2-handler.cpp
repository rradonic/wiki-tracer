#include <iostream>

#include "sax2-handler.hpp"

void SAX2Handler::startElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname,
    const xercesc::Attributes& attrs) {

    char* message = xercesc::XMLString::transcode(localname);
    std::cout << "I saw element: "<< message << std::endl;
    xercesc::XMLString::release(&message);
}
