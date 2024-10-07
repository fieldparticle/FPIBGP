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

TimerObj* timerstep;
void Doperf(DrawObj* DrawInstance, VulkanObj* VulkanWin, ResourceGraphicsContainer* rgc, ResourceComputeContainer* rcc,size_t aprCount)
{
	ConfigObj* cfg = VulkanWin->m_CFG;
	std::string filename = cfg->m_AprFile;
	
#ifndef NDEBUG
	filename = filename + "D.csv";
#else
	filename = filename + "R.csv";
#endif

	

		float totFps = 0.0;
		float totTime = 0.0;
		std::ofstream ostrm(filename);
		if (!ostrm.is_open())
		{
			std::string rpt = "Failed to open report file:" + filename;
			throw std::runtime_error(rpt.c_str());
		}

		//
		ostrm << "time,fps,cpums,cms,gms,expectedp,loadedp,shaderp_comp,shaderp_grph, expectedc,shaderc,threadcount, sidelen,density,PERR,CERR" << std::endl;
		for (size_t ii = 0; ii < aprCount-1; ii++)
		{
			
			totFps += VulkanWin->m_ReportBuffer[ii].FrameRate;
			totTime += VulkanWin->m_ReportBuffer[ii].Second;
			uint32_t partErr = 0;
			uint32_t colErr = 0;
			ostrm	<< VulkanWin->m_ReportBuffer[ii].Second << ","				// time
					<< VulkanWin->m_ReportBuffer[ii].FrameRate << ","			// fps
					<< 1.0f/ VulkanWin->m_ReportBuffer[ii].FrameRate << ","		 // cpums: cpu time
					<< VulkanWin->m_ReportBuffer[ii].ComputeExecutionTime << ","	// cms: compute ms
					<< VulkanWin->m_ReportBuffer[ii].GraphicsExecutionTime << ","	// gms: graphics ms				
					<< cfg->m_partcount << ","										// expectedp: frm tst - generated
					<< VulkanWin->m_Numparticles-1 << ","							// loadedp: loaded into rccdApp
					<< VulkanWin->m_ReportBuffer[ii].NumParticlesComputeCount << ","// shaderp_comp: counted from compute
					<< VulkanWin->m_ReportBuffer[ii].NumParticlesGraphicsCount << ","							// shaderp_grp: counted from graphics
					<< cfg->m_colcount << ","										// expectedc: expected collisions
					<< VulkanWin->m_ReportBuffer[ii].NumCollisionsComputeCount << ","							// shaderc: compute counted collisions
					<< VulkanWin->m_ReportBuffer[ii].ThreadCountComp << ","									// threadcount: number of threads compute
					<< VulkanWin->m_SideLength << ","								// sidelen
					<< cfg->m_density << ","										// density
					<< partErr << ","
					<< colErr 
					<< std::endl;
#ifndef NDEBUG
				if(VulkanWin->m_ReportBuffer[ii].NumParticlesComputeCount != VulkanWin->m_Numparticles-1)
				{
					
					std::ostringstream  objtxt;
					objtxt << "Compute counted particles not equal to loaded particles:Expected:" 
						<< VulkanWin->m_Numparticles-1 << ":Counted:" 
						<< VulkanWin->m_ReportBuffer[ii].NumParticlesComputeCount << std::ends;
					throw std::runtime_error(objtxt.str());;
				}
				if(VulkanWin->m_ReportBuffer[ii].NumCollisionsComputeCount !=  cfg->m_colcount)
				{
					
					std::ostringstream  objtxt;
					objtxt << "Compute counted collisions not equal to calulated collisons:Expected:" 
						<< cfg->m_colcount << ":Counted:" 
						<< VulkanWin->m_ReportBuffer[ii].NumCollisionsComputeCount << std::ends;
					throw std::runtime_error(objtxt.str());;
				}
#endif

		}
		ostrm.flush();
		ostrm.close();

	std::cout << "\n\n\n\n================= Done Perf ======================= \n\n\n\n" << std::endl;

}

