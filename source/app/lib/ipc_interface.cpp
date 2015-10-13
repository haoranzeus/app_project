#include <stdio.h>
#include <map>
#include "ipc_interface.h"

int hello(){
	printf("Hello World!\n");
	return 0;
}

std::map<int32_t, int32_t> MsgQueue::_sMsgQueueIdMap;

// ==============================================================================
// class:	MsgQueue
// func name:	getMsgQueId
// permission:	private
// parameters:	key -- IPC key
// return:	XSI IPC message queue ID
// description:	Create a msg queue using a key if the msg is not exist.
// 		Get the msg queue ID of the key if the msg is exist.
// ==============================================================================
int32_t MsgQueue::getMsgQueId(int32_t key){
	int32_t msgID = -1;
	std::map<int32_t, int32_t>::iterator ite_pos;
	ite_pos = MsgQueue::_sMsgQueueIdMap.find(key);
	if (MsgQueue::_sMsgQueueIdMap.end() != ite_pos)	// if find the key in msg queue map
		msgID = ite_pos->second;	// return the id mapped the key
	else {					// if not find the key in msg queue map
		msgID = msgget((key_t)key, 0666 | IPC_CREAT);	// create msg queue
		if (-1 != msgID)
			MsgQueue::_sMsgQueueIdMap.insert(std::make_pair(key, msgID));
	}
	return msgID;
}

// ==============================================================================
// class:	MsgQueue
// func name:	MsgQueue
// permission:	public
// parameters:	key -- IPC key
// 		flag -- sendmsg flag, default is IPC_NOWAIT
// description:	Constructor of the class
// ==============================================================================
MsgQueue::MsgQueue(int32_t key, int32_t flag){
	_queueId = getMsgQueId(key);		// initialize the msg queue
	_key = key;				// save the key
	_flag = flag;				// save the flag, default is IPC_NOWAIT
}

// ==============================================================================
// class:	MsgQueue
// func name:	~MsgQueue
// permission:	public
// descritpion:	Destructor of the class
// ==============================================================================
MsgQueue::~MsgQueue(){
}

