#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket               # 导入 socket 模块

s = socket.socket()         # 创建 socket 对象
host = "0.0.0.0" # 获取本地主机名
port = 22222                # 设置端口
s.bind((host, port))        # 绑定端口

s.listen(5)                 # 等待客户端连接
while True:
    c, addr = s.accept()     # 建立客户端连接。
    print '连接地址：', addr
    c.send('hello world')
    c.close()                # 关闭连接
