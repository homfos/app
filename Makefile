DST := server
SRC := tcpservselect01.c error.c wraplib.c wrapsock.c wrapunix.c writen.c

$(DST) : $(SRC)
	$(CC) -g -o $@ $^

clean:
	$(RM) *.o $(DST)
