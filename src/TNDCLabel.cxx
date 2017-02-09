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
#include "TNDCLabel.h"

ClassImp(ROOT6tools::TNDCLabel)

namespace ROOT6tools {

TNDCLabel::TNDCLabel() { }

TNDCLabel::TNDCLabel(double xmin, double ymin, double xmax, double ymax, const char *text):
    TPaveText(xmin, ymin, xmax, ymax, "NDC")
{
    SetBorderSize(0);
    SetFillStyle(0);
    SetTextFont(42);
    AddText(text);
}


TNDCLabel::~TNDCLabel() { }

} /* namespace ROOT6tools */
