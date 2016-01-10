#ifndef _MTG_H_	// 
#define _MTG_H_
 

#define MTG_PATH_MAX_LEN		255
#define MTG_MAX_FILE_BUF_LEN	6000

#define MTG_HIGHEST_PRIORITY		0
#define MTG_LOWEST_PRIORITY		5

//#define MTG_MAJOR_VERSION			MAJOR_VERSION
//#define MTG_MINOR_VERSION			MINOR_VERSION

#define	MTG_ERROR_INVALID_PARAMETER		1
#define	MTG_ERROR_INVALID_STATE			2
#define	MTG_ERROR_LOW_LEVEL_FAILED		3
#define	MTG_ERROR_RESOURCE_CONFLICT		4
#define	MTG_ERROR_INVALID_PATH			5
#define	MTG_ERROR_INVALID_DATA_TYPE		6
#define	MTG_ERROR_INVALID_COMMAND			7
#define MTG_ERROR_INVALID_TOKEN_PATH		8
#define	MTG_ERROR_FILE_NOT_FOUND			9
#define	MTG_ERROR_FILE_INCORRECT_FORMAT	10
#define	MTG_ERROR_FILE_OP_FAILED			11
#define MTG_ERROR_NOT_IN_PLAYBACK_STATE	12
#define MTG_ERROR_PLAYBACK_COMPLETE		13
#define MTG_ERROR_INVALID_DATA_LEN		14

#define MTG_LEFT_REASON_CONNECT_FAILED				1
#define MTG_LEFT_REASON_HOST_LEFT						2
#define MTG_LEFT_REASON_DUPLICATE_UID					3
#define MTG_LEFT_REASON_NETWORK_BROKEN				4
#define	MTG_LEFT_REASON_UNCOVERED_RESOURCE_CONFLICT	5

#define MTG_LEFT_REASON_SERV_LICENCE_EXPIRE						1001
#define MTG_LEFT_REASON_MAX_CONCURRENT_MEETING_NUM				1002
#define MTG_LEFT_REASON_MAX_CONCURRENT_CLIENT_NUM				1003
#define MTG_LEFT_REASON_DB_MEETING_OPEN_1						1004
#define MTG_LEFT_REASON_DB_MEETING_OPEN_2						1005
#define MTG_LEFT_REASON_DB_USER_JOIN_1							1006
#define MTG_LEFT_REASON_DB_USER_JOIN_2							1007
#define MTG_LEFT_REASON_DB_CONN_BROKEN							1008
#define MTG_LEFT_REASON_TIME_DIFF_TOO_MUCH						1009
#define MTG_LEFT_REASON_VERSION_NOT_MATCH						1010
#define MTG_LEFT_REASON_MEETING_TIME_EXPIRE						1011

#define MTG_LEFT_REASON_NO_RESULT_SET							40020
#define MTG_LEFT_REASON_WEB_MAX_MEETING_NUM						40021
#define MTG_LEFT_REASON_WEB_MAX_CLIENT_NUM_IN_MEETING			40022
#define MTG_LEFT_REASON_WEB_MAX_CLIENT_NUM_IN_SITE				40023
#define MTG_LEFT_REASON_MEETING_IS_CLOSED						40024
#define MTG_LEFT_REASON_WAIT_FOR_HOST							40025
#define MTG_LEFT_REASON_WRONG_JOIN_TIME							40026
#define MTG_LEFT_REASON_MEETING_KEY_NOT_EXIST					40027

#define	MTG_MSG_TYPE_JOINED					1	
#define	MTG_MSG_TYPE_LEFT					2	
#define	MTG_MSG_TYPE_RESOURCE_UPDATE		3	
#define	MTG_MSG_TYPE_MSG_FROM_PEER			4
#define	MTG_MSG_TYPE_ACTION_REQUEST			5
#define MTG_MSG_TYPE_CLIENT_BUFFER_FULL		6	
#define MTG_MSG_TYPE_MSG_FROM_SERVER		7	
#define MTG_MSG_TYPE_PLAYBACK_COMPLETE		8	
#define MTG_MSG_TYPE_PLAYBACK_RESTART		9	
#define MTG_MSG_TYPE_SEND_DS_UPDATE			10	
												
#define	MTG_ATTRIB_INHERIT_PARENT			1
#define	MTG_ATTRIB_OWNERSHIP_MASK			6
#define	MTG_ATTRIB_NOT_OWNED				0
#define	MTG_ATTRIB_OWNED_BY_NODE			2
#define	MTG_ATTRIB_OWNED_BY_TOKEN			4
#define	MTG_ATTRIB_DELETE_IF_NOT_OWNED		8	
#define	MTG_ATTRIB_SELF_FLOW_CONTROL		0x10
#define	MTG_ATTRIB_NEVER_DELETE				0x20


