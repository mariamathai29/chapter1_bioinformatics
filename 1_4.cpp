#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <limits>

std::vector<int> minimum_skew(const std::string& genome) {
    int skew = 0;
    int min_skew = 0;
    std::vector<int> min_positions;

    // Initialize a map to track positions of each skew value
    std::unordered_map<int, std::vector<int>> skew_positions;
    skew_positions[0].push_back(0); // Start with position 0 having skew of 0

    // Iterate through the genome
    for (size_t i = 0; i < genome.length(); ++i) {
        if (genome[i] == 'G') {
            skew += 1;
        } else if (genome[i] == 'C') {
            skew -= 1;
        }

        // Store the current position in the map for this skew value
        skew_positions[skew].push_back(i + 1); // +1 for 1-indexing

        // Update the minimum skew and positions
        if (skew < min_skew) {
            min_skew = skew;
            min_positions = {static_cast<int>(i + 1)}; // +1 for 1-indexing
        } else if (skew == min_skew) {
            min_positions.push_back(i + 1); // +1 for 1-indexing
        }
    }

    return min_positions;
}

int main() {
    std::string genome;

    // Example input
    std::cout << "Enter genome: ";
    std::getline(std::cin, genome);

    std::vector<int> positions = minimum_skew(genome);
    
    // Print the results
    std::cout << "Positions of minimum skew: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    return 0;
}
