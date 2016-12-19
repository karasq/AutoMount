/*
 * This file is part of Automount
 *
 * (c) Krystian Karaś <dev@karashome.pl>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
*/

#include "coredll.h"
//#include "debug.h"

// Initalisation of static CoreDll members
CoreDll::shared_ptr CoreDll::m_instance;

CoreDll::CoreDll() : 
    OpenStore(false),
    GetStoreInfo(false),
    FindFirstStore(false),
    FindCloseStore(false),
    FindNextStore(false),
    FindFirstPartition(false),
    FindNextPartition(false),
    FindClosePartition(false),
    OpenPartition(false),
    GetPartitionInfo(false),
    MountPartition(false),
    m_isLoaded(false)
{
    m_hDll = LoadLibrary(L"coredll.dll");

    if (!m_hDll) {
        return;
    }

    OpenStore = reinterpret_cast<OpenStoreProc>(GetProcAddress(m_hDll, L"OpenStore"));
    GetStoreInfo = reinterpret_cast<GetStoreInfoProc>(GetProcAddress(m_hDll, L"GetStoreInfo"));
    FindFirstStore = reinterpret_cast<FindFirstStoreProc>(GetProcAddress(m_hDll, L"FindFirstStore"));
    FindNextStore = reinterpret_cast<FindNextStoreProc>(GetProcAddress(m_hDll, L"FindNextStore"));
    FindCloseStore = reinterpret_cast<FindCloseStoreProc>(GetProcAddress(m_hDll, L"FindCloseStore"));
    FindFirstPartition = reinterpret_cast<FindFirstPartitionProc>(GetProcAddress(m_hDll, L"FindFirstPartition"));
    FindNextPartition = reinterpret_cast<FindNextPartitionProc>(GetProcAddress(m_hDll, L"FindNextPartition"));
    FindClosePartition = reinterpret_cast<FindClosePartitionProc>(GetProcAddress(m_hDll, L"FindClosePartition"));
    OpenPartition = reinterpret_cast<OpenPartitionProc>(GetProcAddress(m_hDll, L"OpenPartition"));
    GetPartitionInfo = reinterpret_cast<GetPartitionInfoProc>(GetProcAddress(m_hDll, L"GetPartitionInfo"));
    MountPartition = reinterpret_cast<MountPartitionProc>(GetProcAddress(m_hDll, L"MountPartition"));
    CeGetVolumeInfo = reinterpret_cast<CeGetVolumeInfoProc>(GetProcAddress(m_hDll, L"CeGetVolumeInfoW"));

    if (!OpenStore || !GetStoreInfo || !FindFirstStore || 
        !FindNextStore || !FindCloseStore  || !FindFirstPartition || !FindNextPartition || 
        !FindClosePartition || !OpenPartition || !GetPartitionInfo || !MountPartition || !CeGetVolumeInfo) 
    {
        m_isLoaded = false;
    } else {
        m_isLoaded = true;
    }
}

CoreDll::~CoreDll()
{
    if (m_hDll) {
        FreeLibrary(m_hDll);
    }
}

CoreDll::shared_ptr CoreDll::load()
{
    if (!m_instance) {
        m_instance = static_cast<CoreDll::shared_ptr>(new CoreDll());
    }

    return m_instance;
}
