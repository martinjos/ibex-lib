/*---------------------------------------------------------------------------------
 * 
 * BOX Consistency 
 * ---------------
 *
 * Copyright (C) 2007-2009 Gilles Chabert
 * 
 * This file is part of IBEX.
 *
 * IBEX is free software; you can redistribute it and/or modify it under the terms of 
 * the GNU General Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 *
 * IBEX is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with IBEX; 
 * if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 * Boston, MA 02110-1301, USA 
 *
 --------------------------------------------------------------------------------*/

#include "IbexBox.h"
#include "IbexBoxNarrow.h"
#include "IbexPropagation.h"

namespace ibex {

Box::Box(const System& sys, REAL propag_ratio, REAL narrow_ratio, bool incremental) : 
  Operator(sys.space), 
  Propagation(ContractorList(ToBoxNarrow(narrow_ratio),sys),sys.space, propag_ratio,incremental)
  
{ }
 
Box::Box(const Box& b) : Operator(b.space), Propagation(b) { }

} // end namespace