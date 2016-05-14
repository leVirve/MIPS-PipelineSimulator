TARGET= pipeline
OBJ= pipeline.o simulator.o Memory.o Stage.o RegisterFile.o WriteBackStage.o MemoryAccessStage.o ExecuteStage.o DecodeStage.o FetchStage.o

$(TARGET):$(OBJ)
	g++ -o $(TARGET) $(OBJ) -DDEBUG

simulator.o: ./src/simulator.cpp ./src/Memory.cpp ./src/Stage.h ./src/Register.h ./src/RegisterFile.h
	g++ -c ./src/simulator.cpp

Stage.o: ./src/Stage.cpp
	g++ -c ./src/Stage.cpp

pipeline.o: ./src/pipeline.cpp
	g++ -c ./src/pipeline.cpp

WriteBackStage.o: ./src/WriteBackStage.cpp
	g++ -c ./src/WriteBackStage.cpp

MemoryAccessStage.o: ./src/MemoryAccessStage.cpp
	g++ -c ./src/MemoryAccessStage.cpp

ExecuteStage.o: ./src/ExecuteStage.cpp
	g++ -c ./src/ExecuteStage.cpp

Memory.o: ./src/Memory.cpp
	g++ -c ./src/Memory.cpp

DecodeStage.o: ./src/DecodeStage.cpp
	g++ -c ./src/DecodeStage.cpp

FetchStage.o: ./src/FetchStage.cpp
	g++ -c ./src/FetchStage.cpp

RegisterFile.o: ./src/RegisterFile.cpp
	g++ -c ./src/RegisterFile.cpp

Register.o: ./src/Register.cpp
	g++ -c ./src/Register.cpp

clean:
	rm -f *.o $(TARGET)
