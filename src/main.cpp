// #include "../include/Vessel.h"
//
// int main() {
//     Vessel<int> v("Circadian Rhythm");
//
//     const auto A = v.add("A", 3);
//     const auto R = v.add("R", 5);
//     const auto C = v.add("C", 5);
//     const auto DR = v.add("DR", 1);
//     const auto MR = v.add("MR", 0);
//
//     // Create reactions using the updated syntax
//     v.add(DR >> 1 >>= MR);          // DR reacts with rate 5 to produce MR and DR
//     v.add((A + R) >> 1 >>= C);           // A and R react with rate 3 to produce C
//
//     // Print items and reactions
//     v.printItems();
//     v.beginSimulation(1000);
//
//
//     return 0;
// }