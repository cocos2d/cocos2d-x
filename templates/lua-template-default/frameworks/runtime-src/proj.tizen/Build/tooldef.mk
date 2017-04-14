# Add inputs and outputs from these tool invocations to the build variables

ifneq ($(strip $(SHELL_BIN)),)
SHELL = $(SHELL_BIN)
else
SHELL = sh
endif

ifneq ($(strip $(MKDIR_BIN)),)
MKDIR = $(MKDIR_BIN)
MKDIR_OP = -p
else
MKDIR = mkdir
MKDIR_OP = -p
endif

ifneq ($(strip $(UNAME_BIN)),)
UNAME = $(UNAME_BIN)
else
UNAME = uname
endif

ifneq ($(strip $(M4_BIN)),)
M4 = $(M4_BIN)
else
M4 = m4
endif

ifneq ($(strip $(TR_BIN)),)
TR = $(TR_BIN)
else
TR = tr
endif

ifneq ($(strip $(FIND_BIN)),)
FIND = $(FIND_BIN)
else
FIND = find
endif

ifneq ($(strip $(SED_BIN)),)
SED = $(SED_BIN)
else
SED = sed
endif

ifneq ($(strip $(GREP_BIN)),)
GREP = $(GREP_BIN)
else
GREP = grep
endif

ifneq ($(strip $(EDJE_CC_BIN)),)
EDJE_CC = $(EDJE_CC_BIN)
else
EDJE_CC = edje_cc
endif

ifneq ($(strip $(MSGFMT_BIN)),)
MSGFMT = $(MSGFMT_BIN)
else
MSGFMT = msgfmt
endif
