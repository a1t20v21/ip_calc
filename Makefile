TARGET: ipcalcexe
	
test_ipcalc.o: test_ipcalc.c
	gcc -g -c -I . test_ipcalc.c -o test_ipcalc.o

ipcalc.o: ipcalc.c
	gcc -g -c -I . ipcalc.c -o ipcalc.o

libipcalc.a: ipcalc.o
	ar rs libipcalc.a ipcalc.o

ipcalcexe: libipcalc.a test_ipcalc.o
	gcc -g -I . test_ipcalc.o -o ipcalcexe -L . libipcalc.a

clean:
	rm ipcalcexe
	rm libipcalc.a
	rm test_ipcalc.o
	rm ipcalc.o
