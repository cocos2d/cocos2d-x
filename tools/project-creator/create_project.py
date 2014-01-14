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

import sys
def commandCreate():
        from module.core import CocosProject
        project = CocosProject()
        name, package, language, path = project.checkParams()
        project.createPlatformProjects(name, package, language, path)


# ------------ main --------------
if __name__ == '__main__':
    """
    There have double ways to create cocos project.
    1.UI
    2.console
        #create_project.py --help
        #create_project.py -n MyGame -k com.MyCompany.AwesomeGame -l javascript -p c:/mycompany
    """
    if len(sys.argv)==1:
        try:
            from module.ui import createTkCocosDialog
            createTkCocosDialog()
        except ImportError:
            commandCreate()
    else:
        commandCreate()


