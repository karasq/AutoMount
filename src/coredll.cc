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
    FindFirstPartition(false),
    OpenPartition(false),
    MountPartition(false),
    m_isLoaded(false)
{
    m_hDll = LoadLibrary(L"coredll.dll");

    if (!m_hDll) {
        return;
    }
    
    OpenStore = reinterpret_cast<OpenStoreProc>(GetProcAddress(m_hDll, L"OpenStore"));
    FindFirstPartition = reinterpret_cast<FindFirstPartitionProc>(GetProcAddress(m_hDll, L"FindFirstPartition"));
    OpenPartition = reinterpret_cast<OpenPartitionProc>(GetProcAddress(m_hDll, L"OpenPartition"));
    MountPartition = reinterpret_cast<MountPartitionProc>(GetProcAddress(m_hDll, L"MountPartition"));

    if (!OpenStore || !FindFirstPartition || !OpenPartition || !MountPartition) {
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
