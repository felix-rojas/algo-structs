#include <iostream>
#include <vector>
typedef long long ll;

long binary_search(std::vector < ll >
const &arr,
ll lo,
ll hi,
ll max_water
) {
ll res = -1;
while (lo <= hi) {
// find the midpoint
ll mid = lo + (hi - lo) / 2;
// calculate how many water blocks there are
// height - coral_height = water_blocks
ll water_accum = 0;
for (
ll coral_height
: arr) {
// coral height must be less than the mid-height
// because if it is higher, there is no area for water to add
if (coral_height<mid)
water_accum += (mid - coral_height);
}
// if it just so happens that the sum if equal
if (water_accum == max_water) return
mid;
// now we have two cases
// there's more accumulated water than the given max
if (water_accum<max_water) {
// move the lower limit up by a half
res = mid;
lo = mid + 1;
}
// there's less accumulated water than the given max
else {
// move the upper limit down to a half
hi = mid - 1;
}}
return
res;
}

int main() {
    ll test_cases;
    ll coral_cols, max_water;
    std::cin >> test_cases;
    for (ll i = 0; i < test_cases; i++) {
        std::cin >> coral_cols;
        std::cin >> max_water;
        std::vector<ll> corals;
        corals.reserve(coral_cols);
        ll tallest_coral = 0;
        ll area_sum = 0;
        for (ll j = 0; j < coral_cols; j++) {
            ll temp = 0;
            std::cin >> temp;
            area_sum += temp;
            corals.push_back(temp);
            if (tallest_coral <= temp) { tallest_coral = temp; }
        }
        ll low = 1;
        ll high = 1e10 - 1;
        ll water_blocks_under_tallest_coral = (coral_cols * tallest_coral) - area_sum;
        // more area under the tallest coral means our hi
        // is actually the tallest coral
        if (water_blocks_under_tallest_coral > max_water) {
            high = tallest_coral;
        }
        // less area under the tallest coral means our lo
        // is the tallest coral
        if (water_blocks_under_tallest_coral < max_water) {
            low = tallest_coral;
        }
        if (coral_cols != 1){
            std::cout << binary_search(corals, low, high, max_water) << std::endl;
        } else {
            std::cout << tallest_coral + max_water << std::endl;
        }
    }
}