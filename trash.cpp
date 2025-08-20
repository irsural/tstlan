#include <irspch.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif // __BORLANDC__

#include "trash.h"

#include <irsfinal.h>

#include <string>
#include <fstream>

#ifdef NOP
bool file_exists(const std::string& path)
{
  std::string clean_path = remove_quotes(path);
  std::ifstream file(clean_path.c_str());
  return file.good();
}

bool create_file(const std::string& path)
{
  std::string clean_path = remove_quotes(path);
  std::ofstream file(clean_path.c_str());
  return file.is_open();
}
#endif //NOP

#ifdef NOP
    fs_t::file_t* file = fs_cppbuilder()->open(
      wstring_to_utf8(L"C:\\Users\\501\\Data\\Documents\\Временное\\Путь.txt"), fm_write);
    if (file) {
      string data = "1234";
      fs_cppbuilder()->write(file, reinterpret_cast<const uint8_t*>(data.c_str()), data.size());
      fs_cppbuilder()->close(file);
    } else {
      irs::mlog() << "Ошибка открытия файла" << endl;
    }
#endif //NOP

#ifdef NOP
    fstream fstrm("C:\\Users\\501\\Data\\Documents\\Временное\\Путь.txt", ios::out | ios::binary);
    if (!fstrm.is_open()) {
      mlog() << "Ошибка открытия файла!" << endl;
    }
    string path = param_to_utf8(irst("Путь к локальному файлу"));
    fstrm.write(path.c_str(), path.size());
    if (!fstrm.is_open()) {
      mlog() << "Ошибка записи файла!" << endl;
    }
#endif //NOP

#ifdef NOP
// Конвертация UTF-8 в UTF-16
std::u16string utf8_to_utf16(const std::string& utf8) {
  std::u16string utf16;

  try {
    std::mbstate_t state = std::mbstate_t();
    std::codecvt<char16_t, char, std::mbstate_t> const& facet =
      std::use_facet<std::codecvt<char16_t, char, std::mbstate_t> >(std::locale());

    const char* from_next = 0;
    char16_t* to_next = 0;

    // Выделяем буфер достаточного размера
    std::vector<char16_t> buf(utf8.size());

    auto result = facet.in(
      state,
      &utf8[0], &utf8[0] + utf8.size(), from_next,
      &buf[0], &buf[0] + buf.size(), to_next
    );

    if (result != std::codecvt_base::ok) {
      throw std::runtime_error("Conversion failed");
    }

    utf16.assign(&buf[0], to_next);
  }
  catch (const std::exception& e) {
    throw std::runtime_error(std::string("UTF-8 to UTF-16 conversion error: ") + e.what());
  }

  return utf16;
}

// Конвертация UTF-16 в UTF-8
std::string utf16_to_utf8(const std::u16string& utf16) {
  std::string utf8;

  try {
    std::mbstate_t state = std::mbstate_t();
    std::codecvt<char16_t, char, std::mbstate_t> const& facet =
      std::use_facet<std::codecvt<char16_t, char, std::mbstate_t> >(std::locale());

    const char16_t* from_next = 0;
    char* to_next = 0;

    // Выделяем буфер достаточного размера
    std::vector<char> buf(utf16.size() * 4);

    auto result = facet.out(
      state,
      &utf16[0], &utf16[0] + utf16.size(), from_next,
      &buf[0], &buf[0] + buf.size(), to_next
    );

    if (result != std::codecvt_base::ok) {
      throw std::runtime_error("Conversion failed");
    }

    utf8.assign(&buf[0], to_next);
  }
  catch (const std::exception& e) {
    throw std::runtime_error(std::string("UTF-16 to UTF-8 conversion error: ") + e.what());
  }

  return utf8;
}





// Преобразование u16string в wstring (Windows)
std::wstring u16string_to_wstring(const std::u16string& u16str)
{
  // В Windows wchar_t и char16_t имеют одинаковый размер (2 байта)
  static_assert(sizeof(wchar_t) == sizeof(char16_t),
                "This implementation is Windows-specific");

  std::wstring wstr;
  wstr.reserve(u16str.size());

  // Простое побайтовое копирование с приведением типа
  for (std::u16string::const_iterator it = u16str.begin(); it != u16str.end(); ++it) {
    wstr.push_back(static_cast<wchar_t>(*it));
  }

  return wstr;
}

// Преобразование wstring в u16string (Windows)
std::u16string wstring_to_u16string(const std::wstring& wstr)
{
  static_assert(sizeof(wchar_t) == sizeof(char16_t),
                "This implementation is Windows-specific");

  std::u16string u16str;
  u16str.reserve(wstr.size());

  // Простое побайтовое копирование с приведением типа
  for (std::wstring::const_iterator it = wstr.begin(); it != wstr.end(); ++it) {
    u16str.push_back(static_cast<char16_t>(*it));
  }

  return u16str;
}



