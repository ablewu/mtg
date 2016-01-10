#ifndef MTG_SDK_H
#define MTG_SDK_H

#include <pthread.h>
#include <string>
#include <vector>
#include <semaphore.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "mtg.h"

//#define _MTG_REMOTE_

using std::string;

class MtgSdk 
{
public:
  static void* MtgHeartbeatThread(void* pParam) ;
  static void* MtgAudioStreamThread(void* pParam) ;
  
public:
  MtgSdk();
  ~MtgSdk();
public:
  bool MtgInit() ;
  bool MtgUnInit() ;
  bool MtgUserJoin() ;
  bool MtgJoinConf(const char* pMtgIP, int confId,int uId) ;
  bool MtgLeaveConf();

  // different path
  int  MtgSendVideoData(char * pdata,int length);
  int  MtgSendSDIData(char * pdata,int length);

  s_handle_t MtgGetHandle(){ return m_conf_handle;};
  int  IsReadyToSend(void) {return m_ready;}
private:
  int	MtgSendData(BYTE data_type, BYTE action, BYTE attrib, BYTE priority, tMtgPath path, StShortData* uid, DWORD param_dw, DWORD param_dw2, DWORD param_dw3, StLongData* param_bs);
  void MtgAudioStream() ;
  void MtgHeartbeat();
  bool MtgLoadFunc() ;
  
public:
  sem_t m_joinSem;
  bool m_bJoinMtg;
  
  char m_listenSeq[4];
private:
  void* m_plibHandle;
  
  pthread_t m_heartbeatThreadId;
  pthread_attr_t m_heartbeatThreadAttr;
  
  pthread_t m_audioThreadId;
  pthread_attr_t m_audioThreadAttr;
  
  int m_confId;
  bool m_bHeartbeat;
  string m_strMtgIP;
  
  sem_t m_exitSem;
  
  
  char m_sendvideopath[128];
  char m_sendsdipath[128];
  char m_sendaudiopath[128];
  
  char m_userSeq[4];
  int  m_userId;
  s_handle_t m_conf_handle;
  int  m_ready;
private:
  
  int (*pfun_wx_mtg_init)(char*,char*,unsigned short,unsigned short);
  int (*pfun_wx_mtg_uninit)(DWORD );
  int (*pfun_wx_mtg_get_setting)(s_handle_t,int,DWORD*,void*);
  int (*pfun_wx_mtg_set_setting)(s_handle_t,int,DWORD*,void*);
  s_handle_t (*pfun_wx_mtg_join)(char*,WxFunCallBack,void*,DWORD,DWORD,WORD,char*,char*,StMbyteData*);
  int (*pfun_wx_mtg_modify)(s_handle_t,WORD,WxDataUpdate*);
  int (*pfun_wx_mtg_register)(s_handle_t,char*,WxFunCallBack,void*);
  int (*pfun_wx_mtg_get_buffer_size)(s_handle_t,BYTE,DWORD*);
  int (*pfun_wx_mtg_set_buffer_size)(s_handle_t,BYTE,char*,DWORD);
  int (*pfun_wx_mtg_subscribe)(s_handle_t,char*,BYTE);
  int (*pfun_wx_mtg_leave)(s_handle_t,short);
  void (*pfun_wx_mtg_timer)();
  int (*pfun_wx_mtg_detect_stream)(s_handle_t,BYTE);
  int (*pfun_wx_mtg_rejoin)(s_handle_t);
  
};

#endif	// MTG_SDK_H
