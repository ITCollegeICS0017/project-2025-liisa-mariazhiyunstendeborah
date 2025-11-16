#ifndef CONSTANTDEFS_H
#define CONSTANTDEFS_H

constexpr unsigned int pay_per_day {1400};
constexpr double expr_surcharge {1.25};

enum Service
{
Photo_printing,
Film_devel,
};

enum CompletionStatus
{
Created,
Assigned,
InProgress,
Completed,
};

#endif