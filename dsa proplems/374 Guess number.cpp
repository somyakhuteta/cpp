/*
 * ============================================================================
 * GUESS NUMBER GAME - Advanced Educational Project
 * ============================================================================
 * A comprehensive C++ project demonstrating binary search algorithm with
 * advanced features including game modes, statistics tracking, difficulty levels,
 * input validation, and game history tracking.
 * 
 * Author: Learning Project
 * Date: 2024
 * 
 * FEATURES:
 *   - 4 difficulty levels (Easy, Medium, Hard, Expert)
 *   - Two game modes (Player guesses or AI guesses)
 *   - Comprehensive statistics tracking
 *   - Game history records
 *   - Binary search algorithm tutorial
 *   - Input validation and error handling
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;

// ============================================================================
// CONSTANTS AND CONFIGURATION
// ============================================================================

const int EASY_RANGE = 100;          // Easy mode: guess number 1-100
const int MEDIUM_RANGE = 1000;       // Medium mode: guess number 1-1000
const int HARD_RANGE = 10000;        // Hard mode: guess number 1-10000
const int EXPERT_RANGE = 100000;     // Expert mode: guess number 1-100000
const int MAX_ATTEMPTS = 100;        // Maximum attempts allowed per game
const int HISTORY_SIZE = 50;         // Maximum game history records
const string VERSION = "1.0.0";      // Game version

// ============================================================================
// STRUCTURES FOR DATA MANAGEMENT
// ============================================================================

/**
 * GameRecord structure stores information about each completed game
 */
struct GameRecord {
    long long range;
    long long target;
    long long guesses_taken;
    long long optimal_guesses;
    bool won;
    string difficulty;
    string game_type;  // "Player" or "AI"
};

/**
 * PlayerStats structure tracks overall player performance
 */
struct PlayerStats {
    long long total_games;
    long long games_won;
    long long games_lost;
    long long total_guesses;
    double average_guesses;
    long long best_game_guesses;
    long long worst_game_guesses;
    double best_win_rate;
    double win_win;
    long long multiples;
};

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

vector<GameRecord> game_history;
PlayerStats player_stats;

// ============================================================================
// FORWARD DECLARATIONS
// ============================================================================

long long calculate_optimal_guesses(long long range);

// ============================================================================
// HELPER FUNCTIONS - INPUT VALIDATION
// ============================================================================

/**
 * Validates if input string contains only digits
 * Parameters: str - the string to validate
 * Returns: true if string contains only digits, false otherwise
 */
bool is_valid_number(const string& str) {
    if (str.empty()) {
        return false;
    }
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

/**
 * Converts string to long long with error handling
 * Parameters: str - the string to convert
 * Returns: the converted long long value
 */
long long string_to_long_long(const string& str) {
    try {
        return stoll(str);
    } catch (...) {
        return -1;
    }
}

/**
 * Gets a valid long long input from user with retry logic
 * Parameters: prompt - the message to display to user
 * Returns: valid long long input from user
 */
long long get_valid_input(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        // Trim whitespace
        while (!input.empty() && isspace(input.back())) {
            input.pop_back();
        }
        while (!input.empty() && isspace(input.front())) {
            input.erase(0, 1);
        }
        
        
        if (is_valid_number(input)) {
            return string_to_long_long(input);
        }
        cout << "ERROR: Please enter a valid number!\n";
    }
}

/**
 * Gets user's guess with range validation
 * Parameters: min_val - minimum valid value, max_val - maximum valid value
 * Returns: valid guess within the specified range
 */
long long get_valid_guess(long long min_val, long long max_val) {
    while (true) {
        long long guess = get_valid_input("Enter your guess: ");
        if (guess < min_val || guess > max_val) {
            cout << "ERROR: Guess must be between " << min_val << " and " 
                 << max_val << "!\n";
            continue;
        }
        return guess;
    }
}

/**
 * Gets single character input from user
 * Parameters: prompt - message to display
 * Returns: the character entered by user
 */
char get_char_input(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    if (!input.empty()) {
        return input[0];
    }
    return 'n';
}

// ============================================================================
// CORE BINARY SEARCH GUESSING LOGIC
// ============================================================================

/**
 * AI guesses number using binary search algorithm
 * The computer plays as the guesser and tries to find the player's number
 * 
 * Algorithm:
 *   1. Start with search space [1, max_range]
 *   2. Calculate middle: mid = left + (right - left) / 2
 *   3. Ask player if their number is higher, lower, or equals to mid
 *   4. Adjust search space accordingly
 *   5. Repeat until number is found
 * 
 * Parameters:
 *   max_range: upper limit of the number range
 *   player_number: the number the player is thinking of
 * 
 * Returns: number of guesses AI took to find the number
 */
