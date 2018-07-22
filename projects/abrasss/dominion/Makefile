CFLAGS = -Wall -fpic -coverage -lm

unittestresults.out: clean unittests cardtests
	@echo "Results for Assignment3 unit testing:" > tests.out
	
	@echo "unittest1:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./unittest1 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out
	
	@echo "unittest2:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./unittest2 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out
	
	@echo "unittest3:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./unittest3 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out
	
	@echo "unittest4:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./unittest4 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out
	
	@echo "cardtest1:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./cardtest1 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out
	
	@echo "cardtest2:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./cardtest2 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out
	
	@echo "cardtest3:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./cardtest3 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out
	
	@echo "cardtest4:" | tee -a tests.out
	@/bin/rm -f dominion.gcda
	@ ./cardtest4 | tee -a tests.out
	@gcov dominion.c | tee -a tests.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

unittests: unittest1 unittest2 unittest3 unittest4

cardtest1: dominion.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

cardtests: cardtest1 cardtest2 cardtest3 cardtest4

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest[1234] cardtest[1234] unittestresults.out
