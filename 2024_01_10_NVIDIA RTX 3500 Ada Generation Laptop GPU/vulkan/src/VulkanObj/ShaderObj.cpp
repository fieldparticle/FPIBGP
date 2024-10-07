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
void ShaderObj::Create(ResourceVertexParticle* VPO, ResourceCollMatrix* CMO, ResourceLockMatrix* LMO, SwapChain* SCO)
{
		m_VPO = VPO;
		m_CMO = CMO;
		m_SCO = SCO;
		m_LMO = LMO;
		ConfigObj* cfg = m_App->m_CFG;
		GenWorkGroups();
		if(cfg->m_TstFileVersion == 2)
		{
			cfg->GetParticleSettingsV2();
			WriteShaderHeaderV2();
		}
		else
		{
			cfg->GetParticleSettings();
			WriteShaderHeader();
		}
		
}
void ShaderObj::GenWorkGroups()
{

	ConfigObj* cfg = m_App->m_CFG;
	std::string filename = "../../shaders/workgroups.glsl";
	{
		std::ofstream ostrm(filename);
		if (!ostrm.is_open())
		{
			std::string rpt = "Failed to open file:" + filename;
			throw std::runtime_error(rpt.c_str());
		}
		ostrm << "layout(local_size_x = " << cfg->m_wkx <<
			", local_size_y = " << cfg->m_wky <<
			", local_size_z = " << cfg->m_wkz << ") in;\n";
	}
}

	
void  ShaderObj::WriteShaderHeader()
{
	
	uint32_t compflag=0;
	ConfigObj* cfg = m_App->m_CFG;
	
    std::string filename = "../../shaders/params.glsl";
    {
		std::string dbgflag = {};
#ifdef NDEBUG
		 dbgflag = "RELEASE";
#else
		dbgflag = "DEBUG";
#endif
		
		
        std::ofstream ostrm(filename);
		if (!ostrm.is_open())
		{
			std::string rpt = "Failed to open file:" + filename;
			throw std::runtime_error(rpt.c_str());
		}
		ostrm << "const uint WIDTH=" << m_VPO->m_SideLength << ";\n"
			<< "const uint HEIGHT=" << m_VPO->m_SideLength << ";\n"
			<< "const uint DEPTH=" << m_VPO->m_SideLength << ";\n"
			<< "const uint MAX_ARY=" << m_App->m_CFG->m_MaxCollArray << ";\n"
			<< "const uint SCR_W =" << m_SCO->m_SwapWidth << ";\n"
			<< "const uint SCR_H =" << m_SCO->m_SwapHeight << ";\n"
			<< "const uint SCR_X =" << m_SCO->m_SwapX << ";\n"
			<< "const uint SCR_Y =" << m_SCO->m_SwapY << ";\n"
			<< "const uint NUMPARTS =" << m_VPO->m_NumParticles << ";\n"
			<< "const uint NUMCOLS =" << m_App->m_CFG->m_colcount << ";\n"
			<< "const uint MAXSPCOLLS =" << m_VPO->m_MaxColls << ";\n"
			<< "const uint doMotion =" << m_App->m_CFG->m_DoMotion << ";\n"
			<< "const uint MaxLocation =" << m_CMO->m_MaxLoc << ";\n"
			<< "const uint ColArySize=" << m_CMO->m_BufSize << ";\n"
			<< "const uint LockArySize=" << m_LMO->m_BufSize << ";\n"
			<< "const float dt =" << m_VPO->m_dt << ";\n"
			<< "const uint compflag =" << compflag << ";\n"
			<< "const uint bbound =" << m_VPO->BoundaryParticleLimit << ";\n"
			<< "#define " << dbgflag << "\n";
		ostrm.flush();
		ostrm.close();
    }
}

