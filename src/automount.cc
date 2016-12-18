/*
 * This file is part of Automount
 *
 * (c) Krystian Karaś <dev@karashome.pl>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
*/

#include <cstdio>
#include <tr1/memory>
#include <windows.h>
#include "coredll.h"
#include "debug.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    HANDLE hStore, hPartFirst, hPart;
    LPCTSTR Store = L"DSK2:";
    PARTINFO PartInfo = {0};
    PartInfo.cbSize = sizeof(PARTINFO);

    CoreDllPtr coreDll = CoreDll::load();

    if (!coreDll->isLoaded())
    {
        debug(L"Coredll.dll", L"Could not open coredll.dll library.\nError code: %d", GetLastError());
        return ERROR_INVALID_HANDLE;
    }

    hStore = coreDll->OpenStore(Store);

    if (hStore == INVALID_HANDLE_VALUE)
    {
        debug(L"OpenStore", L"Could not open \"%ls\" store.\nError code: %d", Store, GetLastError());
        return ERROR_INVALID_HANDLE;
    }

    hPartFirst = coreDll->FindFirstPartition(hStore, &PartInfo);

    if (hPartFirst == INVALID_HANDLE_VALUE)
    {
        debug(L"FindFirstPartition", L"Could not find first partition.\nError code: %d", GetLastError());
        return ERROR_INVALID_HANDLE;
    }

    hPart = coreDll->OpenPartition(hStore, PartInfo.szPartitionName);

    if (hPart == INVALID_HANDLE_VALUE)
    {
        debug(L"OpenPartition", L"Could not open first partition store.\nError code: %d", GetLastError());
        return ERROR_INVALID_HANDLE;
    }

    if (coreDll->MountPartition(hPart))
        debug(L"MountPartition", L"Success!");
    else
        debug(L"MountPartition", L"Failed!");

    return 0;
}
