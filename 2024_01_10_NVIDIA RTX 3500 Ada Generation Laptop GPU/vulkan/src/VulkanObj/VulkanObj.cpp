/*******************************************************************
%***      C PROPRIETARY SOURCE FILE IDENTIFICATION               ***
%*******************************************************************
% $Author: jb $
%
% $Date: 2023-06-12 16:17:58 -0400 (Mon, 12 Jun 2023) $
% $HeadURL: https://jbworkstation/svn/svnrootr5/svnvulcan/src/vulkan/VulkanObject.cpp $
% $Id: VulkanObject.cpp 31 2023-06-12 20:17:58Z jb $
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

// This is done once in a cpp file cause it generates functions and data.
#define STB_IMAGE_IMPLEMENTATION
#define VMA_IMPLEMENTATION
#include "VulkanObj/VulkanApp.hpp"
#if 0
void VulkanObj::InitImgui(VkDescriptorPool discriptorPool,
						VkRenderPass renderPass, 
						uint32_t NumSwapImages)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForVulkan(m_Window, true);
	ImGui_ImplVulkan_InitInfo init_info = {};
	init_info.Instance = m_Instance;
	init_info.PhysicalDevice = m_PhysicalDevice;
	init_info.Device = m_LogicalDevice;
	init_info.QueueFamily = m_ComputeQueueIndex;
	init_info.Queue = m_GraphicsQueue;
	init_info.PipelineCache = VK_NULL_HANDLE;
	init_info.DescriptorPool = discriptorPool;
	init_info.RenderPass = renderPass;
	init_info.Subpass = 0;
	init_info.MinImageCount = 2;
	init_info.ImageCount = NumSwapImages;
	init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
	init_info.Allocator = VK_NULL_HANDLE;
	init_info.CheckVkResultFn = VK_NULL_HANDLE;
	//ImGui_ImplVulkan_Init(&init_info);




}
#endif

void VulkanObj::Create(ConfigObj* CFG)
{
	m_CFG = CFG;
	m_FramesBuffered = m_CFG->m_FramesBuffered;

	
	
}
//
//
//
//
void VulkanObj::CleanAll()
{
	BaseObj* baseObj;
	while (!m_CleanupList.empty())
	{

		baseObj = m_CleanupList.top();
		baseObj->Cleanup();
		m_CleanupList.pop();
	}
	//Cleanup();
}

void VulkanObj::Cleanup() 
{
#if 0
	if (!m_vmaAllocator->)
	{

		std::ostringstream  objtxt;
		objtxt << "Error in:" << "VulkanObj::Cleanup:vmaMemoryPolls Not empty -> memory leak" <<
			 std::ends;
		throw std::runtime_error(objtxt.str());
	}
#endif
	vmaDestroyAllocator(m_vmaAllocator);
	
	
	if (m_CFG->m_EnableValidationLayers)
	{
		DestroyReportUtilsMessengerEXT();
		DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
	}
	vkDestroyDevice(m_LogicalDevice, nullptr);
	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	vkDestroyInstance(m_Instance, nullptr);
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
