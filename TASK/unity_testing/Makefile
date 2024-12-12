CC = gcc
CFLAGS = -I./ -I./Unity/src -Wall -g  # Include debugging flag (-g) and warnings (-Wall)

# Your source file
SOURCE = dhosa.c
TEST_SOURCE = test_dhosa.c

# Executable name
TARGET = test_dhosa

all: $(TARGET)

$(TARGET): $(SOURCE) $(TEST_SOURCE) Unity/src/unity.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

