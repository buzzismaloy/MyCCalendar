#include <stdio.h>
#include <time.h>
#include <string.h>

#define BEGIN_EPOCH 1900

const char* months[] = {"January", "February", "March", "April", "May", "June", 
                    "July", "August", "September", "October", "November", "December"};

int get_days_in_month(int month_n, int year);
void print_header();
void current_year_calendar();
void print_custom_calendar(int* year);
void print_spaces(int first_day);

int main(){
    while(1){
        int choice = 0, result = 0;
        printf("To display calendar of the current month, enter 1\n");
        printf("To display the calendar of any year starting from 1900, enter 2\n");
        result = scanf("%d", &choice);
        if(result == 1){
            if(choice == 1) {
                current_year_calendar();
                break;
            }
            else if(choice == 2){
                int user_year = 0, inp_res = 0;
                printf("Please, enter any number greater(or equal) than 1900:\n");
                while(1){
                    inp_res = scanf("%d", &user_year);
                    if(inp_res == 1){
                        if(user_year >= BEGIN_EPOCH){
                            break;
                        }
                        else printf("Number must not be less than 1900\n\n");
                        
                    }
                    else printf("Wrong input\n\n");
                    
                }
                print_custom_calendar(&user_year);
            }
            else printf("Wrong input\n\n");
            
        }
        else{
            printf("Wrong input type\n\n");
            int c;
            while((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    
    return 0;
}

int get_days_in_month(int month_n, int year){
    switch(month_n){
        case 1:
            return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        case 3:
        case 5:
        case 8:
        case 10:
            return 30;
        default:
            return 31;
    }
}

void print_header(){
    printf("Mo Tu We Th Fr \033[1;30mSa\033[0m \033[1;31mSu\033[0m\n");//gray for Sa, red for Su   
}

void print_spaces(int first_day){
    if(first_day == 0){
        for(int i = 6; i > 0; --i) printf("   ");
    }
    else 
        for(int i = 1; i < first_day; ++i) printf("   ");
}

void current_year_calendar(){
    int year = 0, month_n = 0, day = 0, weekday = 0, days_in_month = 0, first_day = 0;//31;
    const char* month;
    time_t current_time = time(NULL);
    struct tm* local_time = localtime(&current_time);

    year = local_time->tm_year + BEGIN_EPOCH;
    month_n = local_time->tm_mon;
    month = months[month_n];
    day = local_time->tm_mday;
    
    printf("\033[1;32mThe %d calendar, month of %s\n\033[0m",year,month);//font colour green and set to default
    print_header();

    //weekday = (local_time->tm_wday + 6) % 7 + 1;
    local_time->tm_mday = 1;
    mktime(local_time);
    weekday = local_time->tm_wday;
    first_day = weekday;
    print_spaces(first_day);
    days_in_month = get_days_in_month(month_n, year);

    for(int i = 1; i <= days_in_month; ++i){
        if(i == day){
            printf("\033[1;37;44m%2d\033[0m ",i);
        }
        else if((i + first_day - 1) % 7 == 0){
            printf("\033[1;31m%2d\033[0m ", i);
        }
        else if((i + first_day) % 7 == 0){
            printf("\033[1;30m%2d\033[0m ", i);
        }
        else printf("%2d ", i);

        if((weekday++) % 7 == 0) printf("\n");
    }
    printf("\n\n");
}

void print_custom_calendar(int* year){
    int days_in_month = 0, first_day = 0, weekday = 0;
    time_t time_stamp;
    struct tm* date;
    printf("\n\033[1;32mCalendar for %d\033[0m\n\n", *year);
    

    for(int month = 0; month < 12; ++month){
        time_stamp = time(NULL);
        date = localtime(&time_stamp);

        printf("\033[1;32m%s\033[0m\n", months[month]);
        days_in_month = get_days_in_month(month, *year);
        print_header();
        
        date->tm_year = *year - BEGIN_EPOCH;
        date->tm_mon = month;
        date->tm_mday = 1;
        mktime(date);
        weekday = date->tm_wday;
        first_day = weekday;
        print_spaces(weekday);

        for(int day = 1; day <= days_in_month; ++day){
            if((day + first_day - 1) % 7 == 0){
            printf("\033[1;31m%2d\033[0m ", day);
        }
        else if((day + first_day) % 7 == 0){
            printf("\033[1;30m%2d\033[0m ", day);
        }
        else printf("%2d ", day);

        if((weekday++) % 7 == 0) printf("\n");
        }

        printf("\n\n");
    }
}