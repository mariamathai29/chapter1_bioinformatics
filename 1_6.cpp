#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// Forward declaration of the helper function
void generate_neighbors(const std::string& pattern, size_t index, int current_distance, int max_distance, std::unordered_set<std::string>& neighbors_set);

std::unordered_set<std::string> neighbors(const std::string& s, int d) {
    std::unordered_set<std::string> neighbors_set;
    generate_neighbors(s, 0, 0, d, neighbors_set);
    return neighbors_set;
}

void generate_neighbors(const std::string& pattern, size_t index, int current_distance, int max_distance, std::unordered_set<std::string>& neighbors_set) {
    if (current_distance > max_distance) {
        return;
    }
    
    if (index == pattern.length()) {
        if (current_distance <= max_distance) {
            neighbors_set.insert(pattern);
        }
        return;
    }
    
    // Keep the original character
    generate_neighbors(pattern, index + 1, current_distance, max_distance, neighbors_set);
    
    // Change the character at the current index
    char nucleotides[] = {'A', 'C', 'G', 'T'};
    for (char nucleotide : nucleotides) {
        if (nucleotide != pattern[index]) {
            std::string new_pattern = pattern;
            new_pattern[index] = nucleotide; // Change character
            generate_neighbors(new_pattern, index + 1, current_distance + 1, max_distance, neighbors_set);
        }
    }
}

int main() {
    std::string input;
    int distance;

    // Example input
    std::cout << "Enter a string (DNA sequence): ";
    std::cin >> input;
    std::cout << "Enter the maximum Hamming distance: ";
    std::cin >> distance;

    std::unordered_set<std::string> result = neighbors(input, distance);
    
    std::cout << "Neighbors within distance " << distance << ":\n";
    for (const auto& neighbor : result) {
        std::cout << neighbor << "\n";
    }

    return 0;
}
