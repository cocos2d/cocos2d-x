import sys, string, os
from Tkinter import *

# define class step
class step:
    stepFrame = None
    def initStep(self, root):
        return

    def checkStep(self):
        return None

# define class step1
class step1(step):
    step_entry = None
    def initStep(self, root):
        self.stepFrame = Frame(root)
        
        step_tip = Label(self.stepFrame, text="Input the android project path of your game:")
        step_tip.pack(anchor='nw', padx=30)
        step_tip2 = Label(self.stepFrame, text="(Pleasd avoid using spaces in your project path)")
        step_tip2.pack(anchor='nw', padx=30)
        self.step_entry = Entry(self.stepFrame)
        self.step_entry.pack(anchor='nw', fill=X, padx=30)
        return
    
    def checkStep(self):
        tipStr = None
        projPath = self.step_entry.get()
        haveDir = os.path.exists(projPath)
        isPorj = os.path.exists(projPath + '/AndroidManifest.xml')
        if projPath == None or len(projPath) == 0 or haveDir == False or isPorj == False:
            tipStr = 'The project path is wrong'
        return tipStr
    
    def getPath(self):
        return self.step_entry.get()

# define class step2
class step2(step):
    checkBtns = []
    checkValues = []
    def initStep(self, root, pluginList):
        self.stepFrame = Frame(root)
        
        step_tip = Label(self.stepFrame, text="Select plugins you needed:")
        step_tip.pack(anchor='nw', padx=30)
        
        for plugin in pluginList:
            var = StringVar()
            self.checkValues.append(var)
            btn = Checkbutton(self.stepFrame, text=plugin, variable=var, onvalue=plugin, offvalue='')
            btn.pack(anchor='nw', padx=50)
            self.checkBtns.append(btn)
        return
    
    def checkStep(self):
        tipStr = None
        num = 0
        for var in self.checkValues:
            if len(var.get()) != 0:
                num += 1
                break
        
        if num == 0:
            tipStr = 'At least select one plugin'
        return tipStr
    
    def getSelectedPlugins(self):
        selectPlugins = []
        for var in self.checkValues:
            if len(var.get()) != 0:
                plugin = var.get()
                selectPlugins.append(plugin)
        return selectPlugins
