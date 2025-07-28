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

noinst_LTLIBRARIES = libfwupgrademanager_middle_layer_src.la

libfwupgrademanager_middle_layer_src_la_CPPFLAGS = -I$(top_srcdir)/source/TR-181/include -I$(top_srcdir)/source/TR-181/middle_layer_src -I$(top_srcdir)/source/FwUpgradeManager
libfwupgrademanager_middle_layer_src_la_SOURCES = fwupgrademgr_dml.c  plugin_main_apis.c  plugin_main_apis.h  plugin_main.c
libfwupgrademanager_middle_layer_src_la_LDFLAGS = -lccsp_common -lrdkloggers -lhal_platform $(DBUS_LIBS) $(SYSTEMD_LDFLAGS) 
