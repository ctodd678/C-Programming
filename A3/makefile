objects = frequency_table decode copyrecords
all: $(objects)

$(objects): %: %.c
				$(CC) $(CFLAGS) -o $@ $<
