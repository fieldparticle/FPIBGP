/*******************************************************************
%***      C PROPRIETARY SOURCE FILE IDENTIFICATION               ***
%*******************************************************************
% $Author: jb $
%
% $Date: 2023-06-12 16:17:58 -0400 (Mon, 12 Jun 2023) $
% $HeadURL: https://jbworkstation/svn/svnrootr5/svnvulcan/src/vulkan/VulkanObj.hpp $
% $Id: VulkanObj.hpp 31 2023-06-12 20:17:58Z jb $
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
#include "VulkanObj/TimerObj.hpp"
#include "VulkanObj/Core.hpp"
#include "VulkanObj/VulkanDefines.hpp"
#include "VulkanObj/ConfigObj.hpp"
#include "VulkanObj/BaseObj.hpp"
#include "VulkanObj/VulkanObj.hpp"
#include "VulkanObj/SyncObj.hpp" // Needs obj
#include "VulkanObj/SwapChainObj.hpp"
#include "VulkanObj/Resource.hpp"
#include "VulkanObj/ImageObject.hpp"
#include "VulkanObj/RenderPassObj.hpp" // Needs obj
#include "VulkanObj/FrameBufferObj.hpp"// Needs obj
#include "VulkanObj/ContainerObj.hpp" 
#include "VulkanObj/PipelineObj.hpp"
#include "VulkanObj/CommandObj.hpp"
#include "VulkanObj/CommandPoolObj.hpp"
#include "VulkanObj/DrawObj.hpp"
#include "VulkanObj/Input.hpp"
#include "VulkanObj/PhysDevObj.hpp"
#include "VulkanObj/InstanceObj.hpp"
#include "VulkanObj/ResourceVertexObj.hpp"
#include "particleOnly/ParticleOnly.hpp"
void MemStats(VulkanObj* vulkanObj);

#include <glm/glm.hpp>
//#include "objloader.hpp"
#if 0
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
//#include "LoadWavefrontFile.hpp"
#endif


extern bool Extflg;
int Loop(DrawObj* DrawInstance, VulkanObj* VulkanWin, ResourceGraphicsContainer* rgc, ResourceComputeContainer* rcc);
int ParticleOnly(ConfigObj* configVCube);
int ParticleBoundary(ConfigObj* configVCube);
int ParticleBoundaryV2(ConfigObj* configVCube);
int glsl(std::vector<std::string>& InputArgs, std::vector<char>& OutPutSPV);
int ParticleOnlyGraphics(ConfigObj* configVCube);
