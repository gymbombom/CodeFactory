#!/usr/bin/env python

#client<--------------server

import ftplib
from ftplib import FTP

#client variables
Client_Path = "/home/client/"


#server variables
Server_Address = "111.222.333.444"
Server_User = "user"
Server_Password = "password"
Server_Port = "21"

Server_Directory = "/home/server"
Server_File = "server_file"


ftp = FTP()
ftp.connect(Server_Address, Server_Port)

ftp.login(Server_User, Server_Password)
file = open(Client_Path + Server_File, "wb")
ftp.cwd(Server_Directory)
ftp.retrbinary("RETR " + Server_File, file.write)

print "RETRRing File now..."
ftp.quit()
file.close()
print "File transfered"
