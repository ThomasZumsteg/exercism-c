#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

char *phone_number_clean(const char *number);
char *phone_number_get_area_code(const char *number);
char *phone_number_format(const char *number);

#endif