long long ai_guess_binary_search(long long max_range, long long player_number) {
    long long left = 1;
    long long right = max_range;
    long long guess_count = 0;
    
    cout << "\n========== AI IS GUESSING YOUR NUMBER ==========\n";
    cout << "Instructions:\n";
    cout << "  - Type 'H' if your number is Higher than my guess\n";
    cout << "  - Type 'L' if your number is Lower than my guess\n";
    cout << "  - Type 'C' if my guess is Correct\n";
    cout << "  - Type 'Q' to Quit\n\n";
    
    while (left <= right && guess_count < MAX_ATTEMPTS) {
        long long mid = left + (right - left) / 2;
        guess_count++;
        
        cout << "Attempt " << guess_count << ": AI guesses " << mid << " ... ";
        
        if (mid == player_number) {
            cout << "CORRECT!\n";
            cout << "AI found your number in " << guess_count << " guesses!\n";
            return guess_count;
        } else if (mid < player_number) {
            cout << "(too low, searching higher)\n";
            left = mid + 1;
        } else {
            cout << "(too high, searching lower)\n";
            right = mid - 1;
        }
        
        if (guess_count <= 0) {
            cout << "ERROR: Exceeded maximum attempts!\n";
            return -1;
        }
    }
    
    return guess_count;
}

/**
 * Player guesses a number generated by the computer
 * Computer randomly generates a target number and player tries to guess it
 * 
 * Game Flow:
 *   1. Computer randomly generates target between 1 and max_range
 *   2. Player enters a guess
 *   3. Computer provides feedback (too high, too low, correct)
 *   4. Player tries again until number is found or max attempts reached
 * 
 * Parameters:
 *   max_range: upper limit of the number range
 * 
 * Returns: number of guesses player took (or -1 if failed)
 */
long long player_guess_mode(long long max_range) {
    long long target = (rand() % max_range) + 1;
    long long guess_count = 0;
    long long player_guess;
    
    cout << "\n========== YOU ARE GUESSING ==========\n";
    cout << "I'm thinking of a number between 1 and " << max_range << "\n";
    cout << "Try to guess it! You have " << MAX_ATTEMPTS << " attempts.\n\n";
    
    while (guess_count < MAX_ATTEMPTS) {
        player_guess = get_valid_guess(1, max_range);
        guess_count++;
        
        cout << "Attempt " << guess_count << ": ";
        
        if (player_guess == target) {
            cout << "CORRECT! You found the number " << target << "\n";
            cout << "You took " << guess_count << " guesses!\n";
            cout << "Optimal would have been " << calculate_optimal_guesses(max_range) 
                 << " guesses.\n";
            return guess_count;
        } else if (player_guess < target) {
            cout << "Too Low! Try a higher number.\n";
        } else {
            cout << "Too High! Try a lower number.\n";
        }
        
        cout << "Remaining attempts: " << (MAX_ATTEMPTS - guess_count) << "\n\n";
    }
    
    cout << "ERROR: You exceeded " << MAX_ATTEMPTS << " attempts!\n";
    cout << "The number was: " << target << "\n";
    return -1;
}

/**
 * Calculates the optimal/theoretical minimum number of guesses needed
 * Uses binary search formula: ceil(log2(n)) where n is the range
 * 
 * Example:
 *   - Range 100: log2(100) = 6.64, so optimal = 7
 *   - Range 1000: log2(1000) = 9.97, so optimal = 10
 * 
 * Parameters:
 *   range: the size of the search range
 * fix the inputs and outputs 
 * Returns: theoretical minimum guesses needed
 */
long long calculate_optimal_guesses(long long range) {
    long long optimal = 0;
    long long temp = range;
    
    // Count how many times we can divide by 2
    while (temp > 0) {
        temp /= 2;
        optimal++;
    }
    
    return optimal;
}

/**
 * Calculates efficiency score as percentage
 * Lower guess count = higher efficiency
 * 
 * Parameters:
 *   actual: actual number of guesses taken
 *   optimal: theoretical minimum guesses
 * 
 * Returns: efficiency percentage (100 = optimal)
 */
double calculate_efficiency(long long actual, long long optimal) {
    if (optimal == 0) return 0.0;
    return (optimal * 100.0) / actual;
}

// ============================================================================
// GAME MODE FUNCTIONS
// ============================================================================

/**
 * Easy Mode: Range 1-100, max 7 optimal guesses
 */
