#pragma once
#include <string>

namespace os {

class IPath {
public:
	virtual std::string  GetApplicationPath() = 0;	// /opt/twopitau/Sprites C:/Program Files/TwoPiTau.com/
	virtual std::string  GetUserPath() = 0;			// $HOME/.towpitau.com/Sprites/ or C:/Users/$user/AppData/Roaming/TwoPiTau.com/Sprites
	virtual std::string  GetSharedPath() = 0;		// /usr/local/share/twopitau.com or c:/ProgramData/TwoPiTau.com/Sprites
};

} // namespace os

