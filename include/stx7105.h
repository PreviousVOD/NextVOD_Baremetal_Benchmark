#ifndef STX7105_H
#define STX7105_H

#include <stdint.h>

#define __PACKED __attribute__((packed, aligned(1)))
#define __IO     volatile

typedef struct {
    __IO uint8_t POUT;        /* Offset: 0x00, GPIO pin output register */
    uint8_t      UNUSED0[3];  /* Offset: 0x01 */
    __IO uint8_t SET_POUT;    /* Offset: 0x04, GPIO pin output set register */
    uint8_t      UNUSED1[3];  /* Offset: 0x05 */
    __IO uint8_t CLR_POUT;    /* Offset: 0x08, GPIO pin output clear register */
    uint8_t      UNUSED2[7];  /* Offset: 0x09 */
    __IO uint8_t PIN;         /* Offset: 0x10, GPIO pin input register */
    uint8_t      UNUSED3[15]; /* Offset: 0x11 */
    __IO uint8_t PC0;         /* Offset: 0x20, GPIO pin config register 0 */
    uint8_t      UNUSED4[3];  /* Offset: 0x21 */
    __IO uint8_t SET_PC0;     /* Offset: 0x24, GPIO pin config set register 0 */
    uint8_t      UNUSED5[3];  /* Offset: 0x25 */
    __IO uint8_t CLR_PC0;     /* Offset: 0x28, GPIO pin config clear register 0 */
    uint8_t      UNUSED6[7];  /* Offset: 0x29 */
    __IO uint8_t PC1;         /* Offset: 0x30, GPIO pin config register 1 */
    uint8_t      UNUSED7[3];  /* Offset: 0x31 */
    __IO uint8_t SET_PC1;     /* Offset: 0x34, GPIO pin config set register 1 */
    uint8_t      UNUSED8[3];  /* Offset: 0x35 */
    __IO uint8_t CLR_PC1;     /* Offset: 0x38, GPIO pin config clear register 1 */
    uint8_t      UNUSED9[7];  /* Offset: 0x39 */
    __IO uint8_t PC2;         /* Offset: 0x40, GPIO pin config register 2 */
    uint8_t      UNUSED10[3]; /* Offset: 0x41 */
    __IO uint8_t SET_PC2;     /* Offset: 0x44, GPIO pin config set register 2 */
    uint8_t      UNUSED11[3]; /* Offset: 0x45 */
    __IO uint8_t CLR_PC2;     /* Offset: 0x48, GPIO pin config clear register 2 */
    uint8_t      UNUSED12[7]; /* Offset: 0x49 */
    __IO uint8_t PCOMP;       /* Offset: 0x50, GPIO pin input comparison register */
    uint8_t      UNUSED13[3]; /* Offset: 0x51 */
    __IO uint8_t SET_PCOMP;   /* Offset: 0x54, GPIO pin input comparison set regiser */
    uint8_t      UNUSED14[3]; /* Offset: 0x55 */
    __IO uint8_t CLR_PCOMP;   /* Offset: 0x58, GPIO pin input comparison clear regiser */
    uint8_t      UNUSED15[7]; /* Offset: 0x59 */
    __IO uint8_t PMASK;       /* Offset: 0x60, GPIO pin input comparison mask register */
    uint8_t      UNUSED16[3]; /* Offset: 0x61 */
    __IO uint8_t SET_PMASK;   /* Offset: 0x64, GPIO pin input comparison mask set regiser */
    uint8_t      UNUSED17[3]; /* Offset: 0x65 */
    __IO uint8_t CLR_PMASK;   /* Offset: 0x68, GPIO pin input comparison mask clear regiser */
} PIO_TypeDef;

typedef struct {
    __IO uint32_t BAUDRATE;  /* Offset: 0x00, ASCn baud rate generator register */
    __IO uint32_t TX_BUF;    /* Offset: 0x04, ASCn transmit buffer register */
    __IO uint32_t RX_BUF;    /* Offset: 0x08, ASCn receive buffer register */
    __IO uint32_t CTRL;      /* Offset: 0x0C, ASCn control register */
    __IO uint32_t INT_EN;    /* Offset: 0x10, ASCn interrupt enable register */
    __IO uint32_t STA;       /* Offset: 0x14, ASCn interrupt status register */
    __IO uint32_t GUARDTIME; /* Offset: 0x18, ASCn guard time register */
    __IO uint32_t TIMEOUT;   /* Offset: 0x1C, ASCn time out register */
    __IO uint32_t TX_RST;    /* Offset: 0x20, ASCn transmit FIFO reset register */
    __IO uint32_t RX_RST;    /* Offset: 0x24, ASCn receive FIFO reset register */
    __IO uint32_t RETRIES;   /* Offset: 0x28, ASCn number of retries on transmission register */
} ASC_TypeDef;

