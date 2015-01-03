def main():
	origin=raw_input("Please input CMD: ")
	hex_store=0
	for item in origin.split(' '):
		hex_store=int(item,16)+hex_store
		print hex(int(item,16))[2:]
	last_two_digi=int(format(hex_store,'02x')[-2:],16)
	checksum=0xff-last_two_digi
	print "Checksum is: "
	print hex(checksum)


while (1):
	main()
