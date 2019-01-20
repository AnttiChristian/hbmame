// license:BSD-3-Clause
// copyright-holders:Ryan Holtz
#ifndef MAME_BUS_VSMILE_VSMILE_CTRL_H
#define MAME_BUS_VSMILE_VSMILE_CTRL_H

#pragma once


/***************************************************************************
 FORWARD DECLARATIONS
 ***************************************************************************/

class vsmile_ctrl_port_device;


/***************************************************************************
 TYPE DEFINITIONS
 ***************************************************************************/

// ======================> device_vsmile_ctrl_interface

class device_vsmile_ctrl_interface : public device_slot_card_interface
{
public:
	virtual ~device_vsmile_ctrl_interface();

protected:
	device_vsmile_ctrl_interface(machine_config const &mconfig, device_t &device);

	// device_interface implementation
	virtual void interface_validity_check(validity_checker &valid) const override ATTR_COLD;
	virtual void interface_pre_start() override;

	// otuput signals
	void rts_out(int state);
	void data_out(uint8_t data);

private:
	// input signal handlers for implementataions to override
	virtual void cts_w(int state) = 0;
	virtual void data_w(uint8_t data) = 0;

	vsmile_ctrl_port_device *const m_port;

	friend class vsmile_ctrl_port_device;
};


// ======================> vsmile_ctrl_port_device

class vsmile_ctrl_port_device : public device_t, public device_slot_interface
{
public:
	// configuration
	auto rts_cb() { return m_rts_cb.bind(); }
	auto data_cb() { return m_data_cb.bind(); }

	// construction/destruction
	template <typename T>
	vsmile_ctrl_port_device(machine_config const &mconfig, char const *tag, device_t *owner, T &&opts, char const *dflt)
		: vsmile_ctrl_port_device(mconfig, tag, owner, 0U)
	{
		option_reset();
		opts(*this);
		set_default_option(dflt);
		set_fixed(false);
	}
	vsmile_ctrl_port_device(machine_config const &mconfig, char const *tag, device_t *owner, uint32_t clock = 0U);
	virtual ~vsmile_ctrl_port_device();

	// input signals
	void cts_w(int state) { if (m_device) m_device->cts_w(state); }
	void data_w(uint8_t data) { if (m_device) m_device->data_w(data); }

protected:
	// device_t implementation
	virtual void device_validity_check(validity_checker &valid) const override ATTR_COLD;
	virtual void device_resolve_objects() override;
	virtual void device_start() override;

private:
	device_vsmile_ctrl_interface *m_device;
	devcb_write_line m_rts_cb;
	devcb_write8 m_data_cb;

	friend class device_vsmile_ctrl_interface;
};


/***************************************************************************
 INLINE FUNCTIONS
 ***************************************************************************/

inline void device_vsmile_ctrl_interface::rts_out(int state) { m_port->m_rts_cb(state); }
inline void device_vsmile_ctrl_interface::data_out(uint8_t data) { m_port->m_data_cb(data); }


/***************************************************************************
 FUNCTIONS
 ***************************************************************************/

void vsmile_controllers(device_slot_interface &device);


/***************************************************************************
 DEVICE TYPES
 ***************************************************************************/

DECLARE_DEVICE_TYPE(VSMILE_CTRL_PORT, vsmile_ctrl_port_device)

#endif // MAME_BUS_VSMILE_VSMILE_CTRL_H
