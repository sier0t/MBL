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

#include "MBL.h"

#include "MBL/measure.h"

namespace MBL {

Measure::Measure(MBL& mbl, const std::string& name):
    m_mbl{mbl}
{
    m_mbl.m_measurement.record_start(name);
}

Measure::~Measure()
{
    m_mbl.m_measurement.record_end();
}

} // namespace MBL
