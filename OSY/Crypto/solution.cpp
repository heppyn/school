#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <pthread.h>
#include <semaphore.h>
#include <cstdint>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>
using namespace std;


class CFITCoin;
class CCVUTCoin;
class CCustomer;

typedef struct shared_ptr<CFITCoin> AFITCoin;
typedef struct shared_ptr<CCVUTCoin> ACVUTCoin;
typedef struct shared_ptr<CCustomer> ACustomer;
//=================================================================================================

class CFITCoin {
public:

    CFITCoin(const vector<uint32_t> & vectors, int distMax)
    : m_Vectors(vectors)
    , m_DistMax(distMax)
    , m_Count(0) 
    {
    }
    virtual ~CFITCoin(void) = default;
    vector<uint32_t> m_Vectors;
    int m_DistMax;
    /* determines work thread */
    uint64_t m_Count;
};
//=================================================================================================

class CCVUTCoin {
public:

    CCVUTCoin(const vector<uint8_t> & data, int distMin, int distMax)
    : m_Data(data)
    , m_DistMin(distMin)
    , m_DistMax(distMax)
    , m_Count(0) 
    {
    }
    virtual ~CCVUTCoin(void) = default;
    vector<uint8_t> m_Data;
    int m_DistMin;
    int m_DistMax;
    uint64_t m_Count;
};
//=================================================================================================

class CCustomer {
public:
    virtual ~CCustomer(void) = default;
    virtual AFITCoin FITCoinGen(void) = 0;
    virtual ACVUTCoin CVUTCoinGen(void) = 0;

    virtual void FITCoinAccept(AFITCoin x) = 0;
    virtual void CVUTCoinAccept(ACVUTCoin x) = 0;
};
//=================================================================================================
#endif /* __PROGTEST__ */

class CRig {
public:
    static void Solve(ACVUTCoin x) {}
    static void Solve(AFITCoin x) {}

    CRig(void) {}
    ~CRig(void) {}
    void Start(int thrCnt) {}
    void Stop(void) {}
    void AddCustomer(ACustomer c) {}
    uint64_t Shrink (uint64_t x, uint64_t mask) {
        uint64_t ret = 0;
        int cnt = 0;
        while (mask) {
            if (!(mask & 1)) {
                mask = mask >> 1;
                x = x >> 1;
                continue;
            }
            else {
                ret = ret | ( (x & 1) << cnt++);
                mask = mask >> 1;
                x = x >> 1;
            }
        }
        return ret;
    }
//private:
    int BitCompare (uint64_t x, uint64_t y, int num) {
        int cnt = 0;
        for (int i = 0; i < num; ++i) {
            if (((x >> i) & 1) == ((y >> i) & 1))
                ++cnt;
        }
        return cnt;
    }
    uint64_t SameBits (AFITCoin x) {
        x.operator *().m_DistMax;
    }
};

#ifndef __PROGTEST__
#include "test.inc"

#endif /* __PROGTEST__ */