objects = obj/lsamain.o obj/lsabase.o obj/lsaread.o
includes = inc/lsabase.h inc/lsaprint.h inc/lsaprocess.h inc/lsaread.h

lsa : $(objects)
	cc -o lsa $(objects)

obj/lsamain.o : lsamain.c $(includes)
	cc -c lsamain.c && mv lsamain.o obj

obj/lsabase.o : inc/lsabase.h lsabase.c
	cc -c lsabase.c && mv lsabase.o obj

obj/lsaread.o : lsaread.c inc/lsaread.h inc/lsabase.h
	cc -c lsaread.c && mv lsaread.o obj

