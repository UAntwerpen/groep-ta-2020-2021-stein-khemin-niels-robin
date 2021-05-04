// de lib file zal constanten, enums, ... bevatten

#ifndef TA_LIB_H
#define TA_LIB_H

#define GENOME_SIZE 390624
#define POPULATION_SIZE 100
#define PARALLELISM_ENABLED true
#define GENERATION_LIMIT 2500

enum EDirections: char{noord, oost, zuid, west};
enum EStates: char{EVegetation, ERoad, EResidentialZone, EIndustrialZone, EStoreZone};

#endif //TA_LIB_H
