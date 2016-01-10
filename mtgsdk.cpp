#include "mtgsdk.h"
#include <stdio.h>
#include <sys/time.h>

namespace
{
#define STR_BUFSIZE_LENG  (sizeof(stsendinfor) - kMaxBufferSize)
  const int  kHeadBufferSize      = 0x5A5AA5A5;
  const int  kJoinUidResMax       = 10;
  const char kVideoLivePathHead[] = "/video/live";
  const char kAudioLivePathHead[] = "/audio";
  const char kSendPathHead[]      = "/video/live";
  const char kRosterPathHead[]    = "/roster";
  const int  kNetRosterPriority   = 1;
  const char kMtgSoFile[]         = "mtgsdk.so";
   
  static int calc_result_time(struct timeval *result, struct timeval *after,
							  struct timeval *before)
  {
	/* Perform the carry for the later subtraction by updating "before" */
	if (after->tv_usec < before->tv_usec) {
	  int nsec = (before->tv_usec - after->tv_usec) / 1000000 + 1;
	  before->tv_usec -= 1000000 * nsec;
	  before->tv_sec += nsec;
	}
	if (after->tv_usec - before->tv_usec > 1000000) {
	  int nsec = (after->tv_usec - before->tv_usec) / 1000000;
	  
	  before->tv_usec += 1000000 * nsec;
	  before->tv_sec -= nsec;
	}
	/* Compute the time remaining to wait, tv_usec is certainly positive.
	 * */
	result->tv_sec = after->tv_sec - before->tv_sec;
	result->tv_usec = after->tv_usec - before->tv_usec;
	/* Return 1 if result is negative. */
	return after->tv_sec < before->tv_sec;
  }


  static void UserIDToSeq(short int uid, char* pSeq, int len) {
	BYTE b1 = uid % 253;
	BYTE b2 = uid / 253;
	
	b1++;
	if (b1 >= '/')
	  b1++;
	
	if (b1 >= '\\')
	  b1++;
	
	b2++;
	if (b2 >= '/')
	  b2++;
	
	if (b2 >= '\\')
	  b2++;
	
	pSeq[0] = b2;
	pSeq[1] = b1;
  }
  
  static WORD UserSeqToID(const char* seq) {
	if (NULL == seq) 
	  return 0;
	
	BYTE bt1;
	BYTE bt2;
	bt2 = *(BYTE*) seq;
	bt1 = *(BYTE*) (seq + 1);
	
	if (bt2 > '/') 
	  bt2--;
	
	if (bt2 > '\\') 
	  bt2--;
	
	bt2--;
	
	if (bt1 > '/') 
	  bt1--;

	if (bt1 > '\\')
	  bt1--;
	return (bt2 * 253 + bt1);
  }

  int DoVideoRecvData(WxDataUpdate * ds,MtgSdk * pPlane )
  {
	if ((ds == NULL) ||
		(ds->uid.data == NULL) ||
		(ds->param_bs.data == NULL &&
		 ds->action != MTG_ACTION_VIDEO_DESTROY &&
		 ds->action != MTG_ACTION_VIDEO_CREATE)) {
	  return -1;
	}

	//  MTG_ACTION_VIDEO_CREATE == 1  MTG_ACTION_BINARY_CREATE == 1
	
	if (ds->action == MTG_ACTION_VIDEO_CREATE) {
	  
	} else if (ds->action ==  MTG_ACTION_BINARY_CREATE) {
		
	} else if (ds->action == MTG_ACTION_VIDEO_DATA) {
	 
	} else if(ds->action == MTG_ACTION_VIDEO_DESTROY) {
	  /*用户离开*///对于状态3的判断需要拿到外面来做
	}
	
	return 1;
  }

  int DoAudioRecvData(WxDataUpdate * ds,MtgSdk * pPlane)
  {
	if ((ds == NULL) ||
		(ds->uid.data == NULL) ||
		(ds->param_bs.data == NULL &&
		 ds->action != MTG_ACTION_VIDEO_DESTROY &&
		 ds->action != MTG_ACTION_VIDEO_CREATE)) {
	  return -1;
	}
	
	if (ds->action == MTG_ACTION_AUDIO_CREATE) {
	  printf("MTG: audio create\n");
	} else if (ds->action == MTG_ACTION_BINARY_CREATE) {
	  printf("MTG: binary create\n");
	} else if (ds->action == MTG_ACTION_AUDIO_DATA) {

	  
	  
	} else if (ds->action == MTG_ACTION_AUDIO_DESTROY) {
	  printf("MTG: audio destroy\n");
	}
	
	return 1;
  }
  