void play_easy_mode() {
    cout << "\n========== EASY MODE ==========\n";
    cout << "Range: 1 - 100\n";
    cout << "Optimal guesses: " << calculate_optimal_guesses(EASY_RANGE) << "\n";
    cout << "\nSelect game mode:\n";
    cout << "  1) You guess the number\n";
    cout << "  2) AI guesses your number\n";
    cout << "  0) Cancel\n";
    
    long long choice = get_valid_input("Enter choice (0-2): ");
    
    if (choice == 1) {
        long long guesses = player_guess_mode(EASY_RANGE);
        if (guesses != -1) {
            GameRecord record;
            record.range = EASY_RANGE;
            record.target = 0;  // Not tracked in this mode
            record.guesses_taken = guesses;
            record.optimal_guesses = calculate_optimal_guesses(EASY_RANGE);
            record.won = true;
            record.difficulty = "Easy";
            record.game_type = "Player";
            game_history.push_back(record);
            player_stats.games_won++;
            player_stats.total_guesses += guesses;
        }
    } else if (choice == 2) {
        long long player_number = get_valid_input("Think of a number 1-100: ");
        if (player_number >= 1 && player_number <= EASY_RANGE) {
            long long guesses = ai_guess_binary_search(EASY_RANGE, player_number);
            if (guesses != -1) {
                GameRecord record;
                record.range = EASY_RANGE;
                record.target = player_number;
                record.guesses_taken = guesses;
                record.optimal_guesses = calculate_optimal_guesses(EASY_RANGE);
                record.won = true;
                record.difficulty = "Easy";
                record.game_type = "AI";
                game_history.push_back(record);
            }
        }
    }
}

/**
 * Medium Mode: Range 1-1000, max 10 optimal guesses
 */
void play_medium_mode() {
    cout << "\n========== MEDIUM MODE ==========\n";
    cout << "Range: 1 - 1000\n";
    cout << "Optimal guesses: " << calculate_optimal_guesses(MEDIUM_RANGE) << "\n";
    cout << "\nSelect game mode:\n";
    cout << "  1) You guess the number\n";
    cout << "  2) AI guesses your number\n";
    cout << "  0) Cancel\n";
    cout << " Note: Medium mode is a great way to practice biinary search with a large range and more options for guessing strategy than easymode. It's perfect for players who want a bit mode of a challenge while still being able to find the number in a reeasonable number of guesses. Try it out and see how you do! ";

    long long choice = get_valid_input("Enter choice (0-2): ");
    
    if (choice == 1) {
        long long guesses = player_guess_mode(MEDIUM_RANGE);
        if (guesses != -1) {
            GameRecord record;
            record.range = MEDIUM_RANGE;
            record.guesses_taken = guesses;
            record.optimal_guesses = calculate_optimal_guesses(MEDIUM_RANGE);
            record.won = true;
            record.difficulty = "Medium";
            record.game_type = "Player";
            game_history.push_back(record);
            player_stats.games_won++;
            player_stats.total_guesses += guesses;
        }
    } else if (choice == 2) {
        long long player_number = get_valid_input("Think of a number 1-1000: ");
        if (player_number >= 1 && player_number <= MEDIUM_RANGE) {
            long long guesses = ai_guess_binary_search(MEDIUM_RANGE, player_number);
            if (guesses != -1) {
                GameRecord record;
                record.range = MEDIUM_RANGE;
                record.target = player_number;
                record.guesses_taken = guesses;
                record.optimal_guesses = calculate_optimal_guesses(MEDIUM_RANGE);
                record.won = true;
                record.difficulty = "Medium";
                record.game_type = "AI";
                game_history.push_back(record);
            }
        }
    }
}

/**
 * Hard Mode: Range 1-10000, max 14 optimal guesses
 */
void play_hard_mode() {
    cout << "\n========== HARD MODE ==========\n";
    cout << "Range: 1 - 10000\n";
    cout << "Optimal guesses: " << calculate_optimal_guesses(HARD_RANGE) << "\n";
    cout << "\nSelect game mode:\n";
    cout << "  1) You guess the number\n";
    cout << "  2) AI guesses your number\n";
    cout << "  0) Cancel\n";
    
    long long choice = get_valid_input("Enter choice (0-2): ");
    
    if (choice == 1) {
        long long guesses = player_guess_mode(HARD_RANGE);
        if (guesses != -1) {
            GameRecord record;
            record.range = HARD_RANGE;
            record.guesses_taken = guesses;
            record.optimal_guesses = calculate_optimal_guesses(HARD_RANGE);
            record.won = true;
            record.difficulty = "Hard";
            record.game_type = "Player";
            game_history.push_back(record);
            player_stats.games_won++;
            player_stats.total_guesses += guesses;
        }
    } else if (choice == 2) {
        long long player_number = get_valid_input("Think of a number 1-10000: ");
        if (player_number >= 1 && player_number <= HARD_RANGE) {
            long long guesses = ai_guess_binary_search(HARD_RANGE, player_number);
            if (guesses != -1) {
                GameRecord record;
                record.range = HARD_RANGE;
                record.target = player_number;
                record.guesses_taken = guesses;
                record.optimal_guesses = calculate_optimal_guesses(HARD_RANGE);
                record.won = true;
            
                record.difficulty = "Hard";
                record.game_type = "AI";
                game_history.push_back(record);
            }
        }
    }
}

/**
 * Expert Mode: Range 1-100000, max 17 optimal guesses
 */
