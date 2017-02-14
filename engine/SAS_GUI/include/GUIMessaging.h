#pragma once
#include <string>

namespace SAS_GUI {

	#define CURSORTYPE 0xC
	#define GUIMANAGERID 0xBEEF
	#define EMPTYPAYLOAD -100

	enum class MESSAGETYPE {ADD, MODIFY, DELETE};

	struct Payload {
		int type;	// User determined type for synchronizing what components care about what payloads
		std::string texture;
		SDL_Rect cliprect;
		std::string description;

		Payload() 
			:type(EMPTYPAYLOAD)
		{

		}

		Payload(int type, std::string texture, SDL_Rect cliprect, std::string description) 
			: type(type)
			, texture(texture)
			, cliprect(cliprect)
			, description(description)
		{

		}

		Payload(const Payload& p) 
			: type(p.type)
			, texture(p.texture)
			, cliprect(p.cliprect)
			, description(p.description)
		{

		}

		Payload& operator=(const Payload& other) {
			this->type = other.type;
			this->texture = other.texture;
			this->cliprect = other.cliprect;
			this->description = other.description;

			return *this;
		}
	};

	struct Message {
		int senderid;
		int destid;
		MESSAGETYPE messagetype;
		Payload data;

		Message() {

		}

		Message(int sid, int dst, MESSAGETYPE msgtype, const Payload& data) 
			: senderid(sid)
			, destid(dst)
			, messagetype(msgtype)
			, data(data)
		{

		}
	};
}
