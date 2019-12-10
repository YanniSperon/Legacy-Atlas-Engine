#include "Convert.h"
#include <sstream>

namespace Atlas {

	glm::vec3 Convert::Vector3(const btVector3& vec)
	{
		return glm::vec3(vec[0], vec[1], vec[2]);
	}

	btVector3 Convert::Vector3(const glm::vec3& vec)
	{
		return btVector3(vec[0], vec[1], vec[2]);
	}

	std::vector<std::string> Convert::SeperateByDelimiter(const std::string& in, const char& delimiter)
	{
		std::vector<std::string> internal;
		std::stringstream ss(in);
		std::string token;

		while (getline(ss, token, delimiter)) {
			internal.push_back(token);
		}

		return internal;
	}

	std::string Convert::FormatSpaces(std::string in)
	{
		bool lastSpace = false;
		std::string output = "";
		for (int i = 0; i < in.size(); i++) {
			if (in.at(i) == ' ') {
				if (!lastSpace) {
					output += in.at(i);
				}
				lastSpace = true;
			}
			else {
				output += in.at(i);
				lastSpace = false;
			}
		}
		return output;
	}

	std::string Convert::Trim(std::string in)
	{
		std::string temp = std::string(in);
		LeftTrim(temp);
		RightTrim(temp);
		return temp;
	}

	void Convert::LeftTrim(std::string& in)
	{
		in.erase(in.begin(), std::find_if(in.begin(), in.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	void Convert::RightTrim(std::string& in)
	{
		in.erase(std::find_if(in.rbegin(), in.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), in.end());
	}
}