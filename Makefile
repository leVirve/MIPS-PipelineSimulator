TARGET= pipeline
OBJ= pipeline.o simulator.o Memory.o Stage.o RegisterFile.o WriteBackStage.o MemoryAccessStage.o ExecuteStage.o DecodeStage.o FetchStage.o

$(TARGET):$(OBJ)
	g++ -o $(TARGET) $(OBJ) -DDEBUG

simulator.o: simulator.cpp Memory.cpp Stage.h Register.h RegisterFile.h
	g++ -c simulator.cpp

Stage.o: Stage.cpp
	g++ -c Stage.cpp

pipeline.o: pipeline.cpp
	g++ -c pipeline.cpp

WriteBackStage.o: WriteBackStage.cpp
	g++ -c WriteBackStage.cpp

MemoryAccessStage.o: MemoryAccessStage.cpp
	g++ -c MemoryAccessStage.cpp

ExecuteStage.o: ExecuteStage.cpp
	g++ -c ExecuteStage.cpp	

Memory.o: Memory.cpp
	g++ -c Memory.cpp

DecodeStage.o: DecodeStage.cpp
	g++ -c DecodeStage.cpp

FetchStage.o: FetchStage.cpp
	g++ -c FetchStage.cpp

RegisterFile.o: RegisterFile.cpp
	g++ -c RegisterFile.cpp

Register.o: Register.cpp
	g++ -c Register.cpp

clean:
	rm -f *.o $(TARGET)
