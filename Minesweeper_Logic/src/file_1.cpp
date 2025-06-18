#include <iostream>
#include <vector>
#include<set>
#include <random>
#include <iomanip>
#include <queue>

// using namespace std;
#include <sstream>
#include<bitset>

using namespace std;

void bitsm() {

    int x = 6;
    int y = 4;
    cout << bitset<8>(x) << endl;
    cout << bitset<8>(y) << endl;
    cout <<(x ^ y) << endl;

    std::vector set = {0,1,2,3};
    int mask = 0;
    mask = mask | (1<<0);
    mask |= (1<<1);
    mask |= (1<<3);
    cout << mask << endl;
    /*
     * adding a bit implies taking mask = 0001
     *       and bit 3 we make (1<<3) = 1000;
     *       then mask | 1<<3 = 1001
     *
     * removing a bit say mask = 0101011
     *      removing bit 3 we make (1<<3) = 1000;
     *      then ~(1<<3) = ~~110111;
     *      then perform mask & ~(1<<3) = 1110011
     *
     * toggle an item say mask =    01010'1'10
     *      item 2 we make (1<<2) = ~~111100
     *      then we take mask ^ (1<<2) = 10101'0'10
     *      taking again mask ^ (1<<2)  =
     */

    for (int mas = 0; mas < (1<<5); ++mas) {
        cout << '{';
        for (int i=0; i<5; ++i) {
            if (mas & (1<<i)) {
                cout << i+1 << ' ';
            }
        }
        cout<<'}'<<endl;
    }

    int bitmask = 0;
    bitmask |= (1<<0);
    bitmask |= (1<<2);
    bitmask |= (1<<4);

    cout << bitset<8>(bitmask) << endl;

    bitmask ^= (1<<0); cout << bitset<8>(bitmask) << endl;

    bitmask ^= (1<<0); cout << bitset<8>(bitmask) << endl;

    bitmask ^= (1<<0); cout << bitset<8>(bitmask) << endl;

    bitmask ^= (1<<0); cout << bitset<8>(bitmask) << endl;

    if ( bitmask & (1<<4)) cout << "present" << endl;

    int read = 0, write = 1, execute = 2;

    int permission = 0;

    // permission |= (1<<read);
    // permission |= (1<<write);
    // permission |= (1<<execute);

    if (permission & 1<<read) cout << "read" << endl;
    else cout << "no read" << endl;
    if (permission & 1<<write) cout << "write" << endl;
    else cout << "no write" << endl;
    if (permission & 1<<execute) cout << "execute" << endl;
    else cout << "no execute" << endl;

}

class Solution {
    public:
    int maxDifference(std::string s, int k) {
        int ans=0;



        return ans;
    }
};






