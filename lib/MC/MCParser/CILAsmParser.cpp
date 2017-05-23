//===- CILAsmParser.cpp - CIL Assembly Parser -----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/MC/MCParser/MCAsmParserExtension.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/ADT/Twine.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCParser/MCAsmLexer.h"
#include "llvm/MC/MCSectionCIL.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbolCIL.h"
#include "llvm/Support/CIL.h"
using namespace llvm;

namespace {

class CILAsmParser : public MCAsmParserExtension {
  template<bool (CILAsmParser::*HandlerMethod)(StringRef, SMLoc)>
  void addDirectiveHandler(StringRef Directive) {
    MCAsmParser::ExtensionDirectiveHandler Handler = std::make_pair(
        this, HandleDirective<CILAsmParser, HandlerMethod>);

    getParser().addDirectiveHandler(Directive, Handler);
  }

  bool ParseSectionSwitch(StringRef Section, unsigned Type, unsigned Flags,
                          SectionKind Kind);

public:
  CILAsmParser() { BracketExpressionsSupported = true; }

  void Initialize(MCAsmParser &Parser) override {
    // Call the base implementation.
    this->MCAsmParserExtension::Initialize(Parser);

    addDirectiveHandler<&CILAsmParser::ParseSectionDirectiveData>(".data");
  }

  bool ParseSectionDirectiveData(StringRef, SMLoc) {
    return true;
  }
};

}

namespace llvm {

MCAsmParserExtension *createCILAsmParser() {
  return new CILAsmParser;
}

}
