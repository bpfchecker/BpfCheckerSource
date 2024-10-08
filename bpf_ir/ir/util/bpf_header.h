#ifndef BPF_IR_BPF_HEADER_H
#define BPF_IR_BPF_HEADER_H

#include <cstdint>

typedef uint8_t __u8;
typedef uint16_t __u16;
typedef uint32_t __u32;
typedef uint64_t __u64;
typedef int8_t __s8;
typedef int16_t __s16;
typedef int32_t __s32;
typedef int64_t __s64;

#define BPF_ANY 0
#define BPF_MAP_TYPE_ARRAY 2
#define BPF_FUNC_map_lookup_elem 1
#define BPF_FUNC_map_update_elem 2

// From uapi/linux/bpf_common.h

/* Extended instruction set based on top of classic BPF */

/* instruction classes */
#define BPF_JMP32    0x06    /* jmp mode in word width */
#define BPF_ALU64    0x07    /* alu mode in double word width */

/* ld/ldx fields */
#define BPF_DW        0x18    /* double word (64-bit) */
#define BPF_ATOMIC    0xc0    /* atomic memory ops - op type in immediate */
#define BPF_XADD    0xc0    /* exclusive add - legacy name */

/* alu/jmp fields */
#define BPF_MOV        0xb0    /* mov reg to reg */
#define BPF_ARSH    0xc0    /* sign extending arithmetic shift right */

/* change endianness of a register */
#define BPF_END        0xd0    /* flags for endianness conversion: */
#define BPF_TO_LE    0x00    /* convert to little-endian */
#define BPF_TO_BE    0x08    /* convert to big-endian */
#define BPF_FROM_LE    BPF_TO_LE
#define BPF_FROM_BE    BPF_TO_BE

/* jmp encodings */
#define BPF_JNE        0x50    /* jump != */
#define BPF_JLT        0xa0    /* LT is unsigned, '<' */
#define BPF_JLE        0xb0    /* LE is unsigned, '<=' */
#define BPF_JSGT    0x60    /* SGT is signed '>', GT in x86 */
#define BPF_JSGE    0x70    /* SGE is signed '>=', GE in x86 */
#define BPF_JSLT    0xc0    /* SLT is signed, '<' */
#define BPF_JSLE    0xd0    /* SLE is signed, '<=' */
#define BPF_CALL    0x80    /* function call */
#define BPF_EXIT    0x90    /* function return */

/* atomic op type fields (stored in immediate) */
#define BPF_FETCH    0x01    /* not an opcode on its own, used to build others */
#define BPF_XCHG    (0xe0 | BPF_FETCH)    /* atomic exchange */
#define BPF_CMPXCHG    (0xf0 | BPF_FETCH)    /* atomic compare-and-write */

/* Register numbers */
enum {
    BPF_REG_0 = 0,
    BPF_REG_1,
    BPF_REG_2,
    BPF_REG_3,
    BPF_REG_4,
    BPF_REG_5,
    BPF_REG_6,
    BPF_REG_7,
    BPF_REG_8,
    BPF_REG_9,
    BPF_REG_10,
    __MAX_BPF_REG,
};

/* BPF has 10 general purpose 64-bit registers and stack frame. */
#define MAX_BPF_REG    __MAX_BPF_REG
#endif //BPF_IR_BPF_HEADER_H

struct bpf_insn {
    __u8 code;        /* opcode */
    __u8 dst_reg: 4;    /* dest register */
    __u8 src_reg: 4;    /* source register */
    __s16 off;        /* signed offset */
    __s32 imm;        /* signed immediate constant */
};

// From bpf_common.h
/* Instruction classes */
#define BPF_CLASS(code) ((code) & 0x07)
#define        BPF_LD        0x00
#define        BPF_LDX        0x01
#define        BPF_ST        0x02
#define        BPF_STX        0x03
#define        BPF_ALU        0x04
#define        BPF_JMP        0x05
#define        BPF_RET        0x06
#define        BPF_MISC        0x07

/* ld/ldx fields */
#define BPF_SIZE(code)  ((code) & 0x18)
#define        BPF_W        0x00 /* 32-bit */
#define        BPF_H        0x08 /* 16-bit */
#define        BPF_B        0x10 /*  8-bit */
/* eBPF		BPF_DW		0x18    64-bit */
#define BPF_MODE(code)  ((code) & 0xe0)
#define        BPF_IMM        0x00
#define        BPF_ABS        0x20
#define        BPF_IND        0x40
#define        BPF_MEM        0x60
#define        BPF_LEN        0x80
#define        BPF_MSH        0xa0

/* alu/jmp fields */
#define BPF_OP(code)    ((code) & 0xf0)
#define        BPF_ADD        0x00
#define        BPF_SUB        0x10
#define        BPF_MUL        0x20
#define        BPF_DIV        0x30
#define        BPF_OR        0x40
#define        BPF_AND        0x50
#define        BPF_LSH        0x60
#define        BPF_RSH        0x70
#define        BPF_NEG        0x80
#define        BPF_MOD        0x90
#define        BPF_XOR        0xa0

// WARNING BEGINNING: SDIV is the operator of rbpf only
#define BPF_SDIV 0xe0
// WARNING END.

#define        BPF_JA        0x00
#define        BPF_JEQ        0x10
#define        BPF_JGT        0x20
#define        BPF_JGE        0x30
#define        BPF_JSET        0x40
#define BPF_SRC(code)   ((code) & 0x08)
#define        BPF_K        0x00
#define        BPF_X        0x08

#ifndef BPF_MAXINSNS
#define BPF_MAXINSNS 4096
#endif

// From uapi/linux/filter.h
/* ret - BPF_K and BPF_X also apply */
#define BPF_RVAL(code)  ((code) & 0x18)
#define         BPF_A           0x10

/* misc */
#define BPF_MISCOP(code) ((code) & 0xf8)
#define         BPF_TAX         0x00
#define         BPF_TXA         0x80
