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

#include "plugin_main_apis.h"
#include "fwupgrademgr_dml.h"
#include "ssp_global.h"

extern PBACKEND_MANAGER_OBJECT               g_pBEManager;


/**********************************************************************  
    caller:     owner of this object 
    prototype: 
        ULONG
        FirmwareUpgrade_GetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                char*                       pValue,
                ULONG*                      pUlSize
            );
    description:
        This function is called to retrieve string parameter value; 
    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;
                char*                       ParamName,
                The parameter name;
                char*                       pValue,
                The string value buffer;
                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;
    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.
**********************************************************************/

ULONG
FirmwareUpgrade_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{
    char DL_Status[128]={0};
    char Protocol[16]={0};
    PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;

    /* check the parameter name and return the corresponding value */
    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadStatus") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            /* collect value */
            FwDlDmlDIGetDLStatus((ANSC_HANDLE)pMyObject, DL_Status);
            if ( strlen(DL_Status) >= *pUlSize )
            {
                *pUlSize = strlen(DL_Status);
                return 1;
            }

            AnscCopyString(pValue, DL_Status);
        }
        return 0;
    }

    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadProtocol") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            /* collect value */
            FwDlDmlDIGetProtocol(Protocol);
            if ( strlen(Protocol) >= *pUlSize )
            {
                *pUlSize = strlen(Protocol);
                return 1;
            }

            AnscCopyString(pValue, Protocol);
        }
        return 0;
    }

    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadURL") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            /* collect value */
            if ( strlen(pMyObject->DownloadURL) >= *pUlSize )
            {
                *pUlSize = strlen(pMyObject->DownloadURL);
                return 1;
            }

            AnscCopyString(pValue, pMyObject->DownloadURL);
        }
        return 0;
    }

    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareToDownload") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            /* collect value */
            if ( strlen(pMyObject->Firmware_To_Download) >= *pUlSize )
            {
                *pUlSize = strlen(pMyObject->Firmware_To_Download);
                return 1;
            }

            AnscCopyString(pValue, pMyObject->Firmware_To_Download);
        }
        return 0;
    }
    return -1;
}

/**********************************************************************  
    caller:     owner of this object 
    prototype: 
        BOOL
        FirmwareUpgrade_SetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                char*                       pString
            );
    description:
        This function is called to set string parameter value; 
    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;
                char*                       ParamName,
                The parameter name;
                char*                       pString
                The updated string value;
    return:     TRUE if succeeded.
**********************************************************************/
BOOL
FirmwareUpgrade_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    )
{
    PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;
    /* check the parameter name and set the corresponding value */
    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadURL") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            if(FwDlDmlDISetURL((ANSC_HANDLE)pMyObject, pString) == ANSC_STATUS_BAD_SIZE)
            {
                CcspTraceError(("X_RDKCENTRAL-COM_FirmwareDownloadURL string is too long\n"));
                return 0;
            }
        }
        else
        {
            CcspTraceError(("FW DL is not allowed for this image type \n"));
        }
        return 1;
    }

    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareToDownload") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            if(FwDlDmlDISetImage((ANSC_HANDLE)pMyObject, pString) == ANSC_STATUS_BAD_SIZE)
            {
                CcspTraceError(("X_RDKCENTRAL-COM_COM_FirmwareToDownload string is too long\n"));
                return 0;
            }
        }
        else
        {
            CcspTraceError(("FW DL is not allowed for this image type \n"));
        }
        return 1;
    }

   if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadProtocol") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            FwDlDmlDISetProtocol(pString);
        }
        else
        {
            CcspTraceError(("FW DL is not allowed for this image type \n"));
        }
        return 1;
    }

    return 0;
}


/**********************************************************************
    caller:     owner of this object

    prototype:
        BOOL
        FirmwareUpgrade_GetParamBoolValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                BOOL*                       pBool
            );

    description:
        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.
**********************************************************************/
BOOL
FirmwareUpgrade_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{
    PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;
    /* check the parameter name and return the corresponding value */
    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadNow") == 0)
    {
         if(pMyObject->Download_Control_Flag)
         {
                *pBool = FALSE;
         }
        return 1;
    }
}

/**********************************************************************
    caller:     owner of this object

    prototype:

        BOOL
        FirmwareUpgrade_SetParamBoolValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                BOOL                        bValue
            );

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.
**********************************************************************/
BOOL
FirmwareUpgrade_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    )
{
    PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;
    /* check the parameter name and set the corresponding value */
    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadNow") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            if(bValue)
            {
                FwDlDmlDIDownloadNow((ANSC_HANDLE)pMyObject);
            }
        }
        else
        {
            CcspTraceError(("FW DL is not allowed for this image type \n"));
        }
        return 1;
    }
    return 0;
}

/**********************************************************************
    caller:     owner of this object

    prototype:
        BOOL
        FirmwareUpgrade_GetParamIntValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                int*                        pInt
            );

    description:
        This function is called to retrieve Integer parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                INT*                        pInt
                The buffer of returned integer value;

    return:     TRUE if succeeded.
**********************************************************************/
BOOL
FirmwareUpgrade_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    )
{
    PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;
    /* check the parameter name and return the corresponding value */
    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadAndFactoryReset") == 0)
    {
         if(pMyObject->Download_Control_Flag)
         {
             *pInt = 0;
         }
         return 1;
    }
    return 0;
}

/**********************************************************************
    caller:     owner of this object

    prototype:

        BOOL
        FirmwareUpgrade_SetParamBoolValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                INT                        bValue
            );

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                INT                         iValue
                The updated INT value;

    return:     TRUE if succeeded.
**********************************************************************/
BOOL
FirmwareUpgrade_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int                         iValue
    )
{
    PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;
    /* check the parameter name and set the corresponding value */
    if (strcmp(ParamName, "X_RDKCENTRAL-COM_FirmwareDownloadAndFactoryReset") == 0)
    {
        if(pMyObject->Download_Control_Flag)
        {
            if(iValue)
            {
                FwDlDmlDIDownloadAndFactoryReset((ANSC_HANDLE)pMyObject);
            }
        }
        else
        {
            CcspTraceError(("FW DL is not allowed for this image type \n"));
        }
        return 1;
    }
    return 0;
}

/***********************************************************************

 APIs for Object:

    DeviceInfo.X_RDKCENTRAL-COM_xOpsDeviceMgmt.RPC.

    *  FirmwareUpgradeRPC_GetParamUlongValue
    *  FirmwareUpgradeRPC_SetParamUlongValue

***********************************************************************/

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        FirmwareUpgradeRPC_GetParamUlongValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                ULONG*                      puLong
            );

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
FirmwareUpgradeRPC_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    )
{
	PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;
    /* check the parameter name and return the corresponding value */
    if (strcmp(ParamName, "DeferFWDownloadReboot") == 0)
    {
        /* collect value */
        *puLong = pMyObject->DeferFWDownloadReboot;
        return TRUE;
    }
    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        FirmwareUpgradeRPC_SetParamUlongValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                ULONG                       uValue
            );

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
FirmwareUpgradeRPC_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG                       uValue
    )
{
	PDEVICE_INFO pMyObject = (PDEVICE_INFO) g_pBEManager->pDeviceInfo;
    /* check the parameter name and set the corresponding value */
    if (strcmp(ParamName, "DeferFWDownloadReboot") == 0)
    {
        /* collect value */
		FwDlDmlDISetDeferFWDownloadReboot(&(pMyObject->DeferFWDownloadReboot), uValue);
		return TRUE;
    }
    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}
