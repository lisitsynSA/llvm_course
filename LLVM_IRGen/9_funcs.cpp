#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <stack>

/*
    S -> E
    E -> T (['+''-'] E)?
    T -> P (['*''/'] T)?
    P -> '(' E ')' | N | F
    N -> ['0' - '9']+
    F -> ['sin''cos''sqr''sqrt']+ '(' E ')'
*/

#define LENGTH 100

#define NUMBER 1
#define ACTION 2
#define FUNCTION 3

char *S;
FILE *File;

struct info_t {
  double value;
  char action;
  char *name;
  int kind;
};

struct tree_node_t {
  int level;
  info_t *info;
  tree_node_t **link;
};

struct tree_t {
  tree_node_t *root;
  int size;
};

tree_t *construct_tree();
tree_node_t *add_node_tree(tree_t *tree, tree_node_t *current, int place);

void dump_tree(tree_t *tree);
void print_node(tree_node_t *current);
void print_info(info_t *info);

void GetS(tree_t *tree, char *string);
void GetN(tree_t *tree, tree_node_t *current, int level);
void GetE(tree_t *tree, tree_node_t *current, int level);
void GetT(tree_t *tree, tree_node_t *current, int level);
void GetP(tree_t *tree, tree_node_t *current, int level);
void GetWS();
void GetF(tree_t *tree, tree_node_t *current, int level);

tree_node_t *fscanf_tree(tree_t *tree);
void copy_node(tree_node_t *current1, tree_node_t *current2);
void calloc_node(tree_node_t *current);
void level_up(tree_node_t *new_current);
void level_down(tree_node_t *current);
void shifting_node(tree_t *tree, tree_node_t *current);

void fprint_tree(tree_t *tree);
void fprint_prenode(tree_node_t *current);
void fprint_innode(tree_node_t *current);
void fprint_posnode(tree_node_t *current);
void fprint_stackVM(tree_node_t *current);
void fprint_info(info_t *info);
void fprint_cpu(info_t *info);

void LLVM_GEN(tree_t *tree);
void LLVM_GEN_node(tree_node_t *current, llvm::IRBuilder<> &builder);
void LLVM_GEN_value(info_t *info, llvm::IRBuilder<> &builder);

void destruct_tree(tree_t *tree);
void delete_node_tree(tree_node_t *current);
void free_info(info_t *info);

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cout << "[ERROR] Need 1 argument: file with exspression\n";
    return 1;
  }
  File = fopen(argv[1], "r");

  tree_t *tree = construct_tree();

  fscanf_tree(tree);
  dump_tree(tree);
  LLVM_GEN(tree);
  fprint_tree(tree);
  destruct_tree(tree);
  return 0;
}

///////////////////
/// Tree functions
///////////////////

tree_t *construct_tree() {
  tree_t *tree = (tree_t *)calloc(1, sizeof(tree_t));
  tree->size = 0;
  tree->root = NULL;
  return tree;
}

void destruct_tree(tree_t *tree) {
  if (tree->root)
    delete_node_tree(tree->root);
  free(tree);
}

void delete_node_tree(tree_node_t *current) {
  if (current == NULL)
    return;
  if (current->link[0])
    delete_node_tree(current->link[0]);
  if (current->link[1])
    delete_node_tree(current->link[1]);
  free_info(current->info);
  free(current);
}

void free_info(info_t *info) {
  if (info->name)
    free(info->name);
  free(info);
}

tree_node_t *fscanf_tree(tree_t *tree) {
  char *string = (char *)calloc(LENGTH, sizeof(char));
  fgets(string, LENGTH, File);
  fclose(File);

  GetS(tree, string);
  free(string);
  return tree->root;
}

void copy_node(tree_node_t *current1, tree_node_t *current2) {
  current2->link = current1->link;
  current2->level = current1->level;
  current2->info = current1->info;
}

void level_up(tree_node_t *current) {
  if (!current)
    return;
  current->level++;
  level_up(current->link[0]);
  level_up(current->link[1]);
}

void level_down(tree_node_t *current) {
  if (!current)
    return;
  current->level--;
  level_down(current->link[0]);
  level_down(current->link[1]);
}

void calloc_node(tree_node_t *current) {
  current->info = (info_t *)calloc(1, sizeof(info_t));
  current->link = (tree_node_t **)calloc(2, sizeof(tree_node_t *));
}

bool division = false;
bool substitution = false;

void shifting_node(tree_t *tree, tree_node_t *current) {
  tree->size += 2;
  tree_node_t *new_current = (tree_node_t *)calloc(1, sizeof(tree_node_t));
  copy_node(current, new_current);
  level_up(new_current);
  calloc_node(current);
  current->info->kind = ACTION;
  if (S[0] == '-') {
    current->info->action = '+';
    substitution = true;
  } else if (S[0] == '/') {
    current->info->action = '*';
    division = true;
  } else {
    current->info->action = S[0];
  }
  S++;
  current->link[0] = new_current;
}

