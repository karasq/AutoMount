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
	HANDLE hStore, hPartFirst, hPart;
	LPCTSTR Store = L"DSK2:";
	PARTINFO PartInfo = { 0 };
	PartInfo.cbSize = sizeof(PARTINFO);

	HMODULE hlib = LoadLibrary(L"coredll.dll");

	if ( !hlib ) {
		debug(L"Coredll.dll", L"Could not open coredll.dll library.\nError code: %d", GetLastError());
		return ERROR_INVALID_HANDLE;
	}

	OpenStoreProc OpenStore = (OpenStoreProc) GetProcAddress(hlib, L"OpenStore");
	FindFirstPartitionProc FindFirstPartition = (FindFirstPartitionProc) GetProcAddress(hlib, L"FindFirstPartition");
	OpenPartitionProc OpenPartition = (OpenPartitionProc) GetProcAddress(hlib, L"OpenPartition");
	MountPartitionProc MountPartition = (MountPartitionProc) GetProcAddress(hlib, L"MountPartition");

	if ( !OpenStore || !FindFirstPartition || !MountPartition ) {
		debug(L"Coredll.dll", L"Could not load functions from coredll.dll.\nError code: %d", GetLastError());
		return ERROR_INVALID_HANDLE;
	}

	hStore = OpenStore(Store);

	if ( hStore == INVALID_HANDLE_VALUE ) {
		debug(L"OpenStore", L"Could not open \"%ls\" store.\nError code: %d", Store, GetLastError());
		return ERROR_INVALID_HANDLE;
	}

	hPartFirst = FindFirstPartition(hStore, &PartInfo);
	
	if ( hPartFirst == INVALID_HANDLE_VALUE ) {
		debug(L"FindFirstPartition", L"Could not find first partition.\nError code: %d", GetLastError());
		return ERROR_INVALID_HANDLE;
	}

	hPart = OpenPartition(hStore, PartInfo.szPartitionName);

	if ( hPart == INVALID_HANDLE_VALUE ) {
		debug(L"OpenPartition", L"Could not open first partition store.\nError code: %d", GetLastError());
		return ERROR_INVALID_HANDLE;
	}

	if ( MountPartition(hPart) )
		debug(L"MountPartition", L"Success!");
	else
		debug(L"MountPartition", L"Failed!");

	FreeLibrary(hlib);

	return 0;
}
