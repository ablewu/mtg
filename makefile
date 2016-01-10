CC=/home/muti/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-g++
OUT_EXE=test_mtg

$OUT_EXE:app.o mtgsdk.o
	$(CC) -o $(OUT_EXE) app.o mtgsdk.o -lpthread -ldl

app.o:app.cpp
	$(CC) -c app.cpp

mtgsdk.o:mtgsdk.h mtgsdk.cpp
	$(CC) -c mtgsdk.cpp

.PHONY:
clean:
	rm -rf app.o mtgsdk.o $(OUT_EXE) 
