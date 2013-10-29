#------------------------------------------------
#           Monkeyrunner Test Report
#                         10/08/2012
#------------------------------------------------

from email.MIMEBase import MIMEBase
from email.MIMEText import MIMEText
from email.MIMEMultipart import MIMEMultipart
from email.utils import COMMASPACE,formatdate
from email import Encoders
from email.header import Header  
import smtplib,email,os,sys

if os.path.exists(os.getcwd()+'\\monkeyrunner_Error.log') or os.path.exists(os.getcwd()+'/monkeyrunner_Error.log'):
    print "Sending Monkeyrunner Test Report..."
    mail_from = 'redmine@cocos2d-x.org' #where the mail from
    mail_to  = ['739657621@qq.com','yangguangzaidongji@hotmail.com','yangguangzaidongji@gmail.com']
    to_string =''
    for item in mail_to:
        to_string += item +','
    mail_subject = "Monkeyrunner Test Report"
    msg = MIMEMultipart()
    #msg = MIMEText('body')
    mail_attachment = 'monkeyrunner_Error.log'
    #msg = "\nhell"
    print mail_to

    username = 'redmine@cocos2d-x.org'
    password = 'cocos2d-x.org'
    msg["From"] = mail_from
    msg["To"] = to_string
    msg["Subject"] = mail_subject
    msg["Date"] = formatdate(localtime=True)
    mail_body = "Monkeyrunner Test Finish! See attachment for logs."
    msg.attach(MIMEText(mail_body))

    #Add attachment.
    fp = open(mail_attachment,"rb")
    part = MIMEBase("application", "octet-stream")
    part.set_payload(fp.read())
    fp.close()
    Encoders.encode_base64(part)
    part.add_header("Content-Disposition", "attachment; filename=%s" % mail_attachment)
    msg.attach(part)
	 
    #Send email. 
    server = smtplib.SMTP('smtp.gmail.com:587')
    server.starttls()
    server.login(username,password)
    server.sendmail(mail_from, mail_to, msg.as_string())
    print 'Eamil success!'
    server.quit()
