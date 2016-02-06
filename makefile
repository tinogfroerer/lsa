objects = obj/lsamain.o obj/lsabase.o obj/lsaread.o obj/lsaprocess.o \
	obj/log2xorseq.o obj/lsaprint.o obj/lsaman.o

includes = inc/lsabase.h inc/lsaprint.h inc/lsaprocess.h \
	inc/lsaread.h  inc/lsaprocess.h inc/log2xorseq.h inc/lsaprint.h \
	inc/lsaman.h

CFLAGS += -I"./inc" -g -o

lsa : $(objects)
	cc -o lsa $(objects)

obj/lsamain.o : src/lsamain.c $(includes)
	cc -c src/lsamain.c $(CFLAGS) obj/lsamain.o

obj/lsabase.o : inc/lsabase.h src/lsabase.c
	cc -c src/lsabase.c $(CFLAGS) obj/lsabase.o

obj/lsaread.o : src/lsaread.c inc/lsaread.h inc/lsabase.h
	cc -c src/lsaread.c $(CFLAGS) obj/lsaread.o

obj/lsaprocess.o : src/lsaprocess.c inc/lsaprocess.h inc/lsabase.h
	cc -c src/lsaprocess.c $(CFLAGS) obj/lsaprocess.o

obj/log2xorseq.o : src/log2xorseq.c inc/log2xorseq.h
	cc -c src/log2xorseq.c $(CFLAGS) obj/log2xorseq.o

obj/lsaprint.o : src/lsaprint.c inc/lsaprint.h inc/lsabase.h
	cc -c src/lsaprint.c $(CFLAGS) obj/lsaprint.o

obj/lsaman.o : src/lsaman.c inc/lsaman.h
	cc -c src/lsaman.c $(CFLAGS) obj/lsaman.o

.PHONY : clean
clean :
	-rm lsa $(objects)
