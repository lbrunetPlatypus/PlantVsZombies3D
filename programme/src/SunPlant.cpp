#include "SunPlant.h"

SunPlant::SunPlant(): Plant() {

}

SunPlant::SunPlant(int cooldown) : Plant(cooldown) {

}

SunPlant::SunPlant(int cooldown, int hp) : Plant(cooldown,hp) {

}

void SunPlant::produceSun() {

}