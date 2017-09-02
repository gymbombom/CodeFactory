#!/usr/bin/env python

#client--------------->server

import ftplib
from ftplib import FTP

#client variables
Client_Path = "/home/client/"
Client_File = "upload_file"

#server variables
Server_Address = "111.222.333.444"
Server_User = "user"
Server_Password = "password"
Server_Port = "21"

Server_Directory = "/home/server"


ftp = FTP()
ftp.connect(Server_Address, Server_Port)

ftp.login(Server_User, Server_Password)
file = open(Client_Path + Client_File, "rb")
ftp.cwd(Server_Directory)
ftp.storbinary('STOR ' + Client_File, file)
#ftp.storlines('STOR ' + Client_File, file)

print "STORing(binary mode) File now..."
ftp.quit()
file.close()
print "File transfered"
