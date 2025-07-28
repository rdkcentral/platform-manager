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

#ifndef _DEVICEINFO_APIS_H
#define _DEVICEINFO_APIS_H

#include "ansc_debug_wrapper_base.h"
#include "plugin_main_apis.h"

ANSC_STATUS FwDlDmlDIGetDLFlag(ANSC_HANDLE hContext);
ANSC_STATUS FwDlDmlDIGetFWVersion(ANSC_HANDLE hContext);
ANSC_STATUS FwDlDmlDIGetDLStatus(ANSC_HANDLE hContext, char *DL_Status);
ANSC_STATUS FwDlDmlDIGetProtocol(char *Protocol);
ANSC_STATUS FwDlDmlDIDownloadNow(ANSC_HANDLE hContext);
ANSC_STATUS FwDmlDIGetURL(ANSC_HANDLE pMyObject);
ANSC_STATUS FwDmlDIGetImage(ANSC_HANDLE pMyObject);
ANSC_STATUS FwDlDmlDIDownloadAndFactoryReset(ANSC_HANDLE hContext);
ANSC_STATUS FwDlDmlDISetURL(ANSC_HANDLE hContext, char *URL);
ANSC_STATUS FwDlDmlDISetImage(ANSC_HANDLE hContext, char *Image);
ANSC_STATUS FwDlDmlDISetProtocol(char *Protocol);
void FwDlDmlDIGetDeferFWDownloadReboot(ULONG* puLong);
void FwDlDmlDISetDeferFWDownloadReboot(ULONG* DeferFWDownloadReboot, ULONG uValue);
void FwDl_ThreadFunc();
void FwDlAndFR_ThreadFunc();
convert_to_validFW(char *fw,char *valid_fw);

#endif