int Loop(DrawObj* DrawInstance, VulkanObj* VulkanWin, ResourceGraphicsContainer* rgc, ResourceComputeContainer* rcc)
{
	float				deltaTime = 0.0f;
	float				lastFrame = 0.0f;
	uint32_t			quit_event = 0;

	ConfigObj* cfg = VulkanWin->m_CFG;
	uint32_t AutoWait = 0;
	if (cfg->m_AutoTimeOut != 0)
		AutoWait = cfg->m_AutoTimeOut;
	else
		AutoWait = 61;
	VulkanWin->m_ReportBuffer.resize(AutoWait);
	

	size_t aprCount = 0;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	timerstep = new TimerObj;
	
	SetCallBacks(VulkanWin);


	try
	{
		// While window is open.
	
		
		while (!glfwWindowShouldClose(VulkanWin->GetGLFWWindow())
			&& glfwGetKey(VulkanWin->GetGLFWWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
		{
			VulkanWin->m_ReportBuffer[aprCount].SecondPerFrame = timerstep->elapsed();
			timerstep->reset();
			//Esc normal termination
			if (QuitEvent)
			{
				VulkanWin->m_quit_event = 1;
				return 0;
			};

			if (VulkanWin->m_quit_event > 1)
			{
				std::ostringstream  objtxt;
				objtxt << "Quit Loop Error number:" << VulkanWin->m_quit_event <<  std::ends;
				throw std::runtime_error(objtxt.str());
			};
			float currentBuffer = static_cast<float>(glfwGetTime());
			deltaTime = currentBuffer - lastFrame;
			lastFrame = currentBuffer;

			
			// Test for frame number end.
			if (cfg->m_EndFrame != 0)
			{
				if (VulkanWin->m_FrameNumber >= cfg->m_EndFrame)
					break;

			};
			// Poll window events.
			glfwPollEvents();
			// Draw frame.
			DrawInstance->DrawFrame();
			if(Extflg == true)
				throw std::runtime_error("External Flag Exit.");

			VulkanWin->m_FrameNumber++;
			double currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0)
			{
				if (aprCount < AutoWait )
				{
					VulkanWin->m_ReportBuffer[aprCount].Second = aprCount;
					VulkanWin->m_ReportBuffer[aprCount].FrameRate = static_cast<float>(nbFrames);
					VulkanWin->m_ReportBuffer[aprCount].SecondPerFrame = static_cast<float>(aprCount);
					VulkanWin->m_ReportBuffer[aprCount].ComputeExecutionTime =
						DrawInstance->m_ComputeCommandObj->m_ExecutionTime;
					VulkanWin->m_ReportBuffer[aprCount].GraphicsExecutionTime =
						DrawInstance->m_GraphicsCommandObj->m_ExecutionTime;

					for (int ii = 0; ii < rgc->m_DRList.size(); ii++)
						rgc->m_DRList[ii]->AskObject(aprCount);

					for (int ii = 0; ii < rcc->m_DRList.size(); ii++)
						rcc->m_DRList[ii]->AskObject(aprCount);

					aprCount++;
				}
#if 0
				if (AutoWait == 0 && cfg->m_DoAuto )
				{
					aprCount++;
					
					Doperf(DrawInstance, VulkanWin, rgc,rcc,aprCount);
					if (VulkanWin->m_FrameNumber >= AutoWait)
					{
						break;
					}
				}
#endif
				if (aprCount == AutoWait && AutoWait != 0)
				{
					aprCount++;
					Doperf(DrawInstance, VulkanWin, rgc, rcc, aprCount);
					if (cfg->m_Stopondata)
					{
						
						break;
					}
					
				}
				

				std::cout << "Seconds:" << aprCount << " FrameNumber:" << VulkanWin->m_FrameNumber << " FRate:" << 1000.0 / double(nbFrames) << " ms/F, " << " FPS:" << nbFrames << " F/s." << std::endl;
				nbFrames = 0;
				lastTime += 1.0;
			}
			Sleep(cfg->m_FrameDelay);
			vkDeviceWaitIdle(VulkanWin->GetLogicalDevice());
		}

		vkDeviceWaitIdle(VulkanWin->GetLogicalDevice());
		
	}
	catch (const std::exception& e)
	{
		mout << "STANDARD ERROR:" << e.what() << ende;
		mout << "End at frame:" << VulkanWin->m_FrameNumber << ende;
		return EXIT_FAILURE;
	}

	mout << "End at frame:" << VulkanWin->m_FrameNumber << ende;
	
	return 0;
};
