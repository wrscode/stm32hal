/*
 *  Created on: Dec 16, 2017
 *  Author:     wrscode
 *  File:       stm32f4xx_uart_int.h
 */

#ifndef STM32F4XX_UXART_INT_H_
#define STM32F4XX_UXART_INT_H_

#include <cstdint>

namespace Stm32f4xx
{
namespace Device
{
namespace Inside
{
namespace Uxart
{
struct sr_t
{
    volatile std::uint32_t pe;
    volatile std::uint32_t fe;
    volatile std::uint32_t nf;
    volatile std::uint32_t ore;
    volatile std::uint32_t idle;
    volatile std::uint32_t rxne;
    volatile std::uint32_t tc;
    volatile std::uint32_t txe;
    volatile std::uint32_t lbd;
    volatile std::uint32_t cts;
    volatile std::uint32_t _resv0[22];
};

struct dr_t
{
    volatile std::uint32_t value[9];
    volatile std::uint32_t _resv0[32 - 9];
};

struct brr_t
{
    volatile std::uint32_t fraction[4];
    volatile std::uint32_t mantissa[12];
    volatile std::uint32_t _resv0[16];
};

struct cr1_t
{
    volatile std::uint32_t sbk;
    volatile std::uint32_t rwu;
    volatile std::uint32_t re;
    volatile std::uint32_t te;
    volatile std::uint32_t idleie;
    volatile std::uint32_t rxneie;
    volatile std::uint32_t tcie;
    volatile std::uint32_t txeie;
    volatile std::uint32_t peie;
    volatile std::uint32_t ps;
    volatile std::uint32_t pce;
    volatile std::uint32_t wake;
    volatile std::uint32_t m;
    volatile std::uint32_t ue;
    volatile std::uint32_t _resv0;
    volatile std::uint32_t over8;
    volatile std::uint32_t _resv1[16];
};

struct cr2_t
{
    volatile std::uint32_t add[4];
    volatile std::uint32_t _resv0;
    volatile std::uint32_t lbdl;
    volatile std::uint32_t lbdie;
    volatile std::uint32_t _resv1;
    volatile std::uint32_t lbcl;
    volatile std::uint32_t cpha;
    volatile std::uint32_t cpol;
    volatile std::uint32_t clken;
    volatile std::uint32_t stop[2];
    volatile std::uint32_t linen;
    volatile std::uint32_t _resv2[17];
};

struct cr3_t
{
    volatile std::uint32_t eie;
    volatile std::uint32_t iren;
    volatile std::uint32_t irlp;
    volatile std::uint32_t hdsel;
    volatile std::uint32_t nack;
    volatile std::uint32_t scen;
    volatile std::uint32_t dmar;
    volatile std::uint32_t dmat;
    volatile std::uint32_t rtse;
    volatile std::uint32_t ctse;
    volatile std::uint32_t ctsie;
    volatile std::uint32_t onebit;
    volatile std::uint32_t _resv0[20];
};

struct gtpr_t
{
    volatile std::uint32_t psc[8];
    volatile std::uint32_t gt[8];
    volatile std::uint32_t _resv0[16];
};

struct BitBand_t
{
    sr_t sr;
    dr_t dr;
    brr_t brr;
    cr1_t cr1;
    cr2_t cr2;
    cr3_t cr3;
    gtpr_t gtpr;
};

std::uint32_t CalcValueOfBRR(const std::size_t Clock, const std::size_t BaudRate, const std::size_t Sampling);

}  // namespace Inside
}  // namespace Uxart
}  // namespace Device
}  // namespace STM32F4XX

#endif /* STM32F4XX_UXART_INT_H_ */
