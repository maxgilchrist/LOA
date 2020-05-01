CC	= gcc-9
CCFLAGS = -mavx 
TARGETS = PerformanceTest
OBJECTS = test.o 4x4Naive.o 4x4Check.o 8x8Naive.o 8x8Check.o
PerformanceTest : $(OBJECTS)
	@$(CC) -w -o $(TARGETS) $(OBJECTS) 
	@echo "Build Successful"
	@rm -f $(OBJECTS)
	@echo "Cleaned up"
test.o : test.c 
	@$(CC) -w -c test.c
	@echo "Compiled test.c"
4x4Naive.o : 4x4Naive.c
	@$(CC) -w -c 4x4Naive.c
	@echo "Compiled 4x4Naive.c"
4x4Check.o : 4x4Check.c 
	@$(CC) -w -c 4x4Check.c
	@echo "Compiled 4x4Check.c"
8x8Naive.o : 8x8Naive.c 
	@$(CC) -w -c 8x8Naive.c
	@echo "Compiled 8x8Naive.c"
8x8Check.o : 8x8Check.c 
	@$(CC) -w $(CCFLAGS) -c 8x8Check.c
	@echo "Compiled 8x8Check.c"
.PHONY : clean verbose
verbose:
	$(CC) -o $(TARGETS) $(OBJECTS)
clean :
	@rm -f $(TARGETS) $(OBJECTS)
	@echo "Manual clean successful"
