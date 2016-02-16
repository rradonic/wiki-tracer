#include <iostream>
#include <memory>

#include "sax2-handler.hpp"

SAX2Handler::SAX2Handler() : redirect(false) {
}

void SAX2Handler::startElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname,
    const xercesc::Attributes& attrs) {

    (void)uri;
    (void)qname;
    (void)attrs;

    auto deleter = [](char* p) {
        xercesc::XMLString::release(&p);
    };

    std::unique_ptr<char, decltype(deleter)> nodeName(
        xercesc::XMLString::transcode(localname),
        deleter);

    this->state.push(std::string(nodeName.get()));

    if(this->state.top() == "redirect") {
        this->redirect = true;
    }
}

void SAX2Handler::endElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname) {

    (void)uri;
    (void)qname;

    auto deleter = [](char* p) {
        xercesc::XMLString::release(&p);
    };

    std::unique_ptr<char, decltype(deleter)> nodeName(
        xercesc::XMLString::transcode(localname),
        deleter);

    if(this->state.top() == "page") {
        if(!this->redirect &&
            this->title.compare(0, 5, std::string("User:")) != 0 &&
            this->title.compare(0, 10, std::string("Wikipedia:")) != 0 &&
            this->title.compare(0, 5, std::string("File:")) != 0 &&
            this->title.compare(0, 10, std::string("MediaWiki:")) != 0 &&
            this->title.compare(0, 9, std::string("Template:")) != 0 &&
            this->title.compare(0, 5, std::string("Help:")) != 0 &&
            this->title.compare(0, 9, std::string("Category:")) != 0 &&
            this->title.compare(0, 7, std::string("Portal:")) != 0 &&
            this->title.compare(0, 5, std::string("Book:")) != 0 &&
            this->title.compare(0, 6, std::string("Draft:")) != 0 &&
            this->title.compare(0, 10, std::string("TimedText:")) != 0 &&
            this->title.compare(0, 7, std::string("Module:")) != 0 &&
            this->title.compare(0, 6, std::string("Topic:")) != 0 &&
            this->title.find("disambiguation") == std::string::npos) {

            std::cout << this->title << std::endl;
        }

        this->title.clear();
        this->content.clear();
        this->redirect = false;
    }

    this->state.pop();
}

void SAX2Handler::characters(
    const XMLCh* const chars,
    const XMLSize_t length) {

    if(this->state.top() != "title") {
        return;
    }

    std::unique_ptr<char[]> buffer(new char[length + 1]);

    xercesc::XMLString::transcode(chars, buffer.get(), length);

    this->title.append(buffer.get());
}
