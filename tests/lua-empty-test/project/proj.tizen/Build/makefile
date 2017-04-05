# 
# Usege : make -f <proj_root>/Build/makefile -C <proj_root> 
#
 
BUILD_SCRIPT_VERSION := 1.1.0

.PHONY : app_version app_build app_clean build_version


all : app_build

clean : app_clean

version : build_version

#PROJ_ROOT = .
BUILD_ROOT := $(PROJ_PATH)/Build#

ifeq ($(MAKE_NAME),mingw32-make)
ifneq ($(SHELL),)
OPTIONS += --eval="SHELL=$(SHELL)"
endif
endif

app_build :
	@echo $(MAKE) -f "$(BUILD_ROOT)/makefile.mk"
	@$(MAKE) -f "$(BUILD_ROOT)/makefile.mk" -C "$(PROJ_PATH)" $(OPTIONS)

app_clean :
	@$(MAKE) -f "$(BUILD_ROOT)/makefile.mk" -C "$(PROJ_PATH)" $(OPTIONS) clean

build_version :
	@echo makefile : $(BUILD_SCRIPT_VERSION)
	@$(MAKE) -f "$(BUILD_ROOT)/makefile.mk" -C "$(PROJ_PATH)" $(OPTIONS) version
