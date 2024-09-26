#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

// Function to calculate the Hamming distance between two strings
int hamming_distance(const std::string& p, const std::string& q) {
    if (p.length() != q.length()) {
        throw std::invalid_argument("Strings must be of equal length");
    }
    int distance = 0;
    for (size_t i = 0; i < p.length(); ++i) {
        if (p[i] != q[i]) {
            distance++;
        }
    }
    return distance;
}

// Function to find all starting positions where Pattern appears as a substring of Text with at most d mismatches
std::vector<int> approximate_pattern_matching(const std::string& pattern, const std::string& text, int d) {
    std::vector<int> positions;
    size_t k = pattern.length();
    for (size_t i = 0; i <= text.length() - k; ++i) {
        std::string substring = text.substr(i, k);
        int mismatches = hamming_distance(pattern, substring);
        if (mismatches <= d) {
            positions.push_back(i);
        }
    }
    return positions;
}

// Function to count occurrences of a pattern in a text, allowing for up to d mismatches
int approximate_pattern_count(const std::string& text, const std::string& pattern, int d) {
    int count = 0;
    size_t pattern_length = pattern.length();
    for (size_t i = 0; i <= text.length() - pattern_length; ++i) {
        std::string substring = text.substr(i, pattern_length);
        int mismatches = hamming_distance(substring, pattern);
        if (mismatches <= d) {
            count++;
        }
    }
    return count;
}

// Function to generate all k-mers that are within d mismatches of the given pattern
std::unordered_set<std::string> neighbors(const std::string& pattern, int d) {
    if (d == 0) {
        return {pattern};
    }
    if (pattern.length() == 1) {
        return {"A", "C", "G", "T"};
    }
    
    std::unordered_set<std::string> neighborhood;
    char last_char = pattern[0];
    std::string suffix = pattern.substr(1);
    std::unordered_set<std::string> suffix_neighbors = neighbors(suffix, d);

    for (const auto& text : suffix_neighbors) {
        if (hamming_distance(suffix, text) < d) {
            for (char nucleotide : "ACGT") {
                neighborhood.insert(nucleotide + text);
            }
        } else {
            neighborhood.insert(last_char + text);
        }
    }

    return neighborhood;
}

// Function to find the most frequent k-mers with up to d mismatches in a text
std::vector<std::string> frequent_words_with_mismatches(const std::string& text, int k, int d) {
    std::unordered_map<std::string, int> kmer_count;

    for (size_t i = 0; i <= text.length() - k; ++i) {
        std::string kmer = text.substr(i, k);
        auto neighbor_set = neighbors(kmer, d);
        for (const auto& neighbor : neighbor_set) {
            kmer_count[neighbor]++;
        }
    }

    int max_count = 0;
    for (const auto& pair : kmer_count) {
        max_count = std::max(max_count, pair.second);
    }

    std::vector<std::string> frequent_kmers;
    for (const auto& pair : kmer_count) {
        if (pair.second == max_count) {
            frequent_kmers.push_back(pair.first);
        }
    }

    std::sort(frequent_kmers.begin(), frequent_kmers.end());
    return frequent_kmers;
}

// Function to get the reverse complement of a DNA string
std::string reverse_complement(const std::string& pattern) {
    std::unordered_map<char, char> complement = {{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};
    std::string rev_comp;
    for (auto it = pattern.rbegin(); it != pattern.rend(); ++it) {
        rev_comp += complement[*it];
    }
    return rev_comp;
}

// Function to count occurrences of pattern in text with up to d mismatches (including reverse complements)
int count_d(const std::string& text, const std::string& pattern, int d) {
    int count = 0;
    for (size_t i = 0; i <= text.length() - pattern.length(); ++i) {
        if (hamming_distance(text.substr(i, pattern.length()), pattern) <= d) {
            count++;
        }
    }
    return count;
}

// Function to find the most frequent k-mers with up to d mismatches, including reverse complements
std::vector<std::string> frequent_words_mismatches_reverse_complements(const std::string& text, int k, int d) {
    std::unordered_map<std::string, int> frequency_map;
    int max_count = 0;

    for (size_t i = 0; i <= text.length() - k; ++i) {
        std::string pattern = text.substr(i, k);
        std::string rc_pattern = reverse_complement(pattern);
        
        int count_pattern = count_d(text, pattern, d);
        int count_rc_pattern = count_d(text, rc_pattern, d);
        
        int total_count = count_pattern + count_rc_pattern;
        
        frequency_map[pattern] = total_count;
        frequency_map[rc_pattern] = total_count;

        max_count = std::max(max_count, total_count);
    }

    std::unordered_set<std::string> result;
    for (const auto& pair : frequency_map) {
        if (pair.second == max_count) {
            result.insert(pair.first);
        }
    }

    std::vector<std::string> sorted_result(result.begin(), result.end());
    std::sort(sorted_result.begin(), sorted_result.end());
    return sorted_result;
}

int main() {
    // Example usage
    std::string text = "ACGTACGTGACG";
    std::string pattern = "ACG";
    int d = 1;

    // Test approximate pattern matching
    std::vector<int> positions = approximate_pattern_matching(pattern, text, d);
    std::cout << "Approximate pattern matching positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    // Test frequent words with mismatches
    std::vector<std::string> frequent_kmers = frequent_words_with_mismatches(text, 3, 1);
    std::cout << "Frequent k-mers with mismatches: ";
    for (const std::string& kmer : frequent_kmers) {
        std::cout << kmer << " ";
    }
    std::cout << std::endl;

    // Test frequent words mismatches with reverse complements
    std::vector<std::string> frequent_kmers_rc = frequent_words_mismatches_reverse_complements(text, 3, 1);
    std::cout << "Frequent k-mers with mismatches and reverse complements: ";
    for (const std::string& kmer : frequent_kmers_rc) {
        std::cout << kmer << " ";
    }
    std::cout << std::endl;

    return 0;
}
