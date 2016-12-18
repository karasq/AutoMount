/*
 * This file is part of Automount
 *
 * (c) Krystian Karaś <dev@karashome.pl>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
*/

#include <windows.h>
#include "debug.h"

#ifdef DEBUG

void debug(LPCTSTR title, LPCTSTR format, ...)
{
    TCHAR buffer[1024];

    va_list args;
    va_start(args, format);
    vswprintf(buffer, format, args);
    va_end(args);

    MessageBox(NULL, (LPCTSTR)buffer, title, MB_OK | MB_TOPMOST);
}

#endif