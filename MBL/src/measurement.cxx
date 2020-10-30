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

#include <iostream>

#include "MBL/measurement.h"

namespace MBL {
    
Measurement::Measurement(const std::string& name, std::chrono::time_point<std::chrono::steady_clock> time_zero, Time_unit time_unit):
    m_name{name},
    m_time_zero{time_zero},
    m_time_unit{time_unit},
    m_start{std::chrono::steady_clock::now()},
    m_ended{false}
{}

void Measurement::record_start(const std::string& name)
{
    // this measurement is already running -> pass start or create new submeasurement
    for (auto&& submeasurement : m_submeasurements) {
        if (!submeasurement->m_ended) {
            // submeasurement still running (inner submeasurement start)
            submeasurement->record_start(name);
            return;
        }
    }
    // no submeasurement is running (create new submeasurement)
    m_submeasurements.emplace_back(new Measurement{name, m_time_zero, m_time_unit});
}

void Measurement::record_end()
{
    for (auto&& submeasurement : m_submeasurements) {
        if (!submeasurement->m_ended) {
            // submeasurement still running (inner submeasurement end)
            submeasurement->record_end();
            return;
        }
    }
    // all submeasurements has ended -> end this one
    m_end = std::chrono::steady_clock::now();
    m_ended = true;
}

float Measurement::time_to_float(const std::chrono::nanoseconds& time) {
    switch (m_time_unit)
    {
        case Time_unit::nanoseconds:
            return std::chrono::duration<float, std::nano>(time).count();
        case Time_unit::microseconds:
            return std::chrono::duration<float, std::micro>(time).count();
        case Time_unit::milliseconds:
            return std::chrono::duration<float, std::milli>(time).count();
        case Time_unit::seconds:
            return std::chrono::duration<float>(time).count();
        case Time_unit::minutes:
            return std::chrono::duration<float, std::ratio<60>>(time).count();
        case Time_unit::hours:
            return std::chrono::duration<float, std::ratio<3600>>(time).count();
        default:
            return 0.0f;
    }
}

void indent(std::ostream& os, int indent_level)
{
    for (int i = 0; i < indent_level; i++) {
        os << "  ";
    }
}

void Measurement::to_stream(std::stringstream& ss, int indent_level, bool last_element) {
    // open element
    indent(ss, indent_level);
    ss << "{" << std::endl;

    indent(ss, indent_level + 1);
    ss << "\"name\": \"" << m_name << "\"," << std::endl;
    
    indent(ss, indent_level + 1);
    ss << "\"start\": " << time_to_float(m_start - m_time_zero) << "," << std::endl;
    
    indent(ss, indent_level + 1);
    ss << "\"end\": " << time_to_float(m_end - m_time_zero) << "," << std::endl;
    
    indent(ss, indent_level + 1);
    ss << "\"elapsed time\": " << time_to_float(m_end - m_start) << "," << std::endl;

    indent(ss, indent_level + 1);
    ss << "\"submeasurements\": [" << std::endl;

    if (!m_submeasurements.empty()) {
        int i = 0;
        for (; i < m_submeasurements.size() - 1; i++) {
            m_submeasurements[i]->to_stream(ss, indent_level + 2, false);
        }
        m_submeasurements[i]->to_stream(ss, indent_level + 2, true); 
    }

    // close submeasurements
    indent(ss, indent_level + 1);
    ss << "]" << std::endl;
    
    // close element
    indent(ss, indent_level);
    if (last_element) {
        ss << "}" << std::endl;
    } else {
        ss << "}," << std::endl;
    }
}

std::string Measurement::to_json()
{
    std::stringstream ss;
    ss << "[" << std::endl;
    if (!m_submeasurements.empty()) {
        int i = 0;
        for (; i < m_submeasurements.size() - 1; i++) {
            m_submeasurements[i]->to_stream(ss, 1, false);
        }
        m_submeasurements[i]->to_stream(ss, 1, true);
    }
    ss << "]" << std::endl;

    return ss.str();
}

} // namespace MBL
