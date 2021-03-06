#include "messagecenter.h"

#include "../../common/logger/logger.h"

MessageCenter& MessageCenter::instance()
{
	static MessageCenter instance;

	return instance;
}

// Synonym to instance()
MessageCenter& MessageCenter::defaultCenter()
{
	return instance();
}

MessageCenter::MessageCenter()
{
	init();
}

MessageCenter::~MessageCenter()
{
	dispose();
}

bool MessageCenter::init()
{
	bool result = false;

	// Explicitly start processing queue
	m_queue.start();

	return result;
}

void MessageCenter::dispose()
{
	m_queue.stop();
}


// Public methods
void  MessageCenter::addObserver(const char* name, const EventObserverPtr& observer)
{
	string packedName(name);
	addObserver(packedName, observer);
}

void MessageCenter::addObserver(const string& name, const EventObserverPtr& observer)
{
	m_queue.addObserver(name, observer);

	DEBUG(m_queue.dumpObservers().c_str());
}

void MessageCenter::addObserver(const string& name, const EventObserverPtr& observer, const EventHandler& handler)
{
	m_queue.addObserver(name, observer, handler);

	DEBUG(m_queue.dumpObservers().c_str());
}

void MessageCenter::removeObserver(const EventObserverPtr& observer)
{
	m_queue.removeObserver(observer);

	DEBUG(m_queue.dumpObservers().c_str());
}

void MessageCenter::removeObserver(const string& name, const EventObserverPtr& observer)
{
	m_queue.removeObserver(name, observer);

	DEBUG(m_queue.dumpObservers().c_str());
}

void MessageCenter::removeObservers()
{
	m_queue.removeObservers();

	DEBUG(m_queue.dumpObservers().c_str());
}

void MessageCenter::post(const char* topic, const EventSourcePtr source, MessagePayloadBase* payload)
{
	EventMessageBase message = EventMessageBase(topic, source, payload);

	post(topic, message);
}

void MessageCenter::post(const string& topic, const EventSourcePtr source, MessagePayloadBase* payload)
{
	EventMessageBase message = EventMessageBase(topic, source, payload);

	post(topic, message);
}

void MessageCenter::post(const string& topic, EventMessageBase& event)
{
	event.topic = string(topic);
	m_queue.post(event);
}
