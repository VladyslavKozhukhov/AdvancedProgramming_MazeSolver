
#include "AlgorithmRegistration.h"


AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
    MatchManager::getInstance()->addAlgorithm(algorithm);
}