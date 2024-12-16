# Compiler ve flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Çıktı dosyası
TARGET = game

# Kaynak dosyalar ve header dosyalar
SRCS = main.c player.c creature.c item.c room.c
OBJS = $(SRCS:.c=.o)
HEADERS = creature.h room.h item.h player.h game.exe

# Varsayılan hedef
all: $(TARGET)

# Çalıştırılabilir dosyayı oluştur
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Her bir .c dosyasını .o dosyasına derle
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Oyunu çalıştır
run: $(TARGET)
	./$(TARGET)

# Temizlik işlemi
clean:
	rm -f $(TARGET) $(OBJS)

# Debug için derleme
debug: CFLAGS += -g
debug: clean all

.PHONY: all clean run debug
