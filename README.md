# SortedLinkedList
linked list that maintains a list of integers in sorted order

Input format: This program takes a file name as an argument from the command line. The file
is either blank or contains successive lines of input. Each line contains a character, either ‘i’ or
‘d’, followed by a tab character and then an integer. For each of the lines that starts with ‘i’, the
program should insert that number in the linked list in sorted order if it is not already there. The
program should not insert any duplicate values. If the line starts with a ‘d’, your program should
delete the value if it is present in the linked list. The program should silently ignore the line if the
requested value is not present in the linked list.
Output format: At the end of the execution, the program should print the number of nodes
in the list in the first line of the output and all the values of the linked list in sorted order in the
next line. The values should be in a single line separated by tabs. There should be no leading or
trailing white spaces in the output. The program should print “error” (and nothing else) if the
file does not exist. The program should print 0 followed by a blank line if the input file is empty
or the resulting linked list has no nodes.
