#include "HolidayManager.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

HolidayManager::HolidayManager() : holidayCount(0) {}

void HolidayManager::addHoliday(const char* name, const std::tm& date) {
    if (holidayCount < MAX_HOLIDAYS) {
        std::strncpy(holidays[holidayCount].name, name, MAX_NAME_LEN - 1);
        holidays[holidayCount].name[MAX_NAME_LEN - 1] = '\0';
        holidays[holidayCount].date = date;
        holidayCount++;
    }
}

void HolidayManager::removeHoliday(const char* name) {
    for (int i = 0; i < holidayCount; ++i) {
        if (std::strncmp(holidays[i].name, name, MAX_NAME_LEN) == 0) {
            for (int j = i; j < holidayCount - 1; ++j) {
                holidays[j] = holidays[j + 1];
            }
            holidayCount--;
            break;
        }
    }
}

void HolidayManager::editHoliday(const char* oldName, const char* newName, const std::tm& newDate) {
    for (int i = 0; i < holidayCount; ++i) {
        if (std::strncmp(holidays[i].name, oldName, MAX_NAME_LEN) == 0) {
            std::strncpy(holidays[i].name, newName, MAX_NAME_LEN - 1);
            holidays[i].name[MAX_NAME_LEN - 1] = '\0';
            holidays[i].date = newDate;
            break;
        }
    }
}

void HolidayManager::remindHolidays() const {
    std::tm currentTime = getCurrentTime();
    std::tm reminderDate = addDays(currentTime, 3);

    for (int i = 0; i < holidayCount; ++i) {
        if (isSameDay(holidays[i].date, reminderDate)) {
            std::cout << "Reminder: Holiday " << holidays[i].name << " is in 3 days!" << std::endl;
        }
    }
}

void HolidayManager::showTodayHolidays() const {
    std::tm currentTime = getCurrentTime();

    for (int i = 0; i < holidayCount; ++i) {
        if (isSameDay(holidays[i].date, currentTime)) {
            std::cout << "Today is " << holidays[i].name << "!" << std::endl;
        }
    }
}

void HolidayManager::showAllHolidays() const {
    for (int i = 0; i < holidayCount; ++i) {
        std::cout << holidays[i].name << " on "
            << std::put_time(&holidays[i].date, "%Y-%m-%d") << std::endl;
    }
}

void HolidayManager::saveToFile(const char* filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&holidayCount), sizeof(holidayCount));
        file.write(reinterpret_cast<const char*>(holidays), sizeof(Holiday) * holidayCount);
        file.close();
    }
    else {
        std::cerr << "Error opening file for saving: " << filename << std::endl;
    }
}

void HolidayManager::loadFromFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&holidayCount), sizeof(holidayCount));
        file.read(reinterpret_cast<char*>(holidays), sizeof(Holiday) * holidayCount);
        file.close();
    }
    else {
        std::cerr << "Error opening file for loading: " << filename << std::endl;
    }
}

std::tm HolidayManager::getCurrentTime() const {
    std::time_t t = std::time(nullptr);
    return *std::localtime(&t);
}

std::tm HolidayManager::addDays(const std::tm& date, int days) {
    std::tm newDate = date;
    newDate.tm_mday += days;
    std::mktime(&newDate);
    return newDate;
}

bool HolidayManager::isSameDay(const std::tm& date1, const std::tm& date2) {
    return date1.tm_year == date2.tm_year &&
        date1.tm_mon == date2.tm_mon &&
        date1.tm_mday == date2.tm_mday;
}
