#include <string>
#include <iostream>
#include <stdio.h>
#include <random>

const std::string
    BEDTIME[] = {
        "〜20:59",
        "21:00~21:59",
        "22:00~22:59",
        "23:00~23:59",
        "24:00~24:59",
        "25:00~"
    },
    WAKETIME[] = {
        "〜5：55",
        "6：00〜6：59",
        "7：00〜7：59",
        "8：00〜8：59",
        "9：00〜9：59",
        "10:00~AM"
    },
    EXERCISE[] = {
        "散歩;",
        "ランニング;",
        "サイクリング;",
        "筋力トレーニング;"
    };

std::random_device rnd;

class Date {
public:
    int month, day;

    Date (int _month, int _day) {
        month = _month;
        day   = _day;
    }

    void rewind() {
        day--;

        if (day <= 0) {
            day = 30;
            month--;

            if (month <= 0) {
                month = 1;
            }

            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                day++;
            }
            if (month == 2) day = 28;
        }
    }

    Date forward() {
        day++;

        if (
            (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) &&
            day > 31 ||
            (month == 4 || month == 6 || month == 9 || month == 11) &&
            day > 30 ||
            month == 2 &&
            day > 28
        ) {
            day = 1;
            month++;

            if (month > 12) {
                month = 1;
            }
        }

        return *this;
    }

    bool operator <= (Date d) {
        return month < d.month || month == d.month && day <= d.day;
    }
};

class Time {
public:
    int hour, minute, second;

    Time operator + (int s) {
        Time time;

        time.second = (second + s) % 60;
        time.minute = (minute + s / 60) % 60;
        time.hour   = (hour + s / 3600) % 24;

        return time;
    }
};

Time generate_random_time() {
    Time time;

    time.hour   = rnd() % 14 + 8;
    time.minute = rnd() % 60;
    time.second = rnd() % 60;

    return time;
}

int generate_random_gap() {
    return rnd() % 100 + 10;
}

double generate_random_difference() {
    int a = (rnd() % 11 - 5);
    return a / 10.0;
}

std::string generate_random_meal() {
    return "なし;";
}

int main() {
    int start_m, start_d, end_m, end_d, heat;
    std::string email, id;

    std::cout<<"始まりの日(例: 6/27): ";
    scanf("%d/%d", &start_m, &start_d);

    std::cout<<"終わりの日(例: 6/27): ";
    scanf("%d/%d", &end_m, &end_d);

    Date
        now(start_m, start_d),
        end(end_m,   end_d);

    std::cout<<"学生ID: ";
    std::cin>>email;

    std::cout<<"クラス、名簿(例: Ec4-32): ";
    std::cin>>id;

    std::cout<<"平熱(整数で大体): ";
    std::cin>>heat;

    now.rewind();

    while (now.forward() <= end) {
        Time start, finish;

        start  = generate_random_time();
        finish = start + generate_random_gap();

        printf(
            "%d/%d/20 %d:%02d:%02d,%d/%d/20 %d:%02d:%02d,%s@nagaoka.kosen-ac.jp,%s %s,%d/%d/2020,%s,%s,%f,%s,%s,%s,%s\n",
            now.month, now.day, start.hour,  start.minute,  start.second,
            now.month, now.day, finish.hour, finish.minute, finish.second,
            email.c_str(),
            id.c_str(), email.c_str(),
            now.month, now.day,
            BEDTIME[rnd() % 6].c_str(),
            WAKETIME[rnd() % 6].c_str(),
            heat + generate_random_difference(),
            generate_random_meal().c_str(),
            generate_random_meal().c_str(),
            generate_random_meal().c_str(),
            EXERCISE[rnd() % 4].c_str()
        );
    }
}