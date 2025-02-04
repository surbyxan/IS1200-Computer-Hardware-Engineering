you need to have mcb32 toolchain installed
	if not go to this link and download and install:
			http://github.com/is1200-example-projects/mcb32tools/releases/

else open MSYS or a terminal window
	for windows and linux write:

		. /opt/mcb32tools/environment

Navigate to the directory where the project is located, using cd commands.
connect the CHIPkit to your computer with the USB cord
the type:

make

make install TTYDEV=/dev/ttySX 

where X are the chosen USB port. if you dont know witch one, try the numbers 1-4
