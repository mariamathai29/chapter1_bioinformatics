#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Function to compute the reverse complement of a DNA pattern
std::string rev_comp(const std::string& pattern) {
    std::unordered_map<char, char> complement = {
        {'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}
    };
    std::string reverse_comp;

    // Iterate through the pattern in reverse order
    for (auto it = pattern.rbegin(); it != pattern.rend(); ++it) {
        reverse_comp += complement[*it]; // Append the complement
    }

    return reverse_comp;
}

// Function to find positions of a pattern in a genome
std::vector<int> pattern_match(const std::string& pattern, const std::string& genome) {
    std::vector<int> positions;
    int pattern_length = pattern.length();
    int genome_length = genome.length();
    
    // Iterate through genome and check each substring
    for (int i = 0; i <= genome_length - pattern_length; ++i) {
        if (genome.substr(i, pattern_length) == pattern) {
            positions.push_back(i);
        }
    }

    return positions;
}

int main() {
    std::string pattern;
    std::string genome;

    // Get input for the pattern and genome
    std::cout << "Enter DNA pattern: ";
    std::getline(std::cin, pattern);

    // Calculate and display the reverse complement
    std::string reverse_comp_result = rev_comp(pattern);
    std::cout << "Reverse complement: " << reverse_comp_result << std::endl;

    std::cout << "Enter the genome: ";
    std::getline(std::cin, genome);

    // Find and display positions of the pattern in the genome
    std::vector<int> result = pattern_match(pattern, genome);
    
    std::cout << "Positions: ";
    for (int position : result) {
        std::cout << position << " ";
    }
    std::cout << std::endl;

    return 0;
}
