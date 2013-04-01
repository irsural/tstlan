#include <irspch.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif // __BORLANDC__

#include "trash.h"

#include <irsfinal.h>

#ifdef NOP
class vle_reference
{
private:
  TValueListEditor* mp_value_list_editor;
  int m_position;

  vle_reference();
public:
  vle_reference(TValueListEditor* ap_value_list_editor, int a_position):
    mp_value_list_editor(ap_value_list_editor),
    m_position(a_position)
  {
  }
  operator irs::string_t()
  {
    return mp_value_list_editor->Keys[m_position].c_str();
  }
  void operator=(const irs::string_t& a_value)
  {
    mp_value_list_editor->Keys[m_position] = a_value.c_str();
  }
};
inline bool operator<(vle_reference a_left, vle_reference a_right)
{
  irs::string_t left = a_left;
  irs::string_t right = a_right;
  return left < right;
}
inline bool operator<(vle_reference a_left, const irs::string_t& a_right)
{
  irs::string_t left = a_left;
  irs::string_t right = a_right;
  return left < right;
}
inline bool operator<(const irs::string_t& a_left, vle_reference a_right)
{
  irs::string_t left = a_left;
  irs::string_t right = a_right;
  return left < right;
}
namespace std {
void swap(vle_reference a_left, vle_reference a_right)
{
  irs::string_t left_str = a_left;
  irs::string_t right_str = a_right;
  a_left = right_str;
  a_right = left_str;
}
}

class vle_iterator:
  public iterator<random_access_iterator_tag, irs::string_t,
  ptrdiff_t, irs::string_t, vle_reference>
{
private:
  TValueListEditor* mp_value_list_editor;
  int m_position;

  vle_iterator();
public:
  vle_iterator(TValueListEditor* ap_value_list_editor, int a_position):
    mp_value_list_editor(ap_value_list_editor),
    m_position(a_position)
  {
  }
  reference operator*()
  {
    return reference(mp_value_list_editor, m_position);
  }
  vle_iterator& operator++()
  {
    m_position++;
    return *this;
  }
  vle_iterator operator++(int)
  {
    vle_iterator copy_this = *this;
    (*this)++;
    return copy_this;
  }
  vle_iterator& operator--()
  {
    m_position--;
    return *this;
  }
  vle_iterator operator--(int)
  {
    vle_iterator copy_this = *this;
    (*this)--;
    return copy_this;
  }
  vle_iterator& operator+=(difference_type a_shift)
  {
    m_position += a_shift;
    return *this;
  }
  vle_iterator& operator-=(difference_type a_shift)
  {
    m_position -= a_shift;
    return *this;
  }
  reference operator[](size_t a_shift)
  {
    vle_iterator copy_this = *this;
    copy_this += a_shift;
    return *copy_this;
  }
  static inline difference_type distance(vle_iterator a_it_left,
    vle_iterator a_it_right)
  {
    return a_it_left.m_position - a_it_right.m_position;
  }
  static inline bool less(vle_iterator a_it_left, vle_iterator a_it_right)
  {
    return a_it_left.m_position < a_it_right.m_position;
  }
  static inline bool equal(vle_iterator a_it_left, vle_iterator a_it_right)
  {
    return a_it_left.m_position == a_it_right.m_position;
  }
};

inline vle_iterator::difference_type
  operator-(vle_iterator a_it_left, vle_iterator a_it_right)
{
  return vle_iterator::distance(a_it_left, a_it_right);
}
inline vle_iterator operator+(vle_iterator a_it,
  vle_iterator::difference_type a_shift)
{
  return a_it += a_shift;
}
inline vle_iterator operator+(vle_iterator::difference_type a_shift,
  vle_iterator a_it)
{
  return a_it + a_shift;
}
inline vle_iterator operator-(vle_iterator a_it,
  vle_iterator::difference_type a_shift)
{
  return a_it -= a_shift;
}
inline bool operator==(vle_iterator a_it_left, vle_iterator a_it_right)
{
  return vle_iterator::equal(a_it_left, a_it_right);
}
inline bool operator!=(vle_iterator a_it_left, vle_iterator a_it_right)
{
  return !vle_iterator::equal(a_it_left, a_it_right);
}
inline bool operator<(vle_iterator a_it_left, vle_iterator a_it_right)
{
  return vle_iterator::less(a_it_left, a_it_right);
}
inline bool operator<=(vle_iterator a_it_left, vle_iterator a_it_right)
{
  return (a_it_left < a_it_right) && (a_it_left == a_it_right);
}
inline bool operator>(vle_iterator a_it_left, vle_iterator a_it_right)
{
  return !(a_it_left <= a_it_right);
}
inline bool operator>=(vle_iterator a_it_left, vle_iterator a_it_right)
{
  return !(a_it_left < a_it_right);
}

