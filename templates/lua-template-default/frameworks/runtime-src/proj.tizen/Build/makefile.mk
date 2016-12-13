#
# Usege : make -f <proj_root>/Build/makefile -C <proj_root>
#

BUILD_SCRIPT_VERSION := 1.2.3

.PHONY : app_version app_clean build_version


all : app_build

clean : app_clean

version : build_version


#PROJ_ROOT := $(call BSLASH2SLASH,$(PROJ_PATH))
PROJ_ROOT := .
BUILD_ROOT := $(PROJ_ROOT)/Build

include $(BUILD_ROOT)/basedef.mk

include $(PROJ_ROOT)/project_def.prop
-include $(PROJ_ROOT)/build_def.prop

include $(BUILD_ROOT)/funcs.mk

-include $(BUILD_ROOT)/tooldef.mk
-include $(BUILD_ROOT)/flags.mk
-include $(BUILD_ROOT)/platform.mk


APPTYPE := $(type)

OUTPUT_DIR := $(PROJ_ROOT)/$(BUILD_CONFIG)
OBJ_OUTPUT := $(OUTPUT_DIR)/${BUILD_ARCH}/objs

LOWER_APPNAME := $(call LOWER_CASE,$(APPNAME))
APPID2 := $(subst $(basename $(APPID)).,,$(APPID))

ifeq ($(strip $(APPTYPE)),app)
APPFILE := $(OUTPUT_DIR)/$(LOWER_APPNAME)
endif
ifeq ($(strip $(APPTYPE)),staticLib)
APPFILE := $(OUTPUT_DIR)/${BUILD_ARCH}/lib$(LOWER_APPNAME).a
endif
ifeq ($(strip $(APPTYPE)),sharedLib)
APPFILE := $(OUTPUT_DIR)/${BUILD_ARCH}/lib$(LOWER_APPNAME).so
endif

ifneq ($(strip $(PLATFORM_INCS)),)
PLATFORM_INCS_FILE := $(OBJ_OUTPUT)/platform_incs_file.inc
endif

include $(BUILD_ROOT)/build_c.mk


ifeq ($(strip $(APPTYPE)),app)
EXT_OP := -fPIE
endif
ifeq ($(strip $(APPTYPE)),staticLib)
EXT_OP := -fPIE
endif
ifeq ($(strip $(APPTYPE)),sharedLib)
EXT_OP := -fPIC
endif

C_OPT := $(COMPILE_FLAGS) $(TC_COMPILER_MISC) $(RS_COMPILER_MISC) $(EXT_OP) --sysroot="$(SYSROOT)" -Werror-implicit-function-declaration $(M_OPT)
CPP_OPT := $(CPP_COMPILE_FLAGS) $(TC_COMPILER_MISC) $(RS_COMPILER_MISC) $(EXT_OP) --sysroot="$(SYSROOT)" -Werror-implicit-function-declaration $(M_OPT)
C_OPT_FILE := $(PLATFORM_INCS_FILE)

OBJS := #

# Global C/C++
ifeq ($(strip $(USER_ROOT)),)
USER_ROOT := $(PROJ_ROOT)
endif
$(eval $(call C_PROC_RAW,$(OBJ_OUTPUT),$(USER_SRCS),$(USER_INC_DIRS),$(USER_INC_FILES),$(USER_DEFS),$(USER_UNDEFS),$(C_OPT),$(C_OPT_FILE),C,c,$(CC),OBJS))
$(foreach ext,cpp cxx cc c++ C,$(eval $(call C_PROC_RAW,$(OBJ_OUTPUT),$(USER_SRCS),$(USER_INC_DIRS),$(USER_CPP_INC_FILES),$(USER_CPP_DEFS),$(USER_CPP_UNDEFS),$(CPP_OPT),$(C_OPT_FILE),C++,$(ext),$(CXX),OBJS)))

# Individual C/C++
ifneq ($(strip $(USER_EXT_C_KEYS)),)
$(foreach var,$(USER_EXT_C_KEYS),$(eval $(call C_PROC_RAW,$(OBJ_OUTPUT),$(USER_EXT_$(var)_SRCS),$(USER_EXT_$(var)_INC_DIRS),$(USER_EXT_$(var)_INC_FILES),$(USER_EXT_$(var)_DEFS),$(USER_EXT_$(var)_UNDEFS),$(C_OPT),$(C_OPT_FILE),C,c,$(CC),OBJS)))
$(foreach ext,cpp cxx cc c++ C,$(foreach var,$(USER_EXT_C_KEYS),$(eval $(call C_PROC_RAW,$(OBJ_OUTPUT),$(USER_EXT_$(var)_SRCS),$(USER_EXT_$(var)_INC_DIRS),$(USER_EXT_$(var)_CPP_INC_FILES),$(USER_EXT_$(var)_CPP_DEFS),$(USER_EXT_$(var)_CPP_UNDEFS),$(C_OPT),$(C_OPT_FILE),C++,$(ext),$(CXX),OBJS))))
endif


