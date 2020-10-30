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

#include <fstream>
#include <iostream>

#include "MBL.h"

namespace MBL {

MBL::MBL(const std::string& filename, Time_unit time_unit):
    m_filename{filename},
    m_measurement{"root", std::chrono::steady_clock::now(), time_unit}
{}

MBL::~MBL()
{
    m_measurement.record_end(); // end root measurement
    
    std::ofstream file;
    file.open(m_filename);
    if (file.is_open()) {
        file << m_measurement.to_json() << std::endl;
        file.close();
    } else {
        std::cerr << "Cannot create file: " << m_filename << std::endl;
    }
}

} // namespace MBL
