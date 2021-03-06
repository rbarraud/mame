// license:BSD-3-Clause
// copyright-holders:R. Belmont
/******************************************************************************
*
*   MIPS DECstation I/O Gate Array emulation
*
*
*/

#ifndef MAME_MACHINE_DECIOGA_H
#define MAME_MACHINE_DECIOGA_H

#pragma once

#include "emu.h"

class dec_ioga_device : public device_t
{
public:
    dec_ioga_device(const machine_config &mconfig, const char *tag, device_t *owner)
    	: dec_ioga_device(mconfig, tag, owner, (uint32_t)0)
    {
	}

    dec_ioga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void map(address_map &map);

protected:
    virtual void device_start() override;
    virtual void device_reset() override;

	DECLARE_READ32_MEMBER(csr_r);
	DECLARE_WRITE32_MEMBER(csr_w);

private:
	uint32_t m_csr;
};

DECLARE_DEVICE_TYPE(DECSTATION_IOGA, dec_ioga_device)

#endif // MAME_MACHINE_DECIOGA_H