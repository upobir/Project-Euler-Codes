# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/

class GregorianDate{
private:
    static int monthDays[];
    int day, month, year;
public:
    enum weekDay{MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDYA, SATURDAY, SUNDAY};
    static bool isLeapYear(int year){
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    }
    
    GregorianDate(int d, int m, int y): day(d), month(m), year(y){
        assert(1 <= year);
        assert(1 <= month && month <=12);
        assert(1 <= day && day <= monthDays[month] - monthDays[month-1]);
    }

    int dayOfYear(){
        return day + monthDays[month-1] + ((month > 2 && isLeapYear(year))? 1 : 0);
    }

    bool operator<(GregorianDate other){
        return tie(year, month, day) < tie(other.year, other.month, other.day);
    }

    int operator-(GregorianDate other){
        if(other.day == 1 && other.month == 1 && other.year == 1){
            int ret = (year - 1) * 365;
            ret += dayOfYear()-1;
            ret += (year-1)/4 - (year-1)/100 + (year-1)/400;
            return ret;
        }
        else{
            GregorianDate firstDay(1, 1, 1);
            return (*this - firstDay) - (other - firstDay);
        }
    }

    //Zeller's formula
    weekDay dayOfWeek(){
        //return weekDay(operator-(GregorianDate(1, 1, 1)) % 7 + 1);
        int d = day, m = month, y = year;
        if(m < 3) m += 12, y -= 1;

        int ans = (d+13*(m+1)/5 + y + y/4 - y/100 + y/400 + 5) % 7 + 1;
        if(ans < 0) ans += 7;
        return weekDay(ans);
    }
};
int GregorianDate::monthDays[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

int sundaysInDaysOfCentury(int century, int day){
    int startYear = (century-1)*100+1, finishYear = century*100;
    int ret = 0;
    for(int year = startYear; year <= finishYear; year++){
        for(int month = 1; month <=12; month++)
            if(GregorianDate::SUNDAY == GregorianDate(day, month, year).dayOfWeek())
                ret++;
    }
    return ret;
}

int main(){
    Time(
        cout<<sundaysInDaysOfCentury(20, 1)<<endl;
    )
    return 0;
}

/*
Note:
 This could've been solved by zeller's equation alone, but for generality I mad a class for gregorian dates, which assumes gregorian date 
 from year 1 (which is false, but good for implementation)
 Complexity: O(1)
*/