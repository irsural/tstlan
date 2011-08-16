//---------------------------------------------------------------------------
#include <irspch.h>
#pragma hdrstop

#include <irserror.h>

#include <irsfinal.h>
//---------------------------------------------------------------------------
USEFORM("main.cpp", MainForm);
USEFORM("options.cpp", OptionsForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  irs::exception_error_handler_t exception_error_handler;

  try
  {
    Application->Initialize();
    Application->Title = "Тест сети 4";
    Application->CreateForm(__classid(TMainForm), &MainForm);
    Application->Run();
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  catch (...)
  {
    try
    {
      throw Exception("");
    }
    catch (Exception &exception)
    {
      Application->ShowException(&exception);
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