void play_expert_mode() {
    cout << "\n========== EXPERT MODE ==========\n";
    cout << "Range: 1 - 100000\n";
    cout << "Optimal guesses: " << calculate_optimal_guesses(EXPERT_RANGE) << "\n";
    cout << "\nSelect game mode:\n";
    cout << "  1) You guess the number\n";
    cout << "  2) AI guesses your number\n";
    cout << "  0) Cancel\n";
    
    long long choice = get_valid_input("Enter choice (0-2): ");
    
    if (choice == 1) {
        long long guesses = player_guess_mode(EXPERT_RANGE);
        if (guesses != -1) {
            GameRecord record;
            record.range = EXPERT_RANGE;
            record.guesses_taken = guesses;
            record.optimal_guesses = calculate_optimal_guesses(EXPERT_RANGE);
            record.won = true;
            record.difficulty = "Expert";
            record.game_type = "Player";
            game_history.push_back(record);
            player_stats.games_won++;
            player_stats.total_guesses += guesses;
        }
    } else if (choice == 2) {
        long long player_number = get_valid_input("Think of a number 1-100000: ");
        if (player_number >= 1 && player_number <= EXPERT_RANGE) {
            long long guesses = ai_guess_binary_search(EXPERT_RANGE, player_number);
            if (guesses != -1) {
                GameRecord record;
                record.range = EXPERT_RANGE;
                record.target = player_number;
                record.guesses_taken = guesses;
                record.optimal_guesses = calculate_optimal_guesses(EXPERT_RANGE);
                record.won = true;
                record.difficulty = "Expert";
                record.game_type = "AI";
                game_history.push_back(record);
            }
        }
    }
}

// ============================================================================
// STATISTICS AND HISTORY FUNCTIONS
// ============================================================================

/**
 * Displays comprehensive player statistics
 * Shows games played, win rate, average guesses, and best/worst performance
 */
void display_player_statistics() {
    cout << "\n========== PLAYER STATISTICS ==========\n";
    
    if (player_stats.total_games == 0) {
        cout << "No games played yet. Start playing to see statistics!\n";
        return;
    }
    
    double win_rate = (player_stats.games_won * 100.0) / player_stats.total_games;
    double avg_guesses = player_stats.games_won > 0 ? 
                         (player_stats.total_guesses * 1.0) / player_stats.games_won : 0.0;
    
    cout << "Total Games:           " << player_stats.total_games << "\n";
    cout << "Games Won:             " << player_stats.games_won << "\n";
    cout << "Games Lost:            " << player_stats.games_lost << "\n";
    cout << "Win Rate:              " << fixed << setprecision(2) 
         << win_rate << "%\n";
    cout << "Total Guesses:         " << player_stats.total_guesses << "\n";
    
    if (player_stats.games_won > 0) {
        cout << "Average Guesses:       " << fixed << setprecision(2) 
             << avg_guesses << "\n";
        cout << "Best Game:             " << player_stats.best_game_guesses 
             << " guesses\n";
        cout << "Worst Game:            " << player_stats.worst_game_guesses 
             << " guesses\n";
    }
}

/**
 * Displays the game history in a formatted table
 * Shows all completed games with their details
 */
void display_game_history() {
    cout << "\n========== GAME HISTORY ==========\n";
    
    if (game_history.empty()) {
        cout << "No games in history. Play some games first!\n";
        return;
    }
    
    cout << "\nTotal games played: " << game_history.size() << "\n\n";
    cout << left << setw(4) << "No." << setw(8) << "Mode" 
         << setw(12) << "Difficulty" << setw(10) << "Range" 
         << setw(10) << "Guesses" << setw(10) << "Optimal"
         << setw(12) << "Efficiency\n";
    cout << string(66, '-') << "\n";
    
    int count = 0;
    for (const auto& record : game_history) {
        if (count >= HISTORY_SIZE) break;
        
        count++;
        double efficiency = calculate_efficiency(record.guesses_taken, 
                                               record.optimal_guesses);
        
        cout << left << setw(4) << count 
             << setw(8) << record.game_type
             << setw(12) << record.difficulty
             << setw(10) << record.range
             << setw(12) << record.guesses_taken
             << setw(10) << record.optimal_guesses
             << fixed << setprecision(1) << setw(12) << efficiency << "%\n";
    }
}

/**
 * Clears all game history with confirmation
 */
void clear_game_history() {
    if (game_history.empty()) {
        cout << "No history to clear.\n";
        return;
    }
    
    char confirm = get_char_input(
        "Are you sure you want to clear all game history? (y/n): ");
    
    if (confirm == 'y' || confirm == 'Y') {
        game_history.clear();
        player_stats = {0, 0, 0, 0, 0.0, 0, 0, 0.0};
        cout << "Game history cleared!\n";
    } else {
        cout << "Operation cancelled.\n";
    }
}

