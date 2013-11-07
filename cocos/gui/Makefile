TARGET = libgui.a

INCLUDES = -I../ \
-I../editor-support \
-I../../external

SOURCES = UIRootWidget.cpp \
UIWidget.cpp \
UILayout.cpp \
UILayoutParameter.cpp \
UILayoutDefine.cpp \
CocosGUI.cpp \
UIHelper.cpp \
UIInputManager.cpp \
UILayer.cpp \
UIListView.cpp \
UIPageView.cpp \
UIScrollView.cpp \
UIButton.cpp \
UICheckBox.cpp \
UIImageView.cpp \
UILabel.cpp \
UILabelAtlas.cpp \
UILabelBMFont.cpp \
UILoadingBar.cpp \
UISlider.cpp \
UITextField.cpp

include ../2d/cocos2dx.mk

CXXFLAGS += -Wno-multichar

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