  int  NetVideoRecvData( void* user_data,tMtgConfID conf_id,short msg,DWORD uParam1, DWORD uParam2, void* pParam)
  {
	
	MtgSdk * pPlane = (MtgSdk *) user_data;
	if (!pPlane) 
	  return 0;
	
	WxDataUpdate * ps = (WxDataUpdate *)pParam;     
	for (DWORD i = 0;i < uParam2;i ++) {
	  DoVideoRecvData(ps,pPlane);
	  ps++;
	}
	return uParam2;
  }

  int NetAudioRecvData(void* user_data, tMtgConfID conf_id,short msg,DWORD uParam1, DWORD uParam2, void* pParam)
  {
	MtgSdk * pPlane = (MtgSdk *) user_data;
	if (!pPlane) 
	  return 0;
	
	WxDataUpdate * ps = (WxDataUpdate *)pParam;     
	for (DWORD i = 0;i < uParam2;i ++) {
	  DoAudioRecvData(ps,pPlane);
	  ps++;
	}
	return uParam2;
  }

  int JoinCallback(void* user_data, tMtgConfID conf_id, short msg, DWORD uParam1, DWORD uParam2, void* pParam)
  {
	MtgSdk * pPlane = (MtgSdk *) user_data;
	if (!pPlane)
	  return 0;
	switch (msg) {
	case MTG_MSG_TYPE_JOINED: 
	  if (!pPlane->m_bJoinMtg) {
		if (uParam1 == 0) {
		  printf("Join Ok! \n");
		  pPlane->m_bJoinMtg = true;
		} else if (MTG_LEFT_REASON_CONNECT_FAILED == uParam1
				   || MTG_LEFT_REASON_WAIT_FOR_HOST == uParam1) {
		  printf("rejoin\n");
		  pPlane->m_bJoinMtg = false;
		} else {
		  printf("Join Failed, result=%d\n", uParam1);
		  pPlane->m_bJoinMtg = false;
		}
		sem_post(&pPlane->m_joinSem);
	  } else {
		printf("else user Join Ok! \n");
	  }
	  break;
	  
	case MTG_MSG_TYPE_RESOURCE_UPDATE:
	  NetVideoRecvData(user_data,conf_id, msg,uParam1, uParam2, pParam);
	  break;
	case MTG_MSG_TYPE_LEFT: 
	  break; 
	default:
	  printf("Join msg= %d\n", msg);
	  break;
	}
	return 0;
  }

} // namespace


void* MtgSdk::MtgHeartbeatThread(void* pParam) 
{
  MtgSdk* pSelf = (MtgSdk*) pParam;
  if (NULL != pSelf) {
	pSelf->MtgHeartbeat();
  }
  pthread_exit(NULL);
  return NULL;
}

void* MtgSdk::MtgAudioStreamThread(void* pParam) 
{
  MtgSdk* pSelf = (MtgSdk*) pParam;
  if (NULL != pSelf) {
	pSelf->MtgAudioStream();
  }
  pthread_exit(NULL);
  return NULL;
}

MtgSdk::MtgSdk() :m_bJoinMtg(false) 
{
  MtgLoadFunc();
  sem_init(&m_joinSem, 0, 0);
  m_bHeartbeat = false;
  memset(m_sendvideopath,0,128);
  memset(m_sendsdipath, 0, 128);
  memset(m_sendaudiopath, 0, 128);
  m_ready = false;
}

MtgSdk::~MtgSdk()
{
  MtgUnInit();
}


