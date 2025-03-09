#include "PoolWorkerThread.h"
#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int threadID, IFinishedTask* finishedTask)
{
	this->id = threadID;
	this->finishedTask = finishedTask;
}

PoolWorkerThread::~PoolWorkerThread()
{
}

int PoolWorkerThread::getThreadID()
{
	return this->id;
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->action = action;
}

void PoolWorkerThread::run()
{
	if (this->action != nullptr) {
		this->action->onStartTask();
	}

	finishedTask->onFinished(this->id);

}
