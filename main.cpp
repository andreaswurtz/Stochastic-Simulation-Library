#include "Vessel.h"

int main() {
    Vessel<int> v("Circadian Rhythm");

    const auto A = v.add("A", 0);
    const auto R = v.add("R", 0);
    const auto C = v.add("C", 0);

    // Example reaction (extend operator overloading for full functionality)
    const auto reaction = A + R;

    v.printItems();

    return 0;
}