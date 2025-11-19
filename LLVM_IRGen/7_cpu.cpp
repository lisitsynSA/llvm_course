#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

//////////////////////////////
// All instructions
//////////////////////////////

enum InsnId_t {
  EXIT,  // 0
  PUSH,  // imm
  POP,   // 1r
  ADD_S, // 0
  SUB_S, // 0
  MUL_S, // 0
  DIV_S, // 0
  NEG,   // 1r
  ADD,   // 3r
  SUB,   // 3r
  MUL,   // 3r
  DIV,   // 3r
  ADDI,  // 2r imm
  SUBI,  // 2r imm
  MULI,  // 2r imm
  DIVI,  // 2r imm
  B,     // imm
  RET,   // 0
  BL,    // imm
  BEQ,   // 2r imm
  BNE,   // 2r imm
  BGE,   // 2r imm
  BLT,   // 2r imm
  READ,  // 1r
  WRITE  // 1r
};

//////////////////////////////
// Model for simulation
//////////////////////////////

using RegId_t = uint8_t;
using RegVal_t = uint32_t;
using Stack_t = std::stack<RegVal_t>;

const int REG_FILE_SIZE = 4;
class CPU {
public:
  RegVal_t REG_FILE[REG_FILE_SIZE] = {};
  RegVal_t PC;
  RegVal_t NEXT_PC;
  Stack_t CALL_STACK;
  Stack_t STACK;
  uint32_t RUN;
  bool stack_ok() {
    if (STACK.empty()) {
      RUN = 0;
      outs() << "[RUNTIME ERROR] STACK ERROR\n";
      return false;
    }
    return true;
  }
  bool call_stack_ok() {
    if (CALL_STACK.empty()) {
      RUN = 0;
      outs() << "[RUNTIME ERROR] CALL STACK ERROR\n";
      return false;
    }
    return true;
  }
};

//////////////////////////////
// Universal Instruction
//////////////////////////////

class Instr {
public:
  InsnId_t m_ID;
  void (*m_INSTR)(CPU *, Instr *);
  RegId_t m_rs1;
  RegId_t m_rs2;
  RegId_t m_rs3;
  RegVal_t m_imm;
  std::string m_name;
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegId_t rs1)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_rs1(rs1) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegVal_t imm)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_imm(imm) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegId_t rs1, RegId_t rs2, RegId_t rs3)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_rs1(rs1), m_rs2(rs2),
        m_rs3(rs3) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegId_t rs1, RegId_t rs2, RegVal_t imm)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_rs1(rs1), m_rs2(rs2),
        m_imm(imm) {}
  void dump() { outs() << m_name << '\n'; }
};

//////////////////////////////
// Interpreter function
//////////////////////////////

void do_exit(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->RUN = 0;
}
void do_push(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->STACK.push(instr->m_imm);
}
void do_pop(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  cpu->REG_FILE[instr->m_rs1] = cpu->STACK.top();
  cpu->STACK.pop();
}
void do_add_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val1 + val2);
}
void do_sub_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val2 - val1);
}
void do_mul_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val1 * val2);
}
void do_div_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val2 / val1);
}
void do_neg(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = -cpu->REG_FILE[instr->m_rs1];
}
void do_add(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] + cpu->REG_FILE[instr->m_rs3];
}
void do_sub(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] - cpu->REG_FILE[instr->m_rs3];
}
void do_mul(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] * cpu->REG_FILE[instr->m_rs3];
}
void do_div(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] / cpu->REG_FILE[instr->m_rs3];
}
void do_addi(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] + instr->m_imm;
}
void do_subi(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] - instr->m_imm;
}
void do_muli(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] * instr->m_imm;
}
void do_divi(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] / instr->m_imm;
}
void do_b(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->NEXT_PC = instr->m_imm;
}
void do_ret(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->call_stack_ok()) {
    return;
  }
  cpu->NEXT_PC = cpu->CALL_STACK.top();
  cpu->CALL_STACK.pop();
}
void do_bl(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->CALL_STACK.push(cpu->PC + 1);
  cpu->NEXT_PC = instr->m_imm;
}
void do_beq(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] == cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_bne(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] != cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_bge(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] >= cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_blt(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] < cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_read(CPU *cpu, Instr *instr) {
  instr->dump();
  outs() << "[x" << (uint32_t)instr->m_rs1 << "] = ";
  std::cin >> cpu->REG_FILE[instr->m_rs1];
}
void do_write(CPU *cpu, Instr *instr) {
  instr->dump();
  outs() << "[x" << (uint32_t)instr->m_rs1
         << "] = " << cpu->REG_FILE[instr->m_rs1] << '\n';
}

