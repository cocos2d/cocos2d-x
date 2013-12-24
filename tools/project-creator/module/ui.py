#!/usr/bin/python
#coding=utf-8
# ui.py
# Create cross-platform cocos2d-x project
# Copyright (c) 2012 cocos2d-x.org
# Author: chuanwei


import platform
import os, os.path
import shutil
import threading
import Queue
import time

from core import CocosProject

if int(platform.python_version().split('.')[0])>=3:
    from tkinter import *
    from tkinter.filedialog import *
    from tkinter.messagebox import *
else:
    from Tkinter import *
    from tkFileDialog import *
    from tkMessageBox import *



class ThreadedTask(threading.Thread):
    def __init__(self, queue, projectName, packageName, language, projectPath):
        threading.Thread.__init__(self)
        self.queue = queue
        self.projectName = projectName
        self.packageName = packageName
        self.language = language
        self.projectPath = projectPath

    def run(self):

        if os.path.exists(os.path.join(self.projectPath, self.projectName)):
            shutil.rmtree(os.path.join(self.projectPath, self.projectName))
        putMsg = "begin@%d@%d@%s" %(0,100,"begin create")
        self.queue.put(putMsg)
        project = CocosProject()
        breturn=project.createPlatformProjects(
            self.projectName,
            self.packageName,
            self.language,
            self.projectPath,
            self.newProjectCallBack
        )
        if breturn:
            putMsg = "end@%d@%d@%s" %(100,100,"create successful")
        else:
            putMsg = "end@%d@%d@%s" %(100,100,"create failure")
        self.queue.put(putMsg)

    def newProjectCallBack(self, step, totalStep, showMsg):
        putMsg = "doing@%d@%d@%s" %(step,totalStep,showMsg)
        self.queue.put(putMsg)

class TkProjectDialog():
    def __init__(self):

        #reload(sys)
        #sys.setdefaultencoding('utf-8')
        self.projectName = ""
        self.packageName = ""
        self.language = ""

        self.top = Tk()
        top_width = 500
        top_height = 250
        screen_width = self.top.winfo_screenwidth()
        screen_height = self.top.winfo_screenheight()
        #center window on desktop
        #self.top.geometry('%sx%s+%s+%s' % (top_width,top_height, int((screen_width - top_width)/2), int((screen_height - top_height)/2)) )
        #self.top.maxsize(top_width,top_height)
        #self.top.minsize(top_width,top_height)
        self.top.title("CocosCreateProject")

        self.frameName = Frame(self.top)
        self.labName = Label(self.frameName,text="project_name:",width=15)
        self.strName=StringVar()
        self.strName.set("MyGame")
        self.editName = Entry(self.frameName,textvariable=self.strName,width=40 )
        self.labName.pack(side = LEFT,fill = BOTH)
        self.editName.pack(side = LEFT)
        self.frameName.pack(padx=0,pady=10,anchor="nw")

        self.framePackage = Frame(self.top)
        self.labPackage = Label(self.framePackage,text="package_name:",width=15)
        self.strPackage=StringVar()
        self.strPackage.set("com.MyCompany.AwesomeGame")
        self.editPackage = Entry(self.framePackage,textvariable=self.strPackage,width=40 )
        self.labPackage.pack(side = LEFT)
        self.editPackage.pack(side = LEFT)
        self.framePackage.pack(padx=0, anchor="nw")

        self.framePath = Frame(self.top)
        self.labPath = Label(self.framePath,text="project_path:",width=15)
        self.editPath = Entry(self.framePath,width=40)
        self.btnPath = Button(self.framePath,text="...",width=10,command = self.pathCallback)
        self.labPath.pack(side = LEFT)
        self.editPath.pack(side = LEFT)
        self.btnPath.pack(side = RIGHT)
        self.framePath.pack(padx=0,pady=10,anchor="nw")

        self.frameLanguage = Frame(self.top)
        self.labLanguage = Label(self.frameLanguage,text="language:",width=15)
        self.var=IntVar()
        self.var.set(1)
        self.checkcpp = Radiobutton(self.frameLanguage,text="cpp", variable=self.var, value=1, width=8)
        self.checklua = Radiobutton(self.frameLanguage,text="lua", variable=self.var, value=2, width=8)
        self.checkjs = Radiobutton(self.frameLanguage,text="javascript", variable=self.var, value=3, width=15)
        self.labLanguage.pack(side = LEFT)
        self.checkcpp.pack(side = LEFT)
        self.checklua.pack(side = LEFT)
        self.checkjs.pack(side = LEFT)
        self.frameLanguage.pack(padx=0,anchor="nw")

        self.progress = Scale(self.top,state= DISABLED,length=400,from_=0,to=100,orient=HORIZONTAL)
        self.progress.set(0)
        self.progress.pack(padx=10,pady=0,anchor="nw")

        self.frameOperate = Frame(self.top)
        self.btnCreate = Button(self.frameOperate, text="create", width=15, height =5, command = self.createBtnCallback)
        self.btnCreate.pack(side = LEFT)
        self.frameOperate.pack(pady=20)

        self.top.mainloop()

    def process_queue(self):

        if self.queue.empty():
            self.top.after(100, self.process_queue)
            return
        msg = self.queue.get(0)
        msglist = msg.split("@")
        if len(msglist) < 4:
            return

        if msglist[0] == "begin":
            pass
        elif msglist[0] == "doing":
            self.progress.set(0)
        elif msglist[0] == "end":
            showwarning("create", msglist[3])
            self.btnCreate['state'] = NORMAL

        self.progress.set(int(int(msglist[1])*100/int(msglist[2])))

    def createBtnCallback(self):

        projectName = self.editName.get()
        if projectName == "":
            showwarning("warning", "project_name is empty")
            return

        packageName = self.editPackage.get()
        if packageName == "":
            showwarning("warning", "package_name is empty")
            return

        language = "cpp"
        if self.var.get() == 1:
            language = "cpp"
        elif self.var.get() == 2:
            language = "lua"
        elif self.var.get() == 3:
            language = "javascript"

        projectPath = self.editPath.get()
        if projectPath == "":
            showwarning("warning", "project_path is empty")
            return

        if os.path.exists(os.path.join(projectPath, projectName)):
            if not askyesno("warning", "%s had exist,do you want to recreate!" %projectName ):
                return

        print("state start")
        self.btnCreate['state'] = DISABLED
        self.queue = Queue.Queue()
        print("state end")
        ThreadedTask(self.queue, projectName, packageName, language, projectPath).start()
        self.top.after(100, self.process_queue)

    def pathCallback(self):
        filepath = askdirectory()
        if filepath:
            self.editPath.delete(0, END)
            self.editPath.insert(0, filepath)
            #entry.insert(0,filepath)

if __name__ =='__main__':
    TkProjectDialog()