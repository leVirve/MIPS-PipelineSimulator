#include "Stage.h"

#include "WriteBackStage.h"
#include "MemoryAccessStage.h"
#include "ExecuteStage.h"
#include "DecodeStage.h"
#include "FetchStage.h"

Stage* Stage::StageWriteBack = NULL;
Stage* Stage::StageMemoryAccess = NULL;
Stage* Stage::StageExecute = NULL;
Stage* Stage::StageDecode = NULL;
Stage* Stage::StageFetch = NULL;

Stage* Stage::GetStage(StageId id)
{
    switch (id) {
#define CASE(X)	\
        case X: \
                if (Stage ## X == NULL) Stage ## X = new X ## Stage; \
        return Stage ## X
        CASE(WriteBack);
        CASE(MemoryAccess);
        CASE(Execute);
        CASE(Decode);
        CASE(Fetch);
#undef CASE

        default:
        return 0;
    }
}
