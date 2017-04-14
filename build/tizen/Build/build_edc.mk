# EDC build script


FUNC_EDC2EDJ = $(patsubst %.edc,$(2)/%.edj,$(1))

# parameter :
#  $(1) - C/C++ soruce file
#  $(2) - output path
CONVERT_ESC_EDC_TO_EDJ = $(call CONVERT_4MAKE_TO_OUT,$(call FUNC_EDC2EDJ,$(1),$(2)))


# parameter :
#  $(1) - encoded one C/C++ soruce file
#  $(2) - output path
#  $(3) - build opt
# output :
#  $(4) - output files list
define EDJ_BUILD_PROC_RAW
$(call CONVERT_ESC_EDC_TO_EDJ,$(1),$(2)) : $(call DECODE_4MAKE,$(1))
	@echo '  Building file: $$<'
	@echo '  Invoking: EDC Resource Compiler'
	$$(call MAKEDIRS,$$(@D))
	$$(EDJE_CC) $(3) "$$<" "$$@"
	@echo '  Finished building: $$<'
$(4) += $(call CONVERT_ESC_EDC_TO_EDJ,$(1),$(2))
endef


# parameter :
#  $(1) - output paths
#  $(2) - src paths
#  $(3) - image inc paths
#  $(4) - sound inc paths
#  $(5) - font inc paths
# output :
#  $(6) - OBJS 
# return :
#  none
define EDJ_PROC_RAW

_OUTPUT_DIR := $$(strip $(1))#
_SRCS := $(2)# 
_IMAGE_DIRS := $(3)# 
_SOUND_DIRS := $(4)# 
_FONT_DIRS := $(5)# 

ifneq ($$(strip $$(_SRCS)),)

_ENC_SRCS := $$(call ENCODE_4MAKE,$$(_SRCS)) 

_NORMAL_SRCS := $$(filter-out %*.edc,$$(_ENC_SRCS))
_WIDLCARD_SRCS := $$(filter %*.edc,$$(_ENC_SRCS))

_ALL_SRCS := $$(call DECODE_4MAKE,$$(_NORMAL_SRCS)) \
             $$(foreach var,$$(_WIDLCARD_SRCS),$$(call FIND_FILES_4MAKE,$$(call DECODE_4MAKE,$$(var))))

ifneq ($$(strip $$(_ALL_SRCS)),)

_ENC_SRCS := $$(call ENCODE_4MAKE,$$(_ALL_SRCS)) 

_COMPILER_FLAGS := -id "$$(ENVENTOR_SHARED_RES_PATH)/images"
_COMPILER_FLAGS += -sd "$$(ENVENTOR_SHARED_RES_PATH)/sounds"
_COMPILER_FLAGS += -fd "$$(ENVENTOR_SHARED_RES_PATH)/fonts"

ifneq ($$(strip $$(_IMAGE_DIRS)),)
_COMPILER_FLAGS += $$(addprefix -id ,$$(_IMAGE_DIRS))
endif
ifneq ($$(strip $$(_SOUND_DIRS)),)
_COMPILER_FLAGS += $$(addprefix -sd ,$$(_SOUND_DIRS))
endif
ifneq ($$(strip $$(_FONT_DIRS)),)
_COMPILER_FLAGS += $$(addprefix -fd ,$$(_FONT_DIRS))
endif

$$(foreach var,$$(_ENC_SRCS),$$(eval $$(call EDJ_BUILD_PROC_RAW,$$(var),$$(_OUTPUT_DIR),$$(_COMPILER_FLAGS),$(6))))

endif  # (_(strip _(_ALL_SRCS)),)

endif  # (_(strip _(_SRCS)),)

endef
