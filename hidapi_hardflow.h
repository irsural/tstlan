#ifndef LIBUSB_HID_T_H
#define LIBUSB_HID_T_H

#include <hardflowg.h>
#include <cassert>
#include "hidapi.h"

class hidapi_hardflow_t: public irs::hardflow_t
{
public:
  typedef irs::hardflow_t::size_type size_type;
  typedef irs::hardflow_t::string_type string_type;

  hidapi_hardflow_t(uint16_t a_pid, uint16_t a_vid,
    size_type a_channel_start_index = invalid_channel + 1, size_type a_channel_count = 1);
  virtual ~hidapi_hardflow_t();
  virtual string_type param(const string_type &a_name);
  virtual void set_param(const string_type &a_name, const string_type &a_value);
  virtual size_type read(size_type a_channel_ident, irs_u8 *ap_buf, size_type a_size);
  virtual size_type write(size_type a_channel_ident, const irs_u8 *ap_buf, size_type a_size);
  virtual size_type channel_next();
  virtual bool is_channel_exists(size_type a_channel_ident);
  virtual void tick();

private:
  enum { hid_interface_class = 0x03 };

  typedef irs_u8 channel_field_type;

  #pragma pack(push, 1)
  struct packet_t
  {
    uint8_t report_id;
    uint8_t channel_id;
    uint16_t data_size;
    uint8_t data[61];
    packet_t(uint8_t a_report_id = 0, uint8_t a_channel_id = 0, uint16_t a_data_size = 0,
      const uint8_t *a_src_data = NULL
    ):
      report_id(a_report_id),
      channel_id(a_channel_id),
      data_size(a_data_size)
    {
      memset(data, 0, sizeof(data));
      if (a_src_data) {
        memcpy(data, a_src_data, a_data_size);
      }
    }
  };
  #pragma pack(pop)

  size_type m_channel;
  const size_type m_channel_start_index;
  const size_type m_channel_end_index;
  const size_type m_channel_count;

  hid_device *m_device_handle;
  const size_t m_report_size;
  std::vector<uint8_t> m_read_over_bytes;

  inline size_type channel_id_to_buf_index(size_type a_channel_id)
  {
    return a_channel_id - 1;
  }
  inline size_type buf_index_to_channel_id(size_type a_buf_index)
  {
    return a_buf_index + 1;
  }
  inline size_type packet_channel_id_to_buf_index(
    channel_field_type a_channel_id)
  {
    return a_channel_id - (m_channel_start_index - 1);
  }
  inline channel_field_type buf_index_to_packet_channel_id(
    size_type a_buf_index)
  {
    return static_cast<channel_field_type>(
      a_buf_index + (m_channel_start_index - 1));
  }
};

#endif // LIBUSB_HID_T_H

