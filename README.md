LAllarme
========

This is an alarm/stopwatch easy-to-use software.<br/>
I develop it in C++ with Qt Library when I have free time.

You can download the project and compile it yourself and then use it, but I didn't upload binaries yet.

Presentation
============

This application is an alarm :
 - Choose the time and start the timer, you will be warned when the time will be up.
 - The title is updated to display the remaining time, allow you to minimize the window.
 - You can pause/resume it.

It's a stopwatch too :
 - Click on Start button.
 - Adding a note will add the current time to the text edit.
 - You can pause/resume it.

And a useless clock :D :
Tools --> Hour...

I don't think I need help for development. But if you have any (good ?) ideas, contact me : ds.la.lun@gmail.com.

Compilation
===========

You might have Qt SDK installed - I personnally use the 4.8.4 version.<br/>
Then, just open LAllarme.pro with Qt Creator and build !<br />
It needs those dynamic libraries to be executed :
 - libgcc_s_dw2-1.dll
 - mingwm10.dll
 - release : QtCore4.dll || debug : QtCored4.dll
 - release : QtGui4.dll || debug : QtGuid4.dll

Notes
=====

The last version is 1.5 beta (I didn't built any alpha version yet).

Sometimes, the encodage made me crazy.<br/>
This version has been coded on Windows 7 and you might use ``QString::fromAscii()`` or ``QString::fromUtf8()``
for each sentence which contains non-english characters (i.e : accents) if you have some mistakes.

French is the original language, but I translated it in english.<br/>
And as you can see, I haven't got a good english and it would be great if someone would do the english translations.

Language selection in Options doesn't work yet.
