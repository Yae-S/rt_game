// -*- C++ -*-
/*!
 * @file  Main_comp.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Main_comp.h"

// Module specification
// <rtc-template block="module_spec">
static const char* main_comp_spec[] =
  {
    "implementation_id", "Main_comp",
    "type_name",         "Main_comp",
    "description",       "ModuleDescription",
    "version",           "2.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.test_conf_1", "-1",
    "conf.default.test_conf_2", "-1",
    "conf.default.test_conf_3", "-1",
    "conf.default.test_conf_4", "-1",
    // Widget
    "conf.__widget__.test_conf_1", "text",
    "conf.__widget__.test_conf_2", "text",
    "conf.__widget__.test_conf_3", "text",
    "conf.__widget__.test_conf_4", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Main_comp::Main_comp(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_main_ainIn("main_ain", m_main_ain),
    m_positionIn("position", m_position),
    m_main_sinIn("main_sin", m_main_sin),
    m_main_aoutOut("main_aout", m_main_aout),
    m_main_soutOut("main_sout", m_main_sout),
    m_triggerPort("trigger")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Main_comp::~Main_comp()
{
}



RTC::ReturnCode_t Main_comp::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("main_ain", m_main_ainIn);
  addInPort("position", m_positionIn);
  addInPort("main_sin", m_main_sinIn);
  
  // Set OutPort buffer
  addOutPort("main_aout", m_main_aoutOut);
  addOutPort("main_sout", m_main_soutOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_triggerPort.registerConsumer("recogPort", "RecognitionService", m_recogPort);
  
  // Set CORBA Service Ports
  addPort(m_triggerPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("test_conf_1", m_test_conf_1, "-1");
  bindParameter("test_conf_2", m_test_conf_2, "-1");
  bindParameter("test_conf_3", m_test_conf_3, "-1");
  bindParameter("test_conf_4", m_test_conf_4, "-1");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Main_comp::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Main_comp::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Main_comp::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Main_comp::onActivated(RTC::UniqueId ec_id)
{
  ready_a=0;
  ready_e=0;
  ready_s=0;
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Main_comp::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Main_comp::onExecute(RTC::UniqueId ec_id)
{
	int TF01=5,TF02=7; //アニメーションコンポーネントから渡される罠情報.T(トラップ)F(フラグ).
	char x='a';

	if(ready_a==0){
		
	/*	if(x=='a'){
			getchar();
		}*/

		m_main_aout.data=0; //アニメーションコマンド-0,アニメーションスタート.

		std::cout<<"Animation Start Command"<<std::endl;

		m_main_aoutOut.write(); //出力ポートに書き込み.	

	//	x='b';

	//	std::cout<<x<<std::endl;

	}

	
	if(m_main_ainIn.isNew()||m_positionIn.isNew()||m_main_sinIn.isNew()){ //各入力ポートの検出.
		m_main_ainIn.read(); //データ読み込み.
		m_positionIn.read();
		m_main_sinIn.read();

		if(ready_a==0){

			if(m_main_ain.data==9){ //アニメーションコンポーネントからのレスポンス.待機状態へ.
				std::cout<<"Animation Start"<<std::endl;
				ready_a=1;
			}
		}

		else{

			if(m_main_ain.data==TF01){ //そのデータがどの罠か判断.

				if(ready_e==0){

					std::cout<<"TF01 Catch"<<std::endl;
					try{
						m_recogPort->setModelID(-1); //画像コンポーネントに命令.
					}
					catch(...){
						std::cerr << "Error in service port." <<std::endl;
						return RTC::RTC_ERROR;
					}

					ready_e=1;

				}
				
				else{

					if(m_position.data[1]==0){ //画像認識が成功していた場合.

						std::cout<<m_position.data[1]<<std::endl;

						m_main_aout.data=1; //アニメーションコマンド-1,メイン変化なし.背景差し替え.
						m_main_aoutOut.write(); //出力ポートに書き込み.

						std::cout<<"Animation Command-1 "<<std::endl;

					}
					else if(m_position.data[1]!=0){ //画像認識が失敗していた場合.
						m_main_aout.data=3; //アニメーションコマンド-3,障害回避失敗.
						m_main_aoutOut.write(); //出力ポートに書き込み.	

						std::cout<<"Animation Command-3 "<<std::endl;

					/*	ready_a=0;
						ready_e=0;*/
					}
				}

			}
			

			else if(m_main_ain.data==TF02){ //罠判断.音声パターン.

				if(ready_s==0){
					std::cout<<"TF02 Catch"<<std::endl;
					m_main_sout.data=1; //音声認識コンポーネントに命令.受けた音声コンポーネントは判断コンポーネントへ投げて,そちらがメインに結果を戻す.
					m_main_soutOut.write(); //出力ポートに書き込み.	
					ready_s=1;

				}
				else{

					if(m_main_sin.data==1){ //音声認識が成功していた場合.
						m_main_aout.data=2; //アニメーションコマンド-2,キャラクター差し替え.
						m_main_aoutOut.write(); //出力ポートに書き込み.

						std::cout<<"Animation Command-2 "<<std::endl;

				/*		ready_a=0;
						ready_e=0;
						ready_s=0;
						x='a';

						std::cout<<ready_a<<std::endl;
						std::cout<<ready_e<<std::endl;
						std::cout<<ready_s<<std::endl;*/
	
					}
					else if(m_main_sin.data==0){ //音声認識が失敗していた場合.
						m_main_aout.data=3; //アニメーションコマンド-3,障害回避失敗.
						m_main_aoutOut.write(); //出力ポートに書き込み.

						std::cout<<"Animation Command-3 "<<std::endl;

					/*	ready_a=0;
						ready_s=0;*/
					}
				}
			
			}

		}
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Main_comp::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Main_comp::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Main_comp::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Main_comp::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Main_comp::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void Main_compInit(RTC::Manager* manager)
  {
    coil::Properties profile(main_comp_spec);
    manager->registerFactory(profile,
                             RTC::Create<Main_comp>,
                             RTC::Delete<Main_comp>);
  }
  
};


