// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once

#ifndef SALARIES_COMPLETED_H
#define SALARIES_COMPLETED_H

#include <string>
#include <vector>

namespace salaries
{

struct TaxedSalary
{
    double taxes{};
    double salary_after_taxes{};
};

double process_salary(
    int day_number, double salary_per_day, const char* employee_name,
    std::vector<double>& all_salaries
);

TaxedSalary compute_taxed_salary(int day_number, double salary_per_day);

double compute_salary_before_taxes(int day_number, double salary_per_day);

double compute_taxes(double salary_before_taxes);

double compute_tax_rate(double salary);

void store_salary(double salary, std::vector<double>& all_salaries);

void print_salary(int day_number, double salary_per_day, const char* employee_name);

const std::string& compute_day_of_week_name(int day_number);
} // namespace salaries

#endif