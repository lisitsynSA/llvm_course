# LLVM Cource examples
LLVM passes, IR generations, Flex&Bison parsers, LLVM BackEnd and simulator code examples for simple graphical SDL2 applications.

## SDL
Simple examples of graphical application with simple interface based on the SDL 2.0.
IRGen: LLVM IR generation for graphical application. Asm2IR LLVM IR generator for graphical application.

## LLVM Pass
Examples of LLVM passes that collect static application IR inforamtion, insert instrumentation for collecting dynamic information and dummy optimization passes.

## LLVM IRGen
LLVM IR generators examples:
"hello world" LLVM IR generator => Calculator based on LLVM IR => assembly file to LLVM IR lifter => mathematical expressions frontend.

## Flex_Bison
Examples of parsers based on Flex and Bison:
"hello world" => simple mathematical expressions => expressions with variables and arrays => simple programming language files => interpretation and LLVM IR building => simple FrontEnd.

## LLVM_Backend
TableGen examples. Descriptions for simple steps for LLVM Backend implimentation for `sim` target.
Steps are placed in https://github.com/lisitsynSA/llvm-add-backend.

## Simulator
Simple simulator for generated object files for `sim` target. Simulator ELF parsing is based on elfio.

## Full_Pipeline
"Compiler driver" example for programming language files.
`*.lang` => Flex_Bison parser => `*.ll` => opt => `*.opt.ll` => Custom llc => `*.opt.s` + `*.opt.o` => simulator
