#include <irspch.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif // __BORLANDC__

#include "trash.h"

#include <irsfinal.h>

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

  char alpha = 'Я';
  if (isalpha(alpha, loccpp)) {
    irs::mlog() << alpha << " - буква" << endl;
  } else {
    irs::mlog() << alpha << " - не буква" << endl;
  }
  //sprintf(str.data(), "Привет");
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
//! \brief Структура для очереди байтовых операций mxnet_client_t
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
#endif //NOP

