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
#include "storemgr.h"

#ifdef DEBUG
    void debug(LPCTSTR title, LPCTSTR format, ...);
#else
    #define debug(...)
#endif

inline void debugStore(LPCTSTR title, PSTOREINFO stInfo)
{
    debug(title,
          L"DevName: %ls\n"
          L"StoreName: %ls\n"
          L"Partitions mounted: %d/%d\n"
          L"SotreAttr: %08x\n"
          L"DevClass: %08x\n"
          L"DevType: %08x\n"
          L"DevFlags: %08x\n",
          stInfo->szDeviceName,
          stInfo->szStoreName,
          stInfo->dwMountCount,
          stInfo->dwPartitionCount,
          stInfo->dwAttributes,
          stInfo->dwDeviceClass,
          stInfo->dwDeviceType,
          stInfo->dwDeviceFlags);
}

inline void debugPartition(LPCTSTR title, PPARTINFO partInfo, PCE_VOLUME_INFO volInfo)
{
    debug(title,
          L"PartName: %ls\n"
          L"PartFilesys: %ls\n"
          L"VolName: %ls\n"
          L"PartAttr: %08x\n"
          L"PartType: %08x\n"
          L"VolStoreName: %ls\n"
          L"VolPartitionName: %ls\n"
          L"VolFlags: %08x\n"
          L"VolAttr: %08x\n",
          partInfo->szPartitionName,
          partInfo->szFileSys,
          partInfo->szVolumeName,
          partInfo->dwAttributes,
          partInfo->bPartType,
          volInfo->szStoreName,
          volInfo->szPartitionName,
          volInfo->dwFlags,
          volInfo->dwAttributes);
}

#endif // __DEBUG_H__