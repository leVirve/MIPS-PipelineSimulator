/*
 * Define the enviromental parameters
 *
 * iimage.bin : LE (little endian) encoded.
 *				First 4 bytes for initial PC : the starting address to load the instruction image,
 *				Next 4 bytes specifies the number of words to be loaded into instruction memory (I Memory)
 * dimage.bin : LE (little endian) encoded.
 *				First 4 bytes for initial $sp,
 *				Next 4 bytes indicate the number of words to be loaded into data memory (D Memory)
 */

#include <cstdio>
#include <cstring>

#ifndef __ENV_H__
#define __ENV_H__

#define UINT32 unsigned int
#define ITER unsigned int
#define INT32 int
#define BYTE unsigned char
#define MEMORY_SIZE 1024
#define STAGES 5

#define ERR_WRITE_REG_ZERO 0x1
#define ERR_D_MEM_ADDRESS_OVERFLOW 0x2
#define ERR_D_MEM_MISALIGN 0x3
#define ERR_NUMBER_OVERFLOW 0x4
#define ERR_I_MEM_ADDRESS_OVERFLOW 0x5
#define ERR_I_MEM_MISALIGN 0x6

#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

/* Input File */
#ifndef _DEBUG
# define INSTRUCTION_BIN "iimage.bin"
# define DATA_BIN "dimage.bin"
#else
//# define INSTRUCTION_BIN "../../open_testcase/pipeline1/iimage.bin"
# define INSTRUCTION_BIN "../iimage.bin"
# define DATA_BIN "../dimage.bin"
#endif

/* Output File */

#define SNAPSHOT "snapshot.rpt"
#define ERR_DUMP "error_dump.rpt"

/* Debug print */
#ifdef _DEBUG
# define DEBUG_PRINT(...) fprintf( stderr, __VA_ARGS__ );
#else
# define DEBUG_PRINT(x) do {} while (0);
#endif

#endif
