# Morgue-Application-QT ![alt text](https://github.com/StefanCsPurge/Morgue-Application-QT/blob/master/happySkull.png)
A complete QT GUI application for managing the victims of a morgue.


The application can be used in two modes: EC-PD morgue admin (mode A) and EC-PD morgue assistant (mode B). When the program is started, it will offer the option to choose the mode.

EC-PD morgue administrator mode: 

The program has a database, which lists victim files stored in the morgue's backroom cabinets. The guys in the forensics department must be able to update the database, meaning: add a new victim file (you grit your teeth at the prospect), delete a victim file (in the event that a file is proven to be unconnected to the Slayer's rampage or is moved to another department for research) and update the information of a victim file. Each victim file has a name, a place of origin, an age and a photograph taken post-autopsy. The EC-PD administrators will also have the option to see all victim files that have been stored.

EC-PD morgue assistant mode: 

An assistant can access the program and choose one or more victim files to mark as unconnected to the string of murders or to move to other departments for research, in the event of new findings. The program allows the assistant to:

1. See the victim files in the database, one by one. When the assistant chooses this option, the data of the first victim (place of origin, name, age) is displayed, along with its post-autopsy photograph.
2. Choose to transfer the file to another department, in which case the victim file is added to the assistant's “to be transferred” list.
3. Choose not to transfer the victim file and to continue to the next. In this case, the information corresponding to the next victim file is shown and the assistant is again offered the possibility to transfer it. This can continue as long as the assistant wants, as when arriving to the end of the list, if the assistant chooses next, the application will again show the first victim file.
4. See all victim files of a given place of origin, having an age less than a given number. If the place of origin is empty, then all victim files will be considered. The same options (a, b and c) apply in this case.
5. See the list of victim files selected to be removed as irrelevant or transferred to other departments for additional research.

![alt text](https://github.com/StefanCsPurge/Morgue-Application-QT/blob/master/commands.png)
