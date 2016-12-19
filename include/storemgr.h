/*
 * This file is part of Automount
 *
 * (c) Krystian Karaś <dev@karashome.pl>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
*/

#ifndef __STOREMGR__
#define __STOREMGR__

// Some missing CeGCC type definitions and constants
// Constants
#define DEVICENAMESIZE    8
#define STORENAMESIZE     32
#define FILESYSNAMESIZE   32
#define FORMATNAMESIZE    32
#define PARTITIONNAMESIZE 32
#define PROFILENAMESIZE   32
#define FOLDERNAMESIZE    32
#define VOLUMENAMESIZE    64
#define FSDDESCSIZE       32

/* attributes of a store */
#define STORE_ATTRIBUTE_READONLY    0x00000001
#define STORE_ATTRIBUTE_REMOVABLE   0x00000002
#define STORE_ATTRIBUTE_UNFORMATTED 0x00000004
#define STORE_ATTRIBUTE_AUTOFORMAT  0x00000008
#define STORE_ATTRIBUTE_AUTOPART    0x00000010
#define STORE_ATTRIBUTE_AUTOMOUNT   0x00000020

/* attributes for a partition */
#define PARTITION_ATTRIBUTE_EXPENDABLE 0x00000001  // partition may be trashed 
#define PARTITION_ATTRIBUTE_READONLY   0x00000002  // partition is read-only   
#define PARTITION_ATTRIBUTE_AUTOFORMAT 0x00000004  
#define PARTITION_ATTRIBUTE_ACTIVE     0x00000008
#define PARTITION_ATTRIBUTE_BOOT       0x00000008  // Active(DOS) == Boot(CE)
#define PARTITION_ATTRIBUTE_MOUNTED    0x00000010

#define STORAGE_DEVICE_CLASS_BLOCK         0x1
#define STORAGE_DEVICE_CLASS_MULTIMEDIA    0x2

/* storage device type definitions */
#define STORAGE_DEVICE_TYPE_PCIIDE               (1 << 0)
#define STORAGE_DEVICE_TYPE_FLASH                (1 << 1)
#define STORAGE_DEVICE_TYPE_ATA                  (1 << 2)
#define STORAGE_DEVICE_TYPE_ATAPI                (1 << 4)
#define STORAGE_DEVICE_TYPE_PCCARD               (1 << 5)
#define STORAGE_DEVICE_TYPE_CFCARD               (1 << 6)
#define STORAGE_DEVICE_TYPE_SRAM                 (1 << 7)
#define STORAGE_DEVICE_TYPE_DVD                  (1 << 8)
#define STORAGE_DEVICE_TYPE_CDROM                (1 << 9)
#define STORAGE_DEVICE_TYPE_USB                  (1 << 10)
#define STORAGE_DEVICE_TYPE_1394                 (1 << 11)
#define STORAGE_DEVICE_TYPE_DOC                  (1 << 12)
#define STORAGE_DEVICE_TYPE_UNKNOWN              (1 << 29)
#define STORAGE_DEVICE_TYPE_REMOVABLE_DRIVE      (1 << 30) // Drive itself is removable
#define STORAGE_DEVICE_TYPE_REMOVABLE_MEDIA      (1 << 31) // Just the media is removable ex. CDROM, FLOPPY

/* storage device flags */
#define STORAGE_DEVICE_FLAG_READWRITE      (1 << 0)
#define STORAGE_DEVICE_FLAG_READONLY       (1 << 1)
#define STORAGE_DEVICE_FLAG_TRANSACTED     (1 << 2)
#define STORAGE_DEVICE_FLAG_MEDIASENSE     (1 << 3)  // Device requires media sense calls
#define STORAGE_DEVICE_FLAG_XIP            (1 << 4)

/* Volume attributes */
#define CE_VOLUME_ATTRIBUTE_READONLY                0x1
#define CE_VOLUME_ATTRIBUTE_HIDDEN                  0x2
#define CE_VOLUME_ATTRIBUTE_REMOVABLE               0x4
#define CE_VOLUME_ATTRIBUTE_SYSTEM                  0x8
#define CE_VOLUME_ATTRIBUTE_BOOT                    0x10

/* Volume flags */
#define CE_VOLUME_TRANSACTION_SAFE                  0x1     // Performs transaction safe operations
#define CE_VOLUME_FLAG_TRANSACT_WRITE               0x2
#define CE_VOLUME_FLAG_WFSC_SUPPORTED               0x4
#define CE_VOLUME_FLAG_LOCKFILE_SUPPORTED           0x8
#define CE_VOLUME_FLAG_NETWORK                      0x10
#define CE_VOLUME_FLAG_STORE                        0x20

// Type definitions
typedef ULONGLONG SECTORNUM;

/* information about a store */
typedef struct tagSTORAGEDEVICEINFO
{
    DWORD cbSize;
    TCHAR szProfile[PROFILENAMESIZE];
    DWORD dwDeviceClass;
    DWORD dwDeviceType;
    DWORD dwDeviceFlags;
} STORAGEDEVICEINFO, *PSTORAGEDEVICEINFO;

typedef struct tagSTOREINFO
{
    DWORD      cbSize;                  // sizeof(PD_STOREINFO)                   
    TCHAR      szDeviceName[DEVICENAMESIZE];
    TCHAR      szStoreName[STORENAMESIZE];
    DWORD      dwDeviceClass;
    DWORD      dwDeviceType;
    STORAGEDEVICEINFO sdi;
    DWORD      dwDeviceFlags;
    SECTORNUM  snNumSectors;            // number of sectors on store             
    DWORD      dwBytesPerSector;        // number of bytes per sector             
    SECTORNUM  snFreeSectors;           // number of unallocated sectors          
    SECTORNUM  snBiggestPartCreatable;  // biggest partition currently creatable  
    FILETIME   ftCreated;               // last time store was formatted          
    FILETIME   ftLastModified;          // last time partition table was modified 
    DWORD      dwAttributes;            // store attributes, see below            
    DWORD      dwPartitionCount;        // Number of Partitions 
    DWORD      dwMountCount;            // Number of partitions that have been mounted
} STOREINFO, *PSTOREINFO;

/* information about a partition */
typedef struct tagPARTINFO
{
    DWORD     cbSize;                               // sizeof(PD_PARTINFO)             
    TCHAR     szPartitionName[PARTITIONNAMESIZE];   // name of partition                 
    TCHAR     szFileSys[FILESYSNAMESIZE];
    TCHAR     szVolumeName[VOLUMENAMESIZE];
    SECTORNUM snNumSectors;                         // number of sectors in partition    
    FILETIME  ftCreated;                            // creation time of partition        
    FILETIME  ftLastModified;                       // last time partition was modified  
    DWORD     dwAttributes;                         // partition attributes, see below   
    BYTE      bPartType;                  
} PARTINFO, *PPARTINFO;

/* information about volume */
typedef struct _CE_VOLUME_INFO {
    DWORD cbSize;
    DWORD dwAttributes;
    DWORD dwFlags;
    DWORD dwBlockSize;
    TCHAR szStoreName[STORENAMESIZE];
    TCHAR szPartitionName[PARTITIONNAMESIZE];
} CE_VOLUME_INFO, *PCE_VOLUME_INFO, *LPCE_VOLUME_INFO;

typedef enum _CE_VOLUME_INFO_LEVEL {
    CeVolumeInfoLevelStandard,
} CE_VOLUME_INFO_LEVEL;

#endif