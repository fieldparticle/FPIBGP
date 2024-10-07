
/*******************************************************************
%***      C PROPRIETARY SOURCE FILE IDENTIFICATION               ***
%*******************************************************************
% $Author: jb $
%
% $Date: 2023-06-12 16:17:58 -0400 (Mon, 12 Jun 2023) $
% $HeadURL: https://jbworkstation/svn/svnrootr5/svnvulcan/src_app/mps/main.cpp $
% $Id: main.cpp 31 2023-06-12 20:17:58Z jb $
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

#include "VulkanObj/VulkanApp.hpp"
#include "windows.h"
MsgStream			mout;
uint32_t DoStudy(ConfigObj* configVCube);
int main() try
{
	
	mout.Init("particle.log", "Particle");
	ConfigObj* config = new ConfigObj;
	std::filesystem::path cwd = std::filesystem::current_path();
	mout << "Working Directory :" << cwd.string().c_str() << ende;
	
	config->Create("mps.cfg");
	if (config->m_DoAuto == true)
	{
		config->m_TstFileVersion = 2;
		config->m_TstFileMinorVersion = 3;
		if (DoStudy(config))
			return 1;
	}
	else
	{
		config->m_TstFileVersion = 2;
		config->m_TstFileMinorVersion = 3;
		config->GetParticleSettingsV2();
		if (ParticleOnly(config))
			return 1;
	}
	return 0;
}
#if 1
catch (const std::exception& e)
{

	mout << "EXITING| TYPE:" << typeid(e).name() << " MSG:" << e.what() << ende;
	
	exit(1);
}
#endif
#include <iostream>
#include <filesystem>
uint32_t DoStudy(ConfigObj* config)
{
	
	namespace fs = std::filesystem;



	std::string path = config->m_TestDir;
	std::set<fs::path> sorted_by_name;
	std::vector<std::string> filename;

	for (auto& entry : fs::directory_iterator(path))
	{
		sorted_by_name.insert(entry.path());
		filename.push_back(entry.path().string());
	}
#if 0
	for (const auto& entry : sorted_by_name)
	{
		if ((entry.string().find("tst")) != std::string::npos)
			filename.push_back(entry.string());
	}
#endif
	uint32_t count = 0;

	//for (size_t ii = 0; ii < 4; ii++)
	for(size_t ii = 0; ii< filename.size();ii++)
	{
		++count;
		std::string::size_type pos = filename[ii].find("tst");
		size_t pt = 0;
		std::string pathtest{};
		pathtest = filename[ii];
	
		if ((pt= pathtest.find("tst")) != std::string::npos)
		{
			std::cout	<< "=======================" 
						<< filename[ii] 
						<< "=======================" << std::endl;
			std::cout << filename[ii] << std::endl;
			config->m_TestName.clear();
			config->m_TestName = filename[ii];
			if(config->m_TstFileVersion == 2)
				config->GetParticleSettingsV2();
			else
				config->GetParticleSettings();
			
			std::string hold = filename[ii].substr(0, pt);
			//config->m_AprFile = hold;
			config->m_DataFile = hold + "bin";
			mout << "Auto DataFile : " << config->m_DataFile << ende;
#ifdef PARTICLE_GRAPHICS_PIPE_ONLY			
			if (ParticleOnlyGraphics(config))
			{
				mout << "Auto - ParticleOnly failed" << ende;
				return 1;
			}
#endif

			if (ParticleOnly(config))
			{
				mout << "Auto - ParticleOnly failed" << ende;
				return 1;
			}
			

			if (QuitEvent == 1)
			return 0;
			
			

		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			return 0;
		}
	}
	

	return 0;
}