/////////////////////
/// Grammar functions
/////////////////////

void GetS(tree_t *tree, char *string) {
  S = string;
  printf("%s\n", S);

  tree->size++;
  tree->root = (tree_node_t *)calloc(1, sizeof(tree_node_t));
  calloc_node(tree->root);
  GetE(tree, tree->root, 0);
}

void GetN(tree_t *tree, tree_node_t *current, int level) {
  GetWS();

  double val = 0;
  char *start_pos = S;
  while ('0' <= S[0] && S[0] <= '9')
    val = val * 10 + (S++)[0] - '0';

  if (start_pos != S) {
    calloc_node(current);
    current->info->kind = NUMBER;
    current->level = level;
    current->info->value = val;
    if (substitution) {
      current->info->value = -val;
      substitution = false;
    }
    if (division) {
      current->info->value = 1 / val;
      division = false;
    }
  } else {
    printf("ERROR:IN GetN: %s\n", S);
  }
  GetWS();
}

void GetE(tree_t *tree, tree_node_t *current, int level) {
  GetT(tree, current, level);

  if (S[0] == '+' || S[0] == '-') {
    shifting_node(tree, current);
    current->link[1] = (tree_node_t *)calloc(1, sizeof(tree_node_t));
    calloc_node(current->link[1]);
    GetE(tree, current->link[1], level + 1);
  }
}

void GetT(tree_t *tree, tree_node_t *current, int level) {
  GetWS();

  GetP(tree, current, level);

  if (S[0] == '*' || S[0] == '/') {
    shifting_node(tree, current);
    current->link[1] = (tree_node_t *)calloc(1, sizeof(tree_node_t));
    calloc_node(current->link[1]);
    GetT(tree, current->link[1], level + 1);
  }

  GetWS();
}

void GetP(tree_t *tree, tree_node_t *current, int level) {
  GetWS();
  if (S[0] == '(') {
    S++;
    GetE(tree, current, level);
    if (S[0] != ')') {
      printf("ERROR:IN GetE: %s\n", S);
    }
    S++;
  } else if ('a' <= S[0] && S[0] <= 'z')
    GetF(tree, current, level);
  else
    GetN(tree, current, level);
  GetWS();
}

void GetWS() {
  while (S[0] == ' ')
    S++;
}

void GetF(tree_t *tree, tree_node_t *current, int level) {
  GetWS();

  char *function = (char *)calloc(LENGTH, sizeof(char));
  int counter = 0;
  while ('a' <= S[0] && S[0] <= 'z')
    function[counter++] = (S++)[0];
  function[counter] = 0;

  if ((counter != 0) && ((S++)[0] == '(')) {
    current->level = level;
    if (!(strcmp(function, "sin") && strcmp(function, "cos") &&
          strcmp(function, "sqr") && strcmp(function, "sqrt"))) {
      current->info->kind = FUNCTION;
      current->info->name = function;
      tree->size++;
      current->link[0] = (tree_node_t *)calloc(1, sizeof(tree_node_t));
      calloc_node(current->link[0]);
      GetE(tree, current->link[0], level + 1);

      if ((S++)[0] != ')') {
        printf("ERROR:IN GetF: %s\n", S);
      }

      GetWS();
      return;
    }
  }
  printf("ERROR:IN GetF: %s\n", S);
  free(function);
}

///////////////////
/// Print functions
///////////////////

void dump_tree(tree_t *tree) {
  printf("\n*******TREE*******\nSIZE: %d\n------------------\n", tree->size);
  print_node(tree->root);
  printf("\n******************\n");
}

void print_node(tree_node_t *current) {
  if (!current)
    return;
  print_node(current->link[0]);
  printf("%*s", current->level * 3, " ");
  print_info(current->info);
  putc('\n', stdout);
  print_node(current->link[1]);
}

void print_info(info_t *info) {
  if (info->kind == NUMBER) {
    printf("%lg", info->value);
    return;
  }
  if (info->kind == FUNCTION) {
    printf("%s", info->name);
    return;
  }
  printf("%c", info->action);
}

void fprint_tree(tree_t *tree) {
  File = fopen("expression_check.txt", "w");
  fprint_prenode(tree->root);
  putc('\n', File);
  fprint_innode(tree->root);
  putc('\n', File);
  fprint_posnode(tree->root);
  putc('\n', File);
  fclose(File);

  File = fopen("expr.s", "w");
  fprint_stackVM(tree->root);
  fprintf(File, " pop x1\n write x1\n exit");
  fclose(File);
}

