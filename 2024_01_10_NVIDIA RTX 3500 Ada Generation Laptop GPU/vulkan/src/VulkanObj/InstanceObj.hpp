/*******************************************************************
%***      C PROPRIETARY SOURCE FILE IDENTIFICATION               ***
%*******************************************************************
% $Author: jb $
%
% $Date: 2023-06-12 16:17:58 -0400 (Mon, 12 Jun 2023) $
% $HeadURL: https://jbworkstation/svn/svnrootr5/svnvulcan/src/vulkan/VAPhysicalDevice.cpp $
% $Id: VAPhysicalDevice.cpp 31 2023-06-12 20:17:58Z jb $
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
%*$Revision: 31 $
%*
%*
%******************************************************************/

#ifndef INSTANCEOBJ_HPP
#define INSATCNEOBJ_HPP

class InstanceObj : public BaseObj
{
public:
	ConfigObj* m_CO;
	void InitWindow();

	InstanceObj(VulkanObj* App, std::string Name) : BaseObj(Name, 0, App) {};
	void Create() 
	{
		InitWindow();
		CreateInstance();
		m_App->AssignMarkerFunctions();
		m_App->SetupDebugMessenger();
		m_App->CreateReportUtilsMessengerEXT();
		CreateSurface();
	};
	std::vector<const char*> GetRequiredInstanceExtensions();
	bool CheckValidationLayerSupport();
	void CreateInstance();
	
	void CreateSurface();
	void Cleanup() {};


};

#endif