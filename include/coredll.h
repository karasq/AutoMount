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

#include <tr1/memory>
#include <windows.h>
#include "storemgr.h"

class CoreDll
{
    CoreDll();

  public:
    // Destructor
    virtual ~CoreDll();

    // Class type definitions
    typedef std::tr1::shared_ptr<CoreDll> shared_ptr;

    // Store Manager functions from Windows CE coredll.dll library
    typedef HANDLE (WINAPI *OpenStoreProc)(LPCTSTR szDeviceName);
    typedef HANDLE (WINAPI *FindFirstPartitionProc)(HANDLE hStore, PPARTINFO pPartInfo);
    typedef HANDLE (WINAPI *OpenPartitionProc)(HANDLE hStore, LPCTSTR szPartitionName);
    typedef BOOL (WINAPI *MountPartitionProc)(HANDLE hPartition);

    // Imported functions
    OpenStoreProc OpenStore;
    FindFirstPartitionProc FindFirstPartition;
    OpenPartitionProc OpenPartition;
    MountPartitionProc MountPartition;

    // Class functions
    static shared_ptr load();
    
    bool isLoaded() { 
        return m_isLoaded; 
    }
  private:
    // Single instance of this class
    static shared_ptr m_instance;

    // Dll Windows handle
    HMODULE m_hDll;

    // Initialization flag
    bool m_isLoaded;
};

// Alias for CoreDll pointer
typedef CoreDll::shared_ptr CoreDllPtr;

#endif // __COREDLL_H__