typedef struct {
    __IO uint16_t ICR;        /* Offset: 0x00, Interrupt control register */
    uint8_t       UNUSED0[2]; /* Offset: 0x02 */
    __IO uint16_t IPRA;       /* Offset: 0x04, Interrupt priority level A register */
    uint8_t       UNUSED1[2]; /* Offset: 0x06 */
    __IO uint16_t IPRB;       /* Offset: 0x08, Interrupt priority level B register */
    uint8_t       UNUSED2[2]; /* Offset: 0x0A */
    __IO uint16_t IPRC;       /* Offset: 0x0C, Interrupt priority level C register */
    uint8_t       UNUSED3[2]; /* Offset: 0x0E */
    __IO uint16_t IPRD;       /* Offset: 0x10, Interrupt priority level D register */
    uint8_t       UNUSED4[2]; /* Offset: 0x12 */
} INTC_TypeDef;

typedef struct {
    __IO uint8_t  TOCR;       /* Offset: 0x00, Timer output control register */
    uint8_t       UNUSED0[3]; /* Offset: 0x01 */
    __IO uint8_t  TSTR;       /* Offset: 0x04, Timer start register */
    uint8_t       UNUSED1[3]; /* Offset: 0x05 */
    __IO uint32_t TCOR0;      /* Offset: 0x08, Timer constant register 0 */
    __IO uint32_t TCNT0;      /* Offset: 0x0C, Timer counter 0 */
    __IO uint16_t TCR0;       /* Offset: 0x10, Timer control register 0 */
    uint8_t       UNUSED2[2]; /* Offset: 0x11 */
    __IO uint32_t TCOR1;      /* Offset: 0x14, Timer constant register 1 */
    __IO uint32_t TCNT1;      /* Offset: 0x18, Timer counter 1 */
    __IO uint16_t TCR1;       /* Offset: 0x1C, Timer control register 1 */
    uint8_t       UNUSED3[2]; /* Offset: 0x1E */
    __IO uint32_t TCOR2;      /* Offset: 0x20, Timer constant register 2 */
    __IO uint32_t TCNT2;      /* Offset: 0x24, Timer counter 2 */
    __IO uint16_t TCR2;       /* Offset: 0x28, Timer control register 2 */
    __IO uint8_t  UNUSED4[2]; /* Offset: 0x2A */
    uint32_t      TCPR2;      /* Offset: 0x2C */
} TMU_TypeDef;

