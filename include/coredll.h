/*
 * This file is part of Automount
 *
 * (c) Krystian Karaś <dev@karashome.pl>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
*/

#ifndef __COREDLL_H__
#define __COREDLL_H__

#include <windows.h>
#include "storemgr.h"

// Store Manager functions from Windows CE coredll.dll library
typedef HANDLE (WINAPI *OpenStoreProc)(LPCTSTR szDeviceName);
typedef HANDLE (WINAPI *FindFirstPartitionProc)(HANDLE hStore, PPARTINFO pPartInfo);
typedef HANDLE (WINAPI *OpenPartitionProc)(HANDLE hStore, LPCTSTR szPartitionName);
typedef BOOL   (WINAPI *MountPartitionProc)(HANDLE hPartition);

#endif // __COREDLL_H__