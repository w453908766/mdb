
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/Instructions.h"
#include "Utils.h"

using namespace llvm;


class Film {
public:
  Instruction* Inst;
  GenericValue Val;
  Film* Prev;

  std::vector<GenericValue> ArgVals;
  Film* LastInst;

  Film(Instruction* Call, ArrayRef<GenericValue> &ArgVals0, Film* Prev): 
    Inst(Call), Prev(Prev), LastInst(nullptr) {
      for(GenericValue V:ArgVals0)
        ArgVals.push_back(V);
    }

  Film(Instruction* Store, GenericValue Val, Film* Prev):
    Inst(Store), Val(Val), Prev(Prev), LastInst(nullptr) {}

  void makeStoreFilm(Instruction* Store, GenericValue Val){
    Film* newFilm = new Film(Store, Val, this->LastInst);
    this->LastInst = newFilm;
  }

  Film* makeCallFilm(Instruction* Call, ArrayRef<GenericValue> &ArgVals){
    Film* newFilm = new Film(Call, ArgVals, this->LastInst);
    this->LastInst = newFilm;
    return newFilm;
  }

  void dump() { dumpImpl(0); };
private:

  void dumpImpl(unsigned space){
    if((void*)this == nullptr) return;
      Prev->dumpImpl(space);
      putIndent(space);
      if(StoreInst* Store = dyn_cast<StoreInst>(Inst))
        llvm::outs() << Store->getPointerOperand()->getName() << '=' << Val.IntVal << '\n';
      else {
        CallInst* Call = cast<CallInst>(Inst);
        llvm::outs() << Call->getCalledFunction()->getName();
     
        for(GenericValue V:ArgVals)
          llvm::outs() << ' ' <<  V.IntVal;
        llvm::outs()<<'\n';

        LastInst->dumpImpl(space+2);

        putIndent(space+2);
        llvm::outs() << "return " << Val.IntVal << '\n';
      }
}

};
