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
#include <fstream>
#include <iostream>
#include <unordered_map>

/*
    G0::= E
    E ::= T {['+''-'] T}*
    T ::= D {'*' D}*
    D ::= P {'^' D}*
    P ::= '(' E ')' | N | F
    N ::= ['0' - '9']+
    F ::= ['a' - 'z']+ '(' E ')'
*/

#define MAX_LENGTH 20
#define NODE 2
#define LENGTH 100

#define NUMBER 1
#define ACTION 2
#define FUNCTION 3

char *S;
int Error;
const char *Namefile;
FILE *File;

struct info_t {
  int value;
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

void GetG0(tree_t *tree, char *string);
void GetN(tree_t *tree, tree_node_t *current, int level);
void GetE(tree_t *tree, tree_node_t *current, int level);
void GetT(tree_t *tree, tree_node_t *current, int level);
void GetD(tree_t *tree, tree_node_t *current, int level);
void GetP(tree_t *tree, tree_node_t *current, int level);
void GetS();
void GetF(tree_t *tree, tree_node_t *current, int level);

tree_node_t *fscanf_tree(tree_t *tree);
void copy_node(tree_node_t *current1, tree_node_t *current2);
void calloc_node(tree_node_t *current);
void level_up(tree_node_t *new_current);
void level_down(tree_node_t *current);
void shifting_node(tree_t *tree, tree_node_t *current);

void node_ok(tree_node_t *current, int *size, int level);
void tree_ok(tree_t *tree);
#define ASSERT(tree)                                                           \
  if (tree)                                                                    \
    tree_ok(tree);                                                             \
  else                                                                         \
    printf("TREE doesn't exist");

void fprint_tree(tree_t *tree);
void fprint_posnode(tree_node_t *current);
void fprint_innode(tree_node_t *current);
void fprint_info(info_t *info);
void fprint_cpu(info_t *info);

void LLVM_GEN(tree_t *tree);
void LLVM_GEN_posnode(tree_node_t *current, llvm::IRBuilder<> &builder);
void LLVM_GEN_cpu(info_t *info, llvm::IRBuilder<> &builder);

void destruct_tree(tree_t *tree);
void delete_node_tree(tree_node_t *current);
void free_info(info_t *info);

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cout << "[ERROR] Need 1 argument: file with exspression\n";
    return 1;
  }
  Namefile = argv[1];

  tree_t *tree = construct_tree();
  tree_node_t *current = NULL;

  fscanf_tree(tree);
  fprint_tree(tree);
  // dump_tree(tree);
  destruct_tree(tree);
  return 0;
}

tree_t *construct_tree() {
  tree_t *tree = (tree_t *)calloc(1, sizeof(tree_t));
  tree->size = 0;
  tree->root = NULL;

  ASSERT(tree)
  return tree;
}

void destruct_tree(tree_t *tree) {
  ASSERT(tree)

  if (tree->root)
    delete_node_tree(tree->root);
  free(tree);
}

void delete_node_tree(tree_node_t *current) {
  if (current == NULL)
    return;
  for (int i = 0; i < NODE; i++)
    if (current->link[i])
      delete_node_tree(current->link[i]);
  free_info(current->info);
  free(current);
}

void free_info(info_t *info) {
  if (info->name)
    free(info->name);
  free(info);
}

void dump_tree(tree_t *tree) {
  ASSERT(tree)

  printf("\n*******TREE*******\nSIZE: %d\n------------------\n", tree->size);
  print_node(tree->root);
  printf("\n******************\n");

  ASSERT(tree)
}

void print_node(tree_node_t *current) {
  if (!current)
    return;
  print_node(current->link[0]);
  printf("%*s", current->level * 3, " ");
  print_info(current->info);
  printf("\n");
  print_node(current->link[1]);
}

void print_info(info_t *info) {
  if (info->kind == NUMBER) {
    printf("%d", info->value);
    return;
  }
  if (info->kind == FUNCTION) {
    printf("%s", info->name);
    return;
  }
  printf("%c", info->action);
}

tree_node_t *fscanf_tree(tree_t *tree) {
  ASSERT(tree)

  File = fopen(Namefile, "r");
  char *string = (char *)calloc(LENGTH, sizeof(char));
  fgets(string, LENGTH, File);
  fclose(File);

  GetG0(tree, string);
  free(string);

  ASSERT(tree)
  return tree->root;
}