bool MtgSdk::MtgInit() {
  (*pfun_wx_mtg_init)(NULL, NULL, 1024 + getpid(), 2048 + getpid());
  int http_port = 0;
  int udp_port = 0;
  int tcp_port = 443;
  (*pfun_wx_mtg_set_setting)(NULL, MTG_SET_OPT_HTTP_PORT, NULL, (void*)&http_port);
  (*pfun_wx_mtg_set_setting)(NULL, MTG_SET_OPT_TCP_PORT, NULL, (void*)&tcp_port);
  (*pfun_wx_mtg_set_setting)(NULL, MTG_SET_OPT_UDP_PORT, NULL, (void*)&udp_port);

  m_bHeartbeat = true;
  pthread_attr_init(&m_heartbeatThreadAttr);
  if (0 != pthread_create(&m_heartbeatThreadId, &m_heartbeatThreadAttr,  MtgHeartbeatThread, this)) {
	printf("create thread failed\n");
	return false;
  }
  pthread_attr_init(&m_audioThreadAttr);
  if (0 != pthread_create(&m_audioThreadId,	&m_audioThreadAttr,	MtgAudioStreamThread, this)) {
  	printf("mtg create audio thread failed\n");
  }	
  sem_init(&m_exitSem, 0, 0);
  m_bJoinMtg = false;
  return true;
}

bool MtgSdk::MtgUnInit() {
  if (!m_bHeartbeat) 
	return false;

  MtgLeaveConf();
  
  m_bJoinMtg = false;
  m_bHeartbeat = false;
  sem_wait(&m_exitSem);
  pthread_join(m_heartbeatThreadId, NULL);
  pthread_join(m_audioThreadId, NULL);
  pthread_attr_destroy(&m_heartbeatThreadAttr);
  pthread_attr_destroy(&m_audioThreadAttr);
  sem_destroy(&m_exitSem);
  
  (*pfun_wx_mtg_uninit)(0);

  if (NULL != m_plibHandle) {
	  dlclose(m_plibHandle);
	  m_plibHandle = NULL;
  }
  sem_destroy(&m_joinSem);
  
  return true;
}

bool MtgSdk::MtgUserJoin() 
{
  StLongData lbData;
  char path[32];	
  lbData.data = (BYTE*)m_userSeq; 
  lbData.len =  3;
  

  int re = (*pfun_wx_mtg_register)(m_conf_handle, const_cast<char *>(kVideoLivePathHead),NetVideoRecvData,this);

  
  re = (*pfun_wx_mtg_register)(m_conf_handle, const_cast<char *>(kAudioLivePathHead),NetAudioRecvData,this);

  
  sprintf(path,  "%s/%s", kRosterPathHead, m_userSeq);
  re = MtgSendData(MTG_DATA_TYPE_BINARY, MTG_ACTION_BINARY_CREATE, MTG_ATTRIB_OWNED_BY_NODE, kNetRosterPriority, path, NULL, 0, 0, 0, &lbData);
  
  re = MtgSendData(MTG_DATA_TYPE_VIDEO, MTG_ACTION_VIDEO_CREATE, MTG_ATTRIB_OWNED_BY_NODE, kNetRosterPriority, m_sendvideopath, NULL, 0, 0, 0, &lbData);

  re = MtgSendData(MTG_DATA_TYPE_VIDEO, MTG_ACTION_VIDEO_CREATE, MTG_ATTRIB_OWNED_BY_NODE, kNetRosterPriority, m_sendsdipath, NULL, 0, 0, 0, &lbData);

  re = MtgSendData(MTG_DATA_TYPE_AUDIO, MTG_ACTION_AUDIO_CREATE, MTG_ATTRIB_OWNED_BY_NODE, kNetRosterPriority, m_sendaudiopath, NULL, 0, 0, 0, &lbData);
  
  m_ready = true;
  
  return re;
}

bool MtgSdk::MtgJoinConf(const char* pMtgIP, int confId,int uId) 
{
  m_strMtgIP = pMtgIP;
  m_confId = confId;
  m_userId = uId;
  UserIDToSeq(uId, m_userSeq, 3) ;
  printf("ip = %s,user id is %d,seq is %s,confId=%d\n", pMtgIP,m_userId, m_userSeq,confId);
  
  /*serverip,callback,this,siteid,confid,uid,seqid,confkey,null*/
  m_conf_handle = (*pfun_wx_mtg_join)(const_cast<char *>(m_strMtgIP.c_str()), JoinCallback, this, 0, m_confId, m_userId, m_userSeq, "wxplanform", NULL);
  if (NULL == m_conf_handle) {
	printf("conf_handle=NULL\n");
  }
  
  timespec tv;
  tv.tv_sec = time(NULL)+60;
  tv.tv_nsec = 0;
  
  sem_timedwait(&m_joinSem, &tv);
  
  if (!m_bJoinMtg) {
	  //printf("Join conf failed\n");
	return false;
  }

  return true;
}

