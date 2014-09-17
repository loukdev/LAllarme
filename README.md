LAllarme
========

This is an alarm/stopwatch easy-to-use software.<br/>
I develop it in C++ with Qt Library when I have free time.

You can download the project and compile it yourself and then use it, but binaries are not ready yet.

Presentation
============

This application is an alarm :
 - Choose the time and start the timer, you will be warned when the time is up.
 - The title is updated to display the remaining time, allowing you to minimize the window.
 - You can pause and resume it.

A stopwatch :
 - Click on Start button.
 - Adding a note will add the current time to the text edit.
 - You can pause and resume it.

And a useless clock :
Tools --> Hour...

I don't think I need help for development. But if you have any (good ?) ideas, contact me : louk.dev@gmail.com.

Compilation
===========

You must have Qt SDK installed - I use the 4.8.4 version.<br/>
Then, just open LAllarme.pro with Qt Creator and build !<br />
It needs those dynamic libraries to be executed :
 - libgcc_s_dw2-1.dll
 - mingwm10.dll
 - release : QtCore4.dll || debug : QtCored4.dll
 - release : QtGui4.dll || debug : QtGuid4.dll

Notes
=====

The last version is 1.5 beta (no alpha version built yet).

Sometimes, the encodage made me crazy.<br/>
This version has been coded on Windows 7 (I hadn't my Linux computer with me) and you should use ``QString::fromAscii()`` or ``QString::fromUtf8()``
on each sentence containing non-english characters (like accents) if you have some mistakes.

The original language is french and I (badly) translated it in english.<br/>
And as you can see, I haven't got a nice english and it would be great if someone could improve english translations.

Language selection in Options doesn't work yet (I don't master translations with Qt for the moment).