// ============================================================================
// TUTORIAL AND HELP FUNCTIONS
// ============================================================================

/**
 * Displays comprehensive tutorial about binary search algorithm
 * Explains concept, complexity, and provides worked examples
 */
void display_tutorial() {
    cout << "\n========== BINARY SEARCH TUTORIAL ==========\n\n";
    
    cout << "WHAT IS BINARY SEARCH?\n";
    cout << "─────────────────────\n";
    cout << "Binary Search is an efficient algorithm for finding a value in a\n";
    cout << "SORTED array or range. It eliminates half of the remaining elements\n";
    cout << "with each comparison.\n\n";
    
    cout << "KEY CONCEPT:\n";
    cout << "─────────────\n";
    cout << "  1. Start with left = 1, right = max_range\n";
    cout << "  2. Calculate middle: mid = left + (right - left) / 2\n";
    cout << "  3. Compare target with middle element\n";
    cout << "  4. If target == mid: FOUND!\n";
    cout << "  5. If target > mid: Search right half (left = mid + 1)\n";
    cout << "  6. If target < mid: Search left half (right = mid - 1)\n";
    cout << "  7. Repeat until found or search space is empty\n\n";
    
    cout << "TIME COMPLEXITY: O(log n)\n";
    cout << "──────────────────────────\n";
    cout << "  - Range 1-100:      Maximum " << calculate_optimal_guesses(100) 
         << " guesses\n";
    cout << "  - Range 1-1000:     Maximum " << calculate_optimal_guesses(1000) 
         << " guesses\n";
    cout << "  - Range 1-10000:    Maximum " << calculate_optimal_guesses(10000) 
         << " guesses\n";
    cout << "  - Range 1-100000:   Maximum " << calculate_optimal_guesses(100000) 
         << " guesses\n";
    cout << "  - Range 1-1M:       Maximum " << calculate_optimal_guesses(1000000) 
         << " guesses\n\n";
    
    cout << "EXAMPLE 1: Finding 50 in range 1-100\n";
    cout << "───────────────────────────────────\n";
    cout << "  Step 1: mid = 50  ->  FOUND! (1 guess)\n\n";
    
    cout << "EXAMPLE 2: Finding 73 in range 1-100\n";
    cout << "───────────────────────────────────\n";
    cout << "  Step 1: mid = 50  ->  73 > 50 (search 51-100)\n";
    cout << "  Step 2: mid = 75  ->  73 < 75 (search 51-74)\n";
    cout << "  Step 3: mid = 62  ->  73 > 62 (search 63-74)\n";
    cout << "  Step 4: mid = 68  ->  73 > 68 (search 69-74)\n";
    cout << "  Step 5: mid = 71  ->  73 > 71 (search 72-74)\n";
    cout << "  Step 6: mid = 73  ->  FOUND! (6 guesses)\n\n";
    cout << "Example 3: Finding 999 in range 1-1000. Then finding 1 in range 1-1000. Then finding 500 in range 1-1000.";
    cout << "WHY IS IT EFFICIENT?\n";
    cout << "───────────────────\n";
    cout << "  - Linear search: worst case O(n) - checks every element\n";
    cout << "  - Binary search: worst case O(log n) - eliminates half each time\n";
    cout << "  - For 1,000,000 elements:\n";                                                                                                                                                                                                                                     
    cout << "Big O notation is a way to describe thhe efficiency of an algorithm in terms of the number of operations it performs as the input size grows. It provides a high-level understanding of how the algorithms.";
        
    cout << "    * Linear search: up to 1,000,000 comparisons\n";
    cout << "    * Binary search: up to " 
         << calculate_optimal_guesses(1000000) << " comparisons\n\n";
}

/**
 * Displays algorithm complexity information
 */
void display_algorithm_info() {
    cout << "\n========== ALGORITHM INFORMATION ==========\n\n";
    
    cout << "TIME COMPLEXITIES COMPARISON:\n";
    cout << "───────────────────────────\n";
    cout << "Algorithm          | Best   | Average | Worst  | Space\n";
    cout << "──────────────────────────────────────────────────────\n";
    cout << "Linear Search      | O(1)   | O(n)    | O(n)   | O(1)\n";
    cout << "Binary Search      | O(1)   | O(log n)| O(log n)| O(1)\n";
    cout << "Jump Search        | O(1)   | O(√n)   | O(√n)  | O(1)\n\n";
    
    cout << "WHEN TO USE BINARY SEARCH:\n";
    cout << "─────────────────────────\n";
    cout << "✓ Data is sorted or range is known\n";
    cout << "✓ Need efficient search performance\n";
    cout << "✓ Working with large datasets\n";
    cout << "✓ Limited time complexity requirements\n\n";
    
    cout << "WHEN NOT TO USE:\n";
    cout << "───────────────\n";
    cout << "✗ Data is unsorted and sorting is expensive\n";
    cout << "✗ Need to search by complex criteria\n";
    cout << "✗ Frequent insertions/deletions (overhead)\n";
}

