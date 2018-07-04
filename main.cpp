#include "llvm/AsmParser/Parser.h"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/IR/AssemblyAnnotationWriter.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/DiagnosticPrinter.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"
#include "Interpreter.h"

#include <system_error>

using namespace std;
using namespace llvm;

static cl::opt<std::string>
    InputFilename(cl::Positional, cl::desc("<input bitcode>"), cl::init("-"));

static cl::opt<std::string> OutputFilename("o",
                                           cl::desc("Override output filename"),
                                           cl::value_desc("filename"),
                                           cl::init("-"));

cl::list<std::string>
    InputArgv(cl::ConsumeAfter, cl::desc("<program arguments>..."));


static cl::opt<bool>
    ShowAnnotations("show-annotations",
                    cl::desc("Add informational comments to the .ll file"));

static cl::opt<bool> PreserveAssemblyUseListOrder(
    "preserve-ll-uselistorder",
    cl::desc("Preserve use-list order when writing LLVM assembly."),
    cl::init(false), cl::Hidden);

static cl::opt<bool>
    MaterializeMetadata("materialize-metadata",
                        cl::desc("Load module without materializing metadata, "
                                 "then materialize only the metadata"));

static void diagnosticHandler(const DiagnosticInfo &DI, void *Context) {
  raw_ostream &OS = errs();
  OS << (char *)Context << ": ";
  switch (DI.getSeverity()) {
  case DS_Error:
    OS << "error: ";
    break;
  case DS_Warning:
    OS << "warning: ";
    break;
  case DS_Remark:
    OS << "remark: ";
    break;
  case DS_Note:
    OS << "note: ";
    break;
  }

  DiagnosticPrinterRawOStream DP(OS);
  DI.print(DP);
  OS << '\n';

  if (DI.getSeverity() == DS_Error)
    exit(1);
}

static ExitOnError ExitOnErr;

static std::unique_ptr<llvm::Module> openInputFile(LLVMContext &Context) {
  StringRef extensionName = sys::path::extension(InputFilename.data());

  if (extensionName.equals(".ll")) {
    SMDiagnostic Err;
    return parseAssemblyFile(InputFilename, Err, Context);
  } else if (extensionName.equals(".bc")) {
    std::unique_ptr<MemoryBuffer> MB = ExitOnErr(
        errorOrToExpected(MemoryBuffer::getFileOrSTDIN(InputFilename)));
    std::unique_ptr<llvm::Module> M =
        ExitOnErr(getOwningLazyBitcodeModule(std::move(MB), Context,
                                             /*ShouldLazyLoadMetadata=*/true));
    if (MaterializeMetadata)
      ExitOnErr(M->materializeMetadata());
    else
      ExitOnErr(M->materializeAll());

    return M;
  } else {
    errs() << "unknown file format\n";
    return std::unique_ptr<llvm::Module>();
  }
}

/*
std::multimap<std::pair<unsigned, unsigned>, GenericValue> posMap;

void putPosMap(Film* Films){
  for(Film* F=Films; F; F=F->Clue){
    if(F->Inst->getDebugLoc()){
      const DebugLoc &Loc = F->Inst->getDebugLoc();
      auto item = std::make_pair(std::make_pair(Loc.getLine(), Loc.getCol()), F->Val);
      posMap.insert(item);
    }
  }      
}

void printPosMap(){
  for(auto item : posMap){
    unsigned line = item.first.first;
    unsigned col  = item.first.second;
    GenericValue val = item.second;
    llvm::outs() << line << ':' << col << ' ' << val.IntVal << '\n';
  }
}
*/


Film* run(Interpreter*);
Film* runf(Interpreter*);

int main(int argc, char **argv, char * const *envp){
  // Print a stack trace if we signal out.
  sys::PrintStackTraceOnErrorSignal(argv[0]);
  PrettyStackTraceProgram X(argc, argv);

  ExitOnErr.setBanner(std::string(argv[0]) + ": error: ");

  LLVMContext Context;
  llvm_shutdown_obj Y; // Call llvm_shutdown() on exit.

  Context.setDiagnosticHandler(diagnosticHandler, argv[0]);

  cl::ParseCommandLineOptions(argc, argv, "llvm IR -> C/C++ source\n");

  std::unique_ptr<llvm::Module> M = openInputFile(Context);

  Interpreter* EE = static_cast<Interpreter*>(Interpreter::create(move(M)));

  Film* MainFilm = run(EE);
//  Film* fFilm = runf(EE);


 
   MainFilm->Inst->deleteValue();
//  fFilm->Inst->deleteValue();
  return 0;
}





Film* run(Interpreter* EE){

Function* main = EE->FindFunctionNamed("main");

 EE->runFunctionAsMain(main, InputArgv, nullptr);

  Film* MainFilm = EE->MainFilm;


  return MainFilm;
}

Film* runf(Interpreter* EE){
    
  GlobalVariable* b = EE->FindGlobalVariableNamed("b");
  GenericValue Val;
  Val.IntVal = APInt(32, 900);
  GenericValue SRC =PTOGV(EE->getPointerToGlobal(b)); 
  EE->StoreValueToMemory(Val, (GenericValue *)GVTOP(SRC), b->getType()->getElementType());


  GenericValue a1;
  a1.IntVal = APInt(32, 100);
  vector<GenericValue> args;
  args.push_back(a1);


  Function* f = EE->FindFunctionNamed("f");

  EE->runFunction(f,  args);

  Film* fFilm = EE->MainFilm;

  return fFilm;

}