bool MtgSdk::MtgLeaveConf() {
	printf("Leave Conf.\n");
	if (NULL != m_conf_handle) {
		char path[32];	
		sprintf(path, "%s/%s", kRosterPathHead,m_userSeq);	
		MtgSendData(MTG_DATA_TYPE_BINARY, MTG_ACTION_BINARY_DESTROY, MTG_ATTRIB_OWNED_BY_NODE, kNetRosterPriority, path, NULL, 0, 0, 0,  NULL);
	
		(*pfun_wx_mtg_leave)(m_conf_handle, 0);
		m_conf_handle = NULL;
		m_userId = 0;
		memset(m_userSeq, 0, sizeof(m_userSeq));
	}
	m_bJoinMtg = false;
	return true;
}

int	MtgSdk::MtgSendVideoData(char * pdata,int length)
{
  if(m_conf_handle == -1)
	return 0;
  WxDataUpdate update_item;
  update_item.data_type = MTG_DATA_TYPE_VIDEO;
  update_item.action = MTG_ACTION_VIDEO_DATA;
  update_item.attrib =  MTG_ATTRIB_OWNED_BY_NODE;
  update_item.priority = kNetRosterPriority;
  update_item.path = m_sendvideopath;
  update_item.uid.data = (BYTE*)m_userSeq; 
  update_item.uid.len = 3;
  
  update_item.param_dw = 0;
  update_item.param_dw2 = 0;
  update_item.param_dw3 = 0;
  update_item.param_bs.data = (BYTE*)pdata;
  update_item.param_bs.len = length;	
  //printf("pfun_wx_mtg_modify \n");
  return (*pfun_wx_mtg_modify)(m_conf_handle, 1, &update_item);
}

int	MtgSdk::MtgSendSDIData(char * pdata,int length)
{
  if (m_conf_handle == -1)
	return 0;
  WxDataUpdate update_item;
  update_item.data_type = MTG_DATA_TYPE_VIDEO;
  update_item.action = MTG_ACTION_VIDEO_DATA;
  update_item.attrib =  MTG_ATTRIB_OWNED_BY_NODE;
  update_item.priority = kNetRosterPriority;
  update_item.path = m_sendsdipath;
  update_item.uid.data = (BYTE*)m_userSeq; 
  update_item.uid.len = 3;
  
  update_item.param_dw = 0;
  update_item.param_dw2 = 0;
  update_item.param_dw3 = 0;
  update_item.param_bs.data = (BYTE*)pdata;
  update_item.param_bs.len = length;	
  //printf("pfun_wx_mtg_modify \n");
  return (*pfun_wx_mtg_modify)(m_conf_handle, 1, &update_item);
}


int	MtgSdk::MtgSendData(BYTE data_type, BYTE action, BYTE attrib, BYTE priority, tMtgPath path, StShortData* uid, DWORD param_dw, DWORD param_dw2, DWORD param_dw3, StLongData* param_bs)
{
  if(m_conf_handle == -1)
	return 0;
  WxDataUpdate update_item;
  update_item.data_type = data_type;
  update_item.action = action;
  update_item.attrib = attrib;
  //update_item.priority = priority;
  update_item.priority = kNetRosterPriority;
  update_item.path = path;
  if (uid) {
	update_item.uid.data = uid->data;
	update_item.uid.len = uid->len;
  }	else {
	update_item.uid.data = NULL;
	update_item.uid.len = 0;
  }
  update_item.param_dw = param_dw;
  update_item.param_dw2 = param_dw2;
  update_item.param_dw3 = param_dw3;
  if (param_bs)	{
	update_item.param_bs.data = param_bs->data;
	update_item.param_bs.len = param_bs->len;
  }	else {
	update_item.param_bs.data = NULL;
	update_item.param_bs.len = 0;
  }
  //printf("pfun_wx_mtg_modify \n");
  return (*pfun_wx_mtg_modify)(m_conf_handle, 1, &update_item);
}

