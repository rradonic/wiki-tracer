#include <iostream>
#include <memory>

#include "sax2-handler.hpp"

void SAX2Handler::startElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname,
    const xercesc::Attributes& attrs) {

    auto deleter = [](char* p) {
        xercesc::XMLString::release(&p);
    };

    std::unique_ptr<char, decltype(deleter)> nodeName(
        xercesc::XMLString::transcode(localname),
        deleter);

    this->state.push(std::string(nodeName.get()));
}

void SAX2Handler::endElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname) {

    auto deleter = [](char* p) {
        xercesc::XMLString::release(&p);
    };

    std::unique_ptr<char, decltype(deleter)> nodeName(
        xercesc::XMLString::transcode(localname),
        deleter);

    if(this->state.top() == "title") {
        std::cout << this->text << std::endl;
    }

    this->state.pop();
    this->text.clear();
}

void SAX2Handler::characters(
    const XMLCh* const chars,
    const XMLSize_t length) {

    if(this->state.top() != "title") {
        return;
    }

    std::unique_ptr<char[]> buffer(new char[length + 1]);

    xercesc::XMLString::transcode(chars, buffer.get(), length);

    this->text.append(buffer.get());
}
