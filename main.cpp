#include <iostream>
#include <memory>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLString.hpp>

#include "sax2-handler.hpp"

int main (int argc, char* args[]) {
    xercesc::XMLPlatformUtils::Initialize();

    const std::string xmlFile =
        "/home/ranko/Documents/enwiki-20160204-pages-articles-multistream.xml";

    std::unique_ptr<xercesc::SAX2XMLReader> parser(xercesc::XMLReaderFactory::createXMLReader());
    parser->setFeature(xercesc::XMLUni::fgXercesSchema, false);

    std::unique_ptr<SAX2Handler> defaultHandler(new SAX2Handler());
    parser->setContentHandler(defaultHandler.get());
    parser->setErrorHandler(defaultHandler.get());

    parser->parse(xmlFile.c_str());

    return 0;
}
