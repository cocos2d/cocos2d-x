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

#import head files by python version.
if int(platform.python_version().split('.')[0])>=3:
    from tkinter import *
    from tkinter.filedialog import *
    from tkinter.messagebox import *
else:
    from Tkinter import *
    from tkFileDialog import *
    from tkMessageBox import *


class ThreadedTask(threading.Thread):
    """Create cocos project thread.
    """
    def __init__(self, queue, projectName, packageName, language, projectPath):
        threading.Thread.__init__(self)
        self.queue = queue
        self.projectName = projectName
        self.packageName = packageName
        self.language = language
        self.projectPath = projectPath

    def run(self):
        """Create cocos project.
        custom message rules to notify ui
        As follow:
            begin@%d@%d@%s  --- create before
            doing@%d@%d@%s  --- creating
            end@%d@%d@%s    --- create after
        """
        #delete exist project.
        if os.path.exists(os.path.join(self.projectPath, self.projectName)):
            print ("###begin remove... " + self.projectName)
            shutil.rmtree(os.path.join(self.projectPath, self.projectName))
            print ("###remove finish:  " + self.projectName)
        putMsg = "begin@%d@%d@%s" %(0, 100, "begin create")
        self.queue.put(putMsg)

        project = CocosProject()
        breturn = project.createPlatformProjects(
            self.projectName,
            self.packageName,
            self.language,
            self.projectPath,
            self.newProjectCallBack
        )
        if breturn:
            putMsg = "end@%d@%d@%s" %(100, 100, "create successful")
        else:
            putMsg = "end@%d@%d@%s" %(100, 100, "create failure")
        self.queue.put(putMsg)

    def newProjectCallBack(self, step, totalStep, showMsg):
        """Creating cocos project callback.
        """
        putMsg = "doing@%d@%d@%s" %(step, totalStep, showMsg)
        self.queue.put(putMsg)

class StdoutRedirector(object):
    """Redirect output.
    """
    def __init__(self, text_area):
        self.text_area = text_area

    def write(self, str):
        self.text_area.insert(END, str)
        self.text_area.see(END)

