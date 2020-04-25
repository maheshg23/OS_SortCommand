# Operating System (OS-6233) NYU Spring 2020 

In this assignment, you’ll start getting familiar with xv6 by writing a couple simple programs that run in the xv6 OS.
As a prerequisite, make sure that you have followed the install instructions from NYU Classes to get your build
environment set up.
A common theme of the homework assignments is that we’ll start off with xv6, and then add something or modify it
in some way. This assignment is no exception. Start by getting a copy of xv6 using git (commands typed at the
terminal, and their output, will be shown using a monospace font; the commands type will be indicated by a $):

`$ git clone https://github.com/moyix/xv6-public.git`  
`$ cd xv6-public`  
`$ make`  
Then, to run it inside of QEMU, you can do:  
`$ make qemu-nox`  
QEMU should appear and show the xv6 command prompt, where you can run programs inside xv6.  

## Hello Command 
Write a program for xv6 that, when run, prints ”Hello world” to the xv6 console. This can be broken up into a few
steps:
1. Create a file in the xv6 directory named hello.c
2. Put code you need to implement printing ”Hello world” into hello.c
3. Edit the file Makefile.
4. Run make to build xv6, including your new program (repeating steps 2 and 4 until you have compiling code)
5. Run make qemu to launch xv6, and then type hello in the QEMU window. You should see ”Hello world” be
printed out

## Sort Command

sort is used to sort a file, arranging the records in a particular order. By default, the sort command sorts file assuming
the contents are ASCII. Using options in sort command, it can also be used to sort numerically. If a filename is
provided on the command line (i.e., sort FILE) then sort should open it, read, sort, print sorted lines in this file, and
then close it. If no filename is provided, sort should read from standard input.

## Extending sort 

The traditional UNIX sort utility can do lots of things, such as:
• -r: Sorting in reverse order
• -o: Write the output to a new file
• -n: To sort a file numerically
Here, we are going to implement these three behaviors in your version of sort. The expected output of these
commands should be:

`$ sort -r example.txt`


