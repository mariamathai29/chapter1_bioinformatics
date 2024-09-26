#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::vector<std::string> find_clumps(const std::string& genome, int k, int L, int t) {
    std::unordered_set<std::string> clumps; // To store distinct k-mers that form clumps
    std::unordered_map<std::string, int> kmer_count; // To count k-mers in the current window

    // Loop over the genome with a sliding window of size L
    for (size_t i = 0; i <= genome.length() - L; ++i) {
        // Get the current window
        std::string window = genome.substr(i, L);
        
        // Count k-mers in the current window
        for (size_t j = 0; j <= window.length() - k; ++j) {
            std::string kmer = window.substr(j, k);
            kmer_count[kmer]++;
        }

        // Check for clumps in the current window
        for (const auto& pair : kmer_count) {
            if (pair.second >= t) {
                clumps.insert(pair.first);
            }
        }

        // Reset k-mer count for the next window
        kmer_count.clear();
    }

    // Convert set to vector and sort it
    std::vector<std::string> result(clumps.begin(), clumps.end());
    std::sort(result.begin(), result.end());
    return result;
}

int main() {
    std::string genome;
    int k, L, t;

    // Example input
    std::cout << "Enter genome: ";
    std::getline(std::cin, genome);
    std::cout << "Enter values for k, L, and t: ";
    std::cin >> k >> L >> t;

    std::vector<std::string> clumps = find_clumps(genome, k, L, t);
    
    // Print the results
    std::cout << "Clumps found: ";
    for (const std::string& kmer : clumps) {
        std::cout << kmer << " ";
    }
    std::cout << std::endl;

    return 0;
}
