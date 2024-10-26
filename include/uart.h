#pragma once

#include "common.h"

#define UART0               (0x201000U)
#define UART2               (0x201400U)
#define UART3               (0x201600U)
#define UART4               (0x201800U)
#define UART5               (0x201A00U)

#define UART_DR_OFF         (0x0U)
#define UART_FR_OFF         (0x18U)
#define UART_IBRD_OFF       (0x24U)
#define UART_FBRD_OFF       (0x28U)
#define UART_LCRH_OFF       (0x2CU)
#define UART_CR_OFF         (0x30U)

#define REG_UART_DR(IDX)    ( (volatile u32 *) (PBASE + IDX + UART_DR_OFF) )
#define REG_UART_FR(IDX)    ( (volatile u32 *) (PBASE + IDX + UART_FR_OFF) )
#define REG_UART_IBRD(IDX)  ( (volatile u32 *) (PBASE + IDX + UART_IBRD_OFF) )
#define REG_UART_FBRD(IDX)  ( (volatile u32 *) (PBASE + IDX + UART_FBRD_OFF) )
#define REG_UART_LCRH(IDX)  ( (volatile u32 *) (PBASE + IDX + UART_LCRH_OFF) )
#define REG_UART_CR(IDX)    ( (volatile u32 *) (PBASE + IDX + UART_CR_OFF) )

#define UART_LCRH_MASK      (0xFFFFFF00U)
#define UART_CR_MASK        (0xFFFF0078U)
#define UART_DR_TX_MASK     (0xFFU)

#define UART_CR_TXFF_BIT    (0x20U)

void test_uart();
