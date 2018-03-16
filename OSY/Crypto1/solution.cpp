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
    static void Solve(ACVUTCoin x) {
        /* convert to bit field */
        vector<bool> sequence;
        for (uint8_t vec : x->m_Data) {
            uint8_t cur = vec;
            for (int i = 0; i < 8; ++i) {
                sequence.push_back(cur & 1);
                cur >>= 1;
            }
        }


    }
    static void Solve(AFITCoin x) {

        uint32_t mask = SameBits(x);
        uint64_t count = 0;

        if (!mask) {
            for (int k = 0; k <= x.operator*().m_DistMax; ++k) {
                count += Com(32, k);
            }
            x.operator*().m_Count = count;
            return;
        }
        int numOfDiffBits = NumOfOnes(mask);
        int numOfVec = 0;
        vector<uint32_t> numbers;
        for (uint32_t v : x.operator*().m_Vectors) {
            numbers.push_back(Shrink(v, mask));
        }

        for (int i = 0; i < numOfDiffBits; ++i) {
            numOfVec = numOfVec << 1;
            ++numOfVec;
        }

//        cout << hex << "mask:" << mask << endl;
//        cout << dec << "numOfDiffBits: " << numOfDiffBits
//             << " numOfVec: " << numOfVec << endl;

        for (int i = 0; i <= numOfVec; ++i) {
            int dist = 0;
            for (uint32_t v : numbers) {
                int d = NumberOfDifferentBits(v, i, numOfDiffBits);
                if (d > dist)
                    dist = d;
            }
            if (dist > x.operator*().m_DistMax)
                continue;
            for (int k = 0, n = 32 - numOfDiffBits; k <= x.operator*().m_DistMax - dist; ++k) {
                count += Com(n, k);
            }
        }
        x.operator*().m_Count = count;
    }

    CRig(void) {}
    ~CRig(void) {}
    void Start(int thrCnt) {}
    void Stop(void) {}
    void AddCustomer(ACustomer c) {}
    static uint32_t Shrink (uint32_t x, uint32_t mask) {
        uint32_t ret = 0;
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
    static int NumberOfDifferentBits(uint32_t x, uint32_t y, int num) {
        int cnt = 0;
        for (int i = 0; i < num; ++i) {
            if (((x >> i) & 1) == ((y >> i) & 1))
                ++cnt;
        }
        return cnt;
    }
    static uint32_t SameBits (AFITCoin x) {
        /* returns mask with same bits = 0, different bits = 1 */
        uint32_t mask = 0;
        uint32_t bit;
        for (int i = 0; i < 32; ++i ) {
            bit = static_cast<uint32_t>(1 << i);
            uint32_t same = bit;
            for (size_t j = 0; j < x.operator*().m_Vectors.size() - 1; ++j) {
                if ((x.operator*().m_Vectors[j] & bit) != (x.operator*().m_Vectors[j + 1] & bit)) {
                    same = 0;
                    break;
                }
            }
            mask = mask | same;
        }
        return ~mask;
    }
    static int NumOfOnes (uint32_t x) {
        int sum = 0;
        while (x) {
            if (x & 1) {
                ++sum;
            }
            x = x >> 1;
        }
        return sum;
    }
    static uint64_t Com( int n, int k ) {
        if (k > n) return 0;
        if (k * 2 > n) k = n-k;
        if (k == 0) return 1;

        uint64_t res = n;
        for ( int i = 2; i <= k; ++i ) {
            res *= (n-i+1);
            res /= i;
        }
        return res;
    }
};

#ifndef __PROGTEST__
#include "test.inc"

#endif /* __PROGTEST__ */