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
  size_type read_size = 0;
  size_type channel_buf_index = channel_id_to_buf_index(a_channel_ident);
  channel_t& channel_cur = m_channel_list.channel[channel_buf_index];

  if (channel_cur.packet.empty()) {
    packet_t packet;
    uint8_t *a_packet_raw = reinterpret_cast<uint8_t*>(&packet) + 1;
    int res = hid_read(m_device_handle, a_packet_raw, m_report_size);
    if (res > 0) {
      const size_type packet_buf_index = packet_channel_id_to_buf_index(packet.channel_id);
      if (packet_buf_index == channel_buf_index) {
        size_type packet_size = packet.data_size;

//        irs::mlog() << "packet.channel_id = " << (int)packet.channel_id << endl;
//        irs::mlog() << "packet.data_size = " << packet_size << endl;

        read_size = min(a_size, packet_size);
        memcpy(ap_buf, packet.data, read_size);

        if (packet_size > a_size) {
          channel_cur.packet_add(packet);
          channel_cur.packet_read_pos = read_size;
        }
      } else {
        channel_t& channel_in_recived_packet = m_channel_list.channel[packet_buf_index];
        channel_in_recived_packet.packet_add(packet);
        channel_in_recived_packet.packet_read_pos = 0;
      }
    }
  } else {
    size_type data_size = channel_cur.packet.front().data_size;
    read_size = min(a_size, data_size - channel_cur.packet_read_pos);
    memcpy(ap_buf, channel_cur.packet.front().data + channel_cur.packet_read_pos, read_size);
    channel_cur.packet_read_pos += read_size;
    if (channel_cur.packet_read_pos >= data_size) {
      channel_cur.packet.pop_front();
      channel_cur.packet_read_pos = 0;
    }
  }

  return read_size;
}

hidapi_hardflow_t::size_type hidapi_hardflow_t::write(size_type a_channel_ident,
  const irs_u8 *ap_buf, size_type a_size)
{
  size_type buf_index = channel_id_to_buf_index(a_channel_ident);
  channel_field_type packet_channel_id = buf_index_to_packet_channel_id(buf_index);
  packet_t packet(0x00, packet_channel_id, static_cast<uint16_t>(a_size), ap_buf);
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