typedef struct {
    __IO uint32_t PTEH;             /* Offset: 0x00000, Page table entry high register */
    __IO uint32_t PTEL;             /* Offset: 0x00004, Page table entry low register */
    __IO uint32_t TTB;              /* Offset: 0x00008, Translation table base register */
    __IO uint32_t TEA;              /* Offset: 0x0000C, TLB exception address register */
    __IO uint32_t MMUCR;            /* Offset: 0x00010, MMU control register */
    __IO uint8_t  BASRA;            /* Offset: 0x00014, Break ASID register A*/
    uint8_t       UNUSED0[3];       /* Offset: 0x00015 */
    __IO uint8_t  BASRB;            /* Offset: 0x00018, Break ASID register B*/
    uint8_t       UNUSED1[3];       /* Offset: 0x00019 */
    __IO uint32_t CCR;              /* Offset: 0x0001C, Cache control register */
    __IO uint32_t TRA;              /* Offset: 0x00020, TRAPA exception register */
    __IO uint32_t EXPEVT;           /* Offset: 0x00024, Exception event register */
    __IO uint32_t INTEVT;           /* Offset: 0x00028, Interrupt event register */
    uint32_t      UNUSED2[3];       /* Offset: 0x0002C */
    __IO uint32_t QACR0;            /* Offset: 0x00038, Queue address control register 0 */
    __IO uint32_t QACR1;            /* Offset: 0x0003C, Queue address control register 1 */
    uint32_t      UNUSED3[12];      /* Offset: 0x00040 */
    __IO uint32_t PASCR;            /* Offset: 0x00070, Physical address space control register */
    __IO uint32_t RAMCR;            /* Offset: 0x00074, On-chip memory control register */
    __IO uint32_t IRMCR;            /* Offset: 0x00078, Instruction refetch inhibit control register */
    uint32_t      UNUSED4[2097028]; /* Offset: 0x0007C, Am I serious? */
    __IO uint32_t BARA;             /* Offset: 0x20000, Break address register A */
    __IO uint8_t  BAMRA;            /* Offset: 0x20004, Break address mask register A */
    uint8_t       UNUSED5[3];       /* Offset: 0x20005 */
    __IO uint16_t BBRA;             /* Offset: 0x20008, Break bus cycle register A */
    uint8_t       UNUSED6[2];       /* Offset: 0x2000A */
    __IO uint32_t BARB;             /* Offset: 0x2000B, Break address register B */
    __IO uint8_t  BAMRB;            /* Offset: 0x20010, Break address mask register B */
    uint8_t       UNUSED7[3];       /* Offset: 0x20011 */
    __IO uint16_t BBRB;             /* Offset: 0x20014, Break bus cycle register B */
    uint8_t       UNUSED8[2];       /* Offset: 0x20016 */
    __IO uint32_t BDRB;             /* Offset: 0x20018, Break data register B */
    __IO uint32_t BDMRB;            /* Offset: 0x2001C, Break data mask register B */
    __IO uint16_t BRCR;             /* Offset: 0x20020, Break control register */
    uint8_t       UNUSED9[2];       /* Offset: 0x20022 */
} CSR_TypeDef;

#define PIO0_BASE (0xFD020000U)
#define PIO1_BASE (0xFD021000U)
#define PIO2_BASE (0xFD022000U)
#define PIO3_BASE (0xFD023000U)
#define PIO4_BASE (0xFD024000U)
#define PIO5_BASE (0xFD025000U)
#define PIO6_BASE (0xFD026000U)
#define ASC0_BASE (0xFD030000U)
#define ASC1_BASE (0xFD031000U)
#define ASC2_BASE (0xFD032000U)
#define ASC3_BASE (0xFD033000U)
#define CSR_BASE  (0xFF000000U)
#define INTC_BASE (0xFFD00000U)
#define TMU_BASE  (0xFFD80000U)

#define PIO0 ((PIO_TypeDef *)PIO0_BASE)
#define PIO1 ((PIO_TypeDef *)PIO1_BASE)
#define PIO2 ((PIO_TypeDef *)PIO2_BASE)
#define PIO3 ((PIO_TypeDef *)PIO3_BASE)
#define PIO4 ((PIO_TypeDef *)PIO4_BASE)
#define PIO5 ((PIO_TypeDef *)PIO5_BASE)
#define PIO6 ((PIO_TypeDef *)PIO6_BASE)
#define ASC0 ((ASC_TypeDef *)ASC0_BASE)
#define ASC1 ((ASC_TypeDef *)ASC1_BASE)
#define ASC2 ((ASC_TypeDef *)ASC2_BASE)
#define ASC3 ((ASC_TypeDef *)ASC3_BASE)
#define CSR  ((CSR_TypeDef *)CSR_BASE)
#define INTC ((INTC_TypeDef *)INTC_BASE)
#define TMU  ((TMU_TypeDef *)TMU_BASE)

#define TMU_TSTR_STR0_Pos 0
#define TMU_TSTR_STR0_Msk (1U << TMU_TSTR_STR0_Pos)

#define TMU_TSTR_STR1_Pos 1
#define TMU_TSTR_STR1_Msk (1U << TMU_TSTR_STR1_Pos)

#define TMU_TSTR_STR2_Pos 2
#define TMU_TSTR_STR3_Msk (1U << TMU_TSTR_STR2_Pos)

#define TMU_TCR_UNIE_Pos 5
#define TMU_TCR_UNIE_Msk (1U << TMU_TCR_UNIE_Pos)

#define TMU_TCR_UNF_Pos 8
#define TMU_TCR_UNF_Msk (1U << TMU_TCR_UNF_Pos)

#define INTC_IPRA_IPR_TMU0_Pos 12
#define INTC_IPRA_IPR_TMU0_Msk (0x0FU << INTC_IPRA_IPR_TMU0_Pos)

#endif