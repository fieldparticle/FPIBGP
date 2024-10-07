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
#ifndef VULKANOBJ_HPP
#define VULKANOBJ_HPP

class CommandObj;
class BaseObj;
class ResourceAtomic;
class PhysDevObj;

class VulkanObj
{
	public:
		struct ReportType
		{
			uint32_t Second;
			float		FrameRate;
			float		SecondPerFrame;
			double		ComputeExecutionTime;
			double		GraphicsExecutionTime;
			uint32_t	NumParticlesGenerated;
			uint32_t	NumParticlesLoaded;
			uint32_t	NumParticlesComputeCount;
			uint32_t	NumParticlesGraphicsCount;
			uint32_t	NumCollisionsGenerated;
			uint32_t	NumCollisionsComputeCount;
			uint32_t	ThreadCountComp;
			uint32_t	SideLengthLoaded;
			uint32_t	SideLengthGraphics;
			uint32_t	SideLengthCompute;
		};

		// Needs to quit from debug function which is outside the 
		// Obj
		
		std::vector< ReportType> m_ReportBuffer;
		uint32_t m_TimeStampDivisor = 0;
		uint32_t			m_quit_event = 0;
		uint32_t			m_CurrentBuffer = 0;
		uint32_t			m_FramesBuffered = 1;
		uint32_t			m_FrameNumber = 0;
		bool				m_FramebufferResized = false;
		uint32_t			m_Numparticles=0;
		uint32_t			m_Collisons=0;
		uint32_t			m_SideLength = 0;
		PhysDevObj*			m_QA = nullptr;
		uint16_t			m_SwapCount = 0;
		VmaAllocator		m_vmaAllocator = {};
		//float				m_dt=0;
		//int					createSemaphores();
		VkSemaphore s_imageAvailableSemaphore;
		VkSemaphore s_renderFinishedSemaphore;
		std::stack<BaseObj*> m_CleanupList;
		double m_TotalMemoryBytes = 0;

		void AddToCleanup(BaseObj* VObj)
		{
			m_CleanupList.push(VObj);
		}
		void CleanAll();

	
	//Permanent configuration variables.
	std::string			m_AppName;
	GLFWwindow* 		m_Window={};
	VkDevice 			m_LogicalDevice=VK_NULL_HANDLE;
	VkPhysicalDevice 	m_PhysicalDevice=VK_NULL_HANDLE;
	VkQueue 			m_GraphicsQueue=VK_NULL_HANDLE;
	VkQueue				m_ComputeQueue = VK_NULL_HANDLE;;
	VkQueue				m_PresentQueue = VK_NULL_HANDLE;;
	QueueFamilyIndices	m_QueueFamiliesIndexes;
	uint32_t 			m_GraphicsQueueIndex = 0;
	uint32_t				m_ComputeQueueIndex = 0;
	uint32_t				m_PresentQueueIndex =0;
	uint32_t			m_NumSwapImages = 0; 
	VkSurfaceKHR 		m_Surface = {};
	
	VkInstance 			m_Instance;
	VkDebugUtilsMessengerEXT 				m_DebugMessenger;
	VkDebugReportCallbackEXT  				m_ReportMessenger;
	PFN_vkDestroyDebugReportCallbackEXT		m_DDRCE;
	std::vector<VkDeviceQueueCreateInfo> 	m_QueueCreateInfos;
	
	public:
	ConfigObj*			m_CFG;


	VulkanObj() {};
	void InitImgui(VkDescriptorPool discriptorPool,
		VkRenderPass renderPass,
		uint32_t NumSwapImages);
	void		createSyncObjects();
	void		NameObject(VkObjectType objectType,
						uint64_t objectHandle, 
						const char* pObjectName);
	void AssignMarkerFunctions();
	void		NameStaticObjects();
	void		Create(ConfigObj* CFG);
	void		Create(ConfigObj* CFG, PhysDevObj* QA)
				{
					m_QA = QA;
					Create(CFG);
				}

	void		Cleanup(); 
    
