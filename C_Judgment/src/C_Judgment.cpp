// -*- C++ -*-
/*!
 * @file  C_Judgment.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "C_Judgment.h"

// Module specification
// <rtc-template block="module_spec">
static const char* c_judgment_spec[] =
  {
    "implementation_id", "C_Judgment",
    "type_name",         "C_Judgment",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
C_Judgment::C_Judgment(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_C_Judgment_inIn("C_Judgment_in", m_C_Judgment_in),
    m_C_Judgment_outOut("C_Judgment_out", m_C_Judgment_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
C_Judgment::~C_Judgment()
{
}



RTC::ReturnCode_t C_Judgment::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("C_Judgment_in", m_C_Judgment_inIn);
  
  // Set OutPort buffer
  addOutPort("C_Judgment_out", m_C_Judgment_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t C_Judgment::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t C_Judgment::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t C_Judgment::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t C_Judgment::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t C_Judgment::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t C_Judgment::onExecute(RTC::UniqueId ec_id)
{	
	std::string::size_type pos;
	std::string::size_type pos2;
	

	//èoóÕÇ≥ÇÍÇΩï∂éöóÒÇì¸
	std::string str;
	std::string result;
	

	if(m_C_Judgment_inIn.isNew()){
		 m_C_Judgment_inIn.read();
		 str =  m_C_Judgment_in.data;
		// std::cout << str.c_str()<<std::endl;

		pos = str.find("rank=\"1\"");
		if(pos!=std::string::npos){
			std::cout << "èÍèärank:" << pos << std::endl;
			pos = str.find("text=\"",pos);
			if(pos!=std::string::npos){
				std::cout << "èÍèätext:" << pos << std::endl;
				pos2 = str.find("\"",pos+6);
				if(pos2!=std::string::npos){
					std::cout << "èÍèä\":" << pos2 << std::endl;
					result = str.substr(pos+6,pos2-(pos+6));
					std::cout << "åãâ : "<<result.c_str()<<std::endl;

					if(result == "jump"){
						std::cout << "ê≥âÅI" << std::endl;
						//ÇPÇìäÇ∞ÇÈ
						m_C_Judgment_out.data = 1;
						m_C_Judgment_outOut.write();
					}else{
						std::cout <<"ïsê≥â" << std::endl;
						//0ÇìäÇ∞ÇÈ
						m_C_Judgment_out.data = 0;
						m_C_Judgment_outOut.write();
					}
				}
			}
		}
	}


//	std::cin >> str; 

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t C_Judgment::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t C_Judgment::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t C_Judgment::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t C_Judgment::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t C_Judgment::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void C_JudgmentInit(RTC::Manager* manager)
  {
    coil::Properties profile(c_judgment_spec);
    manager->registerFactory(profile,
                             RTC::Create<C_Judgment>,
                             RTC::Delete<C_Judgment>);
  }
  
};


