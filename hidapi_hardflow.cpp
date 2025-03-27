#include "hidapi_hardflow.h"

hidapi_hardflow_t::hidapi_hardflow_t(uint16_t a_pid, uint16_t a_vid,
  size_type a_channel_start_index, size_type a_channel_count
):
  m_channel(invalid_channel + 1),
  m_channel_start_index(a_channel_start_index),
  m_channel_end_index(m_channel_start_index + a_channel_count - 1),
  m_channel_count(a_channel_count),
  m_channel_list(m_channel_count),
  m_device_handle(NULL),
  m_report_size(65),
  m_read_over_bytes()
{
  hid_init();
  m_device_handle = hid_open(a_vid, a_pid, NULL);
  hid_set_nonblocking(m_device_handle, 1);
}

hidapi_hardflow_t::~hidapi_hardflow_t()
{
  hid_close(m_device_handle);
  hid_exit();
}

hidapi_hardflow_t::string_type hidapi_hardflow_t::param(const string_type &a_name)
{
  string_type s;
  return s;
}

void hidapi_hardflow_t::set_param(const string_type &a_name, const string_type &a_value)
{
}


hidapi_hardflow_t::size_type hidapi_hardflow_t::read(size_type a_channel_ident, irs_u8 *ap_buf,
  size_type a_size)
{
  packet_t packet;
  size_type read_size = 0;

  if (m_read_over_bytes.empty()) {
    uint8_t *a_packet_raw = reinterpret_cast<uint8_t*>(&packet) + 1;
    int res = hid_read(m_device_handle, a_packet_raw, m_report_size);
    if (res > 0) {
      size_type packet_size = packet.data_size;

//      irs::mlog() << "packet.channel_id = " << (int)packet.channel_id << endl;
//      irs::mlog() << "packet.data_size = " << packet_size << endl;

      read_size = ((a_size <= packet_size) ? a_size : packet_size);
      memcpy(ap_buf, packet.data, read_size);

      if (packet_size > a_size) {
        size_type oversize = packet_size - read_size;
        m_read_over_bytes.resize(oversize);
        memcpy(&m_read_over_bytes[0], packet.data + read_size, oversize);
      }
    }
  } else {
    read_size = a_size <= m_read_over_bytes.size() ? a_size : m_read_over_bytes.size();
    memcpy(ap_buf, &m_read_over_bytes[0], read_size);
    m_read_over_bytes.erase(m_read_over_bytes.begin(), m_read_over_bytes.begin() + read_size);
  }
  return read_size;
}

hidapi_hardflow_t::size_type hidapi_hardflow_t::write(size_type a_channel_ident,
  const irs_u8 *ap_buf, size_type a_size)
{
  packet_t packet(0x00, 0x00, static_cast<uint16_t>(a_size), ap_buf);
  int res = hid_write(m_device_handle, reinterpret_cast<uint8_t*>(&packet), m_report_size);
  return res > 0 ? res : 0;
}

hidapi_hardflow_t::size_type hidapi_hardflow_t::channel_next()
{
  size_type channel = m_channel;
  m_channel++;
  if (m_channel > m_channel_end_index) {
    m_channel = m_channel_start_index;
  }
  return channel;
}

bool hidapi_hardflow_t::is_channel_exists(size_type a_channel_ident)
{
  if ((a_channel_ident >= m_channel_start_index) &&
    (a_channel_ident <= m_channel_end_index)) {
    return true;
  }
  return false;
}

void hidapi_hardflow_t::tick()
{
}
