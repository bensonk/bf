#!/usr/bin/env python

def bf(s):
  print s
  for c in s:
    print '+' * ord(c) + '.' + '>'
  print


if __name__ == "__main__":
  from sys import argv
  for arg in argv[1:]:
    bf(arg)