/**
 * Displays game help and instructions
 */
void display_help() {
    cout << "\n========== HELP MENU ==========\n\n";
    cout << "MAIN MENU OPTIONS:\n";
    cout << "──────────────────\n";
    cout << "1) Easy Mode        - Guess number 1-100 (7 optimal)\n";
    cout << "2) Medium Mode      - Guess number 1-1000 (10 optimal)\n";
    cout << "3) Hard Mode        - Guess number 1-10000 (14 optimal)\n";
    cout << "4) Expert Mode      - Guess number 1-100000 (17 optimal)\n";
    cout << "5) Statistics       - View your game statistics\n";
    cout << "6) History          - View past game records\n";
    cout << "7) Tutorial         - Learn about binary search\n";
    cout << "8) Algorithm Info   - Understand complexity analysis\n";
    cout << "9) Clear History    - Reset all game data\n";
    cout << "0) Help             - Show this menu\n";
    cout << "Q) Quit             - Exit the program\n\n";
    cout << "GAME MODE SELECTION:\n";
    cout << "───────────────────\n";
    cout << "1) Player Guesses   - Computer picks, you guess using hints\n";
    cout << "2) AI Guesses       - You pick, AI guesses using binary search\n\n";
    
    cout << "EFFICIENCY CALCULATION:\n";
    cout << "──────────────────────\n";
    cout << "Efficiency % = (Optimal Guesses / Your Guesses) * 100\n";
    cout << "Example: If optimal is 7 and you took 8 guesses: 87.5% efficiency\n";
}

// ============================================================================
// INITIALIZATION AND UTILITY FUNCTIONS
// ============================================================================

/**
 * Initializes all player statistics to zero
 */
void initialize_player_stats() {
    player_stats.total_games = 0;
    player_stats.games_won = 0;
    player_stats.games_lost = 0;
    player_stats.total_guesses = 0;
    player_stats.average_guesses = 0.0;
    player_stats.best_game_guesses = INT_MAX;
    player_stats.worst_game_guesses = 0;
    player_stats.best_win_rate = 0.0;
}

/**
 * Calculates player achievement level based on statistics
 * Returns achievement tier based on games won and efficiency
 */
string calculate_achievement_level() {
    if (player_stats.total_games == 0) {
        return "Beginner";
    }
    
    double win_rate = (player_stats.games_won * 100.0) / player_stats.total_games;
    long long games_played = player_stats.total_games;
    
    if (games_played >= 100 && win_rate >= 95) {
        return "Grand Master";
    } else if (games_played >= 50 && win_rate >= 90) {
        return "Expert";
    } else if (games_played >= 25 && win_rate >= 85) {
        return "Master";
    } else if (games_played >= 10 && win_rate >= 80) {
        return "Advanced";
    } else if (games_played >= 5) {
        return "Intermediate";
    } else {
        return "Beginner";
    }
}

/**
 * Gets achievement badges based on performance metrics
 */
void display_achievements() {
    cout << "\n========== ACHIEVEMENTS ==========\n";
    cout << "Current Rank: " << calculate_achievement_level() << "\n\n";
    
    if (player_stats.total_games == 0) {
        cout << "Play some games to unlock achievements!\n";
        return;
    }
    
    // Achievement tracking
    int achievements_unlocked = 0;
    int total_achievements = 10;
    
    cout << "UNLOCKED ACHIEVEMENTS:\n";
    cout << "─────────────────────\n";
    
    if (player_stats.total_games >= 1) {
        cout << "✓ First Step        - Play your first game\n";
        achievements_unlocked++;
    }
    if (player_stats.total_games >= 5) {
        cout << "✓ Five Wins         - Win 5 games\n";
        achievements_unlocked++;
    }
    if (player_stats.total_games >= 10) {
        cout << "✓ Persistent        - Play 10 games\n";
        achievements_unlocked++;
    }
    if (player_stats.total_games >= 25) {
        cout << "✓ Dedicated         - Play 25 games\n";
        achievements_unlocked++;
    }
    if (player_stats.total_games >= 50) {
        cout << "✓ Unstoppable       - Play 50 games\n";
        achievements_unlocked++;
    }
    if (player_stats.total_games >= 100) {
        cout << "✓ Century Club      - Play 100 games\n";
        achievements_unlocked++;
    }
    if (player_stats.best_game_guesses <= 7 && player_stats.total_games >= 1) {
        cout << "✓ Perfect Strike    - Find number in optimal guesses\n";
        achievements_unlocked++;
    }
    if (player_stats.games_won == player_stats.total_games) {
        cout << "✓ Undefeated        - Win all games played\n";
        achievements_unlocked++;
    }
    
    double win_rate = (player_stats.games_won * 100.0) / player_stats.total_games;
    if (win_rate >= 90) {
        cout << "✓ High Efficiency   - Maintain 90%+ win rate\n";
        achievements_unlocked++;
    }
    if (win_rate == 100) {
        cout << "✓ Perfect Record    - 100% win rate\n";
        achievements_unlocked++;
    }
    
    cout << "\nProgress: " << achievements_unlocked << "/" << total_achievements 
         << " achievements\n";
}