void MtgSdk::MtgAudioStream() 
{
  while (m_bHeartbeat) {
	(*pfun_wx_mtg_detect_stream)(m_conf_handle, MTG_DATA_TYPE_AUDIO);
	usleep(10000);
  }
}

void MtgSdk::MtgHeartbeat() 
{
  while (m_bHeartbeat) {
	(*pfun_wx_mtg_timer)();
	usleep(1000);
  }
  sem_post(&m_exitSem);
}

bool MtgSdk::MtgLoadFunc() 
{
  m_plibHandle = dlopen(kMtgSoFile, RTLD_LAZY); //RTLD_LAZY
  if (NULL == m_plibHandle) {
	return false;
  }
  pfun_wx_mtg_init = (int (*)(char*, char*, unsigned short, unsigned short))
	dlsym(m_plibHandle, "wx_mtg_init");
  if (NULL == pfun_wx_mtg_init) {
	return false;
  }
  pfun_wx_mtg_uninit = (int (*)(DWORD))dlsym(m_plibHandle, "wx_mtg_uninit");
  if (NULL == pfun_wx_mtg_uninit) {
	return false;
  }
  pfun_wx_mtg_get_setting = (int (*)(s_handle_t, int, DWORD*, void*))dlsym(m_plibHandle, "wx_mtg_get_setting");
  if (NULL == pfun_wx_mtg_get_setting) {
	return false;
  }
  pfun_wx_mtg_set_setting = (int (*)(s_handle_t, int, DWORD*, void*))dlsym(m_plibHandle, "wx_mtg_set_setting");
  if (NULL == pfun_wx_mtg_set_setting) {
	return false;
  }
  pfun_wx_mtg_join = (s_handle_t (*)(char*, WxFunCallBack, void*, DWORD, DWORD, WORD, char*, char*, StMbyteData*))dlsym(m_plibHandle, "wx_mtg_join");
  if (NULL == pfun_wx_mtg_join) {
	return false;
  }
  pfun_wx_mtg_modify = (int (*)(s_handle_t, WORD, WxDataUpdate*))dlsym( m_plibHandle, "wx_mtg_modify");
  if (NULL == pfun_wx_mtg_modify) {
	return false;
  }
  pfun_wx_mtg_register = (int (*)(s_handle_t, char*, WxFunCallBack, void*))dlsym( m_plibHandle, "wx_mtg_register");
  if (NULL == pfun_wx_mtg_register) {
	return false;
  }
  pfun_wx_mtg_get_buffer_size = (int (*)(s_handle_t, BYTE, DWORD*))dlsym( m_plibHandle, "wx_mtg_get_buffer_size");
  if (NULL == pfun_wx_mtg_get_buffer_size) {
	return false;
  }
  pfun_wx_mtg_set_buffer_size = (int (*)(s_handle_t, BYTE, char*, DWORD))dlsym( m_plibHandle, "wx_mtg_set_buffer_size");
  if (NULL == pfun_wx_mtg_set_buffer_size) {
	return false;
  }
  pfun_wx_mtg_subscribe = (int (*)(s_handle_t, char*, BYTE))dlsym( m_plibHandle, "wx_mtg_subscribe");
  if (NULL == pfun_wx_mtg_subscribe) {
	return false;
  }
  pfun_wx_mtg_leave = (int (*)(s_handle_t, short))dlsym( m_plibHandle, "wx_mtg_leave");
  if (NULL == pfun_wx_mtg_leave) {
	return false;
  }
  pfun_wx_mtg_timer = (void (*)())dlsym( m_plibHandle, "wx_mtg_timer");
  if (NULL == pfun_wx_mtg_timer) {
	return false;
  }
  pfun_wx_mtg_detect_stream = (int (*)(s_handle_t, BYTE))dlsym( m_plibHandle, "wx_mtg_detect_stream");
  if (NULL == pfun_wx_mtg_detect_stream) {
	return false;
  }
  
  pfun_wx_mtg_rejoin = (int (*) (s_handle_t))dlsym(m_plibHandle, "wx_mtg_rejoin");
  if (NULL == pfun_wx_mtg_rejoin) {
	return false;
  }
  return true;
}