void GetG0(tree_t *tree, char *string) {
  ASSERT(tree)
  // printf("G0\n");dump_tree(tree);

  S = string;
  Error = 0;

  tree->size++;
  tree->root = (tree_node_t *)calloc(1, sizeof(tree_node_t));
  calloc_node(tree->root);
  GetE(tree, tree->root, 0);

  if (S[0])
    printf("%s\n", string);
  switch (Error) {
  case 1:
    printf("ERROR in GETN!!!");
    break;

  case 2:
    printf("ERROR in GETP!!!");
    break;

  case 3:
    printf("ERROR in GETF!!!");
    break;
  }

  ASSERT(tree)
}

void GetN(tree_t *tree, tree_node_t *current, int level) {
  ASSERT(tree)
  // printf("N\n");dump_tree(tree);

  GetS();

  double val = 0;
  char *dap = S;
  while ('0' <= S[0] && S[0] <= '9')
    val = val * 10 + (S++)[0] - '0';

  if (dap != S) {
    calloc_node(current);
    current->info->kind = NUMBER;
    current->level = level;
    current->info->value = val;
  } else {
    Error = 1;
    printf("ERROR:IN GETN: %s\n", S);
  }
  GetS();

  ASSERT(tree)
}

void GetE(tree_t *tree, tree_node_t *current, int level) {
  ASSERT(tree)
  // printf("E\n");dump_tree(tree);

  GetS();

  GetT(tree, current, level);

  if (S[0] == '+' || S[0] == '-') {
    shifting_node(tree, current);
    current->link[1] = (tree_node_t *)calloc(1, sizeof(tree_node_t));
    calloc_node(current->link[1]);
    GetE(tree, current->link[1], level + 1);
  }

  GetS();

  ASSERT(tree)
}

void GetT(tree_t *tree, tree_node_t *current, int level) {
  ASSERT(tree)
  // printf("T\n");dump_tree(tree);

  GetS();

  GetD(tree, current, level);

  if (S[0] == '*' || S[0] == '/') {
    shifting_node(tree, current);
    current->link[1] = (tree_node_t *)calloc(1, sizeof(tree_node_t));
    calloc_node(current->link[1]);
    GetT(tree, current->link[1], level + 1);
  }

  GetS();

  ASSERT(tree)
}

void GetD(tree_t *tree, tree_node_t *current, int level) {
  ASSERT(tree)
  // printf("D\n");dump_tree(tree);

  GetS();

  GetP(tree, current, level);

  if ((S)[0] == '^') {
    shifting_node(tree, current);
    current->link[1] = (tree_node_t *)calloc(1, sizeof(tree_node_t));
    calloc_node(current->link[1]);
    GetD(tree, current->link[1], level + 1);
  }

  GetS();

  ASSERT(tree)
}

void GetP(tree_t *tree, tree_node_t *current, int level) {
  ASSERT(tree)
  // printf("P\n");dump_tree(tree);

  GetS();

  if (S[0] == '(') {
    S++;
    GetE(tree, current, level);
    if (S[0] != ')') {
      Error = 2;
      printf("ERROR:IN GETE: %s\n", S);
    }
    S++;
  } else if ('a' <= S[0] && S[0] <= 'z')
    GetF(tree, current, level);
  else
    GetN(tree, current, level);

  GetS();

  ASSERT(tree)
}

void GetS() {
  while (S[0] == ' ' || S[0] == 10)
    S++;
}

void GetF(tree_t *tree, tree_node_t *current, int level) {
  ASSERT(tree)
  // printf("F\n");dump_tree(tree);

  GetS();

  char *function = (char *)calloc(LENGTH, sizeof(char));
  int counter = 0;
  function[counter] = (S++)[0];
  char *dap = S;
  while ('a' <= S[0] && S[0] <= 'z')
    function[++counter] = (S++)[0];
  function[++counter] = 0;

  GetS();

  if ((dap != S) && ((S++)[0] == '(')) {
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
        Error = 3;
        printf("ERROR:IN GETF: %s\n", S);
      }

      GetS();

      ASSERT(tree)

      return;
    }
  }
  Error = 3;
  printf("ERROR:IN GETF: %s\n", S);
  free(function);

  ASSERT(tree)
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

void shifting_node(tree_t *tree, tree_node_t *current) {
  ASSERT(tree)

  tree->size += 2;
  tree_node_t *new_current = (tree_node_t *)calloc(1, sizeof(tree_node_t));
  ;
  copy_node(current, new_current);
  level_up(new_current);
  calloc_node(current);
  current->info->kind = ACTION;
  current->info->action = (S++)[0];
  current->link[0] = new_current;

  ASSERT(tree)
}

void fprint_tree(tree_t *tree) {
  ASSERT(tree)

  File = fopen("expression_check.txt", "w");
  fprint_innode(tree->root);
  fclose(File);

  File = fopen("expr.s", "w");
  fprint_posnode(tree->root);
  fprintf(File, " pop x1\n write x1\n exit");
  fclose(File);

  LLVM_GEN(tree);

  ASSERT(tree)
}

