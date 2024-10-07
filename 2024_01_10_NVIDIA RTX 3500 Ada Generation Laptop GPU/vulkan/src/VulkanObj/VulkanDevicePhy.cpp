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

#include "VulkanObj/VulkanApp.hpp"
#if 0
void VulkanObj::CreatePhysicalDevice() 
{
	
	
	vkEnumeratePhysicalDevices(m_Instance, &m_QA->m_DeviceCount, nullptr);

	if (m_QA->m_DeviceCount == 0)
	{
		throw std::runtime_error("vkEnumeratePhysicalDevices number of devices is zero.");
	}

	
	m_QA->m_Devices.resize(m_QA->m_DeviceCount);
	
	
	vkEnumeratePhysicalDevices(m_Instance, &m_QA->m_DeviceCount, m_QA->m_Devices.data());
	for (const auto& device : m_QA->m_Devices)
	{
		
		

		vkGetPhysicalDeviceProperties(device, &m_QA->m_Properties);
		uint32_t ver = VK_VERSION_MAJOR(m_QA->m_Properties.apiVersion);
		uint32_t ver2 = VK_VERSION_MINOR(m_QA->m_Properties.apiVersion);;

		mout << "Device Available #:" << m_QA->m_Properties.deviceID << " is:" << m_QA->m_Properties.deviceName <<
			" API Version:" << ver << "." << ver2 << ende;
		
		
		if (strcmp(m_QA->m_Properties.deviceName, m_CFG->m_PhysDevice.c_str()) == 0)
		{
			mout << "Looking for:" << m_CFG->m_PhysDevice.c_str() << " Finding:" << m_QA->m_Properties.deviceName << ende;
			if (IsPhysDevSuitable(device))
			{
				mout << "Device Selected #:" <<
					m_QA->m_Properties.deviceID << " is:" << m_QA->m_Properties.deviceName << ende;
				m_PhysicalDevice = device;
				
				break;
			}
			else
			{
				mout << "No Match:" << m_CFG->m_PhysDevice.c_str() << " Finding:" << properties.deviceName << ende;

			}

		}
		else
		{
			
			mout << "Requested device not found Default Device Selected #:" <<
				m_QA->m_Properties.deviceID << " is:" << m_QA->m_Properties.deviceName << ende;
			if (IsPhysDevSuitable(device))
			{
				m_PhysicalDevice = device;
				break;
			}

		}

	}
	

	if (m_PhysicalDevice == VK_NULL_HANDLE) 
	{
		throw std::runtime_error("Failed to find a suitable GPU!");
	}

	GetPhysDeviceLimits();
	//GetPhysDeviceFeatures(physicalDevice);
}

