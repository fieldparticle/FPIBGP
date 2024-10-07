/*******************************************************************
%***      C PROPRIETARY SOURCE FILE IDENTIFICATION               ***
%*******************************************************************
% $Author: jb $
%
% $Date: 2023-05-03 15:30:42 -0400 (Wed, 03 May 2023) $
% $HeadURL: https://jbworkstation/svn/svnrootr5/svnvulcan/src/vulkan/DescriptorSSBO.cpp $
% $Id: DescriptorSSBO.cpp 28 2023-05-03 19:30:42Z jb $
%*******************************************************************
%***                         DESCRIPTION                         ***
%*******************************************************************
@doc
@module
			@author: Jackie Michael Bell<nl>
			COPYRIGHT <cp> Jackie Michael Bell<nl>
			Property of Jackie Michael Bell<rtm>. All Rights Reserved.<nl>
			This source code file contains proprietary<nl>
			and confidential information.<nl>


@head3 		Description. |
@normal


********************************************************************
%***                     SVN CHANGE RECORD                       ***
%*******************************************************************
%*$Revision: 28 $
%*
%*
%******************************************************************/

const float PI 			= 3.14159265359;
const uint npos= 4294967294;

// Params is generated by the applcation at each runtime.


// Cuboid is always square
const uint CWIDTH		= WIDTH;
const uint CHEIGHT		= WIDTH;
const uint CDEPTH		= WIDTH;
const uint FRM = 0;
const uint TO  = 1;


// For walls not yet implimented.
const float XMAX = WIDTH;
const float XMIN = 0.5f;
const float YMAX = HEIGHT;
const float YMIN = 0.5f;
const float ZMAX = DEPTH;
const float ZMIN = 0.5f;

// Debug flag compute - main
const float DEBUG01 	= 1.0;
// Debug flag compute - Detector
const float DEBUG02 	= 2.0;
// Debug flag compute- Collision parms
const float DEBUG03 	= 3.0;
// Debug flag - Vertex displacment 
const float DEBUG04 	= 4.0;

// Maximum number of corners
const uint MAX_OCCUPANCY 	= 8;


