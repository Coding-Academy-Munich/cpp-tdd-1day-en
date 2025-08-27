// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once

#include <string>
#include <vector>

namespace prime_factors
{

std::vector<long> compute_prime_factors(long n);

std::string format_primes(const std::vector<long>& primes);

void compute_and_write_primes(long n, std::ostream& os);

} // namespace prime_factors