void  ShaderObj::WriteShaderHeaderV2()
{
	
	uint32_t compflag=0;
	ConfigObj* cfg = m_App->m_CFG;
    std::string filename = "../../shaders/params.glsl";
    {
		std::string dbgflag = {};
#ifdef NDEBUG
		dbgflag = "RELEASE ";
#else
		dbgflag = "DEBUG ";
#endif
		
		std::string version = {};
		if(cfg->m_TstFileMinorVersion == 0)
			version = "VERPIPE ";
		if(cfg->m_TstFileMinorVersion == 1)
			version = "VERCUBE ";
		if(cfg->m_TstFileMinorVersion == 2)
			version = "VERCDNOZ ";
		if(cfg->m_TstFileMinorVersion == 3)
			version = "VERPONLY ";
		
		
		

		
		uint32_t MaxLoc = static_cast<uint32_t>((cfg->m_CellAryW) * (cfg->m_CellAryH) * (cfg->m_CellAryL));
        std::ofstream ostrm(filename);
		if (!ostrm.is_open())
		{
			std::string rpt = "Failed to open file:" + filename;
			throw std::runtime_error(rpt.c_str());
		}
		ostrm	<< "#define " << dbgflag << "\n"
				<< "#define " << version.c_str()  << "\n"
				<< "const uint WIDTH=" << cfg->m_CellAryW << ";\n"
				<< "const uint HEIGHT=" << cfg->m_CellAryH << ";\n"
				<< "const uint DEPTH=" << cfg->m_CellAryL << ";\n"
				<< "const uint CENTER=" << cfg->m_PipeCenter << ";\n"
				<< "const float RADIUS=" << cfg->m_PipeRadius << ";\n"
				<< "const uint MAX_ARY=" << m_App->m_CFG->m_MaxCollArray << ";\n"
				<< "const uint SCR_W =" << m_SCO->m_SwapWidth << ";\n"
				<< "const uint SCR_H =" << m_SCO->m_SwapHeight << ";\n"
				<< "const uint SCR_X =" << m_SCO->m_SwapX << ";\n"
				<< "const uint SCR_Y =" << m_SCO->m_SwapY << ";\n"
				<< "const uint NUMPARTS =" << m_VPO->m_NumParticles << ";\n"
				<< "const uint NUMCOLS =" << m_App->m_CFG->m_colcount << ";\n"
				<< "const uint MAXSPCOLLS =" << m_VPO->m_MaxColls << ";\n"
				<< "const uint ColArySize=" << m_CMO->m_BufSize << ";\n"
				<< "const uint LockArySize=" << m_LMO->m_BufSize << ";\n"
				<< "const uint doMotion =" << m_App->m_CFG->m_DoMotion << ";\n"
				<< "const uint MaxLocation =" << m_CMO->m_MaxLoc << ";\n"
				<< "const float dt =" << m_VPO->m_dt << ";\n"
				<< "const uint compflag =" << compflag << ";\n"
				<< "const uint bbound =" << m_VPO->BoundaryParticleLimit << ";\n";
			
			
		ostrm.flush();
		ostrm.close();
    }
}

int ShaderObj::CompileShader(std::string ShaderGLSLName, 
		std::string ShaderSPVFileName, std::vector<char> &SPVBuffer, uint32_t type)
{
	ConfigObj* cfg = m_App->m_CFG;
	std::vector<std::string> InputArgs;

	//std::cout << cfg->m_CompileShaders << std::endl;
	if (cfg->m_CompileShaders == true)
	{
		InputArgs.push_back("ParticleOnly.exe");
		InputArgs.push_back("--target-env=vulkan1.3");
		InputArgs.push_back("-g");
		if (type == SH_FRAG)
		{
			InputArgs.push_back("-fshader-stage=fragment");
		}
		else if (type == SH_VERT)
		{
			InputArgs.push_back("-fshader-stage=vertex");
		}
		else if (type == SH_COMP)
		{
			InputArgs.push_back("-fshader-stage=compute");
		}

		std::string infl = ShaderGLSLName;
		InputArgs.push_back(infl);
		InputArgs.push_back("-o");
		InputArgs.push_back(ShaderSPVFileName);
		int ret =  glsl(InputArgs, SPVBuffer);
		if (ret != 0 || SPVBuffer.empty())
		{
			std::ostringstream  objtxt;
			objtxt << "Error from glsl in:" << m_Name 
				<< " Returns:" << ret << " for:" << ShaderGLSLName << std::ends;
			throw std::runtime_error(objtxt.str());
		}
		else
		{
			mout << "glsl success :" << m_Name
				<< " Returns:" << ret << " for:" << ShaderGLSLName 
				<< " Size:" << SPVBuffer.size() << ende;
			
		}
		std::string fname = ShaderGLSLName + ".bin";
		//WriteBinaryFile(fname, SPVBuffer);
		return ret;
	}
	return 0;

}
int ShaderObj::WriteBinaryFile(std::string fileName, std::vector<char> buffer)
{
	std::ofstream fout(fileName, std::ios::out | std::ios::binary);
	if (!fout.is_open())
	{
		std::string rpt = "Failed to open file:" + fileName;
		throw std::runtime_error(rpt.c_str());
	}

	size_t size = buffer.size();
	for (uint32_t ii = 0; ii < size; ii++)
	{
		char ch = (char)buffer[ii];
		fout.write(&ch, 1);
	}

	fout.flush();
	fout.close();
	return 0;
	
}