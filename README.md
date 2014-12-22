regex_test
==========

Test POSIX regular expressions - simple C commandline tester
Written 2014 by Paul H Alfille

Do you want to test the rather archane regex routines separately from your program? This program allows you to do that without much fuss. 

It compiles easily:

gcc -o regex_test regex_test.c
chmod +x regex_test  # only the first time
./regex_test

The program only uses input from the command line, and runs in a loop until you Control-C:

paul@linux-an2t:~/regex_test> ./regex_test 

----------------------
Hello World!
0    X    1    X    2    X    3    X    4    X    5    X    6    X    7    X    8    X    
0:      0 -> 12  <Hello World!>

Choosse:
1. Regex : <.*>
2. String: <Hello World!>
3. Mode  :  Extended 
1
New regular expression: l([^l]+)l

----------------------
Hello World!
0    X    1    X    2    X    3    X    4    X    5    X    6    X    7    X    8    X    
0:      3 -> 10  <lo Worl>
1:      4 -> 9  <o Wor>

Choosse:
1. Regex : <l([^l]+)l>
2. String: <Hello World!>
3. Mode  :  Extended 
