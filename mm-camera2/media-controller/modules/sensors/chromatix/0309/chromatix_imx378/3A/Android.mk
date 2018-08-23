# Copyright (C) 2016 Tcl Corporation Limited
ifeq ($(call is-vendor-board-platform,QCOM),true)
include $(call all-subdir-makefiles)
endif
