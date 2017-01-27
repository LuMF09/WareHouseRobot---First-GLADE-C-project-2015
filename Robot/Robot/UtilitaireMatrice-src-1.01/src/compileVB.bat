set DIR=E:\/GTK_install\/


set INCLUDES=-I. -I X:\/MinGW\/include -I %DIR%\/GTK\/include\/gtk-2.0 -I %DIR%\/GTK\/include\/glib-2.0 -I %DIR%\/GTK\/lib\/glib-2.0\/include -I %DIR%\/GTK\/include\/cairo\/ -I %DIR%\/GTK\/include\/pango-1.0\/ -I %DIR%\/GTK\/lib\/gtk-2.0\/include -I %DIR%\/GTK\/include\/gdk-pixbuf-2.0 -I %DIR%\/GTK\/include\/atk-1.0



set LIBS=-L %DIR%\/GTK\/lib -l glib-2.0 -l gio-2.0 -l cairo -l atk-1.0 -l gdk-win32-2.0 -l gdk_pixbuf-2.0 -l gthread-2.0 -l gtk-win32-2.0 -l libpng -l pango-1.0 -l pangocairo-1.0 -l pangowin32-1.0 -l gmodule-2.0 -l gailutil -l freetype -l fontconfig -l expat -l gobject-2.0 -l gmodule-2.0



gcc -Wall main.c callbacks.c presentation.c modele.c controle.c matrice.c -mms-bitfields %INCLUDES% %LIBS% -o matrice.glade.exe

