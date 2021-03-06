# Team04_MicrobeControllers
# Brian Landry, Felix Ekness

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
sudo shutdown -r now -> restarts
sudo shutdown now -> shutsdown pi
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
### ls -la
gives file infromation in bites, prints hidden files/non text files
### head and tail
prints either the first 10 or last line 10, respectively, of a file
-[1-10] prints the 1st, 2nd, 3rd...10th line of head or last
-1 = first line, -3 = third lien
### more
prints contents of file to fill screen and allows for scrolling to additional lines of the file using the arrow keys
### |
suppresses data stream (does not print to screen) but allows functions to act on the stream.
Example: more hi.txt | grep hi  returns all instances containing the characters "hi"
### grep
find
### -n
prints line number
### wget
access a website
#### -q
quietes output of wget
#### -qO-
prevents from saving to a disk
### tee
Outputs standard output and writes result to a file
e.g. ifconfi | cat -n | grep "inet addr" | tee specific_line_in_ifconfi.txt
### cp
Copies from a file to a new file
e.g. cp hi.txt new_file.txt
### id -u
Prints user specific information
### nano
onboard text editor
### raspistill
activates camera
-o output filename
-v verbose output: gives you detailed information on photo captured
### opt-get
the downloader or package manager for linux
### fbi
image viewer
e.g. fbi smile.jpg
-a autozoom
-d framebuffer of device
-vf vertical flip
-hf horizontal flip
-v be verbose, status line on bottom of prompt
-noverbose
-t time in secomds (e.g. -t 1 equates to a picture per second slide show on repeat)
### raspivid
takes video with camera
-o specifies output file
### omxplayer
video player
-o specifies out type (e.g. hdmi)
### 2>&1
pipes standard error (stderr) to standards output (stdout)  

------------------------------------------------------------------------------------------------------------
# Lab 3
### CHMOD
```
CHMOD +x filename
````
Use this command to make a file execuable

### grep

global regular expression print

Searchs an input file for a string and prints lines which match it
````
grep string filepath
````

-n Shows line numbers  
-v Gives negative results instead of positive results  
-vn Gives negative results and line numbers  
-c only prints number of lines matched  
-l only prints filesnames of files which contain the string  
-i ignores case when searching  
-x Searchs for exact matches only
-A# Display additional lines following the line in which the match was made

####REGEXP
You can include regular expressions in your grep queries  
-E also use of extended regexp commands  
$ is end of line  
? matchs 1 or 0 occurences of the previous character  
| seperates two search strings with or functionality, eg. string1|string2  
\ escapes a special character allowing it to be searched for. Use 'single quotes' when using this character.

###AWK
A text pattern scanning and processing language. read here fo rmore info http://www-users.york.ac.uk/~mijp1/teaching/2nd_year_Comp_Lab/guides/grep_awk_sed.pdf
````
BEGIN { b &. initialization awk commands b &}
{ b &. awk commands for each line of the fileb &}
END { b &. finalization awk commands b &}
````
Example which prints every third file using a for loop and getline to iterate  
````
ls -l | awk '{for (i=1;i<3;i++) {getline}; print NR,$0}'
````
Uses the following control statements:
-  if (condition) statement [ else statement ]
-  while (condition) statement
-  do statement while (condition)
-  for (expr1; expr2; expr3) statement
-  for (var in array) statement
-  break
-  continue
-  exit [ expression ]
-  
Example, find PMIDs from PubMed records:
````
awk '{if($1=="PMID-"){print $2}}' tsien.txt > tsien_PMIDs.txt
````
---------------------------------------------------------------------------------------------------------
# Lab 4 notes
### passwd
changes password for pi - must first renter old password then will take new password
### id
lists all user id's in the following form:  
uid=1000(pi) gid=1000(pi) groups=1000(pi)...  
uid = user id in integer with actual text in paretheses  
gid = group id
### apropos
searchers all manuel pages (grep for man)  
example: apropos user -> finds all man pages (liens of pages) with the word user in them
### addgroup
requires root, adds user to specified group  
addgroup <group name>
### adduser
requires root, adds new user  
adduser <user> <group name>  
note: to update user info, need to type $exit and then login to newly created user
### userdel
requires root, deletes a user  
userdel <user name>
### killall
force quits all processes of given name or all except killall  
example: killall python -> kills all python instances
## Python codes
### #! /usr/bin/python
added to the top of a python script, will idicate to the bash interpreter where to find the python interpreter to run the python script
### chmod +x python-dot.py
will make python-dot.py executable by the bash terminal  
e.g. ./python-dot.py
### Python: import re
use re to search for strings of given length:  
e.g. re.search(r".....", string1) will evaluate as either true or false for if string1 is of length 5 (true) or not (false)
### Python: import sys
sys.argv -> takes all options passed to the bash interpreter and stores them in a list  
e.g. $python ./python-dot.py 'hello world!!'  
with the python-dot.py containing the following lines:  

    sys.argv 
    print(arg)

will print ['./python-dot.py', 'hellow world!!']
# End of python codes
### crontab
type the following into the crontab -e file  
    * * * * *  command to execute
exicutes the command at m h  dom mon dow   command
### scp
copies files between hosts on a network. It uses ssh(1) for data transfer, and uses the same authentication and provides the same security as ssh(1)  
e.g. scp file user@IPaddress[directory]
