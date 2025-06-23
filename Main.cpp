#include "pch.h"

#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(cli::array<System::String^>^ args)


{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Replace 'dllgui' with your actual project namespace (see top of MainForm.h)
    dllgui::MyForm form;
    Application::Run(% form);
    return 0;
}
