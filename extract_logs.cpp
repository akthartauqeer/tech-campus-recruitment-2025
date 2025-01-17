#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

void process_log_file(const std::string& date) {
    // Open the log file for reading
    std::ifstream logFile("logs_2024.log");  // Update the filename here
    if (!logFile) {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }

    // Prepare the output file for the given date
    std::ofstream outFile("output/output_" + date + ".txt");
    if (!outFile) {
        std::cerr << "Error creating output file!" << std::endl;
        return;
    }

    std::string line;
    size_t match_count = 0;
    
    // Process the log file line by line
    while (std::getline(logFile, line)) {
        // Extract the date part from the timestamp
        std::string timestamp = line.substr(0, 10); // First 10 chars represent YYYY-MM-DD

        // Check if the line's date matches the input date
        if (timestamp == date) {
            // Write the matching log entry to the output file
            outFile << line << std::endl;
            match_count++;
        }
    }

    // Check if no matching logs were found
    if (match_count == 0) {
        std::cout << "No logs found for the date: " << date << std::endl;
    } else {
        std::cout << "Successfully written " << match_count << " logs to output_" << date << ".txt" << std::endl;
    }

    // Close the files
    logFile.close();
    outFile.close();
}

int main(int argc, char* argv[]) {
    // Ensure a date argument is provided
    if (argc != 2) {
        std::cerr << "Usage: ./extract_logs <YYYY-MM-DD>" << std::endl;
        return 1;
    }

    std::string date = argv[1];
    
    // Validate the date format (YYYY-MM-DD)
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        std::cerr << "Invalid date format. Please use YYYY-MM-DD." << std::endl;
        return 1;
    }

    // Call the function to process the log file
    process_log_file(date);

    return 0;
}
