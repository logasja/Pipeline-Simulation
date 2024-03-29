#ifndef _BPRED_H_
#define _BPRED_H_
#include <inttypes.h>
#include <map>



static inline uint32_t SatIncrement(uint32_t x, uint32_t max)
{
    if(x < max)
        return x+1;
    return x;
}

static inline uint32_t SatDecrement(uint32_t x)
{
    if(x > 0)
        return x-1;
    return x;
}

typedef enum BPRED_TYPE_ENUM {
    BPRED_PERFECT=0,
    BPRED_ALWAYS_TAKEN=1,
    BPRED_GSHARE=2,
    NUM_BPRED_TYPE=3
} BPRED_TYPE;

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

class BPRED{
    BPRED_TYPE policy;

    public:
    uint64_t stat_num_branches;
    uint64_t stat_num_mispred;
    //   Global history register
    uint16_t ghr;
    //   Pattern History Table
    std::map<uint16_t, uint8_t> pht;

    // The interface to the three functions below CAN NOT be changed
    BPRED(uint32_t policy);
    bool GetPrediction(uint32_t PC);
    void UpdatePredictor(uint32_t PC, bool resolveDir, bool predDir);
    uint16_t PCxorGHR(uint32_t PC);
    void UpdateGHR(bool resolveDir);
    uint8_t GetPHTEntry(uint16_t hsh);
    void UpdatePHTEntry(uint16_t hsh, bool resolveDir);
};

/***********************************************************/
#endif

