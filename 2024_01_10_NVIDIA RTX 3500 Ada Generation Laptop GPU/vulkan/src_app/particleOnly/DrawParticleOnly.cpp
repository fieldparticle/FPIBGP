/*******************************************************************
%***      C PROPRIETARY SOURCE FILE IDENTIFICATION               ***
%*******************************************************************GPO
% $Author: jb $
%
% $Date: 2023-06-12 16:17:58 -0400 (Mon, 12 Jun 2023) $
% $HeadURL: https://jbworkstation/svn/svnrootr5/svnvulcan/src_app/mfpm/DrawObj.cpp $
% $Id: DrawObj.cpp 31 2023-06-12 20:17:58Z jb $
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
///FIXX THIS
void DrawParticleOnly::Create(CommandPoolObj* CPL,
	SwapChainObj* SCO,
	RenderPassObj* RPO,
	FrameBufferObj* FBO,
	SyncObj* SO)
{
	m_CPL = CPL;
	m_SCO = SCO;
	m_FBO = FBO; 
	m_SO = SO;
	m_ComputeCommandObj = m_CPL->GetCommandObjByName("CommandParticleCompute");
	m_GraphicsCommandObj = m_CPL->GetCommandObjByName("CommandObjParticleGraphics");
	m_Graphicslst = m_GraphicsCommandObj->m_RCO->m_DRList;
	m_Computelst = m_ComputeCommandObj->m_RCO->m_DRList;
	
}

void DrawParticleOnly::DrawFrame()
{
	VkResult ret;
	
	//=========================================================
	// Allocate all semaphores
	//=========================================================
	
	//if (m_App->m_CFG->m_NoCompute != true)
	{
		//=========================================================
		// Wait for compute fences
		//=========================================================
		if ((ret = vkWaitForFences(m_App->GetLogicalDevice(), 1,
			&m_SO->m_Fences[SyncObjPO::F_CINFLIGHT].fencevec[currentBuffer], VK_TRUE, UINT64_MAX)) != VK_SUCCESS)
		{

			std::ostringstream  objtxt;
			objtxt << "DrawIParticle::DrawFrame() vkWaitForFences failed:" << ret << std::ends;

			throw std::runtime_error(objtxt.str().c_str());
		};
		if(Extflg == true)
			return ;
		//=========================================================
		// Update Compute resources
		//=========================================================

		m_Computelst[0]->PushMem(currentBuffer);
		m_Computelst[3]->PushMem(currentBuffer);

		ret = vkResetFences(m_App->GetLogicalDevice(), 1,
			&m_SO->m_Fences[SyncObjPO::F_CINFLIGHT].fencevec[currentBuffer]);
		if (ret != VK_SUCCESS)
		{

			std::ostringstream  objtxt;
			objtxt << "DrawIParticle::DrawFrame() vkResetFences computeInFlightFences failed:" << ret << std::ends;

			throw std::runtime_error(objtxt.str().c_str());
		};
		if(Extflg == true)
			return ;


		//=========================================================
		// Reset Compute Command Buffers.
		//=========================================================

		ret = vkResetCommandBuffer(
			m_ComputeCommandObj->m_CommandBuffers[currentBuffer],
			VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
		if (ret != VK_SUCCESS)
		{

			std::ostringstream  objtxt;
			objtxt << "DrawIParticle::DrawFrame() vkResetCommandBuffer failed:"
				<< ret << std::ends;

			throw std::runtime_error(objtxt.str().c_str());
		};

		

		//=========================================================
		// Record Compute commands
		//=========================================================
		m_ComputeCommandObj->RecordCommands(0,currentBuffer);
		if(Extflg == true)
			return ;
		VkSubmitInfo csubmitInfo{};
		csubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		csubmitInfo.commandBufferCount = 1;
		csubmitInfo.pCommandBuffers =
			&m_ComputeCommandObj->m_CommandBuffers[currentBuffer];
		csubmitInfo.signalSemaphoreCount = 1;
		csubmitInfo.pSignalSemaphores =
			&m_SO->m_WaitSemaphores[SyncObjPO::W_COMPUTEFIN].semvec[currentBuffer];
		if(Extflg == true)
			return ;

		//=========================================================
		// Submit Compute commands
		//=========================================================
		ret = vkQueueSubmit(m_App->GetComputeQueue(), 1, &csubmitInfo,
			m_SO->m_Fences[SyncObjPO::F_CINFLIGHT].fencevec[currentBuffer]);
		if (ret != VK_SUCCESS)
		{

			std::ostringstream  objtxt;
			objtxt << "DrawIParticle::DrawFrame() vkQueueSubmit GetComputeQueue failed:"
				<< ret << std::ends;

			throw std::runtime_error(objtxt.str().c_str());
		};
		m_ComputeCommandObj->FetchRenderTimeResults(currentBuffer);
#ifndef NDEBUG
		m_Computelst[3]->PullMem(currentBuffer);
#endif
		if(Extflg == true)
			return ;
		//########################################### Graphics ##########################################################
		//=========================================================
		// Wait for graphics fences
		//=========================================================

#if 1
		ret = vkWaitForFences(m_App->GetLogicalDevice(), 1,
			&m_SO->m_Fences[SyncObjPO::F_INFLIGHT].fencevec[currentBuffer], VK_TRUE, UINT64_MAX);
		if (ret != VK_SUCCESS)
		{

			std::ostringstream  objtxt;
			objtxt << "DrawIParticle::DrawFrame() vkWaitForFences inFlightFences failed:" << ret << std::ends;

			throw std::runtime_error(objtxt.str().c_str());
		};
#endif
		// Get draw count from compute


		//=========================================================
		// Acquire next completed image from swap-chain. Get the id of swap chain image
	// 
		//=========================================================
		uint32_t imageIndex = 0;
		VkResult result = vkAcquireNextImageKHR(
			m_App->GetLogicalDevice(),
			m_SCO->m_SwapChain,
			UINT64_MAX,
			m_SO->m_WaitSemaphores[SyncObjPO::W_IMAGAVAIL].semvec[currentBuffer],
			VK_NULL_HANDLE,
			&imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			//m_SCO->RecreateSwapChain(m_FBO);
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("Acquire Swap Chain Image Error.");
		}


		//=========================================================
		// Reset all fences unsignald
		//=========================================================
		ret = vkResetFences(m_App->GetLogicalDevice(), 1, &m_SO->m_Fences[SyncObjPO::F_INFLIGHT].fencevec[currentBuffer]);
		if (ret != VK_SUCCESS)
		{

			std::ostringstream  objtxt;
			objtxt << "DrawIParticle::DrawFrame() vkResetFences inFlightFences failed:" << ret << std::ends;

			throw std::runtime_error(objtxt.str().c_str());
		};

		//=========================================================
		// 	// Clear command buffer to rerecord. 
		//  If everything is on the GPU chnage this.
		//=========================================================
		ret = vkResetCommandBuffer(m_GraphicsCommandObj->m_CommandBuffers[currentBuffer],
			VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
		if (ret != VK_SUCCESS)
		{
			std::ostringstream  objtxt;
			objtxt << "DrawIParticle::DrawFrame() vkResetCommandBuffer m_CommandGBuffers failed:" << ret << std::ends;
			throw std::runtime_error(objtxt.str().c_str());
		};
	
		m_Graphicslst[1]->PushMem(currentBuffer);
		m_Graphicslst[2]->PushMem(currentBuffer);
		m_Graphicslst[5]->PushMem(currentBuffer);

		// Record a new command buffer for the current frame and associate with swap chain image.
		m_GraphicsCommandObj->RecordCommands(imageIndex,currentBuffer );
		if(Extflg == true)
			return ;
		VkSemaphore waitSemaphores[] = 
		{ m_SO->m_WaitSemaphores[SyncObjPO::W_COMPUTEFIN].semvec[currentBuffer] ,
			 m_SO->m_WaitSemaphores[SyncObjPO::W_IMAGAVAIL].semvec[currentBuffer] };
		if(Extflg == true)
			return ;
		VkPipelineStageFlags waitStages[] = 
		{ m_SO->m_WaitSemaphores[SyncObjPO::W_COMPUTEFIN].pipeStage[currentBuffer] ,
			 m_SO->m_WaitSemaphores[SyncObjPO::W_IMAGAVAIL].pipeStage[currentBuffer] };
		if(Extflg == true)
			return ;
		// Build submit info
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 2;
		submitInfo.pWaitSemaphores = waitSemaphores,
		submitInfo.pWaitDstStageMask = waitStages,
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_GraphicsCommandObj->m_CommandBuffers[currentBuffer];
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &m_SO->m_SigSemaphores[SyncObjPO::S_RENDERFIN].semvec[currentBuffer];
		if(Extflg == true)
			return ;

		// Submit the command pool to the graphics command queue.
		VkResult subret = vkQueueSubmit(m_App->GetGraphicsQueue(),
			1,
			&submitInfo,
			m_SO->m_Fences[SyncObjPO::F_INFLIGHT].fencevec[currentBuffer]);
		std::ostringstream  objtxt;
		if (subret == VK_ERROR_OUT_OF_HOST_MEMORY)
		{
			objtxt << "Error - DrawObj:" << m_Name
				<< " Returns:VK_ERROR_OUT_OF_HOST_MEMORY " << m_App->m_TotalMemoryBytes << std::ends;
			throw std::runtime_error(objtxt.str());
		}
		else
			if (subret == VK_ERROR_OUT_OF_DEVICE_MEMORY)
			{
				objtxt << "Error - DrawObj:" << m_Name
					<< " Returns:VK_ERROR_OUT_OF_DEVICE_MEMORY " << m_App->m_TotalMemoryBytes << std::ends;
				throw std::runtime_error(objtxt.str());
			}
			else
				if (subret == VK_ERROR_DEVICE_LOST)
				{
					objtxt << "Error - DrawObj:" << m_Name
						<< " Returns:VK_ERROR_DEVICE_LOST" << m_App->m_TotalMemoryBytes << std::ends;
					throw std::runtime_error(objtxt.str());

				}
		m_GraphicsCommandObj->FetchRenderTimeResults(currentBuffer);
#ifndef NDEBUG
		m_Graphicslst[5]->PullMem(currentBuffer);
#endif
		// Wait for complettion of rendering then pick up the completed frame buffer 
		// and send to presentation device.
		VkSwapchainKHR swapChains[] = { m_SCO->m_SwapChain };

		// Build presentation info
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &m_SO->m_SigSemaphores[SyncObjPO::S_RENDERFIN].semvec[currentBuffer];
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;

		// Send to presentation device
		result = vkQueuePresentKHR(m_App->GetPresentQueue(), &presentInfo);
		if (result == VK_ERROR_OUT_OF_DATE_KHR ||
			result == VK_SUBOPTIMAL_KHR)
		{
			//	m_App->m_FramebufferResized = false;
			//	m_SCO->RecreateSwapChain(m_FBO);
		}
		else if (result != VK_SUCCESS)
		{
			throw std::runtime_error("vkQueuePresentKHR in DrawFrame Failed.");
		}
		currentBuffer = (currentBuffer + 1) % m_App->m_FramesBuffered;
		m_App->SetCurrentBuffer(currentBuffer);
		
	}

}