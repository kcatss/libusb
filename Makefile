libusb : libusb.c
	gcc -o libusb libusb.c -lusb-1.0 -L /usr/lib/x86_64-linux-gnu/
clean:
	rm libusb
