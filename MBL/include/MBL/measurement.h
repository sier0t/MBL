/************************************************************************
 * Copyright (C) 2020 Karol Sierocinski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.                           
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ************************************************************************/

#ifndef MBL_MEASUREMENT_H_
#define MBL_MEASUREMENT_H_

#include <chrono>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "MBL_fwd.h"
#include "time_unit.h"

namespace MBL {

class Measurement {
    Time_unit m_time_unit;
    std::string m_name;

    const std::chrono::time_point<std::chrono::steady_clock> m_time_zero;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_end;

    std::vector<std::unique_ptr<Measurement>> m_submeasurements;
    
    bool m_ended;

    float time_to_float(const std::chrono::nanoseconds& time);
    void to_stream(std::stringstream& ss, int indent_level, bool last_element);

public:
    Measurement(const std::string& name, std::chrono::time_point<std::chrono::steady_clock> time_zero, Time_unit time_unit);
    void record_start(const std::string& name);
    void record_end();
    
    std::string to_json();
};

} // namespace MBL

#endif // MBL_MEASUREMENT_H_