void *lazyFunctionCreator(const std::string &fnName) {
  if (fnName == "do_exit") {
    return reinterpret_cast<void *>(do_exit);
  }
  if (fnName == "do_push") {
    return reinterpret_cast<void *>(do_push);
  }
  if (fnName == "do_pop") {
    return reinterpret_cast<void *>(do_pop);
  }
  if (fnName == "do_add_s") {
    return reinterpret_cast<void *>(do_add_s);
  }
  if (fnName == "do_sub_s") {
    return reinterpret_cast<void *>(do_sub_s);
  }
  if (fnName == "do_mul_s") {
    return reinterpret_cast<void *>(do_mul_s);
  }
  if (fnName == "do_div_s") {
    return reinterpret_cast<void *>(do_div_s);
  }
  if (fnName == "do_neg") {
    return reinterpret_cast<void *>(do_neg);
  }
  if (fnName == "do_add") {
    return reinterpret_cast<void *>(do_add);
  }
  if (fnName == "do_sub") {
    return reinterpret_cast<void *>(do_sub);
  }
  if (fnName == "do_mul") {
    return reinterpret_cast<void *>(do_mul);
  }
  if (fnName == "do_div") {
    return reinterpret_cast<void *>(do_div);
  }
  if (fnName == "do_addi") {
    return reinterpret_cast<void *>(do_addi);
  }
  if (fnName == "do_subi") {
    return reinterpret_cast<void *>(do_subi);
  }
  if (fnName == "do_muli") {
    return reinterpret_cast<void *>(do_muli);
  }
  if (fnName == "do_divi") {
    return reinterpret_cast<void *>(do_divi);
  }
  if (fnName == "do_b") {
    return reinterpret_cast<void *>(do_b);
  }
  if (fnName == "do_ret") {
    return reinterpret_cast<void *>(do_ret);
  }
  if (fnName == "do_bl") {
    return reinterpret_cast<void *>(do_bl);
  }
  if (fnName == "do_beq") {
    return reinterpret_cast<void *>(do_beq);
  }
  if (fnName == "do_bne") {
    return reinterpret_cast<void *>(do_bne);
  }
  if (fnName == "do_bge") {
    return reinterpret_cast<void *>(do_bge);
  }
  if (fnName == "do_blt") {
    return reinterpret_cast<void *>(do_blt);
  }
  if (fnName == "do_read") {
    return reinterpret_cast<void *>(do_read);
  }
  if (fnName == "do_write") {
    return reinterpret_cast<void *>(do_write);
  }
  outs() << "[ExecutionEngine] Can't find function " << fnName
          << ". Catch the Segmentation fault:)\n";
  return nullptr;
}

//////////////////////////////
// MAIN
//////////////////////////////

