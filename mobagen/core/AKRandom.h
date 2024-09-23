//
// Created by anne.konicki on 9/16/2024.
//

#ifndef RANDOM_H
#define RANDOM_H
#include <limits>


namespace ak {

class AKRandom {
public:
    AKRandom(int seedX, int seedY) : mSeeds(seedX, seedY), mOriginalSeeds(seedX, seedY),
        mMin(0), mMax(std::numeric_limits<int>::max()){}
    AKRandom();
    int nextInt();
    void setBounds(int min, int max);

    int* getOriginalSeeds() { return mOriginalSeeds; }

private:
    int clampToBounds(int value);
    int mMin, mMax;
    int mSeeds[2];
    int mOriginalSeeds[2];
};

} // ak

#endif //RANDOM_H
