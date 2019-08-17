//
// Created by VladKo on 4/25/2019.
//

#ifndef MAZESOLVER_ALGORITHMREGISTRATION_H
#define MAZESOLVER_ALGORITHMREGISTRATION_H
#pragma once

#include <functional>
#include <memory>
#include "AbstractAlgorithm.h"
#include "MatchManager.h"

class AlgorithmRegistration {
public:
    AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()>);
};

#define REGISTER_ALGORITHM(class_name) \
AlgorithmRegistration register_me_##class_name \
	([]{return std::make_unique<class_name>();} );

#endif //MAZESOLVER_ALGORITHMREGISTRATION_H
