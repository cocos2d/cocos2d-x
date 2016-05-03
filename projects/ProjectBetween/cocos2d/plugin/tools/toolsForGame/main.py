import sys, string, os
from Tkinter import *
import steps

Plugins = sys.argv[1]

print Plugins

pluginList = Plugins.split(':')
maxStep = 2
curStep = 1

stepList = []

# functions
# show step on the num index
def showStep(num):
    global stepList
    stepNum = len(stepList)
    if num >= stepNum or num <= 0 :
        pass
    
    i = 0
    while i < stepNum:
        if i == num:
            stepList[i].stepFrame.pack(fill=BOTH, anchor='nw')
        else:
            stepList[i].stepFrame.pack_forget()
        i += 1

# update the pre & next buttons status
def updateBtnState():
    global curStep
    global btnNextStep
    global btnPreStep
    if curStep == 1:
        btnPreStep['state'] = DISABLED
        btnNextStep['state'] = NORMAL
        btnNextStep['text'] = 'Next'
    elif curStep == maxStep:
        btnPreStep['state'] = NORMAL
        btnNextStep['state'] = NORMAL
        btnNextStep['text'] = 'Finish'
    else:
        btnPreStep['state'] = NORMAL
        btnNextStep['state'] = NORMAL
        btnNextStep['text'] = 'Next'

# next button clicked
def nextStep():
    if btnNextStep['text'] == 'close':
        root.quit()
        return
    
    global curStep
    nowStepObj = stepList[curStep - 1]
    bRet = nowStepObj.checkStep()
    if bRet != None:
        stepError['text'] = bRet
        return
    else:
        stepError['text'] = ''
    
    if curStep < maxStep:
        curStep += 1
        showStep(curStep - 1)
        updateBtnState()
    elif curStep == maxStep:
        # disable buttons when process
        btnPreStep['state'] = DISABLED
        btnNextStep['state'] = DISABLED
        
        # get user input arguments
        projPath = stepList[0].getPath()
        plugins = stepList[1].getSelectedPlugins()
        strPlugins = ''
        i = 0
        while i < len(plugins):
            strPlugins += "plugins/"
            strPlugins += plugins[i]
            if i != (len(plugins) - 1):
                strPlugins += ':'
            i += 1
        
        # process shell script to modify the game project
        ret = os.system('bash ./toolsForGame/addPluginForGame.sh ' + projPath + ' ' + strPlugins)
        
        if ret != 0:
            # enable buttons after process
            btnPreStep['state'] = NORMAL
            btnNextStep['state'] = NORMAL
            stepError['text'] = 'Error during process'
        else:
            # enable next button & change text to close
            btnNextStep['state'] = NORMAL
            btnNextStep['text'] = 'close'
            stepError['text'] = 'Process Successful!'

# pre button clicked
def preStep():
    global curStep
    global stepError
    stepError['text'] = ''
    if curStep > 1:
        curStep -= 1
        showStep(curStep - 1)
    
    updateBtnState()

# init root view
root = Tk()
root.title('Plugin-x Integration Guide')
root.geometry("600x400")
rootFrame = Frame(root)
rootFrame.pack(fill=BOTH)

# steps view
MyStep1 = steps.step1()
MyStep1.initStep(rootFrame)
MyStep2 = steps.step2()
MyStep2.initStep(rootFrame, pluginList)
stepList.append(MyStep1)
stepList.append(MyStep2)

MyStep1.stepFrame.pack(fill=BOTH, anchor='nw')

# add step error message
controlFrame = Frame(root)
controlFrame.pack(side=BOTTOM, fill=X, anchor='s')
stepError = Label(controlFrame)
stepError.pack(side=LEFT, padx=30)

# add step button
btnNextStep = Button(controlFrame, text='Next', command=nextStep)
btnPreStep = Button(controlFrame, text='Back', command=preStep, state=DISABLED)
btnNextStep.pack(side=RIGHT, padx=30)
btnPreStep.pack(side=RIGHT)

root.mainloop()
