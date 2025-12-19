#ifndef CONSTANTDEFS_H
#define CONSTANTDEFS_H

constexpr unsigned int pay_per_day {1400};
//express surcharge that takes effect if an order less than 2 days of work
constexpr double expr_surcharge {1.25};

enum Service
{
Photo_printing,
Film_devel,
Invalid_Service,
};

enum CompletionStatus
{
Created,
Assigned,
InProgress,
Completed,
Invalid_Status,
};

#endif