
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/Instructions.h"
#include "Utils.h"

using namespace llvm;

typedef std::pair<StoreInst*, GenericValue> Spot;

class Film {
public:
  Instruction* Inst;
  GenericValue Val;
  Film* Prev;

  std::vector<GenericValue> ArgVals; // for CallInst
  Film* LastInst; // for CallInst

  unsigned EnvBefore;
  unsigned EnvAfter;

  //Film* Clue;
  

  Film(Instruction* Call, ArrayRef<GenericValue> &ArgVals0, Film* Prev, unsigned CurEnv):
    Inst(Call), Prev(Prev), LastInst(nullptr), EnvBefore(CurEnv) {
      for(GenericValue V:ArgVals0)
        ArgVals.push_back(V);
      
    }

/*
  Film(Instruction* Store, GenericValue Val, Film* Prev):
    Inst(Store), Val(Val), Prev(Prev), LastInst(nullptr) {}
  void makeStoreFilm(Instruction* Store, GenericValue Val){
    Film* newFilm = new Film(Store, Val, this->LastInst);
    this->LastInst = newFilm;
  }
*/
  Film* makeCallFilm(Instruction* Call, ArrayRef<GenericValue> &ArgVals, unsigned CurEnv){
    Film* newFilm = new Film(Call, ArgVals, this->LastInst, CurEnv);
    this->LastInst = newFilm;
    return newFilm;
  }

/*
  void dump() { dumpImpl(0); };
  Film* makeClue(Film* tail){
    if((void*)this == nullptr) return tail;
    else if(isa<StoreInst>(Inst)){
      this->Clue = this->Prev->makeClue(tail);
      return this;
    } else {
      this->Clue = this->LastInst->makeClue(this->Prev->makeClue(tail));
      return this;
    }
  }

  void dumpClue(){
    if((void*)this == nullptr) return;
    else if(StoreInst* Store = dyn_cast<StoreInst>(Inst)){

      this->Clue->dumpClue();
      llvm::outs() << Store->getPointerOperand()->getName() << '=' << Val.IntVal << '\n';
    } else {

        this->Clue->dumpClue();

        CallInst* Call = cast<CallInst>(Inst);
        llvm::outs() << Call->getCalledFunction()->getName();
     
        for(GenericValue V:ArgVals)
          llvm::outs() << ' ' <<  V.IntVal;

        llvm::outs() << " = " << Val.IntVal << '\n';
        
    }
  }

*/

private:
/*
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

   unsigned dump(unsigned i){
     if((void*)this == nullptr)return;

     unsigned k = Prev->dump(i);
     for(unsigned kk=k;kk<this->EnvBefore;kk++){
       llvm::outs() << 


     CallInst* Call = cast<CallInst>(Inst);
     llvm::outs() << Call->getCalledFunction()->getName();
     
     for(GenericValue V:ArgVals)
       llvm::outs() << ' ' <<  V.IntVal;
     llvm::outs()<<'\n';
     for(


}
*/
};
