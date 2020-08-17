logaloud
========

Watches the log and espeaks notable strings aloud.

Requires Qt 4.0 or higher.
Of course, <a href="http://espeak.sourceforge.net/">espeak</a> has to be installed.

Runs from a console. Like this:

    ./logalaout "ERROR" ~/some_project/log/error.log
  
And every time there is something like this added to the log,

    ERROR! Things have gone wrong!
  
It will run the espeak with the string so you'll hear _"ERROR! Things have gone wrong!"_ with your own ears.
