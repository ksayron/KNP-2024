#include "CodeExectution.h"
#include <Windows.h>
#include<iostream>
#include<string>
#include <codecvt>


void compileAndRunAssemblyFile(wchar_t* asmFileName) {

    std::wstring name = asmFileName;
    std::wstring masmCommand = L"ml /c " + name;
    std::wstring objFileName = name.substr(0, name.find_last_of('.')) + L".obj";
    std::wstring linkCommand = L"link /SUBSYSTEM:CONSOLE " + objFileName;
   
    std::wstring executeCommand = objFileName.substr(0, objFileName.find_last_of('.')) + L".exe";

    std::wstring launch = L"/k \"D:\\Soft\\Visual Studio\\Common7\\Tools\\VsDevCmd.bat\" && " + masmCommand + L" && " + linkCommand + L"&& cls && echo Консольный вывод кода: &&" + executeCommand+ L" && pause && exit";



    // Execute the commands in Visual Studio Developer Command Prompt
    std::wcout << L"\n\n Код " << name << L" запущен";
    ShellExecute(NULL, L"open", L"cmd.exe", launch.c_str(), NULL, SW_SHOWNORMAL);
}