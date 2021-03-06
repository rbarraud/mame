// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/*****************************************************************************
 *
 * includes/radio86.h
 *
 ****************************************************************************/

#ifndef MAME_INCLUDES_RADIO86_H
#define MAME_INCLUDES_RADIO86_H

#include "machine/i8255.h"
#include "machine/i8257.h"
#include "video/i8275.h"
#include "imagedev/cassette.h"
#include "bus/generic/slot.h"
#include "bus/generic/carts.h"
#include "emupal.h"


class radio86_state : public driver_device
{
public:
	enum
	{
		TIMER_RESET
	};

	radio86_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_cassette(*this, "cassette"),
		m_cart(*this, "cartslot"),
		m_dma8257(*this, "dma8257"),
		m_ppi8255_1(*this, "ppi8255_1"),
		m_ppi8255_2(*this, "ppi8255_2"),
		m_region_maincpu(*this, "maincpu"),
		m_bank1(*this, "bank1"),
		m_io_line(*this, "LINE%u", 0),
		m_io_cline(*this, "CLINE%u", 0),
		m_palette(*this, "palette") { }

	virtual void video_start() override;

	uint8_t m_tape_value;
	uint8_t m_mikrosha_font_page;
	int m_keyboard_mask;
	std::unique_ptr<uint8_t[]> m_radio_ram_disk;
	uint8_t m_romdisk_lsb;
	uint8_t m_romdisk_msb;
	uint8_t m_disk_sel;
	const uint8_t *m_charmap;
	DECLARE_READ8_MEMBER(radio_cpu_state_r);
	DECLARE_READ8_MEMBER(radio_io_r);
	DECLARE_WRITE8_MEMBER(radio_io_w);
	DECLARE_WRITE8_MEMBER(radio86_pagesel);
	void init_radioram();
	void init_radio86();
	DECLARE_MACHINE_RESET(radio86);
	DECLARE_PALETTE_INIT(radio86);
	DECLARE_READ8_MEMBER(radio86_8255_portb_r2);
	DECLARE_READ8_MEMBER(radio86_8255_portc_r2);
	DECLARE_WRITE8_MEMBER(radio86_8255_porta_w2);
	DECLARE_WRITE8_MEMBER(radio86_8255_portc_w2);
	DECLARE_READ8_MEMBER(rk7007_8255_portc_r);
	DECLARE_READ8_MEMBER(kr03_8255_portb_r2);
	DECLARE_WRITE_LINE_MEMBER(hrq_w);
	DECLARE_READ8_MEMBER(radio86rom_romdisk_porta_r);
	DECLARE_READ8_MEMBER(radio86ram_romdisk_porta_r);
	DECLARE_WRITE8_MEMBER(radio86_romdisk_portb_w);
	DECLARE_WRITE8_MEMBER(radio86_romdisk_portc_w);
	DECLARE_WRITE8_MEMBER(mikrosha_8255_font_page_w);
	DECLARE_READ8_MEMBER(memory_read_byte);
	DECLARE_WRITE8_MEMBER(memory_write_byte);
	I8275_DRAW_CHARACTER_MEMBER(display_pixels);
	required_device<cpu_device> m_maincpu;

	void impuls03(machine_config &config);
	void mikron2(machine_config &config);
	void rk7007(machine_config &config);
	void rk700716(machine_config &config);
	void radiorom(machine_config &config);
	void radio86(machine_config &config);
	void radio16(machine_config &config);
	void radioram(machine_config &config);
	void kr03(machine_config &config);
	void impuls03_mem(address_map &map);
	void mikron2_mem(address_map &map);
	void radio86_16_mem(address_map &map);
	void radio86_io(address_map &map);
	void radio86_mem(address_map &map);
	void radio86ram_mem(address_map &map);
	void radio86rom_mem(address_map &map);
	void rk7007_io(address_map &map);
protected:
	required_device<cassette_image_device> m_cassette;
	optional_device<generic_slot_device> m_cart;    // for ROMDisk - only Radio86K & Orion?
	optional_device<i8257_device> m_dma8257;
	required_device<i8255_device> m_ppi8255_1;
	optional_device<i8255_device> m_ppi8255_2;
	required_memory_region m_region_maincpu;
	required_memory_bank m_bank1;
	required_ioport_array<9> m_io_line;
	optional_ioport_array<8> m_io_cline;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	void radio86_init_keyboard();
public:
	required_device<palette_device> m_palette;
};


/*----------- defined in drivers/radio86.c -----------*/

INPUT_PORTS_EXTERN( radio86 );
INPUT_PORTS_EXTERN( ms7007 );

#endif // MAME_INCLUDES_RADIO86_H
