# Team04_MicrobeControllers
### man
Use to get the help manual for different commands with format: ``` man command```
### who
Lists all of the system user variables.  
Use ```who -u``` to determine the username
### whoami
Displays the current user
### hostname
Use ```hostname --short``` to display short hostname
Use ```hostname -i``` to display the IP address
### pwd
Print the current working directory
### uptime
Displays the amount of time the Pi has been on
### python
Use ```python --version``` to determine python version
### ping
Use ```ping url``` to ping a website
### whereis
Use to display the location of a command, such as ```whereis man```
### which
Locates a command on the disk
### cat
Opens a short text file, example: ```cat /proc/cpuinfo```
### raspistill
Controls the raspberry's camera
### crontab
Used to schedule the firig of commands perodically
http://kvz.io/blog/2007/07/29/schedule-tasks-on-linux-using-crontab/
### top
displays currently active commands and their resource usage

### Restart and Shutdown
sudo restart
sudo shutdown
---------------------------------------------------------------------------------------------------------
# Lab 2 Notes
### echo
Prints what was written in the command line after submission

### cat
prints out contents of file as well as concatinates files, strings, variables, etc

### wc
Prints out total number of words (-w) or total number of characters in bites (-c)

### >
creates new file or rewrites selected file
e.g. echo "Hello world!" > hi.txt

### >>
Creates file from echo if file does not yet exist, appends if file exists

### ls la
gives file infromation in bites

### head and tail
prints either the first 10 or last line 10, respectively, of a file
#### -[1-10]
prints the 1st, 2nd, 3rd...10th line of head or last
-1 = first line, -3 = third lien

### more
prints contents of file to fill screen and allows for scrolling to additional lines of the file using the arrow keys

### |
suppresses data stream (does not print to screen) but allows functions to act on the stream.
Example: more hi.txt | grep hi  returns all instances containing the characters "hi"

### grep
find

### n
prints line number

###
