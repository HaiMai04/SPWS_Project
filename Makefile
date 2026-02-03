CC = gcc
CFLAGS = -Wall -I.
OBJ = main.o spws_controller.o hal_sensors.o hal_actuators.o hal_buttons.o

TARGET = spws_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)