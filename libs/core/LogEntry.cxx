//
// Created by darkboss on 9/13/20.
//

#include "LogEntry.h"

quasar::core::LogEntry::LogEntry(const quasar::core::LogLevel &level, const quasar::core::String &channel,
                                 const quasar::core::String &message,
                                 const quasar::core::LogEntry::time_point &timestamp)
		: mLevel(level)
		, mChannel(channel)
		, mMessage(message)
		, mTimestamp(timestamp) {}

const quasar::core::LogLevel &quasar::core::LogEntry::getLevel() const {
	return mLevel;
}

void quasar::core::LogEntry::setLevel(const quasar::core::LogLevel &level) {
	mLevel = level;
}

const quasar::core::String &quasar::core::LogEntry::getChannel() const {
	return mChannel;
}

void quasar::core::LogEntry::setChannel(const quasar::core::String &channel) {
	mChannel = channel;
}

const quasar::core::LogEntry::time_point &quasar::core::LogEntry::getTimestamp() const {
	return mTimestamp;
}

void quasar::core::LogEntry::setTimestamp(const quasar::core::LogEntry::time_point &timestamp) {
	mTimestamp = timestamp;
}

const quasar::core::String &quasar::core::LogEntry::getMessage() const {
	return mMessage;
}

void quasar::core::LogEntry::setMessage(const quasar::core::String &message) {
	mMessage = message;
}
