#pragma once

#include "MinimalIniFile.hpp"

#define WINDOW_CLASS _T("Haushaltsbuch")
#define WINDOW_TEXT  _T("�،v�� Rev.4rc")

bool MainWindow_Initialize();
bool MainWindow_PreTranslateMessage(MSG &msg);
