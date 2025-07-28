/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Sky
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
/*
 * Copyright [2014] [Cisco Systems, Inc.]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     LICENSE-2.0" target="_blank" rel="nofollow">http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef  _PLUGIN_MAIN_APIS_H
#define  _PLUGIN_MAIN_APIS_H

#include <stdio.h>
#include "ansc_debug_wrapper_base.h"
#include "ansc_common_structures.h"
#include "ansc_status.h"
#include "cosa_plugin_api.h" 
#include "ssp_global.h"

typedef  ANSC_HANDLE
(*PFN_DM_CREATE)
    (
        VOID
    );

typedef  ANSC_STATUS
(*PFN_DM_REMOVE)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_DM_INITIALIZE)
    (
        ANSC_HANDLE                 hThisObject
    );

#define  BASE_CONTENT                                                                       \
    /* start of object class content */                                                     \
    ULONG                           Oid;                                                    \
    ANSC_HANDLE                     hSbContext;                                             \
    PFN_DM_CREATE                   Create;                                                 \
    PFN_DM_REMOVE                   Remove;                                                 \
    PFN_DM_INITIALIZE               Initialize;                                             \

typedef struct 
_DEVICE_INFO
{
    BOOL            Download_Control_Flag;
    char            Current_Firmware[128];
    char            Firmware_To_Download[128];
    char            DownloadURL[2048];
    ULONG           DeferFWDownloadReboot;
} 
DEVICE_INFO, *PDEVICE_INFO;

//To store URL + FW + some extra overhead.
#define CM_HTTPURL_LEN (sizeof(((DEVICE_INFO *)0)->DownloadURL) + sizeof(((DEVICE_INFO *)0)->Firmware_To_Download) + 10)

#define BACKEND_MANAGER_CLASS_CONTENT                                       \
        PDEVICE_INFO            pDeviceInfo;                                \
        PCOSA_PLUGIN_INFO hCosaPluginInfo;

typedef  struct
_BACKEND_MANAGER_OBJECT
{
    BASE_CONTENT
    BACKEND_MANAGER_CLASS_CONTENT
}
BACKEND_MANAGER_OBJECT, *PBACKEND_MANAGER_OBJECT;

/* The OID for all objects s*/
#define DATAMODEL_BASE_OID                                 0


extern COSAGetParamValueByPathNameProc    g_GetParamValueByPathNameProc;
extern COSASetParamValueByPathNameProc    g_SetParamValueByPathNameProc;
extern COSAGetParamValueStringProc        g_GetParamValueString;
extern COSAGetParamValueUlongProc         g_GetParamValueUlong;
extern COSAGetParamValueIntProc           g_GetParamValueInt;
extern COSAGetParamValueBoolProc          g_GetParamValueBool;
extern COSASetParamValueStringProc        g_SetParamValueString;
extern COSASetParamValueUlongProc         g_SetParamValueUlong;
extern COSASetParamValueIntProc           g_SetParamValueInt;
extern COSASetParamValueBoolProc          g_SetParamValueBool;
extern COSAGetInstanceNumbersProc         g_GetInstanceNumbers;

extern COSAValidateHierarchyInterfaceProc g_ValidateInterface;
extern COSAGetHandleProc                  g_GetRegistryRootFolder;
extern COSAGetInstanceNumberByIndexProc   g_GetInstanceNumberByIndex;
extern COSAGetHandleProc                  g_GetMessageBusHandle;
extern COSAGetSubsystemPrefixProc         g_GetSubsystemPrefix;
extern COSAGetInterfaceByNameProc         g_GetInterfaceByName;
extern PCCSP_CCD_INTERFACE                g_pPnmCcdIf;
extern ANSC_HANDLE                        g_MessageBusHandle;
extern char*                              g_SubsystemPrefix;
extern COSARegisterCallBackAfterInitDmlProc  g_RegisterCallBackAfterInitDml;

ANSC_HANDLE
BackEndManagerCreate
    (
        VOID
    );

ANSC_STATUS
BackEndManagerInitialize
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
BackEndManagerRemove
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
