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
quites output of wget
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
