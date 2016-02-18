#include <iostream>
#include <memory>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLString.hpp>

#include "sax2-handler.hpp"

void extractGraph(std::string);

int main(int argc, char* args[]) {
    if(argc < 2) {
        std::cout << "Usage: graph-extractor [FILE]" << std::endl;
        return -1;
    }

    std::string xmlFile(args[1]);

    xercesc::XMLPlatformUtils::Initialize();

    extractGraph(xmlFile);

    xercesc::XMLPlatformUtils::Terminate();

    return 0;
}

void extractGraph(std::string xmlFile) {
    std::unique_ptr<xercesc::SAX2XMLReader> parser(xercesc::XMLReaderFactory::createXMLReader());
    parser->setFeature(xercesc::XMLUni::fgXercesSchema, false);

    std::unique_ptr<SAX2Handler> defaultHandler(new SAX2Handler());
    parser->setContentHandler(defaultHandler.get());
    parser->setErrorHandler(defaultHandler.get());

    parser->parse(xmlFile.c_str());
}