/**
 * Displays leaderboard (simulated - based on current player stats)
 */
void display_leaderboard() {
    cout << "\n========== LEADERBOARD ==========\n";
    cout << "Your Ranking:\n\n";
    cout << left << setw(20) << "Metric" << setw(20) << "Value\n";
    cout << string(40, '-') << "\n";
    
    double win_rate = player_stats.total_games > 0 ? 
                      (player_stats.games_won * 100.0) / player_stats.total_games : 0;
    
    cout << left << setw(20) << "Total Games" 
         << setw(20) << player_stats.total_games << "\n";
    cout << left << setw(20) << "Win Rate" 
         << fixed << setprecision(1) << setw(20) << win_rate << "%\n";
    cout << left << setw(20) << "Best Game" 
         << setw(20) << (player_stats.best_game_guesses == INT_MAX ? 
                         0 : player_stats.best_game_guesses) << "\n";
    cout << left << setw(20) << "Rank" 
         << setw(20) << calculate_achievement_level() << "\n";
}

/**
 * Shows difficulty recommendations based on current performance
 */
void show_recommendations() {
    cout << "\n========== RECOMMENDATIONS ==========\n";
    
    if (player_stats.total_games == 0) {
        cout << "Start with Easy Mode to learn the basics!\n";
        return;
    }
    
    double avg_efficiency = 0;
    if (game_history.size() > 0) {
        double total_efficiency = 0;
        for (const auto& record : game_history) {
            total_efficiency += calculate_efficiency(record.guesses_taken, 
                                                     record.optimal_guesses);
        }
        avg_efficiency = total_efficiency / game_history.size();
    }
    
    cout << "Average Efficiency: " << fixed << setprecision(1) 
         << avg_efficiency << "%\n\n";
    
    if (avg_efficiency >= 95) {
        cout << "You're playing OPTIMALLY! Challenge yourself with Expert Mode!\n";
    } else if (avg_efficiency >= 85) {
        cout << "Great job! Try Hard Mode to improve further.\n";
    } else if (avg_efficiency >= 70) {
        cout << "Good progress! Practice Medium Mode for better efficiency.\n";
    } else {
        cout << "Keep practicing! Understand the binary search pattern.\n";
    }
}

/**
 * Displays practice tips for binary search
 */
void display_practice_tips() {
    cout << "\n========== PRACTICE TIPS ==========\n\n";
    
    cout << "HOW TO PLAY OPTIMALLY:\n";
    cout << "─────────────────────\n";
    cout << "1. Always guess the MIDDLE of your search range\n";
    cout << "2. Use feedback (too high/too low) to eliminate half\n";
    cout << "3. Don't skip over the middle - always split in half\n\n";
    
    cout << "MENTAL MATH FOR MIDDLE:\n";
    cout << "──────────────────────\n";
    cout << "If range is 1-100:\n";
    cout << "  low + (high - low) / 2 = 1 + 99/2 = 1 + 49 = 50\n";
    cout << "If range is 51-100:\n";
    cout << "  low + (high - low) / 2 = 51 + 49/2 = 51 + 24 = 75\n\n";
    
    cout << "OPTIMAL GUESSES BY RANGE:\n";
    cout << "────────────────────────\n";
    cout << "100 numbers:     " << calculate_optimal_guesses(100) << " guesses\n";
    cout << "1,000 numbers:   " << calculate_optimal_guesses(1000) << " guesses\n";
    cout << "10,000 numbers:  " << calculate_optimal_guesses(10000) << " guesses\n";
    cout << "100,000 numbers: " << calculate_optimal_guesses(100000) << " guesses\n";
}

/**
 * Displays welcome banner with game information
 */
void display_welcome() {
    cout << "\n";
    cout << "╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║        WELCOME TO THE GUESS NUMBER GAME!                 ║\n";
    cout << "║         A Binary Search Learning Tool v" << VERSION 
         << "               ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n";
    cout << "\nThis interactive game teaches you the binary search algorithm\n";
    cout << "through engaging gameplay with difficulty levels and statistics.\n";
    cout << "\nFeatures:\n";
    cout << "  • 4 difficulty levels with varying ranges\n";
    cout << "  • Two game modes (Player vs AI)\n";
    cout << "  • Comprehensive statistics tracking\n";
    cout << "  • Achievement system and leaderboard\n";
    cout << "  • Binary search algorithm tutorial\n\n";
    cout << "Type '0' for help anytime!\n";
}

