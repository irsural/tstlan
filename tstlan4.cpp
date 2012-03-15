//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <irserror.h>

#include "locktick.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
USEFORM("options.cpp", OptionsForm);
USEFORM("main.cpp", MainForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  irs::exception_error_handler_t exception_error_handler;

  try
  {
    Application->Initialize();
    Application->Title = "���� ���� 4";
    Application->CreateForm(__classid(TMainForm), &MainForm);
    Application->Run();
  }
  catch (Exception &exception)
  {
    tstlan4::tick_lock()->enable();
    Application->ShowException(&exception);
    tstlan4::tick_lock()->disable();
  }
  catch (...)
  {
    try
    {
      throw Exception("");
    }
    catch (Exception &exception)
    {
      tstlan4::tick_lock()->enable();
      Application->ShowException(&exception);
      tstlan4::tick_lock()->disable();
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
