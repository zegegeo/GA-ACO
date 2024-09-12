//
// Created by Lwz on 2024/9/12.
//

#include "Population.h"
#include <iostream>
#include "mechanism.h"

Population::Population(int populationSize, int chromosomeSize){

    individuals.resize(populationSize,Individual(chromosomeSize));

}

void Population::initializePopulation() {

        for(auto& ind:individuals){
            ind.initialize();
        }

}

const std::vector<Individual> &Population::getIndividuals() const {

    return individuals;

}

void Population::setIndividual(int index, const Individual& individual) {

    if(index>=0&&index<individuals.size()){
        individuals[index]=individual;
    }
    else{
        std::cerr<<"Index out of range!"<<std::endl;
    }
}

const Individual& Population::getIndividual(int index) const {

    return individuals[index];

}

int Population::getPopulationSize() const {

    return individuals.size();

}

void Population::evaluate() {

    for(auto& ind:individuals){

        double fitness=evaluateFitness(ind);
        ind.setFitness(fitness);

    }
}

void Population::printPopulation() const {
    for (int i = 0; i < getPopulationSize(); ++i) {
        const Individual& individual = getIndividual(i);
        std::cout << "Genes: ";
        for (int gene : individual.getGenes()) {
            std::cout << gene << " ";
        }
        std::cout << "| Fitness: " << individual.getFitness() << std::endl;
    }
}

const Individual& Population::getBestIndividual() const {
    double bestFitness = std::numeric_limits<double>::lowest();
    const Individual* bestIndividual = nullptr;
    for (const auto& individual : individuals) {
        if (individual.getFitness() > bestFitness) {
            bestFitness = individual.getFitness();
            bestIndividual = &individual;
        }
    }
    return *bestIndividual;
}