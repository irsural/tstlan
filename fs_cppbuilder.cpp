#include <irspch.h>
#pragma hdrstop

#include <stringapiset.h>

#include "fs_cppbuilder.h"
#include "error.h"

#include <irsfinal.h>

namespace tstlan4 {

// Конвертация UTF-8 в wstring (Windows)
wstring utf8_to_wstring(const string& utf8)
{
  if (utf8.empty()) return L"";

  // Получаем необходимый размер буфера
  int wchars_count = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
  if (wchars_count == 0) {
    throw runtime_error("Failed to convert UTF-8 to wchar_t (size calculation)");
  }

  // Выделяем буфер
  vector<wchar_t> buffer(wchars_count);

  // Выполняем преобразование
  if (MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &buffer[0], wchars_count) == 0) {
    throw runtime_error("Failed to convert UTF-8 to wchar_t");
  }

  return wstring(&buffer[0]);
}

// Конвертация wstring в UTF-8 (Windows)
string wstring_to_utf8(const wstring& wstr)
{
  if (wstr.empty()) return "";

  // Получаем необходимый размер буфера
  int utf8_count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
  if (utf8_count == 0) {
    throw runtime_error("Failed to convert wchar_t to UTF-8 (size calculation)");
  }

  // Выделяем буфер
  vector<char> buffer(utf8_count);

  // Выполняем преобразование
  if (WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &buffer[0], utf8_count, NULL, NULL) == 0) {
    throw runtime_error("Failed to convert wchar_t to UTF-8");
  }

  return string(&buffer[0]);
}

class dir_iterator_dummy_t: public irs::dir_iterator_t
{
public:
  dir_iterator_dummy_t() {}
  virtual ~dir_iterator_dummy_t() {}
  virtual irs::fs_result_t next_dir_item(irs::file_info_t*)
  {
    return irs::fs_result_t::fsr_end_of_dir;
  }
  virtual irs::fs_result_t break_iter()
  {
    return irs::fs_result_t::fsr_success;
  }
};

bool fs_cppbuilder_t::is_mounted()
{
  return irs::fs_result_t::fsr_success;
}

irs::fs_result_t fs_cppbuilder_t::mkfs(const string& a_path)
{
  return irs::fs_result_t::fsr_error;
}

fs_cppbuilder_t::file_t* fs_cppbuilder_t::open(const string& a_filename,
  irs::file_mode_t a_mode)
{
  string mode = "";
  switch (a_mode) {
    case (irs::file_mode_t::fm_read): {
      mode = "r";
    } break;
    case (irs::file_mode_t::fm_write): {
      mode = "w";
    } break;
    case (irs::file_mode_t::fm_readwrite): {
      mode = "w+";
    } break;
    case (irs::file_mode_t::fm_append): {
      mode = "a+";
    } break;
  }
  return _wfopen(utf8_to_wstring(a_filename).c_str(), utf8_to_wstring(mode).c_str());
}

irs::fs_result_t fs_cppbuilder_t::close(file_t* a_file)
{
  if (fclose(fc(a_file)) == 0) {
    return irs::fs_result_t::fsr_success;
  } else {
    return irs::fs_result_t::fsr_error;
  }
}

size_t fs_cppbuilder_t::read(
  file_t* a_file, uint8_t* a_buffer, size_t a_count, irs::fs_result_t* ap_result
)
{
  size_t read_count =
    fread(static_cast<void*>(a_buffer), sizeof(uint8_t), a_count, fc(a_file));
  if (read_count == a_count || feof(fc(a_file))) {
    *ap_result = irs::fs_result_t::fsr_success;
    return read_count;
  } else {
    *ap_result = irs::fs_result_t::fsr_error;
    return read_count;
  }
}

irs::fs_result_t fs_cppbuilder_t::write(file_t* a_file, const uint8_t* a_buffer, size_t a_count)
{
  size_t written =
    fwrite(reinterpret_cast<const void*>(a_buffer), sizeof(uint8_t), a_count, fc(a_file));
  fflush(fc(a_file));
  if (written == a_count) {
    return irs::fs_result_t::fsr_success;
  } else {
    return irs::fs_result_t::fsr_error;
  }
}

size_t fs_cppbuilder_t::get_file_size(file_t* a_file, irs::fs_result_t* ap_result)
{
  *ap_result = irs::fs_result_t::fsr_success;
  fseek(fc(a_file), 0L, SEEK_END);
  return ftell(fc(a_file));
}

irs::fs_result_t fs_cppbuilder_t::truncate_to_zero(const string& a_filename)
{
  fs_cppbuilder_t::file_t* file_handle = open(a_filename, irs::file_mode_t::fm_write);
  if (file_handle == NULL) {
    return irs::fs_result_t::fsr_error;
  }

  irs::fs_result_t res = close(file_handle);
  return res;
}

irs::fs_result_t fs_cppbuilder_t::rename(const string& a_old_name,
  const string& a_new_name)
{
  irs::fs_result_t res = irs::fs_result_t::fsr_success;
  if (is_file_exists(a_new_name, &res)) {
    if (res != irs::fs_result_t::fsr_success) {
      return res;
    }

    res = unlink(a_new_name);
    if (res != irs::fs_result_t::fsr_success) {
      return res;
    }
  }
  int result = _wrename(utf8_to_wstring(a_old_name).c_str(), utf8_to_wstring(a_new_name).c_str());
  return result == 0 ? irs::fs_result_t::fsr_success : irs::fs_result_t::fsr_error;
}

bool fs_cppbuilder_t::is_dir_exists(const string&, irs::fs_result_t* ap_result)
{
  *ap_result = irs::fs_result_t::fsr_error;
  TL4_ERROR(irs::ec_standard, "Операция fs_cppbuilder_t::is_dir_exists не поддерживается");
  return false;
}

bool fs_cppbuilder_t::is_file_exists(const string& a_file_name, irs::fs_result_t* ap_result)
{
  *ap_result = irs::fs_result_t::fsr_error;
  TL4_ERROR(irs::ec_standard, "Операция fs_cppbuilder_t::is_file_exists не поддерживается");
  return false;
}

irs::fs_result_t fs_cppbuilder_t::unlink(const string&)
{
  TL4_ERROR(irs::ec_standard, "Операция fs_cppbuilder_t::unlink не поддерживается");
  return irs::fs_result_t::fsr_error;
}

irs::fs_result_t fs_cppbuilder_t::mkdir(const string&)
{
  TL4_ERROR(irs::ec_standard, "Операция fs_cppbuilder_t::mkdir не поддерживается");
  return irs::fs_result_t::fsr_error;
}

irs::handle_t<irs::dir_iterator_t> fs_cppbuilder_t::get_dir_iterator(const string&)
{
  TL4_ERROR(irs::ec_standard, "Операция fs_cppbuilder_t::get_dir_iterator не поддерживается");
  return irs::handle_t<irs::dir_iterator_t>(new dir_iterator_dummy_t());
}

FILE* fs_cppbuilder_t::fc(file_t* ap_vfile)
{
  return reinterpret_cast<FILE*>(ap_vfile);
}

} // namespace clb

