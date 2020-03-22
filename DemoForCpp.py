#!/usr/bin/python
#coding:utf-8

import time

def run(name):
 print("Hi,"+name+".")
 print("It is "+time.strftime("%Y-%m-%d %X", time.localtime())+".")
   
def main():
 run("Kevin")
    
if __name__=='__main__':
 main()