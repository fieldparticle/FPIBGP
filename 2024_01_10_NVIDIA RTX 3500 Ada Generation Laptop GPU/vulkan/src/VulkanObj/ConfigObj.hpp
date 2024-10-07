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

#ifndef CONFIGOBJ_HPP
#define CONFIGOBJ_HPP
class VulkanObj;
class ConfigObj 
{
public:

	bool						m_DebugVerbose = false;
	std::string					m_rccdrv;
	std::string					m_rccdver;
	std::string					m_fragShaderSphere;
	std::string					m_vertShaderSphere;
	std::string					m_fragShaderBoundary;
	std::string					m_vertShaderBoundary;
	std::string					m_fragShaderParticle;
	std::string					m_vertShaderParticle;
	std::string					m_compShaderParticle;

	std::string					m_fragSPVSphere;
	std::string					m_vertSPVSphere;
	std::string					m_fragSPVBoundary;
	std::string					m_vertSPVBoundary;
	std::string					m_fragSPVParticle;
	std::string					m_vertSPVParticle;
	std::string					m_compSPVParticle;
	std::string					m_glslc_path;

	bool						m_DebugVer=false;
	bool						m_ReleaseVer=false;
	std::string					m_runOnly;

	std::string					m_PQBTestName;
	std::string					m_PQBTestDir;

	std::string					m_CFBStudyName;
	std::string					m_CFBTestName;
	std::string					m_CFBTestDir;

	std::string					m_PCDStudyName;
	std::string					m_PCDTestName;
	std::string					m_PCDTestDir;

	std::string					m_DUPStudyName;
	std::string					m_DUPTestName;
	std::string					m_DUPTestDir;


	std::string					m_MMRRStudyName;
	std::string					m_MMRRTestName;
	std::string					m_MMRRTestDir;

	std::string					m_TestName;
	std::string					m_TestDir;
	std::string					m_TestCFG;
	std::string					m_testPQBDir;
	std::string					m_testCFBDir;
	std::string					m_testPCDDir;
	std::string					m_testDUPDir;

	std::string					m_Name;
	uint32_t					m_View;
	std::string					m_AppName;
	std::string					m_StudyName;
	std::string					m_Version;
	std::string					m_Boundary;
	std::string					m_SphereFile;
	std::string					m_PhysDevice;
	std::string					m_CapFlName;
	std::string					m_AprFile;
	std::string					m_DataFile;
	
	uint32_t					m_CapFrmNum = 0;
	uint32_t					m_CfgSidelen = 0;
	float						m_PipeCenter = 0.0;
	float						m_PipeRadius = 0.0;
	uint32_t					m_PartPerCell = 0;
	uint32_t					m_CapFrms = 0;
	uint32_t					m_EndFrame = 0;
	bool						m_BoundaryFlag = false;
	bool						m_BoundaryOnly = false;
	bool						m_NSight = false;
	bool						m_NoCompute = false;
	uint32_t					m_DoMotion = false;
	uint32_t					m_FramesBuffered = 1;
	uint32_t					m_WorkGroups = 0;
	uint32_t					m_CellAryW	= 0;
	uint32_t					m_CellAryH	= 0;
	uint32_t					m_CellAryL	= 0;
	uint32_t					m_TstFileVersion = 0;
	uint32_t					m_TstFileMinorVersion = 0;
	std::string					m_Compiler;
	
	std::string					m_Substance;
	std::vector<const char*>	m_DeviceExtensions;
	std::vector<const char*>	m_InstanceExtensions;
	std::vector<const char*>	m_ValidationLayers;
	bool						m_SaveExtensions = false;
	bool						m_SaveDevLimits = false;
	bool						m_EnableValidationLayers = false;
	uint32_t					m_reportCompFramesLessThan = 0;
	uint32_t					m_reportGraphFramesLessThan = 0;
	uint32_t					m_PopPerCell = 0;
	bool						m_CompileShaders = true;
	uint32_t					m_StartFrame = 0;
	bool						m_WireFlag = false;
	bool						m_DoAuto = false;
	uint32_t					m_AutoTimeOut = 0;
	uint32_t					m_StudyType = 0;
	uint32_t					m_Width = 0;
	uint32_t					m_Height = 0;
	uint32_t					m_RequestedWidth = 0;
	uint32_t					m_RequestedHeight = 0;
	unsigned long				m_FrameDelay = 0;
	uint32_t					m_startSideLength = 0;
	int							m_TestNumber = 0;
	uint32_t					m_colcount = 0;
	uint32_t					m_MaxPopPerCell = 0;
	float						m_radius = 0.0;
	float						m_serialTime = 0;
	float						m_density = 0;
	float						m_TempHigh = 0.0;
	float						m_TempLow = 0.0;
	float						m_PDensity = 0.0;
	float						m_CDensity = 0.0;
	float						m_Radius = 0.0;


	float						m_dt = 0.0;
	uint32_t					m_wkx = 0;
	uint32_t					m_wky = 0;
	uint32_t					m_wkz = 0;
	uint32_t					m_dkx = 0;
	uint32_t					m_dky = 0;
	uint32_t					m_dkz = 0;
			
	//---------------------------- Read write used to record across instances
	bool						m_Stopondata = false;
	int							m_partcount = 0;
	int							m_threadGroup = 0;
	int							m_MaxCollArray = 0;
	uint32_t					m_MaxSingleCollisions = 0;
	uint32_t					m_BoundarySideLength = 0;

	int					_StructCount=0;
	uint32_t			m_StructIdx=0;
	std::string			m_cfg_file;
	config_t 			m_cfg;
	config_setting_t* m_setting;
	int 				int_temp=0;
	const char* str_temp;
	double				float_temp = 0.0;
	std::string			lookup;
	std::string			util;
	config_setting_t*	setting;
	int m_Count=0;
	struct pair
	{
		std::string Name;
		void*		Value;
		uint32_t	Type;
		bool		retFlg;
	};
	uint32_t STRC_STRING = 1;
	uint32_t STRC_INT = 2;
	uint32_t STRC_UINT = 3;
	uint32_t STRC_FLOAT = 4;

	

	int GetInt(std::string lookup, bool failFlag)	;

	uint32_t GetUInt(std::string lookup, bool failFlag);
	const char* GetString(std::string lookup, bool failFlag);
	bool GetBool(std::string lookup, bool failFlag);
	float GetFloat(std::string lookup, bool failFlag);
	void ReadConfigFile(std::string FileName);
	void GetParticleSettings();
	void GetParticleSettingsV2();
	std::vector<const char*> GetArray(std::string Name);
	config_setting_t* StartStructure(std::string Name, int& Count);
	config_setting_t* GetSubStructAddress(config_setting_t* setting, int index);
	bool GetNextSubStruct(config_setting_t* setting, std::vector<pair> &pairs, int index);
	const char* GetArrayElementString(config_setting_t* setting, int index);
	void GetArrayElementFloats(config_setting_t* setting, std::string Name, float *Ary, uint32_t Max,int index);

	VulkanObj* m_App;
	//ConfigObj(VulkanObj* App, std::string Name, uint32_t VTType=0) 
	//	: BaseObj(Name, VTType, App) { };

	ConfigObj() {};
	virtual void Create(std::string cfg_file)
	{
		m_cfg_file = cfg_file;
		// Intialize libconfig
		config_init(&m_cfg);
		ReadConfigFile(m_cfg_file);
		GetSettings();
	}
	void SetVulkanObj(VulkanObj* app)
	{
		m_App = app;
	}
	virtual void GetSettings();

};

#endif