/**
 * Displays exit message with final statistics
 */
void display_exit_message() {
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║      Thank you for playing Guess Number Game!            ║\n";
    cout << "║           Keep improving your algorithm skills!          ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
    
    if (player_stats.total_games > 0) {
        cout << "YOUR FINAL STATISTICS:\n";
        display_player_statistics();
        cout << "\nYour Final Rank: " << calculate_achievement_level() << "\n";
    }
    cout << "\nGoodbye!\n";
}

/**
 * Multiplayer simulation mode
 * Player plays multiple rounds and compares with average
 */
void tournament_mode() {
    cout << "\n========== TOURNAMENT MODE ==========\n";
    cout << "Play 3 games and see your average performance!\n";
    cout << "Select difficulty:\n";
    cout << "1) Easy\n2) Medium\n3) Hard\n4) Expert\n";
    
    long long difficulty = get_valid_input("Choose (1-4): ");
    long long range;
    string difficulty_name;
    
    switch (difficulty) {
        case 1:
            range = EASY_RANGE;
            difficulty_name = "Easy";
            break;
        case 2:
            range = MEDIUM_RANGE;
            difficulty_name = "Medium";
            break;
        case 3:
            range = HARD_RANGE;
            difficulty_name = "Hard";
            break;
        case 4:
            range = EXPERT_RANGE;
            difficulty_name = "Expert";
            break;
        default:
            cout << "Invalid choice!\n";
            return;
    }
    
    vector<long long> scores;
    long long total = 0;
    
    for (int i = 1; i <= 3; i++) {
        cout << "\n--- Game " << i << " of 3 ---\n";
        long long guesses = player_guess_mode(range);
        if (guesses != -1) {
            scores.push_back(guesses);
            total += guesses;
        }
    }
    
    if (scores.size() == 3) {
        cout << "\n========== TOURNAMENT RESULTS ==========\n";
        cout << "Game 1: " << scores[0] << " guesses\n";
        cout << "Game 2: " << scores[1] << " guesses\n";
        cout << "Game 3: " << scores[2] << " guesses\n";
        cout << "Average: " << fixed << setprecision(1) 
             << (total / 3.0) << " guesses\n";
        cout << "Optimal: " << calculate_optimal_guesses(range) << " guesses\n";
        double avg_efficiency = (calculate_optimal_guesses(range) * 100.0) / 
                               (total / 3.0);
        cout << "Efficiency: " << fixed << setprecision(1) 
             << avg_efficiency << "%\n";
    }
}

// ============================================================================
// MAIN GAME LOOP
// ============================================================================

int main() {
    // Seed random number generator with current time
    srand(static_cast<unsigned>(time(0)));
    
    // Initialize game state
    initialize_player_stats();
    display_welcome();
    
    long long choice = -1;
    
    while (choice != 9 && choice != 'Q') {
        cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        cout << "║                    MAIN MENU                             ║\n";
        cout << "╚═══════════════════════════════════════════════════════════╝\n";
        cout << "1) Easy Mode\n";
        cout << "2) Medium Mode\n";
        cout << "3) Hard Mode\n";
        cout << "4) Expert Mode\n";
        cout << "5) Statistics\n";
        cout << "6) History\n";
        cout << "7) Tutorial\n";
        cout << "8) Algorithm Info\n";
        cout << "9) Achievements\n";
        cout << "10) Leaderboard\n";
        cout << "11) Recommendations\n";
        cout << "12) Practice Tips\n";
        cout << "13) Tournament Mode\n";
        cout << "14) Clear History\n";
        cout << "0) Help\n";
        cout << "Q) Quit\n";
        
        choice = get_valid_input("Enter your choice: ");
        
        switch (choice) {
            case 1:
                play_easy_mode();
                player_stats.total_games++;
                break;
            case 2:
                play_medium_mode();
                player_stats.total_games++;
                break;
            case 3:
                play_hard_mode();
                player_stats.total_games++;
                break;
            case 4:
                play_expert_mode();
                player_stats.total_games++;
                break;
            case 5:
                display_player_statistics();
                break;
            case 6:
                display_game_history();
                break;
            case 7:
                display_tutorial();
                break;
            case 8:
                display_algorithm_info();
                break;
            case 9:
                display_achievements();
                break;
            case 10:
                display_leaderboard();
                break;
            case 11:
                show_recommendations();
                break;
            case 12:
                display_practice_tips();
                break;
            case 13:
                tournament_mode();
                player_stats.total_games += 3;
                break;
            case 14:
                clear_game_history();
                break;
            case 0:
                display_help();
                break;
            case 'Q':
            case 'q':
                display_exit_message();
                return 0;
            default:
                cout << "ERROR: Invalid choice! Please try again.\n";
        }
    }
    
    display_exit_message();
    return 0;
}