int main(int argc, char *argv[]) {
  if (argc != 2) {
    outs() << "[ERROR] Need 1 argument: file with assembler\n";
    return 1;
  }
  std::ifstream input;
  input.open(argv[1]);
  if (!input.is_open()) {
    outs() << "[ERROR] Can't open " << argv[1] << '\n';
    return 1;
  }

  std::string name;
  std::string arg1;
  std::string arg2;
  std::string arg3;
  std::vector<Instr *> Instructions;
  Instructions.push_back(
      new Instr(InsnId_t::EXIT, do_exit, "[RUNTIME ERROR] Segmentation fault"));
  // Read instruction from file
  outs() << "[FILE] BEGIN\n";
  while (input >> name) {
    outs() << name;
    // 0 registers
    if (!name.compare("exit")) {
      Instructions.push_back(new Instr(InsnId_t::EXIT, do_exit, name));
      outs() << '\n';
      continue;
    }
    if (!name.compare("ret")) {
      Instructions.push_back(new Instr(InsnId_t::RET, do_ret, name));
      outs() << '\n';
      continue;
    }
    if (!name.compare("add_s")) {
      Instructions.push_back(new Instr(InsnId_t::ADD_S, do_add_s, name));
      outs() << '\n';
      continue;
    }
    if (!name.compare("sub_s")) {
      Instructions.push_back(new Instr(InsnId_t::SUB_S, do_sub_s, name));
      outs() << '\n';
      continue;
    }
    if (!name.compare("mul_s")) {
      Instructions.push_back(new Instr(InsnId_t::MUL_S, do_mul_s, name));
      outs() << '\n';
      continue;
    }
    if (!name.compare("div_s")) {
      Instructions.push_back(new Instr(InsnId_t::DIV_S, do_div_s, name));
      outs() << '\n';
      continue;
    }

    // 3 registers
    if (!name.compare("add") || !name.compare("sub") || !name.compare("mul") ||
        !name.compare("div")) {
      input >> arg1 >> arg2 >> arg3;
      outs() << " " << arg1 << " " << arg2 << " " << arg3 << '\n';
      RegId_t rs1 = stoi(arg1.substr(1));
      RegId_t rs2 = stoi(arg2.substr(1));
      RegId_t rs3 = stoi(arg3.substr(1));
      if (!name.compare("add")) {
        Instructions.push_back(
            new Instr(InsnId_t::ADD, do_add, name, rs1, rs2, rs3));
      }
      if (!name.compare("sub")) {
        Instructions.push_back(
            new Instr(InsnId_t::SUB, do_sub, name, rs1, rs2, rs3));
      }
      if (!name.compare("mul")) {
        Instructions.push_back(
            new Instr(InsnId_t::MUL, do_mul, name, rs1, rs2, rs3));
      }
      if (!name.compare("div")) {
        Instructions.push_back(
            new Instr(InsnId_t::DIV, do_div, name, rs1, rs2, rs3));
      }
      continue;
    }

    // 1 register
    if (!name.compare("read") || !name.compare("write") ||
        !name.compare("neg") || !name.compare("pop")) {
      input >> arg1;
      outs() << " " << arg1 << '\n';
      RegId_t rs1 = stoi(arg1.substr(1));
      if (!name.compare("read")) {
        Instructions.push_back(new Instr(InsnId_t::READ, do_read, name, rs1));
      }
      if (!name.compare("write")) {
        Instructions.push_back(new Instr(InsnId_t::WRITE, do_write, name, rs1));
      }
      if (!name.compare("neg")) {
        Instructions.push_back(new Instr(InsnId_t::NEG, do_neg, name, rs1));
      }
      if (!name.compare("pop")) {
        Instructions.push_back(new Instr(InsnId_t::POP, do_pop, name, rs1));
      }
      continue;
    }

    // 1 imm
    if (!name.compare("b") || !name.compare("bl") || !name.compare("push")) {
      input >> arg1;
      outs() << " " << arg1 << '\n';
      RegVal_t imm = stoi(arg1);
      if (!name.compare("b")) {
        Instructions.push_back(new Instr(InsnId_t::B, do_b, name, imm));
      }
      if (!name.compare("bl")) {
        Instructions.push_back(new Instr(InsnId_t::BL, do_bl, name, imm));
      }
      if (!name.compare("push")) {
        Instructions.push_back(new Instr(InsnId_t::PUSH, do_push, name, imm));
      }
      continue;
    }

    // 2 registers and imm
    if (!name.compare("addi") || !name.compare("subi") ||
        !name.compare("muli") || !name.compare("divi") ||
        !name.compare("beq") || !name.compare("bne") || !name.compare("bge") ||
        !name.compare("blt")) {
      input >> arg1 >> arg2 >> arg3;
      outs() << " " << arg1 << " " << arg2 << " " << arg3 << '\n';
      RegId_t rs1 = stoi(arg1.substr(1));
      RegId_t rs2 = stoi(arg2.substr(1));
      RegVal_t imm = stoi(arg3);
      if (!name.compare("addi")) {
        Instructions.push_back(
            new Instr(InsnId_t::ADDI, do_addi, name, rs1, rs2, imm));
      }
      if (!name.compare("subi")) {
        Instructions.push_back(
            new Instr(InsnId_t::SUBI, do_subi, name, rs1, rs2, imm));
      }
      if (!name.compare("muli")) {
        Instructions.push_back(
            new Instr(InsnId_t::MULI, do_muli, name, rs1, rs2, imm));
      }
      if (!name.compare("divi")) {
        Instructions.push_back(
            new Instr(InsnId_t::DIVI, do_divi, name, rs1, rs2, imm));
      }
      if (!name.compare("beq")) {
        Instructions.push_back(
            new Instr(InsnId_t::BEQ, do_beq, name, rs1, rs2, imm));
      }
      if (!name.compare("bne")) {
        Instructions.push_back(
            new Instr(InsnId_t::BNE, do_bne, name, rs1, rs2, imm));
      }
      if (!name.compare("bge")) {
        Instructions.push_back(
            new Instr(InsnId_t::BGE, do_bge, name, rs1, rs2, imm));
      }
      if (!name.compare("blt")) {
        Instructions.push_back(
            new Instr(InsnId_t::BLT, do_blt, name, rs1, rs2, imm));
      }
      continue;
    }

    outs() << "[ERROR] Unknown instruction: " << name << '\n';
    Instructions.clear();
    return 1;
  }
  outs() << "[FILE] END\n";

  // App simulation
  outs() << "\n[EXEC] BEGIN\n";
  CPU cpu;
  for (int i = 0; i < REG_FILE_SIZE; i++) {
    cpu.REG_FILE[i] = 0;
  }
  cpu.RUN = 1;
  cpu.PC = 1;
  // Loop execution
  while (cpu.RUN) {
    cpu.NEXT_PC = cpu.PC + 1;
    Instructions[cpu.PC]->m_INSTR(&cpu, Instructions[cpu.PC]);
    cpu.PC = cpu.NEXT_PC;
  }
  outs() << "[EXEC] END\n";

  // Dump registers after simulation
  for (int i = 0; i < REG_FILE_SIZE; i++) {
    outs() << "[" << i << "] " << cpu.REG_FILE[i] << '\n';
  }

  // Build IR for application
  outs() << "[LLVM IR] BEGIN\n";
  LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  Module *module = new Module("top", context);
  IRBuilder<> builder(context);

  // declare void @main()
  FunctionType *funcType = FunctionType::get(builder.getInt32Ty(), false);
  Function *mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);
  // entry:
  BasicBlock *entryBB = BasicBlock::Create(context, "entry", mainFunc);

  builder.SetInsertPoint(entryBB);

  // createCalleeFunctions(builder, module);
  FunctionType *CalleeType = FunctionType::get(
      builder.getVoidTy(),
      ArrayRef<Type *>({builder.getInt64Ty(), builder.getInt64Ty()}), false);

  // Get pointer to CPU for function args
  Value *cpu_p = builder.getInt64((uint64_t)&cpu);
  ArrayType *regFileType = ArrayType::get(builder.getInt32Ty(), REG_FILE_SIZE);
  module->getOrInsertGlobal("regFile", regFileType);
  GlobalVariable *regFile = module->getNamedGlobal("regFile");

  for (RegVal_t PC = 1; PC < Instructions.size(); PC++) {
    /*
    // IR implementation for ADD instruction
    if (Instructions[PC]->m_ID == ADD) {
      // res
      Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                Instructions[PC]->m_rs1);
      // arg1
      Value *arg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 Instructions[PC]->m_rs2);
      // arg2
      Value *arg2_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 Instructions[PC]->m_rs3);
      Value *add_arg1_arg2 =
          builder.CreateAdd(builder.CreateLoad(builder.getInt32Ty(), arg1_p),
                            builder.CreateLoad(builder.getInt32Ty(), arg2_p));
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    // IR implementation for ADDI instruction
    if (Instructions[PC]->m_ID == ADDI) {
      // res
      Value *res_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                Instructions[PC]->m_rs1);
      // arg1
      Value *arg1_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                 Instructions[PC]->m_rs2);
      // arg2
      Value *arg2 = builder.getInt32(Instructions[PC]->m_imm);
      Value *add_arg1_arg2 = builder.CreateAdd(
          builder.CreateLoad(builder.getInt32Ty(), arg1_p), arg2);
      builder.CreateStore(add_arg1_arg2, res_p);
      continue;
    }
    */
    // Get pointer to instruction for function args
    Value *instr_p = builder.getInt64((uint64_t)Instructions[PC]);
    // Call simulation function for other instructions
    builder.CreateCall(module->getOrInsertFunction(
                           "do_" + Instructions[PC]->m_name, CalleeType),
                       ArrayRef<Value *>({cpu_p, instr_p}));
  }
  // ret i32 0
  builder.CreateRet(builder.getInt32(0));

  outs() << "[LLVM IR] DUMP\n";
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");
  outs() << "[LLVM IR] END\n";
  for (int i = 0; i < REG_FILE_SIZE; i++) {
    cpu.REG_FILE[i] = 0;
  }

  // App simulation with execution engine
  outs() << "[LLVM EE] RUN\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator(lazyFunctionCreator);
  ee->addGlobalMapping(regFile, (void *)cpu.REG_FILE);
  ee->finalizeObject();
  ArrayRef<GenericValue> noargs;

  cpu.RUN = 1;
  cpu.PC = 1;
  ee->runFunction(mainFunc, noargs);
  outs() << "[LLVM EE] END\n";

  // Registers dump after simulation with EE
  for (int i = 0; i < REG_FILE_SIZE; i++) {
    outs() << "[" << i << "] " << cpu.REG_FILE[i] << '\n';
  }

  Instructions.clear();
  return 0;
}
