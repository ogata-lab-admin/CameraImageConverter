// -*- C++ -*-
/*!
 * @file  CameraImageConverter.cpp
 * @brief Camera Image Converter RTC
 * @date $Date$
 *
 * $Id$
 */

#include "CameraImageConverter.h"

// Module specification
// <rtc-template block="module_spec">
static const char* cameraimageconverter_spec[] =
  {
    "implementation_id", "CameraImageConverter",
    "type_name",         "CameraImageConverter",
    "description",       "Camera Image Converter RTC",
    "version",           "1.0.0",
    "vendor",            "Ogata Laboratory, Waseda Univ.",
    "category",          "Experimental",
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
CameraImageConverter::CameraImageConverter(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CameraImageConverter::~CameraImageConverter()
{
}



RTC::ReturnCode_t CameraImageConverter::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraImageConverter::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraImageConverter::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraImageConverter::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CameraImageConverter::onActivated(RTC::UniqueId ec_id)
{
	m_out.height = m_height;
	m_out.width = m_width;
	m_out.pixels.length(m_height * m_width * 3);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraImageConverter::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraImageConverter::onExecute(RTC::UniqueId ec_id)
{
	if (m_inIn.isNew()) {
		m_inIn.read();
		if (m_width != m_in.data.image.width || m_height != m_in.data.image.height) {
			m_width = m_in.data.image.width;
			m_height = m_in.data.image.height;

			m_out.height = m_height;
			m_out.width = m_width;
			m_out.pixels.length(m_height * m_width * 3);
		}

		m_out.tm = m_in.data.captured_time;
		memcpy(&(m_out.pixels[0]), &(m_in.data.image.raw_data[0]), m_width * m_height * 3);
		m_outOut.write();
	}
	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraImageConverter::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraImageConverter::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraImageConverter::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraImageConverter::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraImageConverter::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CameraImageConverterInit(RTC::Manager* manager)
  {
    coil::Properties profile(cameraimageconverter_spec);
    manager->registerFactory(profile,
                             RTC::Create<CameraImageConverter>,
                             RTC::Delete<CameraImageConverter>);
  }
  
};


