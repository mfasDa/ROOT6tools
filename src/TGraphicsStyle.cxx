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
#include "TGraphicsStyle.h"

#include <TH1.h>
#include <TGraphErrors.h>

namespace r6tools {
  
  TGraphicsStyle::TGraphicsStyle(Color_t color, Style_t marker):
  fColor(color),
  fMarker(marker)
  {
  }
  
  void TGraphicsStyle::DefineHistogram(TH1 *hist) const {
    hist->SetMarkerColor(fColor);
    hist->SetLineColor(fColor);
    hist->SetMarkerStyle(fMarker);
  }
  
  void TGraphicsStyle::DefineGraph(TGraphErrors *graph) const {
    graph->SetMarkerColor(fColor);
    graph->SetLineColor(fColor);
    graph->SetMarkerStyle(fMarker);
  }
  
} /* namespace r6tools */
