// -*- C++ -*-
/*!
 * @file  Anime_comp.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Anime_comp.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define OPENCV_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define OPENCV_VERSION_CODE OPENCV_VERSION(CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION)

void overlay(cv::Mat &foreground, cv::Mat &background, cv::Mat &dst, cv::Point &pos);

char* winname="Game Capture";

void overlay(cv::Mat &foreground, cv::Mat &background, cv::Mat &dst, cv::Point &pos){

  // BGRAチャンネルに分離
  std::vector<cv::Mat> f_split;
  cv::split(foreground, f_split);
  // BGRチャンネルに分離
  std::vector<cv::Mat> b_split;
  cv::split(background, b_split);

  // 4番目のチャンネル（=アルファ）の取り出しと正規化
  cv::Mat alpha32f;
  f_split[3].convertTo(alpha32f, CV_32FC1);
  cv::normalize(alpha32f, alpha32f, 0., 1., cv::NORM_MINMAX);

  // 画像の合成
  for(int y=pos.y; y<pos.y+foreground.rows; y++){
	//領域外なら次の位置へ
	if(y<0){continue;}
	else if(y>=background.rows){break;}

	for(int x=pos.x; x<pos.x+foreground.cols; x++){
	  //領域外なら次の位置へ
	  if(x<0){continue;}
      else if(x>=background.cols){break;}

	  if(alpha32f.at<float>(cv::Point(x-pos.x,y-pos.y))>0.5){ //透明でない画素だったら
		for(int i=0;i<3;i++){
			b_split[i].at<unsigned char>(cv::Point(x,y)) = f_split[i].at<unsigned char>(cv::Point(x-pos.x,y-pos.y)); //背景の上に前景を重ねる
		}
	  }
	}
  }

  cv::merge(b_split, dst); //分離したチャンネルを戻す

  return;
}

void walk(int start_x,int end_x,int y,cv::Mat character1,cv::Mat character2,cv::Mat back,int width,int height){
	int x=0;
	char c;
	cv::Mat blend;
	cv::Mat img;

	while(start_x+x<=end_x){
		if(x%3==0){
			if(!img.data) img = character1;
			else if(img.data==character1.data) img = character2;
			else if(img.data==character2.data) img = character1;
		}	

//		std::cout<<"x="<<x+start_x<<",y="<<y<<std::endl;
//		std::cout<<"width="<<width<<",height="<<height<<std::endl;
		overlay(img, back, blend, cv::Point(200+x+start_x,225)); //合成
		cv::Mat anime(blend,cv::Rect(start_x+x,0,width,height));
		imshow(winname,anime);
	
		x=x+4;
		c=cv::waitKey(10);
		if(c==27){
			break;
		}
	}
}

void jump(int start_x,int x_end,int start_y,cv::Mat character,cv::Mat back,int width,int height){

	cv::Mat blend;
	cv::Mat img;
	
	char c;
	int walk_end_x = x_end-start_x-329;
	int top_x =(start_x+x_end)/2;
	int y = start_y-50; 
	int x = start_x;
	int up_y=start_y+character.rows;
	std::cout<<"y="<<y<<",start_y"<<start_y<<std::endl;
	std::cout<<"x="<<x<<std::endl;
	img = character;
	x= 0;
	std::cout<<"top_x"<<top_x<<std::endl;	
	while(start_x<=x_end){
		overlay(img, back, blend, cv::Point(start_x+200,start_y));
		cv::Mat anime(blend,cv::Rect(x+start_x,0,width,height));
		//std::cout<<"x="<<start_x<<",y="<<start_y<<std::endl;
		imshow(winname,anime);

		if(start_y >= 255-img.rows){
			start_y=start_y-6;
		}else if(start_x<x_end){
			start_x=start_x+6;
			//std::cout<<"x_2="<<x+start_x<<std::endl;
		}

		c=cv::waitKey(10);
		if(c==27){
			break;
		}
	}
	while(start_x>=x_end){
		overlay(img, back, blend, cv::Point(start_x+200,start_y));
		cv::Mat anime(blend,cv::Rect(x+start_x,0,width,height));
		//std::cout<<"x="<<start_x<<",y="<<start_y<<std::endl;
		imshow(winname,anime);

		if(start_y <= y){
			start_y=start_y+6;
		}
		else if(start_y>=y){
			break;
		}

		c=cv::waitKey(10);
		if(c==27){
			break;
		}
	}
}

void fall(int start_x,int start_y,int fall,cv::Mat character1,cv::Mat character2,cv::Mat back,int width,int height){
	int end_x =start_x+character1.cols+fall;
	int y=0;
	cv::Mat img = character1;
	cv::Mat blend;
	char c;	
	
//	walk(start_x,end_x,start_y,character1,character2,back,width,height);
	std::cout<<"end_x="<<end_x<<std::endl;
	end_x=end_x+200;
	while(start_y>=y){
		std::cout<<"end_x="<<end_x<<std::endl;
		overlay(img, back, blend, cv::Point(end_x,225+y)); //合成
		cv::Mat anime(blend,cv::Rect(end_x-200,0,width,height));
		imshow(winname,anime);
		y=y+4;
		c=cv::waitKey(10);
		if(c==27){
			break;
		}
	}
}

// Module specification
// <rtc-template block="module_spec">
static const char* anime_comp_spec[] =
  {
    "implementation_id", "Anime_comp",
    "type_name",         "Anime_comp",
    "description",       "ModuleDescription",
    "version",           "1.0.1",
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
Anime_comp::Anime_comp(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_anime_inIn("anime_in", m_anime_in),
    m_anime_outOut("anime_out", m_anime_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Anime_comp::~Anime_comp()
{
}



RTC::ReturnCode_t Anime_comp::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("anime_in", m_anime_inIn);
  
  // Set OutPort buffer
  addOutPort("anime_out", m_anime_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Anime_comp::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Anime_comp::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Anime_comp::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Anime_comp::onActivated(RTC::UniqueId ec_id)
{
	img1 = cv::imread("../../../1.png", -1);
	if(img1.empty()) return RTC::RTC_ERROR;
	img2 = cv::imread("../../../2.png", -1);
	if(img2.empty()) return RTC::RTC_ERROR;
	img3 = cv::imread("../../../3.png", -1);
	if(img3.empty()) return RTC::RTC_ERROR;
	back = cv::imread("../../../haikei.png", 1);
	if(back.empty()) return RTC::RTC_ERROR;;
	bridge = cv::imread("../../../test.png",-1);
	if(bridge.empty()) return RTC::RTC_ERROR;; 
	anime = cv::imread("../../../start.png",1);
	
	c=0;
	cv::resize(img1,character1,cv::Size(186,247));
	cv::resize(img2,character2,cv::Size(186,247));
	cv::resize(img3,character3,cv::Size(186,247));
	cv::resize(bridge,bridge,cv::Size(bridge.rows*3,bridge.cols/2));
	
	cv::namedWindow(winname,CV_WINDOW_AUTOSIZE);
//	cv::moveWindow(winname,0,0);//ウィンドの位置を変更させる

	height=back.rows;
	width = back.cols/5;
	y = 255;
	
	x_start = 0;
	x_end = (width/2)-300;
	
	ready=0;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Anime_comp::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Anime_comp::onExecute(RTC::UniqueId ec_id)
{
#if OPENCV_VERSION_CODE<OPENCV_VERSION(2,3,1)
    std::cout << "cannot support this opencv version:" 
              <<  CV_VERSION << std::endl;
    return -1;
#else

//	std::cout << "onExecute" << std::endl;
	cv::imshow(winname,anime);
	while(c!=27){
		c=cv::waitKey(10);
	}
	
	int TF01=5; //罠情報.T(トラップ)F(フラグ).(仮)
	int TF02=7;

	if(m_anime_inIn.isNew()){ //入力ポートの検出.
		m_anime_inIn.read(); //データ読み込み.
		
		std::cout<<"Command received"<<std::endl;
		
		if(ready==0){
			if(m_anime_in.data==0){
				std::cout<<"Start Main Animation"<<std::endl;
				std::cout<<"Start Back Animation"<<std::endl;
				
				walk(x_start,x_end,y,character1,character2,back,width,height);
				std::cout<<"road1::end"<<std::endl;
				x_start=x_end;
				x_end=x_end+(width/2);
				
				// タイムキープ開始? //
				m_anime_out.data=9; //メインコンポーネントにアニメーションがスタートしたことを知らせる.
				m_anime_outOut.write();

				m_anime_out.data=TF01; //TF01をメインコンポーネントに投げる.TFの更新と投げるまでの動作を関数化したい.
				m_anime_outOut.write();
				
				walk(x_start,x_end,y,character1,character2,back,width,height);
				std::cout<<"road2::end"<<std::endl;
				x_start=x_end;
				x_end=x_end+width;
				
				std::cout<<"TF01 Throw"<<std::endl;
				ready=1;
			}
		}
		
		else{ //結果待機中.次のフラグを投げる.
			
			if(m_anime_in.data==1){
				std::cout<<"Start Newback Animation"<<std::endl;
				overlay(bridge,back,back,cv::Point(750,400));
				walk(x_start,x_end,255,character1,character2,back,width,height);
				std::cout<<"road3::end"<<std::endl;
				x_start =x_end;
				x_end = x_end + width/2;
				
				walk(x_start,x_end,y,character1,character2,back,width,height);
				std::cout<<"road4::end"<<std::endl;
				x_start=x_end;
				x_end=x_end+(width/2);

				m_anime_out.data=TF02; //TF02をメインコンポーネントに投げる.
				m_anime_outOut.write();
				std::cout<<"TF02 Throw"<<std::endl;
				walk(x_start,x_end,255,character1,character2,back,width,height);
				std::cout<<"road5::end"<<std::endl;
				x_start=x_end;
				x_end=x_end+width;
			}
			else if(m_anime_in.data==2){
				std::cout<<"Start Jump Animation"<<std::endl;
				jump(x_start,x_end,y,character3,back,width,height);
				std::cout<<"road6::end"<<std::endl;
				x_start=x_end;
				x_end=x_end+300;
				walk(x_start,x_end,y,character1,character2,back,width,height);
				std::cout<<"road7::end"<<std::endl;
			}
			else if(m_anime_in.data==3){
				std::cout<<"Start Failed Animation"<<std::endl;
				fall(x_start,y,350,character1,character2,back,width,height);
				ready=0;
			}
		}
	}
	return RTC::RTC_OK;

#endif
}

/*
RTC::ReturnCode_t Anime_comp::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Anime_comp::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Anime_comp::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Anime_comp::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Anime_comp::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void Anime_compInit(RTC::Manager* manager)
  {
    coil::Properties profile(anime_comp_spec);
    manager->registerFactory(profile,
                             RTC::Create<Anime_comp>,
                             RTC::Delete<Anime_comp>);
  }
  
};