class TkCocosDialog():
    def __init__(self):
        self.projectName = ""
        self.packageName = ""
        self.language = ""
        self.old_stdout = sys.stdout

        print("create_project.py -n MyGame -k com.MyCompany.AwesomeGame -l javascript -p c:/mycompany")
        # top window
        self.top = Tk()
        self.top.title("CocosCreateProject")

        # project name frame
        self.frameName = Frame(self.top)
        self.labName = Label(self.frameName, text="projectName:", width=15)
        self.strName = StringVar()
        self.strName.set("MyGame")
        self.editName = Entry(self.frameName, textvariable=self.strName, width=40 )
        self.labName.pack(side = LEFT, fill = BOTH)
        self.editName.pack(side = LEFT)
        self.frameName.pack(padx=0, pady=10, anchor="nw")

        # package name frame
        self.framePackage = Frame(self.top)
        self.labPackage = Label(self.framePackage, text="packageName:", width=15)
        self.strPackage=StringVar()
        self.strPackage.set("com.MyCompany.AwesomeGame")
        self.editPackage = Entry(self.framePackage, textvariable=self.strPackage, width=40 )
        self.labPackage.pack(side = LEFT)
        self.editPackage.pack(side = LEFT)
        self.framePackage.pack(padx=0, anchor="nw")

        # project path frame
        self.framePath = Frame(self.top)
        self.labPath = Label(self.framePath, text="projectPath:", width=15)
        self.editPath = Entry(self.framePath, width=40)
        self.btnPath = Button(self.framePath, text="...", width=10, command = self.pathCallback)
        self.labPath.pack(side = LEFT)
        self.editPath.pack(side = LEFT)
        self.btnPath.pack(side = RIGHT)
        self.framePath.pack(padx=0, pady=10, anchor="nw")

        # language frame
        self.frameLanguage = Frame(self.top)
        self.labLanguage = Label(self.frameLanguage, text="language:", width=15)
        self.var=IntVar()
        self.var.set(1)
        self.checkcpp = Radiobutton(self.frameLanguage, text="cpp", variable=self.var, value=1, width=8)
        self.checklua = Radiobutton(self.frameLanguage, text="lua", variable=self.var, value=2, width=8)
        self.checkjs = Radiobutton(self.frameLanguage, text="javascript", variable=self.var, value=3, width=15)
        self.labLanguage.pack(side = LEFT)
        self.checkcpp.pack(side = LEFT)
        self.checklua.pack(side = LEFT)
        self.checkjs.pack(side = LEFT)
        self.frameLanguage.pack(padx=0,anchor="nw")

        # show progress
        self.progress = Scale(self.top, state= DISABLED, length=400, from_=0, to=100, orient=HORIZONTAL)
        self.progress.set(0)
        self.progress.pack(padx=10, pady=0, anchor="nw")

        # msg text frame
        self.frameText = Frame(self.top)
        self.text=Text(self.frameText, height=10, width=50)
        self.text.bind("<KeyPress>", lambda e : "break")
        self.scroll=Scrollbar(self.frameText, command=self.text.yview)
        self.text.configure(yscrollcommand=self.scroll.set)
        self.text.pack(side=LEFT, anchor="nw")
        self.scroll.pack(side=RIGHT, fill=Y)
        self.frameText.pack(padx=10, pady=5, anchor="nw")

        # new project button
        self.frameOperate = Frame(self.top)
        self.btnCreate = Button(self.frameOperate, text="create", width=15, height =5, command = self.createBtnCallback)
        self.btnCreate.pack(side = LEFT)
        self.frameOperate.pack(pady=20)

        #center window on desktop
        self.top.update()
        curWidth = self.top.winfo_reqwidth()
        curHeight = self.top.winfo_height()
        scnWidth = self.top.winfo_screenwidth()
        scnHeight = self.top.winfo_screenheight()
        tmpcnf = '%dx%d+%d+%d'%(curWidth, curHeight, int((scnWidth-curWidth)/2), int((scnHeight-curHeight)/2))
        self.top.geometry(tmpcnf)

        #fix size
        self.top.maxsize(curWidth, curHeight)
        self.top.minsize(curWidth, curHeight)

        #redirect out to text
        sys.stdout = StdoutRedirector(self.text)
        self.top.mainloop()
        sys.stdout = self.old_stdout

    def process_queue(self):
        """
        """
        #message is empty
        if self.queue.empty():
            self.top.after(100, self.process_queue)
            return

        #parse message
        msg = self.queue.get(0)
        msglist = msg.split("@")
        if len(msglist) < 4:
            return

        #begin
        if msglist[0] == "begin":
            self.progress['state'] = NORMAL
        #doing
        elif msglist[0] == "doing":
            pass

        self.progress.set(int(int(msglist[1])*100/int(msglist[2])))
        #end
        if msglist[0] == "end":
            showwarning("create", msglist[3])
            self.progress.set(0)
            self.text.insert(END,"=================END==============\n")
            self.progress['state'] = DISABLED
            self.btnCreate['state'] = NORMAL
            return
        self.top.after(100, self.process_queue)

    def createBtnCallback(self):
        """Create button event.
        """
        #Check project name
        projectName = self.editName.get()
        if projectName == "":
            showwarning("warning", "projectName is empty")
            return

        #Check the package name is effective
        packageName = self.editPackage.get()
        packageList = packageName.split(".")
        if len(packageList) < 2:
            showwarning("warning", "packageName format  error!")
            return
        for index in range(len(packageList)):
            if (packageList[index] == "") or (packageList[index][0].isdigit()):
                showwarning("warning", "packageName format  error!")
                return

        # get select language type
        language = "cpp"
        if self.var.get() == 1:
            language = "cpp"
        elif self.var.get() == 2:
            language = "lua"
        elif self.var.get() == 3:
            language = "javascript"

        projectPath = self.editPath.get()
        if projectPath == "":
            showwarning("warning", "projectPath is empty")
            return

        # if project has already exist,....
        if os.path.exists(os.path.join(projectPath, projectName)):
            if not askyesno("warning", "%s had exist,do you want to recreate!" %projectName ):
                return

        #create a new thread to deal with create new project.
        self.btnCreate['state'] = DISABLED
        self.queue = Queue.Queue()
        ThreadedTask(self.queue, projectName, packageName, language, projectPath).start()
        self.top.after(100, self.process_queue)

    def pathCallback(self):
        """Paht button event.
        """
        filepath = askdirectory()
        if filepath:
            self.editPath.delete(0, END)
            self.editPath.insert(0, filepath)

if __name__ =='__main__':
    TkCocosDialog()