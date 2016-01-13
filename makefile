CC=clang++
OUT_EXE=test_mtg
CFLAGS=-m32

$OUT_EXE:app.o mtgsdk.o
	$(CC) -o $(OUT_EXE) $(CFLAGS) app.o mtgsdk.o -lpthread -ldl -L. -lavnMtgLib

app.o:app.cpp
	$(CC) -c $(CFLAGS) app.cpp

mtgsdk.o:mtgsdk.h mtgsdk.cpp
	$(CC) -c $(CFLAGS) mtgsdk.cpp

.PHONY:
clean:
	rm -rf app.o mtgsdk.o $(OUT_EXE) 