vle_iterator vle_begin(TValueListEditor* ap_value_list_editor)
{
  return vle_iterator(ap_value_list_editor, 1);
}
vle_iterator vle_end(TValueListEditor* ap_value_list_editor)
{
  return vle_iterator(ap_value_list_editor, ap_value_list_editor->RowCount);
}
#endif //NOP

  #ifdef NOP
  //irs::cstr_convert::exec(irs::mlog());
  //irs::compiler_test::template_template_inheritance::exec(irs::mlog());
  //irs::display_parametrs_of_built_in_types(irs::mlog());
  //irs::convert_str_test(irs::mlog());

  //Russian_Russia.1251
  //Russian_Russia.866
  locale loccpp("Russian_Russia.1251");
  irs::mlog().imbue(loccpp);
  irs::mlog() << IRS_PI << endl;
  #ifdef NOP
  char* loc = setlocale(LC_ALL, "Russian_Russia.1251");
  if (loc) {
    irs::mlog() << loc << endl;
  } else {
    irs::mlog() << "bad locale" << endl;
  }
  #endif //NOP
  irs::mlog() << IRS_PI << endl;
  irs::raw_data_t<char> str(30);

  char alpha = 'я';
  if (isalpha(alpha, loccpp)) {
    irs::mlog() << alpha << " - буква" << endl;
  } else {
    irs::mlog() << alpha << " - не буква" << endl;
  }
  //sprintf(str.data(), "ѕривет");
  //irs::mlog() << str.data() << endl;

  std::string s;
  //locale loccpp("Russian_Russia.1251");
  //locale loc = irs::loc().get();
  locale::global(locale("Russian_Russia.1251"));
  //locale::global(loccpp);
  //irs::loc().get();
  irs::number_to_string(15.5, &s, locale());
  irs::mlog() << s << endl;
  #endif //NOP

#ifdef NOP
  typedef mxnet_client_queue_item_t queue_item_type;

  m_write_queue(),
  deque<queue_item_type> m_write_queue;
  void queue_push(const irs_u8 *ap_buf, irs_uarc a_index, irs_uarc a_size);
//! \brief —труктура дл€ очереди байтовых операций mxnet_client_t
struct mxnet_client_queue_item_t
{
  irs_uarc index;
  raw_data_t<irs_i32> data;

  mxnet_client_queue_item_t():
    index(0),
    data()
  {
  }
};
void irs::mxnet_client_t::queue_push(const irs_u8 *ap_buf, irs_uarc a_index,
  irs_uarc a_size)
{
  mxn_cnt_t var_front_idx = a_index/m_size_var_byte;
  mxn_cnt_t var_back_idx = (a_index + a_size)/m_size_var_byte;
  IRS_LIB_ASSERT(var_back_idx >= var_front_idx);
  mxn_cnt_t var_size = var_back_idx - var_front_idx + 1;
  m_write_queue.push_back(queue_item_type());
  m_write_queue.back().index = var_front_idx;
  raw_data_t<irs_i32>& data = m_write_queue.back().data;
  data.resize(var_size);
  data[0] = m_data_vars[var_front_idx];
  data[var_size - 1] = m_data_vars[var_back_idx];
  raw_data_view_t<irs_u8, irs_i32> data_u8(&data);

  size_t byte_shift_idx = a_index%m_size_var_byte;
  size_t size = static_cast<size_t>(a_size);
  c_array_view_t<const irs_u8> buf_view(ap_buf, size);
  mem_copy(buf_view, 0u, data_u8, byte_shift_idx, size);
}



{
  irs::handle_t<irs::hardflow_t> p_hardflow =
    irs::hardflow::make_udp_flow_client(
      "192.168.0.201",
      "5006")
    );
  size_t read_bits_byte_count = 0;
  size_t rw_bits_byte_count = 1; // в байтах
  size_t rw_regs_count = 10; // в регистах по 2 байта
  size_t read_regs_count = 0;
  irs::modbus_client_t modbus_client(
    p_hardflow,
    irs::modbus_client_t::mode_refresh_auto,
    read_bits_byte_count,
    rw_bits_byte_count,
    rw_regs_count,
    read_regs_count,
    irs::make_cnt_ms(200)
  );
}
#endif //NOP

