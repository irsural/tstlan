//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//#include <irserror.h>
//#include <irslocale.h>
#include <irsinit.h>

#include "locktick.h"

#include <irsfinal.h>
//---------------------------------------------------------------------------
USEFORM("connectionlog.cpp", ConnectionLogForm);
USEFORM("main.cpp", MainForm);
//---------------------------------------------------------------------------
// 15.05.2020 5.0.20.250 rev. 81 mxsrclib rev. 1400 extern_libs rev. 37

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  //irs::exception_error_handler_t exception_error_handler;
  //irs::loc();
  irs::init();

  try
  {
    Application->Initialize();
    Application->Title = "Тест сети 4";
    Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TConnectionLogForm), &ConnectionLogForm);
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
