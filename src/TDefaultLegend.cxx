/****************************************************************************
 * Various helpers making life easier when working with ROOT6               *
 * Copyright (C) 2015  Markus Fasel, Lawrence Berkeley National Laboratory  *
 *                                                                          *
 * This program is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation, either version 3 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License        *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 ****************************************************************************/
#include "TDefaultLegend.h"

ClassImp(ROOT6tools::TDefaultLegend)

namespace ROOT6tools {

TDefaultLegend::TDefaultLegend() {
}

TDefaultLegend::TDefaultLegend(double xmin, double ymin, double xmax, double ymax):
    TLegend(xmin, ymin, xmax, ymax)
{
  SetBorderSize(0);
  SetFillStyle(0);
  SetTextFont(42);
}

TDefaultLegend::~TDefaultLegend() {
}

} /* namespace ROOT6tools */
