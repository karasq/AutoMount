/*
 * This file is part of Automount
 *
 * (c) Krystian Karaś <dev@karashome.pl>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <windows.h>

#ifdef DEBUG
    void debug(LPCTSTR title, LPCTSTR format, ...);
#else
    #define debug(...)
#endif

#endif // __DEBUG_H__