//// Конвертация UTF-8 в wchar_t
//std::wstring utf8_to_wchar(const std::string& utf8)
//{
//  return u16string_to_wstring(utf8_to_utf16(utf8));
//}
//
//// Конвертация wchar_t в UTF-8
//std::string wchar_to_utf8(const std::wstring& wstr)
//{
//  return utf16_to_utf8(wstring_to_u16string(wstr));
//}




// Конвертация UTF-8 в std::wstring (Windows)
std::wstring utf8_to_wchar(const std::string& utf8)
{
  if (utf8.empty()) return L"";

  // Получаем необходимый размер буфера
  int wchars_count = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
  if (wchars_count == 0) {
    throw std::runtime_error("Failed to convert UTF-8 to wchar_t (size calculation)");
  }

  // Выделяем буфер
  std::vector<wchar_t> buffer(wchars_count);

  // Выполняем преобразование
  if (MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &buffer[0], wchars_count) == 0) {
    throw std::runtime_error("Failed to convert UTF-8 to wchar_t");
  }

  return std::wstring(&buffer[0]);
}

// Конвертация std::wstring в UTF-8 (Windows) с WC_NO_BEST_FIT_CHARS
std::string wchar_to_utf8(const std::wstring& wstr)
{
  if (wstr.empty()) return "";

  // Получаем необходимый размер буфера
  int utf8_count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
  if (utf8_count == 0) {
    throw std::runtime_error("Failed to convert wchar_t to UTF-8 (size calculation)");
  }

  // Выделяем буфер
  std::vector<char> buffer(utf8_count);

  // Выполняем преобразование
  if (WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &buffer[0], utf8_count, NULL, NULL) == 0) {
    throw std::runtime_error("Failed to convert wchar_t to UTF-8");
  }

  return std::string(&buffer[0]);
}




// Чтение UTF-8 файла
std::string read_utf8_file(const char* filename)
{
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file) throw std::runtime_error("Cannot open file");

  std::streamsize size = file.tellg();
  file.seekg(0);

  std::string content(static_cast<size_t>(size), '\0');
  if (!file.read(&content[0], size)) {
    throw std::runtime_error("Read failed");
  }

  return content;
}

// Запись wchar_t в файл
void write_wchar_file(const char* filename, const std::wstring& wstr)
{
  std::ofstream file(filename, std::ios::binary);
  if (!file) throw std::runtime_error("Cannot create file");

  if (!file.write(reinterpret_cast<const char*>(&wstr[0]),
         static_cast<std::streamsize>(wstr.size() * sizeof(wchar_t)))) {
    throw std::runtime_error("Write failed");
  }
}

// Чтение wchar_t из файла
std::wstring read_wchar_file(const char* filename)
{
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file) throw std::runtime_error("Cannot open file");

  std::streamsize size = file.tellg();
  file.seekg(0);

  if (size % sizeof(wchar_t) != 0) {
    throw std::runtime_error("Invalid file size for wchar_t");
  }

  std::wstring wstr(static_cast<size_t>(size / sizeof(wchar_t)), L'\0');
  if (!file.read(reinterpret_cast<char*>(&wstr[0]), size)) {
    throw std::runtime_error("Read failed");
  }

  return wstr;
}

// Запись UTF-8 в файл
void write_utf8_file(const char* filename, const std::string& utf8)
{
  std::ofstream file(filename, std::ios::binary);
  if (!file) throw std::runtime_error("Cannot create file");

  if (!file.write(&utf8[0], static_cast<std::streamsize>(utf8.size()))) {
    throw std::runtime_error("Write failed");
  }
}


int test_utf8() {
  try {
    // 1. Чтение исходного UTF-8 файла
    std::string utf8_content = read_utf8_file(
      "C:\\Users\\501\\Data\\Documents\\Временное\\input_utf8.txt");

    // 2. Конвертация в wchar_t и запись
    std::wstring wchar_content = utf8_to_wchar(utf8_content);
    write_wchar_file("C:\\Users\\501\\Data\\Documents\\Временное\\output_wchar.txt",
      wchar_content);

    // 3. Чтение wchar_t файла
    std::wstring read_wchar = read_wchar_file(
      "C:\\Users\\501\\Data\\Documents\\Временное\\output_wchar.txt");

    // 4. Конвертация обратно в UTF-8 и запись
    std::string utf8_output = wchar_to_utf8(read_wchar);
    write_utf8_file("C:\\Users\\501\\Data\\Documents\\Временное\\output_utf8.txt", utf8_output);

    // 5. Проверка целостности
    if (utf8_content != utf8_output) {
      throw std::runtime_error("Data integrity check failed");
    }

    std::cout << "All operations completed successfully\n";
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
#endif //NOP

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