void fprint_innode(tree_node_t *current) {
  if (!current) {
    // fprintf(File,"n");
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
    // fprintf(File,"n");
    return;
  }
  fprint_posnode(current->link[0]);
  fprint_posnode(current->link[1]);
  fprint_cpu(current->info);
}

void fprint_info(info_t *info) {
  if (info->kind == NUMBER) {
    fprintf(File, "%d", info->value);
    return;
  }
  if (info->kind == FUNCTION) {
    fprintf(File, "%s", info->name);
    return;
  }
  fprintf(File, "%c", info->action);
}

void fprint_cpu(info_t *info) {
  if (info->kind == NUMBER) {
    fprintf(File, " push %d\n", info->value);
    return;
  }
  if (info->kind == FUNCTION) {
    fprintf(File, " %s\n", info->name);
    return;
  }
  switch (info->action) {
  case '^':
    fprintf(File, " pow_s\n");
    break;

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

std::vector<llvm::Value *> stackIR;
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

  LLVM_GEN_posnode(tree->root, builder);

  builder.CreateRet(stackIR.back());

  llvm::outs() << "#[LLVM IR]:\n";
  module->print(llvm::outs(), nullptr);
}

void LLVM_GEN_posnode(tree_node_t *current, llvm::IRBuilder<> &builder) {
  if (!current)
    return;

  LLVM_GEN_posnode(current->link[0], builder);
  LLVM_GEN_posnode(current->link[1], builder);
  LLVM_GEN_cpu(current->info, builder);
}

void LLVM_GEN_cpu(info_t *info, llvm::IRBuilder<> &builder) {
  llvm::Value *arg1;
  llvm::Value *arg2;
  llvm::Value *res;
  if (info->kind == NUMBER) {
    // fprintf(File, " push %d\n", info->value);
    arg1 = llvm::ConstantInt::get(builder.getInt32Ty(), info->value);
    stackIR.push_back(arg1);
    return;
  }
  if (info->kind == FUNCTION) {
    fprintf(File, " %s\n", info->name);
    llvm::FunctionType *funcType = llvm::FunctionType::get(
        builder.getInt32Ty(),
        llvm::ArrayRef<llvm::Type *>(builder.getInt32Ty()), false);
    llvm::FunctionCallee func =
        module->getOrInsertFunction(info->name, funcType);

    arg1 = stackIR.back();
    stackIR.pop_back();
    res = builder.CreateCall(func, llvm::ArrayRef<llvm::Value *>(arg1));
    stackIR.push_back(res);
    return;
  }
  switch (info->action) {
  case '+':
    // fprintf(File, " add_s\n");
    if (stackIR.empty())
      return;
    arg1 = stackIR.back();
    stackIR.pop_back();
    if (stackIR.empty())
      return;
    arg2 = stackIR.back();
    stackIR.pop_back();
    res = builder.CreateAdd(arg1, arg2);
    stackIR.push_back(res);
    break;

  case '-':
    // fprintf(File, " sub_s\n");
    if (stackIR.empty())
      return;
    arg1 = stackIR.back();
    stackIR.pop_back();
    if (stackIR.empty())
      return;
    arg2 = stackIR.back();
    stackIR.pop_back();
    res = builder.CreateSub(arg2, arg1);
    stackIR.push_back(res);
    break;

  case '*':
    // fprintf(File, " mul_s\n");
    if (stackIR.empty())
      return;
    arg1 = stackIR.back();
    stackIR.pop_back();
    if (stackIR.empty())
      return;
    arg2 = stackIR.back();
    stackIR.pop_back();
    res = builder.CreateMul(arg1, arg2);
    stackIR.push_back(res);
    break;

  case '/':
    // fprintf(File, " div_s\n");
    if (stackIR.empty())
      return;
    arg1 = stackIR.back();
    stackIR.pop_back();
    if (stackIR.empty())
      return;
    arg2 = stackIR.back();
    stackIR.pop_back();
    res = builder.CreateUDiv(arg2, arg1);
    stackIR.push_back(res);
    break;

  default:
    // fprintf(File, " error\n");
    break;
  }
}

void tree_ok(tree_t *tree) {
  int size = tree->size;
  node_ok(tree->root, &size, 0);
}

void node_ok(tree_node_t *current, int *size, int level) {
  if (!current)
    return;
  if ((*size == 0) && (current) && (current->level != level))
    printf("ERROR IN TREE!!!\n");

  for (int i = 0; i < NODE; i++) {
    if (current->link[i])
      node_ok(current->link[i], &--(*size), level + 1);
  }
}
