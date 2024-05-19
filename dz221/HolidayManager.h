#pragma warning(disable : 4996)
#ifndef HOLIDAYMANAGER_H
#define HOLIDAYMANAGER_H

#include <ctime>

#define MAX_HOLIDAYS 100
#define MAX_NAME_LEN 50

class HolidayManager {
public:
    struct Holiday {
        char name[MAX_NAME_LEN];
        std::tm date;
    };

    HolidayManager();

    void addHoliday(const char* name, const std::tm& date);
    void removeHoliday(const char* name);
    void editHoliday(const char* oldName, const char* newName, const std::tm& newDate);
    void remindHolidays() const;
    void showTodayHolidays() const;
    void showAllHolidays() const;
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

private:
    Holiday holidays[MAX_HOLIDAYS];
    int holidayCount;

    std::tm getCurrentTime() const;
    static std::tm addDays(const std::tm& date, int days);
    static bool isSameDay(const std::tm& date1, const std::tm& date2);
};

#endif // HOLIDAYMANAGER_H
