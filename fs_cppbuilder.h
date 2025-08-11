#ifndef fs_cppbuilderH
#define fs_cppbuilderH

#include <irsdefs.h>

#include <irsfs.h>
#include <irscpp.h>

#include <irsfinal.h>

namespace tstlan4 {

wstring utf8_to_wstring(const string& utf8);
string wstring_to_utf8(const wstring& wstr);

class fs_cppbuilder_t: public irs::fs_t
{
public:
  virtual ~fs_cppbuilder_t() {};

  virtual bool is_mounted();
  virtual irs::fs_result_t mkfs(const string& a_path);

  virtual file_t* open(const string& a_filename, irs::file_mode_t a_mode);
  virtual irs::fs_result_t close(file_t* a_file);
  virtual size_t read(
    file_t* a_file, uint8_t* a_buffer, size_t a_count, irs::fs_result_t* ap_result
  );
  virtual irs::fs_result_t write(file_t* a_file, const uint8_t* a_buffer, size_t a_count);

  virtual irs::fs_result_t rename(const string& a_old_name, const string& a_new_name);
  virtual size_t get_file_size(file_t* a_file, irs::fs_result_t* ap_result);

  virtual irs::fs_result_t truncate_to_zero(const string& a_filename);

  virtual bool is_dir_exists(const string& a_dir_name, irs::fs_result_t* ap_result);
  virtual bool is_file_exists(const string& a_file_name, irs::fs_result_t* ap_result);

  virtual irs::fs_result_t unlink(const string& a_file_name);

  virtual irs::fs_result_t mkdir(const string& a_dir_name);
  virtual irs::handle_t<irs::dir_iterator_t> get_dir_iterator(const string& a_dir_name);

private:
  // fc - file convert. Преобразование указателя на файл.
  static FILE* fc(file_t* ap_vfile);
};

} // namespace clb

#endif //fs_cppbuilderH

