#!/usr/bin/env python3
# Multithread ESP32 Communication - Server


''' Enzo Zavorski Delevatti
||| @Zvorky                   
\\\          ___,             
 \\\      .~´    `-,          
  \\°    /  _    _ \.         
   \°   ,\`|_|''|_|´\         
    °    /          /)   °    
        (\  ,    , .\`   |°   
         `) ;`,; `,^,)   ||°  
         ´,´  `,  `  `   |||  
                          \\\ 
        September 2025     |||
                           '''


import time, threading, socket
from utils import *


HOST = ''
UDP_PORT = 1337
TCP_PORT = 4269
TCP_CONNECTIONS = 3
BUFSIZE = 1024
TIMEOUT = 1.0

ACTIVE = False
EXIT = 'SHUTDOWN'


def udp_loop(udp_socket):
    udp_socket.bind((HOST, UDP_PORT))
    udp_socket.settimeout(TIMEOUT)

    log(f'UDP server listening on port {UDP_PORT}', 'UDP')

    while ACTIVE:
        try:
            data, client = udp_socket.recvfrom(BUFSIZE)
            message = data.decode('utf-8')
            log(f'UDP message from {client}: {message}', 'UDP')
            # TODO: Implement processing
            response = f'ACK: {message}'
            udp_socket.sendto(response.encode('utf-8'), client)
        except socket.timeout:
            continue
        except Exception as e:
            log(f'UDP error: {e}', 'ERROR')

    udp_socket.close()
    log('UDP server stopped.', 'UDP')


def tcp_loop(tcp_socket):
    tcp_socket.bind((HOST, TCP_PORT))
    tcp_socket.settimeout(TIMEOUT)
    tcp_socket.listen(TCP_CONNECTIONS)

    log(f'TCP server listening on port {TCP_PORT}', 'TCP')

    while ACTIVE:
        try:
            connection, client = tcp_socket.accept()
            log(f'TCP connection established by {client}', 'TCP')
            data = connection.recv(BUFSIZE)
            message = data.decode('utf-8')
            log(f'TCP message from {client}: {message}', 'TCP')
            # TODO: Implement processing
            response = f'ACK: {message}'
            tcp_socket.sendto(response.encode('utf-8'), client)
            connection.close()
            log(f'TCP connection {client} closed.', 'TCP')
        except socket.timeout:
            continue
        except Exception as e:
            log(f'TCP error: {e}', 'ERROR')

    tcp_socket.close()
    log('TCP server stopped.', 'TCP')


if __name__ == '__main__':
    clear()
    log('Multithread ESP32 Communication - Server', 'MAIN')
    log('By Enzo Zavorski Delevatti (@Zvorky)', 'MAIN')
    print(f'\n→ Type "{EXIT}" to stop the server.\n')
    time.sleep(3)

    log('Initializing server...', 'MAIN')
    ACTIVE = True
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    udp_thread = threading.Thread(target=udp_loop, args=(udp_socket,))
    tcp_thread = threading.Thread(target=tcp_loop, args=(tcp_socket,))

    udp_thread.start()
    tcp_thread.start()

    x = ''
    while x.upper() != f"{EXIT}".upper():
        x = input()

    log('Shutting down server...', 'MAIN')
    ACTIVE = False