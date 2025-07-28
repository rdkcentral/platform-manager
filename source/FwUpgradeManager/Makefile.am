##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2020 Sky
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
AM_CFLAGS =

ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = fwupgrademanager

fwupgrademanager_DEPENDENCIES = \
    $(EXTRA_DEPENDENCIES) \
    ${top_builddir}/source/TR-181/middle_layer_src/libfwupgrademanager_middle_layer_src.la 

fwupgrademanager_CFLAGS = $(SYSTEMD_CFLAGS)
fwupgrademanager_CPPFLAGS = -I$(top_srcdir)/source/TR-181/include -I$(top_srcdir)/source/TR-181/middle_layer_src
fwupgrademanager_SOURCES = deviceinfo_apis.c Makefile.am ssp_action.c ssp_internal.h ssp_main.c ssp_messagebus_interface.c dm_pack_datamodel.c
fwupgrademanager_LDFLAGS = -lccsp_common -ldl -lfw_upgrade $(SYSTEMD_LDFLAGS) -lrdkloggers -lhal_platform -lsyscfg -lsysevent -lprivilege -lpthread
fwupgrademanager_LDADD = $(fwupgrademanager_DEPENDENCIES)
