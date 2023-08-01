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
#include <TClass.h>
#include "TAxisFrame.h"

ClassImp(ROOT6tools::TAxisFrame)

namespace ROOT6tools {

TAxisFrame::TAxisFrame() : TH1F() {

}

TAxisFrame::TAxisFrame(const char *name, const char *xtitle, const char *ytitle, double xmin, double xmax, double ymin, double ymax):
    TH1F(name, "", 100, xmin, xmax)
{
    IsA()->SetName("TH1F"); // Fake type name to be the base class
    SetDirectory(nullptr);
    SetStats(false);
    SetXTitle(xtitle);
    SetYTitle(ytitle);
    GetYaxis()->SetRangeUser(ymin, ymax);
}

TAxisFrame::~TAxisFrame() {
}

} /* namespace ROOT6tools */
