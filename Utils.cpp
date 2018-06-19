
#include "Utils.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void putIndent(unsigned space){
  if(space==0)return;
  for(unsigned i=0;i<space-2;i++)
    llvm::outs() << ' ';
  llvm::outs() << "|-";
}
