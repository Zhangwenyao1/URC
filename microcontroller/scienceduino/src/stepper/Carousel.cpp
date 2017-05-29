//
// Created by matthew on 28/05/17.
//

#include "Carousel.h"
#include <A4988.h>

Carousel::Carousel(A4988 motor): motor(motor) {
    this->aligned = true; // Assume we are aligned at the base = true setpoint (0)
    this->index = 0;
    this->base = true;
    this->reverseDirection = 0;
    this->stepsSinceConfirm = 0;

}
