
BSLASH := \\#
NULL_CHAR := #
SPACE := \ #
COLON := :#
DOTDOT := ..#
SPACE_ESC := &sp;#
COLON_ESC := &co;#
SPACE_OUT := ~sp~#
COLON_OUT := ~co~#
DOTDOT_OUT := ~dtdt~#

BSLASH2SLASH = $(subst $(BSLASH),/,$(1))

REMOVE_TAIL = $(patsubst %/,%,$(1))

#LOWER_CASE = $(shell echo translit($(1),[A-Z],[a-z])|$(M4))
LOWER_CASE = $(shell echo $(1)|$(TR) [A-Z] [a-z])

#ifneq ($(findstring Windows,$(OS)),)
# ...
#endif

FIND_FILES = $(shell $(FIND) $(1)/$(2) | $(SED) 's/^$(subst /,$(BSLASH)/,$(1))$(BSLASH)///')
FIND_FILES_ESC = $(shell $(FIND) $(1)/$(2) | $(SED) 's/^$(subst /,$(BSLASH)/,$(1))$(BSLASH)///' -e 's/:/$(BSLASH)&co;/g' -e 's/$(BSLASH) /$(BSLASH)&sp;/g')
FIND_FILES_4MAKE = $(shell $(FIND) $(1)/$(2) | $(SED) 's/^$(subst /,$(BSLASH)/,$(1))$(BSLASH)///')

FIND_FILES_ABS = $(shell $(FIND) $(1))
FIND_FILES_ABS_4MAKE = $(shell $(FIND) $(1) -e 's/$(BSLASH) /$(BSLASH)&sp;/g')
FIND_FILES_ABS_ESC = $(shell $(FIND) $(1) -e 's/:/$(BSLASH)&co;/g' -e 's/$(BSLASH) /$(BSLASH)&sp;/g')

FIND_FILES_4MAKE = $(shell $(FIND) $(1) | $(SED) 's/ /\\\ /g')

#ENCODE_ESC = $(shell echo $(1) | $(SED) -e 's/:/$(BSLASH)&co;/g' -e 's/$(BSLASH) /$(BSLASH)&sp;/g')
#DECODE_ESC = $(shell echo $(1) | $(SED) -e 's/$(BSLASH)&co;/:/g' -e 's/$(BSLASH)&sp;/$(BSLASH) / g')
ENCODE_ESC = $(subst $(SPACE),$(SPACE_ESC),$(subst $(COLON),$(COLON_ESC),$(1)))
DECODE_ESC = $(subst $(COLON_ESC),$(COLON),$(subst $(SPACE_ESC),$(SPACE),$(1)))
ENCODE_4MAKE = $(subst $(SPACE),$(SPACE_ESC),$(1))
DECODE_4MAKE = $(subst $(SPACE_ESC),$(SPACE),$(1))

CONVERT_TO_OUT = $(subst $(DOTDOT),$(DOTDOT_OUT),$(subst $(COLON),$(COLON_OUT),$(subst $(SPACE),$(SPACE_OUT),$(1))))
CONVERT_ESC_TO_OUT = $(subst $(DOTDOT),$(DOTDOT_OUT),$(subst $(COLON_ESC),$(COLON_OUT),$(subst $(SPACE_ESC),$(SPACE_OUT),$(1))))
CONVERT_4MAKE_TO_OUT = $(subst $(DOTDOT),$(DOTDOT_OUT),$(subst $(COLON),$(COLON_OUT),$(subst $(SPACE_ESC),$(SPACE_OUT),$(1))))

PROC_NO_EXIST = $(if $(wildcard $(1)),,$(call $(2),$(1)))
define MAKEDIRS0
	@echo '  Building directory: $(1)'
	@$(MKDIR) $(MKDIR_OP) $(subst $(BSLASH),/,$(1))	
endef
MAKEDIRS = $(call PROC_NO_EXIST,$(1),MAKEDIRS0)
