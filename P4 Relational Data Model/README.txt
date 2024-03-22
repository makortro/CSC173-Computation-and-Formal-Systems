Project 4 - Relational Data Model
MaKayla Robinson
mrobin45


I didn’t collaborate with anyone on this project.


Use the following commands…
“make” to compile
“make clean” will clear the .o files if you need to run again
“./auto” will load program


The program will load the database, print each tuple, then display part 1 (a-e) of the project prompts. Everything is working properly besides my delete functions. For some reason they won’t delete every specified item from the tuple.


Part 2 is broken up into two parts, each in a REPL; (a) is What grade did [name] get in [course]? and will prompt you to enter a student’s name, then a course (separately). When entering names, please don’t use a space after the period. [e.g. do M.Smith, don’t do M. Smith] The results will print similarly to the tuples from the beginning. If the tuple is blank, then the student is not in the specified class; it doesn’t print a message. After the results are printed if you want to test another student type “Y”, or “N” to move on.


Part 2b Where is [name] at [hour] on [day]? isn’t working properly; the result doesn’t print the correct day/time/room. I programmed it to print if the student isn’t in the specified class, but I’m not sure if it’s working correctly either. After the results are printed if you want to test another student type “Y”, or “N” to exit the program.


During input on part 2, please only enter values from the tuples (case sensitive). I didn’t add print statements to catch errors assuming you would follow the given data.


I didn’t make it to part 3.