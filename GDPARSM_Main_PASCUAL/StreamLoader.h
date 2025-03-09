#pragma once
#include "IETThread.h"
#include "IWorkerAction.h"

class IExecutionEvent;

class StreamLoader : public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamLoader(String path, IExecutionEvent* executionEvent);
	~StreamLoader();

private:
	void onStartTask() override;

	String path;
	IExecutionEvent* execEvent;
};

