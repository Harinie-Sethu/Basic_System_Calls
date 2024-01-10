# Basic_System_Calls
System calls related to file management and processes

## Part 1
__Task__  
Given a file, you need to reverse the contents of the file provided to you and store the result in a new file in directory named “Copies”.  

### Directory Structure
```
Part 1
├── Copies
│   └── newfile_reverse.txt
├── main.c
├── main.h
└── newfile.txt

```

### Input
Input will be the filename and it will be given from command line and not stdin.

### Note
"newfile.txt" is just taken as an example here. Filename can be anything (without white space characters). <br>
Test your program with files of size of at least a few GBs. It is expected to run in around a minute at most.

<br>
<br>

## Part 2
__Task__  
Given a string of both uppercase and lowercase Latin letters, write a program to print string in lowercase in the parent process and in uppercase in the child process.  

**Note** : Given string will only contain letters from Latin alphabet.  

### Directory Structure
```
Part 2
├── main.c
└── main.h

```

### Input
The string input will be given from command line and not from stdin.

### Note
Running program multiple times will print the output of two processes in seemingly random order, this is expected and not an error.

