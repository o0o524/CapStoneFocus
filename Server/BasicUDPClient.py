#
# BasicUDPClient.py
# 20131187 권용일
#

import time
from datetime import datetime
from socket import *

serverName = '165.194.17.28'
serverPort = 31187

clientSocket = socket(AF_INET, SOCK_DGRAM)

# Show information about message and reply time to client
def response_print(send_time):
    modified_message, server_address = clientSocket.recvfrom(2048)
    resp_time = datetime.now()
    print('Reply from server:', modified_message.decode())
    print('Response time : ', (resp_time - send_time).microseconds / 1000,'ms')


# Menu
while 1:
    print('<Menu>')
    print('1) convert text to UPPER-case')
    print('2) convert text to LOWER-case')
    print('3) get my IP address and port number')
    print('4) get server time')
    print('5) exit')
    try:
        menu_num = input('Input option : ')
    # Process KeyboardInterrupt while waiting menu's number
    except KeyboardInterrupt:
        print('\n'
              'Bye bye~')
        clientSocket.close()
        break
    if menu_num == '1':
        clientSocket.sendto(menu_num.encode(), (serverName, serverPort))
        try:
            message = input('Input sentence: ')
        # Process KeyboardInterrupt while waiting input string
        except KeyboardInterrupt:
            print('\n'
                  'Bye bye~')
            clientSocket.sendto(''.encode(), (serverName, serverPort))
            clientSocket.close()
            break
        clientSocket.sendto(message.encode(), (serverName, serverPort))
        response_print(datetime.now())
    elif menu_num == '2':
        clientSocket.sendto(menu_num.encode(), (serverName, serverPort))
        try:
            message = input('Input sentence: ')
        # Process KeyboardInterrupt while waiting input string
        except KeyboardInterrupt:
            print('\n'
                  'Bye bye~')
            clientSocket.sendto(''.encode(), (serverName, serverPort))
            clientSocket.close()
            break
        clientSocket.sendto(message.encode(), (serverName, serverPort))
        response_print(datetime.now())
    elif menu_num == '3':
        clientSocket.sendto(menu_num.encode(), (serverName, serverPort))
        response_print(datetime.now())
    elif menu_num == '4':
        clientSocket.sendto(menu_num.encode(), (serverName, serverPort))
        response_print(datetime.now())
    elif menu_num == '5':
        print('Bye bye~')
        clientSocket.close()
        break
    else:
        print('One more check your input')
