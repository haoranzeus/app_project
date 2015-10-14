#ifndef IPC_INTERFACE_
#define IPC_INTERFACE_

#include <sys/msg.h>
#include <sys/types.h>
#include <map>

int hello();


class MsgQueue {
	private:
		int32_t	_key;
		int32_t	_flag;
		int32_t	_queueId;
		static std::map<int32_t, int32_t> _sMsgQueueIdMap;	// a map for <key, ID>
		int32_t getMsgQueId(int32_t key, int32_t flag = IPC_NOWAIT);
	public:
		MsgQueue(int32_t key, int32_t flage = IPC_NOWAIT);
		~MsgQueue();
};
#endif
