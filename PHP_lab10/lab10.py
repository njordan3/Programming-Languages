#!/usr/bin/env python
"""
CMPS 3500 Lab 10

Altered By: Nicholas Jordan
Date: 11/17/2020

Execute with:

     ./lab10.py lab10.data <integer>

lab10.data is structured like this:

      3
      11
      15
      20
      0
      17
"""

import sys
from sys import argv

"""  
my_map takes a function and a list, and returns the result of the
function applied to the every element in the list; e.g.,

    my_map(lambda x: x + 1, [1, 2, 3]) 

returns [2, 3, 4]
"""

def my_mean(func, list):
  sum = 0
  count = 0
  for item in list:
    if (func(item)):
      sum += item
      count += 1
  return sum/count

def my_filter(func, list):
  new_list = []
  for item in list:
    if (func(item)):
      new_list.append(item)
  return new_list

def my_map(func, list):
  new_list = []
  for item in list:
    new_list.append(func(item))
  return new_list

def printjob(job):              
   sys.stdout.write(f'{job} ')

"""
+  CONSUMER 
+  'yield stuff' passes stuff back to the producer; when control resumes a 
+  message (it may be empty) is available from the producer as the return 
+  value from yield; note: cannot remove everything from the list since
+  the dereference to jobs[i] in yield is invalid
"""
def consumer(jobs):
   print("Consumer Starting")

   i = -1 
   while jobs:
      i = (i + 1) % len(jobs)
      getRequest = yield jobs[i]
      if getRequest:
          request, name, num = getRequest
          if request == "add":
              jobs.append((name, num))
              sys.stdout.write("\nADD ") 
          elif request == "remove" and (name,num) in jobs:
              jobs.remove((name, num))
              buf = "\nREMOVE " + name + "\n"
              sys.stdout.write(buf)

   print ("\nNo jobs left to do!\n")

"""
+ acts as the producer coroutine
+ next passes a job to the consumer with no message passing
+ send passes a job to the consumer with a message 
"""
def producer(jobs):
   print("Producer Starting")
   con = consumer(jobs)                           # start the consumer 

   for i in range(len(jobs)): 
      printjob(con.__next__())                    # next sends job to consumer w/ no msg 

   printjob(con.send(("add", "iron", 44)))        # send sends job to consumer w/ msg
   sys.stdout.write("\n")
   for i in range(len(jobs)): 
      printjob(con.__next__())                             

   con.send(("remove","iron", 44))         
   for i in range(len(jobs)): 
      printjob(con.__next__())

   print ("\nProducer Done." )

if len(argv) < 3:
  print("Usage: %s <filename> <integer> " % argv[0])
else:
  values = []
  n = int(argv[2])
  input = open(argv[1], 'r')
  for line in input:
     values.append(int(line))
  input.close()

  print('Part I:')
  print(f'Data from file: {values}') 
  print('==========[my_map]==========')
  squared = my_map(lambda x: x * x, values)
  print(f'Data from file squared: {squared}')
  successor = my_map(lambda x: x + 1, values)
  print(f'Data from file + 1: {successor}')
  print('==========[my_mean]=========')
  mean = my_mean(lambda x: x >= 0, values)
  print(f'Data from file averaged: {round(mean, 2)}')
  mean = my_mean(lambda x: x > 11, values)
  print(f'Data from file > 11 averaged: {round(mean, 2)}')
  print('==========[my_filter]==========')
  filtered = my_filter(lambda x: x % 2, values)
  print(f'Data from file filtered odd: {filtered}')
  filtered = my_filter(lambda x: x > 0 and x < 20, values)
  print(f'Data from file filtered > 0 and < 20: {filtered}')
  
  print('\nPart II:')
  print(f'Command line arg: {n}')
  jobs = [("wash",11+n),("dry",22+n),("fold",33+n)]
  producer(jobs)
