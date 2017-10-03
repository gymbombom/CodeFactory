# import
import sys
import os
import telnetlib
import socket
import getopt

class Telnet(telnetlib.Telnet):
    def __init__(self, host=None, port=0, timeout=10):
        telnetlib.Telnet.__init__(self)
        if host is not None:
            self.open(host, port, timeout)
    def open(self, host, port=0, timeout=10):
        self.eof = 0
        if not port:
            port = telnetlib.TELNET_PORT
        self.host = host
        self.port = port
        msg = "getaddrinfo returns an empty list"

        if self.sock:
            self.sock.close()
        for res in socket.getaddrinfo(host, port, 0, socket.SOCK_STREAM):
            af, socktype, proto, canonname, sa = res
            try:
                self.sock = socket.socket(af, socktype, proto)
                self.sock.settimeout(timeout)
                self.sock.connect(sa)
            except socket.error:
                if self.sock:
                    self.sock.close()
                self.sock = None
                continue
            break

        if not self.sock:
            #raise socket.error, msg
            return None
