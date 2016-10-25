# PO build script


_FUNC_PO2MO = $(patsubst %.po,$(2)/res/locale/%/LC_MESSAGES/$(3).mo,$(notdir $(1)))


# parameter :
#  $(1) - C/C++ soruce file
#  $(2) - output path
#  $(3) - app name
CONVERT_ESC_PO_TO_MO = $(call CONVERT_4MAKE_TO_OUT,$(call _FUNC_PO2MO,$(1),$(2),$(3)))


# parameter :
#  $(1) - encoded one C/C++ soruce file
#  $(2) - output path
#  $(3) - app name
# output :
#  $(4) - output files list
define MO_BUILD_PROC_RAW
$(call CONVERT_ESC_PO_TO_MO,$(1),$(2),$(3)) : $(call DECODE_4MAKE,$(1))
	@echo '  Building file: $$<'
	@echo '  Invoking: msgfmt String Formatter'
	$$(call MAKEDIRS,$$(@D))
	$$(MSGFMT) -o "$$@" "$$<"
	@echo '  Finished building: $$<'
$(4) += $(call CONVERT_ESC_PO_TO_MO,$(1),$(2),$(3))
endef

 
# parameter :
#  $(1) - output dir
#  $(2) - src paths
#  $(3) - app name
# output :
#  $(4) - OBJS 

define MO_PROC_RAW

_PROJ_ROOT := $(1)
_SRCS := $(2)
_APPNAME := $(3)

ifneq ($$(strip $$(_SRCS)),)

_ENC_SRCS := $$(call ENCODE_4MAKE,$$(_SRCS)) 

_NORMAL_SRCS := $$(filter-out %*.po,$$(_ENC_SRCS))
_WIDLCARD_SRCS := $$(filter %*.po,$$(_ENC_SRCS))

_ALL_SRCS := $$(call DECODE_4MAKE,$$(_NORMAL_SRCS)) \
             $$(foreach var,$$(_WIDLCARD_SRCS),$$(call FIND_FILES_4MAKE,$$(call DECODE_4MAKE,$$(var))))

ifneq ($$(strip $$(_ALL_SRCS)),)

_ENC_SRCS := $$(call ENCODE_4MAKE,$$(_ALL_SRCS)) 

$$(foreach var,$$(_ENC_SRCS),$$(eval $$(call MO_BUILD_PROC_RAW,$$(var),$$(_OUTPUT_DIR),$$(_APPNAME),$(4))))

endif  # (_(strip _(_ALL_SRCS)),)

endif  # (_(strip _(_SRCS)),)

endef
