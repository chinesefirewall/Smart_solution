#!/usr/bin/python
import socket
import sys
import argparse


parser = argparse.ArgumentParser(description="Sending message to random server", formatter_class = RawTextHelpFormatter)
parser.add_argument("-hst", "--host", help="Host to which to connect")
parser.add_argument("-p", "--port", help="Port lol", type=int)
args = parser.parse_args()
HOST = args.host
PORT = args.port
