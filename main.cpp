#include "definitions.h"
#include "degree.h"
#include "dfsbfs.h"
#include "bridges_articulations.h"
#include "cliques.h"
#include "spanning.h"
#include "cut.h"

int main() {
    read_data();

//    degree();
//    count_components();
//    calculate_diameter();
//    find_cliques();
//    get_spanning_tree();
    find_bridges_and_articulations();
    find_cut();
}
