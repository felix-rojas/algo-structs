#include <iostream>
#include <vector>

long binary_search(std::vector < long >
const &arr,
long lo,
long hi,
long max_water
) {
long res = -1;
while (lo <= hi) {
// find the midpoint
long mid = lo + (hi - lo) / 2;
// calculate how many water blocks there are
// height - coral_height = water_blocks
long water_accum = 0;
for (
long coral_height
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
    unsigned int test_cases;
    long coral_cols, max_water;
    std::cin >> test_cases;
    std::cout << "Test cases: " << test_cases << std::endl;
    for (unsigned int i = 0; i < test_cases; i++) {
        std::cin >> coral_cols;
        std::cin >> max_water;
        std::cout << "Max water blocks: " << max_water << std::endl;
        std::vector<long> corals;
        corals.reserve(coral_cols);
        long tallest_coral = 0;
        long area_sum = 0;
        std::cout << "Reserved " << coral_cols << " spaces\n";
        for (long j = 0; j < coral_cols; j++) {
            long temp = 0;
            std::cin >> temp;
            area_sum += temp;
            corals.push_back(temp);
            if (tallest_coral <= temp) { tallest_coral = temp; }
        }
        std::cout << "Current vector: ";
        for (auto coral: corals) {
            std::cout << coral << " ";
        }
        std::cout << std::endl;
        // data has been saved
        long low = 1;
        long high = static_cast<long>(1e10 - 1);
        long water_blocks_under_tallest_coral = (coral_cols * tallest_coral) - area_sum;
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
        long result = binary_search(corals, low, high, max_water);
        std::cout << "-------------" << std::endl;
        std::cout << "RESULT is: " << result << std::endl;
        std::cout << "-------------" << std::endl;
        // we found the closest midpoint
    }
}