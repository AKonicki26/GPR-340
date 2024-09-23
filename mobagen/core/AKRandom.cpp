//
// Created by anne.konicki on 9/16/2024.
//

#include "AKRandom.h"

#include <iostream>
#include <random>

namespace ak {
    Random::Random() {
        std::random_device rd;
        std::uniform_int_distribution<int> distribution(0, std::numeric_limits<int>::max());

        mSeeds[0] = distribution(rd);
        mSeeds[1] = distribution(rd);

        mOriginalSeeds[0] = mSeeds[0];
        mOriginalSeeds[1] = mSeeds[1];

        mMax = std::numeric_limits<int>::max();
        mMin = 0;
    }

    // uses xorshoftr+ to generate numbers
    int Random::nextInt() {
        int x = mSeeds[0];
        int const y = mSeeds[1];

        mSeeds[0] = y;
        x ^= x << 23;
        x ^= x >> 17;
        x ^= y;
        x = clampToBounds(x);
        mSeeds[1] = x + y;
        return x;
    }

    void Random::setBounds(int min, int max) {
        if (min > max) {
            std:: cout << "ERROR: Minimum cannot be greater than Maximum.\nValues are unchanged";
            return;
        }
        mMin = min;
        mMax = max;
    }

    int Random::clampToBounds(int value) {
        return mMin + (value % (mMax - mMin + 1));
    }
} // ak

