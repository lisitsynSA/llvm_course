#include "../SDL/sim.h"

#include <iostream>
#include <string>
#include "elfio/elfio.hpp"

using namespace ELFIO;

int main( int argc, char** argv )
{
    if ( argc != 2 ) {
        std::cout << "Usage: " << argv[0] << " <elf_file>" << std::endl;
        return 1;
    }

    // Create an elfio reader
    elfio reader;

    // Load ELF data
    if ( !reader.load( argv[1] ) ) {
        std::cout << "Can't find or process ELF file " << argv[1] << std::endl;
        return 2;
    }

    // Print ELF file sections info
    Elf_Half sec_num = reader.sections.size();
    const uint32_t* code = nullptr;
    Elf_Xword code_size = 0;
    Elf_Xword code_start = 0;
    for ( int i = 0; i < sec_num; ++i ) {
        section* psec = reader.sections[i];
        if (psec->get_name() == ".text") {
            code = (const uint32_t*)reader.sections[i]->get_data();
            code_size = psec->get_size() / 4;
            std::cout << "  [" << i << "] " << psec->get_name() << "\t"
                    << psec->get_size() << std::endl;
        }
    }

    for ( int i = 0; i < sec_num; ++i ) {
        section* psec = reader.sections[i];
        // Check section type
        if ( psec->get_type() == SHT_SYMTAB ) {
            const symbol_section_accessor symbols( reader, psec );
            for ( unsigned int j = 0; j < symbols.get_symbols_num(); ++j ) {
                std::string   name;
                Elf64_Addr    value;
                Elf_Xword     size;
                unsigned char bind;
                unsigned char type;
                Elf_Half      section_index;
                unsigned char other;

                // Read symbol properties
                symbols.get_symbol( j, name, value, size, bind, type,
                                    section_index, other );
                if (name == "app") {
                    code_start = value / 4;
                    std::cout << j << " " << name << " " << value << std::endl;
                }
            }
        }
    }
    if (code) {
        std::cout << "[CODE] SIZE:" << code_size << "(x4) START:" << code_start << std::endl;
        for (int i = 0; i < code_size; ++i) {
            printf("%04x: %08x%s\n", i, code[i], i == code_start ? "<=" : "");
        }
        const int REG_FILE_SIZE = 16;
        uint32_t REG_FILE[REG_FILE_SIZE] = {};
        REG_FILE[0] = code_size + 1; // RA for exit
        uint32_t PC = code_start;
        uint32_t NEXT_PC = PC + 1;
        uint32_t RUN = 1;

        simInit();

        while (RUN) {
            uint16_t r3_imm = code[PC] & 0xFFFF;
            uint8_t r2 = (code[PC] >> 16) & 0xF;
            uint8_t r1 = (code[PC] >> 20) & 0xF;
            uint32_t op = code[PC] >> 24;
            printf("[%04x] ", PC);
            switch (op) {
                default:
                    printf("[ERROR] PC %04x: Incorect opcode %02x\n", PC, op);
                    RUN = 0;
                    break;
                case 0xAA:
                // 0xAA MOVli r2 imm
                    printf("MOVli r%d %x\n", r1, r3_imm);
                    REG_FILE[r1] = r3_imm;
                    break;
                case 0xAF:
                // 0xAF MOVhi r15 65280
                    printf("MOVhi r%d %x\n", r1, r3_imm << 16);
                    REG_FILE[r1] = r3_imm << 16;
                    break;
                case 0xBB:
                // 0xBB BR r0
                    printf("BR r%d\n", r1);
                    NEXT_PC = REG_FILE[r1];
                    break;
                case 0x71:
                // 0x71 B.NE r14 r9 .LBB0_3
                    printf("B.NE r%d r%d %x\n", r1, r2, PC + (int16_t)r3_imm);
                    if (REG_FILE[r1] != REG_FILE[r2]) {
                        NEXT_PC = PC + (int16_t)r3_imm;
                    }
                    break;
                case 0x30:
                // 0x30 ADD r15 r15 r12
                    printf("ADD r%d r%d r%d\n", r1, r2, r3_imm);
                    REG_FILE[r1] = REG_FILE[r2] + REG_FILE[r3_imm];
                    break;
                case 0x40:
                // 0x40 ADDi r14 r14 1
                    printf("ADDi r%d r%d %x\n", r1, r2, r3_imm);
                    REG_FILE[r1] = REG_FILE[r2] + (int16_t)r3_imm;
                    break;
                case 0x44:
                // 0x44 ORi r2 r2 6553
                    printf("ORi r%d r%d %x\n", r1, r2, r3_imm);
                    REG_FILE[r1] = REG_FILE[r2] | r3_imm;
                    break;
                case 0xEE:
                // 0xEE PUTPIXEL r14 r13 r15
                    printf("PUTPIXEL (%d, %d): %x\n", REG_FILE[r1], REG_FILE[r2], REG_FILE[r3_imm]);
                    simPutPixel(REG_FILE[r1], REG_FILE[r2], REG_FILE[r3_imm]);
                    break;
                case 0xFF:
                // 0xFF FLUSH
                    printf("FLUSH\n");
                    simFlush();
                    break;
            }
            PC = NEXT_PC;
            NEXT_PC = PC + 1;
            if (0 > PC || PC > code_size) {
                RUN = 0;
            }
        }

        simExit();
        // return value in r9 register
        return REG_FILE[9];
    }

    return 0;
}
