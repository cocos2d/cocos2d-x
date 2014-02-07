#!/usr/bin/python
#coding=utf-8
"""****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************"""

import platform
import os, os.path
import shutil
import threading
import time

from module.core import CocosProject

#import head files by python version.
if int(platform.python_version().split('.')[0])>=3:
    from tkinter import *
    from tkinter.filedialog import *
    from tkinter.messagebox import *
    from queue import *
else:
    from Tkinter import *
    from tkFileDialog import *
    from tkMessageBox import *
    from Queue import *


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
            print ("###begin remove:  " + self.projectName)
            try:
                shutil.rmtree(os.path.join(self.projectPath, self.projectName))
                print ("###remove finish:  " + self.projectName)
            except:
                print ("###remove folder failure %s" %self.projectName)
                putMsg = "end@%d@%d@%s" %(100, 100, "create failure")
                self.queue.put(putMsg)
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
            putMsg = "end@%d@%d@%s" %(100, 100, "Projected created successfully")
        else:
            putMsg = "end@%d@%d@%s" %(100, 100, "Failed to create project")
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

class TkCocosDialog(Frame):
    def __init__(self, parent):
        Frame.__init__(self,parent)

        self.projectName = ""
        self.packageName = ""
        self.language = ""

        self.parent = parent
        self.columnconfigure(3, weight=1)
        self.rowconfigure(5, weight=1)

        # project name frame
        self.labName = Label(self, text="Project Name:")
        self.strName = StringVar()
        self.strName.set("MyGame")
        self.editName = Entry(self, textvariable=self.strName)
        self.labName.grid(sticky=W, pady=4, padx=5)
        self.editName.grid(row=0, column=1, columnspan=4,padx=5, pady=2,sticky=E+W)

        # package name frame
        self.labPackage = Label(self, text="Package Name:")
        self.strPackage=StringVar()
        self.strPackage.set("com.MyCompany.AwesomeGame")
        self.editPackage = Entry(self, textvariable=self.strPackage)
        self.labPackage.grid(row=1, column=0,sticky=W, padx=5)
        self.editPackage.grid(row=1, column=1, columnspan=4,padx=5, pady=2,sticky=E+W)

        # project path frame
        self.labPath = Label(self, text="Project Path:")
        self.editPath = Entry(self)
        self.btnPath = Button(self, text="...", width = 6, command = self.pathCallback)
        self.labPath.grid(row=2, column=0,sticky=W, pady=4, padx=5)
        self.editPath.grid(row=2, column=1, columnspan=3,padx=5, pady=2, sticky=E+W)
        self.btnPath.grid(row=2, column=4,)

        # language frame
        self.labLanguage = Label(self, text="Language:")
        self.var=IntVar()
        self.var.set(1)
        self.checkcpp = Radiobutton(self, text="C++", variable=self.var, value=1)
        self.checklua = Radiobutton(self, text="Lua", variable=self.var, value=2)
        self.checkjs = Radiobutton(self, text="JavaScript", variable=self.var, value=3)
        self.labLanguage.grid(row=3, column=0,sticky=W, padx=5)
        self.checkcpp.grid(row=3, column=1,sticky=N+W)
        self.checklua.grid(row=3, column=2,padx=5,sticky=N+W)
        self.checkjs.grid(row=3, column=3,padx=5,sticky=N+W)

        # show progress
        self.progress = Scale(self, state= DISABLED, from_=0, to=100, orient=HORIZONTAL)
        self.progress.set(0)
        self.progress.grid(row=4, column=0, columnspan=5,padx=5, pady=2,sticky=E+W+S+N)

        # msg text frame
        self.text=Text(self,background = '#d9efff')
        self.text.bind("<KeyPress>", lambda e : "break")
        self.text.grid(row=5, column=0, columnspan=5, rowspan=1, padx=5, sticky=E+W+S+N)

        # new project button
        self.btnCreate = Button(self, text="create", command = self.createBtnCallback)
        self.btnCreate.grid(row=7, column=3, columnspan=1, rowspan=1,pady=2,ipadx=15,ipady =10, sticky=W)

        #center window on desktop
        curWidth = 500
        curHeight = 450
        scnWidth = self.parent.winfo_screenwidth()
        scnHeight = self.parent.winfo_screenheight()
        tmpcnf = '%dx%d+%d+%d'%(curWidth, curHeight, int((scnWidth-curWidth)/2), int((scnHeight-curHeight)/2))
        self.parent.geometry(tmpcnf)
        self.parent.title("Cocos2d Project Creator")

        #fix size
        #self.parent.maxsize(curWidth, curHeight)
        #self.parent.minsize(curWidth, curHeight)

        #redirect out to text
        self.pack(fill=BOTH, expand=1)
        sys.stdout = StdoutRedirector(self.text)

    def process_queue(self):
        """
        """
        #message is empty
        if self.queue.empty():
            self.parent.after(100, self.process_queue)
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
        self.parent.after(100, self.process_queue)

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
        self.queue = Queue()
        ThreadedTask(self.queue, projectName, packageName, language, projectPath).start()
        self.parent.after(100, self.process_queue)

    def pathCallback(self):
        """Paht button event.
        """
        filepath = askdirectory()
        if filepath:
            self.editPath.delete(0, END)
            self.editPath.insert(0, filepath)

def createTkCocosDialog():

    old_stdout = sys.stdout
    root = Tk()
    app = TkCocosDialog(root)
    root.mainloop()
    sys.stdout = old_stdout

if __name__ =='__main__':
    createTkCocosDialog()
