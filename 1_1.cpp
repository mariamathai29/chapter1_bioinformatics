#include <iostream>
#include <string>
#include <tuple>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

// implement patternCount to find no. of times a certain sequence appears in a string
int countOccurrences(const std::string& full, const std::string& pattern) {
    int count = 0;
    size_t pos = full.find(pattern, 0);
    while (pos != std::string::npos) {
        count++;
        pos = full.find(pattern, pos + 1);
    }
    return count;
}


int PatternCount(std::string Text,
		 std::string Pattern){
    return countOccurrences(Text,Pattern);
}


// find the most common k-length sequence of characters from a DNA sequence
std::vector<std::string> freq_words(const std::string& text, int k) {
    std::unordered_map<std::string, int> kmer_counts;
    int max_count = 0;
    std::vector<std::string> frequent_kmers;

    // Count occurrences of each k-mer
    for (size_t i = 0; i <= text.length() - k; ++i) {
        std::string kmer = text.substr(i, k);
        kmer_counts[kmer]++;

        // Track maximum count
        if (kmer_counts[kmer] > max_count) {
            max_count = kmer_counts[kmer];
            frequent_kmers = {kmer};  // Start new list of frequent kmers
        } else if (kmer_counts[kmer] == max_count) {
            // Add to list if not already present
            if (std::find(frequent_kmers.begin(), frequent_kmers.end(), kmer) == frequent_kmers.end()) {
                frequent_kmers.push_back(kmer);
            }
        }
    }

    return frequent_kmers;
}

std::vector<std::string> frequent_words(const std::string& text, int k) {
    return freq_words(text, k);
}

int main() {
    std::string text;
    int k;

    // Example input
    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    std::cout << "Enter k: ";
    std::cin >> k;

    std::vector<std::string> result = frequent_words(text, k);
    
    std::cout << "Frequent k-mers: ";
    for (const auto& kmer : result) {
        std::cout << kmer << " ";
    }
    std::cout << std::endl;

    return 0;
}