ifneq ($(strip $(USER_LIB_DIRS)),)
_ENC_USER_LIB_DIRS := $(call ENCODE_4MAKE,$(USER_LIB_DIRS))
_ENC_USER_LIB_DIRS := $(addprefix -L,$(_ENC_USER_LIB_DIRS))
LIBPATHS := $(call DECODE_4MAKE,$(_ENC_USER_LIB_DIRS))
endif

LIBS += $(addprefix -l,$(USER_LIBS))

UOBJS += $(USER_OBJS)

M_OPT = -MMD -MP -MF"$(@:%.o=%.d)"

DEPS := $(OBJS:.o=.d)

ifneq ($(strip $(DEPS)),)
-include $(PROJ_ROOT)/Build/$(DEPS)
endif


ifeq ($(strip $(APPTYPE)),app)
$(APPFILE) : $(OBJS) $(UOBJS)
	@echo '  Building target: $@'
	@echo '  Invoking: C/C++ Linker'
	$(call MAKEDIRS,$(@D))
	$(CXX) -o $(APPFILE) $(OBJS) $(UOBJS) $(LIBPATHS) -Xlinker --as-needed $(LIBS) $(LINK_FLAGS) $(TC_LINKER_MISC) $(RS_LINKER_MISC) -pie -lpthread --sysroot="$(SYSROOT)" -Xlinker --version-script="$(PROJ_ROOT)/.exportMap" $(RS_LIB_PATHS) $(RS_LIBRARIES) -Xlinker -rpath="/opt/usr/apps/$(APPID)/lib" -Werror-implicit-function-declaration
	@echo '  Finished building target: $@'
endif
ifeq ($(strip $(APPTYPE)),staticLib)
$(APPFILE) : $(OBJS) $(UOBJS)
	@echo '  Building target: $@'
	@echo '  Invoking: Archive utility'
	$(call MAKEDIRS,$(@D))
	$(AR) -r $(APPFILE) $(OBJS) $(UOBJS) $(AR_FLAGS)
	@echo '  Finished building target: $@'
endif
ifeq ($(strip $(APPTYPE)),sharedLib)
$(APPFILE) : $(OBJS) $(UOBJS)
	@echo '  Building target: $@'
	@echo '  Invoking: C/C++ Linker'
	$(call MAKEDIRS,$(@D))
	$(CXX) -o $(APPFILE) $(OBJS) $(UOBJS) $(LIBPATHS) -Xlinker --as-needed $(LIBS) $(LINK_FLAGS) $(TC_LINKER_MISC) $(RS_LINKER_MISC) -shared -lpthread --sysroot="$(SYSROOT)" $(RS_LIB_PATHS) $(RS_LIBRARIES)
	@echo '  Finished building target: $@'
endif


$(OBJ_OUTPUT) :
	$(call MAKEDIRS,$@)

$(OUTPUT_DIR) :
	$(call MAKEDIRS,$@)


ifneq ($(strip $(PLATFORM_INCS)),)
$(PLATFORM_INCS_FILE) : $(OBJ_OUTPUT)
	@echo '  Building inc file: $@'
ifneq ($(findstring Windows,$(OS)),)
ifneq ($(findstring 3.82,$(MAKE_VERSION)),)
	$(file > $@,$(PLATFORM_INCS))
else
	@echo $(PLATFORM_INCS) > $@
endif
else
	@echo $(PLATFORM_INCS) > $@
endif
endif


include $(BUILD_ROOT)/build_edc.mk

#ifeq ($(strip $(ENVENTOR_SHARED_RES_PATH)),)
ENVENTOR_SHARED_RES_PATH ?= $(ENVENTOR_PATH)/share/enventor
#endif

EDJ_FILES :=

# Global EDCs
ifneq ($(strip $(USER_EDCS)),)
$(eval $(call EDJ_PROC_RAW,$(OUTPUT_DIR),$(USER_EDCS),$(USER_EDCS_IMAGE_DIRS),$(USER_EDCS_SOUND_DIRS),$(USER_EDCS_FONT_DIRS),EDJ_FILES))
endif

# Individual EDCs
ifneq ($(strip $(USER_EXT_EDC_KEYS)),)
$(foreach var,$(USER_EXT_EDC_KEYS),$(eval $(call EDJ_PROC_RAW,$(OUTPUT_DIR),$(USER_EXT_$(var)_EDCS),$(USER_EXT_$(var)_EDCS_IMAGE_DIRS),$(USER_EXT_$(var)_EDCS_SOUND_DIRS),$(USER_EXT_$(var)_EDCS_FONT_DIRS),EDJ_FILES)))
endif


include $(BUILD_ROOT)/build_po.mk

MO_FILES :=

# Global POs
ifneq ($(strip $(USER_POS)),)
$(eval $(call MO_PROC_RAW,$(OUTPUT_DIR),$(USER_POS),$(APPID2),MO_FILES))
endif


secondary-outputs : $(EDJ_FILES) $(MO_FILES)

-include appendix.mk

app_build : $(OUTPUT_DIR) $(APPFILE) secondary-outputs
	@echo ========= done =========


app_clean :
	rm -f $(APPFILE)
	rm -rf $(OUTPUT_DIR)

build_version :
	@echo makefile.mk : $(BUILD_SCRIPT_VERSION)
