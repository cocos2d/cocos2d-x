#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import ftplib

class Upload(object):
    HOST = "127.0.0.1"

    def upload(self, path, workdir, ip = None, fileName = None):
        if ip is None:
            ip = Upload.HOST
        try:
            f = ftplib.FTP(ip)
        except:
            raise Exception('ERROR:cannot reach " %s"' % ip)

        try:  
            f.login()
        except ftplib.error_perm:
            f.quit()
            raise Exception('ERROR: cannot login anonymously')

        try:
            f.mkd(workdir)
        except Exception, e:
            print(e)
            pass

        try:
            f.cwd(workdir)
        except Exception, e:
            print(e)
            pass

        try:
            print("to delete file (%s) if exist" % os.path.basename(path))
            f.delete(os.path.basename(path))
        except Exception, e:
            print(e)
            pass

        try:
            #传一个回调函数给retrbinary() 它在每接收一个二进制数据时都会被调用
            print("Upload file (%s) ......" % os.path.basename(path))
            if fileName is None:
                fileName = os.path.basename(path)
            f.storbinary('STOR ' + fileName, open(path, 'rb'))
        except Exception, e:
            print(e)
            pass

        f.quit()
        print("Upload file (%s) success" % path)


    def uploadFolder(self, path, workdir, ip = None):
        if ip is None:
            ip = Upload.HOST
        try:
            f = ftplib.FTP(ip)
        except:
            raise Exception('ERROR:cannot reach " %s"' % ip)

        try:  
            f.login()
        except ftplib.error_perm:
            f.quit()
            raise Exception('ERROR: cannot login anonymously')

        try:
            try:
                f.rmd(workdir)
            except Exception, e:
                pass

            listName = workdir.split('/')
            newpath = ''
            for name in listName:
                if 0 == cmp(name, ".") or 0 == cmp(name, ".."):
                    continue
                newpath = os.path.join(newpath, name)
                try:
                    f.mkd(newpath)
                except Exception, e:
                    pass
        except Exception, e:
            print(e)
            pass

        try:
            f.cwd(workdir)
        except Exception, e:
            print(e)
            pass

        try:
            for fileName in os.listdir(path):
                newFile = os.path.join(path, fileName)
                if os.path.isdir(newFile):
                    self.uploadFolder(newFile, os.path.join(workdir, fileName))
                elif 0 != cmp(".", fileName[0:1]) :
                    f.storbinary('STOR ' + fileName, open(os.path.join(path, fileName), 'rb'))
        except Exception, e:
            print(e)
            pass

        f.quit()
        print("Upload folder (%s) success" % path)

    def removeFolder(self, workdir, ip = None):
        if ip is None:
            ip = Upload.HOST
        try:
            f = ftplib.FTP(ip)
        except:
            raise Exception('ERROR:cannot reach " %s"' % ip)

        try:  
            f.login()
        except ftplib.error_perm:
            f.quit()
            raise Exception('ERROR: cannot login anonymously')

        try:
            f.rmd(workdir)
        except Exception, e:
            print(e)
            pass

        f.quit()
        print("remove folder (%s) success" % workdir)
