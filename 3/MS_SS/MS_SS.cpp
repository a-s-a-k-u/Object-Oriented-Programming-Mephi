
#include "MS_SS.h"

MissShotSaveShot::MissShotSaveShot() {
    MissedShots = 0;
    SavedShots = 0;
}

size_t MissShotSaveShot::GetMsSh() {
    return MissedShots;
}

size_t MissShotSaveShot::GetSvSh() {
    return SavedShots;
}
