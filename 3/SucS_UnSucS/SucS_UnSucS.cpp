
#include "SucS_UnSucS.h"

SuccesfulShootUnSuccessfulShoot::SuccesfulShootUnSuccessfulShoot() {
    SuccessfulShots = 0;
    UnsuccessfulShots = 0;
}

size_t SuccesfulShootUnSuccessfulShoot::GetSucSh() {
    return SuccessfulShots;
}

size_t SuccesfulShootUnSuccessfulShoot::GetUnSucSh() {
    return UnsuccessfulShots;
}

void SuccesfulShootUnSuccessfulShoot::SetSuccessful(size_t save) {
    SuccessfulShots = save;
}

void SuccesfulShootUnSuccessfulShoot::SetUnSuccessful(size_t unsave) {
    UnsuccessfulShots = unsave;
}

