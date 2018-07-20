/*

    Towers of Hanoi
    ===============

    Print the moves required to transfer all disks from one tower to the other
    (using a third as auxiliary.)

*/

#include <iostream>

using namespace std;

/**
 * @param[in]  disks  Number of disks
 *
 * @param[in]  src    Source tower
 * @param[in]  dst    Destination tower
 * @param[in]  aux    Auxiliary tower
 */
void hanoi(int disks, char src, char dst, char aux) {

    // No disk to move
    if (!disks) {
        return;
    }

    // Move (n-1) disks from src to aux
    hanoi(disks-1, src, aux, dst);

    // Move the remaining 1 disk from src to dst
    cout << "Move disk from " << src << " to " << dst << endl;

    // Move back the disks from aux to dst
    hanoi(disks-1, aux, dst, src);

}


int main()
{

    // Let's begin
    hanoi(3, 'A', 'B', 'C');

    return 0;
}
