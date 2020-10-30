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

#ifndef MBL_MBL_H_
#define MBL_MBL_H_

#include <chrono>
#include <stack>
#include <string>
#include <ratio>

#include "MBL/measure.h"
#include "MBL/measurement.h"

namespace MBL {

class MBL {
    std::string m_filename;
    Measurement m_measurement;

    friend class Measure;
public:
    MBL(const std::string& filename, Time_unit time_unit = Time_unit::seconds);
    ~MBL();
};

} // namespace MBL

#endif // MBL_MBL_H_
