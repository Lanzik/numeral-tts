CC = gcc
CFLAGS = -Wall -Wextra
OBJS = audio_files.o num2voice.o
n2l = num2let.o
TARGET = program
TARGET2 = num2letter

all: $(TARGET) $(TARGET2)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	
$(TARGET2): $(n2l)
	$(CC) $(CFLAGS) $(n2l) -o $(TARGET2)

audio_files.o: audio_files.c audio_files.h
	$(CC) $(CFLAGS) -c audio_files.c

num2voice.o: num2voice.c audio_files.h
	$(CC) $(CFLAGS) -c num2voice.c
	
num2let.o: num2let.c
	$(CC) $(CFLAGS) -c num2let.c

clean:
	rm -f $(OBJS) $(n2l) $(TARGET) $(TARGET2)
