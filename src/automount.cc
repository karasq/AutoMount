/*
 * This file is part of Automount
 *
 * (c) Krystian Karaś <dev@karashome.pl>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
*/

#include <cstdio>
#include <windows.h>
#include "coredll.h"
#include "debug.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    CoreDllPtr coreDll = CoreDll::load();

    if (!coreDll->isLoaded())
    {
        debug(L"Coredll.dll", L"Could not open coredll.dll library.\nError code: %d", GetLastError());
        return ERROR_INVALID_HANDLE;
    }

    STOREINFO stInfo = {0};
    stInfo.cbSize = sizeof(STOREINFO);

    HANDLE hStoreSearch = coreDll->FindFirstStore(&stInfo);

    if (hStoreSearch != INVALID_HANDLE_VALUE)
    {
        // Iterate through all stores
        do
        {
            debugStore(L"Found Store", &stInfo);

            HANDLE hStore = coreDll->OpenStore(stInfo.szDeviceName);

            if (hStore == INVALID_HANDLE_VALUE)
            {
                debug(L"OpenStore", L"Could not open store %ls.\nError code: %d", stInfo.szDeviceName, GetLastError());
                continue;
            }

            PARTINFO partInfo = {0};
            partInfo.cbSize = sizeof(PARTINFO);

            HANDLE hPartSearch = coreDll->FindFirstPartition(hStore, &partInfo);

            if (hPartSearch == INVALID_HANDLE_VALUE)
            {
                debug(L"FindFirstPartition", L"Could not find first partition.\nError code: %d", stInfo.szDeviceName, GetLastError());
                continue;
            }

            // Iterate through all partitions
            do
            {
                if (partInfo.dwAttributes & PARTITION_ATTRIBUTE_MOUNTED) // skip mounted
                    continue;
                if (wcslen(partInfo.szFileSys) == 0) // skip uknown file system
                    continue;

                CE_VOLUME_INFO volInfo = {0};
                volInfo.cbSize = sizeof(CE_VOLUME_INFO);

                BOOL volResult = coreDll->CeGetVolumeInfo(partInfo.szVolumeName, CeVolumeInfoLevelStandard, &volInfo);

                if (volResult && (volInfo.dwAttributes & CE_VOLUME_ATTRIBUTE_HIDDEN)) // skip hidden
                    continue;
                
                debugPartition(L"Found Partition", &partInfo, &volInfo);

                HANDLE hPart = coreDll->OpenPartition(hStore, partInfo.szPartitionName);

                if (hPart == INVALID_HANDLE_VALUE)
                {
                    debug(L"OpenPartition", L"Could not open partition %ls.\nError code: %d", partInfo.szPartitionName, GetLastError());
                    continue;
                }

                if (coreDll->MountPartition(hPart))
                    debug(L"MountPartition", L"Success! Partition %ls has been mounted.", partInfo.szPartitionName);
                else
                    debug(L"MountPartition", L"Failed! Partition %ls could not be mounted.\nErro code: %d", partInfo.szPartitionName, GetLastError());
            } while (coreDll->FindNextPartition(hPartSearch, &partInfo));

            coreDll->FindClosePartition(hPartSearch);
        } while (coreDll->FindNextStore(hStoreSearch, &stInfo));

        coreDll->FindCloseStore(hStoreSearch);
    }
    else
    {
        debug(L"FindFirstStore", L"Could not find first store.\nError code: %d", GetLastError());
        return ERROR_INVALID_HANDLE;
    }

    return 0;
}
