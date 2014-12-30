
#include <vector>
#include <tuple>
#include <rlglue/utils/C/RLStruct_util.h>

typedef std::pair<double, double> coord;

coord getMario(const observation_t obs);

std::vector<coord> getMonsters(const observation_t obs);
