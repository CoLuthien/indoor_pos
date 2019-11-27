CC = gcc 
CFLAGS = -Wall


SYS_LIBS = -lbluetooth -lpthread -lm

build_dir = build
include_path = -I include -I lib -I include/test
src_dir = src

srcv = ble.c comm.c node_ctl.c position.c ble_filter.c

srcs = $(foreach src, $(srcv), $(src_dir)/$(src))

objs = $(foreach src, $(srcv), $(src:.c=.o))

target = position


$(target): $(objs) list.o ./src/main.c
	$(CC) $(include_path) -o $(target) $(CFLAGS) $^ $(SYS_LIBS) 


list.o:	./lib/list.c 
	$(CC) $(CFLAGS) -I lib -c $^


ble.o: ./src/ble.c ./src/node_ctl.c ./src/ble_filter.c
	$(CC) $(CFLAGS) $(include_path) -c $^ $(SYS_LIBS)

comm.o: ./src/comm.c 
	$(CC) $(CFLAGS) $(include_path) -c $^

position.o: ./src/ble.c ./src/comm.c ./src/node_ctl.c ./src/position.c  ./list.o
	$(CC) $(CFLAGS) $(include_path) -c $^ $(SYS_LIBS)

ble_filter.o : ./src/ble_filter.c 
	$(CC) $(CFLAGS) $(include_path) -c $^ $(SYS_LIBS)





