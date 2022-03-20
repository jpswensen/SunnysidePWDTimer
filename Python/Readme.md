We can make a wholly contained exectuable using

pyinstaller --windowed --add-data "mainwindow.ui:." --add-data "commdialog.ui:." --add-data "editcompetitorsdialog.ui:."  pwdtimer.py

I'm not sure what --windowed does on a Windows machine. On a Mac it makes a .app file.
I do know that we can use --onefile instead of --windowed to make a single .exe file on Windows.
