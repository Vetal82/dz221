#include "HolidayManager.h"
#include <iostream>

int main() {
    HolidayManager manager;

    // Load existing holidays from file
    manager.loadFromFile("holidays.dat");

    // Add a new holiday
    std::tm newYear = {};
    newYear.tm_year = 2024 - 1900; // Year 2024
    newYear.tm_mon = 0; // January
    newYear.tm_mday = 1; // 1st
    manager.addHoliday("New Year", newYear);

    // Show all holidays
    std::cout << "All holidays:" << std::endl;
    manager.showAllHolidays();

    // Show today's holidays
    std::cout << "\nToday's holidays:" << std::endl;
    manager.showTodayHolidays();

    // Remind holidays
    std::cout << "\nReminders:" << std::endl;
    manager.remindHolidays();

    // Save holidays to file
    manager.saveToFile("holidays.dat");

    return 0;
}