//
//
//
//
bool VulkanObj::CheckPhysDevExtensionSupport(VkPhysicalDevice PhysDev)
{
	uint32_t extensionCount;
	
	vkEnumerateDeviceExtensionProperties(PhysDev, nullptr, &extensionCount, nullptr);
	
	
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(PhysDev, nullptr, &extensionCount, availableExtensions.data());
	if (m_CFG->m_SaveExtensions)
	{
		std::ofstream file("DeviceExtensions.log", std::ios::out | std::ios::binary);
		for (uint32_t i = 0; i < availableExtensions.size(); i++)
		{
			file << availableExtensions[i].extensionName << std::endl;
		}
		file.close();
	}

	std::set<std::string> requiredExtensions(m_CFG->m_DeviceExtensions.begin(),
		m_CFG->m_DeviceExtensions.end());

	for (const auto& extension : availableExtensions) 
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}	
//
//
//
//
SwapChainSupportDetails VulkanObj::QueryPhysDevSwapChainSupport(VkPhysicalDevice PhysDev)
{
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysDev, m_Surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysDev, m_Surface, &formatCount, nullptr);

    if (formatCount != 0) 
	{
        details.formats.resize(formatCount);
		
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysDev, m_Surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
	
    vkGetPhysicalDeviceSurfacePresentModesKHR(PhysDev, m_Surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) 
	{
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(PhysDev, m_Surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}
//
//
//
// 
bool VulkanObj::IsPhysDevSuitable(VkPhysicalDevice PhysDev)
{

	QueueFamilyIndices indices = FindPhysDevQueueFamilies(PhysDev);

	bool extensionsSupported = CheckPhysDevExtensionSupport(PhysDev);

	bool swapChainAdequate = false;
	if (extensionsSupported)
	{
		SwapChainSupportDetails swapChainSupport = 
			QueryPhysDevSwapChainSupport(PhysDev);
		swapChainAdequate = !swapChainSupport.formats.empty() 
				&& !swapChainSupport.presentModes.empty();
	}

	
	
	
	VkPhysicalDeviceShaderAtomicFloatFeaturesEXT supportedatomics{};
	supportedatomics.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT;
	supportedatomics.pNext = nullptr;


	VkPhysicalDeviceFeatures2 atomicsfeatures{};
	atomicsfeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	atomicsfeatures.pNext = &supportedatomics;
	
	vkGetPhysicalDeviceFeatures2(PhysDev, &atomicsfeatures);

	VkPhysicalDeviceShaderSMBuiltinsFeaturesNV builtins{};
	builtins.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
	builtins.pNext = nullptr;
	VkPhysicalDeviceShadingRateImageFeaturesNV fragFeatures{};
	fragFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV;
	fragFeatures.pNext = nullptr;

	VkPhysicalDeviceFeatures2 otherfeatures{};
	otherfeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	otherfeatures.pNext = &fragFeatures;
	vkGetPhysicalDeviceFeatures2(PhysDev, &otherfeatures);

	otherfeatures={};
	otherfeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	otherfeatures.pNext = &builtins;
	vkGetPhysicalDeviceFeatures2(PhysDev, &otherfeatures);


	VkPhysicalDeviceFeatures supportedFeatures{};
	vkGetPhysicalDeviceFeatures(PhysDev, &supportedFeatures);
	
		
	mout << "Extension Supported:" << extensionsSupported 
		 << " swapChainAdequate:" << swapChainAdequate 
		 << " supportedFeatures.samplerAnisotropy:" << supportedFeatures.samplerAnisotropy
		 << " fragmentStoresAndAtomics:" << supportedFeatures.fragmentStoresAndAtomics << ende;
	return indices.isComplete() &&
		extensionsSupported &&
		swapChainAdequate &&
		supportedFeatures.samplerAnisotropy &&
		supportedFeatures.fragmentStoresAndAtomics;
	//&&
//		supportedatomics.shaderBufferFloat32AtomicAdd;
	
}
//
//
//
//
QueueFamilyIndices VulkanObj::FindPhysDevQueueFamilies(VkPhysicalDevice PhysDev)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(PhysDev, &queueFamilyCount, nullptr);

	
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

	vkGetPhysicalDeviceQueueFamilyProperties(PhysDev, &queueFamilyCount, queueFamilies.data());



	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		mout << "Grapics Family Index" << ende;
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			mout << "->Graphics Family Index :" << i << ende;

		else if (queueFamily.queueFlags& VK_QUEUE_COMPUTE_BIT)
			mout << "->Compute Family Index :" << i << ende;

		else if (queueFamily.queueFlags& VK_QUEUE_TRANSFER_BIT)
			mout << "->Transfer Family Index :" << i << ende;
		else
			mout << "->Unknown Family Index :" << i << ende;


		if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT))
		{
			indices.graphicsFamily = i;
		}

		if ((queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT))
		{
			indices.computeFamily = i;
		}
		VkBool32 presentSupport = false;
	
		vkGetPhysicalDeviceSurfaceSupportKHR(PhysDev, i, m_Surface, &presentSupport);

		if (presentSupport && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT))
		{
			indices.presentFamily = i;
		}

		if (indices.isComplete())
		{
			break;
		}

		i++;
	}
	return indices;
}
void VulkanObj::GetPhysDeviceFeatures()
{
	VkPhysicalDeviceFeatures devFeat{};
	devFeat.fragmentStoresAndAtomics=true;
	vkGetPhysicalDeviceFeatures(m_PhysicalDevice,&devFeat);
	/*
	if (m_SaveExtensions)
	{
	
		
		std::ofstream file("PhysicalFeaturess.log", std::ios::out | std::ios::binary);
    file << "robustBufferAccess:" <<  robustBufferAccess <<  std::endl;
    file << "fullDrawIndexUint32:" <<  fullDrawIndexUint32 <<  std::endl;
    file << "imageCubeArray:" <<  imageCubeArray <<  std::endl;
    file << "independentBlend:" <<  independentBlend <<  std::endl;
    file << "geometryShader:" <<  geometryShader <<  std::endl;
    file << "tessellationShader:" <<  tessellationShader <<  std::endl;
    file << "sampleRateShading:" <<  sampleRateShading <<  std::endl;
    file << "dualSrcBlend:" <<  dualSrcBlend <<  std::endl;
    file << "logicOp:" <<  logicOp <<  std::endl;
    file << "multiDrawIndirect:" <<  multiDrawIndirect <<  std::endl;
    file << "drawIndirectFirstInstance:" <<  drawIndirectFirstInstance <<  std::endl;
    file << "depthClamp:" <<  depthClamp <<  std::endl;
    file << "depthBiasClamp:" <<  depthBiasClamp <<  std::endl;
    file << "fillModeNonSolid:" <<  fillModeNonSolid <<  std::endl;
    file << "depthBounds:" <<  depthBounds <<  std::endl;
    file << "wideLines:" <<  wideLines <<  std::endl;
    file << "largePoints:" <<  largePoints <<  std::endl;
    file << "alphaToOne:" <<  alphaToOne <<  std::endl;
    file << "multiViewport:" <<  multiViewport <<  std::endl;
    file << "samplerAnisotropy:" <<  samplerAnisotropy <<  std::endl;
    file << "textureCompressionETC2:" <<  textureCompressionETC2 <<  std::endl;
    file << "textureCompressionASTC_LDR:" <<  textureCompressionASTC_LDR <<  std::endl;
    file << "textureCompressionBC:" <<  textureCompressionBC <<  std::endl;
    file << "occlusionQueryPrecise:" <<  occlusionQueryPrecise <<  std::endl;
    file << "pipelineStatisticsQuery:" <<  pipelineStatisticsQuery <<  std::endl;
    file << "vertexPipelineStoresAndAtomics:" <<  vertexPipelineStoresAndAtomics <<  std::endl;
    file << "fragmentStoresAndAtomics:" <<  fragmentStoresAndAtomics <<  std::endl;
    file << "shaderTessellationAndGeometryPointSize:" <<  shaderTessellationAndGeometryPointSize <<  std::endl;
    file << "shaderImageGatherExtended:" <<  shaderImageGatherExtended <<  std::endl;
    file << "shaderStorageImageExtendedFormats:" <<  shaderStorageImageExtendedFormats <<  std::endl;
    file << "shaderStorageImageMultisample:" <<  shaderStorageImageMultisample <<  std::endl;
    file << "shaderStorageImageReadWithoutFormat:" <<  shaderStorageImageReadWithoutFormat <<  std::endl;
    file << "shaderStorageImageWriteWithoutFormat:" <<  shaderStorageImageWriteWithoutFormat <<  std::endl;
    file << "shaderUniformBufferArrayDynamicIndexing:" <<  shaderUniformBufferArrayDynamicIndexing <<  std::endl;
    file << "shaderSampledImageArrayDynamicIndexing:" <<  shaderSampledImageArrayDynamicIndexing <<  std::endl;
    file << "shaderStorageBufferArrayDynamicIndexing:" <<  shaderStorageBufferArrayDynamicIndexing <<  std::endl;
    file << "shaderStorageImageArrayDynamicIndexing:" <<  shaderStorageImageArrayDynamicIndexing <<  std::endl;
    file << "shaderClipDistance:" <<  shaderClipDistance <<  std::endl;
    file << "shaderCullDistance:" <<  shaderCullDistance <<  std::endl;
    file << "shaderFloat64:" <<  shaderFloat64 <<  std::endl;
    file << "shaderInt64:" <<  shaderInt64 <<  std::endl;
    file << "shaderInt16:" <<  shaderInt16 <<  std::endl;
    file << "shaderResourceResidency:" <<  shaderResourceResidency <<  std::endl;
    file << "shaderResourceMinLod:" <<  shaderResourceMinLod <<  std::endl;
    file << "sparseBinding:" <<  sparseBinding <<  std::endl;
    file << "sparseResidencyBuffer:" <<  sparseResidencyBuffer <<  std::endl;
    file << "sparseResidencyImage2D:" <<  sparseResidencyImage2D <<  std::endl;
    file << "sparseResidencyImage3D:" <<  sparseResidencyImage3D <<  std::endl;
    file << "sparseResidency2Samples:" <<  sparseResidency2Samples <<  std::endl;
    file << "sparseResidency4Samples:" <<  sparseResidency4Samples <<  std::endl;
    file << "sparseResidency8Samples:" <<  sparseResidency8Samples <<  std::endl;
    file << "sparseResidency16Samples:" <<  sparseResidency16Samples <<  std::endl;
    file << "sparseResidencyAliased:" <<  sparseResidencyAliased <<  std::endl;
    file << "variableMultisampleRate:" <<  variableMultisampleRate <<  std::endl;
    file << "inheritedQueries:" <<  inheritedQueries <<  std::endl;

*/	
	
}
#endif