#!/usr/bin/env python

# demonstrate coroutines in Python 

"""
+  implements a typical producer/consumer algorithm 
+  the consumer is a subroutine and main() is the producer
+  producer sends a job request to consumer; waits for consumer to receive it
+  the consumer waits for job request, does job, waits again
+  keywords: 
+  yield waits on producer - passes argument to producer at handoff
+  next() sends job to consumer w/o msg
+  send() sends job to consumer with msg 
"""

import sys

def printjob(name):              
   sys.stdout.write(f'{name} ')

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

   # as long as something is in the jobs list keep processing requests
   while jobs:
      i = (i + 1) % len(jobs)
      # yield passes control back to producer with the ith job name
      getRequest = yield jobs[i]    # waits for request from producer

      if getRequest:    # if getRequest is not empty process it
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
   con = consumer(jobs)                   # start the consumer 

   for i in range(len(jobs)): 
      printjob(con.__next__())         # next sends job to consumer w/ no msg 

   printjob(con.send(("add", "iron", 44)))  # send sends job to consumer w/ msg
   sys.stdout.write("\n")
   for i in range(len(jobs)): 
      printjob(con.__next__())                             

   con.send(("remove","iron", 44))         
   for i in range(len(jobs)): 
      printjob(con.__next__())

   print ("\nProducer Done." )

"""
+ MAIN 
"""
if __name__ == "__main__":             # this means initialize once only

   jobs = [("wash",11),("dry",22),("fold",33)]  # mutable list

   producer(jobs)