void fprint_prenode(tree_node_t *current) {
  if (!current) {
    return;
  }
  fprintf(File, "(");
  fprint_info(current->info);
  fprint_prenode(current->link[0]);
  fprint_prenode(current->link[1]);
  fprintf(File, ")");
}

void fprint_innode(tree_node_t *current) {
  if (!current) {
    return;
  }
  fprintf(File, "(");
  fprint_innode(current->link[0]);
  fprint_info(current->info);
  fprint_innode(current->link[1]);
  fprintf(File, ")");
}

void fprint_posnode(tree_node_t *current) {
  if (!current) {
    return;
  }
  fprintf(File, "(");
  fprint_posnode(current->link[0]);
  fprint_posnode(current->link[1]);
  fprint_info(current->info);
  fprintf(File, ")");
}

void fprint_info(info_t *info) {
  if (info->kind == NUMBER) {
    fprintf(File, "%lg", info->value);
    return;
  }
  if (info->kind == FUNCTION) {
    fprintf(File, "%s", info->name);
    return;
  }
  fprintf(File, "%c", info->action);
}

void fprint_stackVM(tree_node_t *current) {
  if (!current) {
    return;
  }
  fprint_stackVM(current->link[0]);
  fprint_stackVM(current->link[1]);
  fprint_cpu(current->info);
}

void fprint_cpu(info_t *info) {
  if (info->kind == NUMBER) {
    fprintf(File, " push %lg\n", info->value);
    return;
  }
  if (info->kind == FUNCTION) {
    fprintf(File, " %s\n", info->name);
    return;
  }
  switch (info->action) {
  case '+':
    fprintf(File, " add_s\n");
    break;

  case '-':
    fprintf(File, " sub_s\n");
    break;

  case '*':
    fprintf(File, " mul_s\n");
    break;

  case '/':
    fprintf(File, " div_s\n");
    break;

  default:
    fprintf(File, " error\n");
    break;
  }
}

///////////////////
/// LLVM functions
///////////////////

std::stack<llvm::Value *> stackIR;
llvm::Module *module;

void LLVM_GEN(tree_t *tree) {
  if (!tree)
    return;

  llvm::LLVMContext context;
  // ; ModuleID = 'top'
  // source_filename = "top"
  module = new llvm::Module("top", context);
  llvm::IRBuilder<> builder(context);
  // declare void @main()
  llvm::FunctionType *funcType =
      llvm::FunctionType::get(builder.getVoidTy(), false);
  llvm::Function *mainFunc = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage, "main", module);
  // entry:
  llvm::BasicBlock *mainBB =
      llvm::BasicBlock::Create(context, "entry", mainFunc);
  builder.SetInsertPoint(mainBB);

  LLVM_GEN_node(tree->root, builder);

  builder.CreateRet(stackIR.top());

  llvm::outs() << "#[LLVM IR]:\n";
  module->print(llvm::outs(), nullptr);
}

void LLVM_GEN_node(tree_node_t *current, llvm::IRBuilder<> &builder) {
  if (!current)
    return;

  LLVM_GEN_node(current->link[0], builder);
  LLVM_GEN_node(current->link[1], builder);
  LLVM_GEN_value(current->info, builder);
}

void LLVM_GEN_value(info_t *info, llvm::IRBuilder<> &builder) {
  llvm::Value *arg1;
  llvm::Value *arg2;
  llvm::Value *res;
  // NUMBER
  if (info->kind == NUMBER) {
    arg1 =
        llvm::ConstantFP::get(builder.getContext(), llvm::APFloat(info->value));
    stackIR.push(arg1);
    return;
  }
  // FUNCTION
  if (info->kind == FUNCTION) {
    llvm::FunctionType *funcType = llvm::FunctionType::get(
        builder.getDoubleTy(),
        llvm::ArrayRef<llvm::Type *>(builder.getDoubleTy()), false);
    llvm::FunctionCallee func =
        module->getOrInsertFunction(info->name, funcType);

    arg1 = stackIR.top();
    stackIR.pop();
    res = builder.CreateCall(func, llvm::ArrayRef<llvm::Value *>(arg1));
    stackIR.push(res);
    return;
  }

  // ACTION
  if (stackIR.empty())
    return;
  arg1 = stackIR.top();
  stackIR.pop();
  if (stackIR.empty())
    return;
  arg2 = stackIR.top();
  stackIR.pop();

  switch (info->action) {
  case '+':
    res = builder.CreateFAdd(arg1, arg2);
    stackIR.push(res);
    break;
  case '-':
    res = builder.CreateFSub(arg2, arg1);
    stackIR.push(res);
    break;
  case '*':
    res = builder.CreateMul(arg1, arg2);
    stackIR.push(res);
    break;
  case '/':
    res = builder.CreateUDiv(arg2, arg1);
    stackIR.push(res);
    break;
  default:
    break;
  }
}
