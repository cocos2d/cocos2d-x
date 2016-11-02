# C/C++ build script


_FUNC_EXT2O = $(patsubst %.$(3),$(1)/%.o,$(2))
_FUNC_C2O = $(call _FUNC_EXT2O,$(1),$(2),c)
_FUNC_CPP2O = $(call _FUNC_EXT2O,$(1),$(2),cpp)


# parameter :
#  $(1) - C/C++ soruce file
#  $(2) - output path
#  $(3) - .ext
CONVERT_ESC_EXT_TO_O = $(addprefix $(2)/,$(call CONVERT_4MAKE_TO_OUT,$(patsubst %.$(3),%.o,$(1))))

CONVERT_ESC_C_TO_O = $(call CONVERT_ESC_EXT_TO_O,$(1),$(2),c)
CONVERT_ESC_CPP_TO_O = $(call CONVERT_ESC_EXT_TO_O,$(1),$(2),cpp)


# parameter :
#  $(1) - encoded one C/C++ soruce file
#  $(2) - output path
#  $(3) - ext title (C/C++)
#  $(4) - ext (c/cpp)
#  $(5) - compiler ($(CC)/$(CXX))
#  $(6) - build opt
#  $(7) - build opt file
# output :
#  $(8) - output files list
define C_BUILD_PROC_RAW
$(call CONVERT_ESC_EXT_TO_O,$(1),$(2),$(4)) : $(call DECODE_4MAKE,$(1)) $(7)
	@echo '  Building file: $$<'
	@echo '  Invoking: $(3) Compiler'
	$$(call MAKEDIRS,$$(@D))
	$(5) -c "$$<" -o "$$@" $(6) @$(7)
	@echo '  Finished building: $$<'
$(8) += $(call CONVERT_ESC_EXT_TO_O,$(1),$(2),$(4))
endef


# parameter :
#  $(1) - output paths
#  $(2) - src paths
#  $(3) - inc paths
#  $(4) - inc files
#  $(5) - Defs
#  $(6) - UnDefs
#  $(7) - compiler opt
#  $(8) - compiler opt file
#  $(9) - ext title (C/C++)
#  $(10) - ext (c/cpp)
#  $(11) - compiler ($(CC)/$(CXX))
# output :
#  $(12) - OBJS 
# return :
#  none
define C_PROC_RAW

_OUTPUT_DIR := $$(strip $(1))#
_SRCS := $(2)# 
_INCS := $(3)# 
_INC_FILES := $(4)# 
_DEFS := $(5)# 
_UNDEFS := $(6)# 

_OPT := $(7)
_OPT_FILE := $(8)

_EXT_TITLE := $(9)
_EXT := $(10)
_COMPILER := $(11)

#_OUTPUT_FILES := $(12)

_ENC_SRCS := $$(call ENCODE_4MAKE,$$(_SRCS)) 
_ENC_SRCS := $$(filter %.$$(_EXT),$$(_ENC_SRCS))

ifneq ($$(strip $$(_SRCS)),)

_NORMAL_SRCS := $$(filter-out %*.$$(_EXT),$$(_ENC_SRCS))
_WIDLCARD_SRCS := $$(filter %*.$$(_EXT),$$(_ENC_SRCS))

_ALL_SRCS := $$(call DECODE_4MAKE,$$(_NORMAL_SRCS)) \
             $$(foreach var,$$(_WIDLCARD_SRCS),$$(call FIND_FILES_4MAKE,$$(call DECODE_4MAKE,$$(var))))

ifneq ($$(strip $$(_ALL_SRCS)),)

_ENC_SRCS := $$(call ENCODE_4MAKE,$$(_ALL_SRCS)) 

_CDEFS := $$(CDEFS)
_CDEFS += $$(addprefix -D,$$(_DEFS))
_CDEFS += $$(addprefix -U,$$(_UNDEFS))

_ENC_C_INCS := $$(call ENCODE_4MAKE,$$(_INCS))
_ENC_C_INCS := $$(addprefix -I,$$(_ENC_C_INCS))
 
_ENC_INC_FILES := $$(call ENCODE_4MAKE,$$(_INC_FILES)) 
_ENC_INC_FILES += $$(addprefix -include,$$(_ENC_INC_FILES))

_C_INCS := $$(call DECODE_4MAKE,$$(_ENC_C_INCS) $$(_ENC_C_INC_FILES))

_DEFS := $$(_CDEFS) $$(_C_INCS) -I"pch" $$(_OPT)

$$(foreach var,$$(_ENC_SRCS),$$(eval $$(call C_BUILD_PROC_RAW,$$(var),$$(_OUTPUT_DIR),$$(_EXT_TITLE),$$(_EXT),$$(_COMPILER),$$(_DEFS),$$(_OPT_FILE),$(12))))

endif  # (_(strip _(_ALL_SRCS)),)

endif  # (_(strip _(_SRCS)),)


endef