	void		SetupDebugMessenger() ;
	void		DestroyReportUtilsMessengerEXT();
	void		CreateLogicalDevice(); 
	void		PopulateDebugMessengerCreateInfo(
					VkDebugUtilsMessengerCreateInfoEXT& createInfo) ;
	bool		IsPhysDevSuitable(VkPhysicalDevice PhysDev) ;
	bool		CheckPhysDevExtensionSupport(VkPhysicalDevice PhysDev) ;
	void		GetPhysDeviceFeatures();
	
	VkPhysicalDeviceLimits m_DevLimit{};
	VkPhysicalDeviceMemoryProperties m_DeviceMemory = {};
	VkPhysicalDeviceSparseProperties m_DevSProp{};
	VkPhysicalDeviceProperties m_DevProp{};
	void VMACreateDeviceBuffer(VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VkBuffer& buffer,
		VmaAllocation& allocation,
		std::string Name);
	void VMAMapMemory(VmaAllocation& allocation, void* data, size_t size);
	void VMACreateDeviceMemImage(VkMemoryPropertyFlags properties,
		VkImage& image,
		VmaAllocation& allocation,
		VmaAllocationCreateInfo& stagingAllocInfo,
		VkImageCreateInfo& imageCreateInfo,
		std::string Name);
	void		VMACreateStagingBuffer(VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VkBuffer& buffer,
		VmaAllocation& allocation,
		std::string Name);

	uint32_t	FindMemoryType(uint32_t typeFilter, 
					VkMemoryPropertyFlags properties) ;

	SwapChainSupportDetails		QueryPhysDevSwapChainSupport(VkPhysicalDevice PhysDev);
	VkResult					CreateReportUtilsMessengerEXT();


	static void		FramebufferResizeCallback(GLFWwindow* window,
						int width,
						int height)
	{
		auto app = reinterpret_cast<VulkanObj*>(glfwGetWindowUserPointer(window));
		app->m_FramebufferResized = true;
	}
		
	
	// Get Set--------------------------------------
	void SetCurrentBuffer(uint32_t CurrentBuffer)
	{
		m_CurrentBuffer = CurrentBuffer;
	}
	uint32_t GetCurrentBuffer()
	{
		return m_CurrentBuffer;
	}


	void SetGLFWWindow(GLFWwindow* window)
	{
		m_Window = window;
	}
	GLFWwindow* GetGLFWWindow()
	{
		return m_Window;
	}


	void SetLogicalDevice(VkDevice LogicalDevice)
	{
		m_LogicalDevice = LogicalDevice;
	}

	VkDevice GetLogicalDevice()
	{
		return m_LogicalDevice;
	}
	
	void SetPhysicalDevice(VkPhysicalDevice PhysicalDevice)
	{
		m_PhysicalDevice = PhysicalDevice;
	}
	VkPhysicalDevice GetPhysicalDevice()
	{
		return m_PhysicalDevice;
	}
	
	void SetGraphicsQueue(VkQueue GraphicsQueue)
	{
		m_GraphicsQueue = GraphicsQueue;
	}
	VkQueue GetGraphicsQueue()
	{
		return m_GraphicsQueue;
	}
	void SetPresentQueue(VkQueue PresentQueue)
	{
		m_PresentQueue = PresentQueue;
	}
	VkQueue GetPresentQueue()
	{
		return m_PresentQueue;
	}
	void SetComputeQueue(VkQueue ComputeQueue)
	{
		m_ComputeQueue = ComputeQueue;
	}
	VkQueue GetComputeQueue()
	{
		return m_ComputeQueue;
	}
	
	void SetSwapCount(uint16_t obj)
	{
		m_SwapCount = obj;
	}
	uint16_t GetSwapCount()
	{
		return m_SwapCount;
	}
	
	
	void SetSurface (VkSurfaceKHR obj)
	{
		m_Surface = obj;
	}
	VkSurfaceKHR GetSurface()
	{
		return m_Surface;
	}
	

	/*
	void Set (TYP obj)
	{
		m_ = obj;
	}
	Typ GetGraphicsQueue()
	{
		return m_;
	}
	*/
	
   };




#endif