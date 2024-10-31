//
// Created by anne.konicki on 10/31/2024.
//

#ifndef WAVEFUNCTIONGENERATOR_H
#define WAVEFUNCTIONGENERATOR_H
#include "../GeneratorBase.h"

#include <unordered_set>

enum TileState : unsigned int {
  NONE = 0,
};

class WaveFunctionGenerator : public ScenarioGeneratorBase {
public:
  std::vector<Color32> Generate(int sideSize, float displacement) override;
  std::string GetName() override;
};

struct Tile {
  TileState state = TileState::NONE;
};





#endif //WAVEFUNCTIONGENERATOR_H
