#include <memory>

#include <unicode/ustdio.h>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLString.hpp>

#include "callbacks.hpp"

void extractGraph(const char* inFilePath, const char* outFilePath);

int main(int argc, char* args[]) {
    if(argc < 3) {
        u_printf("Usage: extract-graph [INFILE] [OUTFILE]\n");
        return -1;
    }

    xercesc::XMLPlatformUtils::Initialize();

    u_printf("Extracting graph information...\n");
    extractGraph(args[1], args[2]);
    u_printf("Done.\n");

    xercesc::XMLPlatformUtils::Terminate();

    return 0;
}

void extractGraph(const char* inFilePath, const char* outFilePath) {
    std::unique_ptr<xercesc::SAX2XMLReader> parser(xercesc::XMLReaderFactory::createXMLReader());
    parser->setFeature(xercesc::XMLUni::fgXercesSchema, false);

    std::unique_ptr<Callbacks> defaultHandler(new Callbacks(outFilePath));
    parser->setContentHandler(defaultHandler.get());
    parser->setErrorHandler(defaultHandler.get());

    parser->parse(inFilePath);
}