#define	MTG_DATA_TYPE_LOCATE				0	
#define	MTG_DATA_TYPE_FOLDER				1
#define	MTG_DATA_TYPE_INTEGER				2
#define	MTG_DATA_TYPE_BINARY				3
#define	MTG_DATA_TYPE_TOKEN				4
#define	MTG_DATA_TYPE_DS_STREAM			5
#define	MTG_DATA_TYPE_VIDEO				6
#define	MTG_DATA_TYPE_AUDIO				7
#define MTG_DATA_TYPE_FILE				8
#define MTG_DATA_TYPE_STREAM				9
#define	MTG_DATA_TYPE_MAX					9

#define	MTG_ACTION_FOLDER_CREATE			1	
#define	MTG_ACTION_FOLDER_DESTROY			2

#define	MTG_ACTION_INT_CREATE				1	
#define	MTG_ACTION_INT_DESTROY				2
#define	MTG_ACTION_INT_CHANGE				3	
#define	MTG_ACTION_BINARY_CREATE			1	
#define	MTG_ACTION_BINARY_DESTROY			2
#define	MTG_ACTION_BINARY_REPLACE			3	

#define	MTG_ACTION_TOKEN_GRAB				1	
#define	MTG_ACTION_TOKEN_RELEASE			2

#define	MTG_ACTION_DS_STREAM_CREATE			1	
#define	MTG_ACTION_DS_STREAM_DESTROY		2
#define	MTG_ACTION_DS_STREAM_CONTENT		3	
#define	MTG_ACTION_DS_STREAM_MOUSE			4	

#define	MTG_ACTION_VIDEO_CREATE				1	
#define	MTG_ACTION_VIDEO_DESTROY			2
#define	MTG_ACTION_VIDEO_DATA				3	

#define	MTG_ACTION_AUDIO_CREATE				1
#define	MTG_ACTION_AUDIO_DESTROY			2
#define	MTG_ACTION_AUDIO_DATA				3


#define MTG_ACTION_FILE_CREATE			1	
#define MTG_ACTION_FILE_DESTROY			2
#define MTG_ACTION_FILE_REQUEST			3
#define MTG_ACTION_FILE_REQUEST_CANCEL	4	
#define MTG_ACTION_FILE_DATA				5
#define MTG_ACTION_FILE_REQUEST_COMPLETE	6	

#define MTG_ACTION_STREAM_CREATE			1
#define MTG_ACTION_STREAM_DESTROY			2
#define MTG_ACTION_STREAM_DATA			3

#define	MTG_SEND_PEER_FLAG_BROADCAST		0
#define	MTG_SEND_PEER_FLAG_TO_OWNER		1
#define MTG_SEND_PEER_FLAG_VIA_SERVER		2
#define MTG_SEND_PEER_FLAG_TO_UID			4


#define MTG_GET_OPT_USER_SEQ				1
#define MTG_GET_OPT_UPLOAD_TOTAL			2
#define MTG_GET_OPT_DOWNLOAD_TOTAL		3
#define MTG_GET_OPT_SERVER_TICK			4
#define MTG_GET_OPT_TOTAL_PLAYBACK_TICK	5
#define MTG_GET_OPT_CUR_PLAYBACK_TICK		6
#define MTG_GET_OPT_INCOMING_RECV			7
#define MTG_GET_OPT_INCOMING_DELETE		8
#define MTG_GET_OPT_OUTGOING_SEND			9
#define MTG_GET_OPT_OUTGOING_DELETE		10
#define MTG_GET_OPT_MSERVER_STATUS		11
#define MTG_GET_OPT_TBRECORD_VERSION		12	

#define MTG_SET_OPT_UDP_PORT				1
#define MTG_SET_OPT_TCP_PORT				2
#define MTG_SET_OPT_HTTP_PORT				3

#define MTG_SET_OPT_NEXT_PLAYBACK_TICK	4
#define MTG_SET_OPT_PLAYBACK_PAUSE		5
#define MTG_SET_OPT_PLAYBACK_RESUME		6
#define MTG_SET_OPT_INC_OUTGOING_DELETE	7
#define MTG_SET_OPT_UPLOAD_SPEED			8	

#define MTG_DLL_MODIFIER __declspec(dllimport)

#define MTG_CLIENT_PDU_TYPE_PHONE_CALL			101
#define MTG_CLIENT_PDU_TYPE_CHAT_DATA				102
#define MTG_CLIENT_PDU_TYPE_MESSAGE_DATA			103
#define MTG_CLIENT_PDU_TYPE_MSERVER_STATUS		104
#define MTG_CLIENT_PDU_TYPE_DB_QUERY_RESULT		105
#define MTG_CLIENT_PDU_TYPE_MEETING_TIME_REMAIN	106
#define MTG_CLIENT_PDU_TYPE_LOCK_RESOURCE			107
#define _SEQUENCEID_LEN			3

typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef void*	LPVOID;
typedef int				BOOL;

#define	FALSE			0
#define	TRUE			1

typedef DWORD s_handle_t;

typedef struct
{
	BYTE	len;
	BYTE*	data;
} StShortData;

typedef struct
{
	WORD	len;
	BYTE*	data;
} StMbyteData;

typedef struct
{
	DWORD	len;
	BYTE*	data;
} StLongData;

typedef DWORD	tMtgConfID;
typedef const char*	tMtgPath;

#include <list>



typedef	int (*s_callback_t)(void* user_data, u_int msg, s_handle_t handle, u_int uParam1, u_int uParam2, void* pParam);

typedef struct
{
	BYTE		data_type;
	BYTE			action;
	BYTE			attrib;			
	BYTE			priority;
	tMtgPath		path;
	StShortData	uid;			
	DWORD			param_dw;
	DWORD			param_dw2;
	DWORD			param_dw3;
	StLongData		param_bs;
	DWORD			reserved;
} WxDataUpdate;

typedef int (*WxFunCallBack)(
	void*			user_data, 
	tMtgConfID		conf_id, 
	short			msg, 
	DWORD			uParam1,
	DWORD			uParam2,
	void*			pParam);

extern "C" {

	int wx_mtg_init(
		char*			bind_ip, 
		char*			external_ip, 
		WORD			udp_port, 
		WORD			tcpip_port);

	int wx_mtg_uninit(
		DWORD			flag);

	int wx_mtg_get_setting(
		s_handle_t		conf_handle, 
		int				opt, 
		DWORD*			pdwValue, 
		void*			buf_data);

	int wx_mtg_set_setting(
		s_handle_t		conf_handle, 
		int				opt, 
		DWORD*			pdwValue, 
		void*			buf_data);

	s_handle_t wx_mtg_join(
		char*			server_ip, 
		WxFunCallBack	callback, 
		void*			callback_data, 
		DWORD			site_id, 
		tMtgConfID		conf_id, 
		WORD			user_seq, 
		char*			user_name, 
		char*			meeting_key, 
		StMbyteData*	data);

	int wx_mtg_rejoin(
		s_handle_t		conf_handle);

	int wx_mtg_detect_route(
		s_handle_t		conf_handle,
		const char*		path);

	int wx_mtg_modify(
		s_handle_t		conf_handle, 
		WORD			list_size, 
		WxDataUpdate*	update_list);

	int wx_mtg_sendto(
		s_handle_t		conf_handle, 
		tMtgPath		path, 
		DWORD			flag, 
		StMbyteData*	data);

	int wx_mtg_sendserver(
		s_handle_t		conf_handle,
		void*	pPwdx);

	int wx_mtg_register(
		s_handle_t		conf_handle, 
		tMtgPath		path, 
		WxFunCallBack	callback, 
		void*			callback_data);

	int wx_mtg_flow_control(
		s_handle_t		conf_handle, 
		BYTE		type, 
		WxFunCallBack	callback, 
		void*			callback_data);

	int wx_mtg_get_buffer_size(
		s_handle_t		conf_handle, 
		BYTE			priority,
		DWORD*			max_size);

	int wx_mtg_set_buffer_size(
		s_handle_t		conf_handle,
		BYTE			priority,
		tMtgPath		path,
		DWORD			max_buffer_size);

	int wx_mtg_subscribe(
		s_handle_t		conf_handle, 
		tMtgPath		path, 
		BYTE			turn_off);

	int wx_mtg_log(
		s_handle_t		conf_handle, 
		const char*			log_type,		// log_type, e.g. "1" 
		const char*			action,			// specific action,  e.g. "user add"
		const char*			action_info);	// additional action information,e.g. "new client join"

	int wx_mtg_query(
		s_handle_t		conf_handle,
		DWORD			query_id,
		char*			query_request);

	int wx_mtg_leave(
		s_handle_t		conf_handle, 
		short			reason); // 1: means terminate, 0: means leave

	void wx_mtg_timer();

	int wx_mtg_detect_stream(
		s_handle_t		conf_handle,
		BYTE			data_type);

	s_handle_t wx_mtg_openfile(
		const char*		file_name, 
		WxFunCallBack	callback, 
		void*			callback_data);

	int wx_mtg_savefile(
		s_handle_t		conf_handle,
		BOOL			bStart,
		const char*		file_name);
}

#endif // _MTG_H_
